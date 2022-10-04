#pragma once
//-
// ===========================================================================
// Copyright 2018 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
//+
//
// CLASS:    MLockMessage
//
// ****************************************************************************
//
// CLASS DESCRIPTION (MLockMessage)
//
//	This class is used to register callbacks for conditional node and
//	plug locking. These callbacks allow you to intercept events that
//	involve the internal testing of the lock flag on a node or
//	plug. If the node, or plug, is locked the assigned API callback
//	routine, if attached to the node, will be invoked, and, at this
//	time, you have the option to override the lock. This allows the
//	API programmer the ability to ignore a lock and allow a lock event
//	to occur. This allows the API programmer to adjust the level of
//	granularity on the locking mechanism. There are three levels of
//	locking callbacks.
//
//
//		\li <b>DAG Level Events</b>
//		\li <b>All Other Node Level Events</b>
//      \li <b>Plug Level Events</b>
//
//
// To remove a callback use MMessage::removeCallback.  All callbacks
// that are registered by a plug-in must be removed by that plug-in
// when it is unloaded. Failure to do so will result in a fatal error.
//
// ****************************************************************************

#include <maya/MMessage.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MLockMessage)

//! \ingroup OpenMaya
//! \brief Node and plug locking messages. 
/*!
    Plug locking was implemented with Maya 1.0. Individual plugs can
    be locked so that their values cannot be changed. The locking
    state is held within the plug. The plug's locked state can be
    changed via the API with the method MPlug::setLocked(bool), or, in
    MEL, using the command "setAttr -l {on,off}".

    The ability to lock nodes was added with Maya 4.5. Node locking
    prevents renaming, reparenting, deletion, and other node-related
    changes. It also restricts the ability to change the state of any
    plug locks. The intent is that the user relies upon plug locking
    first, to lock the desired plugs they don't want to change, and
    then uses node locking to lock the node itself. Node locking can
    be set via MEL command, "lockNode", or via
    MFnDependencyNode::setLocked(bool)

	MLockMessage class allows the API user to register callbacks that
	control how Maya handles locks. The registered callbacks are
	invoked whenever a query to the lock state is involved. Therefore,
	the callback would be called even if the node was not locked.

    When a callback is invoked, the API user will be given a decision
    variable where they can place their decision. This decision
    variable is a boolean, and the boolean can take on the following
    values:


    \li <b>true</b> - accept the default behavior. When the node/plug is
    locked the default behavior is to obey the lock. When the node/plug is
    unlocked the default behavior is to do the action/edit.
    \li <b>false</b> - deny the default behavior. When the node/plug is
    locked the default behavior is to deny/override the lock; thus
    allowing the edit/action to occur. When the node/plug is unlocked the
    default behavior is make the node/plug locked - without physically
    setting the lock bit.

	<b>Caveats</b>

	You must use caution when using these routines.  The flow of execution
	is interrupted when these callbacks are invoked. Therefore, you should
	make your decision in a timely maanner or a serious performance penalty
	will result. Also, you should NEVER try to alter the DG state while
	executing within callback.  This includes quering/assigning a plug's
	value.  You may, however, examine state information like the lock
	state of the plug/node.
*/
class OPENMAYA_EXPORT MLockMessage : public MMessage
{
public:
	//! Plug related locking events
    OPENMAYA_ENUM(LockPlugEvent,
		//! An invalid plug event received.
		kInvalidPlug = 0,
		//! User is trying to lock the plug.
		kPlugLockAttr,
		//! User is trying to unlock the plug.
		kPlugUnlockAttr,
		//! Plug lock query on plug value change.
		kPlugAttrValChange,
		//! Plug lock query on a remove attribute event.
		kPlugRemoveAttr,
		//! Plug lock query on a rename attribute event.
		kPlugRenameAttr,
		//! Plug lock query on a connect to a locked attribute.
		kPlugConnect,
		//! Plug lock query on a disconnect from a locked source attribute.
		kPlugDisconnect,
		//! Used for internal bounds checking.
		kLastPlug
	);

	//! DAG related locking events
    OPENMAYA_ENUM(LockDAGEvent,
		//! Invalid DAG event received.
		kInvalidDAG = 0,
		//! Lock query on group action.
		kGroup,
		//! Lock query on ungroup action.
		kUnGroup,
   		//! Lock query on reparent action.
		kReparent,
		//! Lock query on a child add action.
		kChildReorder,
		//! Lock query on an instance event.
		kCreateNodeInstance,
    	//! Lock query on node whose children will be instanced.
		kCreateChildInstance,
		//! Lock query on node whose parent will be instanced.
		kCreateParentInstance,
		//! Used for internal bounds checking.
		kLastDAG
	);

	//! Miscellaneous lock event types
    OPENMAYA_ENUM(LockEvent,
		//! Invalid node lock event received.
		kInvalid = 0,
		//! Lock query on a rename event.
		kRename,
		//! Lock query on a delete event.
		kDelete,
		//! Lock query on a lock event.
		kLockNode,
		//! Lock query on an unlock event.
		kUnlockNode,
		//! Lock query on an add attribute event.
		kAddAttr,
		//! Lock query on an remove attribute event.
		kRemoveAttr,
		//! Lock query on an rename attribute event.
		kRenameAttr,
		//! Lock query on an unlock attribute event.
		kUnlockAttr,
		//! Lock query on a lock attribute event.
		kLockAttr,
		//! Used for internal bounds checking.
		kLast
	);

	//! \brief Pointer to a dependency node lock event callback function.
	/*!
	\param[in,out] node Node for which the lock event occurred.
	\param[in,out] aux Auxiliary data used by some events. E.g. the attribute about to be added.
	\param[in] clientData Pointer to user-defined data supplied when the callback was registered.
	\param[in] eventType Type of node lock event which occurred.
	\param[out] decision Decision of the callback whether to allow (true) or disallow (false) the default action associated with the lock event.
	*/
	typedef void (*MLockEventFunction)( MObject &node,MObject &aux,void* clientData, MLockMessage::LockEvent eventType,bool &decision );

	//! \brief Pointer to a DAG lock event callback function.
	/*!
	\param[in,out] dagPath Path to the DAG node for which the lock event occurred.
	\param[in,out] otherPath Second DAG node used in some events. E.g. the new parent.
	\param[in] clientData Pointer to user-defined data supplied when the callback was registered.
	\param[in] eventType Type of DAG node lock event which occurred.
	\param[out] decision Decision of the callback whether to allow (true) or disallow (false) the default action associated with the lock event.
	*/
	typedef void (*MLockDagEventFunction)( MDagPath &dagPath,MDagPath &otherPath,void* clientData, MLockMessage::LockDAGEvent eventType,bool &decision );

	//! \brief Pointer to a plug lock event callback function.
	/*!
	\param[in,out] plug Plug for which the lock event occurred.
	\param[in,out] otherPlug Second plug used in some events. E.g. during connect and disconnect events.
	\param[in] clientData Pointer to user-defined data supplied when the callback was registered.
	\param[in] eventType Type of plug lock event which occurred.
	\param[out] decision Decision of the callback whether to allow (true) or disallow (false) the default action associated with the lock event.
	*/
	typedef void (*MLockPlugEventFunction)( MPlug &plug,MPlug &otherPlug,void * clientData, MLockMessage::LockPlugEvent eventType,bool &decision );

public:
	static MCallbackId  setNodeLockQueryCallback(
								MObject& node,
								MLockMessage::MLockEventFunction func,
								void *clientData = NULL,
								MStatus *status = NULL );
	static MCallbackId  setNodeLockDAGQueryCallback(
								MDagPath& path,
								MLockMessage::MLockDagEventFunction func,
								void *clientData = NULL,
								MStatus *status = NULL );
	static MCallbackId  setPlugLockQueryCallback(
								MPlug& plug,
								MLockMessage::MLockPlugEventFunction func,
								void *clientData = NULL,
								MStatus *status = NULL );
	static MCallbackId  setPlugLockQueryCallback(
								MObject& node,
								MLockMessage::MLockPlugEventFunction func,
								void *clientData = NULL,
								MStatus *status = NULL );

	static const char* className();

protected:
	// No protected.
};

OPENMAYA_NAMESPACE_CLOSE

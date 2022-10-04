#ifndef _MObject
#define _MObject
//
//-
// ===========================================================================
// Copyright 2017 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
//+
//
// CLASS:    MObject
//
// ****************************************************************************
//
// CLASS DESCRIPTION (MObject)
//
//  MObject is the generic class for accessing all Maya internal modelling,
//	animation and rendering Objects, collectively referred to as Model Objects,
//	through the API.  This includes all Dependency Graph (DG) Nodes, of which
//	Directed Acyclic Graph (DAG) Nodes are a subset.
//	
//	Each instance of an MObject represents a specific Node or Attribute on a
//	Node in the DG.  Under the C++ class scheme MObjects simply have type
//	MObject with no base or derived hierarchy.  However,  MObjects may be many
//	different types of Model objects, from Attributes to Xforms, including
//	components of geometry such as Control Vertices (CV), faces, edges and
//	vertices.  This allows many different types of objects to be moved accessed
//	through the API without undue concern on the part of plug-in developers for
//	the type of object being manipulated.
//
//	Since it is impractical to provide every applicable method on MObjects, the
//	methods applicable to Maya Objects are encapsulated in Function Sets.
//	Function Sets can be attached to compatible MObjects to provide an external
//	interface to methods appropriate to that MObject.
//
//  The link between an MObject and the role it performs as a Maya Model object,
//  as well as the compatibility between MObjects and Function Sets is managed
//  by the API Run-Time Type Identification (RTTI) system.  The two key concepts
//  of this system are the Maya Object type and the Function Set type (both in
//  MFn::Type).  All MObjects have one and only one Maya Object type.  All
//  Function Sets have one and only one Function Set type. MObjects may,
//  however, be compatible with many types of Function Sets.  This compatibility
//  follows the class hierarchy of the Function Sets.  Thus an MObject with Maya
//  Object type MFn::kNurbsSurface would be compatible with MFnNurbsSurface,
//  MFnDagNode, MFnDependencyNode, MFnNamedObject and MFnBase.
//
//	Any MObject can be queried with the MObject::hasFn() method to determine if
//	it is comaptible with a given Function Set.
//
//	The purpose of the Base Function Set (MFnBase) is to provide methods for
//	determining whether or not a Function Set is compatible with a given Maya
//	Object (MObject) type (MFn::Type) or a specific MObject.  See:
//					MFnBase::hasObj(MFn::Type)
//							and
//					MFnBase::hasObj(const MObject &)
//
//	As well, this Function Set provides virtual methods for determining the type
//	of a Function Set under the API RTTI system. 
//
// ****************************************************************************

#if defined __cplusplus

// ****************************************************************************
// INCLUDED HEADER FILES

#include <maya/MFn.h>
#include <maya/MTypes.h>
#include <stdio.h>

// ****************************************************************************
// DECLARATIONS

class MPtrBase;

BEGIN_INTERNAL_CLASS_FORWARD_DECLARE
class TapiObj;
class TtypeCheck;
END_INTERNAL_CLASS_FORWARD_DECLARE

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MObject)

//! \ingroup OpenMaya
//! Generic Class for Accessing Internal Maya Objects
/*!
Determine the exact type (MFn::Type) of an MObject within Maya.

Determine if an Object exists.

Determine if an Object is compatible with a specific Function Set.

  MObject is the generic class for accessing all Maya internal modelling,
  animation and rendering Objects, collectively referred to as Model Objects,
  through the API.  This includes all Dependency Graph (DG) Nodes, of which
  Directed Acyclic Graph (DAG) Nodes are a subset.
	
  Each instance of an MObject represents a specific Node or Attribute on a
  Node in the DG.  Under the C++ class scheme MObjects simply have type
  MObject with no base or derived hierarchy.  However,  MObjects may be many
  different types of Model objects, from Attributes to transforms, including
  components of geometry such as Control Vertices (CV), faces, edges and
  vertices.  This allows many different types of objects to be moved accessed
  through the API without undue concern on the part of plug-in developers for
  the type of object being manipulated.

  Since it is impractical to provide every applicable method in MObjects, the
  methods applicable to Maya Objects are encapsulated in Function Sets.
  Function Sets can be attached to compatible MObjects to provide an external
  interface to methods appropriate to that MObject.

  The link between an MObject and the role it performs as a Maya Model object,
  as well as the compatibility between MObjects and Function Sets is managed
  by the API Run-Time Type Identification (RTTI) system.  The two key concepts
  of this system are the Maya Object type and the Function Set type (both in
  MFn::Type).  All MObjects have one and only one Maya Object type.  All
  Function Sets have one and only one Function Set type. MObjects may,
  however, be compatible with many types of Function Sets.  This compatibility
  follows the class hierarchy of the Function Sets.  Thus an MObject with Maya
  Object type MFn::kNurbsSurface would be compatible with MFnNurbsSurface,
  MFnDagNode, MFnDependencyNode, MFnNamedObject and MFnBase.

  Use the apiType() method to determine the type (MFn::Type) of the Maya Model
  Object.

  Use hasFn() to determine if the Object is comaptible with a given Function Set.

  Use isNull() to determine if the internal Maya Object exists.

*/
class FND_EXPORT  MObject  
{
public:


	MObject();
	MObject( const MObject &other ); 
	~MObject();
	bool			hasFn( MFn::Type fs ) const;
	bool            isNull() const;
 
    MFn::Type		apiType() const;
	const char *    apiTypeStr() const;
 
	bool			operator == (const MObject &) const;
	bool			operator != (const MObject &) const;
	MObject &		operator =  (const MObject &);

	//! Null Object for use as default argument.
	static MObject  kNullObj;

protected:
// No protected members

private:
	bool			isFlagSet( short ) const;
	void			setFlag( short, bool );
	short			allFlags() const;
	
	friend class    ::TapiObj;
	friend class	MObjectHandle;
	friend class	::TtypeCheck;

	MPtrBase *		ptr;
	MFn::Type		tp;
	unsigned short	flags;
};

// ****************************************************************************
OPENMAYA_NAMESPACE_CLOSE

#endif /* __cplusplus */
#endif /* _MObject */

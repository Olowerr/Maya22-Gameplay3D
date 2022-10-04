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
// CLASS:    MItDependencyGraph
//
// ****************************************************************************

#include <maya/MFn.h>
#include <maya/MObject.h>
#include <maya/MObjectArray.h>
#include <maya/MPlug.h>
#include <maya/MPlugArray.h>
#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <maya/MDeprecate.h>


OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MItDependencyGraph)

//! \ingroup OpenMaya
//! \brief Dependency Graph Iterator.
/*!
  Iterate over Dependency Graph (DG) Nodes or Plugs starting at a specified
  root Node or Plug.

  Set and query the root of the iteration.

  Set and query the direction (downstream or upstream), traversal priority
  (depth first or breadth first) and level of detail (Node level or Plug
  level) and relationship (DG connection, dependency, evaluation graph) of the iteration.

  Set and disable a filter to iterate over only specific types (MFn::Type) of
  Nodes.

  Reset the root, filter, direction, traversal priority, relationship and level of detail
  of the iteration.

  Prune branches of the graph from iteration.

In Maya, all geometry, animation and rendering information is implemented
in nodes in the Dependency Graph (DG).  The DG includes the Directed Acyclic
Graph (DAG).  Therefore, all DAG nodes are also DG nodes.  The data on nodes
is associated with Attributes.  Attributes on nodes are connected to
Attributes on other nodes via plugs on the Attributes.  Plugs are, in effect
the external intefaces of Attributes.

The DG Iterator Class (MItDependencyGraph) provides methods for iterating
over either nodes or plugs, as well as methods for setting and querying the
characteristics and behaviour of the iterator.

This iterator will traverse all connected attributes upstream or
downstream from the root node of the traversal. For non root nodes,
only attributes that are affected by the incoming attribute to that
node will be traversed.  Hence, only nodes to which data from the root
node is flowing will be traversed. 

By default, the iterator does not traverse world-space attribute
dependencies (an example of a world-space dependency is that
translateX affects worldMatrix). The
setTraversalOverWorldSpaceDependents method can be used to enable such
traversal. Note that even when world-space traversal is enabled, the
iterator will only iterate to connected nodes. It does not iterate up
and down through the dag hierarchy.

You can set the relationships that the traversal will follow. The default is
kDependOn which traverses plug dependencies. The other options are kConnectedTo
which traverses node connections and kEvaluationGraph which traverses
evaluation graph dependencies.

The DG Iterator is used in conjunction with the Maya Object (MObject), plug
(MPlug), Maya Object Array (MObjectArray) and plug Array (MPlugArray)
classes.

It is also useful to use Function Sets specific to the nodes returned by
the iterator to query and modify the nodes in the DG.

The DG itself can be modified using a DG Modifer (MDGModifier).

Additionally, nodes can be added to and retrieved from selection lists using
the Selection List (MSelectionList) class and Selection List Iterator
(MItSelectionList).  This can be useful for obtaining the root node for an
iteration.

Attributes on the nodes can be manipulated using the Attribute Function Set
(MFnAttribute) and its derivations.
*/
class OPENMAYA_EXPORT MItDependencyGraph
{
public:
				//! Direction within the DG relative to root Node or Plug
                OPENMAYA_ENUM(Direction,
					//! From source to destination
					kDownstream,
					//! From destination to source
					kUpstream
				);

				//! Perform a depth first or breadth first traversal
                OPENMAYA_ENUM(Traversal,
					//! Away from root first
					kDepthFirst,
					//! Equidistant from root first
					kBreadthFirst
				);

				//! Level of detail of the iteration
                OPENMAYA_ENUM(Level,
					//!  Visit each Node at most once
					kNodeLevel,
					//! Visit each Plug at most once
					kPlugLevel
				);

                //! What kind of relationship to follow
                OPENMAYA_ENUM( Relationship,
                    //!  Traverse dependency (this is the default behavior)
                    kDependsOn,
                    //!  Traverse DG connection
                    kConnectedTo,
                    //!  Traverse evaluation graph
                    kEvaluationGraph
                );
                MItDependencyGraph ( MObject& rootNode,
									 MFn::Type filter = MFn::kInvalid,
									 Direction direction = kDownstream,
									 Traversal traversal = kDepthFirst,
									 Level level = kNodeLevel,
									 MStatus* ReturnStatus = NULL );
				MItDependencyGraph ( MPlug& rootPlug,
									 MFn::Type filter = MFn::kInvalid,
									 Direction direction = kDownstream,
									 Traversal traversal = kDepthFirst,
									 Level level = kPlugLevel,
									 MStatus* ReturnStatus = NULL );
				MItDependencyGraph( MObject& rootNode,
									MPlug& rootPlug,
									MIteratorType& infoObject,
									Direction direction = kDownstream,
									Traversal traversal = kDepthFirst,
									Level level = kNodeLevel,
									MStatus* ReturnStatus = NULL );
                MItDependencyGraph( MObject& rootNode,
                                    MFn::Type filter,
                                    Direction direction,
                                    Traversal traversal,
                                    Level level,
                                    Relationship relationship,
                                    MStatus* ReturnStatus = NULL );
                MItDependencyGraph( MPlug& rootPlug,
                                    MFn::Type filter,
                                    Direction direction,
                                    Traversal traversal,
                                    Level level,
                                    Relationship relationship,
                                    MStatus* ReturnStatus = NULL );
                MItDependencyGraph( MObject& rootNode,
                                    MPlug& rootPlug,
                                    MIteratorType& infoObject,
                                    Direction direction,
                                    Traversal traversal,
                                    Level level,
                                    Relationship relationship,
                                    MStatus* ReturnStatus = NULL );
	            ~MItDependencyGraph ();
	MStatus		reset();
	MStatus		resetTo( MObject& rootNode,
						 MFn::Type filter = MFn::kInvalid,
						 Direction direction = kDownstream,
						 Traversal traversal = kDepthFirst,
                         Level level = kNodeLevel,
                         Relationship relationship = kDependsOn );
	MStatus		resetTo( MPlug& rootPlug,
						 MFn::Type filter = MFn::kInvalid,
						 Direction direction = kDownstream,
						 Traversal traversal = kDepthFirst,
                         Level level = kPlugLevel,
                         Relationship relationship = kDependsOn );
	MStatus		resetTo( MObject* rootNode,
						 MPlug* rootPlug,
						 MIteratorType& infoObject,
						 Direction direction = kDownstream,
						 Traversal traversal = kDepthFirst,
                         Level level = kPlugLevel,
                         Relationship relationship = kDependsOn );
	MObject		rootNode( MStatus* ReturnStatus = NULL );
	MPlug		rootPlug( MStatus* ReturnStatus = NULL );
	MFn::Type	currentFilter( MStatus* ReturnStatus = NULL );
	MStatus		setCurrentFilter( MFn::Type filter = MFn::kInvalid );
	MStatus		resetFilter();
	bool		isPruningOnFilter( MStatus* ReturnStatus = NULL );
	MStatus		enablePruningOnFilter();
	MStatus		disablePruningOnFilter();
	bool		isDirectionDownStream(  MStatus* ReturnStatus = NULL );
	Direction	currentDirection(   MStatus* ReturnStatus = NULL );
	MStatus		toggleDirection( );
	bool		isTraversalDepthFirst(  MStatus* ReturnStatus = NULL );
	Traversal	currentTraversal(   MStatus* ReturnStatus = NULL );
	MStatus		toggleTraversal( );
	bool		atNodeLevel( MStatus* ReturnStatus = NULL );
	Level		currentLevel(   MStatus* ReturnStatus = NULL );
    Relationship currentRelationship( MStatus* ReturnStatus = NULL );
    MStatus     setCurrentRelationship( Relationship relationship );
	MStatus		setTraversalOverWorldSpaceDependents(bool val);
	bool		isTraversingOverWorldSpaceDependents(MStatus* ReturnStatus = NULL);
	MStatus		toggleLevel( );
    MStatus     next( );
	bool		isDone( MStatus* ReturnStatus = NULL );
	MStatus		prune( );

	OPENMAYA_DEPRECATED(2019, "Use MItDependencyGraph::currentItem instead.")
	MObject		thisNode( MStatus* ReturnStatus = NULL );

	MObject		currentItem( MStatus* ReturnStatus = NULL );

	bool		thisNodeHasUnknownType( MStatus* ReturnStatus = NULL );
	MPlug		thisPlug( MStatus* ReturnStatus = NULL );
	MPlug		previousPlug( MStatus* ReturnStatus = NULL );
	MStatus		getNodesVisited( MObjectArray& nodesVisted ) const;
	MStatus		getPlugsVisited( MPlugArray& plugsVisted ) const;
	MStatus		getNodePath( MObjectArray& path ) const;
	MStatus		getPlugPath( MPlugArray& path ) const;

	static const char*		className();

OPENMAYA_PRIVATE_NO_SWIG:
	MStatus     __next__();

protected:
// No protected members

private:
	void *					currentIterator;

	bool					objectsHasFnOnFilterOrList(const MObject& nodeObj,
													   const MObject& attrObj);

	void					getCurrentIteratorFromMObjectOrMPlug(MObject& rootNode,
																 MPlug&   rootPlug,
																 Direction direction,
																 Traversal traversal,
																 Level level,
                                                                 Relationship relationship,
																 MStatus* ReturnStatus);

	void					resetCurrentIteratorFromMObjectOrMPlug(MObject& rootNode,
															  MPlug&   rootPlug,
															  Direction direction,
															  Traversal traversal,
															  Level level,
                                                              Relationship relationship,
															  MStatus* ReturnStatus);

	MFn::Type				currentTypeFilter;
	bool					pruneOnNoMatch;

	MIntArray				filterList;
	bool					useFilterList;

};

OPENMAYA_NAMESPACE_CLOSE

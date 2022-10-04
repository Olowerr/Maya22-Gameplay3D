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
// CLASS:    MFnSubd
//
// ****************************************************************************

#include <maya/MFnDagNode.h>

// Default tolerance
#define kMFnSubdTolerance 1.0e-3

// Point equivalent tolerance
#define kMFnSubdPointTolerance 1.0e-10

OPENMAYA_MAJOR_NAMESPACE_OPEN

class MPoint;

// ****************************************************************************
// CLASS DECLARATION (MFnSubd)

//! \ingroup OpenMaya MFn
//! \brief Subdivision surface function set.
/*!
This function set provides access to subdivision surfaces. Objects of type
MFn::kSubdiv, MFn::kSubdivData, and MFn::kSubdivGeom are supported.
MFn::kSubdiv objects are shapes in the DAG, MFn::kSubdivGeom objects are the
raw geometry that the shapes use, and MFn::kSubdivData objects are the data
that is passed through dependency graph connections.

Maya implements fully hierarchical Catmull-Clark quad based subdivision
surfaces.  You can use them without any hierarchical edits, but their full
power is only realized when you do use the hierarchy.  Using the hierarchy
lets you access additional vertices on the existing faces.  For example,
a single 4 vertex plane can give you access, through hierarchy, to over
16,000,000 points at the finest level of the hierarchy (please don't try it).
Additionally, the points at the finer levels are created only as you need them
and only in the areas where you need them, giving you an implied level of
detail workflow.

The "base" mesh is sometimes used to describe the coarsest level of the
hierarchy.  Once we go one level finer (to level "1") all faces are four
sided (though not all vertices are of valence 4).  At that point, each face
can be considered to have 4 "children" faces.  Starting with a 4 vertex single
face plane, there will be 4 faces (and 9 vertices) at level 1, 16 faces (and 25 vertices) at level 2, etc.  You can go as deep as level 12.

Please consult Maya documentation on subdivision surfaces for more details.

<b>Subdivision Surface Construction</b>
Subdivision surfaces are created by specifying a base polygonal mesh,
hierarchical edits (optional) and creases (optional).

The base mesh contains a vertex list,
a list of vertex counts per-polygon, and a list of vertices that make up
the polygons.  If you are familiar with the creation of polygonal meshes,
this is exactly equivalent to that setup.  With a small set of limitations,
any polygonal object can be converted into a subdivision surface.  The
current limitations are:

	\li <b>non manifold geometry</b>
	The polygons must be manifold; i.e., an edge has at most two incident
	faces.

	\li <b>vertex valence</b>
	A vertex must have valence of at least 3, unless it's a boundary vertex
	in which case it needs the valence of at least 2.

	\li <b>polygon vertex count</b>
	Maximal vertex count in a single polygon is 256.

	\li <b>total vertex count</b>
	Maximal vertex count in a base mesh is ~8,000,000 (2^23).

The easiest way to create a subdivision surface is probably to use
polyToSubdiv MEL command to create it from a polygon.  Alternativelly,
the same functionality is available through the API using
<b>createFromPolygon</b> method.

Alternatively, you can create a subdivision surface either by converting
an existing NURBS surface with <b>createFromNurbsSurface</b> or directly, by
specifying vertex lists, vertex connections lists, etc.  The last method will
look familiar to those that have used <b>MFnMesh::create</b> method to create
a polygon.

The following lists are used by the create method to construct a
subdivision surface:


	\li <b>vertex list</b>
	All of the vertices for the subdivision surface are stored in
	a master vertex list which is an array indexed from 0 to numVertices()-1.
	Vertices in this list can be shared among polygons.

	\li <b>polygon count list</b>
	This is a list containing the number of vertices for each polygon. Each
	polygon in the mesh would have an entry in this list containing its
	number of vertices.

	\li <b>vertex connection list</b>
	This is a list of the vertex id's for each polygon. Since polygons can
	have different numbers of vertices, the polygon count list is
	used to determine which polygons are represented by the various
	sections of this list.


<b>Texture Coordinates (UV's)</b>
You can optionally specify texture (uv) coordinates. UV coordinates are 2-d
coordinates used for mapping textures to the polygons of a surface.
Each polygon contains as many UV's as it has vertices.  The UV values are
not shared and you can think of them as "owned" by a polygon, rather than
each vertex in that polygon.

<b>Subdivision Surface Component API Names</b>

In order to successfully use the subdivision surface API, you need to
familiarize yourself with the naming convention used for its components
within the API.

In the polygon case, we simply number the vertices 0, 1, ... N-1.  The faces
and the edges and the faces are numbered similarly.

For the subdivision surfaces, this is not the case, mostly because of the
hierarchical approach we took.  Since it would be prohibitive to instantiate
all the faces all the time (think of those 16M that can from just one original
face) the names have to be order of creation independent.

The simplest way to think about each API name is "start with a face and follow
a path into the finer levels of the hierarchy recording each turn along the
way".

Here's some details.  You should also consult <b>MFnSubdNames</b> class which
contains a number of helpful methods for interpreting, creating and modifying
the component API names.  While this will take some getting used to, the
good news is that instantiating more vertices does not change the names
of the existing ones (unless you're adding more level 0 vertices) so any
vertex animation, etc. will not be affected by a need to model more detail
into another part of the surface.



	\li <b>base face name</b>
	Each component API name is "rooted" at one of the faces in the original,
	coarsest (level 0, "base") mesh.  These faces are numbered 0, 1, etc.

	\li <b>level</b>
	Each component exists only at a single level.  The value ranges from 0
	to 12.

	\li <b>level 1 choice</b>
	Coarsest faces can have up to 256 sides.  Finer faces are always four
	sided.  This portion of the name lets us decide which of the possibly
	256 level 1 faces we are choosing.

	\li <b>path from level 1</b>
	Once we are at a level 1 face, we go down to a finer face by choosing
	one of the four children.  This is recorded as two bits per level,
	giving us a "path" down to the desired level.

	\li <b>vertex/edge choice</b>
	For all but level 0 faces, once we know the face, we just have to choose
	one of the four edges or vertices.  This value is usually 0 for the faces
	(it is ignored).  In the case of the level 0 faces, this contains the
	full index of the vertex within that face

	\li <b>storage</b>
	Subdivision surface components (vertex, faces, names) are stored
	as single unsigned 64 bit integers (MUint64 type is defined in MTypes.h).
	The above 5 values are compressed into the 64 bit int storage. For those
	that want the gory details, the following is the way the components are
    currently organized within the 64 bits of data. However you should use
    the 5 values above and not this 64 bit value as the way these 5 values
    are packed into the 64 bit value may change in future.  The contents of
    the 64 bits are presented here from the highest value bit down to the
    lowest:

		\li {1} - unused
		\li {23} - base face name
		\li {8} - level 1 choice
		\li {2} - unused
		\li {4} - level
		\li {24} - path
		\li {2} - unused

For the subdivision surfaces, the most important names are those of
the faces.  Given a face name, each vertex on that face is named based
on that face.  That does mean that each vertex will typically have
more than one name.  Maya will always give you a unique name by
choosing the one that is numerically the smallest (in the 64 bit
sense).
*/
class OPENMAYA_EXPORT MFnSubd : public MFnDagNode
{
	declareDagMFn(MFnSubd, MFnDagNode);

public:
    MObject createBaseMesh( bool reverseNormal,
							int numVertices, int numPolygons,
							const MPointArray& vertexArray,
							const MIntArray& polygonCounts,
							const MIntArray& polygonConnects,
							MObject parentOrOwner = MObject::kNullObj,
							MStatus* ReturnStatus = NULL );

	MObject		copy( const MObject& source,
					  MObject parentOrOwner = MObject::kNullObj,
					  MStatus* ReturnStatus = NULL );

	MObject		collapse( const int level,
						  bool makeNewNodeInvisible,
						  MStatus* ReturnStatus = NULL );

public:
	// Manual creation:

	int		 vertexBaseMeshAdd( double x, double y, double z,
									MStatus* ReturnStatus = NULL );
	MUint64		 polygonBaseMeshAdd( int vertexCount,
									 const int vertexIds[],
									 MStatus* ReturnStatus = NULL );
	MUint64		 polygonBaseMeshAddWithUVs( int vertexCount,
											const int vertexIds[],
											const double uValues[],
											const double vValues[],
											MStatus* ReturnStatus = NULL );
public:
	int		editsPending( MStatus* ReturnStatus = NULL ) const;
	void		editsUpdateAll( MStatus* ReturnStatus = NULL );

public:
	unsigned int levelMaxCurrent( MStatus* ReturnStatus = NULL ) const;
	unsigned int levelMaxAllowed( MStatus* ReturnStatus = NULL ) const;
	void		levelFullySubdivideTo( int level,
									   MStatus* ReturnStatus = NULL );
	unsigned int    vertexCount( int level = 0,
							 MStatus* ReturnStatus = NULL) const;
public:
	MUint64		vertexIdFromBaseVertexIndex( int baseVertexIndex,
										 MStatus* ReturnStatus = NULL) const;
	int		vertexBaseIndexFromVertexId( MUint64 vertexId,
										 MStatus* ReturnStatus = NULL) const;

	MStatus		vertexEditsGetAllNonBase( MUint64Array& vertexIds,
										  MVectorArray& edits,
							MSpace::Space space = MSpace::kObject ) const;
	MStatus		vertexEditsSetAllNonBase( const MUint64Array& vertexIds,
										  const MVectorArray& edits,
							MSpace::Space space = MSpace::kObject );
	MStatus		vertexEditsClearAllNonBase();

	MStatus		vertexPositionGet( MUint64 vertId, MPoint& position,
							MSpace::Space space = MSpace::kObject)const;
	MStatus		vertexEditGet( MUint64 vertId, MVector& edit,
							MSpace::Space space = MSpace::kObject ) const;
	MStatus		vertexPositionGetNoEdit( MUint64 vertId, MPoint& position,
							MSpace::Space space = MSpace::kObject )const;
	MStatus		vertexPositionSet( MUint64 vertId, const MPoint& position,
								   bool updateEdits,
								   MSpace::Space space = MSpace::kObject );
	MStatus		vertexEditSet( MUint64 vertId, const MVector& edit,
							   bool updateEdits,
								MSpace::Space space = MSpace::kObject );
	MStatus 	vertexBaseMeshGet( MPointArray& positions,
								MSpace::Space space = MSpace::kObject ) const;
	MStatus 	vertexBaseMeshSet( const MPointArray& positions,
								MSpace::Space space = MSpace::kObject );
	MStatus 	vertexBaseMeshGetWithId( MPointArray& positions,
									 MUint64Array& vertexIds,
								MSpace::Space space = MSpace::kObject ) const;
	MStatus 	vertexBaseMeshSetWithId( const MPointArray& positions,
										 const MUint64Array& vertexIds,
								MSpace::Space space = MSpace::kObject );
	int		vertexValence( MUint64 vertId,
							   MStatus* ReturnStatus = NULL ) const;
	MStatus		vertexNormal( MUint64 vertId, MVector& normal ) const;
	MStatus		vertexAdjacentVertices( MUint64 vertId,
										MUint64Array& vertList ) const;
	MStatus		vertexIncidentEdges( MUint64 vertId,
									 MUint64Array& edgeList ) const;
	MStatus		vertexIncidentPolygons( MUint64 vertId,
										MUint64Array& polyList ) const;
	bool		vertexIsBoundary( MUint64 vertId,
								  MStatus* ReturnStatus = NULL ) const;
	bool		vertexIsValid( MUint64 vertId,
							   MStatus* ReturnStatus = NULL ) const;
	bool		vertexIsCreased( MUint64 vertId,
								 MStatus* ReturnStatus = NULL ) const;
	bool		vertexCreaseRelevant( MUint64 vertId,
									  MStatus* ReturnStatus = NULL ) const;
	MStatus		vertexSetCrease( MUint64 vertId, bool creased ) const;
	MStatus		vertexChildren( MUint64 vertId, MUint64Array& children ) const;

public:
	MStatus		creasesGetAll( MUint64Array& vertexIds,
							   MUint64Array& edgeIds ) const;
	MStatus		creasesSetAll( const MUint64Array& vertexIds,
							   const MUint64Array& edgeIds );
	MStatus		creasesClearAll() const;
	MStatus		updateAllEditsAndCreases();

public:
	unsigned int    edgeCount( int level = 0,
						   MStatus* ReturnStatus = NULL ) const;
	MUint64		edgeBetween( MUint64 vertex1, MUint64 vertex2,
							 MStatus* ReturnStatus = NULL ) const;
	MStatus		edgeVertices( MUint64 edge, MUint64& v1, MUint64& v2 ) const;
	MStatus		edgeAdjacentPolygon( MUint64 edge, MUint64Array& polys ) const;
	bool		edgeIsBoundary( MUint64 edge,
								MStatus* ReturnStatus = NULL ) const;
	bool		edgeIsValid( MUint64 edgeId,
							 MStatus* ReturnStatus = NULL  ) const;
	bool		edgeIsCreased( MUint64 edgeId,
							   MStatus* ReturnStatus = NULL  ) const;
	bool		edgeCreaseRelevant( MUint64 edgeId,
									MStatus* ReturnStatus = NULL ) const;
	MStatus		edgeSetCrease( MUint64 edgeId, bool creased ) const;
	MStatus		edgeChildren( MUint64 edgeId, MUint64Array& children ) const;

public:
	unsigned int    polygonCount( int level = 0,
							  MStatus* ReturnStatus = NULL ) const;
	int        polygonCountMaxWithGivenBaseMesh( int level = 1,
								MStatus* ReturnStatus = NULL ) const;
	unsigned int	polygonVertexCount( MUint64 polyId,
									MStatus* ReturnStatus = NULL ) const;
	MStatus		polygonVertices( MUint64 polyId,
								 MUint64Array& vertIds ) const;
	unsigned int	polygonEdgeCount( MUint64 polyId,
								  MStatus* ReturnStatus = NULL ) const;
	MStatus		polygonEdges( MUint64 polyId,
							  MUint64Array& edgeIds ) const;
	bool		polygonIsValid( MUint64 polyId,
							   MStatus* ReturnStatus = NULL ) const;
	bool		polygonHasChildren( MUint64 polyId, MStatus* ReturnStatus = NULL ) const;
	MStatus		polygonChildren( MUint64 polyId, MUint64Array& children ) const;
	MStatus		polygonSubdivide( MUint64 polyId );

	MStatus		polygonSetUseUVs( MUint64 polyId, bool useThem );
	bool		polygonHasVertexUVs( MUint64 polyId,
									 MStatus* ReturnStatus = NULL );
	MStatus		polygonGetVertexUVs( MUint64 polyId,
									 MDoubleArray& uValues,
									 MDoubleArray& vValues ) const;
	MStatus		polygonSetVertexUVs( MUint64 polyId,
									 const MDoubleArray& uValues,
									 const MDoubleArray& vValues );
	MStatus		polygonGetCenterUV( MUint64 polyId,
									double& u, double& v ) const;

public:
	MStatus		evaluatePosition( MUint64 polyId, double u, double v,
								 bool uvNormalized, MPoint& ) const;
	MStatus		evaluateNormal( MUint64 polyId, double u, double v,
								 bool uvNormalized, MVector& nrml ) const;
	MStatus		evaluatePositionAndNormal( MUint64 polyId, double u, double v,
										   bool uvNormalized,
										   MPoint& pos, MVector& nrml ) const;
	bool		getCubicSpline( MUint64 polyId, MPointArray vertices,
								MStatus* ReturnStatus = NULL );

public:
    MStatus getConnectedShaders( unsigned int instanceNumber,
									 MObjectArray & shaders,
									 MUint64Array & faces,
									 MIntArray & indices ) const;
	MObject tesselate(  bool uniform, int depth, int sample,
						MObject parentOrOwner = MObject::kNullObj,
						MStatus* ReturnStatus = NULL );

	MObject tessellateViaNurbs( MObject parentOrOwner = MObject::kNullObj,
								MStatus* ReturnStatus = NULL );

	MStatus convertToNurbs( MObjectArray& newNurbsSurfaces );

	MStatus updateSubdSurface();

public:
	MStatus		 vertexBaseMeshAddWithIndex( double x, double y, double z,
											 int index );
BEGIN_NO_SCRIPT_SUPPORT:

 	declareDagMFnConstConstructor( MFnSubd, MFnDagNode );

	//!	NO SCRIPT SUPPORT
	bool		getCubicSpline( MUint64 polyId, MPoint vertices[16],
								MStatus* ReturnStatus = NULL );

END_NO_SCRIPT_SUPPORT:

protected:
	bool objectChanged( MFn::Type tp, MStatus* ReturnStatus ) override;

private:
	void *f_subdRef;
};

OPENMAYA_NAMESPACE_CLOSE

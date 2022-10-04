#ifndef _MFnNurbsSurface
#define _MFnNurbsSurface
// ===========================================================================
// Copyright 2018 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
//

// ****************************************************************************
//
// CLASS:    MFnNurbsSurface
//
// ****************************************************************************

// ****************************************************************************
// INCLUDED HEADER FILES

#include <maya/MFnDagNode.h>
#include <maya/MPoint.h>
#include <maya/MVector.h>
#include <maya/MObject.h>
#include <maya/MTesselationParams.h>
#include <maya/MObjectArray.h>
#include <maya/MDeprecate.h>

// ****************************************************************************
// DECLARATIONS

class MPtrBase;
class TnurbsCurvePtrArray;
class TcomponentList;
class TsurfaceCVComponent;
class TnurbsSurface;
struct ag_curve;

#define kMFnNurbsEpsilon  1.0e-3



typedef MStatus (MFnNurbsSurface::*setKnotsFnPtr)( unsigned int, double );
typedef int (MFnNurbsSurface::*numKnotsFnPtr)( MStatus* ) const;

OPENMAYA_MAJOR_NAMESPACE_OPEN


// ****************************************************************************
// CLASS DECLARATION (MFnNurbsSurface)

//! \ingroup OpenMaya MFn
//! \brief NURBS surface function set.
/*!
This is the function set for NURBS (Non-Uniform Rational B-spline) surfaces.

The shape of a NURBS surface is defined by an array of CVs (control
vertices), an array of knot values in the U direction and an array of knot
values in the V direction, a degree in U and in V, and a form in U and in V.

The U and V knot vectors for NURBS surfaces are of size
<b>(spansInU + 2*degreeInU -1)</b> and <b>(spansInV + 2*degreeInV -1)</b>.
Note: spans = numCVs - degree.

There are 3 possible "forms" for the surface in the U and V directions:
<b>open</b>, <b>closed</b> and <b>periodic</b>.  These forms are described
below. Note that the descriptions below apply to both the U and V directions.

The <b>open</b> and <b>closed</b> forms are quite similar, and in fact a closed
surface will become an open surface if either the first or last CV is moved so
that they are no longer coincident.  To create an open or closed
surface, of degree N, with M spans, you must provide M+N CVs.
This implies that for a degree N surface, you must specify at least N+1 CVs
to get a surface with a single span.

The number of knots required for the surface is M + 2N - 1.  If you want
the surface to start exactly at the first CV and end exactly
at the last CV, then the knot vector must be structured to have degree N
"multiplicity" at the beginning and end.  This means that the first N knots
must be identical, and the last N knots must be identical.

A <b>periodic</b> surface is a special case of a closed surface.  Instead of
having just the first and last CVs coincident, the last N CVs in the surface,
where N is equal to the degree, overlap the first N CVs.  This results in a
surface with no tangent break where the ends meet.  The last N CVs in a periodic
surface are permanently bound to the first N CVs, and Maya will not allow those
last N CVs to be repositioned.  If one or more of the first N CVs of the
surface are repositioned, the overlapping CV's will remain bound, and will
also be moved.

In order to create a periodic surface, you must specify at least 2N+1
CVs, so that that last N can overlap the first N and you still have 1
non-overlapping CV left.  The number of CVs required to create a
periodic surface is still N+M (with a lower limit of 2N+1), but you
must ensure that the positions of the last N CVs are identical to the
positions of the first N.

You still need M + 2N - 1 knots for a periodic surface, but the knot
values required are more restrictive than for open or closed surfaces
because of the overlap of the last N CVs.  The first N knots should be
specified at the beginning of the knot array as values { -(N-1),
-(N-2), ... 0 } in order to implement the overlap.  Additionally
there can be no knot multiplicity at the end of the surface, because
that would compromise the tangent continuity property.

<b>Managing different knot representations in external applications</b>

Note that some third party applications use a different format for
knots, where the number of knots required for a surface is M+2N+1
rather than M+2N-1 as used in Maya. Both knot representations are
equivalent mathematically. To convert from one of these external
representations into the Maya representation, simply omit the first
and last knots from the external representation when creating the Maya
representation. To convert from the Maya representation into the
external representation, add two new knots at the beginning and end of
the Maya knot sequence. The value of these new knots depends on the
existing knot sequence. For a knot sequence with multiple end knots,
simply duplicate the existing first and last knots once more, for
example:

Maya representation: {0,0,0,...,N,N,N}
External representation: {0,0,0,0,...,N,N,N,N}

For a knot sequence with uniform end knots, create the new knots
offset at an interval equal to the existing first and last knot
intervals, for example:

Maya representation: {0,1,2,...,N,N+1,N+2}
External representation: {-1,0,1,2,...,N,N+1,N+2,N+3}

*/
class OPENMAYA_EXPORT MFnNurbsSurface : public MFnDagNode
{
	declareDagMFn(MFnNurbsSurface, MFnDagNode);

public:
	//! Forms that a surface may take in a given parametric direction.
    OPENMAYA_ENUM(Form,
        kInvalid,	//!< \nop
        kOpen,		//!< Edges are independent.
        kClosed,	//!< Edges are coincident.
        kPeriodic,	//!< Edges overlap such that there is no break in tangency.
		kLast		//!< \nop
	);
    MObject 	create(	const MPointArray &controlVertices,
						const MDoubleArray &uKnotSequences,
						const MDoubleArray &vKnotSequences,
						unsigned int degreeInU,
						unsigned int degreeInV,
						Form formU,
						Form formV,
						bool createRational,
						MObject parentOrOwner = MObject::kNullObj,
						MStatus* ReturnStatus = NULL );
	MObject     copy( const MObject &source,
					  MObject parentOrOwner = MObject::kNullObj,
					  MStatus* ReturnStatus = NULL );
	MObject     getDataObject() const;
	MObject 	cv( unsigned int indexU, unsigned int indexV,
						MStatus * ReturnStatus = NULL );
	MObject		cvsInU( unsigned int startIndex,
					    unsigned int endIndex,
						unsigned int rowIndex,
						MStatus * ReturnStatus = NULL );
	MObject		cvsInV( unsigned int startIndex,
						unsigned int endIndex,
						unsigned int rowIndex,
						MStatus * ReturnStatus = NULL );
	MStatus		getCVs( MPointArray& array,
						MSpace::Space space = MSpace::kObject ) const;
	MStatus		setCVs( const MPointArray& array,
						MSpace::Space space = MSpace::kObject );
	MStatus		getCV( unsigned int indexU, unsigned int indexV, MPoint& pnt,
					   MSpace::Space space = MSpace::kObject) const;
	MStatus		setCV( unsigned int indexU, unsigned int indexV, MPoint& pnt,
					   MSpace::Space space = MSpace::kObject) const;
	Form		formInU( MStatus * ReturnStatus = NULL ) const;
	Form		formInV( MStatus * ReturnStatus = NULL ) const;
	bool		isBezier( MStatus * ReturnStatus = NULL ) const;
	bool		isUniform( MStatus * ReturnStatus = NULL ) const;
	bool		isKnotU( double param, MStatus * ReturnStatus = NULL ) const;
	bool		isKnotV( double param, MStatus * ReturnStatus = NULL ) const;
	bool		isParamOnSurface( double paramU, double paramV,
						MStatus * ReturnStatus = NULL ) const;
	MStatus		getKnotDomain( double &startU, double &endU, double &startV,
						double &endV ) const;
	int			degreeU( MStatus * ReturnStatus = NULL ) const;
	int			degreeV( MStatus * ReturnStatus = NULL ) const;
	int			numSpansInU( MStatus * ReturnStatus = NULL ) const;
	int			numSpansInV( MStatus * ReturnStatus = NULL ) const;
	int			numNonZeroSpansInU( MStatus * ReturnStatus = NULL ) const;
	int			numNonZeroSpansInV( MStatus * ReturnStatus = NULL ) const;
	int			numCVsInU( MStatus * ReturnStatus = NULL ) const;
	int			numCVsInV( MStatus * ReturnStatus = NULL ) const;
	int			numKnotsInU( MStatus * ReturnStatus = NULL ) const;
	int			numKnotsInV( MStatus * ReturnStatus = NULL ) const;
	MStatus		getKnotsInU( MDoubleArray &array ) const;
	MStatus		getKnotsInV( MDoubleArray &array ) const;
	MStatus		setKnotsInU( const MDoubleArray &array, unsigned int startIndex,
						unsigned int endIndex );
	MStatus		setKnotsInV( const MDoubleArray &array, unsigned int startIndex,
						unsigned int endIndex );
	double		knotInU( unsigned int index, MStatus * ReturnStatus = NULL ) const;
	double		knotInV( unsigned int index, MStatus * ReturnStatus = NULL ) const;
	MStatus		setKnotInU( unsigned int index, double param );
	MStatus		setKnotInV( unsigned int index, double param );
	MStatus		removeKnotInU( double atThisParam, bool removeAll = false );
	MStatus		removeKnotInV( double atThisParam,  bool removeAll = false );
	MStatus		removeOneKnotInU( double atThisParam );
	MStatus		removeOneKnotInV( double atThisParam );
    MVector		normal( double paramInU, double paramInV,
						MSpace::Space space = MSpace::kObject,
						MStatus * ReturnStatus = NULL ) const;
    MStatus		getTangents( double paramInU, double paramInV,
						MVector &vectorInU, MVector &vectorInV,
						MSpace::Space space = MSpace::kObject) const;
    MStatus		getDerivativesAtParm( double paramInU, double paramInV,
									  MPoint &pos, MVector &dU, MVector &dV,
									  MSpace::Space space,
									  MVector * dUU = NULL,
									  MVector * dVV = NULL,
									  MVector * dUV = NULL) const;
	bool		isFoldedOnBispan() const;
	double		area( double tolerance = kMFnNurbsEpsilon,
						MStatus * ReturnStatus = NULL ) const;

	double		area( MSpace::Space space,
						double tolerance = kMFnNurbsEpsilon,
						MStatus * ReturnStatus = NULL ) const;

	MPoint		closestPoint( const MPoint &toThisPoint,
						double * paramU = NULL,
						double * paramV = NULL,
						bool ignoreTrimBoundaries = false,
						double tolerance = kMFnNurbsEpsilon,
						MSpace::Space space = MSpace::kObject,
						MStatus * ReturnStatus = NULL ) const;
	MPoint		closestPoint( const MPoint &toThisPoint,
						bool paramAsStart,
						double * paramU,
						double * paramV,
						bool ignoreTrimBoundaries = false,
						double tolerance = kMFnNurbsEpsilon,
						MSpace::Space space = MSpace::kObject,
						MStatus * ReturnStatus = NULL ) const;
	bool		isPointOnSurface( const MPoint &point,
						double tolerance = kMFnNurbsEpsilon,
						MSpace::Space space = MSpace::kObject,
						MStatus * ReturnStatus = NULL ) const;
	MStatus		getParamAtPoint( const MPoint & atThisPoint,
						double &paramU, double &paramV,
						bool ignoreTrimBoundaries,
						MSpace::Space space = MSpace::kObject,
						double tolerance = kMFnNurbsEpsilon) const;
	MStatus		getPointAtParam( double paramU, double paramV, MPoint &point,
						MSpace::Space space = MSpace::kObject) const;
	double		distanceToPoint( const MPoint &pt,
						MSpace::Space space = MSpace::kObject,
						MStatus * ReturnStatus = NULL ) const;
	MObject		tesselate( MTesselationParams & parms =
						MTesselationParams::fsDefaultTesselationParams,
                        MObject parentOrOwner = MObject::kNullObj,
						MStatus * ReturnStatus = NULL );

	bool		intersect( const MPoint &rayStartingPoint,
						const MVector &alongThisDirection,
						double &u, double &v,
						MPoint &intersectionData,
						double tolerance = kMFnNurbsEpsilon,
						MSpace::Space space = MSpace::kObject,
						bool calculateDistance = false,
						double * distance = NULL,
						bool calculateExactHit = false,
						bool* wasExactHit = NULL,
						MStatus* ReturnStatus = NULL ) const;
	bool		intersect( const MPoint &rayStartingPoint,
						const MVector &alongThisDirection,
						MDoubleArray &u, MDoubleArray &v,
						MPointArray &intersectionData,
						double tolerance = kMFnNurbsEpsilon,
						MSpace::Space space = MSpace::kObject,
						bool calculateDistance = false,
						MDoubleArray * distances = NULL,
						bool calculateExactHit = false,
						bool* wasExactHit = NULL,
						MStatus* ReturnStatus = NULL ) const;

	bool		hasHistoryOnCreate( MStatus * ReturnStatus = NULL ) const;
	MStatus		updateSurface();

	//! Boundary types for trimmed surfaces
    OPENMAYA_ENUM(BoundaryType,
		kInvalidBoundary,   //!< \nop
		kOuter,			    //!< Outer boundary, counter clockwise.
		kInner,			    //!< Inner boundary, clockwise.
		kSegment,		    //!< Curve on a face.
		kClosedSegment	    //!< Closed curve on a face.
	);
	bool		isTrimmedSurface( MStatus * ReturnStatus = NULL ) const;
	unsigned int	numRegions( MStatus * ReturnStatus = NULL ) const;
	bool		isFlipNorm( unsigned int region, MStatus * ReturnStatus = NULL ) const;
	unsigned int	numBoundaries( unsigned int region, MStatus * ReturnStatus = NULL);
	BoundaryType boundaryType( unsigned int region, unsigned int boundary,
						MStatus * ReturnStatus = NULL );
	unsigned int     numEdges( unsigned int region, unsigned int boundary,
    					MStatus * ReturnStatus = NULL );
	MObjectArray edge( unsigned int region, unsigned int boundary, unsigned int edge,
				 	 	bool paramEdge = false,
						MStatus * ReturnStatus = NULL );

	bool        isPointInTrimmedRegion( double u, double v,
						MStatus * ReturnStatus = NULL );

	MStatus		getTrimBoundaries(MTrimBoundaryArray& result,
    							  unsigned int region,
    							  bool paramEdge = true);
	MStatus		trimWithBoundaries(const MTrimBoundaryArray& mBoundaries,
								   bool  flipNormal = false,
								   double e_tol = 1e-3,
								   double pe_tol = 1e-5,
								   bool  createNewRegion = false);
	MStatus 	projectCurve(const MDagPath& curve,
							 const MVector * direction = NULL,
				 			 bool constructionHistory = false );
	MStatus		trim(const MDoubleArray& locatorU, const MDoubleArray& locatorV,
						bool constructionHistory = false );

	// Support methods needed to do patch level explicit uv assignment and
	// editing.

	unsigned int     numPatches( MStatus * ReturnStatus = NULL ) const;
	unsigned int     numPatchesInU( MStatus * ReturnStatus = NULL ) const;
	unsigned int     numPatchesInV( MStatus * ReturnStatus = NULL ) const;

	// Explicit uv related methods..
	//
	int			numUVs( MStatus * ReturnStatus = NULL ) const;
	MStatus 	setUVs( const MFloatArray& uArray, const MFloatArray& vArray);
	MStatus 	getUVs( MFloatArray& uArray, MFloatArray& vArray ) const;
	MStatus		setUV( int uvId, float u, float v );
	MStatus		getUV( int uvId, float & u, float & v ) const;
	MStatus 	getPatchUV( int patchId, int cornerIndex,
									float & u, float & v ) const;
	MStatus 	getPatchUVs( int patchId, MFloatArray& uArray,
												MFloatArray& vArray) const;
	MStatus 	getPatchUVid( int patchId, int cornerIndex, int &uvId ) const;
	MStatus 	assignUV( int patchId, int cornerIndex, int uvId );
	MStatus		assignUVs( const MIntArray& uvCounts, const MIntArray& uvIds );
	MStatus		clearUVs( );
	MStatus		getAssignedUVs( MIntArray& uvCounts, MIntArray& uvIds) const;

	// Shader methods.
    MStatus     getConnectedShaders(
                            unsigned int instanceNumber,
                            MObjectArray & shaders,
							MIntArray & indices ) const;

	OPENMAYA_DEPRECATED(2019, "This method is obsolete and simply calls the overloaded MFnNurbsSurface::getParamAtPoint method with ignoreTrimBoundaries set to false.")
	MStatus		getParamAtPoint( const MPoint & atThisPoint,
						double &paramU, double &paramV,
						MSpace::Space space = MSpace::kObject) const;

	OPENMAYA_DEPRECATED(2019, "Use tesselate( MTesselationParams & parms, MObject parentOrOwner, MStatus * ReturnStatus ) instead.")
	MObject		tesselate( MTesselationParams & parms,
						MStatus * ReturnStatus );

BEGIN_NO_SCRIPT_SUPPORT:
 	declareDagMFnConstConstructor( MFnNurbsSurface, MFnDagNode );

END_NO_SCRIPT_SUPPORT:

protected:
	MObject		createMObject(MObject & parentOrOwner,
    						  TnurbsSurface * newSurface,
    						  MStatus * ReturnStatus);
	void *		surfacePtr() const;

	bool objectChanged( MFn::Type, MStatus * ) override;

	bool		getUVSetIndex( const MString * uvSetName,
								int & uvSet) const;
	bool		curveToMObjects(ag_curve*       crv,
    							MObjectArray&   curveArray,
    							MStatus         *ReturnStatus);
	bool		trimWithBoundariesInHistory(
								const TnurbsCurvePtrArray& boundaries,
								bool  flipnorm,
								double   e_tol,
								double   pe_tol,
								bool  createNewRegion,
								MStatus  *status);
private:
    // function used for both setKnotsInU() and setKnotsInV()
    MStatus setKnotsUsingFn( const MDoubleArray& array, unsigned int startIndex,
					 unsigned int endIndex, numKnotsFnPtr numKnotFn,
					 setKnotsFnPtr setKnotFn );

	inline void * updateGeomPtr() const;
	inline void * updateConstGeomPtr() const;

	TcomponentList * fCompList;
	TsurfaceCVComponent * fcvComp;
};

OPENMAYA_NAMESPACE_CLOSE

#endif /* _MFnNurbsSurface */

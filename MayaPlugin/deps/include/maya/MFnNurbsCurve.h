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
// CLASS:    MFnNurbsCurve
//
// ****************************************************************************

#include <maya/MFnDagNode.h>
#include <maya/MObject.h>

// ****************************************************************************
// DECLARATIONS

class MPtrBase;
class TnurbsCurve;
class TcomponentList;
class TcurveCVComponent;
class T4dDblMatrix;

OPENMAYA_MAJOR_NAMESPACE_OPEN

#define kMFnNurbsEpsilon  1.0e-3

// ****************************************************************************
// CLASS DECLARATION (MFnNurbsCurve)

//! \ingroup OpenMaya MFn
//! \brief NURBS curve function set. 
/*!
This is the function set for NURBS (Non-Uniform Rational B-Spline) curves.

The shape of a NURBS curve is defined by an array of CVs (control
vertices), an array of knot values, a degree, and a form.  There are 3
possible "forms" for the curve: <b>open</b>, <b>closed</b> and <b>periodic</b>.

The <b>open</b> and <b>closed</b> forms are quite similar, and in fact a
closed curve will become an open curve if either the first or last CV
is moved so that they are no longer coincident.  To create an open or
closed curve of degree N with M spans, you must provide M+N CVs.
This implies that for a degree N curve, you must specify at least N+1 CVs
to get a curve with a single span.

The number of knots required for a curve is M + 2N - 1. If you want
the curve to start exactly at the first CV and end exactly at the last
CV, then the knot vector must be structured to have degree N
"multiplicity" at the beginning and end.  This means that the first N
knots must be identical, and the last N knots must be identical.

A <b>periodic</b> curve is a special case of a closed curve.  Instead
of having just the first and last CVs coincident, the last N CVs in
the curve must overlap the first N CVs.  This results in a curve with
no tangent break at the seam where the ends meet.  The last N CVs in a
periodic curve are permanently bound to the first N CVs, and Maya will
not allow those last N CVs to be repositioned.  If one or more of the
first N CVs of the curve are repositioned, the overlapping CV's will
remain bound, and will also be moved.

In order to create a periodic curve, you must specify at least 2N+1
CVs, so that that last N can overlap the first N and you still have 1
non-overlapping CV left.  The number of CVs required to create a
periodic curve is still N+M (with a lower limit of 2N+1), but you must
ensure that the positions of the last N CVs are identical to the
positions of the first N.

You still need M + 2N - 1 knots for a periodic curve, but the knot
values required are more restrictive than for open or closed curves
because of the overlap at the ends, The difference between the
first N pairs of knots values should be equal to the difference
between the last N pairs.  Additionally there can be no knot
multiplicity at the ends of the curve, because that would compromise
the tangent continuity property. So an example knot sequence could
begin with knots at { -(N-2), -(N-1), ... , 0}.


<b>Managing different knot representations in external applications</b>

Note that some third party applications use a different format for
knots, where the number of knots required for a curve is M+2N+1
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

Maya representation: {0,0,0,...,N,N,N} <br>
External representation: {0,0,0,0,...,N,N,N,N} <p>

For a knot sequence with uniform end knots, create the new knots
offset at an interval equal to the existing first and last knot
intervals, for example:

Maya representation: {0,1,2,...,N,N+1,N+2} <br>
External representation: {-1,0,1,2,...,N,N+1,N+2,N+3} <p>



*/
class OPENMAYA_EXPORT MFnNurbsCurve : public MFnDagNode
{
	declareDagMFn(MFnNurbsCurve, MFnDagNode);

public:
	//! Forms that a curve may take.
    OPENMAYA_ENUM(Form,
        kInvalid,	//!< \nop
        kOpen,		//!< Ends are independent.
        kClosed,	//!< Endpoints are coincident.
        kPeriodic,	//!< Ends overlap such that there is no break in tangency.
        kLast		//!< \nop
	);
    MObject  	create(	const MPointArray &controlVertices,
						const MDoubleArray &knotSequences,
						unsigned int degree,
						Form agForm,
						bool create2D,
						bool createRational,
						MObject & parentOrOwner = MObject::kNullObj,
						MStatus* ReturnStatus = NULL );
	MObject  	createWithEditPoints( const MPointArray &editPoints,
						unsigned int degree,
						Form agForm,
						bool create2D,
						bool createRational,
						bool uniformParam,
						MObject & parentOrOwner = MObject::kNullObj,
						MStatus* ReturnStatus = NULL );
	MObject		create( const MObjectArray& sources,
						MObject & parentOrOwner = MObject::kNullObj,
						MStatus* ReturnStatus = NULL );
	MObject     copy (const MObject &source,
					  MObject &parentOrOwner = MObject::kNullObj,
					  MStatus* ReturnStatus = NULL);
	MStatus		reverse(bool constructionHistory = false);

	MStatus		makeMultipleEndKnots();

	MObject  	cv( unsigned int index, MStatus * ReturnStatus = NULL ) const;
	MStatus		getCV( unsigned int index, MPoint &pt,
						MSpace::Space space = MSpace::kObject ) const;
	MStatus		setCV( unsigned int index, const MPoint &pt,
						MSpace::Space space = MSpace::kObject );
	Form		form( MStatus * ReturnStatus = NULL ) const;
	int			degree( MStatus * ReturnStatus = NULL ) const;
	int			numCVs( MStatus * ReturnStatus = NULL ) const;
	int			numSpans( MStatus * ReturnStatus = NULL ) const;
	int			numKnots( MStatus * ReturnStatus = NULL ) const;
	MStatus		getKnotDomain( double &start, double &end ) const;
	MStatus		getKnots( MDoubleArray &array ) const;
    MStatus     setKnots( const MDoubleArray &array, unsigned int startIndex,
                          unsigned int endIndex );
	MStatus		setKnot( unsigned int index, double param );
	MObject  	cvs( unsigned int startIndex, unsigned int endIndex,
						MStatus * ReturnStatus = NULL ) const;
	MStatus		getCVs( MPointArray &array,
						MSpace::Space space = MSpace::kObject ) const;
	MStatus		setCVs( const MPointArray &array,
						MSpace::Space space = MSpace::kObject );
	double		knot( unsigned int index, MStatus * ReturnStatus = NULL ) const;
	MStatus		removeKnot( double atThisParam, bool removeAll = false );
	bool		isPointOnCurve( const MPoint &point,
								double tolerance = kMFnNurbsEpsilon,
								MSpace::Space space = MSpace::kObject,
								MStatus * ReturnStatus = NULL ) const;
	MStatus		getPointAtParam( double param, MPoint &point,
								MSpace::Space space = MSpace::kObject
								) const;
	MStatus		getParamAtPoint( const MPoint & atThisPoint, double &param,
								 MSpace::Space space = MSpace::kObject )
								 const;
	MStatus		getParamAtPoint( const MPoint & atThisPoint, double &param,
								 double tolerance,
								 MSpace::Space space = MSpace::kObject )
								 const;
	bool		isParamOnCurve( double param,
								MStatus * ReturnStatus = NULL ) const;
	MVector		normal( double param,
						MSpace::Space space = MSpace::kObject,
						MStatus * ReturnStatus = NULL ) const;
	MVector		tangent( double param,
						 MSpace::Space space = MSpace::kObject,
						 MStatus * ReturnStatus = NULL ) const;
    MStatus		getDerivativesAtParm( double param, MPoint &pos,
									  MVector &dU, MSpace::Space space,
									  MVector * dUU = NULL) const;
	bool		isPlanar( MVector * planeNormal = NULL,
							MStatus * ReturnStatus = NULL ) const;
	MPoint		closestPoint( const MPoint &toThisPoint,
								double * param = NULL,
								double tolerance = kMFnNurbsEpsilon,
								MSpace::Space space = MSpace::kObject,
								MStatus * ReturnStatus = NULL ) const;
	MPoint		closestPoint( const MPoint &toThisPoint,
							    bool paramAsGuess,
								double * param = NULL,
								double tolerance = kMFnNurbsEpsilon,
								MSpace::Space space = MSpace::kObject,
								MStatus * ReturnStatus = NULL ) const;
	double		distanceToPoint( const MPoint &pt,
								MSpace::Space space = MSpace::kObject,
								MStatus * ReturnStatus = NULL ) const;
	double		area( double tolerance = kMFnNurbsEpsilon,
							MStatus * ReturnStatus = NULL ) const;
	double		length( double tolerance = kMFnNurbsEpsilon,
							MStatus * ReturnStatus = NULL ) const;
	double		findParamFromLength( double partLength,
							MStatus * ReturnStatus = NULL ) const;
	double		findParamFromLength( double partLength,
							double tolerance, 
							MStatus * ReturnStatus = NULL ) const;
	double		findLengthFromParam( double param,
							MStatus * ReturnStatus = NULL ) const;
	bool        hasHistoryOnCreate( MStatus * ReturnStatus = NULL ) const;
	MStatus     updateCurve();

    MObject     rebuild( unsigned int spans, unsigned int degree=3,
                    unsigned int keepRange=1, unsigned int endKnots=0,
                    bool keepEndPoints=true, bool keepTangents=true,
                    bool keepControlPoints=false,
                    float tolerance=0.01f, MStatus * ReturnStatus = NULL) const;

BEGIN_NO_SCRIPT_SUPPORT:

 	declareDagMFnConstConstructor( MFnNurbsCurve, MFnDagNode );

END_NO_SCRIPT_SUPPORT:

protected:
	MObject		createMObject(MObject & parentOrOwner,
    						  TnurbsCurve * newCurve,
    						  MStatus * ReturnStatus);

	bool objectChanged( MFn::Type, MStatus * ) override;
private:
	inline void * updateGeomPtr() const;
	inline void * updateConstGeomPtr() const;
	bool fIsCurveData;
	TcomponentList * fCompList;
	TcurveCVComponent * fcvComp;
	T4dDblMatrix * fCurveDataMat;
};

OPENMAYA_NAMESPACE_CLOSE

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
// CLASS:    MFnAnimCurve
//
// ****************************************************************************

#include <maya/MFnDependencyNode.h>
#include <maya/MTime.h>
#include <maya/MAngle.h>
#include <maya/MDoubleArray.h>
#include <maya/MTimeArray.h>
#include <maya/MIntArray.h>
#include <limits.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MFnAnimCurve)

//! \ingroup OpenMayaAnim MFn
//! \brief  Anim Curve Function Set
/*!
  Create, query and edit Anim Curve Nodes and the keys internal to
  those Nodes.

  Create an Anim Curve Node and connect its output to any animatable
  attribute on another Node.

  Evaluate an Anim Curve at a particular time.

  Determine the number of keys held by an Anim Curve.

  Determine the time and value of individual keys, as well as the
  (angle,weight) or (x,y) values and type of key tangents.  The
  in-tangent refers to the tangent entering the key.  The out-tangent
  refers to the tangent leaving the key.

  Find the index of the key at, or closest to a particular time.

  Set the time and value of individual keys, as well as the type of
  the tangent to the curve entering (in-tangent) and leaving
  (out-tangent) the key, specify the tangent as either (angle,weight)
  or (x,y).

  Add and remove keys from an Anim Curve.  Anim Curves are implemented
  as Dependency Graph (DG) Nodes. Each Node can have indexed keys.

  There are eight different types of Anim Curve nodes:

  \li timeToAngular (animCurveTA)
  \li timeToLinear (animCurveTL)
  \li timeToTime (animCurveTT)
  \li timeToUnitless (animCurveTU)
  \li unitlessToAngular (animCurveUA)
  \li unitlessToLinear (animCurveUL)
  \li unitlessToTime (animCurveUT)
  \li unitlessToUnitless (animCurveUU)

  Specifying the correct AnimCurveType during creation will avoid
  implicit unit conversion nodes.

  Use the Anim Curve Function Set to create Anim Curve Nodes and
  connect them to animatable attributes on DG Nodes, as well as to
  query and edit an Anim Curve Node and its keys.

  On creation, an Anim Curve Function Set may be attached to a given
  Anim Curve or it may be unattached.  The Function Set may be
  attached to a different Anim Curve Node using the setObject()
  methods inherited from the Base Function Set (MFnBase) or with the
  create() methods.

  Use the create() methods of an Anim Curve Function Set to create a
  new Anim Curve Node, attach the Function Set to the new Node and
  connect the output of the Node to a specific animatable Attribute or
  Plug of another Node.  Additionally, the output of an Anim Curve
  Node may be attached to an Attribute or Plug of another DG Node
  using the DG Modifier method MDGModifier::connect().

  Use the evaluate() methods to determine the value of an Anim Curve
  at a particular time or a given unitless input.

  Use the addKey() and remove() methods to add and remove keys to and
  from an Anim Curve.

  The query and edit methods of the Anim Curve Function Set act on
  keys at a specific 0-based index. [Note that the numKeys() method
  returns a 1-based value].  Keys can be accessed either randomly (via
  a 0-based index) or serially (using the find() and findClosest()
  methods).

  Use the find() or findClosest() methods to determine the index of a
  key at or closest to a specific time respectively.

  Use the specific query methods to determine the time, value and
  tangent information for a key at a given index.

  Use the specific edit methods to set the time, value and tangent
  information for a key at a given index.

  There are methods for setting the x,y values for the in- and
  out-tangents, as well as setting their angles and weights.

  Setting the time of a key will fail if the new time would require a
  re-ordering of the keys.  Use the remove() and addKey() methods to
  re-order the keys. Or use the keyframe command from mel.

  The Maya developer's kit ships with example code (animDemo) which
  demonstrates how to evaluate a Maya animation curve independent from
  Maya.  The animation parameter curves in Maya are defined by a
  restricted set of cubic two-dimensional Bezier curves. It is defined
  by four points.  P1 = (x1, y1) is the (key,value) pair for the first
  key.  P2 = (x2, y2) is a point which defines the outgoing tangent
  direction at P1.  P4 = (x4, y4) defines the second key and P3 = (x3,
  y3) is a point which defines the incoming tangent direction at P4.
  There are some basic restrictions for the x coordinates of these
  points: x1 <= x2 <= x3 <= x4.

  The 2-dimensional Bezier curve is defined as

  \code
  F(u) = [ u^3 u^2 u 1 ] * B * | P1 |   ,  0 <= u <= 1
                               | P2 |
                               | P3 |
                               | P4 |

       = [ B0(u) B1(u) B2(u) B3(u) ] * | x1 y1 |
                                       | x2 y2 |
                                       | x3 y3 |
                                       | x4 y4 |

   where B is the Bezier Basis matrix  | -1  3  -3  1 |
                                       |  3 -6   3  0 |
                                       | -3  3   0  0 |
                                       |  1  0   0  0 |
  \endcode

  F(u) yields a vector of two cubic polynomials [ Fx(u) Fy(u) ] which
  define an (x, y) position on the parameter curve for some u in the
  range [0,1].

  For an animation parameter curve, we are given the x position and
  want to know its corresponding y position.  To do this we use x =
  Fx(u) and solve for u.  Fx(u) is cubic and the restrictions on valid
  values for x2 and x3 guarantee there will be only one real root
  value for u. Once we know u, we can plug it into Fy(u) to get the y
  value.

  One important note is how the outgoing and incoming tangents
  directions for a key are saved internally and in the Maya Ascii file
  format.  Instead of being specified as points, the tangent
  directions are specified as vectors. The outgoing tangent direction
  at P1 is specified and saved as the vector 3*(P2 - P1) and the
  incoming tangent direction is specified and saved as the vector
  3*(P4 - P3).

  An animation curve is basically a restricted form of a bezier curve
  for which the keys serve as the control points and have tangent
  information embedded within them. There are two different methods
  for converting tangent information into the control points of the
  bezier hull and we have taken to calling the two methods weighted
  and non-weighted tangents.

  The animation curve is evaluated in a piecewise manner, which means
  that each segment between two keys is evaluated on its own, without
  regards to any other segment. The only time keys outside of a
  segment are considered is when tangent values are calculated for the
  spline, clamped, plateau or auto tangent types.

  When evaluating an animation curve, a two stage process is used:
  <ol>
  <li> the evaluation time is examined to determine if it falls within
  the range of the animation curve, and if it does not evaluation is based
  upon the infinity settings for the animation curve.
  <li>if the evaluation time falls within the range of the animation
  curve, the bezier parameters of the curve are computed and used
  as described below.
  </ol>

  Animation curves may have either weighted or non-weighted tangents.
  With non-weighted tangents, tangents are implemented as vectors and
  P2 and P3 are internally adjusted to account for the time difference
  between P1 and P4.

  When evaluating a time within a segment, the following algortithms
  are used:

  \code
For weighted tangents:
	where x is the start of the segment
	given the bezier x parameters a', b', c', d', find the parameter t
	which satisfies the formula:
		(time - x) = (t^3 * a') + (t^2 + b') + (t * c') + d'
	with t (and the bezier y parameters a, b, c, d) compute the value as:
		v = (t^3 * a) + (t^2 + b) + (t * c) + d

For non-weighted tangents:
	where x is the start of the segment
	compute the parameter t as time - x
	with t (and the bezier y parameters a, b, c, d) compute the value as:
		v = (t^3 * a) + (t^2 + b) + (t * c) + d
  \endcode
*/
class OPENMAYAANIM_EXPORT MFnAnimCurve : public MFnDependencyNode
{
	declareMFn(MFnAnimCurve, MFnDependencyNode);
public:
	MFnAnimCurve (const MPlug &plug, MStatus *ReturnStatus = NULL);

public:

//! Defines the input and output type of the animation curve
/*!
Animation curves in Maya support either time or unitless inputs. For
example, curves set using setKeyframe have time inputs. Curves set
using setDrivenKeyframe have unitless inputs. Maya supports four types
of outputs: angular, linear, time and unitless. Time, angular and
linear outputs work according to the units specified in user
preferences and convert units when the preferences are
changes. Unitless outputs are not sensitive to user preferences.
*/	
    OPENMAYA_ENUM(AnimCurveType,
		kAnimCurveTA,					//!< Time to Angular
		kAnimCurveTL,					//!< Time to Linear
		kAnimCurveTT,					//!< Time to Time
		kAnimCurveTU,					//!< Time to Unitless
		kAnimCurveUA,					//!< Unitless to Angular
		kAnimCurveUL,					//!< Unitless to Linear
		kAnimCurveUT,					//!< Unitless to Time
		kAnimCurveUU,					//!< Unitless to Unitless
		kAnimCurveUnknown				//!< Unknown type
	);

	//! Defines the type of the tangent
    OPENMAYA_ENUM(TangentType,
		kTangentGlobal,		//!< Global
		kTangentFixed,		//!< Fixed
		kTangentLinear,		//!< Linear
		kTangentFlat,		//!< Flag
		kTangentSmooth,		//!< Smooth
		kTangentStep,		//!< Step
		kTangentSlow,		//!< OBSOLETE kTangentSlow should not be used. Using this tangent type may produce unwanted and unexpected results.
		kTangentFast,		//!< OBSOLETE kTangentFast should not be used. Using this tangent type may produce unwanted and unexpected results.
		kTangentClamped,	//!< Clamped
		kTangentPlateau,	//!< Plateau
		kTangentStepNext,	//!< StepNext
		kTangentAuto,		//!< Auto 

		kTangentShared1 = 19,   // Custom tangent types which are available to all users, and should only be used internally.
		kTangentShared2 = 20,
		kTangentShared3 = 21,
		kTangentShared4 = 22,
		kTangentShared5 = 23,
		kTangentShared6 = 24,
		kTangentShared7 = 25,
		kTangentShared8 = 26,

		kTangentAutoMix,		//!< AutoMix
		kTangentAutoEase,	//!< AutoEase
		kTangentAutoCustom,		//!< AutoCustom

		kTangentCustomStart = 64,	// Custom tangent types which can be reserved by customers in blocks of 8 through an ADN request.

		// These should always be last
		//
		kTangentCustomEnd = SHRT_MAX,
		kTangentTypeCount = SHRT_MAX + 1
    );

    //! Defines the value type of the tangent
    typedef double TangentValue;

//! Defines the type of the infinity
/*!

The infinity controls the shape of the animation curve in the
regions before the first key and after the last key.

*/
    OPENMAYA_ENUM(InfinityType,
		kConstant = 0,		//!< Constant
		kLinear = 1,		//!< Linear
		kCycle = 3,			//!< Cycle
		kCycleRelative = 4,	//!< Cycle relative
		kOscillate = 5		//!< Oscillate
	);

	MObject     create( const MObject & node,
						const MObject & attribute,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );
	MObject     create( const MObject & node,
						const MObject & attribute,
						AnimCurveType animCurveType,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );
	MObject     create( const MPlug & plug,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );
	MObject     create( const MPlug & plug,
						AnimCurveType animCurveType,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );
	//	the following create method builds an animCurve with
	//	no connections
	MObject		create( AnimCurveType animCurveType,
						MDGModifier * modifier = NULL,
						MStatus * ReturnStatus = NULL );

	AnimCurveType	animCurveType (MStatus *ReturnStatus = NULL) const;

	AnimCurveType   timedAnimCurveTypeForPlug( MPlug& plug,
											   MStatus *ReturnStatus = NULL) const;

	AnimCurveType   unitlessAnimCurveTypeForPlug( MPlug& plug,
											   MStatus *ReturnStatus = NULL) const;

	double      evaluate( const MTime &atTime,
						  MStatus * ReturnStatus = NULL ) const;
	MStatus		evaluate( const MTime &atTime, double &value ) const;
	MStatus		evaluate( const MTime &atTime, MTime &timeValue ) const;
	MStatus		evaluate( const double &atUnitlessInput, double &value ) const;
	MStatus		evaluate( const double &atUnitlessInput,
						  MTime &timeValue ) const;
	bool		isStatic( MStatus * ReturnStatus = NULL ) const;

	OPENMAYA_DEPRECATED(<2016, "Use MFnAnimCurve::numKeys instead.")
	unsigned int    numKeyframes( MStatus * ReturnStatus = NULL ) const;

	unsigned int	numKeys( MStatus * ReturnStatus = NULL ) const;
	MStatus     remove( unsigned int index, MAnimCurveChange * change = NULL );
	MStatus     addKeyframe( const MTime& time, double value,
							 MAnimCurveChange * change = NULL );
	MStatus     addKeyframe( const MTime& time, double value,
							 TangentType tangentInType,
							 TangentType tangentOutType,
							 MAnimCurveChange * change = NULL );
	// for animCurveTU, animCurveTL and animCurveTA
	unsigned int	addKey( const MTime& time, double value,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MAnimCurveChange * change = NULL,
					 	MStatus * ReturnStatus = NULL );
	// for animCurveTT
	unsigned int	addKey( const MTime& timeInput, const MTime& timeValue,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MAnimCurveChange * change = NULL,
					 	MStatus * ReturnStatus = NULL );
	// for animCurveUU, animCurveUL and animCurveUA
	unsigned int	addKey( double unitlessInput, double value,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MAnimCurveChange * change = NULL,
					 	MStatus * ReturnStatus = NULL );
	// for animCurveUT
	unsigned int	addKey( double unitlessInput, const MTime& time,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MAnimCurveChange * change = NULL,
					 	MStatus * ReturnStatus = NULL );
	// block add keys for TL, TA and TU animCurves
	MStatus		addKeys( MTimeArray * timeArray,
						 MDoubleArray * valueArray,
						 TangentType tangentInType = kTangentGlobal,
						 TangentType tangentOutType = kTangentGlobal,
						 bool keepExistingKeys = false,
							 MAnimCurveChange * change = NULL );
	// block add keys for TL, TA and TU animCurves
	MStatus			addKeysWithTangents( MTimeArray * timeArray,
						MDoubleArray * valueArray,
						TangentType tangentInType = kTangentGlobal,
						TangentType tangentOutType = kTangentGlobal,
						MIntArray * tangentInTypeArray = NULL,
						MIntArray * tangentOutTypeArray = NULL,
						MDoubleArray * tangentInXArray = NULL,
						MDoubleArray * tangentInYArray = NULL,
						MDoubleArray * tangentOutXArray = NULL,
						MDoubleArray * tangentOutYArray = NULL,
						MIntArray * tangentsLockedArray = NULL,
						MIntArray * weightsLockedArray = NULL,
						bool convertUnits = true,
						bool keepExistingKeys = false,
						MAnimCurveChange * change = NULL );

	unsigned int	insertKey( const MTime& time,
							bool breakdown = false,
							MAnimCurveChange* change = nullptr,
							MStatus * ReturnStatus = nullptr );

	bool        find( const MTime& time, unsigned int &index,
					         MStatus * ReturnStatus = NULL ) const;
	bool		find( double unitlessInput, unsigned int & index,
					  MStatus * ReturnStatus = NULL ) const;
	unsigned int    findClosest( const MTime& time, MStatus * ReturnStatus = NULL ) const;
	unsigned int	findClosest( double unitlessInput,
							 MStatus * ReturnStatus = NULL ) const;
	MTime       time( unsigned int index, MStatus * ReturnStatus = NULL ) const;
	double      value( unsigned int index, MStatus * ReturnStatus = NULL ) const;
	double		unitlessInput( unsigned int index,
							   MStatus * ReturnStatus = NULL ) const;
	MStatus     setValue( unsigned int index, double value,
					   	  MAnimCurveChange * change = NULL );
	MStatus     setTime( unsigned int index, const MTime& time,
						 MAnimCurveChange * change = NULL );
    MStatus		setUnitlessInput( unsigned int index, double unitlessInput,
								  MAnimCurveChange * change = NULL );
	bool		isTimeInput( MStatus * ReturnStatus = NULL ) const;
	bool		isUnitlessInput( MStatus * ReturnStatus = NULL ) const;
	TangentType inTangentType( unsigned int index,
							   MStatus * ReturnStatus = NULL ) const;
	TangentType outTangentType( unsigned int index,
								MStatus * ReturnStatus = NULL ) const;
	MStatus     setInTangentType( unsigned int index, TangentType tangentType,
								  MAnimCurveChange * change = NULL );
	MStatus     setOutTangentType( unsigned int index, TangentType tangentType,
								   MAnimCurveChange * change = NULL );
	MStatus     setTangentTypes(MIntArray indexArray,
				    TangentType tangentInType  = kTangentGlobal,
				    TangentType tangentOutType = kTangentGlobal,
				    MAnimCurveChange * change = NULL );
	MStatus     getTangent( unsigned int index, TangentValue &x, TangentValue &y,
							bool inTangent) const;
	MStatus     getTangent( unsigned int index, MAngle &angle, double &weight,
							bool inTangent ) const;
    MStatus		setTangent( unsigned int index, TangentValue x, TangentValue y, bool inTangent,
						   	MAnimCurveChange * change = NULL,
							bool convertUnits=true );
    MStatus		setTangent( unsigned int index, const MAngle& angle, double weight,
							bool inTangent, MAnimCurveChange * change = NULL,
							bool convertUnits=true );
	MStatus		setAngle( unsigned int index, const MAngle& angle, bool inTangent,
						  MAnimCurveChange * change = NULL );
	MStatus		setWeight( unsigned int index, double weight, bool inTangent,
						   MAnimCurveChange * change = NULL );
	bool		weightsLocked( unsigned int index,
							   MStatus * ReturnStatus = NULL ) const;
	bool		tangentsLocked( unsigned int index,
								MStatus * ReturnStatus = NULL ) const;
	MStatus		setWeightsLocked( unsigned int index, bool locked,
								  MAnimCurveChange * change = NULL );
	MStatus		setTangentsLocked( unsigned int index, bool locked,
								   MAnimCurveChange * change = NULL );
	InfinityType	preInfinityType( MStatus * ReturnStatus = NULL ) const;
	InfinityType	postInfinityType( MStatus * ReturnStatus = NULL ) const;
	MStatus		setPreInfinityType( InfinityType infinityType,
									MAnimCurveChange * change = NULL );
	MStatus		setPostInfinityType( InfinityType infinityType,
									 MAnimCurveChange * change = NULL );
	bool		isWeighted (MStatus *ReturnStatus = NULL) const;
	MStatus		setIsWeighted (bool isWeighted,
							   MAnimCurveChange *change = NULL);
	bool		isBreakdown( unsigned int index,
							 MStatus * ReturnStatus = NULL ) const;
	MStatus		setIsBreakdown( unsigned int index,
								bool isBreakdown,
								MAnimCurveChange *change = NULL);
BEGIN_NO_SCRIPT_SUPPORT:

 	declareMFnConstConstructor( MFnAnimCurve, MFnDependencyNode );

END_NO_SCRIPT_SUPPORT:

protected:
// No protected members

private:
// No private members
};

OPENMAYA_NAMESPACE_CLOSE

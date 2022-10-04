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
// CLASS:    MPoint
//
// ****************************************************************************

#include <maya/MTypes.h>
#include <maya/MStatus.h>

#define MPoint_kTol	1.0e-10

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MPoint)

//! \ingroup OpenMaya
//! \brief Implementation of a point.
/*!
This class provides an implementation of a point.  Numerous convienence
operators are provided to help with the manipulation of points.  This
includes operators that work with the MVector and MMatrix classes.

All methods that query the point are threadsafe, all methods that
modify the point are not threadsafe.

*/
class OPENMAYA_EXPORT MPoint
{
public:
					MPoint();	// defaults to 0,0,0,1
					MPoint( const MPoint & srcpt );
					MPoint( const MFloatPoint & srcpt );
					MPoint( const MVector & src );
					MPoint( const MFloatVector & src );
					MPoint( double xx, double yy,
							double zz = 0.0, double ww = 1.0 );
					MPoint( const double d[4] );
					MPoint( const float d[4] );
					~MPoint();
	MStatus			get( double[4] ) const;
	MStatus			get( float[4] ) const;
	double  		operator[](unsigned int i) const;
	double  		operator()(unsigned int i) const;
	MPoint & 		operator=( const MPoint & src );
	MVector   		operator-( const MPoint & other ) const;
	MPoint   		operator+( const MVector & other ) const;
	MPoint   		operator-( const MVector & other ) const;
	MPoint & 		operator+=( const MVector & vector );
	MPoint & 		operator-=( const MVector & vector );
	MPoint			operator*(const int scale) const;
	MPoint			operator*(const short scale) const;
	MPoint			operator*(const unsigned int scale) const;
	MPoint			operator*(const unsigned short scale) const;
	MPoint			operator*(const float scale) const;
	MPoint			operator*(const double scale) const;
	MPoint			operator/(const double scale) const;
	MPoint   		operator*(const MMatrix &) const;
	MPoint & 		operator*=(const MMatrix &);
	MPoint & 		operator*=(const int);
	MPoint & 		operator*=(const short);
	MPoint & 		operator*=(const unsigned int);
	MPoint & 		operator*=(const unsigned short);
	MPoint & 		operator*=(const float);
	MPoint & 		operator*=(const double);
	bool           	operator==( const MPoint & other ) const;
	bool           	operator!=( const MPoint & other ) const;
	MPoint & 		cartesianize();
	MPoint & 		rationalize();
	MPoint & 		homogenize();
	double     		distanceTo( const MPoint & other ) const;
	bool           	isEquivalent( const MPoint & other,
								  double tolerance = MPoint_kTol) const;

BEGIN_NO_SCRIPT_SUPPORT:

	//!	NO SCRIPT SUPPORT
	double &        operator[](unsigned int i);

	//!	NO SCRIPT SUPPORT
	double &        operator()(unsigned int i);

	//!	NO SCRIPT SUPPORT
 	friend OPENMAYA_EXPORT MPoint operator*(int, const MPoint &);

	//!	NO SCRIPT SUPPORT
 	friend OPENMAYA_EXPORT MPoint operator*(short, const MPoint &);

	//!	NO SCRIPT SUPPORT
 	friend OPENMAYA_EXPORT MPoint operator*(unsigned int, const MPoint &);

	//!	NO SCRIPT SUPPORT
 	friend OPENMAYA_EXPORT MPoint operator*(unsigned short, const MPoint &);

	//!	NO SCRIPT SUPPORT
 	friend OPENMAYA_EXPORT MPoint operator*(float, const MPoint &);

	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT MPoint operator*(double, const MPoint &);

	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT MPoint operator*(const MMatrix &, const MPoint &);

	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT std::ostream& operator<<(std::ostream& os, const MPoint& p);

END_NO_SCRIPT_SUPPORT:

	static const MPoint origin;
public:
	//! the x component of the point
	double			x;
	//! the y component of the point
	double			y;
	//! the z component of the point
	double			z;
	//! the w component of the point
	double			w;

	static const char* className();

protected:
// No protected members
};

OPENMAYA_NAMESPACE_CLOSE

//	These need to be included *after* the MPoint class definition,
//	otherwise we end up with a chicken-and-egg situation due to mutual
//	header inclusions.
//
#ifndef _MFloatPoint
#include <maya/MFloatPoint.h>
#endif
#ifndef _MFloatVector
#include <maya/MFloatVector.h>
#endif
#ifndef _MVector
#include <maya/MVector.h>
#endif

OPENMAYA_MAJOR_NAMESPACE_OPEN

/*!
	Default constructor. The instance is initialized to the origin.
*/
inline MPoint::MPoint()
 	: x(0.0)
	, y(0.0)
	, z(0.0)
	, w(1.0)
{
}

/*!
	Copy constructor.  Creates an new instance and initializes it to
	the same point as the given point.

	\param[in] srcpt The point object to copy from.
*/
inline MPoint::MPoint(const MPoint& srcpt)
 	: x(srcpt.x)
	, y(srcpt.y)
	, z(srcpt.z)
	, w(srcpt.w)
{
}

/*!
	Creates an new instance and initializes it to
	the x, y, z, w values of the given MFloatPoint.

	\param[in] srcpt the point object to copy
*/
inline MPoint::MPoint(const MFloatPoint& srcpt)
 	: x(srcpt.x)
	, y(srcpt.y)
	, z(srcpt.z)
	, w(srcpt.w)
{
}

/*!
	Create a new instance and initialize it to the given position.

	\param[in] d array of 4 doubles used to initialize x, y, z, and
	w respectively.
*/
inline MPoint::MPoint(const double d[4] )
 	: x(d[0])
	, y(d[1])
	, z(d[2])
	, w(d[3])
{
}

/*!
	Create a new instance and initialize it to the given position.

	\param[in] f An array of 4 floats used to initialize x, y, z, and
	w respectively.
*/
inline MPoint::MPoint(const float f[4] )
 	: x(f[0])
	, y(f[1])
	, z(f[2])
	, w(f[3])
{
}

/*!
	Create a new instance and initialize it to the given position.

	\param[in] xx The initial value of x.
	\param[in] yy The initial value of y.
	\param[in] zz The initial value of z.
	\param[in] ww The initial value of w.
*/
inline MPoint::MPoint(double xx, double yy, double zz, double ww)
 	: x(xx)
	, y(yy)
	, z(zz)
	, w(ww)
{
}

/*!
	Creates an new instance and initializes it to
	the x, y, z values of the given MVector.  The w value is set to 1.0.

	\param[in] src the vector object to copy
*/
inline MPoint::MPoint(const MVector& src)
 	: x(src.x)
	, y(src.y)
	, z(src.z)
	, w(1.0)
{
}

/*!
	Creates an new instance and initializes it to
	the x, y, z values of the given MFloatVector.  The w value is set to 1.0.

	\param[in] src the vector object to copy
*/
inline MPoint::MPoint(const MFloatVector& src)
 	: x(src.x)
	, y(src.y)
	, z(src.z)
	, w(1.0)
{
}

/*!
	Class destructor.
*/
inline MPoint::~MPoint()
{
}

/*!
	The assignment operator.

	\param[in] src Point to copy from.

	\return
	A reference to the assigned point.
*/
inline MPoint& MPoint::operator=(const MPoint& src)
{
	x = src.x;
	y = src.y;
	z = src.z;
	w = src.w;
	return *this;
}

/*!
	The index operator.
	If the argument is 0 it will return the x component of the instance.
	If the argument is 1 it will return the y component of the instance.
	If the argument is 2 it will return the z component of the instance.
	If the argument is 3 it will return the w component of the instance.
	Otherwise it will return the x component of the instance.

	\param[in] i Value indicating which component to return.

	\return
    The value of the indicated component of the instance.
*/
inline double& MPoint::operator() (unsigned int i)
{
	switch( i )
	{
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
	return x;
}

/*!
	The index operator.
	\li If the argument is 0 it will return the x component of the constant
	instance.
	\li If the argument is 1 it will return the y component of the constant
	instance.
	\li If the argument is 2 it will return the z component of the constant
	instance.
	\li If the argument is 3 it will return the w component of the constant
	instance.
	\li Otherwise it will return the x component of the point.

	\param[in] i Value indicating which component to return.

	\return
	The value of the indicated component of the instance.
*/
inline double MPoint::operator() (unsigned int i) const
{
	switch( i )
	{
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
}

/*!
	The index operator.
	\li If the argument is 0 it will return the x component of the instance.
	\li If the argument is 1 it will return the y component of the instance.
	\li If the argument is 2 it will return the z component of the instance.
	\li If the argument is 3 it will return the w component of the instance.
	\li Otherwise it will return the x component of the instance.

	\param[in] i Value indicating which component to return.

	\return
	The value of the indicated component of the instance.
*/
inline double& MPoint::operator[]( unsigned int i )
{
	switch( i )
	{
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
}

/*!
	The index operator.
	\li If the argument is 0 it will return the x component of the constant
	instance.
	\li If the argument is 1 it will return the y component of the constant
	instance.
	\li If the argument is 2 it will return the z component of the constant
	instance.
	\li If the argument is 3 it will return the w component of the constant
	instance.
	\li Otherwise it will return the x component of the point.

	\param[in] i Value indicating which component to return.

	\return
    The value of the indicated component of the instance.
*/
inline double MPoint::operator[]( unsigned int i ) const
{
	switch( i )
	{
		default:
		case 0: return x;
		case 1: return y;
		case 2: return z;
		case 3: return w;
	}
}

/*!
	Copy the values of x, y, z, and w from the instance to the four
	elements of the given array of floats.

	\warning This method converts double precision floating point values to
	         single precision. This will result in a loss of precision and,
			 if the double precision value exceeds the valid range for single
			 precision, the result will be undefined and unusable.

	\param[out] dest The four element array of floats.

	\return
	MS::kSuccess if dest is a non-zero pointer and MS::kFailure otherwise.
*/
inline MStatus MPoint::get( float dest[4] ) const
{
	if( dest != NULL )
	{
		dest[0] = static_cast<float>(x);
		dest[1] = static_cast<float>(y);
		dest[2] = static_cast<float>(z);
		dest[3] = static_cast<float>(w);
		return MStatus::kSuccess;
	}
	return MStatus::kFailure;
}

/*!
	Copy the values of x, y, z, and w from the instance to the four
	elements of the given array of doubles.

	\param[out] dest The four element array of doubles.

	\return
	MS::kSuccess if dest is a non-zero pointer and MS::kFailure otherwise.
*/
inline MStatus MPoint::get( double dest[4] ) const
{
	if( dest != NULL )
	{
		dest[0] = x;
		dest[1] = y;
		dest[2] = z;
		dest[3] = w;
		return MStatus::kSuccess;
	}
	return MStatus::kFailure;
}

/*!
	The in-place addition operator for adding an MVector to an MPoint.
	The current instance is translated from its original position
	by the vector.

	\param[in] vector Vector to add.

	\return
	A reference to the resulting point.
*/
inline MPoint& MPoint::operator+= (const MVector& vector )
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

/*!
	The in-place subtraction operator for subtracting an MVector from
	an MPoint. The current instance is translated from its original
	position by the inverse of the vector.

	\param[in] vector Vector to substract.

	\return
	A reference to the resulting point.
*/
inline MPoint& MPoint::operator-= (const MVector& vector )
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

/*!
	The addition operator for adding an MVector to an MPoint.
	A new point is returned whose position is that of the original
	point translated by the vector.

	\param[in] other Vector to add.

	\return
	The resulting point.
*/
inline MPoint MPoint::operator+ (const MVector& other) const
{
	if(w==1.0) {
		return MPoint(x+other.x, y+other.y, z+other.z);
	} else {
		MPoint p1(*this); p1.cartesianize();
		return MPoint(p1.x+other.x, p1.y+other.y, p1.z+other.z);
	}
}

/*!
	The addition operator for subtracting an MVector from an MPoint.
	A new point is returned whose position is that of the original
	point translated by the inverse of the vector.

	\param[in] other Vector to substract.

	\return
	The resulting point.
*/
inline MPoint MPoint::operator- (const MVector& other) const
{
	if(w==1.0) {
		return MPoint(x-other.x, y-other.y, z-other.z);
	} else {
		MPoint p1(*this); p1.cartesianize();
		return MPoint(p1.x-other.x, p1.y-other.y, p1.z-other.z);
	}
}

/*!
	The subtraction operator for two MPoints.  The result is the
	MVector from the other point to this instance.

	\param[in] other The other point.

	\return
	MVector from the other point to this point
*/
inline MVector MPoint::operator- (const MPoint& other) const
{
	if(w==1.0 && other.w==1.0) {
		return MVector(x-other.x, y-other.y, z-other.z);
	} else {
		MPoint p1(*this); p1.cartesianize();
		MPoint p2(other); p2.cartesianize();
		return MVector(p1.x-p2.x, p1.y-p2.y, p1.z-p2.z);
	}
}

/*!
	The multipication operator that allows the vector to by scaled
	by the given parameter.  The x, y, and z components are
	each multiplied by the parameter.
	The w component remains unchanged.

	\param[in] scale The scale parameter.

	\return
	The resulting point.
*/
inline MPoint MPoint::operator* (const int scale) const
{
	return MPoint( x*scale, y*scale, z*scale, w );
}

/*!
	The multipication operator that allows the vector to by scaled
	by the given parameter.  The x, y, and z components are
	each multiplied by the parameter.
	The w component remains unchanged.

	\param[in] scale The scale parameter.

	\return
	The resulting point.
*/
inline MPoint MPoint::operator* (const short scale) const
{
	return MPoint( x*scale, y*scale, z*scale, w );
}

/*!
	The multipication operator that allows the vector to by scaled
	by the given parameter.  The x, y, and z components are
	each multiplied by the parameter.
	The w component remains unchanged.

	\param[in] scale The scale parameter.

	\return
	The resulting point.
*/
inline MPoint MPoint::operator* (const unsigned int scale) const
{
	return MPoint( x*scale, y*scale, z*scale, w );
}

/*!
	The multipication operator that allows the vector to by scaled
	by the given parameter.  The x, y, and z components are
	each multiplied by the parameter.
	The w component remains unchanged.

	\param[in] scale The scale parameter.

	\return
	The resulting point.
*/
inline MPoint MPoint::operator* (const unsigned short scale) const
{
	return MPoint( x*scale, y*scale, z*scale, w );
}

/*!
	The multipication operator that allows the vector to by scaled
	by the given parameter.  The x, y, and z components are
	each multiplied by the parameter.
	The w component remains unchanged.

	\param[in] scale The scale parameter.

	\return
	The resulting point.
*/
inline MPoint MPoint::operator* (const float scale) const
{
	return MPoint( x*scale, y*scale, z*scale, w );
}

/*!
	The multipication operator that allows the vector to by scaled
	by the given parameter.  The x, y, and z components are
	each multiplied by the parameter.
	The w component remains unchanged.

	\param[in] scale The scale parameter.

	\return
	The resulting point.
*/
inline MPoint MPoint::operator* (const double scale) const
{
	return MPoint( x*scale, y*scale, z*scale, w );
}

/*!
	The division operator that allows the vector to by scaled
	by the given double parameter.  The x, y, and z components are
	each divided by the parameter.
	The w component remains unchanged.

	\param[in] scale The scale parameter.

	\return
    The resulting point.
*/
inline MPoint MPoint::operator/ (const double scale) const
{
	return MPoint( x/scale, y/scale, z/scale, w );
}

/*!
	The equality operator. 

	\param[in] other Point to compare with.

	\return
	True if all of the x, y, z and w components of the two
	points are identical.
*/
inline bool MPoint::operator== (const MPoint& other) const
{
	return (x == other.x && y == other.y && z == other.z && w == other.w);
}

/*!
	The inequality operator.  

	\param[in] other Point to compare with.

	\return
	True if any of the x, y, z and w components of the two points are
	not identical.
*/
inline bool MPoint::operator!= (const MPoint& other) const
{
	return !(*this == other);
}

/*!
	Returns true if this instance of the point passed as an argument
	represent the same position within the specified tolerance.

	\param[in] other The other point to compare to.
	\param[in] tol   The tolerance to use during the comparison.

	\return
	True if the points are equal within the given tolerance and false
	otherwise.
*/
inline bool MPoint::isEquivalent(const MPoint& other, double tol) const
{
	MPoint diff = *this - other;
	return (diff.x*diff.x + diff.y*diff.y + diff.z*diff.z) < tol*tol;
}

/*!
	Return the distance between this instance and the point passed as an
	argument.

	\param[in] other The point to compute the distance to.

	\return
	The distance between the two points.
*/
inline double MPoint::distanceTo(const MPoint& other) const
{
	MVector diff = *this - other;
	return diff.length();
}

#if ! defined(SWIG)

/*!
	The multiplication operator that allows the scalar value to
	precede the point.  The point's x, y, and z components are
	each multiplied by the scalar.
	The w component remains unchanged.

	\param[in] scale The scale parameter.
	\param[in] p The point to be scaled.

	\return
	A new point containing the value of 'p' scaled by 'scale'.
*/
inline MPoint operator* (int scale, const MPoint& p)
{
	return MPoint( p.x*scale, p.y*scale, p.z*scale, p.w );
}

/*!
	The multiplication operator that allows the scalar value to
	precede the point.  The point's x, y, and z components are
	each multiplied by the scalar.
	The w component remains unchanged.

	\param[in] scale The scale parameter.
	\param[in] p The point to be scaled.

	\return
	A new point containing the value of 'p' scaled by 'scale'.
*/
inline MPoint operator* (short scale, const MPoint& p)
{
	return MPoint( p.x*scale, p.y*scale, p.z*scale, p.w );
}

/*!
	The multiplication operator that allows the scalar value to
	precede the point.  The point's x, y, and z components are
	each multiplied by the scalar.
	The w component remains unchanged.

	\param[in] scale The scale parameter.
	\param[in] p The point to be scaled.

	\return
	A new point containing the value of 'p' scaled by 'scale'.
*/
inline MPoint operator* (unsigned int scale, const MPoint& p)
{
	return MPoint( p.x*scale, p.y*scale, p.z*scale, p.w );
}

/*!
	The multiplication operator that allows the scalar value to
	precede the point.  The point's x, y, and z components are
	each multiplied by the scalar.
	The w component remains unchanged.

	\param[in] scale The scale parameter.
	\param[in] p The point to be scaled.

	\return
	A new point containing the value of 'p' scaled by 'scale'.
*/
inline MPoint operator* (unsigned short scale, const MPoint& p)
{
	return MPoint( p.x*scale, p.y*scale, p.z*scale, p.w );
}

/*!
	The multiplication operator that allows the scalar value to
	precede the point.  The point's x, y, and z components are
	each multiplied by the scalar.
	The w component remains unchanged.

	\param[in] scale The scale parameter.
	\param[in] p The point to be scaled.

	\return
	A new point containing the value of 'p' scaled by 'scale'.
*/
inline MPoint operator* (float scale, const MPoint& p)
{
	return MPoint( p.x*scale, p.y*scale, p.z*scale, p.w );
}

/*!
	The multiplication operator that allows the scalar value to
	precede the point.  The point's x, y, and z components are
	each multiplied by the scalar.
	The w component remains unchanged.

	\param[in] scale The scale parameter.
	\param[in] p The point to be scaled.

	\return
	A new point containing the value of 'p' scaled by 'scale'.
*/
inline MPoint operator* (double scale, const MPoint& p)
{
	return MPoint( p.x*scale, p.y*scale, p.z*scale, p.w );
}

/*!
	The in-place multiplication operator for computing the scalar product
	of this point instance with the given scalar.

	\param[in] factor Scalar to multiply this point by.

	\return
	This point.
*/
inline MPoint& MPoint::operator*= (const int factor)
{
	x *= factor; y *= factor; z *= factor;
	return *this;
}

/*!
	The in-place multiplication operator for computing the scalar product
	of this point instance with the given scalar.

	\param[in] factor Scalar to multiply this point by.

	\return
	This point.
*/
inline MPoint& MPoint::operator*= (const short factor)
{
	x *= factor; y *= factor; z *= factor;
	return *this;
}

/*!
	The in-place multiplication operator for computing the scalar product
	of this point instance with the given scalar.

	\param[in] factor Scalar to multiply this point by.

	\return
	This point.
*/
inline MPoint& MPoint::operator*= (const unsigned int factor)
{
	x *= factor; y *= factor; z *= factor;
	return *this;
}

/*!
	The in-place multiplication operator for computing the scalar product
	of this point instance with the given scalar.

	\param[in] factor Scalar to multiply this point by.

	\return
	This point.
*/
inline MPoint& MPoint::operator*= (const unsigned short factor)
{
	x *= factor; y *= factor; z *= factor;
	return *this;
}

/*!
	The in-place multiplication operator for computing the scalar product
	of this point instance with the given scalar.

	\param[in] factor Scalar to multiply this point by.

	\return
	This point.
*/
inline MPoint& MPoint::operator*= (const float factor)
{
	x *= factor; y *= factor; z *= factor;
	return *this;
}

/*!
	The in-place multiplication operator for computing the scalar product
	of this point instance with the given scalar.

	\param[in] factor Scalar to multiply this point by.

	\return
	This point.
*/
inline MPoint& MPoint::operator*= (const double factor)
{
	x *= factor; y *= factor; z *= factor;
	return *this;
}

#endif /* ! defined(SWIG) */

OPENMAYA_NAMESPACE_CLOSE

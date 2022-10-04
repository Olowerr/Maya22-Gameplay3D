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
// CLASS:    MFloatVectorArray
//
// ****************************************************************************

#include <maya/MTypes.h>
#include <maya/MStatus.h>
#include <maya/MFloatVector.h>
#include <maya/MArrayIteratorTemplate.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MFloatVectorArray)

//! \ingroup OpenMaya MFn
//! \brief Array of MFloatVectors data type.
/*!
This class implements an array of MFloatVectors.  Common convenience functions
are available, and the implementation is compatible with the internal
Maya implementation so that it can be passed efficiently between plugins
and internal maya data structures.
*/
class OPENMAYA_EXPORT MFloatVectorArray
{
public:
	typedef MArrayIteratorTemplate<MFloatVectorArray, MFloatVector> Iterator;
	typedef MArrayConstIteratorTemplate<MFloatVectorArray, MFloatVector> ConstIterator;

	MFloatVectorArray();
	MFloatVectorArray( const MFloatVectorArray& other );

BEGIN_NO_SCRIPT_SUPPORT:
	//!	NO SCRIPT SUPPORT
	MFloatVectorArray( const MFloatVector vectors[], unsigned int count );
END_NO_SCRIPT_SUPPORT:

	MFloatVectorArray( const double vectors[][3], unsigned int count );
	MFloatVectorArray( const float vectors[][3], unsigned int count );
	MFloatVectorArray( unsigned int initialSize,
					   const MFloatVector &initialValue
					   = MFloatVector::zero );
	~MFloatVectorArray();

 	const MFloatVector&	operator[]( unsigned int index ) const;
 	MFloatVectorArray &  operator=( const MFloatVectorArray & other );
	MStatus			set( const MFloatVector& element, unsigned int index );
	MStatus			set( double element[3], unsigned int index );
	MStatus			set( float element[3], unsigned int index );
	MStatus			setLength( unsigned int length );
	unsigned int		length() const;
	MStatus			remove( unsigned int index );
	MStatus			insert( const MFloatVector & element, unsigned int index );
	MStatus			append( const MFloatVector & element );
 	MStatus         copy( const MFloatVectorArray& source );
	MStatus			clear();
	MStatus			get( double [][3] ) const;
	MStatus			get( float [][3] ) const;
	void			setSizeIncrement ( unsigned int newIncrement );
	unsigned int		sizeIncrement () const;

BEGIN_NO_SCRIPT_SUPPORT:

	//!	NO SCRIPT SUPPORT
 	MFloatVector &		operator[]( unsigned int index );

	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT std::ostream &operator<<(std::ostream &os,
											   const MFloatVectorArray &array);
#if !defined(SWIG)
	Iterator begin();
	Iterator end();

	ConstIterator begin() const;
	ConstIterator end() const;

	ConstIterator cbegin() const;
	ConstIterator cend() const;
#endif

END_NO_SCRIPT_SUPPORT:

	static const char* className();

protected:
// No protected members

OPENMAYA_PRIVATE:
	MFloatVectorArray( void* );
	void * arr;
	struct api_data
	{
		float  x;
		float  y;
		float  z;
	};
	const api_data* debugPeekValue ;
	bool   own;
	void syncDebugPeekValue();
};

OPENMAYA_NAMESPACE_CLOSE

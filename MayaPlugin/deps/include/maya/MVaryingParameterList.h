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
// CLASS:    MVaryingParameterList
//
// ****************************************************************************

#include <maya/MTypes.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MVaryingParameterList)

//! \ingroup OpenMayaRender
//! \brief Geometric data cache.
/*!

  MVaryingParameterList specify the surface component level data
  used by a hardware shader, allowing Maya to handle setting up the
  node and user interfaces to the data, the population and access of
  cached data, etc.
*/
class OPENMAYARENDER_EXPORT MVaryingParameterList
{
public:

	MVaryingParameterList();

	~MVaryingParameterList();
  
    MVaryingParameterList(const MVaryingParameterList &src);

	void			append( const MVaryingParameter& element);

	int				length() const;

	void			setLength( int n);

	MVaryingParameter getElement( int n) const;

	void			setElement( int n, const MVaryingParameter& p);

	const MVaryingParameterList& operator=( const MVaryingParameterList& other);

OPENMAYA_PRIVATE:
	MVaryingParameterList( void* ptr, bool ownsData);

	void*			_ptr;
	bool			_ownsData;
};

OPENMAYA_NAMESPACE_CLOSE

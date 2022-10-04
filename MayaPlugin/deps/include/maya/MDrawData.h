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
// CLASS:    MDrawData
//
// ****************************************************************************
//

#include <maya/MTypes.h>

// ****************************************************************************
// DECLARATIONS

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MDrawData)

//! \ingroup OpenMayaUI
/*!
The MDrawData class holds geometry specific information for user
defined shapes which maya does not intrinsicly know about.

This class is used in the draw methods of MPxSurfaceShapeUI
For each draw request you must create and add a draw data object
which will contain geometry specific information that you will need
in the subsequent call to MPxSurfaceShapeUI::draw.

MDrawData contains one void* member which is a pointer to an
object that you define. This object is the geometry needed to draw
your shape.

To create draw data use the function MPxSurfaceShapeUI::getDrawData.
This function takes two arguments, the first is a pointer to your
geometry object, the second is the draw data being created.
To add the data to a request use MDrawRequest::setDrawData.

Draw data is also used to carry texture information to your draw method.
For materials with texture you must call MMaterial::evaluateTexture
from your MPxSurfaceShapeUI::getDrawRequests method.
Then in your draw method use MMaterial::applyTexture to set up the
viewport to draw using the textured material.
*/
class OPENMAYAUI_EXPORT OPENMAYA_DEPRECATED(<2016, "Use MHWRender::MRenderItem and MHWRender::MPxGeometryOverride instead for Viewport 2.0 support.") MDrawData
{
public:
	MDrawData();
	MDrawData( const MDrawData& in );
	~MDrawData();

public:
	void *		geometry();

	static const char*	className();

protected:
	MDrawData& operator=(const MDrawData& other);

OPENMAYA_PRIVATE:
    MDrawData( void* in );
	void*	 fDrawData;
};
OPENMAYA_NAMESPACE_CLOSE

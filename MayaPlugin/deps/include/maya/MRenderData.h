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
// CLASS:    MRenderData
//
// ****************************************************************************

#include <maya/MFloatVector.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatMatrix.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

//! \ingroup OpenMayaRender
//! \brief Access Rendering Data
/*!
The rendered image and depth map can be changed following the software
render by instanciating a MRenderCallback and overriding renderCallback()
or postProcessCallback(). When these methods are invoked, a MRenderData is
passed as an argument; the rgbaArr and depthArr can then be changed by this
API. Methods and data are provided to assist in transforming back and forth
from world space to image space. Paint Effects and Fur are two examples
which use this mechanism to change the rendered image.
*/
class OPENMAYARENDER_EXPORT MRenderData {
public:
						MRenderData();

    void                worldToScreen(
                            const MFloatPoint&  worldPoint,
                            MFloatPoint&        screenPoint) const;

    void                screenToWorld(
                            const MFloatPoint& screenPoint,
                            MFloatPoint&        worldPoint) const;

    // in data
    //! set if the camera has a perspective projection
    bool                perspective;
    //! the x resolution of the rendered image
    unsigned short      resX;
    //! the y resolution of the rendered image
    unsigned short      resY;

    //! the left (low) render region dimension
    unsigned short      left;
    //! the bottom (low) render region dimension
    unsigned short      bottom;
    //! the right (high) render region dimension
    unsigned short      right;
    //! the top (high) render region dimension
    unsigned short      top;

    //! number of bytes per channel of the rgbaArr
    unsigned short      bytesPerChannel;
    //! the actual x resolution of rgbaArr and depthArr
    unsigned short      xsize;
    //! the actual y resolution of rgbaArr and depthArr
    unsigned short      ysize;

    //! camera horizontal field of view in radians
    float               fieldOfView;
    //! camera pixel aspect ratio
    float               aspectRatio;

    //! view direction of the camera (object space)
    MFloatVector        viewDirection;
    //! position of the camera (object space)
    MFloatPoint         eyePoint;
    //! camera matrix to transform to eye space
    MFloatMatrix        worldToEyeMatrix;

    //! this is a 1d array representing the output image buffer.
	//! It is of size: resX * resY * 4 * bytesPerChannel.  The
	//! array is indexed as [(resX * x + y) * 4 * bytesPerChannel],
	//! where (x,y) is the current pixel coordinates.  The "4"
	//! multiplier is used for storing RGBA information, in the
	//! order of a,b,g,r (on OSX) or b,g,r,a (on Windows and Linux).
    unsigned char       *rgbaArr;
    //! this is a 1d array representing the output depth buffer.
	//! It is of size: resX * resY, where each depth value is a
	//! single precision floating point vlue.  It is indexed as
	//! [resX * x + y], where (x,y) is the current pixel coordinates.
    float               *depthArr;

    // private
    const void*         internalData;

protected:
// No protected members

private:
// No private members
};
OPENMAYA_NAMESPACE_CLOSE

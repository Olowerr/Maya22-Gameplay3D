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
// CLASS:    MPxImagePlane
//
// ****************************************************************************

#include <maya/MPxNode.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// DECLARATIONS


// ****************************************************************************
// CLASS DECLARATION (MPxImagePlane)

//! \ingroup OpenMaya MPx
//! \brief Base class for user defined imagePlane nodes. 
/*!
   MPxImagePlane provides you with the ability to write your own image
   plane classes. This allows you to support non-standard image data
   in an image plane or change the standard behaviour of the image
   plane.

   Note, once you have created a custom image plane and created the
   node in a scene. You must attach the image plane to a camera using
   the 'imagePlane' attribute on the
   'cameraShape'.
*/
class OPENMAYA_EXPORT MPxImagePlane : public MPxNode
{
public:
			MPxImagePlane();
		~MPxImagePlane() override;

	MPxNode::Type type() const override;

	virtual MStatus loadImageMap( const MString &fileName, int frame, MImage &image );

BEGIN_NO_SCRIPT_SUPPORT:

	bool getExactImageFile( const MString &refFileName, MString &actualName );

END_NO_SCRIPT_SUPPORT:

	MString exactImageFile( const MString &refFileName );

	void refreshImage( );

	void setImageDirty();

	//
    // Inherited attributes
	//

	//! controls the source of the image on the Image plane.
	static MObject imageType;

	//! The file name of the image to be used
	//! in the image plane. Only used if Type is set to Image File.
	static MObject imageName;

	//!	When this is on, the system will substitute the frame number
	//! in the Image Name with the number from the Frame Extension attribute (see below).
	static MObject useFrameExtension;

	//! The frame extension in Image Name is replaced by the number here.
	static MObject frameExtension;

	static MObject frameOffset;

	//! Controls the amount of the image that will be used in the image plane.
	static MObject coverage;

	//! The width in pixels of the area on the source image to be used.
	static MObject coverageX;

	//! The height in pixels of the area on the source image to be used.
	static MObject coverageY;

	//! Controls the lower-left-corner of the area of the input image
	//! that will be used on the image plane.
	static MObject coverageOrigin;

	//! The pixel position of the left edge of the area of the source image to be used.
	static MObject coverageOriginX;

	//! The pixel position of the bottom edge of the area of the source image to be used.
	static MObject coverageOriginY;

	//! If the Type attribute is set to Texture, then this attribute is connected to
	//! the texture node used by the image plane.
	static MObject sourceTexture;

	//! Controls how the image file will be fit into the image plane.
	static MObject fit;

	//! Controls how the image plane will be displayed both in the 3d view,
	//! and when rendered.
	static MObject displayMode;

	//! If enabled, you will only see the image plane when you are looking
	//! through the camera that the plane is attached to.
	static MObject displayOnlyIfCurrent;

	//! A multiplier applied to the colors in the image plane.
	static MObject colorGain;

	//! The red component of Color Gain
	static MObject colorGainR;

	//! The green component of Color Gain
	static MObject colorGainG;

	//! The blue component of Color Gain
	static MObject colorGainB;

	//! An additive value applied to the colors in the image plane.
	static MObject colorOffset;

	//! The red component of Color Offset
	static MObject colorOffsetR;

	//! The green component of Color Offset
	static MObject colorOffsetG;

	//! The blue component of Color Offset
	static MObject colorOffsetB;

	//! A multiplier that is applied to the alpha value.
	static MObject alphaGain;

	//! The flag to control if this surface should override global shading sample settings.
	static MObject shadingSamplesOverride;

	//! Specifies the minimum number of shading samples should be taken for this surface during rendering.
	static MObject shadingSamples;

	//! Specifies the max number of shading samples can be taken for this surface during rendering.
	static MObject maxShadingSamples;

	//! If enabled, the image plane is locked to the camera's position.
	static MObject lockedToCamera;

	//! Controls the distance of the plane from the camera.
	static MObject depth;

	//! Applies a horizontal scaling to an image.
	static MObject squeezeCorrection;

	//! Controls the width and height of the image plane.
	static MObject size;

	//! Image plane width
	static MObject sizeX;

	//! Image plane height.
	static MObject sizeY;

	//! Controls how much the center of the image plane is offset
	//! from the centre of the viewing frustum of the camera.
	static MObject offset;

	//! Horizontal component of Offset
	static MObject offsetX;

	//! Vertical component of Offset
	static MObject offsetY;

	//! Controls the world-space position of the center
	//! of the image plane.
	static MObject center;

	//! X component of Center
	static MObject centerX;

	//! Y component of Center
	static MObject centerY;

	//! Z component of Center
	static MObject centerZ;

	//! Controls the width of the image plane in world space.
	static MObject width;

	//! Controls the height of the image plane in world space.
	static MObject height;

	//! When ray tracing, controls whether the image plane
	//! will sppear in reflected surfaces.
	static MObject visibleInReflections;

	//! When ray tracing, controls whether the image plane will
	//! appear when seen through a transparent, refractive surface.
	static MObject visibleInRefractions;

	//! Rotation of the image plane around the view vector.
	static MObject rotate;

	//! Indicates if the image plane has already been pre-multiplied by its
	//! alpha.
	static MObject alreadyPremult;

	//! Indicates that the image plane has depth information.
	static MObject useDepthMap;

	//!	Indicates whether or not the image plane's color should be
	//!	composited into the final image.
	static MObject composite;

	//! Indicates if the depth information is at a higher resolution
	//! than the image resolution.
	static MObject depthOversample;

	//! Users can specify a depth buffer that is larger than the
	//! image buffer using the 'depthFile' attribute.
	static MObject separateDepth;

	//! Separate file that contains depth information.
	static MObject depthFile;

	//! Depth offset value -- centered at the center of the view frustum.
	static MObject depthBias;

	//! Scale the depth -- centered at the center of the view frustum.
	static MObject depthScale;

	static const char*	    className();

OPENMAYA_PRIVATE:
    static void				initialSetup();
};

OPENMAYA_NAMESPACE_CLOSE

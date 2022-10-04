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
// CLASS:    MRenderTargetLegacy
//
// ****************************************************************************

#include <maya/MTypes.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MRenderTargetLegacy)

//! \ingroup OpenMayaRender
/*!
	MRenderTargetLegacy is a class contains information about a given
	hardware render target.
*/

class OPENMAYARENDER_EXPORT OPENMAYA_DEPRECATED(2016, "Use MHWRender::MRenderTargetManager and MHWRender::MRenderTarget instead.") MRenderTargetLegacy
{
public:
	//! Width of render target in pixels
	unsigned int	width() const;

	//! Height of render target in pixels
	unsigned int	height() const;

	void			makeTargetCurrent() const;
	MStatus			writeColorBuffer( const MImage &image, signed short x = 0, signed short y = 0,
										bool writeDepth = false) const;

protected:
	// No protected data

OPENMAYA_PRIVATE:
	MRenderTargetLegacy();
	~MRenderTargetLegacy();
	void			set( void * );
	void			setWidth( unsigned int w ) { fWidth = w; }
	void			setHeight( unsigned int h ) { fHeight = h; }

	// Render target dimensions
	unsigned int	fWidth;
	unsigned int	fHeight;

	void			*fRenderTarget;
};
OPENMAYA_NAMESPACE_CLOSE

#pragma once
//
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
// CLASS:    MPxCameraSet
//
// *****************************************************************************

#include <maya/MTypes.h>
#include <maya/MPxNode.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// *****************************************************************************
// CLASS DECLARATION (MPxCameraSet)

//! \ingroup OpenMaya MPx
//! \brief Base class for user-defined camera set nodes.
/*!
	MPxCameraSet is the parent class of all user defined cameraSet nodes.

	This class can be used to implement new kinds of cameraSets within maya that
	behave in a similar manner to the cameraSet node included in maya.
*/
class OPENMAYA_EXPORT MPxCameraSet : public MPxNode  
{
public:

	MPxCameraSet();
	~MPxCameraSet() override;
	MPxNode::Type type() const override;

	//
    // Attributes
	//

	//!  Compound array attribute for storing the list of camera layers.
	static MObject 		cameraLayer;

	//!  Message attribute connecting to layer's camera transform. Child of 'cameraLayer'.
	static MObject 		camera;

	//!  Message attribute connecting to layer's objectSet. Child of 'cameraLayer'.
	static MObject 		sceneData;

	//!  Boolean attribute determining if layer will be processed. Child of 'cameraLayer'.
	static MObject 		active;

	//!  Integer attribute giving the processing order of the layer. Child of 'cameraLayer'.
	static MObject 		order;

	static const char*	className();

OPENMAYA_PRIVATE:
    static void			initialSetup();
};

OPENMAYA_NAMESPACE_CLOSE

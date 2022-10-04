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
// CLASS:    MFnToolContext
//
// *****************************************************************************

#include <maya/MFnBase.h>
#include <maya/MString.h>
#include <maya/MObject.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// *****************************************************************************
// CLASS DECLARATION (MFnToolContext)

//! \ingroup OpenMaya MFn
//! \brief Tool context function set.
/*!
	MFnToolContext is the function set that is used for querying tool contexts.

	Typically this could be used in conjunction with MGlobal::currentToolContext().
*/
class OPENMAYAUI_EXPORT MFnToolContext : public MFnBase
{

	declareMFn(MFnToolContext, MFnBase);

public:

	MString		name( MStatus* = NULL ) const;
	MString		title( MStatus* = NULL ) const;

BEGIN_NO_SCRIPT_SUPPORT:

 	declareMFnConstConstructor( MFnToolContext, MFnBase );

END_NO_SCRIPT_SUPPORT:

private:
};

// *****************************************************************************
OPENMAYA_NAMESPACE_CLOSE

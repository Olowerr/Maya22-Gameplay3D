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
// CLASS:    MFnNIdData
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MFnNIdData)
// 
// This class is the function set for nucleus geometry data.
//
// *****************************************************************************

#include <maya/MFnData.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// *****************************************************************************

// CLASS DECLARATION (MFnNIdData)

//! \ingroup OpenMayaFX MFn
//! \brief function set for nId object data 
/*!
  Class for transferring N id data between connections
*/

class OPENMAYAFX_EXPORT MFnNIdData : public MFnData 
{

    declareMFn( MFnNIdData, MFnData );

public:

    MObject         create() const ;    
BEGIN_NO_SCRIPT_SUPPORT:
	//!	NO SCRIPT SUPPORT
    MStatus			getObjectPtr( MnObject *& ptr ) const;
END_NO_SCRIPT_SUPPORT:
    MnObject *		getObjectPtr( MStatus *status=NULL ) const;

BEGIN_NO_SCRIPT_SUPPORT:

 	declareMFnConstConstructor( MFnNIdData, MFnData );
	
END_NO_SCRIPT_SUPPORT:

protected:
// No protected members

private:
// No Private members
 
};

OPENMAYA_NAMESPACE_CLOSE

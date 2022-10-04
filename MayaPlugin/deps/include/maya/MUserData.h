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
// CLASS:    MUserData
//
// ****************************************************************************
//
// CLASS DESCRIPTION (MUserData)
//
//  MUserData is a virtual base class meant to provide a means for users to
//  attach blind data to certain Maya object types such that the lifetime of
//  the blind data is managed by Maya.
//
// ****************************************************************************

#include <maya/MApiNamespace.h>
#include <maya/MDeprecate.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// INCLUDED HEADER FILES

// ****************************************************************************
// DECLARATIONS

// ****************************************************************************
// CLASS DECLARATION (MUserData)

//! \ingroup OpenMayaRender MPx
//! \brief Virtual base class for user data caching
/*!
MUserData is a virtual base class meant to provide a means for users to
attach blind data to certain Maya object types such that the lifetime of
the blind data is managed by Maya.
*/
class OPENMAYA_EXPORT MUserData
{
public:
	OPENMAYA_DEPRECATED(2022, "Please use MUserData() instead. MUserData should be managed with MSharedPtr<MUserData>.")
	MUserData(bool deleteAfterUse);
	MUserData();
	virtual ~MUserData();

	OPENMAYA_DEPRECATED(2022, "Deallocation after use should be managed via MSharedPtr<MUserData>.")
	bool deleteAfterUse();
	OPENMAYA_DEPRECATED(2022, "Deallocation after use should be managed via MSharedPtr<MUserData>.")
	void setDeleteAfterUse(bool shouldDelete);

	static	const char*	className();

private:
	bool fDeleteAfterUse;
};

OPENMAYA_NAMESPACE_CLOSE

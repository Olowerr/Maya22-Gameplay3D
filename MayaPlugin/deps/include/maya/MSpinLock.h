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
// CLASS:    MSpinLock
//
// ****************************************************************************

#include <maya/MTypes.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MSpinLock)

//! \ingroup OpenMaya
//! \brief Methods for managing spin locks on threads.
/*!
 Lightweight spin-lock class to be used with threads.
*/
class OPENMAYA_EXPORT MSpinLock
{

public:
	MSpinLock();

	~MSpinLock();

	void lock();

	void unlock();

	bool tryLock();

private:
	MSpinLock(const MSpinLock&) {}; // disallow this
	MSpinLock & operator=(const MSpinLock&); // disallow this
	void* f_spinLockRef;
};

OPENMAYA_NAMESPACE_CLOSE

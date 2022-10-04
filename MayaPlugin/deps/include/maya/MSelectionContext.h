#pragma once
//-
// ===========================================================================
// Copyright 2020 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
//+

#include <maya/MStatus.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// NAMESPACE

namespace MHWRender
{
// ****************************************************************************
// CLASS DECLARATION (MSelectionContext)
//! \ingroup OpenMayaRender
//! \brief Class to allow control on Viewport 2.0 selection behavior.
/*!
MSelectionContext provides control on selection behavior for a given DAG object.

It cannot be instantiated by plug-ins. During the pre-filtering phase of
Viewport 2.0 selection, an MSelectionContext instance is passed to the following
functions for plug-ins to set up selection context for a custom object:

  \li MPxGeometryOverride::updateSelectionGranularity
  \li MPxSubSceneOverride::updateSelectionGranularity
  \li MPxDrawOverride::updateSelectionGranularity

The MSelectionContext instance is only valid inside these functions, thus
plug-ins should not save its pointer.
*/
class OPENMAYARENDER_EXPORT MSelectionContext
{
public:
	//! Specifies granularity level to use for the selection
    OPENMAYA_ENUM(SelectionLevel,
		kNone,		//!< No selection available.
		kObject,	//!< Object level.
					//!< Objects are selected as a whole. Components are not directly accessible.
		kComponent,	//!< Component level.
					//!< Components such as vertices, edges and faces are selectable.
		kFace,		//!< Face level.
		kEdge,		//!< Edge level.
		kVertex		//!< Vertex level.
	);

	SelectionLevel selectionLevel(MStatus* ReturnStatus = nullptr) const;
	MStatus setSelectionLevel(SelectionLevel level);

	static const char* className();

OPENMAYA_PRIVATE:
    MSelectionContext(void* data);
	virtual ~MSelectionContext();
	void* fData;

#if defined(__linux__) && __GNUC__ >= 9
	friend class MFrameContext;
	friend class MDrawContext;
#endif
}; // MSelectionContext

// ****************************************************************************
// CLASS DECLARATION (MIntersection)
//! \ingroup OpenMayaRender
//! \brief Describes the intersection of a selection hit.
/*!
This class gives a description of an intersection when a selection hit occurs.
*/
class OPENMAYARENDER_EXPORT MIntersection
{
public:
	MSelectionContext::SelectionLevel selectionLevel(
		MStatus* ReturnStatus = nullptr) const;

	int index(MStatus* ReturnStatus = nullptr) const;
	MStatus barycentricCoordinates(float& a, float& b) const;
	float edgeInterpolantValue(MStatus* ReturnStatus = nullptr) const;
	MFloatPoint intersectionPoint(MStatus* ReturnStatus = nullptr) const;
	int instanceID(MStatus* ReturnStatus = nullptr) const;

	static const char* className();

OPENMAYA_PRIVATE:
    MIntersection(const void* data);
	~MIntersection();
	const void* fData;
}; // MIntersection

// ****************************************************************************
// CLASS DECLARATION (MSelectionInfo)
//! \ingroup OpenMayaRender
//! \brief Class to allow access to the selection state information.
/*!
MSelectionInfo encapsulates the selection state information.

It is read-only and cannot be instantiated by plug-ins. During the hit test
phase or the selection interpretation phase of Viewport 2.0 selection, an
MSelectionInfo instance is passed to the following functions for plug-ins to
query the current selection state information:

  \li MPxGeometryOverride::refineSelectionPath
  \li MPxDrawOverride::refineSelectionPath
  \li MPxDrawOverride::userSelect
  \li MRenderOverride::select

The MSelectionInfo instance is only valid inside these functions, thus plug-ins
should not save its pointer.
*/
class OPENMAYARENDER_EXPORT MSelectionInfo
{
public:
	bool singleSelection(MStatus* ReturnStatus = nullptr) const;
	bool selectClosest(MStatus* ReturnStatus = nullptr) const;

	bool selectable(
		const MSelectionMask& mask,
		MStatus* ReturnStatus = nullptr) const;

	bool selectableComponent(
		bool displayed,
		const MSelectionMask& mask,
		MStatus* ReturnStatus = nullptr) const;

	MStatus selectRect(
		unsigned int& x,
		unsigned int& y,
		unsigned int& width,
		unsigned int& height) const;

	MStatus cursorPoint(int& x, int& y) const;

	bool isRay(MStatus* ReturnStatus = nullptr) const;
	MMatrix getAlignmentMatrix(MStatus* ReturnStatus = nullptr) const;
	MStatus getLocalRay(MPoint& pnt, MVector& vec) const;

	bool selectForHilite(
		const MSelectionMask& mask,
		MStatus* ReturnStatus = nullptr) const;

	bool selectOnHilitedOnly(MStatus* ReturnStatus = nullptr) const;

	bool pointSnapping(MStatus* ReturnStatus = nullptr) const;

    bool snapToActive(MStatus* ReturnStatus = nullptr) const;

	static const char* className();

OPENMAYA_PRIVATE:
    MSelectionInfo(const void* data);
	~MSelectionInfo();
	const void* fData;

#if defined(__linux__) && __GNUC__ >= 9
	friend class MDrawContext;
	friend class MFrameContext;
#endif
};

} // namespace MHWRender

OPENMAYA_NAMESPACE_CLOSE

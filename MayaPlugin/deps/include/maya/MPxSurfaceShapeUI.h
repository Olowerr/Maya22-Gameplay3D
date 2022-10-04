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
// CLASS:    MPxSurfaceShapeUI
//
// ****************************************************************************

#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <maya/MObject.h>
#include <maya/MPxNode.h>
#include <maya/MDeprecate.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

class M3dView;
class MSelectInfo;
class MDrawRequest;
class MDrawRequestQueue;

// ****************************************************************************
// CLASS DECLARATION (MPxNode)

//! \ingroup OpenMayaUI MPx
//! \brief drawing and selection for user defined shapes
/*!
The base class for the UI portion of all user defined shapes.
*/
class OPENMAYAUI_EXPORT MPxSurfaceShapeUI
{
public:
	MPxSurfaceShapeUI();
	virtual ~MPxSurfaceShapeUI();

	//! Selection modes for UVs
    OPENMAYA_ENUM(UVSelectionType,
		kSelectMeshUVs,		//!< The UV selection type is UVs.
		kSelectMeshVerts,	//!< The UV selection type is vertices.
		kSelectMeshFaces,	//!< The UV selection type is faces.
		kSelectMeshEdges	//!< The UV selection type is edges.
    );

	OPENMAYA_DEPRECATED(2019, "Please use MHWRender::MPxGeometryOverride, MHWRender::MPxSubSceneOverride, or MHWRender::MPxDrawOverride instead.")
	void					getDrawData( const void * geom, MDrawData & );

	// ************************************************************************
	// Methods to overload

	OPENMAYA_DEPRECATED(2019, "Please use MHWRender::MPxGeometryOverride, MHWRender::MPxSubSceneOverride, or MHWRender::MPxDrawOverride instead.")
	virtual void			getDrawRequests( const MDrawInfo &,
											 bool objectAndActiveOnly,
											 MDrawRequestQueue & requests );

	OPENMAYA_DEPRECATED(2019, "Please use MHWRender::MPxGeometryOverride, MHWRender::MPxSubSceneOverride, or MHWRender::MPxDrawOverride instead.")
	virtual void		    draw( const MDrawRequest &, M3dView & view ) const;

	virtual bool		    select( MSelectInfo &selectInfo,
							    	MSelectionList &selectionList,
							    	MPointArray &worldSpaceSelectPts ) const;
	virtual bool			snap( MSelectInfo & snapInfo ) const;

	virtual bool			canDrawUV() const;
	virtual void			drawUV(M3dView &view, const MTextureEditorDrawInfo &info) const;

	virtual bool			selectUV( M3dView &view,
									  UVSelectionType selType,
									  int xmin, int ymin,
									  int xmax, int ymax,
									  bool singleSelect,
									  MSelectionList &selList ) const;

	// ************************************************************************

	MPxSurfaceShape*		surfaceShape() const;
	MMaterial 				material( MDagPath & path ) const;
	void					materials( MDagPath & path, MObjectArray & componentFilter, MMaterialArray & materials, MObjectArray * componentSet = NULL) const;

	static MPxSurfaceShapeUI *	surfaceShapeUI( const MDagPath & path, MStatus *ReturnStatus = NULL );

	static const char*	    className();

OPENMAYA_PRIVATE:
    void * instance;
};

OPENMAYA_NAMESPACE_CLOSE

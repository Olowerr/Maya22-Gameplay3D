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
// CLASS:    MPxSurfaceShape
//
// ****************************************************************************

#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <maya/MObject.h>
#include <maya/MPxNode.h>
#include <maya/MBoundingBox.h>
#include <maya/MSelectionMask.h>

// ****************************************************************************
// DECLARATIONS

class MSelectArgs;

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MPxSurfaceShape)

//! \ingroup OpenMaya MPx
//! \brief Parent class of all user defined shapes. 
/*!
  MPxSurfaceShape is the parent class of all user defined shapes.
  User defined shapes are dependency nodes (and DAG nodes) which contain
  overridable drawing, selection, and component methods.

  This class can be used to implement new kinds of shapes within Maya that
  can have selectable/manipulatable components and behave in a similar
  manner to the default shapes in maya.

  The UI dependent aspects of the shape should be implemented in a class
  derived from MPxSurfaceShapeUI. This includes the drawing and interactive
  selection of the shape and any components that the shape implements.
*/
class OPENMAYA_EXPORT MPxSurfaceShape : public MPxNode
{
public:
	MPxSurfaceShape();
	~MPxSurfaceShape() override;
	MPxNode::Type type() const override;


	// ************************************************************
	// Methods to overload

	virtual bool		    isBounded() const;
	virtual MBoundingBox    boundingBox() const;

	//! Vertex caching modes.
    OPENMAYA_ENUM(MVertexCachingMode,
		kNoPointCaching,	//!< No point caching.
		kSavePoints,		//!< Points should be saved for undo in the point cache.
		kRestorePoints,		//!< Points should be restored from the point cache.
		kUpdatePoints,		//!< Transform and update the points in the point cache
		kTransformOriginalPoints	//!< Transform using use the original pre-transformation values stored in the pointCache.
	);

	virtual bool    evalNodeAffectsDrawDb(const MEvaluationNode& evaluationNode);

	// Move tool support for components
	virtual void		    transformUsing( const MMatrix& mat,
							    			const MObjectArray& componentList );
	virtual void		    transformUsing( const MMatrix& mat,
							    			const MObjectArray& componentList,
											MVertexCachingMode cachingMode,
											MPointArray* pointCache);
	virtual void		    tweakUsing( const MMatrix& mat,
										const MObjectArray& componentList,
										MVertexCachingMode cachingMode,
										MPointArray* pointCache,
										MArrayDataHandle& handle );
	bool					convertToTweakNodePlug(MPlug& plug) const;

	virtual void			weightedTransformUsing(	const MTransformationMatrix& xform,
													const MMatrix* space,
													const MObjectArray& componentList,
													MVertexCachingMode cachingMode,
													MPointArray* pointCache,
													const MPlane* freezePlane );
	virtual void			weightedTweakUsing(		const MTransformationMatrix& xform,
													const MMatrix* space,
													const MObjectArray& componentList,
													MVertexCachingMode cachingMode,
													MPointArray* pointCache,
													const MPlane* freezePlane,
													MArrayDataHandle& handle );

	//! Vertex offset modes.
    OPENMAYA_ENUM(MVertexOffsetMode,
		kNormal,			//!< Move in normal direction.
		kUTangent,			//!< Move in u tangent direction.
		kVTangent,			//!< Move in v tangent direction.
		kUVNTriad			//!< Calculate u, v, and normal offsets.
	);

	virtual bool			vertexOffsetDirection( MObject & component,
                                                   MVectorArray & direction,
                                                   MVertexOffsetMode mode,
												   bool normalize );
	virtual MObject			newControlPointComponent( ) const;

	virtual void			componentToPlugs( MObject& component,
											  MSelectionList& selectionList
											) const;
	virtual bool			match( const MSelectionMask & mask,
					    		   const MObjectArray& componentList ) const;

	//! Return values for the matchComponent() method.
    OPENMAYA_ENUM(MatchResult,
		//! The component was matched without error.
		kMatchOk,
		//! No component was matched.
		kMatchNone,
		//! Not used.
		kMatchTooMany,
		//! One of the names in the attribute specification was not valid.
		kMatchInvalidName,
		//! Not used.
		kMatchInvalidAttribute,
		//! The attribute specification contained an index for a non-array
		//! attribute.
		kMatchInvalidAttributeIndex,
		//! An attribute index was out of range.
		kMatchInvalidAttributeRange,
		//! The attribute specification provided the wrong number of dimensions
		//! for an attribute.
		kMatchInvalidAttributeDim
	);
	virtual MatchResult		matchComponent( const MSelectionList& item,
											const MAttributeSpecArray& spec,
											MSelectionList& list );

	virtual MSelectionMask	getShapeSelectionMask() const;
	virtual MSelectionMask	getComponentSelectionMask() const;

	virtual MObject			createFullVertexGroup() const;
	virtual MObject			createFullRenderGroup() const;

	virtual MFn::Type		renderGroupComponentType() const;

	virtual bool deleteComponents( const MObjectArray& componentList,
								   MDoubleArray& undoInfo );
	virtual bool undeleteComponents( const MObjectArray& componentList,
									 MDoubleArray& undoInfo );

	virtual MObject 		localShapeInAttr() const;
	virtual MObject 		localShapeOutAttr() const;
	virtual MObject 		worldShapeOutAttr() const;
	virtual MObject 		cachedShapeAttr() const;

	virtual MObject			geometryData() const;

	virtual bool			canMakeLive() const;
	virtual bool			closestPoint(
										const MPoint &raySource,
										const MVector &rayDirection,
										MPoint &theClosestPoint,
										MVector &theClosestNormal,
										bool findClosestOnMiss, 
										double tolerance=MPoint_kTol);
	virtual void			closestPoint( const MPoint& toThisPoint,
										  MPoint& theClosestPoint,
										  double tolerance=MPoint_kTol);
	virtual bool			pointAtParm( const MPoint& atThisParm,
										  MPoint& evaluatedPoint );

	// Geometry iterator methods
	//
	virtual	MPxGeometryIterator *
							geometryIteratorSetup( MObjectArray&, MObject&,
												   bool forReadOnly = false );
	virtual bool			acceptsGeometryIterator( bool  writeable=true );
	virtual bool			acceptsGeometryIterator( MObject&,
													 bool writeable=true,
													 bool forReadOnly = false);

	virtual bool			excludeAsPluginShape() const;

	// ************************************************************

	MObjectArray 			activeComponents() const;
	bool					hasActiveComponents() const;

	//! Scope of change.
    OPENMAYA_ENUM(MChildChanged,
		//! Object geometry changed. Internal caches need to be updated.
		kObjectChanged,
		//! Object geometry is unchanged but its bounding box has changed. This
		//! might happen if the object was moved or an offset changed.
		kBoundingBoxChanged
	);
	void                    childChanged( MChildChanged = kObjectChanged );

	// Marking the object as renderable allows the shaders to be hooked up
    bool                    isRenderable() const;
	void			        setRenderable( bool );

	MMatrix		getWorldMatrix( MDataBlock &, unsigned int ) const;

	// ************************************************************

    // Inherited attributes

	// If true, the object has history and the control point attribute
	// values are tweaks, not the actual values.
	static MObject mHasHistoryOnCreate;

	//! Control points for the derived shapes
	static MObject mControlPoints;
		//! X value of a control point
		static MObject mControlValueX;
		//! Y value of a control point
		static MObject mControlValueY;
		//! Z value of a control point
		static MObject mControlValueZ;

	//! bounding box attribute
	static MObject nodeBoundingBox;
	    //! bounding box minimum point
	    static MObject nodeBoundingBoxMin;
	        //! X component of boundingBoxMin
	        static MObject nodeBoundingBoxMinX;
	        //! Y component of boundingBoxMin
	        static MObject nodeBoundingBoxMinY;
	        //! Z component of boundingBoxMin
	        static MObject nodeBoundingBoxMinZ;
	    //!  bounding box maximum point
	    static MObject nodeBoundingBoxMax;
	        //! X component of boundingBoxMax
	        static MObject nodeBoundingBoxMaxX;
	        //! Y component of boundingBoxMax
	        static MObject nodeBoundingBoxMaxY;
	        //! Z component of boundingBoxMax
	        static MObject nodeBoundingBoxMaxZ;
	    //!  bounding box size vector
	    static MObject nodeBoundingBoxSize;
	        //! X component of boundingBoxSize
	        static MObject nodeBoundingBoxSizeX;
	        //! Y component of boundingBoxSize
	        static MObject nodeBoundingBoxSizeY;
	        //! Z component of boundingBoxSize
	        static MObject nodeBoundingBoxSizeZ;
	//! object center attribute
	static MObject center;
	    //! X component of boundingBoxCenter
	    static MObject boundingBoxCenterX;
	    //! Y component of boundingBoxCenter
	    static MObject boundingBoxCenterY;
	    //! Z component of boundingBoxCenter
	    static MObject boundingBoxCenterZ;
	//! matrix attribute
	static MObject matrix;
	//! inverse matrix attribute
	static MObject inverseMatrix;
	//! world matrix attribute
	static MObject worldMatrix;
	//! inverse world matrix attribute
	static MObject worldInverseMatrix;
	//! parent matrix attribute
	static MObject parentMatrix;
	//! inverse parent matrix attribute
	static MObject parentInverseMatrix;
	//! visibility attribute
	static MObject visibility;
	//! intermediate object attribute
	static MObject intermediateObject;
	//! template attribute
	static MObject isTemplated;
	//! instances object group info attribute
	static MObject instObjGroups;
	    //! object groups attributes
	    static MObject objectGroups;
	        //! component in object groups attribute
	        static MObject objectGrpCompList;
	        //! group id attribute
	        static MObject objectGroupId;
	        //! group id attribute
	        static MObject objectGroupColor;
	//! controls choice of wireframe dormant object color
	static MObject useObjectColor;
	//! the per object dormant wireframe color
	static MObject objectColor;

	static const char*	    className();

protected:

OPENMAYA_PRIVATE:
	static void				initialSetup();
};

OPENMAYA_NAMESPACE_CLOSE

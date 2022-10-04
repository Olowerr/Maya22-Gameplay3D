#ifndef _MFnTransform
#define _MFnTransform

// ===========================================================================
// Copyright 2018 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================

// ****************************************************************************
//
// CLASS:    MFnTransform
//
// ****************************************************************************

// ****************************************************************************
// INCLUDED HEADER FILES

#include <maya/MDeprecate.h>
#include <maya/MFnDagNode.h>
#include <maya/MTransformationMatrix.h>
#include <maya/MObject.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MFnTransform)

//! \ingroup OpenMaya MFn
//! \brief Create and access transform nodes.
/*!
  The MFnTransform function set provides access to transformation DAG nodes
  called transforms.

  DAG nodes are separated into two types, transforms and geometry
  nodes.  All DAG nodes that are not transform nodes must exist as a
  child of a transform node.  Only transforms provide transformation
  information.  Transforms are also commonly used as parent nodes for
  the purpose of hierarchical grouping.

  The transformation in the node is represented as a 4x4
  transformation matrix.  This function set allows access to the whole
  matrix, or the individual components (eg scale, rotation, shear,
  etc) of the transformation.  The transform node is made up of many
  components that make up the final transformation matrix.  This
  breakdown provides animators fine control over the animation of
  these parameters. Therefore, it is necessary to describe the order
  in which these attributes are applied to build the final matrix
  attribute.

  A transformation matrix is composed of the following components. All
  components with units will be in Maya's internal units (radians for
  rotations and centimeters for translations):


  \li <b>Scale pivot point</b>        point around which scales are performed [Sp]
  \li <b>Scale</b>                    scaling about x, y, z axes [S]
  \li <b>Shear</b>                    shearing in xy, xz, yx [Sh]
  \li <b>Scale pivot translation</b>  translation introduced to preserve existing
                                       scale transformations when moving pivot.  This
									   is used to prevent the object from moving when
									   the object's pivot point is not at the origin
									   and a non-unit scale is applied to the object [St].
  \li <b>Rotate pivot point</b>       point about which rotations are performed [Rp]
  \li <b>Rotation orientation</b>     rotation to orient local rotation space [Ro]
  \li <b>Rotation</b>                 rotation [R]
  \li <b>Rotate pivot translation</b> translation introduced to preserve existing
                                       rotate transformations when moving pivot. This
									   is used to prevent the object from moving when
									   the object's pivot point is not at the origin and
									   the pivot is moved. [Rt]
  \li <b>Translate</b>                translation in x, y, z axes [T]


  The matrices are post-multiplied in Maya. For example, to transform
  a point P from object-space to world-space (P') you would need to
  post-multiply by the worldMatrix. (P' = P x WM)

  The transformation matrix is then constructed as follows:

\code
     -1                       -1
  [Sp]x[S]x[Sh]x[Sp]x[St]x[Rp]x[Ro]x[R]x[Rp]x[Rt]x[T]
\endcode

  where 'x' denotes matrix multiplication and '-1' denotes matrix inversion

\code
     Sp = |  1    0    0    0 |     St = |  1    0    0    0 |
          |  0    1    0    0 |          |  0    1    0    0 |
          |  0    0    1    0 |          |  0    0    1    0 |
          | spx  spy  spz   1 |          | sptx spty sptz  1 |

     S  = |  sx   0    0    0 |     Sh = |  1    0    0    0 |
          |  0    sy   0    0 |          | shxy  1    0    0 |
          |  0    0    sz   0 |          | shxz shyz  1    0 |
          |  0    0    0    1 |          |  0    0    0    1 |

     Rp = |  1    0    0    0 |     Rt = |  1    0    0    0 |
          |  0    1    0    0 |          |  0    1    0    0 |
          |  0    0    1    0 |          |  0    0    1    0 |
          | rpx  rpy  rpz   1 |          | rptx rpty rptz  1 |

     Ro = AX * AY * AZ

     AX = |  1    0    0    0 |     AY = |  cy   0   -sy   0 |
          |  0    cx   sx   0 |          |  0    1    0    0 |
          |  0   -sx   cx   0 |          |  sy   0    cy   0 |
          |  0    0    0    1 |          |  0    0    0    1 |

     AZ = |  cz   sz   0    0 |     sx = sin(rax), cx = cos(rax)
          | -sz   cz   0    0 |     sy = sin(ray), cx = cos(ray)
          |  0    0    1    0 |     sz = sin(raz), cz = cos(raz)
          |  0    0    0    1 |

  	 R  = RX * RY * RZ  (Note: order is determined by rotateOrder)

     RX = |  1    0    0    0 |     RY = |  cy   0   -sy   0 |
          |  0    cx   sx   0 |          |  0    1    0    0 |
          |  0   -sx   cx   0 |          |  sy   0    cy   0 |
          |  0    0    0    1 |          |  0    0    0    1 |

     RZ = |  cz   sz   0    0 |     sx = sin(rx), cx = cos(rx)
          | -sz   cz   0    0 |     sy = sin(ry), cx = cos(ry)
          |  0    0    1    0 |     sz = sin(rz), cz = cos(rz)
          |  0    0    0    1 |

     T  = |  1    0    0    0 |
          |  0    1    0    0 |
          |  0    0    1    0 |
          |  tx   ty   tz   1 |
\endcode

  Note that internally the Maya transform does not store the
  individual component values in matrices. It stores them in the data
  structure which makes the most sense for that component. For
  example, translation is stored as a vector. The accessor methods on
  MFnTransform provide  the data in their native structure rather than as a matrix.

  Additionally, each transform can save a temporary "rest position" matrix
  using the setRestPosition method. The rest position is not used internally
  by Maya. It is exclusively for use from the API as a temporary cache, which
  can be set and restored within a single Maya session. Note that the rest
  position is not saved with the scene.
*/
class OPENMAYA_EXPORT MFnTransform : public MFnDagNode
{
	declareDagMFn( MFnTransform, MFn::kTransform );
public:
	MObject     create( MObject parent = MObject::kNullObj,
						MStatus * ReturnStatus = nullptr );
	MTransformationMatrix transformation( MStatus * ReturnStatus = nullptr ) const;
	MStatus		set		( const MTransformationMatrix& transform );

	// Translation
	MVector		getTranslation	( MSpace::Space space, MStatus * ReturnStatus = nullptr ) const;
	MStatus 	setTranslation	( const MVector & vec, MSpace::Space space );
	MStatus 	translateBy		( const MVector & vec, MSpace::Space space );

	// Scale
	MStatus		getScale(       double scale[3] )			const;
	MStatus 	setScale( const double scale[3] );
	MStatus 	scaleBy	( const double scale[3] ) ;
	// Pivots
	MPoint		scalePivot				 ( MSpace::Space space, MStatus * ReturnStatus = nullptr ) const;
	MStatus 	setScalePivot			 ( const MPoint& point, MSpace::Space space, bool balance );
	MVector		scalePivotTranslation	 ( MSpace::Space space, MStatus * ReturnStatus = nullptr ) const;
	MStatus 	setScalePivotTranslation ( const MVector& vec, MSpace::Space space );

	// Shear
	MStatus 	getShear(       double scale[3] )			const;
	MStatus 	setShear( const double shear[3] );
	MStatus 	shearBy	( const double shear[3] );

	// Quaternion Rotation
	MStatus 	getRotation	( MQuaternion &quaternion, MSpace::Space = MSpace::kTransform ) const;
	MStatus 	setRotation	( const MQuaternion &quaternion, MSpace::Space = MSpace::kTransform );
	MStatus 	rotateBy	( const MQuaternion &quaternion, MSpace::Space = MSpace::kTransform);

	// Euler Rotation
	MStatus 	getRotation	( MEulerRotation &rotation ) const;
	MStatus 	setRotation	( const MEulerRotation &rotation );
	MStatus 	rotateBy	( const MEulerRotation &rotation, MSpace::Space = MSpace::kTransform);
	// Pivots
	MPoint		rotatePivot				 ( MSpace::Space space, MStatus * ReturnStatus = nullptr ) const;
	MStatus 	setRotatePivot			 ( const MPoint& point, MSpace::Space space, bool balance );
	MVector		rotatePivotTranslation	 ( MSpace::Space space, MStatus * ReturnStatus = nullptr ) const;
	MStatus 	setRotatePivotTranslation( const MVector& vec, MSpace::Space space );

	// Separated Quaternion values
	MStatus 	getRotationQuaternion( double &x, double &y, double &z, double &w,
									   MSpace::Space = MSpace::kTransform) const;
	MStatus 	setRotationQuaternion( double x, double y, double z, double w,
									   MSpace::Space = MSpace::kTransform);
	MStatus 	rotateByQuaternion( double x, double y, double z, double w,
									MSpace::Space = MSpace::kTransform);
	// Rotation array of values
	MStatus 	getRotation	(       double rotation[3], MTransformationMatrix::RotationOrder& order ) const;
	MStatus 	setRotation	( const double rotation[3], MTransformationMatrix::RotationOrder order );
	MStatus 	rotateBy	( const double rotation[3], MTransformationMatrix::RotationOrder order, MSpace::Space = MSpace::kTransform);

	// Other transformations
	MQuaternion	rotateOrientation		 ( MSpace::Space space, MStatus * ReturnStatus = nullptr ) const;
	MStatus 	setRotateOrientation	 ( const MQuaternion& quat, MSpace::Space space, bool balance );
	MTransformationMatrix::RotationOrder
                rotationOrder			 ( MStatus* ReturnStatus = nullptr ) const;
	MStatus 	setRotationOrder		 ( MTransformationMatrix::RotationOrder order, bool reorder );
	MTransformationMatrix restPosition	 ( MStatus* ReturnStatus) const;
	MStatus		setRestPosition			 ( const MTransformationMatrix& matrix );
	MStatus		resetFromRestPosition	 ();
	MStatus		clearRestPosition		 ();

	//! Limit types.
    OPENMAYA_ENUM(LimitType,
		kScaleMinX,		//!< \nop
		kScaleMaxX,		//!< \nop
		kScaleMinY,		//!< \nop
		kScaleMaxY,		//!< \nop
		kScaleMinZ,		//!< \nop
		kScaleMaxZ,		//!< \nop
		kShearMinXY,		//!< \nop
		kShearMaxXY,		//!< \nop
		kShearMinXZ,		//!< \nop
		kShearMaxXZ,		//!< \nop
		kShearMinYZ,		//!< \nop
		kShearMaxYZ,		//!< \nop
		kRotateMinX,		//!< \nop
		kRotateMaxX,		//!< \nop
		kRotateMinY,		//!< \nop
		kRotateMaxY,		//!< \nop
		kRotateMinZ,		//!< \nop
		kRotateMaxZ,		//!< \nop
		kTranslateMinX,		//!< \nop
		kTranslateMaxX,		//!< \nop
		kTranslateMinY,		//!< \nop
		kTranslateMaxY,		//!< \nop
		kTranslateMinZ,		//!< \nop
		kTranslateMaxZ		//!< \nop
	);

	bool	isLimited( MFnTransform::LimitType type,
						MStatus * ReturnStatus = nullptr ) const;
	double	limitValue ( MFnTransform::LimitType type,
						MStatus * ReturnStatus = nullptr ) const;
	MStatus	setLimit ( MFnTransform::LimitType type, double value);

	MStatus	enableLimit ( MFnTransform::LimitType type, bool flag);

BEGIN_NO_SCRIPT_SUPPORT:

 	declareDagMFnConstConstructor( MFnTransform, MFn::kTransform );

END_NO_SCRIPT_SUPPORT:

	OPENMAYA_DEPRECATED(85, "Use getRotation(double[3], MTransformationMatrix::RotationOrder&) instead.")
	MStatus     getRotation(      double[3], MTransformationMatrix::RotationOrder& order, MSpace::Space space) const;

	OPENMAYA_DEPRECATED(85, "Use setRotation(const double[3], MTransformationMatrix::RotationOrder) instead.")
	MStatus     setRotation(const double[3], MTransformationMatrix::RotationOrder,  MSpace::Space space);

	OPENMAYA_DEPRECATED(85, "Use getTranslation(MSpace::Space, MStatus*) instead.")
	MVector     translation(MSpace::Space, MStatus* = nullptr) const;

protected:
	bool objectChanged( MFn::Type, MStatus * ) override;

private:
// No private members
};

OPENMAYA_NAMESPACE_CLOSE

#endif /* _MFnTransform */

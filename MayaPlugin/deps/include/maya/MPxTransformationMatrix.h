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
// CLASS:	MPxTransformationMatrix
//
// Description:
//
//		This is the API side of user defined transformation matrices.
//		Any MPxTransformationMatrix will have an associated THxformMatrix
//		class to handle the Maya side of things.
//
// ****************************************************************************

#include <maya/MTypeId.h>
#include <maya/MStatus.h>
#include <maya/MTypes.h>
#include <maya/MTransformationMatrix.h>

#include <maya/MMatrix.h>
#include <maya/MQuaternion.h>
#include <maya/MEulerRotation.h>
#include <maya/MVector.h>
#include <maya/MPoint.h>

class THxformMatrix;

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MPxTransformationMatrix)

//! \ingroup OpenMaya MPx
//! \brief Base class of all user defined transformation matrices. 
/*!
	MPxTransformationMatrix is the parent class for all user defined
	transformation matrices. A transformation matrix is a class that
	holds the individual components (i.e. translate, rotate, scale, pivots,
	etc.) that are used to construct a 4x4 matrix. Given that different
	combinations of transform components may produce similar 4x4 matrices,
	it is not always possible to get a generic 4x4 matrix and decompose it
	into unique components. This class allows better control over which
	components are changed than a generic 4x4 MMatrix could offer.

	The MPxTransformationMatrix class is designed for use as the
	mathematical brains behind the MPxTransform node. This separation is
	useful for class reuse (different types of MPxTransform nodes may still
	use the same MPxTransformationMatrix class) as well as simplifying the
	MPxTransform class.

	The MPxTransformationMatrix class is registered using the
	MFnPlugin::registerTransform() method. Both the MPxTransform and the
	MPxTransformationMatrix classes are registered in the same method. This
	allows for a clear association between a MPxTransform and a
	MPxTransformationMatrix.

	When registering the MPxTransformationMatrix, a MTypeId is required.
	For nodes using the default MPxTransformationMatrix, a statically
	defined MTypeId is provided by the
	MPxTransformationMatrix::baseTransformationMatrixId data member.

	Since the MPxTransformationMatrix class gives extended functionality
	to a native Maya class, several methods are given that are needed
	by Maya for this class to properly function in different settings.

	To create a transformation matrix, derive from this class and overload
	the creator() method and the assignment operator for the derived class.
	If any additional data items are added to this class, the copyValues()
	method should also be overloaded. This will ensure that the new values
	will get properly handed by Maya. The rest of the methods may be
	overloaded as needed.
*/
class OPENMAYA_EXPORT MPxTransformationMatrix {
public:
					MPxTransformationMatrix();
					MPxTransformationMatrix(const MTransformationMatrix &);
					MPxTransformationMatrix(const MPxTransformationMatrix &);
					MPxTransformationMatrix(const MMatrix &);
	virtual			~MPxTransformationMatrix();

	virtual void	copyValues(MPxTransformationMatrix *);

	virtual 		MTypeId	typeId() const;

	MPxTransformationMatrix & operator = (const MPxTransformationMatrix &src);
	MPxTransformationMatrix & operator = (const MMatrix &src);
	MPxTransformationMatrix & operator = (const MTransformationMatrix &src);
	bool	  				  operator == (const MPxTransformationMatrix &);
	bool	  				  operator != (const MPxTransformationMatrix &);
	bool					  operator == (const MTransformationMatrix &);
	bool	  				  operator != (const MTransformationMatrix &);
	bool					  operator == (const MMatrix &);
	bool					  operator != (const MMatrix &);

	virtual bool 				isEquivalent(const MPxTransformationMatrix &,
										double tolerance = MMatrix_kTol) const;
	virtual bool 				isEquivalent(const MTransformationMatrix &,
										double tolerance = MMatrix_kTol) const;
	virtual bool 				isEquivalent(const MMatrix &,
										double tolerance = MMatrix_kTol) const;
	virtual MPxTransformationMatrix reverse() const;
	virtual MPxTransformationMatrix	&transformBy(const MTransformationMatrix &);

	virtual MMatrix		asMatrix() const;
	virtual MMatrix		asMatrixInverse() const;
	virtual MMatrix		asScaleMatrix() const;
	virtual MMatrix 	asScaleMatrixInverse() const;
	virtual MMatrix		asRotateMatrix() const;
	virtual MMatrix 	asRotateMatrixInverse() const;
	virtual MMatrix		asMatrix(double percent) const;
	virtual MMatrix		asInterpolationMatrix(const MTransformationMatrix &toM,
											double percent, bool rot,
											int direction = 0) const;
	virtual MTransformationMatrix	asTransformationMatrix() const;

	//
	//	Translation methods:
	//

	virtual MVector 		translation(MSpace::Space = MSpace::kTransform,
										MStatus* ReturnStatus = NULL) const;
	virtual MStatus 		translateTo(const MVector &vector,
										MSpace::Space = MSpace::kTransform);
	virtual MStatus			translateBy(const MVector &vector,
										MSpace::Space = MSpace::kTransform);

	//
	//	Rotation methods:
	//

	virtual MQuaternion		rotation(MSpace::Space = MSpace::kTransform,
									 MStatus *ReturnStatus = NULL) const;
	virtual MEulerRotation	eulerRotation(MSpace::Space space = MSpace::kTransform,
									MStatus *ReturnStatus = NULL) const;
	virtual MStatus 	rotateTo(const MQuaternion &q,
								 MSpace::Space = MSpace::kTransform);
	virtual MStatus 	rotateBy(const MQuaternion &q,
								 MSpace::Space = MSpace::kTransform);
	virtual MStatus		rotateTo(const MEulerRotation &e,
								 MSpace::Space = MSpace::kTransform);
	virtual MStatus 	rotateBy(const MEulerRotation &e,
								 MSpace::Space = MSpace::kTransform);
	virtual MTransformationMatrix::RotationOrder
						rotationOrder(MStatus* ReturnStatus = NULL) const;
	virtual MStatus		setRotationOrder(MTransformationMatrix::RotationOrder,
										 bool preserve = true);
	virtual MQuaternion	rotateOrientation(MSpace::Space = MSpace::kTransform,
											MStatus* ReturnStatus = NULL) const;
	virtual MStatus 	setRotateOrientation(const MQuaternion &q,
											MSpace::Space = MSpace::kTransform,
											bool balance = true);
	virtual MEulerRotation	eulerRotateOrientation(MSpace::Space = MSpace::kTransform,
											MStatus* ReturnStatus = NULL) const;
	virtual MStatus 	setRotateOrientation(const MEulerRotation &euler,
											MSpace::Space = MSpace::kTransform,
											bool balance = true);

	//
	//	Scale methods:
	//

	virtual MVector		scale(MSpace::Space = MSpace::kTransform,
								MStatus* ReturnStatus = NULL) const;
	virtual MStatus		scaleTo(const MVector &,
								MSpace::Space = MSpace::kTransform);
	virtual MStatus 	scaleBy(const MVector &,
								MSpace::Space = MSpace::kTransform);

	//	Shear methods:
	//
	virtual MVector	shear(MSpace::Space = MSpace::kTransform,
							MStatus* ReturnStatus = NULL) const;
	virtual MStatus	shearTo(const MVector& shear,
							MSpace::Space = MSpace::kTransform);
	virtual MStatus	shearBy(const MVector& shear,
							MSpace::Space = MSpace::kTransform);

	//	Scale pivot methods:
	//
	virtual MPoint	scalePivot(MSpace::Space = MSpace::kTransform,
								MStatus* ReturnStatus = NULL) const;
	virtual MStatus setScalePivot(const MPoint &,
									MSpace::Space = MSpace::kTransform,
									bool balance = true);
	virtual MVector	scalePivotTranslation(MSpace::Space = MSpace::kTransform,
										MStatus* ReturnStatus = NULL) const;
	virtual MStatus	setScalePivotTranslation(const MVector &vector,
										MSpace::Space = MSpace::kTransform);

	//	Rotate pivot methods:

	virtual MPoint	rotatePivot(MSpace::Space = MSpace::kTransform,
								MStatus* ReturnStatus = NULL) const;
	virtual MStatus setRotatePivot(const MPoint &,
									MSpace::Space = MSpace::kTransform,
									bool balance = true);
	virtual MVector	rotatePivotTranslation(MSpace::Space = MSpace::kTransform,
											MStatus* ReturnStatus = NULL) const;
	virtual MStatus	setRotatePivotTranslation(const MVector &vector,
										MSpace::Space = MSpace::kTransform);
	virtual	MStatus unSquishIt();
	virtual MMatrix unSquishMatrix() const;

	static MPxTransformationMatrix *creator();

	static MEulerRotation::RotationOrder
			convertTransformationRotationOrder(MTransformationMatrix::RotationOrder,
								 MStatus *ReturnStatus = NULL);
	static MTransformationMatrix::RotationOrder
					convertEulerRotationOrder(MEulerRotation::RotationOrder,
										 MStatus *ReturnStatus = NULL);

	//! The identity transformation matrix.
	static const  MPxTransformationMatrix identity;

	//! Type id for the default MPxTransformationMatrix.
	static MTypeId		baseTransformationMatrixId;

BEGIN_NO_SCRIPT_SUPPORT:
	OPENMAYA_DEPRECATED(<2016, "Use the MPxTransformationMatrix::convertTransformationRotationOrder() method instead.")
	static MEulerRotation::RotationOrder
			convertRotationOrder(MTransformationMatrix::RotationOrder,
								 MStatus *ReturnStatus = NULL);

	OPENMAYA_DEPRECATED(<2016, "Use the MPxTransformationMatrix::convertEulerRotationOrder() method instead.")
	static MTransformationMatrix::RotationOrder
					convertRotationOrder(MEulerRotation::RotationOrder,
										 MStatus *ReturnStatus = NULL);

	friend std::ostream &operator << (std::ostream &os, const MPxTransformationMatrix &m);

END_NO_SCRIPT_SUPPORT:

protected:
    virtual	MStatus		decomposeMatrix(const MMatrix &);

	//!	Scale component of transformation.
	MVector				scaleValue;

	//! Rotation component of transformation.
	MEulerRotation		rotationValue;

	//! Translation component of transformation.
	MVector				translationValue;

	//! Shear component of transformation.
	MVector				shearValue;

	//! Position of pivot used for scaling.
	MPoint 				scalePivotValue;

	//! Translation to compensate for movement of the scale pivot.
	MVector				scalePivotTranslationValue;

	//! Position of pivot used for rotation.
	MPoint				rotatePivotValue;

	//! Translation to compensate for movement of the rotate pivot.
	MVector 			rotatePivotTranslationValue;

	//! Orientation of the local rotation space.
	MQuaternion			rotateOrientationValue;

	static const char*	className();

OPENMAYA_PRIVATE:
    friend class        ::THxformMatrix;
    void*				instance;
};

// ****************************************************************************
// CLASS DECLARATION (MPxTransformationMatrixPreRotation)

//! \ingroup OpenMaya MPx
//! \brief Base class of all user defined transformation matrices with pre-rotation.
/*!
This is a temporary class that allows a user defined transformation matrix to supply
a pre-rotation (that will be applied between the rotation and translation) in order
to replicate jointOrient behaviour in a custom transform.

This functionality will be added directly to MPxTransformationMatrix in a future
release and this class will be removed at that point.
*/

class OPENMAYA_EXPORT MPxTransformationMatrixPreRotation : public MPxTransformationMatrix
{
public:
	MPxTransformationMatrixPreRotation();
	MPxTransformationMatrixPreRotation(const MTransformationMatrix &);
	MPxTransformationMatrixPreRotation(const MPxTransformationMatrixPreRotation &);
	MPxTransformationMatrixPreRotation(const MMatrix &);
	~MPxTransformationMatrixPreRotation() override;

	virtual MQuaternion	preRotation() const;
};

OPENMAYA_NAMESPACE_CLOSE

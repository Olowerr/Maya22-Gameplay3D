#pragma once

//-
// ===========================================================================
// Copyright 2017 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
//+
//
// CLASS:    MFn
//
// ***************************************************************************

#include <maya/MApiNamespace.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ***************************************************************************
// CLASS DECLARATION (MFn)


// ************************************************************************
// NOTE: New entries can be added anywhere in this file, they need not go
// at the end.
// ************************************************************************

// WARNING: Do not remove the //!< lines. They define which enum
// values will be documented in the customer API documentation.
// Ideally, it should be followed by a one line comment. \nop
// generates an empty comment

//! \ingroup MFn OpenMaya
//! \brief Function Set Type Identifiers
/*!
 MFn encapsulates all API Function Set type identifiers used for
 RTTI in the API.
*/
class FND_EXPORT MFn
{
public:
	MFn();

	//! Definition of all API types
	enum Type
	{
		kInvalid = 0,						//!< \nop
		kBase,								//!< \nop
		kNamedObject,						//!< \nop
		kModel,								//!< \nop
		kDependencyNode,					//!< \nop
		kAddDoubleLinear,					//!< \nop
		kAffect,							//!< \nop
		kAnimCurve,							//!< \nop
		kAnimCurveTimeToAngular,			//!< \nop
		kAnimCurveTimeToDistance,			//!< \nop
		kAnimCurveTimeToTime,				//!< \nop
		kAnimCurveTimeToUnitless,			//!< \nop
		kAnimCurveUnitlessToAngular,		//!< \nop
		kAnimCurveUnitlessToDistance,		//!< \nop
		kAnimCurveUnitlessToTime,			//!< \nop
		kAnimCurveUnitlessToUnitless,		//!< \nop
		kResultCurve,						//!< \nop
		kResultCurveTimeToAngular,			//!< \nop
		kResultCurveTimeToDistance,			//!< \nop
		kResultCurveTimeToTime,				//!< \nop
		kResultCurveTimeToUnitless,			//!< \nop
		kAngleBetween,						//!< \nop
		kAudio,								//!< \nop
		kBackground,						//!< \nop
		kColorBackground,					//!< \nop
		kFileBackground,					//!< \nop
		kRampBackground,					//!< \nop
		kBlend,								//!< \nop
		kBlendTwoAttr,						//!< \nop
		kBlendWeighted,						//!< \nop
		kBlendDevice,						//!< \nop
		kBlendColors,						//!< \nop
		kBump,								//!< \nop
		kBump3d,							//!< \nop
		kCameraView,						//!< \nop
		kChainToSpline,						//!< \nop
		kChoice,							//!< \nop
		kCondition,							//!< \nop
		kContrast,							//!< \nop
		kClampColor,						//!< \nop
		kCreate,							//!< \nop
		kAlignCurve,						//!< \nop
		kAlignSurface,						//!< \nop
		kAttachCurve,						//!< \nop
		kAttachSurface,						//!< \nop
		kAvgCurves,							//!< \nop
		kAvgSurfacePoints,					//!< \nop
		kAvgNurbsSurfacePoints,				//!< \nop
		kBevel,								//!< \nop
		kBirailSrf,							//!< \nop
		kDPbirailSrf,						//!< \nop
		kMPbirailSrf,						//!< \nop
		kSPbirailSrf,						//!< \nop
		kBoundary,							//!< \nop
		kCircle,							//!< \nop
		kCloseCurve,						//!< \nop
		kClosestPointOnSurface,				//!< \nop
		kCloseSurface,						//!< \nop
		kCurveFromSurface,					//!< \nop
		kCurveFromSurfaceBnd,				//!< \nop
		kCurveFromSurfaceCoS,				//!< \nop
		kCurveFromSurfaceIso,				//!< \nop
		kCurveInfo,							//!< \nop
		kDetachCurve,						//!< \nop
		kDetachSurface,						//!< \nop
		kExtendCurve,						//!< \nop
		kExtendSurface,						//!< \nop
		kExtrude,							//!< \nop
		kFFblendSrf,						//!< \nop
		kFFfilletSrf,						//!< \nop
		kFilletCurve,						//!< \nop
		kFitBspline,						//!< \nop
		kFlow,								//!< \nop
		kHardenPointCurve,					//!< \nop
		kIllustratorCurve,					//!< \nop
		kInsertKnotCrv,						//!< \nop
		kInsertKnotSrf,						//!< \nop
		kIntersectSurface,					//!< \nop
		kNurbsTesselate,					//!< \nop
		kNurbsPlane,						//!< \nop
		kNurbsCube,							//!< \nop
		kOffsetCos,							//!< \nop
		kOffsetCurve,						//!< \nop
		kPlanarTrimSrf,						//!< \nop
		kPointOnCurveInfo,					//!< \nop
		kPointOnSurfaceInfo,				//!< \nop
		kPrimitive,							//!< \nop
		kProjectCurve,						//!< \nop
		kProjectTangent,					//!< \nop
		kRBFsurface,						//!< \nop
		kRebuildCurve,						//!< \nop
		kRebuildSurface,					//!< \nop
		kReverseCurve,						//!< \nop
		kReverseSurface,					//!< \nop
		kRevolve,							//!< \nop
		kRevolvedPrimitive,					//!< \nop
		kCone,								//!< \nop
		kRenderCone,						//!< \nop
		kCylinder,							//!< \nop
		kSphere,							//!< \nop
		kSkin,								//!< \nop
		kStitchSrf,							//!< \nop
		kSubCurve,							//!< \nop
		kSurfaceInfo,						//!< \nop
		kTextCurves,						//!< \nop
		kTrim,								//!< \nop
		kUntrim,							//!< \nop
		kDagNode,							//!< \nop
		kProxy,								//!< \nop
		kUnderWorld,						//!< \nop
		kTransform,							//!< \nop
		kAimConstraint,						//!< \nop
		kLookAt,							//!< \nop
		kGeometryConstraint,				//!< \nop
		kGeometryVarGroup,					//!< \nop
		kAnyGeometryVarGroup,				//!< \nop
		kCurveVarGroup,						//!< \nop
		kMeshVarGroup,						//!< \nop
		kSurfaceVarGroup,					//!< \nop
		kIkEffector,						//!< \nop
		kIkHandle,							//!< \nop
		kJoint,								//!< \nop
		kManipulator3D,						//!< \nop
		kArrowManip,						//!< \nop
		kAxesActionManip,					//!< \nop
		kBallProjectionManip,				//!< \nop
		kCircleManip,						//!< \nop
		kScreenAlignedCircleManip,			//!< \nop
		kCircleSweepManip,					//!< \nop
		kConcentricProjectionManip,			//!< \nop
		kCubicProjectionManip,				//!< \nop
		kCylindricalProjectionManip,		//!< \nop
		kDiscManip,							//!< \nop
		kFreePointManip,					//!< \nop
		kCenterManip,						//!< \nop
		kLimitManip,						//!< \nop
		kEnableManip,						//!< \nop
		kFreePointTriadManip,				//!< \nop
		kPropMoveTriadManip,				//!< \nop
		kTowPointManip,						//!< \nop
		kPolyCreateToolManip,				//!< \nop
		kPolySplitToolManip,				//!< \nop
		kGeometryOnLineManip,				//!< \nop
		kCameraPlaneManip,					//!< \nop
		kToggleOnLineManip,					//!< \nop
		kStateManip,						//!< \nop
		kIsoparmManip,						//!< \nop
		kLineManip,							//!< \nop
		kManipContainer,					//!< \nop
		kAverageCurveManip,					//!< \nop
		kBarnDoorManip,						//!< \nop
		kBevelManip,						//!< \nop
		kBlendManip,						//!< \nop
		kButtonManip,						//!< \nop
		kCameraManip,						//!< \nop
		kCoiManip,							//!< \nop
		kCpManip,							//!< \nop
		kCreateCVManip,						//!< \nop
		kCreateEPManip,						//!< \nop
		kCurveEdManip,						//!< \nop
		kCurveSegmentManip,					//!< \nop
		kDirectionManip,					//!< \nop
		kDofManip,							//!< \nop
		kDropoffManip,						//!< \nop
		kExtendCurveDistanceManip,			//!< \nop
		kExtrudeManip,						//!< \nop
		kIkSplineManip,						//!< \nop
		kIkRPManip,							//!< \nop
		kJointClusterManip,					//!< \nop
		kLightManip,						//!< \nop
		kMotionPathManip,					//!< \nop
		kOffsetCosManip,					//!< \nop
		kOffsetCurveManip,					//!< \nop
		kProjectionManip,					//!< \nop
		kPolyProjectionManip,				//!< \nop
		kProjectionUVManip,					//!< \nop
		kProjectionMultiManip,				//!< \nop
		kProjectTangentManip,				//!< \nop
		kPropModManip,						//!< \nop
		kQuadPtOnLineManip,					//!< \nop
		kRbfSrfManip,						//!< \nop
		kReverseCurveManip,					//!< \nop
		kReverseCrvManip,					//!< \nop
		kReverseSurfaceManip,				//!< \nop
		kRevolveManip,						//!< \nop
		kRevolvedPrimitiveManip,			//!< \nop
		kSpotManip,							//!< \nop
		kSpotCylinderManip,					//!< \nop
		kTriplanarProjectionManip,			//!< \nop
		kTrsManip,							//!< \nop
		kDblTrsManip,						//!< \nop
		kPivotManip2D,						//!< \nop
		kManip2DContainer,					//!< \nop
		kPolyMoveUVManip,					//!< \nop
		kPolyMappingManip,					//!< \nop
		kPolyModifierManip,					//!< \nop
		kPolyMoveVertexManip,				//!< \nop
		kPolyVertexNormalManip,				//!< \nop
		kTexSmudgeUVManip,					//!< \nop
		kTexLatticeDeformManip,				//!< \nop
		kTexLattice,						//!< \nop
		kTexSmoothManip,					//!< \nop
		kTrsTransManip,						//!< \nop
		kTrsInsertManip,					//!< \nop
		kTrsXformManip,						//!< \nop
		kManipulator2D,						//!< \nop
		kTranslateManip2D,					//!< \nop
		kPlanarProjectionManip,				//!< \nop
		kPointOnCurveManip,					//!< \nop
		kTowPointOnCurveManip,				//!< \nop
		kMarkerManip,						//!< \nop
		kPointOnLineManip,					//!< \nop
		kPointOnSurfaceManip,				//!< \nop
		kTranslateUVManip,					//!< \nop
		kRotateBoxManip,					//!< \nop
		kRotateManip,						//!< \nop
		kHandleRotateManip,					//!< \nop
		kRotateLimitsManip,					//!< \nop
		kScaleLimitsManip,					//!< \nop
		kScaleManip,						//!< \nop
		kScalingBoxManip,					//!< \nop
		kScriptManip,						//!< \nop
		kSphericalProjectionManip,			//!< \nop
		kTextureManip3D,					//!< \nop
		kToggleManip,						//!< \nop
		kTranslateBoxManip,					//!< \nop
		kTranslateLimitsManip,				//!< \nop
		kTranslateManip,					//!< \nop
		kTrimManip,							//!< \nop
		kJointTranslateManip,				//!< \nop
		kManipulator,						//!< \nop
		kCirclePointManip,					//!< \nop
		kDimensionManip,					//!< \nop
		kFixedLineManip,					//!< \nop
		kLightProjectionGeometry,			//!< \nop
		kLineArrowManip,					//!< \nop
		kPointManip,						//!< \nop
		kTriadManip,						//!< \nop
		kNormalConstraint,					//!< \nop
		kOrientConstraint,					//!< \nop
		kPointConstraint,					//!< \nop
		kSymmetryConstraint,				//!< \nop
		kParentConstraint,					//!< \nop
		kPoleVectorConstraint,				//!< \nop
		kScaleConstraint,					//!< \nop
		kTangentConstraint,					//!< \nop
		kUnknownTransform,					//!< \nop
		kWorld,								//!< \nop
		kShape,								//!< \nop
		kBaseLattice,						//!< \nop
		kCamera,							//!< \nop
		kCluster,							//!< \nop
		kSoftMod,							//!< \nop
		kCollision,							//!< \nop
		kDummy,								//!< \nop
		kEmitter,							//!< \nop
		kField,								//!< \nop
		kAir,								//!< \nop
		kDrag,								//!< \nop
		kGravity,							//!< \nop
		kNewton,							//!< \nop
		kRadial,							//!< \nop
		kTurbulence,						//!< \nop
		kUniform,							//!< \nop
		kVortex,							//!< \nop
		kGeometric,							//!< \nop
		kCurve,								//!< \nop
		kNurbsCurve,						//!< \nop
		kNurbsCurveGeom,					//!< \nop
		kDimension,							//!< \nop
		kAngle,								//!< \nop
		kAnnotation,						//!< \nop
		kDistance,							//!< \nop
		kArcLength,							//!< \nop
		kRadius,							//!< \nop
		kParamDimension,					//!< \nop
		kDirectedDisc,						//!< \nop
		kRenderRect,						//!< \nop
		kEnvFogShape,						//!< \nop
		kLattice,							//!< \nop
		kLatticeGeom,						//!< \nop
		kLocator,							//!< \nop
		kDropoffLocator,					//!< \nop
		kMarker,							//!< \nop
		kOrientationMarker,					//!< \nop
		kPositionMarker,					//!< \nop
		kOrientationLocator,				//!< \nop
		kTrimLocator,						//!< \nop
		kPlane,								//!< \nop
		kSketchPlane,						//!< \nop
		kGroundPlane,						//!< \nop
		kOrthoGrid,							//!< \nop
		kSprite,							//!< \nop
		kSurface,							//!< \nop
		kNurbsSurface,						//!< \nop
		kNurbsSurfaceGeom,					//!< \nop
		kMesh,								//!< \nop
		kMeshGeom,							//!< \nop
		kRenderSphere,						//!< \nop
		kFlexor,							//!< \nop
		kClusterFlexor,						//!< \nop
		kGuideLine,							//!< \nop
		kLight,								//!< \nop
		kAmbientLight,						//!< \nop
		kNonAmbientLight,					//!< \nop
		kAreaLight,							//!< \nop
		kLinearLight,						//!< \nop
		kNonExtendedLight,					//!< \nop
		kDirectionalLight,					//!< \nop
		kPointLight,						//!< \nop
		kSpotLight,							//!< \nop
		kParticle,							//!< \nop
		kPolyToolFeedbackShape,				//!< \nop
		kRigidConstraint,					//!< \nop
		kRigid,								//!< \nop
		kSpring,							//!< \nop
		kUnknownDag,						//!< \nop
		kDefaultLightList,					//!< \nop
		kDeleteComponent,					//!< \nop
		kDispatchCompute,					//!< \nop
		kShadingEngine,						//!< \nop
		kDisplacementShader,				//!< \nop
		kDistanceBetween,					//!< \nop
		kDOF,								//!< \nop
		kDummyConnectable,					//!< \nop
		kDynamicsController,				//!< \nop
		kGeoConnectable,					//!< \nop
		kExpression,						//!< \nop
		kExtract,							//!< \nop
		kFilter,							//!< \nop
		kFilterClosestSample,				//!< \nop
		kFilterEuler,						//!< \nop
		kFilterSimplify,					//!< \nop
		kGammaCorrect,						//!< \nop
		kGeometryFilt,						//!< \nop
		kBendLattice,						//!< \nop
		kBlendShape,						//!< \nop
		kCombinationShape,					//!< \nop
		kBulgeLattice,						//!< \nop
		kFFD,								//!< \nop
		kFfdDualBase,						//!< \nop
		kRigidDeform,						//!< \nop
		kSculpt,							//!< \nop
		kTextureDeformer,					//!< \nop
		kTextureDeformerHandle,				//!< \nop
		kTweak,								//!< \nop
		kWeightGeometryFilt,				//!< \nop
		kClusterFilter,						//!< \nop
		kSoftModFilter,						//!< \nop
		kJointCluster,						//!< \nop
        kDeltaMush,					     	//!< \nop
        kTension,                           //!< \nop
        kMorph,                             //!< \nop
        kSolidify,                          //!< \nop
        kProximityWrap,	                    //!< \nop
        kWire,							    //!< \nop
        kGroupId,						    //!< \nop
		kGroupParts,						//!< \nop
        kGuide,							    //!< \nop
		kHsvToRgb,							//!< \nop
		kHyperGraphInfo,					//!< \nop
		kHyperLayout,						//!< \nop
		kHyperView,							//!< \nop
		kIkSolver,							//!< \nop
		kMCsolver,							//!< \nop
		kPASolver,							//!< \nop
		kSCsolver,							//!< \nop
		kRPsolver,							//!< \nop
		kSplineSolver,						//!< \nop
		kIkSystem,							//!< \nop
		kImagePlane,						//!< \nop
		kLambert,							//!< \nop
		kReflect,							//!< \nop
		kBlinn,								//!< \nop
		kPhong,								//!< \nop
		kPhongExplorer,						//!< \nop
		kLayeredShader,						//!< \nop
		kStandardSurface,					//!< \nop
		kLightInfo,							//!< \nop
		kLeastSquares,						//!< \nop
		kLightFogMaterial,					//!< \nop
		kEnvFogMaterial,					//!< \nop
		kLightList,							//!< \nop
		kLightSource,						//!< \nop
		kLuminance,							//!< \nop
		kMakeGroup,							//!< \nop
		kMaterial,							//!< \nop
		kDiffuseMaterial,					//!< \nop
		kLambertMaterial,					//!< \nop
		kBlinnMaterial,						//!< \nop
		kPhongMaterial,						//!< \nop
		kLightSourceMaterial,				//!< \nop
		kMaterialInfo,						//!< \nop
		kMaterialTemplate,					//!< \nop
		kMatrixAdd,							//!< \nop
		kMatrixHold,						//!< \nop
		kMatrixMult,						//!< \nop
		kMatrixPass,						//!< \nop
		kMatrixWtAdd,						//!< \nop
		kMidModifier,						//!< \nop
		kMidModifierWithMatrix,				//!< \nop
		kPolyBevel,							//!< \nop
		kPolyTweak,							//!< \nop
		kPolyAppend,						//!< \nop
		kPolyChipOff,						//!< \nop
		kPolyCloseBorder,					//!< \nop
		kPolyCollapseEdge,					//!< \nop
		kPolyCollapseF,						//!< \nop
		kPolyCylProj,						//!< \nop
		kPolyDelEdge,						//!< \nop
		kPolyDelFacet,						//!< \nop
		kPolyDelVertex,						//!< \nop
		kPolyExtrudeFacet,					//!< \nop
		kPolyMapCut,						//!< \nop
		kPolyMapDel,						//!< \nop
		kPolyMapSew,						//!< \nop
		kPolyMergeEdge,						//!< \nop
		kPolyMergeFacet,					//!< \nop
		kPolyMoveEdge,						//!< \nop
		kPolyMoveFacet,						//!< \nop
		kPolyMoveFacetUV,					//!< \nop
		kPolyMoveUV,						//!< \nop
		kPolyMoveVertex,					//!< \nop
		kPolyMoveVertexUV,					//!< \nop
		kPolyNormal,						//!< \nop
		kPolyPlanProj,						//!< \nop
		kPolyProj,							//!< \nop
		kPolyQuad,							//!< \nop
		kPolySmooth,						//!< \nop
		kPolySoftEdge,						//!< \nop
		kPolySphProj,						//!< \nop
		kPolySplit,							//!< \nop
		kPolySubdEdge,						//!< \nop
		kPolySubdFacet,						//!< \nop
		kPolyTriangulate,					//!< \nop
		kPolyCreator,						//!< \nop
		kPolyPrimitive,						//!< \nop
		kPolyCone,							//!< \nop
		kPolyCube,							//!< \nop
		kPolyCylinder,						//!< \nop
		kPolyMesh,							//!< \nop
		kPolySphere,						//!< \nop
		kPolyTorus,							//!< \nop
		kPolyCreateFacet,					//!< \nop
		kPolyUnite,							//!< \nop
		kMotionPath,						//!< \nop
		kPluginMotionPathNode,				//!< Custom motionPath nodes derived from MPxMotionPathNode
		kMultilisterLight,					//!< \nop
		kMultiplyDivide,					//!< \nop
		kOldGeometryConstraint,				//!< \nop
		kOpticalFX,							//!< \nop
		kParticleAgeMapper,					//!< \nop
		kParticleCloud,						//!< \nop
		kParticleColorMapper,				//!< \nop
		kParticleIncandecenceMapper,		//!< \nop
		kParticleTransparencyMapper,		//!< \nop
		kPartition,							//!< \nop
		kPlace2dTexture,					//!< \nop
		kPlace3dTexture,					//!< \nop
		kPluginDependNode,					//!< Custom dependency nodes derived from MPxNode
		kPluginLocatorNode,					//!< Custom locator node derived from MPxLocatorNode
		kPlusMinusAverage,					//!< \nop
		kPointMatrixMult,					//!< \nop
		kPolySeparate,						//!< \nop
		kPostProcessList,					//!< \nop
		kProjection,						//!< \nop
		kRecord,							//!< \nop
		kRenderUtilityList,					//!< \nop
		kReverse,							//!< \nop
		kRgbToHsv,							//!< \nop
		kRigidSolver,						//!< \nop
		kSet,								//!< \nop
		kTextureBakeSet,					//!< \nop
		kVertexBakeSet,						//!< \nop
		kSetRange,							//!< \nop
		kShaderGlow,						//!< \nop
		kShaderList,						//!< \nop
		kShadingMap,						//!< \nop
		kSamplerInfo,						//!< \nop
		kShapeFragment,						//!< \nop
		kSimpleVolumeShader,				//!< \nop
		kSl60,								//!< \nop
		kSnapshot,							//!< \nop
		kStoryBoard,						//!< \nop
		kSummaryObject,						//!< \nop
		kSuper,								//!< \nop
		kControl,							//!< \nop
		kSurfaceLuminance,					//!< \nop
		kSurfaceShader,						//!< \nop
		kTextureList,						//!< \nop
		kTextureEnv,						//!< \nop
		kEnvBall,							//!< \nop
		kEnvCube,							//!< \nop
		kEnvChrome,							//!< \nop
		kEnvSky,							//!< \nop
		kEnvSphere,							//!< \nop
		kTexture2d,							//!< \nop
		kBulge,								//!< \nop
		kChecker,							//!< \nop
		kCloth,								//!< \nop
		kFileTexture,						//!< \nop
		kFractal,							//!< \nop
		kGrid,								//!< \nop
		kMountain,							//!< \nop
		kRamp,								//!< \nop
		kStencil,							//!< \nop
		kWater,								//!< \nop
		kTexture3d,							//!< \nop
		kBrownian,							//!< \nop
		kCloud,								//!< \nop
		kCrater,							//!< \nop
		kGranite,							//!< \nop
		kLeather,							//!< \nop
		kMarble,							//!< \nop
		kRock,								//!< \nop
		kSnow,								//!< \nop
		kSolidFractal,						//!< \nop
		kStucco,							//!< \nop
		kTxSl,								//!< \nop
		kWood,								//!< \nop
		kTime,								//!< \nop
		kTimeToUnitConversion,				//!< \nop
		kRenderSetup,						//!< \nop
		kRenderGlobals,						//!< \nop
		kRenderGlobalsList,					//!< \nop
		kRenderQuality,						//!< \nop
		kResolution,						//!< \nop
		kHardwareRenderGlobals,				//!< \nop
		kArrayMapper,						//!< \nop
		kUnitConversion,					//!< \nop
		kUnitToTimeConversion,				//!< \nop
		kUseBackground,						//!< \nop
		kUnknown,							//!< \nop
		kVectorProduct,						//!< \nop
		kVolumeShader,						//!< \nop
		kComponent,							//!< \nop
		kCurveCVComponent,					//!< \nop
		kCurveEPComponent,					//!< \nop
		kCurveKnotComponent,				//!< \nop
		kCurveParamComponent,				//!< \nop
		kIsoparmComponent,					//!< \nop
		kPivotComponent,					//!< \nop
		kSurfaceCVComponent,				//!< \nop
		kSurfaceEPComponent,				//!< \nop
		kSurfaceKnotComponent,				//!< \nop
		kEdgeComponent,						//!< \nop
		kLatticeComponent,					//!< \nop
		kSurfaceRangeComponent,				//!< \nop
		kDecayRegionCapComponent,			//!< \nop
		kDecayRegionComponent,				//!< \nop
		kMeshComponent,						//!< \nop
		kMeshEdgeComponent,					//!< \nop
		kMeshPolygonComponent,				//!< \nop
		kMeshFrEdgeComponent,				//!< \nop
		kMeshVertComponent,					//!< \nop
		kMeshFaceVertComponent,				//!< \nop
		kOrientationComponent,				//!< \nop
		kSubVertexComponent,				//!< \nop
		kMultiSubVertexComponent,			//!< \nop
		kSetGroupComponent,					//!< \nop
		kDynParticleSetComponent,			//!< \nop
		kSelectionItem,						//!< \nop
		kDagSelectionItem,					//!< \nop
		kNonDagSelectionItem,				//!< \nop
		kItemList,							//!< \nop
		kAttribute,							//!< \nop
		kNumericAttribute,					//!< \nop
		kDoubleAngleAttribute,				//!< \nop
		kFloatAngleAttribute,				//!< \nop
		kDoubleLinearAttribute,				//!< \nop
		kFloatLinearAttribute,				//!< \nop
		kTimeAttribute,						//!< \nop
		kEnumAttribute,						//!< \nop
		kUnitAttribute,						//!< \nop
		kTypedAttribute,					//!< \nop
		kCompoundAttribute,					//!< \nop
		kGenericAttribute,					//!< \nop
		kLightDataAttribute,				//!< \nop
		kMatrixAttribute,					//!< \nop
		kFloatMatrixAttribute,				//!< \nop
		kMessageAttribute,					//!< \nop
		kPlugin,							//!< Custom Plug-in
		kData,								//!< \nop
		kComponentListData,					//!< \nop
		kDoubleArrayData,					//!< \nop
		kIntArrayData,						//!< \nop
		kUintArrayData,						//!< \nop
		kLatticeData,						//!< \nop
		kMatrixData,						//!< \nop
		kMeshData,							//!< \nop
		kNurbsSurfaceData,					//!< \nop
		kNurbsCurveData,					//!< \nop
		kNumericData,						//!< \nop
		kData2Double,						//!< \nop
		kData2Float,						//!< \nop
		kData2Int,							//!< \nop
		kData2Short,						//!< \nop
		kData3Double,						//!< \nop
		kData3Float,						//!< \nop
		kData3Int,							//!< \nop
		kData3Short,						//!< \nop
		kPluginData,						//!< Custom data types derived from MPxData
		kPointArrayData,					//!< \nop
		kMatrixArrayData,					//!< \nop
		kSphereData,						//!< \nop
		kStringData,						//!< \nop
		kStringArrayData,					//!< \nop
		kVectorArrayData,					//!< \nop
		kSelectionList,						//!< \nop
		kTransformGeometry,					//!< \nop
		kCommEdgePtManip,					//!< \nop
		kCommEdgeOperManip,					//!< \nop
		kCommEdgeSegmentManip,				//!< \nop
		kCommCornerManip,					//!< \nop
		kCommCornerOperManip,				//!< \nop
		kPluginDeformerNode,				//!< Custom deformer node derived from MPxDeformerNode
		kTorus,								//!< \nop
		kPolyBoolOp,						//!< \nop
		kSingleShadingSwitch,				//!< \nop
		kDoubleShadingSwitch,				//!< \nop
		kTripleShadingSwitch,				//!< \nop
		kNurbsSquare,						//!< \nop
		kAnisotropy,						//!< \nop
		kNonLinear,							//!< \nop
		kDeformFunc,						//!< \nop
		kDeformBend,						//!< \nop
		kDeformTwist,						//!< \nop
		kDeformSquash,						//!< \nop
		kDeformFlare,						//!< \nop
		kDeformSine,						//!< \nop
		kDeformWave,						//!< \nop
		kDeformBendManip,					//!< \nop
		kDeformTwistManip,					//!< \nop
		kDeformSquashManip,					//!< \nop
		kDeformFlareManip,					//!< \nop
		kDeformSineManip,					//!< \nop
		kDeformWaveManip,					//!< \nop
		kSoftModManip,						//!< \nop
		kDistanceManip,						//!< \nop
		kScript,							//!< \nop
		kCurveFromMeshEdge,					//!< \nop
		kCurveCurveIntersect,				//!< \nop
		kNurbsCircular3PtArc,				//!< \nop
		kNurbsCircular2PtArc,				//!< \nop
		kOffsetSurface,						//!< \nop
		kRoundConstantRadius,				//!< \nop
		kRoundRadiusManip,					//!< \nop
		kRoundRadiusCrvManip,				//!< \nop
		kRoundConstantRadiusManip,			//!< \nop
		kThreePointArcManip,				//!< \nop
		kTwoPointArcManip,					//!< \nop
		kTextButtonManip,					//!< \nop
		kOffsetSurfaceManip,				//!< \nop
		kImageData,							//!< \nop
		kImageLoad,							//!< \nop
		kImageSave,							//!< \nop
		kImageNetSrc,						//!< \nop
		kImageNetDest,						//!< \nop
		kImageRender,						//!< \nop
		kImageAdd,							//!< \nop
		kImageDiff,							//!< \nop
		kImageMultiply,						//!< \nop
		kImageOver,							//!< \nop
		kImageUnder,						//!< \nop
		kImageColorCorrect,					//!< \nop
		kImageBlur,							//!< \nop
		kImageFilter,						//!< \nop
		kImageDepth,						//!< \nop
		kImageDisplay,						//!< \nop
		kImageView,							//!< \nop
		kImageMotionBlur,					//!< \nop
        kViewColorManager,                  //!< \nop
		kMatrixFloatData,					//!< \nop
		kSkinShader,						//!< \nop
		kComponentManip,					//!< \nop
		kSelectionListData,					//!< \nop
		kObjectFilter,						//!< \nop
		kObjectMultiFilter,					//!< \nop
		kObjectNameFilter,					//!< \nop
		kObjectTypeFilter,					//!< \nop
		kObjectAttrFilter,					//!< \nop
		kObjectRenderFilter,				//!< \nop
		kObjectScriptFilter,				//!< \nop
		kSelectionListOperator,				//!< \nop
		kSubdiv,							//!< \nop
		kPolyToSubdiv,						//!< \nop
		kSkinClusterFilter,					//!< \nop
		kKeyingGroup,
		kCharacter,							//!< \nop
		kCharacterOffset,					//!< \nop
		kDagPose,							//!< \nop
		kStitchAsNurbsShell,				//!< \nop
        kExplodeNurbsShell,					//!< \nop
        kNurbsBoolean,						//!< \nop
        kStitchSrfManip,					//!< \nop
		kForceUpdateManip,					//!< \nop
        kPluginManipContainer,				//!< Custom manipulator containers derived from MPxManipContainer
		kPolySewEdge,						//!< \nop
		kPolyMergeVert,						//!< \nop
		kPolySmoothFacet,					//!< \nop
		kSmoothCurve,						//!< \nop
		kGlobalStitch,						//!< \nop
		kSubdivCVComponent,					//!< \nop
		kSubdivEdgeComponent,				//!< \nop
		kSubdivFaceComponent,				//!< \nop
		kUVManip2D,							//!< \nop
		kTranslateUVManip2D,				//!< \nop
		kRotateUVManip2D,					//!< \nop
		kScaleUVManip2D,					//!< \nop
		kPolyTweakUV,						//!< \nop
		kMoveUVShellManip2D,				//!< \nop
		kPluginShape,						//!< Custom shapes (dependency nodes) derived from MPxSurfaceShape
		kGeometryData,						//!< \nop
		kSingleIndexedComponent,			//!< \nop
		kDoubleIndexedComponent,			//!< \nop
		kTripleIndexedComponent,			//!< \nop
        kExtendSurfaceDistanceManip,		//!< \nop
		kSquareSrf,							//!< \nop
		kSquareSrfManip,					//!< \nop
		kSubdivToPoly,						//!< \nop
        kDynBase,							//!< \nop
        kDynEmitterManip,					//!< \nop
        kDynFieldsManip,					//!< \nop
        kDynBaseFieldManip,					//!< \nop
        kDynAirManip,						//!< \nop
        kDynNewtonManip,					//!< \nop
        kDynTurbulenceManip,				//!< \nop
        kDynSpreadManip,					//!< \nop
        kDynAttenuationManip,				//!< \nop
        kDynArrayAttrsData,					//!< \nop
        kPluginFieldNode,					//!< Custom dependency graph node representing a field derived from MPxFieldNode
        kPluginEmitterNode,					//!< Custom dependency graph node representing an emitter derived from MPxEmitterNode
        kPluginSpringNode,					//!< Custom dependency graph node representing a spring derived from MPxSpringNode
		kDisplayLayer,						//!< \nop
		kDisplayLayerManager,				//!< \nop
        kPolyColorPerVertex,				//!< \nop
		kCreateColorSet,					//!< \nop
		kDeleteColorSet,					//!< \nop
		kCopyColorSet,						//!< \nop
		kBlendColorSet,						//!< \nop
		kPolyColorMod,						//!< \nop
		kPolyColorDel,						//!< \nop
		kCharacterMappingData,				//!< \nop
		kDynSweptGeometryData,				//!< \nop
		kWrapFilter,						//!< \nop
		kMeshVtxFaceComponent,				//!< \nop
		kBinaryData,						//!< \nop
		kAttribute2Double,					//!< \nop
		kAttribute2Float,					//!< \nop
		kAttribute2Short,					//!< \nop
		kAttribute2Int,						//!< \nop
		kAttribute3Double,					//!< \nop
		kAttribute3Float,					//!< \nop
		kAttribute3Short,					//!< \nop
		kAttribute3Int,						//!< \nop
		kReference,							//!< \nop
		kBlindData,							//!< \nop
		kBlindDataTemplate,					//!< \nop
		kPolyBlindData,						//!< \nop
		kPolyNormalPerVertex,				//!< \nop
		kNurbsToSubdiv,						//!< \nop
		kPluginIkSolver,					//!< Custom IK Solvers derived from MPxIkSolverNode
		kInstancer,							//!< \nop
		kMoveVertexManip,					//!< \nop
		kStroke,							//!< \nop
		kBrush,								//!< \nop
		kStrokeGlobals,						//!< \nop
		kPluginGeometryData,				//!< Custom container for arbitrary Geometry type derived from MPxGeometryData
		kLightLink,							//!< \nop
		kDynGlobals,						//!< \nop
		kPolyReduce,						//!< \nop
		kLodThresholds,						//!< \nop
		kChooser,							//!< \nop
		kLodGroup,							//!< \nop
		kMultDoubleLinear,					//!< \nop
		kFourByFourMatrix,					//!< \nop
		kTowPointOnSurfaceManip,			//!< \nop
		kSurfaceEdManip,					//!< \nop
		kSurfaceFaceComponent,				//!< \nop
		kClipScheduler,						//!< \nop
		kClipLibrary,						//!< \nop
		kSubSurface,						//!< \nop
		kSmoothTangentSrf,					//!< \nop
		kRenderPass,						//!< \nop
		kRenderPassSet,						//!< \nop
		kRenderLayer,						//!< \nop
		kRenderLayerManager,				//!< \nop
		kPassContributionMap,				//!< \nop
		kPrecompExport,                     //!< \nop
		kRenderTarget,						//!< \nop
        kRenderedImageSource,               //!< \nop
        kImageSource,                       //!< \nop
		kPolyFlipEdge,						//!< \nop
		kPolyExtrudeEdge,					//!< \nop
		kAnimBlend,							//!< \nop
		kAnimBlendInOut,					//!< \nop
		kPolyAppendVertex,					//!< \nop
		kUvChooser,							//!< \nop
		kSubdivCompId,						//!< \nop
		kVolumeAxis,						//!< \nop
		kDeleteUVSet,						//!< \nop
		kSubdHierBlind,						//!< \nop
		kSubdBlindData,						//!< \nop
		kCharacterMap,						//!< \nop
		kLayeredTexture,					//!< \nop
		kSubdivCollapse,					//!< \nop
		kParticleSamplerInfo,				//!< \nop
		kCopyUVSet,							//!< \nop
		kCreateUVSet,						//!< \nop
		kClip,								//!< \nop
		kPolySplitVert,						//!< \nop
		kSubdivData,						//!< \nop
		kSubdivGeom,						//!< \nop
		kUInt64ArrayData,					//!< \nop
		kInt64ArrayData,					//!< \nop
		kPolySplitEdge,						//!< \nop
		kSubdivReverseFaces,				//!< \nop
		kMeshMapComponent,					//!< \nop
		kSectionManip,						//!< \nop
		kXsectionSubdivEdit,				//!< \nop
		kSubdivToNurbs,						//!< \nop
		kEditCurve,							//!< \nop
		kEditCurveManip,					//!< \nop
		kCrossSectionManager,				//!< \nop
		kCreateSectionManip,				//!< \nop
		kCrossSectionEditManip,				//!< \nop
		kDropOffFunction,					//!< \nop
		kSubdBoolean,						//!< \nop
		kSubdModifyEdge,					//!< \nop
		kModifyEdgeCrvManip,				//!< \nop
		kModifyEdgeManip,					//!< \nop
		kScalePointManip,					//!< \nop
		kTransformBoxManip,					//!< \nop
		kSymmetryLocator,					//!< \nop
		kSymmetryMapVector,					//!< \nop
		kSymmetryMapCurve,					//!< \nop
		kCurveFromSubdivEdge,				//!< \nop
		kCreateBPManip,						//!< \nop
		kModifyEdgeBaseManip,				//!< \nop
		kSubdExtrudeFace,					//!< \nop
		kSubdivSurfaceVarGroup,				//!< \nop
		kSfRevolveManip,					//!< \nop
		kCurveFromSubdivFace,				//!< \nop

		//
		// The next six entries are unused
		kUnused1,							//!< \nop
		kUnused2,							//!< \nop
		kUnused3,							//!< \nop
		kUnused4,							//!< \nop
		kUnused5,							//!< \nop
		kUnused6,							//!< \nop

		//
		// The next five entries are for the polyUVplus plugin
		kPolyTransfer,						//!< \nop
		kPolyAverageVertex,					//!< \nop
		kPolyAutoProj,						//!< \nop
		kPolyLayoutUV,						//!< \nop
		kPolyMapSewMove,					//!< \nop
		kSubdModifier,						//!< \nop
		kSubdMoveVertex,					//!< \nop
		kSubdMoveEdge,						//!< \nop
		kSubdMoveFace,						//!< \nop
		kSubdDelFace,						//!< \nop
		kSnapshotShape,						//!< \nop
		kSubdivMapComponent,				//!< \nop
		kJiggleDeformer,					//!< \nop
		kGlobalCacheControls,				//!< \nop
		kDiskCache,							//!< \nop
		kSubdCloseBorder,					//!< \nop
		kSubdMergeVert,						//!< \nop
		kBoxData,							//!< \nop
		kBox,								//!< \nop
		kRenderBox,							//!< \nop
		kSubdSplitFace,						//!< \nop
		kVolumeFog,							//!< \nop
		kSubdTweakUV,						//!< \nop
		kSubdMapCut,						//!< \nop
		kSubdLayoutUV,						//!< \nop
		kSubdMapSewMove,					//!< \nop
		kOcean,								//!< \nop
		kVolumeNoise,						//!< \nop
		kSubdAutoProj,						//!< \nop
		kSubdSubdivideFace,					//!< \nop
		kNoise,								//!< \nop
		kAttribute4Double,					//!< \nop
		kData4Double,						//!< \nop
		kSubdPlanProj,						//!< \nop
		kSubdTweak,							//!< \nop
		kSubdProjectionManip,				//!< \nop
		kSubdMappingManip,					//!< \nop
		kHardwareReflectionMap,				//!< \nop
		kPolyNormalizeUV,					//!< \nop
		kPolyFlipUV,						//!< \nop
		kHwShaderNode,						//!< \nop
		kPluginHardwareShader,				//!< Custom hardware shader derived from MPxHardwareShader
		kPluginHwShaderNode,				//!< Custom hardware shader derived from MPxHwShaderNode (old implementation)
		kSubdAddTopology,					//!< \nop
		kSubdCleanTopology,					//!< \nop
		kImplicitCone,						//!< \nop
		kImplicitSphere,					//!< \nop
		kRampShader,						//!< \nop
		kVolumeLight,						//!< \nop
		kOceanShader,						//!< \nop
		kBevelPlus,							//!< \nop
		kStyleCurve,						//!< \nop
		kPolyCut,							//!< \nop
		kPolyPoke,							//!< \nop
		kPolyWedgeFace,						//!< \nop
		kPolyCutManipContainer,				//!< \nop
		kPolyCutManip,						//!< \nop
		kPolyMirrorManipContainer,			//!< \nop
		kPolyPokeManip,						//!< \nop
		kFluidTexture3D,					//!< \nop
		kFluidTexture2D,					//!< \nop
		kPolyMergeUV,						//!< \nop
		kPolyStraightenUVBorder,			//!< \nop
		kAlignManip,						//!< \nop
		kPluginTransformNode,				//!< Custom transform node derived from MPxTransform
		kFluid,								//!< \nop
		kFluidGeom,							//!< \nop
		kFluidData,							//!< \nop

		//
		// The next three entries are for the studioImport plugin
		kSmear,								//!< \nop
		kStringShadingSwitch,				//!< \nop
		kStudioClearCoat,					//!< \nop

		kFluidEmitter,						//!< \nop
		kHeightField,						//!< \nop
		kGeoConnector,						//!< \nop
		kSnapshotPath,						//!< \nop
		kPluginObjectSet,					//!< Custom sets (dependency nodes) derived from MPxObjectSet
		kQuadShadingSwitch,					//!< \nop
		kPolyExtrudeVertex,					//!< \nop
		kPairBlend,							//!< \nop
		kTextManip,							//!< \nop
		kViewManip,							//!< \nop
		kXformManip,						//!< \nop
		kMute,								//!< \nop
		kConstraint,						//!< \nop
		kTrimWithBoundaries,				//!< \nop
		kCurveFromMeshCoM,					//!< \nop
		kFollicle,							//!< \nop
		kHairSystem,						//!< \nop
		kRemapValue,						//!< \nop
		kRemapColor,						//!< \nop
		kRemapHsv,							//!< \nop
		kHairConstraint,					//!< \nop
		kTimeFunction,						//!< \nop
		kMentalRayTexture,					//!< \nop
		kObjectBinFilter,					//!< \nop
		kPolySmoothProxy,					//!< \nop
		kPfxGeometry,						//!< \nop
		kPfxHair,							//!< \nop
		kHairTubeShader,					//!< \nop
		kPsdFileTexture,					//!< \nop
		kKeyframeDelta,						//!< \nop
		kKeyframeDeltaMove,					//!< \nop
		kKeyframeDeltaScale,				//!< \deprecated Not used. Maya instead uses kKeyframeDeltaMove and kKeyframe events.
		kKeyframeDeltaAddRemove,			//!< \nop
		kKeyframeDeltaBlockAddRemove,		//!< \nop
		kKeyframeDeltaInfType,				//!< \nop
		kKeyframeDeltaTangent,				//!< \nop
		kKeyframeDeltaWeighted,				//!< \nop
		kKeyframeDeltaBreakdown,			//!< \nop

		kPolyMirror,						//!< \nop
		kPolyCreaseEdge,					//!< \nop
		kPolyPinUV,							//!< \nop
		kHikEffector,						//!< \nop
		kHikIKEffector,						//!< \nop
		kHikFKJoint,						//!< \nop
		kHikSolver,							//!< \nop
		kHikHandle,							//!< \nop
		kProxyManager,						//!< \nop
		kPolyAutoProjManip,					//!< \nop
		kPolyPrism,							//!< \nop
		kPolyPyramid,						//!< \nop
		kPolySplitRing,						//!< \nop
		kPfxToon,							//!< \nop
		kToonLineAttributes,				//!< \nop
		kPolyDuplicateEdge,					//!< \nop

		//
		// Facade types
		kFacade,							//!< \nop
		kMaterialFacade,					//!< \nop
		kEnvFacade,							//!< \nop
		kAISEnvFacade,						//!< \nop
		kLineModifier,						//!< \nop
		kPolyArrow,							//!< \nop
		kPolyPrimitiveMisc,					//!< \nop
		kPolyPlatonicSolid,					//!< \nop
		kPolyPipe,							//!< \nop

		kHikFloorContactMarker,				//!< \nop

		kHikGroundPlane,					//!< \nop
		kPolyComponentData,					//!< \nop
		kPolyHelix,							//!< \nop
		kCacheFile,							//!< \nop
		kHistorySwitch,						//!< \nop
		kClosestPointOnMesh,				//!< \nop
        kUVPin,				    //!< Not fully implemented; Do not use
        kProximityPin,				    //!< Not fully implemented; Do not use
        kTransferAttributes,				//!< \nop
		kDynamicConstraint,					//!< \nop
		kNComponent,						//!< \nop
		kPolyBridgeEdge,					//!< \nop
		kCacheableNode,						//!< \nop
		kNucleus,							//!< \nop
		kNBase,								//!< \nop
		kCacheBase,							//!< \nop
		kCacheBlend,						//!< \nop
		kCacheTrack,						//!< \nop
		kKeyframeRegionManip,				//!< \nop
		kCurveNormalizerAngle,				//!< \nop
		kCurveNormalizerLinear,				//!< \nop
		kHyperLayoutDG,						//!< \nop
		kPluginImagePlaneNode,				//!< Custom Image Plane classes derived from MPxImagePlane
		kNCloth,							//!< \nop
		kNParticle,							//!< \nop
		kNRigid,							//!< \nop
		kPluginParticleAttributeMapperNode,	//!< \nop
		kCameraSet,							//!< \nop
		kPluginCameraSet,  					//!< Custom cameraSet nodes (dependency nodes) derived from MPxCameraSet
		kContainer,							//!< \nop
		kFloatVectorArrayData,				//!< \nop
		kNObjectData,						//!< \nop
		kNObject,							//!< \nop
		kPluginConstraintNode,				//!< Custom constraint node derived from MPxConstraint
		kAsset,								//!< \nop
		kPolyEdgeToCurve,					//!< \nop
		kAnimLayer,							//!< \nop
		kBlendNodeBase,						//!< \nop
		kBlendNodeBoolean,					//!< \nop
		kBlendNodeDouble,					//!< \nop
		kBlendNodeDoubleAngle,				//!< \nop
		kBlendNodeDoubleLinear,				//!< \nop
		kBlendNodeEnum,						//!< \nop
		kBlendNodeFloat,					//!< \nop
		kBlendNodeFloatAngle,				//!< \nop
		kBlendNodeFloatLinear,				//!< \nop
		kBlendNodeInt16,					//!< \nop
		kBlendNodeInt32,					//!< \nop
		kBlendNodeAdditiveScale,			//!< \nop
		kBlendNodeAdditiveRotation,			//!< \nop
		kPluginManipulatorNode,				//!< Custom manipulator node derived from MPxManipulatorNode
		kNIdData,							//!< \nop
		kNId,							//!< \nop
		kFloatArrayData,					//!< \nop
		kMembrane,							//!< \nop
		kMergeVertsToolManip,				//!< \nop
		kUint64SingleIndexedComponent,		//!< \nop
		kPolyToolFeedbackManip,				//!< \nop
		kPolySelectEditFeedbackManip,		//!< \nop
		kWriteToFrameBuffer,                //!< \nop
		kWriteToColorBuffer,                //!< \nop
		kWriteToVectorBuffer,               //!< \nop
		kWriteToDepthBuffer,                //!< \nop
		kWriteToLabelBuffer,                //!< \nop
		kStereoCameraMaster,				//!< Master node for a stereo camera rig
		kSequenceManager,
		kSequencer,
		kShot,
    // RJ
		kBlendNodeTime,					//!< \nop
		kCreateBezierManip,					//!< \nop
		kBezierCurve,						//!< \nop
		kBezierCurveData,					//!< \nop
		kNurbsCurveToBezier,				//!< \nop
		kBezierCurveToNurbs,				//!< \nop
		kPolySpinEdge,						//!< \nop
		kPolyHoleFace,                      //!< \nop
		kPointOnPolyConstraint,             //!< \nop
		kPolyConnectComponents,             //!< \nop
		kSkinBinding,						//!< \nop
		kVolumeBindManip,					//!< \nop
		kVertexWeightSet,					//!< \nop
		kNearestPointOnCurve,				//!< \nop
		kColorProfile,                      //!< Color Profile Node
		kAdskMaterial,                      //!< Consistent material asset from an Autodesk Material Library
		kContainerBase,                     //!< base class for containers
		kDagContainer,                      //!< dag container node
		kPolyUVRectangle,					//!< \nop
		kHardwareRenderingGlobals,					//!< \nop
		kPolyProjectCurve,					//!< \nop
		kRenderingList,                     //!< \nop
		kPolyExtrudeManip,                  //!< \nop
		kPolyExtrudeManipContainer,         //!< \nop
		kThreadedDevice,                    //!< \nop
		kClientDevice,                      //!< \nop
		kPluginClientDevice,                //!< \nop
		kPluginThreadedDevice,				//!< \nop
		kTimeWarp,							//!< \nop
        kAssembly,                          //!< Base class for scene assembly nodes
		kClipGhostShape,                    //!< \nop
        kClipToGhostData,                   //!< \nop
		kMandelbrot,						//!< \nop
		kMandelbrot3D,						//!< \nop
		kGreasePlane,						//!< \nop
        kGreasePlaneRenderShape,			//!< \nop
        kGreasePencilSequence,				//!< \nop
		kEditMetadata,						//!< editMetadata Node
		kCreaseSet,							//!< Crease Set Node
		kPolyEditEdgeFlow,					//!< Edit Edge Flow History Node
		kFosterParent,						//!< \nop
		kSnapUVManip2D,						//!< \nop
		kToolContext,						//!< Tool context
		kNLE,						//!< NLE node 
		kShrinkWrapFilter,					//!< \nop
		kEditsManager,						//!< \nop
		kPolyBevel2,						//!< \nop
		kPolyCBoolOp,						//!< Carve Booleans Node
		kGeomBind,							//!< \nop
        kColorMgtGlobals,					//!< Color management globals node
		kPolyBevel3,						//!< \nop
		kTimeEditorClipBase,				//!< \nop	
		kTimeEditorClipEvaluator,			//!< \nop		
		kTimeEditorClip,					//!< \nop
		kTimeEditor,						//!< \nop
		kTimeEditorTracks,					//!< \nop
		kTimeEditorInterpolator,			//!< \nop
		kTimeEditorAnimSource,				//!< \nop
		kCaddyManipBase,         		    //!< \nop
		kPolyCaddyManip,                    //!< \nop
		kPolyModifierManipContainer,        //!< \nop
		kPolyRemesh,						//!< \nop
		kPolyContourProj,					//!< \nop
		kContourProjectionManip,			//!< \nop
		kNodeGraphEditorInfo,				//!< \nop
		kNodeGraphEditorBookmarks,			//!< \nop
		kNodeGraphEditorBookmarkInfo,		//!< \nop
		kPluginSkinCluster,					//!< Custom deformer node derived from MPxSkinCluster
		kPluginGeometryFilter,				//!< Custom deformer node derived from MPxGeometryFilter
		kPluginBlendShape,					//!< Custom deformer node derived from MPxBlendShape
		kPolyPassThru,
		kTrackInfoManager,					//!< \nop
		kPolyClean,							//!< \nop

		kShapeEditorManager,				//!< \nop
		kOceanDeformer,						//!< \nop
		kPoseInterpolatorManager,		    //!< \nop
        kControllerTag,					    //!< \nop
		kReForm,						    //!< \nop
        kCustomEvaluatorClusterNode,		//!< \nop
		kPolyCircularize,					//!< \nop

		kArubaTesselate,
		kReorderUVSet,
		kUfeProxyTransform, 
		kDecomposeMatrix,
		kComposeMatrix,
		kBlendMatrix,
		kPickMatrix,
		kAimMatrix,
		kPrimitiveFalloff,
		kBlendFalloff,
		kUniformFalloff,
		kTransferFalloff,
		kComponentFalloff,
		kWeightFunctionData,
		kFalloffEval,
		kComponentMatch,
		kProximityFalloff,
		kSubsetFalloff,
		kOpaqueAttribute,

		// This must go at the end of the list.
		kLast,								//!< Defines the last entry.

		//
		// Copies of existing IDs for backward compatibility
		kAttribute2Long = kAttribute2Int,	//!< Used for backward compatibility
		kAttribute3Long = kAttribute3Int,	//!< Used for backward compatibility
		kData2Long = kData2Int,				//!< Used for backward compatibility
		kData3Long = kData3Int				//!< Used for backward compatibility		
	};

	MFn::Type nodeType;

protected:
	// No protected members

private:
	// No private members

};

// ***************************************************************************

OPENMAYA_NAMESPACE_CLOSE

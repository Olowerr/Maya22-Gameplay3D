#pragma once
//-
// Copyright 2020 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk
// license agreement provided at the time of installation or download,
// or which otherwise accompanies this software in either electronic
// or hard copy form.
//+
//
// FILE:    MGLdefinitions.h
//
// ****************************************************************************
//
// DESCRIPTION (MGLdefinitions)
//
//	This file contains the definitions for basic types and constants
//	used for OpenGL.  Refer to an OpenGL reference for the meanings of
//	these types and constants. The difference in naming is only that
//	an "M" prefix prepended to avoid conflicts with existing type and
//	constant declarations.
//
// ****************************************************************************

#include <maya/MTypes.h>

//---------------------------------------------------------------
//
//		OS-SPECIFIC TYPE DEFINITIONS
//
//---------------------------------------------------------------

typedef unsigned int MGLenum;
typedef unsigned int MGLbitfield;
typedef int MGLint;
typedef int MGLsizei;
typedef unsigned int MGLuint;
typedef unsigned char MGLboolean;
typedef signed char MGLbyte;
typedef short MGLshort;
typedef unsigned char MGLubyte;
typedef unsigned short MGLushort;
typedef float MGLfloat;
typedef float MGLclampf;
typedef double MGLdouble;
typedef double MGLclampd;
typedef void MGLvoid;

//---------------------------------------------------------------
//
//		CORE 1.1 OPENGL DEFINITIONS
//		Versions 1.0 - 1.1
//		Extensions that were promoted to the core features of 1.1
//		are always assumed to exist.
//
//---------------------------------------------------------------

/* AccumOp */
#define MGL_ACCUM                          0x0100
#define MGL_LOAD                           0x0101
#define MGL_RETURN                         0x0102
#define MGL_MULT                           0x0103
#define MGL_ADD                            0x0104

/* AlphaFunction */
#define MGL_NEVER                          0x0200
#define MGL_LESS                           0x0201
#define MGL_EQUAL                          0x0202
#define MGL_LEQUAL                         0x0203
#define MGL_GREATER                        0x0204
#define MGL_NOTEQUAL                       0x0205
#define MGL_GEQUAL                         0x0206
#define MGL_ALWAYS                         0x0207

/* AttribMask */
#define MGL_CURRENT_BIT                    0x00000001
#define MGL_POINT_BIT                      0x00000002
#define MGL_LINE_BIT                       0x00000004
#define MGL_POLYGON_BIT                    0x00000008
#define MGL_POLYGON_STIPPLE_BIT            0x00000010
#define MGL_PIXEL_MODE_BIT                 0x00000020
#define MGL_LIGHTING_BIT                   0x00000040
#define MGL_FOG_BIT                        0x00000080
#define MGL_DEPTH_BUFFER_BIT               0x00000100
#define MGL_ACCUM_BUFFER_BIT               0x00000200
#define MGL_STENCIL_BUFFER_BIT             0x00000400
#define MGL_VIEWPORT_BIT                   0x00000800
#define MGL_TRANSFORM_BIT                  0x00001000
#define MGL_ENABLE_BIT                     0x00002000
#define MGL_COLOR_BUFFER_BIT               0x00004000
#define MGL_HINT_BIT                       0x00008000
#define MGL_EVAL_BIT                       0x00010000
#define MGL_LIST_BIT                       0x00020000
#define MGL_TEXTURE_BIT                    0x00040000
#define MGL_SCISSOR_BIT                    0x00080000
#define MGL_ALL_ATTRIB_BITS                0x000fffff

/* BeginMode */
#define MGL_POINTS                         0x0000
#define MGL_LINES                          0x0001
#define MGL_LINE_LOOP                      0x0002
#define MGL_LINE_STRIP                     0x0003
#define MGL_TRIANGLES                      0x0004
#define MGL_TRIANGLE_STRIP                 0x0005
#define MGL_TRIANGLE_FAN                   0x0006
#define MGL_QUADS                          0x0007
#define MGL_QUAD_STRIP                     0x0008
#define MGL_POLYGON                        0x0009

/* BlendingFactorDest */
#define MGL_ZERO                           0
#define MGL_ONE                            1
#define MGL_SRC_COLOR                      0x0300
#define MGL_ONE_MINUS_SRC_COLOR            0x0301
#define MGL_SRC_ALPHA                      0x0302
#define MGL_ONE_MINUS_SRC_ALPHA            0x0303
#define MGL_DST_ALPHA                      0x0304
#define MGL_ONE_MINUS_DST_ALPHA            0x0305

/* BlendingFactorSrc */
/*      MGL_ZERO */
/*      MGL_ONE */
#define MGL_DST_COLOR                      0x0306
#define MGL_ONE_MINUS_DST_COLOR            0x0307
#define MGL_SRC_ALPHA_SATURATE             0x0308
/*      MGL_SRC_ALPHA */
/*      MGL_ONE_MINUS_SRC_ALPHA */
/*      MGL_DST_ALPHA */
/*      MGL_ONE_MINUS_DST_ALPHA */

/* Boolean */
#define MGL_TRUE                           1
#define MGL_FALSE                          0

/* ClearBufferMask */
/*      MGL_COLOR_BUFFER_BIT */
/*      MGL_ACCUM_BUFFER_BIT */
/*      MGL_STENCIL_BUFFER_BIT */
/*      MGL_DEPTH_BUFFER_BIT */

/* ClientArrayType */
/*      MGL_VERTEX_ARRAY */
/*      MGL_NORMAL_ARRAY */
/*      MGL_COLOR_ARRAY */
/*      MGL_INDEX_ARRAY */
/*      MGL_TEXTURE_COORD_ARRAY */
/*      MGL_EDGE_FLAG_ARRAY */

/* ClipPlaneName */
#define MGL_CLIP_PLANE0                    0x3000
#define MGL_CLIP_PLANE1                    0x3001
#define MGL_CLIP_PLANE2                    0x3002
#define MGL_CLIP_PLANE3                    0x3003
#define MGL_CLIP_PLANE4                    0x3004
#define MGL_CLIP_PLANE5                    0x3005

/* ColorMaterialFace */
/*      MGL_FRONT */
/*      MGL_BACK */
/*      MGL_FRONT_AND_BACK */

/* ColorMaterialParameter */
/*      MGL_AMBIENT */
/*      MGL_DIFFUSE */
/*      MGL_SPECULAR */
/*      MGL_EMISSION */
/*      MGL_AMBIENT_AND_DIFFUSE */

/* ColorPointerType */
/*      MGL_BYTE */
/*      MGL_UNSIGNED_BYTE */
/*      MGL_SHORT */
/*      MGL_UNSIGNED_SHORT */
/*      MGL_INT */
/*      MGL_UNSIGNED_INT */
/*      MGL_FLOAT */
/*      MGL_DOUBLE */

/* CullFaceMode */
/*      MGL_FRONT */
/*      MGL_BACK */
/*      MGL_FRONT_AND_BACK */

/* DataType */
#define MGL_BYTE                           0x1400
#define MGL_UNSIGNED_BYTE                  0x1401
#define MGL_SHORT                          0x1402
#define MGL_UNSIGNED_SHORT                 0x1403
#define MGL_INT                            0x1404
#define MGL_UNSIGNED_INT                   0x1405
#define MGL_FLOAT                          0x1406
#define MGL_2_BYTES                        0x1407
#define MGL_3_BYTES                        0x1408
#define MGL_4_BYTES                        0x1409
#define MGL_DOUBLE                         0x140A

// MGL_ARB_half_float_pixel / part of MGL_NV_half_float / OpenEXR half
#define MGL_HALF_FLOAT                     0x140B

/* DepthFunction */
/*      MGL_NEVER */
/*      MGL_LESS */
/*      MGL_EQUAL */
/*      MGL_LEQUAL */
/*      MGL_GREATER */
/*      MGL_NOTEQUAL */
/*      MGL_GEQUAL */
/*      MGL_ALWAYS */

/* DrawBufferMode */
#define MGL_NONE                           0
#define MGL_FRONT_LEFT                     0x0400
#define MGL_FRONT_RIGHT                    0x0401
#define MGL_BACK_LEFT                      0x0402
#define MGL_BACK_RIGHT                     0x0403
#define MGL_FRONT                          0x0404
#define MGL_BACK                           0x0405
#define MGL_LEFT                           0x0406
#define MGL_RIGHT                          0x0407
#define MGL_FRONT_AND_BACK                 0x0408
#define MGL_AUX0                           0x0409
#define MGL_AUX1                           0x040A
#define MGL_AUX2                           0x040B
#define MGL_AUX3                           0x040C

/* Enable */
/*      MGL_FOG */
/*      MGL_LIGHTING */
/*      MGL_TEXTURE_1D */
/*      MGL_TEXTURE_2D */
/*      MGL_LINE_STIPPLE */
/*      MGL_POLYGON_STIPPLE */
/*      MGL_CULL_FACE */
/*      MGL_ALPHA_TEST */
/*      MGL_BLEND */
/*      MGL_INDEX_LOGIC_OP */
/*      MGL_COLOR_LOGIC_OP */
/*      MGL_DITHER */
/*      MGL_STENCIL_TEST */
/*      MGL_DEPTH_TEST */
/*      MGL_CLIP_PLANE0 */
/*      MGL_CLIP_PLANE1 */
/*      MGL_CLIP_PLANE2 */
/*      MGL_CLIP_PLANE3 */
/*      MGL_CLIP_PLANE4 */
/*      MGL_CLIP_PLANE5 */
/*      MGL_LIGHT0 */
/*      MGL_LIGHT1 */
/*      MGL_LIGHT2 */
/*      MGL_LIGHT3 */
/*      MGL_LIGHT4 */
/*      MGL_LIGHT5 */
/*      MGL_LIGHT6 */
/*      MGL_LIGHT7 */
/*      MGL_TEXTURE_GEN_S */
/*      MGL_TEXTURE_GEN_T */
/*      MGL_TEXTURE_GEN_R */
/*      MGL_TEXTURE_GEN_Q */
/*      MGL_MAP1_VERTEX_3 */
/*      MGL_MAP1_VERTEX_4 */
/*      MGL_MAP1_COLOR_4 */
/*      MGL_MAP1_INDEX */
/*      MGL_MAP1_NORMAL */
/*      MGL_MAP1_TEXTURE_COORD_1 */
/*      MGL_MAP1_TEXTURE_COORD_2 */
/*      MGL_MAP1_TEXTURE_COORD_3 */
/*      MGL_MAP1_TEXTURE_COORD_4 */
/*      MGL_MAP2_VERTEX_3 */
/*      MGL_MAP2_VERTEX_4 */
/*      MGL_MAP2_COLOR_4 */
/*      MGL_MAP2_INDEX */
/*      MGL_MAP2_NORMAL */
/*      MGL_MAP2_TEXTURE_COORD_1 */
/*      MGL_MAP2_TEXTURE_COORD_2 */
/*      MGL_MAP2_TEXTURE_COORD_3 */
/*      MGL_MAP2_TEXTURE_COORD_4 */
/*      MGL_POINT_SMOOTH */
/*      MGL_LINE_SMOOTH */
/*      MGL_POLYGON_SMOOTH */
/*      MGL_SCISSOR_TEST */
/*      MGL_COLOR_MATERIAL */
/*      MGL_NORMALIZE */
/*      MGL_AUTO_NORMAL */
/*      MGL_VERTEX_ARRAY */
/*      MGL_NORMAL_ARRAY */
/*      MGL_COLOR_ARRAY */
/*      MGL_INDEX_ARRAY */
/*      MGL_TEXTURE_COORD_ARRAY */
/*      MGL_EDGE_FLAG_ARRAY */
/*      MGL_POLYGON_OFFSET_POINT */
/*      MGL_POLYGON_OFFSET_LINE */
/*      MGL_POLYGON_OFFSET_FILL */

/* ErrorCode */
#define MGL_NO_ERROR                       0
#define MGL_INVALID_ENUM                   0x0500
#define MGL_INVALID_VALUE                  0x0501
#define MGL_INVALID_OPERATION              0x0502
#define MGL_STACK_OVERFLOW                 0x0503
#define MGL_STACK_UNDERFLOW                0x0504
#define MGL_OUT_OF_MEMORY                  0x0505

/* FeedBackMode */
#define MGL_2D                             0x0600
#define MGL_3D                             0x0601
#define MGL_3D_COLOR                       0x0602
#define MGL_3D_COLOR_TEXTURE               0x0603
#define MGL_4D_COLOR_TEXTURE               0x0604

/* FeedBackToken */
#define MGL_PASS_THROUGH_TOKEN             0x0700
#define MGL_POINT_TOKEN                    0x0701
#define MGL_LINE_TOKEN                     0x0702
#define MGL_POLYGON_TOKEN                  0x0703
#define MGL_BITMAP_TOKEN                   0x0704
#define MGL_DRAW_PIXEL_TOKEN               0x0705
#define MGL_COPY_PIXEL_TOKEN               0x0706
#define MGL_LINE_RESET_TOKEN               0x0707

/* FogMode */
/*      MGL_LINEAR */
#define MGL_EXP                            0x0800
#define MGL_EXP2                           0x0801


/* FogParameter */
/*      MGL_FOG_COLOR */
/*      MGL_FOG_DENSITY */
/*      MGL_FOG_END */
/*      MGL_FOG_INDEX */
/*      MGL_FOG_MODE */
/*      MGL_FOG_START */

/* FrontFaceDirection */
#define MGL_CW                             0x0900
#define MGL_CCW                            0x0901

/* GetMapTarget */
#define MGL_COEFF                          0x0A00
#define MGL_ORDER                          0x0A01
#define MGL_DOMAIN                         0x0A02

/* GetPixelMap */
/*      MGL_PIXEL_MAP_I_TO_I */
/*      MGL_PIXEL_MAP_S_TO_S */
/*      MGL_PIXEL_MAP_I_TO_R */
/*      MGL_PIXEL_MAP_I_TO_G */
/*      MGL_PIXEL_MAP_I_TO_B */
/*      MGL_PIXEL_MAP_I_TO_A */
/*      MGL_PIXEL_MAP_R_TO_R */
/*      MGL_PIXEL_MAP_G_TO_G */
/*      MGL_PIXEL_MAP_B_TO_B */
/*      MGL_PIXEL_MAP_A_TO_A */

/* GetPointerTarget */
/*      MGL_VERTEX_ARRAY_POINTER */
/*      MGL_NORMAL_ARRAY_POINTER */
/*      MGL_COLOR_ARRAY_POINTER */
/*      MGL_INDEX_ARRAY_POINTER */
/*      MGL_TEXTURE_COORD_ARRAY_POINTER */
/*      MGL_EDGE_FLAG_ARRAY_POINTER */

/* GetTarget */
#define MGL_CURRENT_COLOR                  0x0B00
#define MGL_CURRENT_INDEX                  0x0B01
#define MGL_CURRENT_NORMAL                 0x0B02
#define MGL_CURRENT_TEXTURE_COORDS         0x0B03
#define MGL_CURRENT_RASTER_COLOR           0x0B04
#define MGL_CURRENT_RASTER_INDEX           0x0B05
#define MGL_CURRENT_RASTER_TEXTURE_COORDS  0x0B06
#define MGL_CURRENT_RASTER_POSITION        0x0B07
#define MGL_CURRENT_RASTER_POSITION_VALID  0x0B08
#define MGL_CURRENT_RASTER_DISTANCE        0x0B09
#define MGL_POINT_SMOOTH                   0x0B10
#define MGL_POINT_SIZE                     0x0B11
#define MGL_POINT_SIZE_RANGE               0x0B12
#define MGL_POINT_SIZE_GRANULARITY         0x0B13
#define MGL_LINE_SMOOTH                    0x0B20
#define MGL_LINE_WIDTH                     0x0B21
#define MGL_LINE_WIDTH_RANGE               0x0B22
#define MGL_LINE_WIDTH_GRANULARITY         0x0B23
#define MGL_LINE_STIPPLE                   0x0B24
#define MGL_LINE_STIPPLE_PATTERN           0x0B25
#define MGL_LINE_STIPPLE_REPEAT            0x0B26
#define MGL_LIST_MODE                      0x0B30
#define MGL_MAX_LIST_NESTING               0x0B31
#define MGL_LIST_BASE                      0x0B32
#define MGL_LIST_INDEX                     0x0B33
#define MGL_POLYGON_MODE                   0x0B40
#define MGL_POLYGON_SMOOTH                 0x0B41
#define MGL_POLYGON_STIPPLE                0x0B42
#define MGL_EDGE_FLAG                      0x0B43
#define MGL_CULL_FACE                      0x0B44
#define MGL_CULL_FACE_MODE                 0x0B45
#define MGL_FRONT_FACE                     0x0B46
#define MGL_LIGHTING                       0x0B50
#define MGL_LIGHT_MODEL_LOCAL_VIEWER       0x0B51
#define MGL_LIGHT_MODEL_TWO_SIDE           0x0B52
#define MGL_LIGHT_MODEL_AMBIENT            0x0B53
#define MGL_SHADE_MODEL                    0x0B54
#define MGL_COLOR_MATERIAL_FACE            0x0B55
#define MGL_COLOR_MATERIAL_PARAMETER       0x0B56
#define MGL_COLOR_MATERIAL                 0x0B57
#define MGL_FOG                            0x0B60
#define MGL_FOG_INDEX                      0x0B61
#define MGL_FOG_DENSITY                    0x0B62
#define MGL_FOG_START                      0x0B63
#define MGL_FOG_END                        0x0B64
#define MGL_FOG_MODE                       0x0B65
#define MGL_FOG_COLOR                      0x0B66
#define MGL_DEPTH_RANGE                    0x0B70
#define MGL_DEPTH_TEST                     0x0B71
#define MGL_DEPTH_WRITEMASK                0x0B72
#define MGL_DEPTH_CLEAR_VALUE              0x0B73
#define MGL_DEPTH_FUNC                     0x0B74
#define MGL_ACCUM_CLEAR_VALUE              0x0B80
#define MGL_STENCIL_TEST                   0x0B90
#define MGL_STENCIL_CLEAR_VALUE            0x0B91
#define MGL_STENCIL_FUNC                   0x0B92
#define MGL_STENCIL_VALUE_MASK             0x0B93
#define MGL_STENCIL_FAIL                   0x0B94
#define MGL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define MGL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define MGL_STENCIL_REF                    0x0B97
#define MGL_STENCIL_WRITEMASK              0x0B98
#define MGL_MATRIX_MODE                    0x0BA0
#define MGL_NORMALIZE                      0x0BA1
#define MGL_VIEWPORT                       0x0BA2
#define MGL_MODELVIEW_STACK_DEPTH          0x0BA3
#define MGL_PROJECTION_STACK_DEPTH         0x0BA4
#define MGL_TEXTURE_STACK_DEPTH            0x0BA5
#define MGL_MODELVIEW_MATRIX               0x0BA6
#define MGL_PROJECTION_MATRIX              0x0BA7
#define MGL_TEXTURE_MATRIX                 0x0BA8
#define MGL_ATTRIB_STACK_DEPTH             0x0BB0
#define MGL_CLIENT_ATTRIB_STACK_DEPTH      0x0BB1
#define MGL_ALPHA_TEST                     0x0BC0
#define MGL_ALPHA_TEST_FUNC                0x0BC1
#define MGL_ALPHA_TEST_REF                 0x0BC2
#define MGL_DITHER                         0x0BD0
#define MGL_BLEND_DST                      0x0BE0
#define MGL_BLEND_SRC                      0x0BE1
#define MGL_BLEND                          0x0BE2
#define MGL_LOGIC_OP_MODE                  0x0BF0
#define MGL_INDEX_LOGIC_OP                 0x0BF1
#define MGL_COLOR_LOGIC_OP                 0x0BF2
#define MGL_AUX_BUFFERS                    0x0C00
#define MGL_DRAW_BUFFER                    0x0C01
#define MGL_READ_BUFFER                    0x0C02
#define MGL_SCISSOR_BOX                    0x0C10
#define MGL_SCISSOR_TEST                   0x0C11
#define MGL_INDEX_CLEAR_VALUE              0x0C20
#define MGL_INDEX_WRITEMASK                0x0C21
#define MGL_COLOR_CLEAR_VALUE              0x0C22
#define MGL_COLOR_WRITEMASK                0x0C23
#define MGL_INDEX_MODE                     0x0C30
#define MGL_RGBA_MODE                      0x0C31
#define MGL_DOUBLEBUFFER                   0x0C32
#define MGL_STEREO                         0x0C33
#define MGL_RENDER_MODE                    0x0C40
#define MGL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#define MGL_POINT_SMOOTH_HINT              0x0C51
#define MGL_LINE_SMOOTH_HINT               0x0C52
#define MGL_POLYGON_SMOOTH_HINT            0x0C53
#define MGL_FOG_HINT                       0x0C54
#define MGL_TEXTURE_GEN_S                  0x0C60
#define MGL_TEXTURE_GEN_T                  0x0C61
#define MGL_TEXTURE_GEN_R                  0x0C62
#define MGL_TEXTURE_GEN_Q                  0x0C63
#define MGL_PIXEL_MAP_I_TO_I               0x0C70
#define MGL_PIXEL_MAP_S_TO_S               0x0C71
#define MGL_PIXEL_MAP_I_TO_R               0x0C72
#define MGL_PIXEL_MAP_I_TO_G               0x0C73
#define MGL_PIXEL_MAP_I_TO_B               0x0C74
#define MGL_PIXEL_MAP_I_TO_A               0x0C75
#define MGL_PIXEL_MAP_R_TO_R               0x0C76
#define MGL_PIXEL_MAP_G_TO_G               0x0C77
#define MGL_PIXEL_MAP_B_TO_B               0x0C78
#define MGL_PIXEL_MAP_A_TO_A               0x0C79
#define MGL_PIXEL_MAP_I_TO_I_SIZE          0x0CB0
#define MGL_PIXEL_MAP_S_TO_S_SIZE          0x0CB1
#define MGL_PIXEL_MAP_I_TO_R_SIZE          0x0CB2
#define MGL_PIXEL_MAP_I_TO_G_SIZE          0x0CB3
#define MGL_PIXEL_MAP_I_TO_B_SIZE          0x0CB4
#define MGL_PIXEL_MAP_I_TO_A_SIZE          0x0CB5
#define MGL_PIXEL_MAP_R_TO_R_SIZE          0x0CB6
#define MGL_PIXEL_MAP_G_TO_G_SIZE          0x0CB7
#define MGL_PIXEL_MAP_B_TO_B_SIZE          0x0CB8
#define MGL_PIXEL_MAP_A_TO_A_SIZE          0x0CB9
#define MGL_UNPACK_SWAP_BYTES              0x0CF0
#define MGL_UNPACK_LSB_FIRST               0x0CF1
#define MGL_UNPACK_ROW_LENGTH              0x0CF2
#define MGL_UNPACK_SKIP_ROWS               0x0CF3
#define MGL_UNPACK_SKIP_PIXELS             0x0CF4
#define MGL_UNPACK_ALIGNMENT               0x0CF5
#define MGL_PACK_SWAP_BYTES                0x0D00
#define MGL_PACK_LSB_FIRST                 0x0D01
#define MGL_PACK_ROW_LENGTH                0x0D02
#define MGL_PACK_SKIP_ROWS                 0x0D03
#define MGL_PACK_SKIP_PIXELS               0x0D04
#define MGL_PACK_ALIGNMENT                 0x0D05
#define MGL_MAP_COLOR                      0x0D10
#define MGL_MAP_STENCIL                    0x0D11
#define MGL_INDEX_SHIFT                    0x0D12
#define MGL_INDEX_OFFSET                   0x0D13
#define MGL_RED_SCALE                      0x0D14
#define MGL_RED_BIAS                       0x0D15
#define MGL_ZOOM_X                         0x0D16
#define MGL_ZOOM_Y                         0x0D17
#define MGL_GREEN_SCALE                    0x0D18
#define MGL_GREEN_BIAS                     0x0D19
#define MGL_BLUE_SCALE                     0x0D1A
#define MGL_BLUE_BIAS                      0x0D1B
#define MGL_ALPHA_SCALE                    0x0D1C
#define MGL_ALPHA_BIAS                     0x0D1D
#define MGL_DEPTH_SCALE                    0x0D1E
#define MGL_DEPTH_BIAS                     0x0D1F
#define MGL_MAX_EVAL_ORDER                 0x0D30
#define MGL_MAX_LIGHTS                     0x0D31
#define MGL_MAX_CLIP_PLANES                0x0D32
#define MGL_MAX_TEXTURE_SIZE               0x0D33
#define MGL_MAX_PIXEL_MAP_TABLE            0x0D34
#define MGL_MAX_ATTRIB_STACK_DEPTH         0x0D35
#define MGL_MAX_MODELVIEW_STACK_DEPTH      0x0D36
#define MGL_MAX_NAME_STACK_DEPTH           0x0D37
#define MGL_MAX_PROJECTION_STACK_DEPTH     0x0D38
#define MGL_MAX_TEXTURE_STACK_DEPTH        0x0D39
#define MGL_MAX_VIEWPORT_DIMS              0x0D3A
#define MGL_MAX_CLIENT_ATTRIB_STACK_DEPTH  0x0D3B
#define MGL_SUBPIXEL_BITS                  0x0D50
#define MGL_INDEX_BITS                     0x0D51
#define MGL_RED_BITS                       0x0D52
#define MGL_GREEN_BITS                     0x0D53
#define MGL_BLUE_BITS                      0x0D54
#define MGL_ALPHA_BITS                     0x0D55
#define MGL_DEPTH_BITS                     0x0D56
#define MGL_STENCIL_BITS                   0x0D57
#define MGL_ACCUM_RED_BITS                 0x0D58
#define MGL_ACCUM_GREEN_BITS               0x0D59
#define MGL_ACCUM_BLUE_BITS                0x0D5A
#define MGL_ACCUM_ALPHA_BITS               0x0D5B
#define MGL_NAME_STACK_DEPTH               0x0D70
#define MGL_AUTO_NORMAL                    0x0D80
#define MGL_MAP1_COLOR_4                   0x0D90
#define MGL_MAP1_INDEX                     0x0D91
#define MGL_MAP1_NORMAL                    0x0D92
#define MGL_MAP1_TEXTURE_COORD_1           0x0D93
#define MGL_MAP1_TEXTURE_COORD_2           0x0D94
#define MGL_MAP1_TEXTURE_COORD_3           0x0D95
#define MGL_MAP1_TEXTURE_COORD_4           0x0D96
#define MGL_MAP1_VERTEX_3                  0x0D97
#define MGL_MAP1_VERTEX_4                  0x0D98
#define MGL_MAP2_COLOR_4                   0x0DB0
#define MGL_MAP2_INDEX                     0x0DB1
#define MGL_MAP2_NORMAL                    0x0DB2
#define MGL_MAP2_TEXTURE_COORD_1           0x0DB3
#define MGL_MAP2_TEXTURE_COORD_2           0x0DB4
#define MGL_MAP2_TEXTURE_COORD_3           0x0DB5
#define MGL_MAP2_TEXTURE_COORD_4           0x0DB6
#define MGL_MAP2_VERTEX_3                  0x0DB7
#define MGL_MAP2_VERTEX_4                  0x0DB8
#define MGL_MAP1_GRID_DOMAIN               0x0DD0
#define MGL_MAP1_GRID_SEGMENTS             0x0DD1
#define MGL_MAP2_GRID_DOMAIN               0x0DD2
#define MGL_MAP2_GRID_SEGMENTS             0x0DD3
#define MGL_TEXTURE_1D                     0x0DE0
#define MGL_TEXTURE_2D                     0x0DE1
#define MGL_FEEDBACK_BUFFER_POINTER        0x0DF0
#define MGL_FEEDBACK_BUFFER_SIZE           0x0DF1
#define MGL_FEEDBACK_BUFFER_TYPE           0x0DF2
#define MGL_SELECTION_BUFFER_POINTER       0x0DF3
#define MGL_SELECTION_BUFFER_SIZE          0x0DF4
/*      MGL_TEXTURE_BINDING_1D */
/*      MGL_TEXTURE_BINDING_2D */
/*      MGL_VERTEX_ARRAY */
/*      MGL_NORMAL_ARRAY */
/*      MGL_COLOR_ARRAY */
/*      MGL_INDEX_ARRAY */
/*      MGL_TEXTURE_COORD_ARRAY */
/*      MGL_EDGE_FLAG_ARRAY */
/*      MGL_VERTEX_ARRAY_SIZE */
/*      MGL_VERTEX_ARRAY_TYPE */
/*      MGL_VERTEX_ARRAY_STRIDE */
/*      MGL_NORMAL_ARRAY_TYPE */
/*      MGL_NORMAL_ARRAY_STRIDE */
/*      MGL_COLOR_ARRAY_SIZE */
/*      MGL_COLOR_ARRAY_TYPE */
/*      MGL_COLOR_ARRAY_STRIDE */
/*      MGL_INDEX_ARRAY_TYPE */
/*      MGL_INDEX_ARRAY_STRIDE */
/*      MGL_TEXTURE_COORD_ARRAY_SIZE */
/*      MGL_TEXTURE_COORD_ARRAY_TYPE */
/*      MGL_TEXTURE_COORD_ARRAY_STRIDE */
/*      MGL_EDGE_FLAG_ARRAY_STRIDE */
/*      MGL_POLYGON_OFFSET_FACTOR */
/*      MGL_POLYGON_OFFSET_UNITS */

/* GetTextureParameter */
/*      MGL_TEXTURE_MAG_FILTER */
/*      MGL_TEXTURE_MIN_FILTER */
/*      MGL_TEXTURE_WRAP_S */
/*      MGL_TEXTURE_WRAP_T */
#define MGL_TEXTURE_WIDTH                  0x1000
#define MGL_TEXTURE_HEIGHT                 0x1001
#define MGL_TEXTURE_INTERNAL_FORMAT        0x1003
#define MGL_TEXTURE_BORDER_COLOR           0x1004
#define MGL_TEXTURE_BORDER                 0x1005
/*      MGL_TEXTURE_RED_SIZE */
/*      MGL_TEXTURE_GREEN_SIZE */
/*      MGL_TEXTURE_BLUE_SIZE */
/*      MGL_TEXTURE_ALPHA_SIZE */
/*      MGL_TEXTURE_LUMINANCE_SIZE */
/*      MGL_TEXTURE_INTENSITY_SIZE */
/*      MGL_TEXTURE_PRIORITY */
/*      MGL_TEXTURE_RESIDENT */

/* HintMode */
#define MGL_DONT_CARE                      0x1100
#define MGL_FASTEST                        0x1101
#define MGL_NICEST                         0x1102

/* HintTarget */
/*      MGL_PERSPECTIVE_CORRECTION_HINT */
/*      MGL_POINT_SMOOTH_HINT */
/*      MGL_LINE_SMOOTH_HINT */
/*      MGL_POLYGON_SMOOTH_HINT */
/*      MGL_FOG_HINT */
/*      MGL_PHONG_HINT */

/* IndexPointerType */
/*      MGL_SHORT */
/*      MGL_INT */
/*      MGL_FLOAT */
/*      MGL_DOUBLE */

/* LightModelParameter */
/*      MGL_LIGHT_MODEL_AMBIENT */
/*      MGL_LIGHT_MODEL_LOCAL_VIEWER */
/*      MGL_LIGHT_MODEL_TWO_SIDE */

/* LightName */
#define MGL_LIGHT0                         0x4000
#define MGL_LIGHT1                         0x4001
#define MGL_LIGHT2                         0x4002
#define MGL_LIGHT3                         0x4003
#define MGL_LIGHT4                         0x4004
#define MGL_LIGHT5                         0x4005
#define MGL_LIGHT6                         0x4006
#define MGL_LIGHT7                         0x4007

/* LightParameter */
#define MGL_AMBIENT                        0x1200
#define MGL_DIFFUSE                        0x1201
#define MGL_SPECULAR                       0x1202
#define MGL_POSITION                       0x1203
#define MGL_SPOT_DIRECTION                 0x1204
#define MGL_SPOT_EXPONENT                  0x1205
#define MGL_SPOT_CUTOFF                    0x1206
#define MGL_CONSTANT_ATTENUATION           0x1207
#define MGL_LINEAR_ATTENUATION             0x1208
#define MGL_QUADRATIC_ATTENUATION          0x1209

/* InterleavedArrays */
/*      MGL_V2F */
/*      MGL_V3F */
/*      MGL_C4UB_V2F */
/*      MGL_C4UB_V3F */
/*      MGL_C3F_V3F */
/*      MGL_N3F_V3F */
/*      MGL_C4F_N3F_V3F */
/*      MGL_T2F_V3F */
/*      MGL_T4F_V4F */
/*      MGL_T2F_C4UB_V3F */
/*      MGL_T2F_C3F_V3F */
/*      MGL_T2F_N3F_V3F */
/*      MGL_T2F_C4F_N3F_V3F */
/*      MGL_T4F_C4F_N3F_V4F */

/* ListMode */
#define MGL_COMPILE                        0x1300
#define MGL_COMPILE_AND_EXECUTE            0x1301

/* ListNameType */
/*      MGL_BYTE */
/*      MGL_UNSIGNED_BYTE */
/*      MGL_SHORT */
/*      MGL_UNSIGNED_SHORT */
/*      MGL_INT */
/*      MGL_UNSIGNED_INT */
/*      MGL_FLOAT */
/*      MGL_2_BYTES */
/*      MGL_3_BYTES */
/*      MGL_4_BYTES */

/* LogicOp */
#define MGL_CLEAR                          0x1500
#define MGL_AND                            0x1501
#define MGL_AND_REVERSE                    0x1502
#define MGL_COPY                           0x1503
#define MGL_AND_INVERTED                   0x1504
#define MGL_NOOP                           0x1505
#define MGL_XOR                            0x1506
#define MGL_OR                             0x1507
#define MGL_NOR                            0x1508
#define MGL_EQUIV                          0x1509
#define MGL_INVERT                         0x150A
#define MGL_OR_REVERSE                     0x150B
#define MGL_COPY_INVERTED                  0x150C
#define MGL_OR_INVERTED                    0x150D
#define MGL_NAND                           0x150E
#define MGL_SET                            0x150F

/* MapTarget */
/*      MGL_MAP1_COLOR_4 */
/*      MGL_MAP1_INDEX */
/*      MGL_MAP1_NORMAL */
/*      MGL_MAP1_TEXTURE_COORD_1 */
/*      MGL_MAP1_TEXTURE_COORD_2 */
/*      MGL_MAP1_TEXTURE_COORD_3 */
/*      MGL_MAP1_TEXTURE_COORD_4 */
/*      MGL_MAP1_VERTEX_3 */
/*      MGL_MAP1_VERTEX_4 */
/*      MGL_MAP2_COLOR_4 */
/*      MGL_MAP2_INDEX */
/*      MGL_MAP2_NORMAL */
/*      MGL_MAP2_TEXTURE_COORD_1 */
/*      MGL_MAP2_TEXTURE_COORD_2 */
/*      MGL_MAP2_TEXTURE_COORD_3 */
/*      MGL_MAP2_TEXTURE_COORD_4 */
/*      MGL_MAP2_VERTEX_3 */
/*      MGL_MAP2_VERTEX_4 */

/* MaterialFace */
/*      MGL_FRONT */
/*      MGL_BACK */
/*      MGL_FRONT_AND_BACK */

/* MaterialParameter */
#define MGL_EMISSION                       0x1600
#define MGL_SHININESS                      0x1601
#define MGL_AMBIENT_AND_DIFFUSE            0x1602
#define MGL_COLOR_INDEXES                  0x1603
/*      MGL_AMBIENT */
/*      MGL_DIFFUSE */
/*      MGL_SPECULAR */

/* MatrixMode */
#define MGL_MODELVIEW                      0x1700
#define MGL_PROJECTION                     0x1701
#define MGL_TEXTURE                        0x1702

/* MeshMode1 */
/*      MGL_POINT */
/*      MGL_LINE */

/* MeshMode2 */
/*      MGL_POINT */
/*      MGL_LINE */
/*      MGL_FILL */

/* NormalPointerType */
/*      MGL_BYTE */
/*      MGL_SHORT */
/*      MGL_INT */
/*      MGL_FLOAT */
/*      MGL_DOUBLE */

/* PixelCopyType */
#define MGL_COLOR                          0x1800
#define MGL_DEPTH                          0x1801
#define MGL_STENCIL                        0x1802

/* PixelFormat */
#define MGL_COLOR_INDEX                    0x1900
#define MGL_STENCIL_INDEX                  0x1901
#define MGL_DEPTH_COMPONENT                0x1902
#define MGL_RED                            0x1903
#define MGL_GREEN                          0x1904
#define MGL_BLUE                           0x1905
#define MGL_ALPHA                          0x1906
#define MGL_RGB                            0x1907
#define MGL_RGBA                           0x1908
#define MGL_LUMINANCE                      0x1909
#define MGL_LUMINANCE_ALPHA                0x190A

/* PixelMap */
/*      MGL_PIXEL_MAP_I_TO_I */
/*      MGL_PIXEL_MAP_S_TO_S */
/*      MGL_PIXEL_MAP_I_TO_R */
/*      MGL_PIXEL_MAP_I_TO_G */
/*      MGL_PIXEL_MAP_I_TO_B */
/*      MGL_PIXEL_MAP_I_TO_A */
/*      MGL_PIXEL_MAP_R_TO_R */
/*      MGL_PIXEL_MAP_G_TO_G */
/*      MGL_PIXEL_MAP_B_TO_B */
/*      MGL_PIXEL_MAP_A_TO_A */

/* PixelStore */
/*      MGL_UNPACK_SWAP_BYTES */
/*      MGL_UNPACK_LSB_FIRST */
/*      MGL_UNPACK_ROW_LENGTH */
/*      MGL_UNPACK_SKIP_ROWS */
/*      MGL_UNPACK_SKIP_PIXELS */
/*      MGL_UNPACK_ALIGNMENT */
/*      MGL_PACK_SWAP_BYTES */
/*      MGL_PACK_LSB_FIRST */
/*      MGL_PACK_ROW_LENGTH */
/*      MGL_PACK_SKIP_ROWS */
/*      MGL_PACK_SKIP_PIXELS */
/*      MGL_PACK_ALIGNMENT */

/* PixelTransfer */
/*      MGL_MAP_COLOR */
/*      MGL_MAP_STENCIL */
/*      MGL_INDEX_SHIFT */
/*      MGL_INDEX_OFFSET */
/*      MGL_RED_SCALE */
/*      MGL_RED_BIAS */
/*      MGL_GREEN_SCALE */
/*      MGL_GREEN_BIAS */
/*      MGL_BLUE_SCALE */
/*      MGL_BLUE_BIAS */
/*      MGL_ALPHA_SCALE */
/*      MGL_ALPHA_BIAS */
/*      MGL_DEPTH_SCALE */
/*      MGL_DEPTH_BIAS */

/* PixelType */
#define MGL_BITMAP                         0x1A00
/*      MGL_BYTE */
/*      MGL_UNSIGNED_BYTE */
/*      MGL_SHORT */
/*      MGL_UNSIGNED_SHORT */
/*      MGL_INT */
/*      MGL_UNSIGNED_INT */
/*      MGL_FLOAT */

/* PolygonMode */
#define MGL_POINT                          0x1B00
#define MGL_LINE                           0x1B01
#define MGL_FILL                           0x1B02

/* ReadBufferMode */
/*      MGL_FRONT_LEFT */
/*      MGL_FRONT_RIGHT */
/*      MGL_BACK_LEFT */
/*      MGL_BACK_RIGHT */
/*      MGL_FRONT */
/*      MGL_BACK */
/*      MGL_LEFT */
/*      MGL_RIGHT */
/*      MGL_AUX0 */
/*      MGL_AUX1 */
/*      MGL_AUX2 */
/*      MGL_AUX3 */

/* RenderingMode */
#define MGL_RENDER                         0x1C00
#define MGL_FEEDBACK                       0x1C01
#define MGL_SELECT                         0x1C02

/* ShadingModel */
#define MGL_FLAT                           0x1D00
#define MGL_SMOOTH                         0x1D01


/* StencilFunction */
/*      MGL_NEVER */
/*      MGL_LESS */
/*      MGL_EQUAL */
/*      MGL_LEQUAL */
/*      MGL_GREATER */
/*      MGL_NOTEQUAL */
/*      MGL_GEQUAL */
/*      MGL_ALWAYS */

/* StencilOp */
/*      MGL_ZERO */
#define MGL_KEEP                           0x1E00
#define MGL_REPLACE                        0x1E01
#define MGL_INCR                           0x1E02
#define MGL_DECR                           0x1E03
/*      MGL_INVERT */

/* StringName */
#define MGL_VENDOR                         0x1F00
#define MGL_RENDERER                       0x1F01
#define MGL_VERSION                        0x1F02
#define MGL_EXTENSIONS                     0x1F03

/* TextureCoordName */
#define MGL_S                              0x2000
#define MGL_T                              0x2001
#define MGL_R                              0x2002
#define MGL_Q                              0x2003

/* TexCoordPointerType */
/*      MGL_SHORT */
/*      MGL_INT */
/*      MGL_FLOAT */
/*      MGL_DOUBLE */

/* TextureEnvMode */
#define MGL_MODULATE                       0x2100
#define MGL_DECAL                          0x2101
/*      MGL_BLEND */
/*      MGL_REPLACE */

/* TextureEnvParameter */
#define MGL_TEXTURE_ENV_MODE               0x2200
#define MGL_TEXTURE_ENV_COLOR              0x2201

/* TextureEnvTarget */
#define MGL_TEXTURE_ENV                    0x2300

/* TextureGenMode */
#define MGL_EYE_LINEAR                     0x2400
#define MGL_OBJECT_LINEAR                  0x2401
#define MGL_SPHERE_MAP                     0x2402

/* TextureGenParameter */
#define MGL_TEXTURE_GEN_MODE               0x2500
#define MGL_OBJECT_PLANE                   0x2501
#define MGL_EYE_PLANE                      0x2502

/* TextureMagFilter */
#define MGL_NEAREST                        0x2600
#define MGL_LINEAR                         0x2601

/* TextureMinFilter */
/*      MGL_NEAREST */
/*      MGL_LINEAR */
#define MGL_NEAREST_MIPMAP_NEAREST         0x2700
#define MGL_LINEAR_MIPMAP_NEAREST          0x2701
#define MGL_NEAREST_MIPMAP_LINEAR          0x2702
#define MGL_LINEAR_MIPMAP_LINEAR           0x2703

/* TextureParameterName */
#define MGL_TEXTURE_MAG_FILTER             0x2800
#define MGL_TEXTURE_MIN_FILTER             0x2801
#define MGL_TEXTURE_WRAP_S                 0x2802
#define MGL_TEXTURE_WRAP_T                 0x2803
/*      MGL_TEXTURE_BORDER_COLOR */
/*      MGL_TEXTURE_PRIORITY */

/* TextureTarget */
/*      MGL_TEXTURE_1D */
/*      MGL_TEXTURE_2D */
/*      MGL_PROXY_TEXTURE_1D */
/*      MGL_PROXY_TEXTURE_2D */

/* TextureWrapMode */
#define MGL_CLAMP                          0x2900
#define MGL_REPEAT                         0x2901

/* VertexPointerType */
/*      MGL_SHORT */
/*      MGL_INT */
/*      MGL_FLOAT */
/*      MGL_DOUBLE */

/* ClientAttribMask */
#define MGL_CLIENT_PIXEL_STORE_BIT         0x00000001
#define MGL_CLIENT_VERTEX_ARRAY_BIT        0x00000002
#ifdef __APPLE__
#define MGL_CLIENT_ALL_ATTRIB_BITS         0xffffffff
#else
#define MGL_CLIENT_ALL_ATTRIB_BITS         0xFFFFFFFF
#endif

/* polygon_offset */
#define MGL_POLYGON_OFFSET_FACTOR          0x8038
#define MGL_POLYGON_OFFSET_UNITS           0x2A00
#define MGL_POLYGON_OFFSET_POINT           0x2A01
#define MGL_POLYGON_OFFSET_LINE            0x2A02
#define MGL_POLYGON_OFFSET_FILL            0x8037

/* texture */
#define MGL_ALPHA4                         0x803B
#define MGL_ALPHA8                         0x803C
#define MGL_ALPHA12                        0x803D
#define MGL_ALPHA16                        0x803E
#define MGL_LUMINANCE4                     0x803F
#define MGL_LUMINANCE8                     0x8040
#define MGL_LUMINANCE12                    0x8041
#define MGL_LUMINANCE16                    0x8042
#define MGL_LUMINANCE4_ALPHA4              0x8043
#define MGL_LUMINANCE6_ALPHA2              0x8044
#define MGL_LUMINANCE8_ALPHA8              0x8045
#define MGL_LUMINANCE12_ALPHA4             0x8046
#define MGL_LUMINANCE12_ALPHA12            0x8047
#define MGL_LUMINANCE16_ALPHA16            0x8048
#define MGL_INTENSITY                      0x8049
#define MGL_INTENSITY4                     0x804A
#define MGL_INTENSITY8                     0x804B
#define MGL_INTENSITY12                    0x804C
#define MGL_INTENSITY16                    0x804D
#define MGL_R3_G3_B2                       0x2A10
#define MGL_RGB4                           0x804F
#define MGL_RGB5                           0x8050
#define MGL_RGB8                           0x8051
#define MGL_RGB10                          0x8052
#define MGL_RGB12                          0x8053
#define MGL_RGB16                          0x8054
#define MGL_RGBA2                          0x8055
#define MGL_RGBA4                          0x8056
#define MGL_RGB5_A1                        0x8057
#define MGL_RGBA8                          0x8058
#define MGL_RGB10_A2                       0x8059
#define MGL_RGBA12                         0x805A
#define MGL_RGBA16                         0x805B

#define MGL_TEXTURE_RED_SIZE               0x805C
#define MGL_TEXTURE_GREEN_SIZE             0x805D
#define MGL_TEXTURE_BLUE_SIZE              0x805E
#define MGL_TEXTURE_ALPHA_SIZE             0x805F
#define MGL_TEXTURE_LUMINANCE_SIZE         0x8060
#define MGL_TEXTURE_INTENSITY_SIZE         0x8061
#define MGL_PROXY_TEXTURE_1D               0x8063
#define MGL_PROXY_TEXTURE_2D               0x8064
#define MGL_TEXTURE_1D_BINDING			  0x8068
#define MGL_TEXTURE_2D_BINDING			  0x8069

/* texture_object */
#define MGL_TEXTURE_PRIORITY               0x8066
#define MGL_TEXTURE_RESIDENT               0x8067
#define MGL_TEXTURE_BINDING_1D             0x8068
#define MGL_TEXTURE_BINDING_2D             0x8069

/* vertex_array */
#define MGL_VERTEX_ARRAY                   0x8074
#define MGL_NORMAL_ARRAY                   0x8075
#define MGL_COLOR_ARRAY                    0x8076
#define MGL_INDEX_ARRAY                    0x8077
#define MGL_TEXTURE_COORD_ARRAY            0x8078
#define MGL_EDGE_FLAG_ARRAY                0x8079
#define MGL_VERTEX_ARRAY_SIZE              0x807A
#define MGL_VERTEX_ARRAY_TYPE              0x807B
#define MGL_VERTEX_ARRAY_STRIDE            0x807C
#define MGL_NORMAL_ARRAY_TYPE              0x807E
#define MGL_NORMAL_ARRAY_STRIDE            0x807F
#define MGL_COLOR_ARRAY_SIZE               0x8081
#define MGL_COLOR_ARRAY_TYPE               0x8082
#define MGL_COLOR_ARRAY_STRIDE             0x8083
#define MGL_INDEX_ARRAY_TYPE               0x8085
#define MGL_INDEX_ARRAY_STRIDE             0x8086
#define MGL_TEXTURE_COORD_ARRAY_SIZE       0x8088
#define MGL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#define MGL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#define MGL_EDGE_FLAG_ARRAY_STRIDE         0x808C
#define MGL_VERTEX_ARRAY_POINTER           0x808E
#define MGL_NORMAL_ARRAY_POINTER           0x808F
#define MGL_COLOR_ARRAY_POINTER            0x8090
#define MGL_INDEX_ARRAY_POINTER            0x8091
#define MGL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#define MGL_EDGE_FLAG_ARRAY_POINTER        0x8093
#define MGL_V2F                            0x2A20
#define MGL_V3F                            0x2A21
#define MGL_C4UB_V2F                       0x2A22
#define MGL_C4UB_V3F                       0x2A23
#define MGL_C3F_V3F                        0x2A24
#define MGL_N3F_V3F                        0x2A25
#define MGL_C4F_N3F_V3F                    0x2A26
#define MGL_T2F_V3F                        0x2A27
#define MGL_T4F_V4F                        0x2A28
#define MGL_T2F_C4UB_V3F                   0x2A29
#define MGL_T2F_C3F_V3F                    0x2A2A
#define MGL_T2F_N3F_V3F                    0x2A2B
#define MGL_T2F_C4F_N3F_V3F                0x2A2C
#define MGL_T4F_C4F_N3F_V4F                0x2A2D

/* These must match the MGL_COLOR_TABLE_*_SGI enumerants */
#define MGL_COLOR_TABLE_FORMAT_EXT         0x80D8
#define MGL_COLOR_TABLE_WIDTH_EXT          0x80D9
#define MGL_COLOR_TABLE_RED_SIZE_EXT       0x80DA
#define MGL_COLOR_TABLE_GREEN_SIZE_EXT     0x80DB
#define MGL_COLOR_TABLE_BLUE_SIZE_EXT      0x80DC
#define MGL_COLOR_TABLE_ALPHA_SIZE_EXT     0x80DD
#define MGL_COLOR_TABLE_LUMINANCE_SIZE_EXT 0x80DE
#define MGL_COLOR_TABLE_INTENSITY_SIZE_EXT 0x80DF

#define MGL_COLOR_INDEX1_EXT               0x80E2
#define MGL_COLOR_INDEX2_EXT               0x80E3
#define MGL_COLOR_INDEX4_EXT               0x80E4
#define MGL_COLOR_INDEX8_EXT               0x80E5
#define MGL_COLOR_INDEX12_EXT              0x80E6
#define MGL_COLOR_INDEX16_EXT              0x80E7

/* WIN_phong_shading */
#define MGL_PHONG_WIN                      0x80EA
#define MGL_PHONG_HINT_WIN                 0x80EB

/* WIN_specular_fog */
#define MGL_FOG_SPECULAR_TEXTURE_WIN       0x80EC

/* HP_occlusion_test */
#ifndef MGL_HP_occlusion_test
#define MGL_OCCLUSION_TEST_HP              0x8165
#define MGL_OCCLUSION_TEST_RESULT_HP       0x8166
#endif

/* automatic generation of mipmaps */
#define MGL_GENERATE_MIPMAP_SGIS			  0x8191

/* For compatibility with OpenGL v1.0 */
// Already defiend in <gl.h>
#define MGL_LOGIC_OP MGL_INDEX_LOGIC_OP
#define MGL_TEXTURE_COMPONENTS MGL_TEXTURE_INTERNAL_FORMAT

//---------------------------------------------------------------
//
//		OTHER OPENGL DEFINITIONS
//		Versions > 1.1
//
//---------------------------------------------------------------


//  MGL_VERSION_1_3
#define MGL_TEXTURE0                       0x84C0
#define MGL_TEXTURE1                       0x84C1
#define MGL_TEXTURE2                       0x84C2
#define MGL_TEXTURE3                       0x84C3
#define MGL_TEXTURE4                       0x84C4
#define MGL_TEXTURE5                       0x84C5
#define MGL_TEXTURE6                       0x84C6
#define MGL_TEXTURE7                       0x84C7
#define MGL_TEXTURE8                       0x84C8
#define MGL_TEXTURE9                       0x84C9
#define MGL_TEXTURE10                      0x84CA
#define MGL_TEXTURE11                      0x84CB
#define MGL_TEXTURE12                      0x84CC
#define MGL_TEXTURE13                      0x84CD
#define MGL_TEXTURE14                      0x84CE
#define MGL_TEXTURE15                      0x84CF
#define MGL_TEXTURE16                      0x84D0
#define MGL_TEXTURE17                      0x84D1
#define MGL_TEXTURE18                      0x84D2
#define MGL_TEXTURE19                      0x84D3
#define MGL_TEXTURE20                      0x84D4
#define MGL_TEXTURE21                      0x84D5
#define MGL_TEXTURE22                      0x84D6
#define MGL_TEXTURE23                      0x84D7
#define MGL_TEXTURE24                      0x84D8
#define MGL_TEXTURE25                      0x84D9
#define MGL_TEXTURE26                      0x84DA
#define MGL_TEXTURE27                      0x84DB
#define MGL_TEXTURE28                      0x84DC
#define MGL_TEXTURE29                      0x84DD
#define MGL_TEXTURE30                      0x84DE
#define MGL_TEXTURE31                      0x84DF
#define MGL_ACTIVE_TEXTURE                 0x84E0
#define MGL_CLIENT_ACTIVE_TEXTURE          0x84E1
#define MGL_MAX_TEXTURE_UNITS              0x84E2
#define MGL_TRANSPOSE_MODELVIEW_MATRIX     0x84E3
#define MGL_TRANSPOSE_PROJECTION_MATRIX    0x84E4
#define MGL_TRANSPOSE_TEXTURE_MATRIX       0x84E5
#define MGL_TRANSPOSE_COLOR_MATRIX         0x84E6
#define MGL_MULTISAMPLE                    0x809D
#define MGL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define MGL_SAMPLE_ALPHA_TO_ONE            0x809F
#define MGL_SAMPLE_COVERAGE                0x80A0
#define MGL_SAMPLE_BUFFERS                 0x80A8
#define MGL_SAMPLES                        0x80A9
#define MGL_SAMPLE_COVERAGE_VALUE          0x80AA
#define MGL_SAMPLE_COVERAGE_INVERT         0x80AB
#define MGL_MULTISAMPLE_BIT                0x20000000
#define MGL_NORMAL_MAP                     0x8511
#define MGL_REFLECTION_MAP                 0x8512
#define MGL_TEXTURE_CUBE_MAP               0x8513
#define MGL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define MGL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define MGL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define MGL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define MGL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define MGL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define MGL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define MGL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define MGL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define MGL_COMPRESSED_ALPHA               0x84E9
#define MGL_COMPRESSED_LUMINANCE           0x84EA
#define MGL_COMPRESSED_LUMINANCE_ALPHA     0x84EB
#define MGL_COMPRESSED_INTENSITY           0x84EC
#define MGL_COMPRESSED_RGB                 0x84ED
#define MGL_COMPRESSED_RGBA                0x84EE
#define MGL_TEXTURE_COMPRESSION_HINT       0x84EF
#define MGL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define MGL_TEXTURE_COMPRESSED             0x86A1
#define MGL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define MGL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define MGL_CLAMP_TO_BORDER                0x812D
#define MGL_CLAMP_TO_BORDER_SGIS           0x812D
#define MGL_COMBINE                        0x8570
#define MGL_COMBINE_RGB                    0x8571
#define MGL_COMBINE_ALPHA                  0x8572
#define MGL_SOURCE0_RGB                    0x8580
#define MGL_SOURCE1_RGB                    0x8581
#define MGL_SOURCE2_RGB                    0x8582
#define MGL_SOURCE0_ALPHA                  0x8588
#define MGL_SOURCE1_ALPHA                  0x8589
#define MGL_SOURCE2_ALPHA                  0x858A
#define MGL_OPERAND0_RGB                   0x8590
#define MGL_OPERAND1_RGB                   0x8591
#define MGL_OPERAND2_RGB                   0x8592
#define MGL_OPERAND0_ALPHA                 0x8598
#define MGL_OPERAND1_ALPHA                 0x8599
#define MGL_OPERAND2_ALPHA                 0x859A
#define MGL_RGB_SCALE                      0x8573
#define MGL_ADD_SIGNED                     0x8574
#define MGL_INTERPOLATE                    0x8575
#define MGL_SUBTRACT                       0x84E7
#define MGL_CONSTANT                       0x8576
#define MGL_PRIMARY_COLOR                  0x8577
#define MGL_PREVIOUS                       0x8578
#define MGL_DOT3_RGB                       0x86AE
#define MGL_DOT3_RGBA                      0x86AF


// texture_edge_clamp (part of 1.2)
#define MGL_CLAMP_TO_EDGE					0x812F
//#define MGL_CLAMP_TO_EDGE_SGIS			0x812F
//#define MGL_CLAMP_TO_EDGE_EXT				0x812F


/* EXT_abgr */
#define MGL_ABGR_EXT                         0x8000

/* EXT_blend_color */
#define MGL_CONSTANT_COLOR                   0x8001
#define MGL_CONSTANT_COLOR_EXT               0x8001
#define MGL_ONE_MINUS_CONSTANT_COLOR         0x8002
#define MGL_ONE_MINUS_CONSTANT_COLOR_EXT     0x8002
#define MGL_CONSTANT_ALPHA                   0x8003
#define MGL_CONSTANT_ALPHA_EXT               0x8003
#define MGL_ONE_MINUS_CONSTANT_ALPHA         0x8004
#define MGL_ONE_MINUS_CONSTANT_ALPHA_EXT     0x8004
#define MGL_BLEND_COLOR                      0x8005
#define MGL_BLEND_COLOR_EXT                  0x8005

/* EXT_blend_minmax */
#define MGL_FUNC_ADD                         0x8006
#define MGL_FUNC_ADD_EXT                     0x8006
#define MGL_MIN                              0x8007
#define MGL_MIN_EXT                          0x8007
#define MGL_MAX                              0x8008
#define MGL_MAX_EXT                          0x8008
#define MGL_BLEND_EQUATION                   0x8009
#define MGL_BLEND_EQUATION_EXT               0x8009

/* EXT_blend_subtract */
#define MGL_FUNC_SUBTRACT                    0x800A
#define MGL_FUNC_SUBTRACT_EXT                0x800A
#define MGL_FUNC_REVERSE_SUBTRACT            0x800B
#define MGL_FUNC_REVERSE_SUBTRACT_EXT        0x800B

/* EXT_packed_pixels */
#define MGL_UNSIGNED_BYTE_3_3_2_EXT          0x8032
#define MGL_UNSIGNED_SHORT_4_4_4_4_EXT       0x8033
#define MGL_UNSIGNED_SHORT_5_5_5_1_EXT       0x8034
#define MGL_UNSIGNED_INT_8_8_8_8_EXT         0x8035
#define MGL_UNSIGNED_INT_10_10_10_2_EXT      0x8036

/* MGL_EXT_rescale_normal */
#define MGL_RESCALE_NORMAL_EXT				0x803A

/* MGL_EXT_texture3D */
#define MGL_PACK_SKIP_IMAGES					0x806B
#define MGL_PACK_SKIP_IMAGES_EXT				0x806B
#define MGL_PACK_IMAGE_HEIGHT					0x806C
#define MGL_PACK_IMAGE_HEIGHT_EXT				0x806C
#define MGL_UNPACK_SKIP_IMAGES					0x806D
#define MGL_UNPACK_SKIP_IMAGES_EXT				0x806D
#define MGL_UNPACK_IMAGE_HEIGHT					0x806E
#define MGL_UNPACK_IMAGE_HEIGHT_EXT				0x806E
#define MGL_TEXTURE_3D							0x806F
#define MGL_TEXTURE_3D_EXT						0x806F
#define MGL_PROXY_TEXTURE_3D					0x8070
#define MGL_PROXY_TEXTURE_3D_EXT				0x8070
#define MGL_TEXTURE_DEPTH						0x8071
#define MGL_TEXTURE_DEPTH_EXT					0x8071
#define MGL_TEXTURE_WRAP_R						0x8072
#define MGL_TEXTURE_WRAP_R_EXT					0x8072
#define MGL_MAX_3D_TEXTURE_SIZE					0x8073
#define MGL_MAX_3D_TEXTURE_SIZE_EXT				0x8073

/* EXT_vertex_array */
#define MGL_VERTEX_ARRAY_EXT                 0x8074
#define MGL_NORMAL_ARRAY_EXT                 0x8075
#define MGL_COLOR_ARRAY_EXT                  0x8076
#define MGL_INDEX_ARRAY_EXT                  0x8077
#define MGL_TEXTURE_COORD_ARRAY_EXT          0x8078
#define MGL_EDGE_FLAG_ARRAY_EXT              0x8079
#define MGL_VERTEX_ARRAY_SIZE_EXT            0x807A
#define MGL_VERTEX_ARRAY_TYPE_EXT            0x807B
#define MGL_VERTEX_ARRAY_STRIDE_EXT          0x807C
#define MGL_VERTEX_ARRAY_COUNT_EXT           0x807D
#define MGL_NORMAL_ARRAY_TYPE_EXT            0x807E
#define MGL_NORMAL_ARRAY_STRIDE_EXT          0x807F
#define MGL_NORMAL_ARRAY_COUNT_EXT           0x8080
#define MGL_COLOR_ARRAY_SIZE_EXT             0x8081
#define MGL_COLOR_ARRAY_TYPE_EXT             0x8082
#define MGL_COLOR_ARRAY_STRIDE_EXT           0x8083
#define MGL_COLOR_ARRAY_COUNT_EXT            0x8084
#define MGL_INDEX_ARRAY_TYPE_EXT             0x8085
#define MGL_INDEX_ARRAY_STRIDE_EXT           0x8086
#define MGL_INDEX_ARRAY_COUNT_EXT            0x8087
#define MGL_TEXTURE_COORD_ARRAY_SIZE_EXT     0x8088
#define MGL_TEXTURE_COORD_ARRAY_TYPE_EXT     0x8089
#define MGL_TEXTURE_COORD_ARRAY_STRIDE_EXT   0x808A
#define MGL_TEXTURE_COORD_ARRAY_COUNT_EXT    0x808B
#define MGL_EDGE_FLAG_ARRAY_STRIDE_EXT       0x808C
#define MGL_EDGE_FLAG_ARRAY_COUNT_EXT        0x808D
#define MGL_VERTEX_ARRAY_POINTER_EXT         0x808E
#define MGL_NORMAL_ARRAY_POINTER_EXT         0x808F
#define MGL_COLOR_ARRAY_POINTER_EXT          0x8090
#define MGL_INDEX_ARRAY_POINTER_EXT          0x8091
#define MGL_TEXTURE_COORD_ARRAY_POINTER_EXT  0x8092
#define MGL_EDGE_FLAG_ARRAY_POINTER_EXT      0x8093

/* MGL_ARB_multisample */
#define MGL_MULTISAMPLE_ARB					0x809D
#define MGL_SAMPLE_ALPHA_TO_COVERAGE_ARB		0x809E
#define MGL_SAMPLE_ALPHA_TO_ONE_ARB			0x809F
#define MGL_SAMPLE_COVERAGE_ARB				0x80A0
#define MGL_SAMPLE_BUFFERS_ARB				0x80A8
#define MGL_SAMPLES_ARB						0x80A9
#define MGL_SAMPLE_COVERAGE_VALUE_ARB		0x80AA
#define MGL_SAMPLE_COVERAGE_INVERT_ARB		0x80AB
#define MGL_MULTISAMPLE_BIT_ARB				0x20000000

/* EXT_bgra */
#define MGL_BGR_EXT                          0x80E0
#define MGL_BGRA_EXT                         0x80E1

/* EXT_clip_volume_hint */
#define MGL_CLIP_VOLUME_CLIPPING_HINT_EXT    0x80F0

/* EXT_point_parameters */
/* ARB_point_parameters */
#define MGL_POINT_SIZE_MIN_ARB               0x8126
#define MGL_POINT_SIZE_MAX_ARB               0x8127
#define MGL_POINT_FADE_THRESHOLD_SIZE_ARB    0x8128
#define MGL_POINT_DISTANCE_ATTENUATION_ARB   0x8129

/* ARB_depth_texture */
#define MGL_ARB_depth_texture				1
#define MGL_DEPTH_COMPONENT16_ARB			0x81A5
#define MGL_DEPTH_COMPONENT24_ARB			0x81A6
#define MGL_DEPTH_COMPONENT32_ARB			0x81A7
#define MGL_TEXTURE_DEPTH_SIZE_ARB			0x884A
#define MGL_DEPTH_TEXTURE_MODE_ARB			0x884B

/* ARB_shadow - needs ARB_depth_texture */
#define MGL_ARB_shadow						1
#define MGL_TEXTURE_COMPARE_MODE_ARB			0x884C
#define MGL_TEXTURE_COMPARE_FUNC_ARB			0x884D
#define MGL_COMPARE_R_TO_TEXTURE_ARB			0x884E
// Old SGIX extension
#define MGL_TEXTURE_COMPARE_SGIX				0x819A
#define MGL_TEXTURE_COMPARE_OPERATOR_SGIX	0x819B
// Old SGIX extension numbers. use MGL_LEQUAL, and MGL_EQUAL instead
// for ARB_shadow definition
#define MGL_TEXTURE_LEQUAL_R_SGIX			0x819C
#define MGL_TEXTURE_GEQUAL_R_SGIX			0x819D

/* ARB_shadow_ambient - needs ARB_shadow + ARB_depth_texture */
#define MGL_ARB_shadow_ambient               1
#define MGL_TEXTURE_COMPARE_FAIL_VALUE_ARB	0x80BF

/* MGL_ARB_texture_border_clamp, replaces SGIS version */
#define MGL_CLAMP_TO_BORDER_ARB             0x812D
//#define MGL_CLAMP_TO_BORDER_SGIS            0x812D

/* EXT_compiled_vertex_array */
#define MGL_ARRAY_ELEMENT_LOCK_FIRST_EXT     0x81A8
#define MGL_ARRAY_ELEMENT_LOCK_COUNT_EXT     0x81A9

/* EXT_cull_vertex */
#define MGL_CULL_VERTEX_EXT                  0x81AA
#define MGL_CULL_VERTEX_EYE_POSITION_EXT     0x81AB
#define MGL_CULL_VERTEX_OBJECT_POSITION_EXT  0x81AC

/* separate_specular_color

   For OGL 1.2, these are no longer extensions
   (no _EXT at the end) but the numbers are the same.
*/
#define MGL_LIGHT_MODEL_COLOR_CONTROL		0x81F8
#define MGL_SINGLE_COLOR						0x81F9
#define MGL_SEPARATE_SPECULAR_COLOR			0x81FA


/* MGL_IBM_texture_mirrored_repeat */
#define MGL_IBM_TEXTURE_MIRRORED_REPEAT	1
#define MGL_MIRRORED_REPEAT_IBM				0x8370

/* MGL_EXT_texture_compression_s3tc */
#define MGL_COMPRESSED_RGB_S3TC_DXT1_EXT   0x83F0
#define MGL_COMPRESSED_RGBA_S3TC_DXT1_EXT  0x83F1
#define MGL_COMPRESSED_RGBA_S3TC_DXT3_EXT  0x83F2
#define MGL_COMPRESSED_RGBA_S3TC_DXT5_EXT  0x83F3

/* MGL_EXT_fog_coord */
#define MGL_FOG_COORDINATE_SOURCE_EXT		0x8450
#define MGL_FOG_COORDINATE_EXT				0x8451
#define MGL_FRAGMENT_DEPTH_EXT				0x8452
#define MGL_CURRENT_FOG_COORDINATE_EXT		0x8453
#define MGL_FOG_COORDINATE_ARRAY_TYPE_EXT	0x8454
#define MGL_FOG_COORDINATE_ARRAY_STRIDE_EXT	0x8455
#define MGL_FOG_COORDINATE_ARRAY_POINTER_EXT 0x8456
#define MGL_FOG_COORDINATE_ARRAY_EXT			0x8457


/* MGL_EXT_secondary_color */
#define MGL_COLOR_SUM_EXT						0x8458
#define MGL_CURRENT_SECONDARY_COLOR_EXT			0x8459
#define MGL_SECONDARY_COLOR_ARRAY_SIZE_EXT		0x845A
#define MGL_SECONDARY_COLOR_ARRAY_TYPE_EXT		0x845B
#define MGL_SECONDARY_COLOR_ARRAY_STRIDE_EXT		0x845C
#define MGL_SECONDARY_COLOR_ARRAY_POINTER_EXT	0x845D
#define MGL_SECONDARY_COLOR_ARRAY_EXT			0x845E

/* ARB_multitexture */
#define MGL_TEXTURE0_ARB                     0x84C0
#define MGL_TEXTURE1_ARB                     0x84C1
#define MGL_TEXTURE2_ARB                     0x84C2
#define MGL_TEXTURE3_ARB                     0x84C3
#define MGL_TEXTURE4_ARB                     0x84C4
#define MGL_TEXTURE5_ARB                     0x84C5
#define MGL_TEXTURE6_ARB                     0x84C6
#define MGL_TEXTURE7_ARB                     0x84C7
#define MGL_TEXTURE8_ARB                     0x84C8
#define MGL_TEXTURE9_ARB                     0x84C9
#define MGL_TEXTURE10_ARB                    0x84CA
#define MGL_TEXTURE11_ARB                    0x84CB
#define MGL_TEXTURE12_ARB                    0x84CC
#define MGL_TEXTURE13_ARB                    0x84CD
#define MGL_TEXTURE14_ARB                    0x84CE
#define MGL_TEXTURE15_ARB                    0x84CF
#define MGL_TEXTURE16_ARB                    0x84D0
#define MGL_TEXTURE17_ARB                    0x84D1
#define MGL_TEXTURE18_ARB                    0x84D2
#define MGL_TEXTURE19_ARB                    0x84D3
#define MGL_TEXTURE20_ARB                    0x84D4
#define MGL_TEXTURE21_ARB                    0x84D5
#define MGL_TEXTURE22_ARB                    0x84D6
#define MGL_TEXTURE23_ARB                    0x84D7
#define MGL_TEXTURE24_ARB                    0x84D8
#define MGL_TEXTURE25_ARB                    0x84D9
#define MGL_TEXTURE26_ARB                    0x84DA
#define MGL_TEXTURE27_ARB                    0x84DB
#define MGL_TEXTURE28_ARB                    0x84DC
#define MGL_TEXTURE29_ARB                    0x84DD
#define MGL_TEXTURE30_ARB                    0x84DE
#define MGL_TEXTURE31_ARB                    0x84DF
#define MGL_ACTIVE_TEXTURE_ARB               0x84E0
#define MGL_CLIENT_ACTIVE_TEXTURE_ARB        0x84E1
#define MGL_MAX_TEXTURE_UNITS_ARB            0x84E2

/* MGL_ARB_transpose_matrix */
#define MGL_TRANSPOSE_MODELVIEW_MATRIX_ARB	0x84E3
#define MGL_TRANSPOSE_PROJECTION_MATRIX_ARB	0x84E4
#define MGL_TRANSPOSE_TEXTURE_MATRIX_ARB		0x84E5
#define MGL_TRANSPOSE_COLOR_MATRIX_ARB		0x84E6

/* MGL_NV_fence */
#define MGL_ALL_COMPLETED_NV               0x84F2
#define MGL_FENCE_STATUS_NV                0x84F3
#define MGL_FENCE_CONDITION_NV             0x84F4

// MGL_NV_fragment_program
#define MGL_FRAGMENT_PROGRAM_NV						0x8870
#define MGL_MAX_TEXTURE_COORDS_NV					0x8871
#define MGL_MAX_TEXTURE_IMAGE_UNITS_NV				0x8872
#define MGL_FRAGMENT_PROGRAM_BINDING_NV				0x8873
#define MGL_PROGRAM_ERROR_STRING_NV					0x8874
#define MGL_MAX_FRAGMENT_PROGRAM_LOCAL_PARAMETERS_NV 0x8868

// MGL_ARB_fragment_program
#define MGL_FRAGMENT_PROGRAM_ARB                         0x8804
#define MGL_PROGRAM_ALU_INSTRUCTIONS_ARB                 0x8805
#define MGL_PROGRAM_TEX_INSTRUCTIONS_ARB                 0x8806
#define MGL_PROGRAM_TEX_INDIRECTIONS_ARB                 0x8807
#define MGL_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB          0x8808
#define MGL_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB          0x8809
#define MGL_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB          0x880A
#define MGL_MAX_PROGRAM_ALU_INSTRUCTIONS_ARB             0x880B
#define MGL_MAX_PROGRAM_TEX_INSTRUCTIONS_ARB             0x880C
#define MGL_MAX_PROGRAM_TEX_INDIRECTIONS_ARB             0x880D
#define MGL_MAX_PROGRAM_NATIVE_ALU_INSTRUCTIONS_ARB      0x880E
#define MGL_MAX_PROGRAM_NATIVE_TEX_INSTRUCTIONS_ARB      0x880F
#define MGL_MAX_PROGRAM_NATIVE_TEX_INDIRECTIONS_ARB      0x8810
#define MGL_MAX_TEXTURE_COORDS_ARB                       0x8871
#define MGL_MAX_TEXTURE_IMAGE_UNITS_ARB                  0x8872
/* Note: Other required definitions for this extension are defined
   as under MGL_ARB_vertex_program */

/* MGL_EXT_texture_filter_anisotropic */
#define MGL_TEXTURE_MAX_ANISOTROPY_EXT		0x84FE
#define MGL_MAX_TEXTURE_MAX_ANISOTROPY_EXT	0x84FF

/* MGL_EXT_vertex_weighting */
#define MGL_MODELVIEW0_STACK_DEPTH_EXT		MGL_MODELVIEW_STACK_DEPTH
#define MGL_MODELVIEW1_STACK_DEPTH_EXT		0x8502
#define MGL_MODELVIEW0_MATRIX_EXT			MGL_MODELVIEW_MATRIX
#define MGL_MODELVIEW_MATRIX1_EXT			0x8506
#define MGL_VERTEX_WEIGHTING_EXT				0x8509
#define MGL_MODELVIEW0_EXT					MGL_MODELVIEW
#define MGL_MODELVIEW1_EXT					0x850A
#define MGL_CURRENT_VERTEX_WEIGHT_EXT		0x850B
#define MGL_VERTEX_WEIGHT_ARRAY_EXT			0x850C
#define MGL_VERTEX_WEIGHT_ARRAY_SIZE_EXT		0x850D
#define MGL_VERTEX_WEIGHT_ARRAY_TYPE_EXT		0x850E
#define MGL_VERTEX_WEIGHT_ARRAY_STRIDE_EXT	0x850F
#define MGL_VERTEX_WEIGHT_ARRAY_POINTER_EXT	0x8510

/* MGL_ARB_texture_compression */
#define MGL_COMPRESSED_ALPHA_ARB					0x84E9
#define MGL_COMPRESSED_LUMINANCE_ARB				0x84EA
#define MGL_COMPRESSED_LUMINANCE_ALPHA_ARB		0x84EB
#define MGL_COMPRESSED_INTENSITY_ARB				0x84EC
#define MGL_COMPRESSED_RGB_ARB					0x84ED
#define MGL_COMPRESSED_RGBA_ARB					0x84EE
#define MGL_TEXTURE_COMPRESSION_HINT_ARB			0x84EF
#define MGL_TEXTURE_IMAGE_SIZE_ARB				0x86A0
#define MGL_TEXTURE_COMPRESSED_ARB				0x86A1
#define MGL_NUM_COMPRESSED_TEXTURE_FORMATS_ARB	0x86A2
#define MGL_COMPRESSED_TEXTURE_FORMATS_ARB		0x86A3

/* ARB_texture_env_dot3 */
#define MGL_ARB_texture_env_dot3			  1
#define MGL_DOT3_RGB_ARB                   0x86AE
#define MGL_DOT3_RGB_EXT                   0x86AE
#define MGL_DOT3_RGBA_ARB                  0x86AF
#define MGL_DOT3_RGBA_EXT                  0x86AF

/* EXT_stencil_wrap */
#define MGL_INCR_WRAP_EXT                    0x8507
#define MGL_DECR_WRAP_EXT                    0x8508

/* NV_texgen_reflection, or EXT_texgen_reflection or ARB_texgen_reflection */
#define MGL_NORMAL_MAP_ARB						0x8511 /* NV == ARB */
#define MGL_REFLECTION_MAP_ARB					0x8512 /* NV == ARB */

// MGL_ARB_texture_cube_map
#define MGL_NORMAL_MAP_ARB						0x8511
#define MGL_REFLECTION_MAP_ARB					0x8512
#define MGL_TEXTURE_CUBE_MAP_ARB					0x8513
#define MGL_TEXTURE_BINDING_CUBE_MAP_ARB			0x8514
#define MGL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB		0x8515
#define MGL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB		0x8516
#define MGL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB		0x8517
#define MGL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB		0x8518
#define MGL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB		0x8519
#define MGL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB		0x851A
#define MGL_PROXY_TEXTURE_CUBE_MAP_ARB			0x851B
#define MGL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB		0x851C

// MGL_ARB_texture_float
#define MGL_TEXTURE_RED_TYPE			    0x8C10
#define MGL_TEXTURE_GREEN_TYPE			0x8C11
#define MGL_TEXTURE_BLUE_TYPE			0x8C12
#define MGL_TEXTURE_ALPHA_TYPE			0x8C13
#define MGL_TEXTURE_LUMINANCE_TYPE		0x8C14
#define MGL_TEXTURE_INTENSITY_TYPE		0x8C15
#define MGL_TEXTURE_DEPTH_TYPE			0x8C16
#define MGL_UNSIGNED_NORMALIZED		    0x8C17
//
#define	MGL_RGBA32F						0x8814
#define	MGL_RGB32F						0x8815
#define	MGL_ALPHA32F						0x8816
#define	MGL_INTENSITY32F					0x8817
#define	MGL_LUMINANCE32F					0x8818
#define	MGL_LUMINANCE_ALPHA32F			0x8819
#define	MGL_RGBA16F						0x881A
#define	MGL_RGB16F						0x881B
#define	MGL_ALPHA16F						0x881C
#define	MGL_INTENSITY16F				    0x881D
#define	MGL_LUMINANCE16F				    0x881E
#define	MGL_LUMINANCE_ALPHA16F		    0x881F

// MGL_TEXTURE_RECTANGLE_ARB
#define MGL_TEXTURE_RECTANGLE              0x84F5
#define MGL_TEXTURE_BINDING_RECTANGLE      0x84F6
#define MGL_PROXY_TEXTURE_RECTANGLE        0x84F7
#define MGL_MAX_RECTANGLE_TEXTURE_SIZE     0x84F8

// MGL_ARB_color_buffer_float.
// See also (WMGL_ARB_pixel_format_float, and GLX_ARB_fbconfig_float)
#define MGL_RGBA_FLOAT_MODE                 0x8820
#define MGL_CLAMP_VERTEX_COLOR              0x891A
#define MGL_CLAMP_FRAGMENT_COLOR            0x891B
#define MGL_CLAMP_READ_COLOR                0x891C
#define MGL_FIXED_ONLY                      0x891D

/* MGL_NV_vertex_array_range */
#define MGL_VERTEX_ARRAY_RANGE_NV			0x851D
#define MGL_VERTEX_ARRAY_RANGE_LENGTH_NV		0x851E
#define MGL_VERTEX_ARRAY_RANGE_VALID_NV		0x851F
#define MGL_MAX_VERTEX_ARRAY_RANGE_ELEMENT_NV 0x8520
#define MGL_VERTEX_ARRAY_RANGE_POINTER_NV	0x8521

/* MGL_NV_vertex_array_range2 */
#define MGL_VERTEX_ARRAY_RANGE_WITHOUT_FLUSH_NV 0x8533

/* MGL_NV_register_combiners */
#define MGL_REGISTER_COMBINERS_NV          0x8522
#define MGL_VARIABLE_A_NV                  0x8523
#define MGL_VARIABLE_B_NV                  0x8524
#define MGL_VARIABLE_C_NV                  0x8525
#define MGL_VARIABLE_D_NV                  0x8526
#define MGL_VARIABLE_E_NV                  0x8527
#define MGL_VARIABLE_F_NV                  0x8528
#define MGL_VARIABLE_G_NV                  0x8529
#define MGL_CONSTANT_COLOR0_NV             0x852A
#define MGL_CONSTANT_COLOR1_NV             0x852B
#define MGL_PRIMARY_COLOR_NV               0x852C
#define MGL_SECONDARY_COLOR_NV             0x852D
#define MGL_SPARE0_NV                      0x852E
#define MGL_SPARE1_NV                      0x852F
#define MGL_DISCARD_NV                     0x8530
#define MGL_E_TIMES_F_NV                   0x8531
#define MGL_SPARE0_PLUS_SECONDARY_COLOR_NV 0x8532
#define MGL_UNSIGNED_IDENTITY_NV           0x8536
#define MGL_UNSIGNED_INVERT_NV             0x8537
#define MGL_EXPAND_NORMAL_NV               0x8538
#define MGL_EXPAND_NEGATE_NV               0x8539
#define MGL_HALF_BIAS_NORMAL_NV            0x853A
#define MGL_HALF_BIAS_NEGATE_NV            0x853B
#define MGL_SIGNED_IDENTITY_NV             0x853C
#define MGL_SIGNED_NEGATE_NV               0x853D
#define MGL_SCALE_BY_TWO_NV                0x853E
#define MGL_SCALE_BY_FOUR_NV               0x853F
#define MGL_SCALE_BY_ONE_HALF_NV           0x8540
#define MGL_BIAS_BY_NEGATIVE_ONE_HALF_NV   0x8541
#define MGL_COMBINER_INPUT_NV              0x8542
#define MGL_COMBINER_MAPPING_NV            0x8543
#define MGL_COMBINER_COMPONENT_USAGE_NV    0x8544
#define MGL_COMBINER_AB_DOT_PRODUCT_NV     0x8545
#define MGL_COMBINER_CD_DOT_PRODUCT_NV     0x8546
#define MGL_COMBINER_MUX_SUM_NV            0x8547
#define MGL_COMBINER_SCALE_NV              0x8548
#define MGL_COMBINER_BIAS_NV               0x8549
#define MGL_COMBINER_AB_OUTPUT_NV          0x854A
#define MGL_COMBINER_CD_OUTPUT_NV          0x854B
#define MGL_COMBINER_SUM_OUTPUT_NV         0x854C
#define MGL_MAX_GENERAL_COMBINERS_NV       0x854D
#define MGL_NUM_GENERAL_COMBINERS_NV       0x854E
#define MGL_COLOR_SUM_CLAMP_NV             0x854F
#define MGL_COMBINER0_NV                   0x8550
#define MGL_COMBINER1_NV                   0x8551
#define MGL_COMBINER2_NV                   0x8552
#define MGL_COMBINER3_NV                   0x8553
#define MGL_COMBINER4_NV                   0x8554
#define MGL_COMBINER5_NV                   0x8555
#define MGL_COMBINER6_NV                   0x8556
#define MGL_COMBINER7_NV                   0x8557
/* reuse MGL_TEXTURE0_ARB */
/* reuse MGL_TEXTURE1_ARB */
/* reuse MGL_ZERO */
/* reuse MGL_NONE */
/* reuse MGL_FOG */

/* MGL_NV_primitive_restart */
#ifndef MGL_NV_primitive_restart
#define MGL_PRIMITIVE_RESTART_NV           0x8558
#define MGL_PRIMITIVE_RESTART_INDEX_NV     0x8559
#endif

/* MGL_NV_texgen_emboss */
#define MGL_EMBOSS_LIGHT_NV					0x855D
#define MGL_EMBOSS_CONSTANT_NV				0x855E
#define MGL_EMBOSS_MAP_NV					0x855F

/* EXT_texture_env_combine */
#define MGL_COMBINE_EXT                      0x8570
#define MGL_COMBINE_RGB_EXT                  0x8571
#define MGL_COMBINE_ALPHA_EXT                0x8572
#define MGL_RGB_SCALE_EXT                    0x8573
#define MGL_ADD_SIGNED_EXT                   0x8574
#define MGL_INTERPOLATE_EXT                  0x8575
#define MGL_CONSTANT_EXT                     0x8576
#define MGL_PRIMARY_COLOR_EXT                0x8577
#define MGL_PREVIOUS_EXT                     0x8578
#define MGL_SOURCE0_RGB_EXT                  0x8580
#define MGL_SOURCE1_RGB_EXT                  0x8581
#define MGL_SOURCE2_RGB_EXT                  0x8582
#define MGL_SOURCE0_ALPHA_EXT                0x8588
#define MGL_SOURCE1_ALPHA_EXT                0x8589
#define MGL_SOURCE2_ALPHA_EXT                0x858A
#define MGL_OPERAND0_RGB_EXT                 0x8590
#define MGL_OPERAND1_RGB_EXT                 0x8591
#define MGL_OPERAND2_RGB_EXT                 0x8592
#define MGL_OPERAND0_ALPHA_EXT               0x8598
#define MGL_OPERAND1_ALPHA_EXT               0x8599
#define MGL_OPERAND2_ALPHA_EXT               0x859A

/* NV_texture_env_combine4 */
#define MGL_COMBINE4_NV                      0x8503
#define MGL_SOURCE3_RGB_NV                   0x8583
#define MGL_SOURCE3_ALPHA_NV                 0x858B
#define MGL_OPERAND3_RGB_NV                  0x8593
#define MGL_OPERAND3_ALPHA_NV                0x859B

/* NV_vertex_program */
#define MGL_VERTEX_PROGRAM_NV              0x8620
#define MGL_VERTEX_STATE_PROGRAM_NV        0x8621
#define MGL_ATTRIB_ARRAY_SIZE_NV           0x8623
#define MGL_ATTRIB_ARRAY_STRIDE_NV         0x8624
#define MGL_ATTRIB_ARRAY_TYPE_NV           0x8625
#define MGL_CURRENT_ATTRIB_NV              0x8626
#define MGL_PROGRAM_LENGTH_NV              0x8627
#define MGL_PROGRAM_STRING_NV              0x8628
#define MGL_MODELVIEW_PROJECTION_NV        0x8629
#define MGL_IDENTITY_NV                    0x862A
#define MGL_INVERSE_NV                     0x862B
#define MGL_TRANSPOSE_NV                   0x862C
#define MGL_INVERSE_TRANSPOSE_NV           0x862D
#define MGL_MAX_TRACK_MATRIX_STACK_DEPTH_NV 0x862E
#define MGL_MAX_TRACK_MATRICES_NV          0x862F
#define MGL_MATRIX0_NV                     0x8630
#define MGL_MATRIX1_NV                     0x8631
#define MGL_MATRIX2_NV                     0x8632
#define MGL_MATRIX3_NV                     0x8633
#define MGL_MATRIX4_NV                     0x8634
#define MGL_MATRIX5_NV                     0x8635
#define MGL_MATRIX6_NV                     0x8636
#define MGL_MATRIX7_NV                     0x8637
#define MGL_CURRENT_MATRIX_STACK_DEPTH_NV  0x8640
#define MGL_CURRENT_MATRIX_NV              0x8641
#define MGL_VERTEX_PROGRAM_POINT_SIZE_NV   0x8642
#define MGL_VERTEX_PROGRAM_TWO_SIDE_NV     0x8643
#define MGL_PROGRAM_PARAMETER_NV           0x8644
#define MGL_ATTRIB_ARRAY_POINTER_NV        0x8645
#define MGL_PROGRAM_TARGET_NV              0x8646
#define MGL_PROGRAM_RESIDENT_NV            0x8647
#define MGL_TRACK_MATRIX_NV                0x8648
#define MGL_TRACK_MATRIX_TRANSFORM_NV      0x8649
#define MGL_VERTEX_PROGRAM_BINDING_NV      0x864A
#define MGL_PROGRAM_ERROR_POSITION_NV      0x864B
#define MGL_VERTEX_ATTRIB_ARRAY0_NV        0x8650
#define MGL_VERTEX_ATTRIB_ARRAY1_NV        0x8651
#define MGL_VERTEX_ATTRIB_ARRAY2_NV        0x8652
#define MGL_VERTEX_ATTRIB_ARRAY3_NV        0x8653
#define MGL_VERTEX_ATTRIB_ARRAY4_NV        0x8654
#define MGL_VERTEX_ATTRIB_ARRAY5_NV        0x8655
#define MGL_VERTEX_ATTRIB_ARRAY6_NV        0x8656
#define MGL_VERTEX_ATTRIB_ARRAY7_NV        0x8657
#define MGL_VERTEX_ATTRIB_ARRAY8_NV        0x8658
#define MGL_VERTEX_ATTRIB_ARRAY9_NV        0x8659
#define MGL_VERTEX_ATTRIB_ARRAY10_NV       0x865A
#define MGL_VERTEX_ATTRIB_ARRAY11_NV       0x865B
#define MGL_VERTEX_ATTRIB_ARRAY12_NV       0x865C
#define MGL_VERTEX_ATTRIB_ARRAY13_NV       0x865D
#define MGL_VERTEX_ATTRIB_ARRAY14_NV       0x865E
#define MGL_VERTEX_ATTRIB_ARRAY15_NV       0x865F
#define MGL_MAP1_VERTEX_ATTRIB0_4_NV       0x8660
#define MGL_MAP1_VERTEX_ATTRIB1_4_NV       0x8661
#define MGL_MAP1_VERTEX_ATTRIB2_4_NV       0x8662
#define MGL_MAP1_VERTEX_ATTRIB3_4_NV       0x8663
#define MGL_MAP1_VERTEX_ATTRIB4_4_NV       0x8664
#define MGL_MAP1_VERTEX_ATTRIB5_4_NV       0x8665
#define MGL_MAP1_VERTEX_ATTRIB6_4_NV       0x8666
#define MGL_MAP1_VERTEX_ATTRIB7_4_NV       0x8667
#define MGL_MAP1_VERTEX_ATTRIB8_4_NV       0x8668
#define MGL_MAP1_VERTEX_ATTRIB9_4_NV       0x8669
#define MGL_MAP1_VERTEX_ATTRIB10_4_NV      0x866A
#define MGL_MAP1_VERTEX_ATTRIB11_4_NV      0x866B
#define MGL_MAP1_VERTEX_ATTRIB12_4_NV      0x866C
#define MGL_MAP1_VERTEX_ATTRIB13_4_NV      0x866D
#define MGL_MAP1_VERTEX_ATTRIB14_4_NV      0x866E
#define MGL_MAP1_VERTEX_ATTRIB15_4_NV      0x866F
#define MGL_MAP2_VERTEX_ATTRIB0_4_NV       0x8670
#define MGL_MAP2_VERTEX_ATTRIB1_4_NV       0x8671
#define MGL_MAP2_VERTEX_ATTRIB2_4_NV       0x8672
#define MGL_MAP2_VERTEX_ATTRIB3_4_NV       0x8673
#define MGL_MAP2_VERTEX_ATTRIB4_4_NV       0x8674
#define MGL_MAP2_VERTEX_ATTRIB5_4_NV       0x8675
#define MGL_MAP2_VERTEX_ATTRIB6_4_NV       0x8676
#define MGL_MAP2_VERTEX_ATTRIB7_4_NV       0x8677
#define MGL_MAP2_VERTEX_ATTRIB8_4_NV       0x8678
#define MGL_MAP2_VERTEX_ATTRIB9_4_NV       0x8679
#define MGL_MAP2_VERTEX_ATTRIB10_4_NV      0x867A
#define MGL_MAP2_VERTEX_ATTRIB11_4_NV      0x867B
#define MGL_MAP2_VERTEX_ATTRIB12_4_NV      0x867C
#define MGL_MAP2_VERTEX_ATTRIB13_4_NV      0x867D
#define MGL_MAP2_VERTEX_ATTRIB14_4_NV      0x867E
#define MGL_MAP2_VERTEX_ATTRIB15_4_NV      0x867F

/* NV_texture_shader */
#define MGL_RGBA_UNSIGNED_DOT_PRODUCT_MAPPING_NV 0x86D9
#define MGL_UNSIGNED_INT_S8_S8_8_8_NV      0x86DA
#define MGL_UNSIGNED_INT_S8_S8_8_8_REV_NV  0x86DB
#define MGL_DSDT_MAG_INTENSITY_NV          0x86DC
#define MGL_SHADER_CONSISTENT_NV           0x86DD
#define MGL_TEXTURE_SHADER_NV              0x86DE
#define MGL_SHADER_OPERATION_NV            0x86DF
#define MGL_CULL_MODES_NV                  0x86E0
#define MGL_OFFSET_TEXTURE_2D_MATRIX_NV    0x86E1
#define MGL_OFFSET_TEXTURE_2D_SCALE_NV     0x86E2
#define MGL_OFFSET_TEXTURE_2D_BIAS_NV      0x86E3
#define MGL_PREVIOUS_TEXTURE_INPUT_NV      0x86E4
#define MGL_CONST_EYE_NV                   0x86E5
#define MGL_PASS_THROUGH_NV                0x86E6
#define MGL_CULL_FRAGMENT_NV               0x86E7
#define MGL_OFFSET_TEXTURE_2D_NV           0x86E8
#define MGL_DEPENDENT_AR_TEXTURE_2D_NV     0x86E9
#define MGL_DEPENDENT_GB_TEXTURE_2D_NV     0x86EA
#define MGL_ISOTROPIC_BRDF_NV              0x86EB
#define MGL_DOT_PRODUCT_NV                 0x86EC
#define MGL_DOT_PRODUCT_DEPTH_REPLACE_NV   0x86ED
#define MGL_DOT_PRODUCT_TEXTURE_2D_NV      0x86EE
#define MGL_DOT_PRODUCT_TEXTURE_3D_NV      0x86EF
#define MGL_DOT_PRODUCT_TEXTURE_CUBE_MAP_NV 0x86F0
#define MGL_DOT_PRODUCT_DIFFUSE_CUBE_MAP_NV 0x86F1
#define MGL_DOT_PRODUCT_REFLECT_CUBE_MAP_NV 0x86F2
#define MGL_DOT_PRODUCT_CONST_EYE_REFLECT_CUBE_MAP_NV 0x86F3
#define MGL_HILO_NV                        0x86F4
#define MGL_DSDT_NV                        0x86F5
#define MGL_DSDT_MAG_NV                    0x86F6
#define MGL_DSDT_MAG_VIB_NV                0x86F7
#define MGL_HILO16_NV                      0x86F8
#define MGL_SIGNED_HILO_NV                 0x86F9
#define MGL_SIGNED_HILO16_NV               0x86FA
#define MGL_SIGNED_RGBA_NV                 0x86FB
#define MGL_SIGNED_RGBA8_NV                0x86FC
#define MGL_SIGNED_RGB_NV                  0x86FE
#define MGL_SIGNED_RGB8_NV                 0x86FF
#define MGL_SIGNED_LUMINANCE_NV            0x8701
#define MGL_SIGNED_LUMINANCE8_NV           0x8702
#define MGL_SIGNED_LUMINANCE_ALPHA_NV      0x8703
#define MGL_SIGNED_LUMINANCE8_ALPHA8_NV    0x8704
#define MGL_SIGNED_ALPHA_NV                0x8705
#define MGL_SIGNED_ALPHA8_NV               0x8706
#define MGL_SIGNED_INTENSITY_NV            0x8707
#define MGL_SIGNED_INTENSITY8_NV           0x8708
#define MGL_DSDT8_NV                       0x8709
#define MGL_DSDT8_MAG8_NV                  0x870A
#define MGL_DSDT8_MAG8_INTENSITY8_NV       0x870B
#define MGL_SIGNED_RGB_UNSIGNED_ALPHA_NV   0x870C
#define MGL_SIGNED_RGB8_UNSIGNED_ALPHA8_NV 0x870D
#define MGL_HI_SCALE_NV                    0x870E
#define MGL_LO_SCALE_NV                    0x870F
#define MGL_DS_SCALE_NV                    0x8710
#define MGL_DT_SCALE_NV                    0x8711
#define MGL_MAGNITUDE_SCALE_NV             0x8712
#define MGL_VIBRANCE_SCALE_NV              0x8713
#define MGL_HI_BIAS_NV                     0x8714
#define MGL_LO_BIAS_NV                     0x8715
#define MGL_DS_BIAS_NV                     0x8716
#define MGL_DT_BIAS_NV                     0x8717
#define MGL_MAGNITUDE_BIAS_NV              0x8718
#define MGL_VIBRANCE_BIAS_NV               0x8719
#define MGL_TEXTURE_BORDER_VALUES_NV       0x871A
#define MGL_TEXTURE_HI_SIZE_NV             0x871B
#define MGL_TEXTURE_LO_SIZE_NV             0x871C
#define MGL_TEXTURE_DS_SIZE_NV             0x871D
#define MGL_TEXTURE_DT_SIZE_NV             0x871E
#define MGL_TEXTURE_MAG_SIZE_NV            0x871F

// MGL_ATI_texture_mirror_once
#define MGL_MIRROR_CLAMP_ATI					0x8742
#define MGL_MIRROR_CLAMP_TO_EDGE_ATI			0x8743

// WMGL_ATI_pixel_format_float related
#define MGL_RGBA_FLOAT_MODE_ATI              0x8820
#define MGL_COLOR_CLEAR_UNCLAMPED_VALUE_ATI  0x8835

// ****************************************************************************

/* For supporting the nVidia NV_float_buffer */
#define MGL_FLOAT_R_NV                       0x8880
#define MGL_FLOAT_RG_NV                      0x8881
#define MGL_FLOAT_RGB_NV                     0x8882
#define MGL_FLOAT_RGBA_NV                    0x8883
#define MGL_FLOAT_R16_NV                     0x8884
#define MGL_FLOAT_R32_NV                     0x8885
#define MGL_FLOAT_RG16_NV                    0x8886
#define MGL_FLOAT_RG32_NV                    0x8887
#define MGL_FLOAT_RGB16_NV                   0x8888
#define MGL_FLOAT_RGB32_NV                   0x8889
#define MGL_FLOAT_RGBA16_NV                  0x888A
#define MGL_FLOAT_RGBA32_NV                  0x888B
#define MGL_TEXTURE_FLOAT_COMPONENTS_NV      0x888C
#define MGL_FLOAT_CLEAR_COLOR_VALUE_NV       0x888D
#define MGL_FLOAT_RGBA_MODE_NV               0x888E

/* NV_occlusion_query */
#define MGL_PIXEL_COUNTER_BITS_NV            0x8864
#define MGL_CURRENT_OCCLUSION_QUERY_ID_NV    0x8865
#define MGL_PIXEL_COUNT_NV                   0x8866
#define MGL_PIXEL_COUNT_AVAILABLE_NV         0x8867
/* ARB_occlusion_query, superscedes NV */
#define MGL_PIXEL_COUNTER_BITS_ARB			0x8864
#define MGL_SAMPLES_PASSED_ARB				0x8914
#define MGL_CURRENT_QUERY_ARB                0x8865
#define MGL_QUERY_RESULT_ARB                 0x8866
#define MGL_QUERY_RESULT_AVAILABLE_ARB       0x8867

// ATI_pn_triangles
#define MGL_PN_TRIANGLES_ATI                             0x87F0
#define MGL_MAX_PN_TRIANGLES_TESSELATION_LEVEL_ATI       0x87F1
#define MGL_PN_TRIANGLES_POINT_MODE_ATI                  0x87F2
#define MGL_PN_TRIANGLES_NORMAL_MODE_ATI                 0x87F3
#define MGL_PN_TRIANGLES_TESSELATION_LEVEL_ATI           0x87F4
#define MGL_PN_TRIANGLES_POINT_MODE_LINEAR_ATI           0x87F5
#define MGL_PN_TRIANGLES_POINT_MODE_CUBIC_ATI            0x87F6
#define MGL_PN_TRIANGLES_NORMAL_MODE_LINEAR_ATI          0x87F7
#define MGL_PN_TRIANGLES_NORMAL_MODE_QUADRATIC_ATI		0x87F8

// EXT_vertex_shader  (ATI, Apple, Matrox, 3DLabs)
#define MGL_EXT_vertex_shader 1
#define MGL_VERTEX_SHADER_EXT								0x8780
#define MGL_VERTEX_SHADER_BINDING_EXT						0x8781
#define MGL_OP_INDEX_EXT										0x8782
#define MGL_OP_NEGATE_EXT									0x8783
#define MGL_OP_DOT3_EXT										0x8784
#define MGL_OP_DOT4_EXT										0x8785
#define MGL_OP_MUL_EXT										0x8786
#define MGL_OP_ADD_EXT										0x8787
#define MGL_OP_MADD_EXT										0x8788
#define MGL_OP_FRAC_EXT										0x8789
#define MGL_OP_MAX_EXT										0x878A
#define MGL_OP_MIN_EXT										0x878B
#define MGL_OP_SET_GE_EXT									0x878C
#define MGL_OP_SET_LT_EXT									0x878D
#define MGL_OP_CLAMP_EXT										0x878E
#define MGL_OP_FLOOR_EXT										0x878F
#define MGL_OP_ROUND_EXT										0x8790
#define MGL_OP_EXP_BASE_2_EXT								0x8791
#define MGL_OP_LOG_BASE_2_EXT								0x8792
#define MGL_OP_POWER_EXT										0x8793
#define MGL_OP_RECIP_EXT										0x8794
#define MGL_OP_RECIP_SQRT_EXT								0x8795
#define MGL_OP_SUB_EXT										0x8796
#define MGL_OP_CROSS_PRODUCT_EXT								0x8797
#define MGL_OP_MULTIPLY_MATRIX_EXT							0x8798
#define MGL_OP_MOV_EXT										0x8799
#define MGL_OUTPUT_VERTEX_EXT								0x879A
#define MGL_OUTPUT_COLOR0_EXT								0x879B
#define MGL_OUTPUT_COLOR1_EXT								0x879C
#define MGL_OUTPUT_TEXTURE_COORD0_EXT						0x879D
#define MGL_OUTPUT_TEXTURE_COORD1_EXT						0x879E
#define MGL_OUTPUT_TEXTURE_COORD2_EXT						0x879F
#define MGL_OUTPUT_TEXTURE_COORD3_EXT						0x87A0
#define MGL_OUTPUT_TEXTURE_COORD4_EXT						0x87A1
#define MGL_OUTPUT_TEXTURE_COORD5_EXT						0x87A2
#define MGL_OUTPUT_TEXTURE_COORD6_EXT						0x87A3
#define MGL_OUTPUT_TEXTURE_COORD7_EXT						0x87A4
#define MGL_OUTPUT_TEXTURE_COORD8_EXT						0x87A5
#define MGL_OUTPUT_TEXTURE_COORD9_EXT						0x87A6
#define MGL_OUTPUT_TEXTURE_COORD10_EXT						0x87A7
#define MGL_OUTPUT_TEXTURE_COORD11_EXT						0x87A8
#define MGL_OUTPUT_TEXTURE_COORD12_EXT						0x87A9
#define MGL_OUTPUT_TEXTURE_COORD13_EXT						0x87AA
#define MGL_OUTPUT_TEXTURE_COORD14_EXT						0x87AB
#define MGL_OUTPUT_TEXTURE_COORD15_EXT						0x87AC
#define MGL_OUTPUT_TEXTURE_COORD16_EXT						0x87AD
#define MGL_OUTPUT_TEXTURE_COORD17_EXT						0x87AE
#define MGL_OUTPUT_TEXTURE_COORD18_EXT						0x87AF
#define MGL_OUTPUT_TEXTURE_COORD19_EXT						0x87B0
#define MGL_OUTPUT_TEXTURE_COORD20_EXT						0x87B1
#define MGL_OUTPUT_TEXTURE_COORD21_EXT						0x87B2
#define MGL_OUTPUT_TEXTURE_COORD22_EXT						0x87B3
#define MGL_OUTPUT_TEXTURE_COORD23_EXT						0x87B4
#define MGL_OUTPUT_TEXTURE_COORD24_EXT						0x87B5
#define MGL_OUTPUT_TEXTURE_COORD25_EXT						0x87B6
#define MGL_OUTPUT_TEXTURE_COORD26_EXT						0x87B7
#define MGL_OUTPUT_TEXTURE_COORD27_EXT						0x87B8
#define MGL_OUTPUT_TEXTURE_COORD28_EXT						0x87B9
#define MGL_OUTPUT_TEXTURE_COORD29_EXT						0x87BA
#define MGL_OUTPUT_TEXTURE_COORD30_EXT						0x87BB
#define MGL_OUTPUT_TEXTURE_COORD31_EXT						0x87BC
#define MGL_OUTPUT_FOG_EXT									0x87BD
#define MGL_SCALAR_EXT										0x87BE
#define MGL_VECTOR_EXT										0x87BF
#define MGL_MATRIX_EXT										0x87C0
#define MGL_VARIANT_EXT										0x87C1
#define MGL_INVARIANT_EXT									0x87C2
#define MGL_LOCAL_CONSTANT_EXT								0x87C3
#define MGL_LOCAL_EXT										0x87C4
#define MGL_MAX_VERTEX_SHADER_INSTRUCTIONS_EXT				0x87C5
#define MGL_MAX_VERTEX_SHADER_VARIANTS_EXT					0x87C6
#define MGL_MAX_VERTEX_SHADER_INVARIANTS_EXT					0x87C7
#define MGL_MAX_VERTEX_SHADER_LOCAL_CONSTANTS_EXT			0x87C8
#define MGL_MAX_VERTEX_SHADER_LOCALS_EXT						0x87C9
#define MGL_MAX_OPTIMIZED_VERTEX_SHADER_INSTRUCTIONS_EXT		0x87CA
#define MGL_MAX_OPTIMIZED_VERTEX_SHADER_VARIANTS_EXT			0x87CB
#define MGL_MAX_OPTIMIZED_VERTEX_SHADER_INVARIANTS_EXT		0x87CC
#define MGL_MAX_OPTIMIZED_VERTEX_SHADER_LOCAL_CONSTANTS_EXT	0x87CD
#define MGL_MAX_OPTIMIZED_VERTEX_SHADER_LOCALS_EXT			0x87CE
#define MGL_VERTEX_SHADER_INSTRUCTIONS_EXT					0x87CF
#define MGL_VERTEX_SHADER_VARIANTS_EXT						0x87D0
#define MGL_VERTEX_SHADER_INVARIANTS_EXT						0x87D1
#define MGL_VERTEX_SHADER_LOCAL_CONSTANTS_EXT				0x87D2
#define MGL_VERTEX_SHADER_LOCALS_EXT							0x87D3
#define MGL_VERTEX_SHADER_OPTIMIZED_EXT						0x87D4
#define MGL_X_EXT											0x87D5
#define MGL_Y_EXT											0x87D6
#define MGL_Z_EXT											0x87D7
#define MGL_W_EXT											0x87D8
#define MGL_NEGATIVE_X_EXT									0x87D9
#define MGL_NEGATIVE_Y_EXT									0x87DA
#define MGL_NEGATIVE_Z_EXT									0x87DB
#define MGL_NEGATIVE_W_EXT									0x87DC
#define MGL_ZERO_EXT											0x87DD
#define MGL_ONE_EXT											0x87DE
#define MGL_NEGATIVE_ONE_EXT									0x87DF
#define MGL_NORMALIZED_RANGE_EXT								0x87E0
#define MGL_FULL_RANGE_EXT									0x87E1
#define MGL_CURRENT_VERTEX_EXT								0x87E2
#define MGL_MVP_MATRIX_EXT									0x87E3
#define MGL_VARIANT_VALUE_EXT								0x87E4
#define MGL_VARIANT_DATATYPE_EXT								0x87E5
#define MGL_VARIANT_ARRAY_STRIDE_EXT							0x87E6
#define MGL_VARIANT_ARRAY_TYPE_EXT							0x87E7
#define MGL_VARIANT_ARRAY_EXT								0x87E8
#define MGL_VARIANT_ARRAY_POINTER_EXT						0x87E9
#define MGL_INVARIANT_VALUE_EXT								0x87EA
#define MGL_INVARIANT_DATATYPE_EXT							0x87EB
#define MGL_LOCAL_CONSTANT_VALUE_EXT							0x87EC
#define MGL_LOCAL_CONSTANT_DATATYPE_EXT						0x87ED

// ATI_fragment_shader
#define MGL_FRAGMENT_SHADER_ATI						0x8920
#define MGL_REG_0_ATI								0x8921
#define MGL_REG_1_ATI								0x8922
#define MGL_REG_2_ATI								0x8923
#define MGL_REG_3_ATI								0x8924
#define MGL_REG_4_ATI								0x8925
#define MGL_REG_5_ATI								0x8926
#define MGL_REG_6_ATI								0x8927
#define MGL_REG_7_ATI								0x8928
#define MGL_REG_8_ATI								0x8929
#define MGL_REG_9_ATI								0x892A
#define MGL_REG_10_ATI								0x892B
#define MGL_REG_11_ATI								0x892C
#define MGL_REG_12_ATI								0x892D
#define MGL_REG_13_ATI								0x892E
#define MGL_REG_14_ATI								0x892F
#define MGL_REG_15_ATI								0x8930
#define MGL_REG_16_ATI								0x8931
#define MGL_REG_17_ATI								0x8932
#define MGL_REG_18_ATI								0x8933
#define MGL_REG_19_ATI								0x8934
#define MGL_REG_20_ATI								0x8935
#define MGL_REG_21_ATI								0x8936
#define MGL_REG_22_ATI								0x8937
#define MGL_REG_23_ATI								0x8938
#define MGL_REG_24_ATI								0x8939
#define MGL_REG_25_ATI								0x893A
#define MGL_REG_26_ATI								0x893B
#define MGL_REG_27_ATI								0x893C
#define MGL_REG_28_ATI								0x893D
#define MGL_REG_29_ATI								0x893E
#define MGL_REG_30_ATI								0x893F
#define MGL_REG_31_ATI								0x8940
#define MGL_CON_0_ATI								0x8941
#define MGL_CON_1_ATI								0x8942
#define MGL_CON_2_ATI								0x8943
#define MGL_CON_3_ATI								0x8944
#define MGL_CON_4_ATI								0x8945
#define MGL_CON_5_ATI								0x8946
#define MGL_CON_6_ATI								0x8947
#define MGL_CON_7_ATI								0x8948
#define MGL_CON_8_ATI								0x8949
#define MGL_CON_9_ATI								0x894A
#define MGL_CON_10_ATI								0x894B
#define MGL_CON_11_ATI								0x894C
#define MGL_CON_12_ATI								0x894D
#define MGL_CON_13_ATI								0x894E
#define MGL_CON_14_ATI								0x894F
#define MGL_CON_15_ATI								0x8950
#define MGL_CON_16_ATI								0x8951
#define MGL_CON_17_ATI								0x8952
#define MGL_CON_18_ATI								0x8953
#define MGL_CON_19_ATI								0x8954
#define MGL_CON_20_ATI								0x8955
#define MGL_CON_21_ATI								0x8956
#define MGL_CON_22_ATI								0x8957
#define MGL_CON_23_ATI								0x8958
#define MGL_CON_24_ATI								0x8959
#define MGL_CON_25_ATI								0x895A
#define MGL_CON_26_ATI								0x895B
#define MGL_CON_27_ATI								0x895C
#define MGL_CON_28_ATI								0x895D
#define MGL_CON_29_ATI								0x895E
#define MGL_CON_30_ATI								0x895F
#define MGL_CON_31_ATI								0x8960
#define MGL_MOV_ATI									0x8961
#define MGL_ADD_ATI									0x8963
#define MGL_MUL_ATI									0x8964
#define MGL_SUB_ATI									0x8965
#define MGL_DOT3_ATI									0x8966
#define MGL_DOT4_ATI									0x8967
#define MGL_MAD_ATI									0x8968
#define MGL_LERP_ATI									0x8969
#define MGL_CND_ATI									0x896A
#define MGL_CND0_ATI									0x896B
#define MGL_DOT2_ADD_ATI								0x896C
#define MGL_SECONDARY_INTERPOLATOR_ATI				0x896D
#define MGL_NUM_FRAGMENT_REGISTERS_ATI				0x896E
#define MGL_NUM_FRAGMENT_CONSTANTS_ATI				0x896F
#define MGL_NUM_PASSES_ATI							0x8970
#define MGL_NUM_INSTRUCTIONS_PER_PASS_ATI			0x8971
#define MGL_NUM_INSTRUCTIONS_TOTAL_ATI				0x8972
#define MGL_NUM_INPUT_INTERPOLATOR_COMPONENTS_ATI	0x8973
#define MGL_NUM_LOOPBACK_COMPONENTS_ATI				0x8974
#define MGL_COLOR_ALPHA_PAIRING_ATI					0x8975
#define MGL_SWIZZLE_STR_ATI							0x8976
#define MGL_SWIZZLE_STQ_ATI							0x8977
#define MGL_SWIZZLE_STR_DR_ATI						0x8978
#define MGL_SWIZZLE_STQ_DQ_ATI						0x8979
#define MGL_SWIZZLE_STRQ_ATI							0x897A
#define MGL_SWIZZLE_STRQ_DQ_ATI						0x897B
#define MGL_RED_BIT_ATI								0x00000001
#define MGL_GREEN_BIT_ATI							0x00000002
#define MGL_BLUE_BIT_ATI								0x00000004
#define MGL_2X_BIT_ATI								0x00000001
#define MGL_4X_BIT_ATI								0x00000002
#define MGL_8X_BIT_ATI								0x00000004
#define MGL_HALF_BIT_ATI								0x00000008
#define MGL_QUARTER_BIT_ATI							0x00000010
#define MGL_EIGHTH_BIT_ATI							0x00000020
#define MGL_SATURATE_BIT_ATI							0x00000040
#define MGL_COMP_BIT_ATI								0x00000002
#define MGL_NEGATE_BIT_ATI							0x00000004
#define MGL_BIAS_BIT_ATI								0x00000008

// ARB_vertex_program
//
#define MGL_VERTEX_PROGRAM                              0x8620
#define MGL_VERTEX_PROGRAM_POINT_SIZE                   0x8642
#define MGL_VERTEX_PROGRAM_TWO_SIDE                     0x8643
#define MGL_COLOR_SUM                                   0x8458
#define MGL_PROGRAM_FORMAT_ASCII                        0x8875
#define MGL_VERTEX_ATTRIB_ARRAY_ENABLED                 0x8622
#define MGL_VERTEX_ATTRIB_ARRAY_SIZE                    0x8623
#define MGL_VERTEX_ATTRIB_ARRAY_STRIDE                  0x8624
#define MGL_VERTEX_ATTRIB_ARRAY_TYPE                    0x8625
#define MGL_VERTEX_ATTRIB_ARRAY_NORMALIZED              0x886A
#define MGL_CURRENT_VERTEX_ATTRIB                       0x8626
#define MGL_VERTEX_ATTRIB_ARRAY_POINTER                 0x8645
#define MGL_PROGRAM_LENGTH                              0x8627
#define MGL_PROGRAM_FORMAT                              0x8876
#define MGL_PROGRAM_BINDING                             0x8677
#define MGL_PROGRAM_INSTRUCTIONS                        0x88A0
#define MGL_MAX_PROGRAM_INSTRUCTIONS                    0x88A1
#define MGL_PROGRAM_NATIVE_INSTRUCTIONS                 0x88A2
#define MGL_MAX_PROGRAM_NATIVE_INSTRUCTIONS             0x88A3
#define MGL_PROGRAM_TEMPORARIES                         0x88A4
#define MGL_MAX_PROGRAM_TEMPORARIES                     0x88A5
#define MGL_PROGRAM_NATIVE_TEMPORARIES                  0x88A6
#define MGL_MAX_PROGRAM_NATIVE_TEMPORARIES              0x88A7
#define MGL_PROGRAM_PARAMETERS                          0x88A8
#define MGL_MAX_PROGRAM_PARAMETERS                      0x88A9
#define MGL_PROGRAM_NATIVE_PARAMETERS                   0x88AA
#define MGL_MAX_PROGRAM_NATIVE_PARAMETERS               0x88AB
#define MGL_PROGRAM_ATTRIBS                             0x88AC
#define MGL_MAX_PROGRAM_ATTRIBS                         0x88AD
#define MGL_PROGRAM_NATIVE_ATTRIBS                      0x88AE
#define MGL_MAX_PROGRAM_NATIVE_ATTRIBS                  0x88AF
#define MGL_PROGRAM_ADDRESS_REGISTERS                   0x88B0
#define MGL_MAX_PROGRAM_ADDRESS_REGISTERS               0x88B1
#define MGL_PROGRAM_NATIVE_ADDRESS_REGISTERS            0x88B2
#define MGL_MAX_PROGRAM_NATIVE_ADDRESS_REGISTERS        0x88B3
#define MGL_MAX_PROGRAM_LOCAL_PARAMETERS                0x88B4
#define MGL_MAX_PROGRAM_ENV_PARAMETERS                  0x88B5
#define MGL_PROGRAM_UNDER_NATIVE_LIMITS                 0x88B6
#define MGL_PROGRAM_STRING                              0x8628
#define MGL_PROGRAM_ERROR_POSITION                      0x864B
#define MGL_CURRENT_MATRIX                              0x8641
#define MGL_TRANSPOSE_CURRENT_MATRIX                    0x88B7
#define MGL_CURRENT_MATRIX_STACK_DEPTH                  0x8640
#define MGL_MAX_VERTEX_ATTRIBS                          0x8869
#define MGL_MAX_PROGRAM_MATRICES                        0x862F
#define MGL_MAX_PROGRAM_MATRIX_STACK_DEPTH              0x862E
#define MGL_PROGRAM_ERROR_STRING                        0x8874
#define MGL_MATRIX0                                     0x88C0
#define MGL_MATRIX1                                     0x88C1
#define MGL_MATRIX2                                     0x88C2
#define MGL_MATRIX3                                     0x88C3
#define MGL_MATRIX4                                     0x88C4
#define MGL_MATRIX5                                     0x88C5
#define MGL_MATRIX6                                     0x88C6
#define MGL_MATRIX7                                     0x88C7
#define MGL_MATRIX8                                     0x88C8
#define MGL_MATRIX9                                     0x88C9
#define MGL_MATRIX10                                    0x88CA
#define MGL_MATRIX11                                    0x88CB
#define MGL_MATRIX12                                    0x88CC
#define MGL_MATRIX13                                    0x88CD
#define MGL_MATRIX14                                    0x88CE
#define MGL_MATRIX15                                    0x88CF
#define MGL_MATRIX16                                    0x88D0
#define MGL_MATRIX17                                    0x88D1
#define MGL_MATRIX18                                    0x88D2
#define MGL_MATRIX19                                    0x88D3
#define MGL_MATRIX20                                    0x88D4
#define MGL_MATRIX21                                    0x88D5
#define MGL_MATRIX22                                    0x88D6
#define MGL_MATRIX23                                    0x88D7
#define MGL_MATRIX24                                    0x88D8
#define MGL_MATRIX25                                    0x88D9
#define MGL_MATRIX26                                    0x88DA
#define MGL_MATRIX27                                    0x88DB
#define MGL_MATRIX28                                    0x88DC
#define MGL_MATRIX29                                    0x88DD
#define MGL_MATRIX30                                    0x88DE
#define MGL_MATRIX31                                    0x88DF

// ARB_vertex_buffer_object
#define MGL_ARRAY_BUFFER_ARB                             0x8892
#define MGL_ELEMENT_ARRAY_BUFFER_ARB                     0x8893
#define MGL_ARRAY_BUFFER_BINDING_ARB                     0x8894
#define MGL_ELEMENT_ARRAY_BUFFER_BINDING_ARB             0x8895
#define MGL_VERTEX_ARRAY_BUFFER_BINDING_ARB              0x8896
#define MGL_NORMAL_ARRAY_BUFFER_BINDING_ARB              0x8897
#define MGL_COLOR_ARRAY_BUFFER_BINDING_ARB               0x8898
#define MGL_INDEX_ARRAY_BUFFER_BINDING_ARB               0x8899
#define MGL_TEXTURE_COORD_ARRAY_BUFFER_BINDING_ARB       0x889A
#define MGL_EDGE_FLAG_ARRAY_BUFFER_BINDING_ARB           0x889B
#define MGL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING_ARB     0x889C
#define MGL_FOG_COORDINATE_ARRAY_BUFFER_BINDING_ARB      0x889D
#define MGL_WEIGHT_ARRAY_BUFFER_BINDING_ARB              0x889E
#define MGL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING_ARB       0x889F
#define MGL_STREAM_DRAW_ARB                              0x88E0
#define MGL_STREAM_READ_ARB                              0x88E1
#define MGL_STREAM_COPY_ARB                              0x88E2
#define MGL_STATIC_DRAW_ARB                              0x88E4
#define MGL_STATIC_READ_ARB                              0x88E5
#define MGL_STATIC_COPY_ARB                              0x88E6
#define MGL_DYNAMIC_DRAW_ARB                             0x88E8
#define MGL_DYNAMIC_READ_ARB                             0x88E9
#define MGL_DYNAMIC_COPY_ARB                             0x88EA
#define MGL_READ_ONLY_ARB                                0x88B8
#define MGL_WRITE_ONLY_ARB                               0x88B9
#define MGL_READ_WRITE_ARB                               0x88BA
#define MGL_BUFFER_SIZE_ARB                              0x8764
#define MGL_BUFFER_USAGE_ARB                             0x8765
#define MGL_BUFFER_ACCESS_ARB                            0x88BB
#define MGL_BUFFER_MAPPED_ARB                            0x88BC
#define MGL_BUFFER_MAP_POINTER_ARB                       0x88BD
// 64 bit types for buffer object
#if defined(_WIN64)
    typedef __int64 MGLintptrARB;
    typedef __int64 MGLsizeiptrARB;
#elif defined(__ia64__) || defined(__x86_64__) || defined(__APPLE__)
    typedef long int MGLintptrARB;
    typedef long int MGLsizeiptrARB;
#else
    typedef int MGLintptrARB;
    typedef int MGLsizeiptrARB;
#endif

// NV_transform_feedback
#define MGL_BACK_PRIMARY_COLOR_NV                            0x8C77
#define MGL_BACK_SECONDARY_COLOR_NV                          0x8C78
#define MGL_TEXTURE_COORD_NV                                 0x8C79
#define MGL_CLIP_DISTANCE_NV                                 0x8C7A
#define MGL_VERTEX_ID_NV                                     0x8C7B
#define MGL_PRIMITIVE_ID_NV                                  0x8C7C
#define MGL_GENERIC_ATTRIB_NV                                0x8C7D
#define MGL_TRANSFORM_FEEDBACK_ATTRIBS_NV                    0x8C7E
#define MGL_TRANSFORM_FEEDBACK_BUFFER_MODE_NV                0x8C7F
#define MGL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_NV    0x8C80
#define MGL_ACTIVE_VARYINGS_NV                               0x8C81
#define MGL_ACTIVE_VARYING_MAX_LENGTH_NV                     0x8C82
#define MGL_TRANSFORM_FEEDBACK_VARYINGS_NV                   0x8C83
#define MGL_TRANSFORM_FEEDBACK_BUFFER_START_NV               0x8C84
#define MGL_TRANSFORM_FEEDBACK_BUFFER_SIZE_NV                0x8C85
#define MGL_TRANSFORM_FEEDBACK_RECORD_NV                     0x8C86
#define MGL_PRIMITIVES_GENERATED_NV                          0x8C87
#define MGL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_NV         0x8C88
#define MGL_RASTERIZER_DISCARD_NV                            0x8C89
#define MGL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_NV 0x8C8A
#define MGL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_NV       0x8C8B
#define MGL_INTERLEAVED_ATTRIBS_NV                           0x8C8C
#define MGL_SEPARATE_ATTRIBS_NV                              0x8C8D
#define MGL_TRANSFORM_FEEDBACK_BUFFER_NV                     0x8C8E
#define MGL_TRANSFORM_FEEDBACK_BUFFER_BINDING_NV             0x8C8F

// EXT_transform_feedback
#define MGL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH_EXT         0x8C76
#define MGL_TRANSFORM_FEEDBACK_BUFFER_MODE_EXT                0x8C7F
#define MGL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS_EXT    0x8C80
#define MGL_TRANSFORM_FEEDBACK_VARYINGS_EXT                   0x8C83
#define MGL_TRANSFORM_FEEDBACK_BUFFER_START_EXT               0x8C84
#define MGL_TRANSFORM_FEEDBACK_BUFFER_SIZE_EXT                0x8C85
#define MGL_PRIMITIVES_GENERATED_EXT                          0x8C87
#define MGL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN_EXT         0x8C88
#define MGL_RASTERIZER_DISCARD_EXT                            0x8C89
#define MGL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS_EXT 0x8C8A
#define MGL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS_EXT       0x8C8B
#define MGL_INTERLEAVED_ATTRIBS_EXT                           0x8C8C
#define MGL_SEPARATE_ATTRIBS_EXT                              0x8C8D
#define MGL_TRANSFORM_FEEDBACK_BUFFER_EXT                     0x8C8E
#define MGL_TRANSFORM_FEEDBACK_BUFFER_BINDING_EXT             0x8C8F

// NVX_gpu_memory_info
#define MGL_GPU_MEMORY_INFO_DEDICATED_VIDMEM_NVX         0x9047
#define MGL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX   0x9048
#define MGL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX 0x9049
#define MGL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX           0x904A
#define MGL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX           0x904B

// ATI_meminfo
#define MGL_VBO_FREE_MEMORY_ATI          0x87FB
#define MGL_TEXTURE_FREE_MEMORY_ATI      0x87FC
#define MGL_RENDERBUFFER_FREE_MEMORY_ATI 0x87FD


//-----------------------------
// OpenGL 2.0 / OpenGL Shading Language
//
//-----------------------------

#define MGL_PROGRAM_OBJECT_ARB                       0x8B40

#define MGL_OBJECT_TYPE_ARB                          0x8B4E
#define MGL_OBJECT_SUBTYPE_ARB                       0x8B4F
#define MGL_OBJECT_DELETE_STATUS_ARB                 0x8B80
#define MGL_OBJECT_COMPILE_STATUS_ARB                0x8B81
#define MGL_OBJECT_LINK_STATUS_ARB                   0x8B82
#define MGL_OBJECT_VALIDATE_STATUS_ARB               0x8B83
#define MGL_OBJECT_INFO_LOG_LENGTH_ARB               0x8B84
#define MGL_OBJECT_ATTACHED_OBJECTS_ARB              0x8B85
#define MGL_OBJECT_ACTIVE_UNIFORMS_ARB               0x8B86
#define MGL_OBJECT_ACTIVE_UNIFORM_MAX_LENGTH_ARB     0x8B87
#define MGL_OBJECT_SHADER_SOURCE_LENGTH_ARB          0x8B88

#define MGL_SHADER_OBJECT_ARB                        0x8B48

#define MGL_FLOAT_VEC2_ARB                           0x8B50
#define MGL_FLOAT_VEC3_ARB                           0x8B51
#define MGL_FLOAT_VEC4_ARB                           0x8B52
#define MGL_INT_VEC2_ARB                             0x8B53
#define MGL_INT_VEC3_ARB                             0x8B54
#define MGL_INT_VEC4_ARB                             0x8B55
#define MGL_BOOL_ARB                                 0x8B56
#define MGL_BOOL_VEC2_ARB                            0x8B57
#define MGL_BOOL_VEC3_ARB                            0x8B58
#define MGL_BOOL_VEC4_ARB                            0x8B59
#define MGL_FLOAT_MAT2_ARB                           0x8B5A
#define MGL_FLOAT_MAT3_ARB                           0x8B5B
#define MGL_FLOAT_MAT4_ARB                           0x8B5C

typedef char         MGLcharARB;
#if defined(__APPLE__)
	typedef void *MGLhandleARB;
#else
	typedef unsigned int MGLhandleARB;
#endif

#define MGL_VERTEX_SHADER_ARB                        0x8B31

#define MGL_MAX_VERTEX_UNIFORM_COMPONENTS_ARB        0x8B4A
#define MGL_MAX_VARYING_FLOATS_ARB                   0x8B4B
#define MGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS_ARB       0x8B4C
#define MGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB     0x8B4D
#define MGL_OBJECT_ACTIVE_ATTRIBUTES_ARB             0x8B89
#define MGL_OBJECT_ACTIVE_ATTRIBUTE_MAX_LENGTH_ARB   0x8B8A

#define MGL_FRAGMENT_SHADER_ARB                      0x8B30
#define MGL_MAX_FRAGMENT_UNIFORM_COMPONENTS_ARB      0x8B49

// EXT_frame_buffer_object
#define MGL_INVALID_FRAMEBUFFER_OPERATION			0x0506
#define MGL_MAX_RENDERBUFFER_SIZE					0x84E8
#define MGL_FRAMEBUFFER_BINDING						0x8CA6
#define MGL_RENDERBUFFER_BINDING					0x8CA7
#define MGL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE		0x8CD0
#define MGL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME		0x8CD1
#define MGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL	0x8CD2
#define MGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE	0x8CD3
#define MGL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET	0x8CD4
#define MGL_FRAMEBUFFER_COMPLETE					0x8CD5
#define MGL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT		0x8CD6
#define MGL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT	0x8CD7
#define MGL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT	0x8CD8
#define MGL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS		0x8CD9
#define MGL_FRAMEBUFFER_INCOMPLETE_FORMATS			0x8CDA
#define MGL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER		0x8CDB
#define MGL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER		0x8CDC
#define MGL_FRAMEBUFFER_UNSUPPORTED					0x8CDD
#define MGL_MAX_COLOR_ATTACHMENTS					0x8CDF
#define MGL_COLOR_ATTACHMENT0						0x8CE0
#define MGL_COLOR_ATTACHMENT1						0x8CE1
#define MGL_COLOR_ATTACHMENT2						0x8CE2
#define MGL_COLOR_ATTACHMENT3          				0x8CE3
#define MGL_COLOR_ATTACHMENT4          				0x8CE4
#define MGL_COLOR_ATTACHMENT5          				0x8CE5
#define MGL_COLOR_ATTACHMENT6          				0x8CE6
#define MGL_COLOR_ATTACHMENT7          				0x8CE7
#define MGL_COLOR_ATTACHMENT8          				0x8CE8
#define MGL_COLOR_ATTACHMENT9          				0x8CE9
#define MGL_COLOR_ATTACHMENT10         				0x8CEA
#define MGL_COLOR_ATTACHMENT11         				0x8CEB
#define MGL_COLOR_ATTACHMENT12         				0x8CEC
#define MGL_COLOR_ATTACHMENT13         				0x8CED
#define MGL_COLOR_ATTACHMENT14         				0x8CEE
#define MGL_COLOR_ATTACHMENT15         				0x8CEF
#define MGL_DEPTH_ATTACHMENT           				0x8D00
#define MGL_STENCIL_ATTACHMENT         				0x8D20
#define MGL_FRAMEBUFFER                				0x8D40
#define MGL_RENDERBUFFER               				0x8D41
#define MGL_RENDERBUFFER_WIDTH         				0x8D42
#define MGL_RENDERBUFFER_HEIGHT        				0x8D43
#define MGL_RENDERBUFFER_INTERNAL_FORMAT 			0x8D44
#define MGL_STENCIL_INDEX1             				0x8D46
#define MGL_STENCIL_INDEX4             				0x8D47
#define MGL_STENCIL_INDEX8             				0x8D48
#define MGL_STENCIL_INDEX16            				0x8D49
#define MGL_RENDERBUFFER_RED_SIZE      				0x8D50
#define MGL_RENDERBUFFER_GREEN_SIZE    				0x8D51
#define MGL_RENDERBUFFER_BLUE_SIZE     				0x8D52
#define MGL_RENDERBUFFER_ALPHA_SIZE    				0x8D53
#define MGL_RENDERBUFFER_DEPTH_SIZE    				0x8D54
#define MGL_RENDERBUFFER_STENCIL_SIZE  				0x8D55
#define MGL_READ_FRAMEBUFFER						0x8CA8
#define MGL_DRAW_FRAMEBUFFER						0x8CA9

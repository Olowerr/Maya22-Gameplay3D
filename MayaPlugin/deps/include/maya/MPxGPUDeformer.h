#pragma once
// ===========================================================================
// Copyright 2020 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
//
// CLASS:    MPxGPUDeformer
//
// ****************************************************************************
//
// CLASS DESCRIPTION (MPxGPUDeformer)
//
//  MPxGPUDeformer allows the user to extend the deformerEvaluator
//  plug-in to support additional nodes with GPU computation APIs
//  such as OpenCL.
//
// ****************************************************************************

#include <maya/MEvaluationNode.h>
#include <maya/MPlug.h>
#include <maya/MOpenCLAutoPtr.h>
#include <maya/MUniqueString.h>
#include <maya/MPlugArray.h>
#include <maya/MIntArray.h>
#include <maya/MIndexMapper.h>

BEGIN_INTERNAL_CLASS_FORWARD_DECLARE
class THGPUDeformer;
END_INTERNAL_CLASS_FORWARD_DECLARE



OPENMAYA_MAJOR_NAMESPACE_OPEN

//! \ingroup OpenMayaAnim
//! \brief Helper class to keep track of CL events
/*!
    MGPUEventList is a simple class to make it easier to manage an event
    wait list for kernels that are queued up.
*/

class OPENMAYAANIM_EXPORT MGPUEventList
{
public:
    MGPUEventList();
    MGPUEventList(const MGPUEventList&);
    ~MGPUEventList();

    void add(const MAutoCLEvent& event);
    void add(MOpenCLBuffer& buf);

    const cl_event* array() const;
    cl_uint size() const;

private:
    friend MPxGPUDeformer;
    struct EventListImpl;
    EventListImpl *fImpl;
};

//! \ingroup OpenMayaAnim
//! \brief Store GPU Representation of a data buffer
/*!
    MGPUDeformerBuffer is a simple buffer structure to group data related to a single
    GPU buffer which is associated with a plug in the DG.
*/
class OPENMAYAANIM_EXPORT MGPUDeformerBuffer
{
public:
    MGPUDeformerBuffer(const MPlug& plug, const MUniqueString& name, bool readOnly, unsigned int elementSizeInBytes, unsigned int elementCount, unsigned int capacityInBytes, const MAutoCLMem& buffer, const MAutoCLEvent& event);
    MGPUDeformerBuffer();
    ~MGPUDeformerBuffer();
    MGPUDeformerBuffer(const MGPUDeformerBuffer& other);
    MGPUDeformerBuffer(MGPUDeformerBuffer&& other);
    MGPUDeformerBuffer& operator=(const MGPUDeformerBuffer& other);
    MGPUDeformerBuffer& operator=(MGPUDeformerBuffer&& other);

    MOpenCLBuffer createMOpenCLBuffer();

    bool isValid() const;

    const MUniqueString name() const;
    const MPlug plug() const;
    bool isReadOnly() const;
    unsigned int elementSizeInBytes() const;
    unsigned int elementCount() const;
    const MAutoCLMem buffer() const;
    const MAutoCLEvent bufferReadyEvent() const;
    void setBufferReadyEvent(const MAutoCLEvent&);

OPENMAYA_PRIVATE:
    MGPUDeformerBuffer(void* impl);
    void destroy();

    void *fImpl;
};

//! \ingroup OpenMayaAnim
//! \brief Store GPU Representation of geometry data
/*!
    MGPUDeformerData is the GPU representation of geometry data used in MPxGPUDeformer.
    MGPUDeformerData::setBuffer() stores an MGPUDeformerBuffer object.  getBuffer() can
    be used to retrieve this buffer by name & plug.

    Data stored in MGPUDeformerData is not owned by MGPUDeformerData, ownership remains
    with the allocator of the data and deleting an MGPUDeformerData does not automatically
    delete any associated MGPUDeformerBuffer objects.
*/
class OPENMAYAANIM_EXPORT MGPUDeformerData
{
public:
    virtual void setBuffer(const MGPUDeformerBuffer&);
    virtual MGPUDeformerBuffer getBuffer(const MUniqueString& name) const;
    virtual MGPUDeformerBuffer getBuffer(const MUniqueString& name, const MPlug& plug) const;

OPENMAYA_PRIVATE:
    MGPUDeformerData();
    MGPUDeformerData(void* impl);
    MGPUDeformerData(const MGPUDeformerData& other);
    MGPUDeformerData(MGPUDeformerData&& other);
    MGPUDeformerData& operator=(const MGPUDeformerData& other);
    MGPUDeformerData& operator=(MGPUDeformerData&& other);
    virtual ~MGPUDeformerData();

    void *fImpl;
};


// ****************************************************************************
// CLASS DECLARATION (MPxGPUDeformer)



//! \ingroup OpenMayaAnim MPx
//! \brief Base class for user defined GPU deformer override evaluators.
/*!
    MPxGPUDeformer lets you create user-defined GPU deformer overrides.  A GPU 
    deformer override replaces the CPU implementation of a deformer node when
    the evaluation manager is enabled and the deformerEvaluator plug-in is
    enabled.  Use MPxGPUDeformer to override the deformation for a Maya deformer
    or for a plug-in deformer implemented through MPxDeformerNode.  MPxGPUDeformer
    must register which node type it overrides using MGPUDeformerRegistry.

    MPxGPUDeformer defines a deformer node as a node which has input geometry
    and output geometry.  MPxGPUDeformer assumes that the number of vertices
    in the input and output geometry of a deformer node are the same.  This 
    definition includes nodes which are traditionally thought of as deformer 
    nodes, such as skinCluster or blendShape, but also includes nodes like
    groupParts, which may be part of deformation chains.

    To ensure optimal performance when you implement MPxGPUDeformer,
    keep the following in mind:
    \li Calls to the constructor must be fast.  Do not do heavy work
    in the constructor because the deformer evaluator may allocate MPxGPUDeformer
    instances which are never used.  Save heavy work for the evaluate() method.
    \li Cache needed values on the graphics card during evaluate().  Use
    the MEvaluationNode interface to determine if input values are constant or
    change over time.

    If you use this interface, you must implement the virtual method
    evaluate() for MPxGPUDeformer to function.  There are several older
    deprecated signatures of evaluate(). See the evaluate()
    documentation for additional requirements on the evaluate() method.  The
    terminate() method is optional.

    <b>About the deformer evaluator:</b>

    The deformer evaluator identifies chains of supported nodes terminated by a
    mesh.  The deformer evaluator then replaces CPU evaluation of these nodes 
    with GPGPU kernels.  The final deformed geometry is directly shared with 
    Viewport 2.0, which avoids any GPU read back.  When you implement an 
    MPxGPUDeformer for a given node type, you expand the list of deformer 
    evaluator supported nodes, which then allows more deformer chains to execute
    on the GPU.

    A deformer chain is created by identifying an animated display mesh and then
    following geometry connections upstream until source plugs, that meet any 
    one of the following criteria, is reached:
    \li On a node not supported by deformer evaluator.
    \li On a node which does not depend on time.
    \li Contains fan out connections.

    When one of the preceding conditions is true for a source plug, that source plug
    is considered an <i>input</i> to the deformation chain, and the corresponding
    source plug node is not evaluated in the deformer evaluator.

    Example Chains:
    \li HistoryNode: any node (supported or unsupported) which does not depend on time.
    \li origMesh: the original mesh shape: the ultimate source of the deformation chain.
    \li SupportedNode: a node that the deformer evaluator explicitly supports that also depends on time.
    \li UnsupportedNode: any node that the deformer evaluator does not support that also depends on time.
    \li displayMesh: the direct connection to Viewport 2.

    <b>Example 1:</b> \li HistoryNode1 -> origMesh -> HistoryNode2 -> SupportedNode1 -> SupportedNode2 -> displayMesh

    When the deformer evaluator initializes it identifies HistoryNode2.outputData
    as the source plug. The first time that the deformer evaluator runs on example 1,
    the HistoryNode2 geometry output is copied to the GPU.  SupportedNode1 and
    SupportedNode2 then run kernels to perform the deformations, and the final deformed
    result is then shared with VP2. Subsequent evaluations re-use the copy of
    HistoryNode2 output geometry already on the GPU, which avoids expensive data transfer.

    <b>Example 2:</b> \li HistoryNode1 -> origMesh -> HistoryNode2 -> UnsupportedNode1 -> SupportedNode1 -> displayMesh

    In this scenario, UnsupportedNode1 runs on the CPU and generates an intermediate
    result.  This intermediate result is copied to the GPU.  Once copied, SupportedNode1
    runs its kernel and displayMesh shares data with VP2.  The intermediate result is
    copied to the GPU every frame, resulting in slower performance.

    <b>Example 3:</b> \li HistoryNode1-> origMesh -> HistoryNode2 -> SupportedNode1 -> UnsupportedNode1 -> displayMesh

    In this scenario, the deformer evaluator may create a chain with just displayMesh in
    it, or it may do nothing.  If we performed SupportedNode1's deformation on the GPU,
    we would need to read back that data and use it as an input for UnsupportedNode1 on
    the CPU.  Read back is not supported by the deformer evaluator.  If the mesh geometry
    is large then a chain of only displayMesh may be used in order to compute mesh normals
    on the GPU.

    <b>Example 4:</b> \li origMesh1 -> SupportedNode1.outMesh[0] -> displayMesh1
				    \li origMesh2 -> SupportedNode1.outMesh[1] -> displayMesh2

    In this scenario, the deformer evaluator creates two chains, one for displayMesh1
    and a second for displayMesh2.  These chains both run on the GPU.
    Note that if SupportedNode1 is derived from MPxDeformerNode, then there can be
    zero relationship between the mesh data used in displayMesh1 and displayMesh2.
    displayMesh1 could have 100 vertices, and displayMesh2 could have one million
    vertices.

    <b>Example 5:</b> \li origMesh1 -> SupportedNode1.outMesh[0] -> displayMesh1
				    \li origMesh2 -> SupportedNode1.outMesh[1] -> UnsupportedNode1 ->displayMesh2

    In this scenario, the deformer evaluator does nothing.  We do support the first
    chain for displayMesh1, but we do not support the chain for displayMesh2.  The deformer
    evaluator does not support the partial override of a node.  In this case, SupportedNode1
    has only partial support because the deformer evaluator can override evaluation for
    outMesh[0] but not for outMesh[1].  This prevents deformer evaluator from doing
    any GPU work in this scenario.

    The deformer evaluator allocates a unique MPxGPUDeformer object for each
    supported node in each supported chain.  In Example 4, two MPxGPUDeformer
    objects are allocated for SupportedNode1, one for multi-element 0 and a second
    for multi-element 1.

    The deformer evaluator's emphasis on avoiding geometry read back from the GPU
    means that unsupported nodes that follow a deformation chain exclude that
    chain from GPU evaluation.

    <b>Example 6:</b> \li origMesh1 -> SupportedNode1.outMesh -> BlendShape.outMesh[0] -> displayMesh1
    			    \li origMesh2 -> SupportedNode2.outMesh -> BlendShape.inputTarget[0].inputTargetGroup[0].inputTargetItem[6000].inputGeomTarget

    In this scenario the blend shape node has an animated inputGeom as well as an
    animated blend shape target.  The deformer evaluator forms a single chain which includes
    SupportedNode1, SupportedNode2, BlendShape and displayMesh1.  MGPUDeformerRegistrationInfo::inputMeshAttributes()
    for the blend shape node returns both inputGeomTarget and inputGeom as attributes
    to search upstream of for additional GPU deformers.

    In this case SupportedNode1 and SupportedNode2 may run in any order, or in parallel
    with each other.  BlendShape won't run until all predecessor deformers have finished
    evaluation.

    <b>Example 7:</b> \li origMesh1 -> SupportedNode1.outMesh -> BlendShape.outMesh[0] -> displayMesh1
    			    \li origMesh2 -> UnsupportedNode1.outMesh -> BlendShape.inputTarget[0].inputTargetGroup[0].inputTargetItem[6000].inputGeomTarget

    In this scenario we have a combination of Example 2 and Example 6.  GPU Override will
    form a chain including SupportedNode1, BlendShape and displayMesh1.  When MPxGPUDeformer::evaluate()
    is called for BlendShape, inputData will include GPU buffers for BlendShape.input[0].inputGeometry and
    BlendShape.inputTarget[0].inputTargetGroup[0].inputTargetItem[6000].inputGeomTarget.  The buffers
    coming from UnsupportedNode1.outMesh will automatically be copied to the GPU every frame.
 */
class OPENMAYAANIM_EXPORT MPxGPUDeformer
{
public:
	enum DeformerStatus {
		kDeformerSuccess = 0,
		kDeformerFailure,
		kDeformerRetryMainThread,
		kDeformerPassThrough
	};

	MPxGPUDeformer();
	virtual ~MPxGPUDeformer();

	virtual DeformerStatus evaluate(MDataBlock& block, const MEvaluationNode& evaluationNode, const MPlug& outputPlug, unsigned int numElements, const MAutoCLMem, const MAutoCLEvent, MAutoCLMem, MAutoCLEvent&);
    virtual DeformerStatus evaluate(MDataBlock& block, const MEvaluationNode& evaluationNode, const MPlug& outputPlug, const MGPUDeformerData& inputData, MGPUDeformerData& outputData);
    virtual DeformerStatus evaluate(MDataBlock& block, const MEvaluationNode& evaluationNode, const MPlug& outputPlug, const MPlugArray& inputPlugs, const MGPUDeformerData& inputData, MGPUDeformerData& outputData);
    virtual void terminate();

    MGPUDeformerBuffer createOutputBuffer(const MGPUDeformerBuffer& inputBuffer);

    static bool hasAttributeBeenModified(const MEvaluationNode& evaluationNode, const MObject& attribute);
    static bool hasPlugBeenModified(const MPlug& plug);

    static MUniqueString sPositionsName();
    static MUniqueString sGeometryMatrixName();
    static MUniqueString sInverseGeometryMatrixName();
    static MUniqueString sAffectedVerticesName();

    bool getIndexMapper(MIndexMapper& imap);

    MObject getFixedSetupData(const MString& name);
    bool isFalloffWeightsDirty()const;
    static bool isFalloffWeightsDependantOnCurrentGeometry(const MEvaluationNode& evaluationNode, unsigned int multiIndex);

OPENMAYA_PRIVATE:
    friend class ::THGPUDeformer;
    void *fImpl;
};

OPENMAYA_NAMESPACE_CLOSE

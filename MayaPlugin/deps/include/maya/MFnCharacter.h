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
// CLASS:    MFnCharacter
//
// ****************************************************************************

#include <maya/MString.h>
#include <maya/MFnSet.h>
#include <maya/MObject.h>

class TsetCmd;
class Tstring;

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MFnCharacter)

//! \ingroup OpenMayaAnim MFn
//! \brief Function Set for Characters 
/*!
  Maya offers "character" nodes to simplify the setting of keyframes
  on collections of attributes. The implementation of the "character"
  is a sub-class of MFnSet taking advantage of the fact that
  attributes can be represented as MObjects and can be made members of a
  set. The fact that sets also derive from MObject means that
  characters may have other character sets as members thus
  establishing a hierarchy. Only attributes and characters can be members
  of a character set. The character node will disallow the addition of
  other objects to its set.

  Character sets are also part of a partition, meaning that membership
  of character sets cannot overlap with other character sets. Thus,
  when an attribute already in a character is added to another
  character it must be removed from the original character.

  Characters are integral to Maya's nonlinear animation system,
  "Trax".  Trax allows the user to create "animation clips", which
  bundle a set of animation curves so that they can be reused multiple
  times, with different timing then the original clip. When a clip is
  created, Maya finds the the animation curves that are attached to
  the attributes in the character set and moves those animation curves
  into the newly created clip. The MFnClip function set is the Maya
  function set for clips.

  Clips in maya can be of two types: source clips and scheduled
  clips. In the Maya UI, source clips are visible in the Visor while
  scheduled clips are visible in Trax. A source clip contains the
  animation curves for the clip. An scheduled clip contains data about
  the placement of an instance of a source clip in the Maya
  timeline. In this context, an "instance" means that the animation
  curves from the source clip are shared by the scheduled
  clip. Scheduled clips never contain their own animation curves, they
  always refer to a source clip's curves.

  For example, if you create a clip called "run" in maya that lasts
  from frames 1-20, a source clip node will be created with a start of
  1, a duration of 19, and dependency graph connections to all of the
  animation curves that make up the "run". If you then place an
  instance of the run clip at frame 5 and another instance of the run
  clip at frame 20, you have 2 scheduled clips: one with a start frame
  of 5 and one with a start frame of 20. As mentioned in the previous
  paragraph, only a single set of animation curves exist for the
  run regardless of the number of times the run is scheduled.

  Trax also allows you to create "blends" between clips, which enable you to
  control the transition between the clips. A blend is represented in the
  dependency graph by an "animBlendInOut" node, which uses an animation curve
  to determine the transition type.

  In the dependency graph, when a character has animation clips, the
  character node will always be connected to a "clipLibrary" node and
  a "clipScheduler" node. The clipLibrary node is connected to all of
  the source clips and their animation curves. The clipScheduler node
  is connected to the scheduled clips and blends. It is the clipScheduler
  that computes the final animation by looking at the placement and overlap
  of the clips and feeding the attribute data back into the character set.
*/
class OPENMAYAANIM_EXPORT MFnCharacter : public MFnSet
{
	declareMFn(MFnCharacter, MFnSet);

public:
	MStatus		attachSourceToCharacter( MObject& sourceClip,
										 MDGModifier& dgMod);
	MStatus		attachInstanceToCharacter( MObject& instanceClip,
										   MDGModifier& dgMod);
	MStatus		addCurveToClip( MObject& curve,
								MObject& sourceClip,
								MPlug& characterPlug,
								MDGModifier& dgMod);
	MObject		createBlend( MObject& instancedClip1,
							 MObject& instancedClip2,
							 MObject& blendAnimCurve,
							 MDGModifier& dgMod,
							 MStatus *ReturnStatus = NULL);
	bool		blendExists(MObject& instancedClip1,
							MObject& instancedClip2,
							MObject& blendResult);
	bool		removeBlend(MObject& instancedClip1,
							MObject& instancedClip2,
							MDGModifier& dgMod,
							MStatus* ReturnStatus = NULL);

	bool	getCharacterThatOwnsPlug(MPlug& plug, MObject& result) const;
	MStatus getMemberPlugs(MPlugArray& result) const;
	MStatus getSubCharacters(MSelectionList& result) const;
	MObject getClipScheduler(MStatus * ReturnStatus = NULL);
	int 	getScheduledClipCount(MStatus * ReturnStatus = NULL);
	MObject	getScheduledClip(int index, MStatus * ReturnStatus = NULL);
	int 	getSourceClipCount(MStatus * ReturnStatus = NULL);
	MObject	getSourceClip(int index, MStatus * ReturnStatus = NULL);
    int		getBlendCount(MStatus * ReturnStatus = NULL);
    MObject getBlend(int index, MStatus * ReturnStatus = NULL);
    MStatus getBlendClips(int index, MObject& clip1, MObject& clip2);

BEGIN_NO_SCRIPT_SUPPORT:

 	declareMFnConstConstructor( MFnCharacter, MFnSet );

END_NO_SCRIPT_SUPPORT:

protected:
			Tstring setCommandString() override;
			TsetCmd* setCommand() override;
private:
// No private members
};

OPENMAYA_NAMESPACE_CLOSE

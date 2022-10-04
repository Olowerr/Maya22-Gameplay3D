#pragma once
// ===========================================================================
// Copyright 2018 Autodesk, Inc. All rights reserved.
//
// Use of this software is subject to the terms of the Autodesk license
// agreement provided at the time of installation or download, or which
// otherwise accompanies this software in either electronic or hard copy form.
// ===========================================================================
// 

#include <maya/MTypes.h>

// ****************************************************************************
// FORWARD DECLARATIONS

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MEvaluationNodeIterator)

//! \ingroup OpenMaya
//! \sa MEvaluationNode
//! \brief Provides access to the Evaluation Manager node dirty plug list. 
/*!
	If you need to access the list of dirty plugs in an MEvaluationNode
	node then use the internal iterator:

    \code
		MEvaluationNode theNode;
		for( MEvaluationNodeIterator it = theNode.iterator(); !it.isDone(); it.next() )
		{
			doSomePlugThing( it.plug() );
		}
    \endcode
*/
class OPENMAYA_EXPORT MEvaluationNodeIterator
{
public:
	~MEvaluationNodeIterator();
	MEvaluationNodeIterator	(const MEvaluationNode& node, MStatus * ReturnStatus = NULL );
	MEvaluationNodeIterator	(const MEvaluationNodeIterator& it);
	MEvaluationNodeIterator& operator=	(MEvaluationNodeIterator& it);

	// Access the current item in the traversal
	MPlug			plug	();

	// Item by item traversal methods
	//
	bool	isDone	() const;
	void	next	();
	void	reset	();

	static const char*	className();

OPENMAYA_PRIVATE:
	const void* fDirtyPlugIterator;
};

OPENMAYA_NAMESPACE_CLOSE

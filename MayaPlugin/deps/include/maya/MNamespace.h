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
// CLASS:    MNamespace
//
// ****************************************************************************

#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MObjectArray.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MNamespace)

//! \ingroup OpenMaya
//! \brief Namespace. 
/*!
	<b>Overview</b>

	The MNamespace class contains methods for efficiently accessing Maya's
	namespace functionality. In Maya, namespaces form a packaging scheme
	for defining collections of objects. You can also have a namespace
	contain other namespaces and thus define a hierarchy. In Maya,
	namespaces are used by default with file referencing to collect all
	the objects from the given referenced file. Namespaces are also used
	for naming UI elements, and of course the user can create namespaces
	on their own to collect objects together in a logical fashion. 

	Here are some important definitions:

		\li Root Namespace: The unnamed namespace at the root of the
		    namespace hierarchy.
		\li Current Namespace: The currently selected namespace. On startup
		    and after file open and new, Maya assigns the root namespace
		    to be current.
		\li Absolute Name: An object name that is fully specified from
		    the root downwards (i.e. starts with a leading colon).
		\li Relative Name: An object name that is relative to the current
	 	    namespace. Can be enabled via MNamespace::setRelativeNames().
		\li Root-Relative Name: When relative name lookup is turned off,
	  	    virtually all name lookups in Maya are relative to the root
		    of the namespace hierarchy.

	<b>About naming rules</b>

	When specifying the name of an object in a namespace, the namespace
	name should prefix the name, separated by a colon character (":").
	There is a special namespace, the root namespace, which lives at
	the root of the namespace tree. In effect, the name of the root
	namespace is the empty string. For example, if we have the object
	"sphere" and it exists in the root namespace, we could use
	":sphere" to identify it.

	Since namespaces can be hierarchical, when completely specifying a
	name one could have several colons and namespaces names in the
	pathname. If we have the namespace ":a:b:c" that contains the object
	"sphere", the full namepath for the object would be thus:

	\code	
				:a:b:c:sphere
    \endcode

	The leading colon specifies that the namespace lookup occur from the
	root-level downwards. In effect, the namespace "a" is a child of the
	root namespace, and "b" is a child of "a", and "c" a child of "b".

	<b>The current namespace</b>

	Maya has the concept of a "current" namespace. On startup, this
	defaults to the root namespace. Some operations
	within Maya are based off the current namespace. For example, if the
	'parent' parameter is not specified to MNamespace::addNamespace()
	then the newly created namespace will be a child of the current
	namespace.


	<b>Relative name lookup</b>

	Maya actually has the concept of name lookup based off the current
	namespace as opposed to lookup based off the root-level namespace
	which is the default behaviour. In relative mode, if we had the
	object ":a:b:c:sphere" and the current namespace were ":a:b", we
	would refer to the sphere as "c:sphere". Similarly, by setting the current
	namespace to be ":a:b:c" we could then refer directly to sphere
	in an operation such as a "setAttr", e.g.

	\code	
				setAttr sphere.translateX 10;
    \endcode

	If relative mode is off, names are root-relative, thus we would
	need to refer to the sphere as follows. Note that when relative
	mode is off, Maya assumes the root namespace to base
	name lookups on:

	\code	
				setAttr a:b:c:sphere.translateX 10;
    \endcode

	Also, we can always specify an absolute namepath (one that starts with
	a leading colon). An absolute namepath will work with relative name lookup
	enabled or disabled and is thus an easy way of referring to objects in a
	way that is name lookup-independent.

	The relative mode feature is designed to allow users to write
	namespace-independent code which is intended to operate upon whatever
	namespace is current. The method MNamespace::currentNamespace() allows
	you to query the name of the current namespace.

	Relative mode can ge toggled using either MNamespace::setRelativeNames()
	or the "namespace" command.
	Turning relative mode "off" causes name lookup to be based off
	the root namespace. Continuing our example where the current namespace
	is ":a:b" to refer to the sphere we would now need to use:

	\code	
				setAttr a:b:c:sphere.translateX 10;
    \endcode

	<b>Using namespaces with the MNamespace class</b>

	Maya provides the "namespace" and "namespaceInfo" commands for dealing
	with namespaces from the command level, and there are also UI features
	which control and edit namespaces. All of these work harmoniously with
	the MNamespace class.

	It is important that any user code which exercises MNamespace methods
	that modify (rather than query) handle undo. For example, if writing a
	plug-in command that creates a new namespace, the plug-in needs to
	handle removal of the namespace on undo.

	The MNamespace class contains methods to create and remove namespaces,
	set and query the current namespace, and edit and query the
	contents of namespaces.

	To add individual objects to a namespace, use MSelectionList::add()
	which is well suited for handling multiple objects having the same
	name as well as hierarchical namespaces.
*/
class OPENMAYA_EXPORT MNamespace
{
public:
	// Operations which work on ENTIRE namespaces...
	//
	static MStatus			addNamespace(
									const MString &name,
									const MString *parent = NULL);
								
	static MString			validateName(const MString &name,
										 MStatus *ReturnStatus = NULL);								

	static MString			currentNamespace(
									MStatus *ReturnStatus = NULL );
	static MStatus			setCurrentNamespace(
									const MString &name );

	static MStringArray		getNamespaces(
									const bool recurse = false,
									MStatus *ReturnStatus = NULL );
	static MStringArray		getNamespaces(
									const MString &parentNamespace,
									const bool recurse = false,
									MStatus *ReturnStatus = NULL );

	static bool				namespaceExists(
									const MString &name,
									MStatus *ReturnStatus = NULL );

	static MString			parentNamespace(
									MStatus *ReturnStatus = NULL );

	static MStatus			removeNamespace(
									const MString &name, 
									bool 		  removeContents = false);

	static MStatus			renameNamespace(
									const MString &oldName,
									const MString &newName,
									const MString *parent = NULL);

	// Operate on the CONTENTS of namespaces...
	//
	static MObjectArray		getNamespaceObjects(
									const MString &parentNamespace,
									const bool	  recurse = false,
									MStatus *ReturnStatus = NULL );

	static MStatus			moveNamespace(
									const MString &src,
									const MString &dst,
									const bool force = false );

	// Global namespace settings and modes...
	//
	static MString			rootNamespace(
									MStatus *ReturnStatus = NULL );

	static bool				relativeNames(
									MStatus *ReturnStatus = NULL );
	static MStatus			setRelativeNames( bool newState );

    // Operate on objects full name.
    //

    //returns the namespace part from a fullname
    //i.e.: a:b:c:ball will return: "a:b:c"
    static MString          getNamespaceFromName(
                                    const MString& fullName,
                                    MStatus *ReturnStatus = NULL);

    //returns the name part from a fullname
    //i.e.: a:b:c:ball will return: "ball"
    static MString          stripNamespaceFromName(
                                    const MString& fullName,
                                    MStatus *ReturnStatus = NULL);
    
    // Utility methods...
	//
	static MString			makeNamepathAbsolute(
									const MString &,
									MStatus *ReturnStatus = NULL );

	static const char		*className();


};

OPENMAYA_NAMESPACE_CLOSE

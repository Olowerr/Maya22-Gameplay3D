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
// CLASS: MStatus
//
// ****************************************************************************

#include <maya/MTypes.h>
#include <maya/MIOStream.h> // Only <iosfwd> would be necessary but to keep backward compatibility, <maya/MIOStream.h> is still included.

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ****************************************************************************
// CLASS DECLARATION (MStatus)

//! \ingroup OpenMaya
//! \brief Manipulate Maya Status codes.
/*!
    This class facilitates API level error handling.  It encapsulates the
	status code and the internal MAYA error code as return by API functions.
	The user can query, set, print the error code along with the error
	description.
*/
class OPENMAYA_EXPORT MStatus
{
public:

	//! Available Status Codes
	enum MStatusCode
	{
		//! The operation was successful
		kSuccess = 0,
		//! The operation failed
		kFailure,
		//! The operation failed due to insufficient memory
		kInsufficientMemory,
		//! An invalid parameter was provided
		kInvalidParameter,
		//! Application is not licensed for the attempted operation
		kLicenseFailure,
		//! Returned by MPxNode::compute for unrecognised plugs
		kUnknownParameter,
		//! \nop
		kNotImplemented,
		//! \nop
		kNotFound,
		//! \nop
		kEndOfFile
	};

						MStatus();
						MStatus( MStatusCode );
						MStatus( const MStatus& );

	MStatus&			operator=( const MStatus& rhs);
	bool				operator==( const MStatus& rhs ) const;
	bool				operator==( const MStatusCode rhs ) const;
	bool				operator!=( const MStatus& rhs ) const;
	bool				operator!=( const MStatusCode rhs ) const;
	bool				error() const;
	void				clear();
	MStatusCode	        statusCode() const;
	MString				errorString() const;
BEGIN_NO_SCRIPT_SUPPORT:
	void				perror( const char * ) const;
    void				pAPIerror(const char* file, int line) const;
END_NO_SCRIPT_SUPPORT:
	void				perror( const MString& ) const;
	//! Internal use only
	void				set( bool status,
							 unsigned char statusCode,
							 unsigned char internalStatusCode);

	void				setSuccess();

BEGIN_NO_SCRIPT_SUPPORT:

	//! 	NO SCRIPT SUPPORT
	operator			bool() const
	{
		return fStatus;
	}

	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT std::ostream& operator<<( std::ostream&, MStatus&);
	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT inline bool operator==( const MStatus::MStatusCode code,
												   const MStatus& status )
	{
		return ( status.fStatusCode == code );
	}

	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT inline bool operator!=( const MStatus::MStatusCode code,
												   const MStatus& status )
	{
		return ( status.fStatusCode != code );
	}

END_NO_SCRIPT_SUPPORT:

protected:
// No protected members

OPENMAYA_PRIVATE:
	unsigned char		fStatusCode;
	unsigned char		fInternalStatusCode;
	bool				fStatus;
};

       

// Convenience macros for checking the return status from API methods.
//

//! \hideinitializer \ingroup Macros
//! \brief Return if status is not MStatus::kSuccess
/*!
  Output an error message and returns the value 'retVal' if status
  is not kSuccess.
  \param[in] _status The status code.
  \param[in] _retVal Return value when status if not kSuccess.
*/
#define CHECK_MSTATUS_AND_RETURN(_status, _retVal)		\
{ 														\
	MStatus _maya_status = (_status);					\
	if ( MStatus::kSuccess != _maya_status ) 			\
	{													\
		_maya_status.pAPIerror ( __FILE__, __LINE__);   \
		return (_retVal);								\
	}													\
}

//! \hideinitializer \ingroup Macros
//! \brief Return if status is not MStatus::kSuccess
/*!
  Output an error message and returns the status if it is not
  kSuccess.
  \param[in] _status The status code.
*/
#define CHECK_MSTATUS_AND_RETURN_IT(_status)			\
CHECK_MSTATUS_AND_RETURN((_status), (_status))

//! \hideinitializer \ingroup Macros
//! \brief Output an error message if status is not kSuccess.
/*!
  \param[in] _status The status code.
*/
#define CHECK_MSTATUS(_status)							\
{														\
	MStatus _maya_status = (_status);					\
	if ( MStatus::kSuccess != _maya_status ) 			\
	{													\
		_maya_status.pAPIerror ( __FILE__, __LINE__);   \
	}													\
}

//! \hideinitializer \ingroup Macros
//! \brief True if the status is not MStatus::kSuccess
/*!
  \param[in] _status The status code.
*/
#define MFAIL(_status)	( MStatus::kSuccess != (_status) )

/*!
	The default class constructor. It initializes the internal
	detailed status code to kSuccess.
*/
inline MStatus::MStatus()
: fStatusCode( kSuccess ),
  fInternalStatusCode( 0xff ),
  fStatus( true )
{
}

/*!
	The copy constructor of the class.  Initialize a new MStatus object with
	the values from another MStatus object.

	\param[in] status The target MStatus object.
*/
inline MStatus::MStatus( const MStatus& status )
:	fStatusCode(status.fStatusCode),
	fInternalStatusCode(status.fInternalStatusCode),
	fStatus(status.fStatus)
{
}

/*!
	The copy operator of the class.

	\param[in] rhs The MStatus object to copy from.

	\return
	A reference to the MStatus object that has been initialized.
*/
inline MStatus& MStatus::operator=( const MStatus& rhs )
{
	fStatusCode = rhs.fStatusCode;
	fInternalStatusCode = rhs.fInternalStatusCode;
	fStatus = rhs.fStatus;
	return *this;
}

/*!
	The equivalence operator that takes another MStatus object.

	\param[in] rhs A reference to the target object.

	\return
	\li <b>true</b> the two MStatus objects are equal.
	\li <b>false</b> the two MStatus objects are not equal.
*/
inline bool MStatus::operator==( const MStatus& rhs ) const
{
	return ( fStatusCode == rhs.fStatusCode );
}

/*!
	The equivalence operator that takes a MStatus::MStatusCode.

	\param[in] rhs a MStatus::MStatusCode, e.g. MS::kSuccess.

	\return
	\li <b>true</b> the object has the given detailed status code.
	\li <b>false</b> the object does not have the given detailed status code.
*/
inline bool MStatus::operator==( const MStatus::MStatusCode rhs ) const
{
	return ( fStatusCode == rhs );
}

/*!
	The not equal operator for MStatus.

	\param[in] rhs a reference to the target object for comparison.

	\return
	\li <b>true</b> the two MStatus objects are not equal.
	\li <b>false</b> the two MStatus objects are equal.
*/
inline bool MStatus::operator!=( const MStatus& rhs ) const
{
	return ( fStatusCode != rhs.fStatusCode );
}

/*!
	The not equal operator that takes a MStatus::MStatusCode.

	\param[in] rhs a MStatus::MStatusCode, e.g. MS::kSuccess.

	\return
	\li <b>true</b> the object does not have the given detailed status code.
	\li <b>false</b> the object has the given detailed status code.
*/
inline bool MStatus::operator!=( const MStatus::MStatusCode rhs ) const
{
	return ( fStatusCode != rhs );
}

/*!
	Determines whether there is an error.

	\return
	\li <b>true</b> an error has occured.
	\li <b>false</b> the operation was successful
*/
inline bool MStatus::error() const
{
	return !fStatus;
}

/*!
	Retrieve the type of error that occurred, as specified in the
	<b>MStatusCode</b> enumeration.

	\return
	The type of error that occurred.
*/
inline MStatus::MStatusCode MStatus::statusCode() const
{
	return ( MStatus::MStatusCode ) fStatusCode;
}

/*!
	The method is called interally by Maya to construct MStatus objects.
	It should not be called from plugins.

	\param[in] status true or false
	\param[in] statusCode an element of MStatusCode
	\param[in] internalStatusCode an internal Maya error code
*/
inline void MStatus::set( 
	bool status,
	unsigned char statusCode,
	unsigned char internalStatusCode)
{
	fStatus = status;
	fStatusCode = statusCode;
	fInternalStatusCode = internalStatusCode;
}

/*!
	The method is called interally by Maya to set the status as success.
	It should not be called from plugins.
*/
inline void MStatus::setSuccess()
{
	fStatus = true;
	fStatusCode = MStatus::kSuccess;
	fInternalStatusCode = 0xff;
}

/*!
	Clear error codes from the MStatus instance.  After this
	call, it will behave as if it contained MS::kSuccess.
*/
inline void MStatus::clear()
{
	fStatusCode =  kSuccess;
	fInternalStatusCode = 0xff;
	fStatus = true;
}

/*!
  \fn MStatus::operator bool() const

	The conversion operator that converts a MStatus object to bool.
	The result it returns will be true if the MStatus does not contain
	an error, and false if it does.
*/

OPENMAYA_NAMESPACE_CLOSE

// The MS typedef can cause errors when linking with
// .NET libraries on Windows.  Use the MNoMSTypedef
// define to force all status codes to be prefixed by
// MStatus:: instead of MS::.
#if !defined(MNoMSTypedef)
typedef MStatus MS;
#endif

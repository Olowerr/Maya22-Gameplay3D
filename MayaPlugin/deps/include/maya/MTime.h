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
// CLASS:    MTime
//
// ***************************************************************************

#include <maya/MTypes.h>
#include <maya/MStatus.h>

#include <stdint.h>

OPENMAYA_MAJOR_NAMESPACE_OPEN

// ***************************************************************************
// CLASS DECLARATION (MTime)

//! \ingroup OpenMaya
//!	\brief Set and retrieve animation time values in various unit systems.
/*!
The MTime class provides a fundamental type for the Maya API to hold
and manipulate animation timing information in various unit systems.
All API methods that require or return timing information do so through
variables of this type.

If one desires to manipulate time in such a way that integer changes
in an MTime instance result in integer changes in the <i>frame</i>
displayed by the timeslider, then an MTime instance should be created that
uses <i>UI</i> units.  This can be done either by using the default
constructor, or by passing the return value of the static method <i>uiUnit</i>
to the normal constructor.  Once such an MTime instance is created, its
value will be equivalent to a <i>frame</i> on the timeslider.

It should be noted that while the timeslider displays <i>frames</i>, a
seemingly unitless value, Maya internally is operating based on the
desired <i>frameRate</i> (one of those specified by the MTime::Unit enum.
It is necessary for the API programmer to be aware of this as MTime
instances are <i>not</i> unitless and allow the manipulation of time in
any desired units.
*/
class OPENMAYA_EXPORT MTime  
{
public:
	//! Time units
    OPENMAYA_ENUM(Unit,
		kInvalid,							//!< Invalid value
		kHours,                             //!< 3600 seconds
		kMinutes,                           //!< 60 seconds
		kSeconds,                           //!< 1 second
		kMilliseconds,                      //!< 1/1000 of a second
		kGames,                             //!< \deprecated Use k15FPS instead.
		k15FPS = kGames,                    //!< 15 frames per second
		kFilm,                              //!< \deprecated Use k24FPS instead.
		k24FPS = kFilm,                     //!< 24 frames per second
		kPALFrame,                          //!< \deprecated Use k25FPS instead.
		k25FPS = kPALFrame,                 //!< 25 frames per second
		kNTSCFrame,                         //!< \deprecated Use k30FPS instead.
		k30FPS = kNTSCFrame,                //!< 30 frames per second 
		kShowScan,                          //!< \deprecated Use k48FPS instead.
		k48FPS = kShowScan,                 //!< twice the speed of film (48 frames per second)
		kPALField,                          //!< \deprecated Use k50FPS instead.
		k50FPS = kPALField,                 //!< twice the speed of PAL (50 frames per second)
		kNTSCField,                         //!< \deprecated Use k60FPS instead.
		k60FPS = kNTSCField,                //!< twice the speed of NTSC (60 frames per second)
		k2FPS,								//!< 2 frames per second
		k3FPS,								//!< 3 frames per second
		k4FPS,								//!< 4 frames per second
		k5FPS,								//!< 5 frames per second
		k6FPS,								//!< 6 frames per second
		k8FPS,								//!< 8 frames per second
		k10FPS,								//!< 10 frames per second
		k12FPS,								//!< 12 frames per second
		k16FPS,								//!< 16 frames per second
		k20FPS,								//!< 20 frames per second
		k40FPS,								//!< 40 frames per second
		k75FPS,								//!< 75 frames per second
		k80FPS,								//!< 80 frames per second
		k100FPS,							//!< 100 frames per second
		k120FPS,							//!< 120 frames per second
		k125FPS,							//!< 125 frames per second
		k150FPS,							//!< 150 frames per second
		k200FPS,							//!< 200 frames per second
		k240FPS,							//!< 240 frames per second
		k250FPS,							//!< 250 frames per second
		k300FPS,							//!< 300 frames per second
		k375FPS,							//!< 375 frames per second
		k400FPS,							//!< 400 frames per second
		k500FPS,							//!< 500 frames per second
		k600FPS,							//!< 600 frames per second
		k750FPS,							//!< 750 frames per second
		k1200FPS,							//!< 1200 frames per second
		k1500FPS,							//!< 1500 frames per second
		k2000FPS,							//!< 2000 frames per second
		k3000FPS,							//!< 3000 frames per second
		k6000FPS,							//!< 6000 frames per second
		k23_976FPS,							//!< 23.976 frames per second
		k29_97FPS,							//!< 29.97 frames per second
		k29_97DF,							//!< 29.97 frames per second with DF TimeCode representation
		k47_952FPS,							//!< 47.952 frames per second
		k59_94FPS,							//!< 59.94 frames per second
		k44100FPS,							//!< 44100 frames per second
		k48000FPS,							//!< 48000 frames per second
		k90FPS,								//!< 90 frames per second
		kUserDef,							//!< user defined units (not implemented yet)
		kLast								//!< Last value, used for counting
	);

 	typedef int64_t MTick;

					MTime();
					MTime( const MTime & );
					MTime( double time_val, Unit = kFilm );
					~MTime();
 	Unit     		unit() const;
 	double   		value() const;
 	MStatus 	 	setUnit( Unit new_unit );
 	MStatus 		setValue( double new_value );

BEGIN_NO_SCRIPT_SUPPORT:
 	double    		as( Unit other_unit ) const;
END_NO_SCRIPT_SUPPORT:

    double          asUnits( Unit other_unit ) const;

	static Unit		uiUnit();
	static MStatus	setUIUnit( Unit new_unit);

	MTime&			operator =  ( const MTime& rhs );
	bool			operator == ( const MTime& rhs ) const;
	bool			operator != ( const MTime& rhs ) const;
	bool			operator <= ( const MTime& rhs ) const;
	bool			operator >= ( const MTime& rhs ) const;
	bool			operator <  ( const MTime& rhs ) const;
	bool			operator >  ( const MTime& rhs ) const;
	MTime			operator +  ( const MTime& rhs ) const;
	MTime&			operator += ( const MTime& rhs );
	MTime			operator +  ( double rhs ) const;
	MTime&			operator += ( double rhs );
	MTime			operator -  ( const MTime& rhs ) const;
	MTime&			operator -= ( const MTime& rhs );
	MTime			operator -  ( double rhs ) const;
	MTime&			operator -= ( double rhs );
	MTime			operator *  ( double rhs ) const;
	MTime&			operator *= ( double rhs );
	MTime			operator /  ( double rhs ) const;
	MTime&			operator /= ( double rhs );

BEGIN_NO_SCRIPT_SUPPORT:

	//!	NO SCRIPT SUPPORT
	MTime&			operator ++ ();
	//!	NO SCRIPT SUPPORT
	MTime&			operator ++ (int);

	//!	NO SCRIPT SUPPORT
	MTime&			operator -- ();
	//!	NO SCRIPT SUPPORT
	MTime&			operator -- (int);

	//!	NO SCRIPT SUPPORT
	friend OPENMAYA_EXPORT std::ostream&	operator << ( std::ostream& os, const MTime& t );

END_NO_SCRIPT_SUPPORT:

	static const	char* className();
	static			MTick ticksPerSecond();

protected:
	// No protected members

public:
    // for internal use ONLY
	MTime&			copy(const MTime&);

OPENMAYA_PRIVATE:
    MTime(MTick);
    MTick	val;
 	Unit	valUnit;
	void*   data;
};

OPENMAYA_NAMESPACE_CLOSE

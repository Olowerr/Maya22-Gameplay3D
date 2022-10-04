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
// CLASS:    MScriptUtil
//
// ****************************************************************************

#include <maya/MIntArray.h>
#include <maya/MFloatArray.h>
#include <maya/MUintArray.h>
#include <maya/MUint64Array.h>

#include <maya/MMatrix.h>
#include <maya/MFloatMatrix.h>

// Define some return types for the as*Ptr methods

//! Array of two ints.
typedef int Mint2[2];
//! Array of three ints.
typedef int Mint3[3];
//! Array of four ints.
typedef int Mint4[4];

//! Array of two shorts.
typedef short Mshort2[2];
//! Array of three shorts.
typedef short Mshort3[3];
//! Array of four shorts.
typedef short Mshort4[4];

//! Array of two floats.
typedef float Mfloat2[2];
//! Array of three floats.
typedef float Mfloat3[3];
//! Array of four floats.
typedef float Mfloat4[4];

//! Array of two doubles.
typedef double Mdouble2[2];
//! Array of three doubles.
typedef double Mdouble3[3];
//! Array of four doubles.
typedef double Mdouble4[4];

//! Array of two unsigned ints.
typedef unsigned int Muint2[2];
//! Array of three unsigned ints.
typedef unsigned int Muint3[3];
//! Array of four unsigned ints.
typedef unsigned int Muint4[4];

OPENMAYA_MAJOR_NAMESPACE_OPEN


// ****************************************************************************
// CLASS DECLARATION (MScriptUtil)

//! \ingroup OpenMaya
//! \brief Utility class for working with pointers and references in Python. 
/*!

  Many of Maya's API methods require that one or more of their parameters
  be passed as pointers or references. Their return values, too, can be
  pointers or references.

  In Python parameters of class types are passed by reference but parameters
  of simple types, like integers and floats, are passed by value, making it
  impossible to call those API methods from Python.  The MScriptUtil class
  bridges this gap by providing methods which return pointers to values of
  simple types and which can extract values from such pointers. These pointers
  can also be used wherever an API method requires a reference to a simple type
  or an array of a simple type.

  For example, MTransformationMatrix::setShear() requires as its first parameter
  an array of three values of simple type 'double'. To call setShear() from Python
  requires using MScriptUtil to create the array of doubles:

  \code
  matrix = maya.OpenMaya.MTransformationMatrix()
  util = maya.OpenMaya.MScriptUtil()
  util.createFromDouble(1.0, 2.0, 3.0)
  ptr = util.asDoublePtr()
  m.setShear(ptr, maya.OpenMaya.MSpace.kObject)
  \endcode

  Similar code is required to get the shear value using
  MTransformationMatrix::getShear(), but MScriptUtil methods
  must also be used to extract the returned values from the array:

  \code
  util = maya.OpenMaya.MScriptUtil()
  util.createFromDouble(0.0, 0.0, 0.0)
  ptr = util.asDoublePtr()
  matrix.getShear(ptr, maya.OpenMaya.MSpace.kObject)

  shearX = util.getDoubleArrayItem(ptr, 0)
  shearY = util.getDoubleArrayItem(ptr, 1)
  shearZ = util.getDoubleArrayItem(ptr, 2)
  \endcode

  If a method requires a reference or pointer to an enumerated value, use
  a pointer to a short int instead.

  An MScriptUtil object keeps two sets of values internally: its \e initial values, and
  its \e working values. The initial values are those supplied either in the constructor
  or by calling one of the object's create*() methods. The working values are those
  to which the as*Ptr() methods return pointers.
  
  Each time a create*() method is called it completely replaces the old
  \e initial values with the new ones. The as*() methods (asInt(), asFloat(),
  etc) but \b not the as*Ptr() methods, all return the first internal value,
  converted to the appropriate type.

  Each time an as*Ptr() method is called it completely replaces the old
  \e working values with new ones of the requested type and initializes them
  from the initial values. If the type of the working values does not match that
  of the initial values then appropriate conversions are done. For example, if
  you have initialized an MScriptUtil object with four doubles via a call to
  createFromDouble(), then a subsequent call to asBoolPtr() will allocate space
  for four boolean working values and initialize them from the initial
  values by converting non-zero values to true and zero values to false.

  The separation of initial and working values means that changes to the working
  values will not affect the initial values. For example, if you pass the pointer
  returned by asBoolPtr() to an API method which changes the working value
  it points to, the object's initial value will remain unchanged and its asInt()
  method will continue to return the same value as it did before the API call.

  The number of working values returned by the as*Ptr() methods will match
  the number of initial values. Thus it is important that you provide a sufficient
  number of initial values before calling an as*Ptr() method. If no initial values
  are provided in the MScriptUtil constructor and none are subsequently supplied
  by calls to the create*() methods, then the pointers returned by the as*Ptr()
  methods won't have room to store even a single value, which will likely lead
  to errors.

  As already noted, each call to one of an object's as*Ptr() methods completely
  replaces the old working values with new ones, thus rendering invalid any pointers
  previously returned by that object.  This means that if you need multiple
  pointers for a single API call, you will need multiple MScriptUtil
  objects. MFnMesh::getUV() provides an example of this:

  \code
  meshFn = maya.OpenMaya.MFnMesh(node)

  u_util = maya.OpenMaya.MScriptUtil(0.0)
  u_ptr = u_util.asFloatPtr()
  v_util = maya.OpenMaya.MScriptUtil(0.0)
  v_ptr = v_util.asFloatPtr()

  meshFn.getUV(0, u_ptr, v_ptr)

  u = u_util.getFloat(u_ptr)
  v = v_util.getFloat(v_ptr)
  \endcode

  When an MScriptUtil object is destroyed any pointers to its data immediately
  become invalid. Thus the following code will fail because the MScriptUtil objects
  created by getUVPtrs() will go out of scope and be destroyed when the function
  returns, rendering the pointers it returns invalid:

  \code
  # WRONG!
  def getUVPtrs():
      u_util = maya.OpenMaya.MScriptUtil(0.0)
      u_ptr = u_util.asFloatPtr()
      v_util = maya.OpenMaya.MScriptUtil(0.0)
      v_ptr = v_util.asFloatPtr()
      return [u_ptr, v_ptr]

  uvPtrs = getUVPtrs()
  meshFn.getUV(0, uvPtrs[0], uvPtrs[1])
  \endcode

  To work, getUVPtrs() would have to preserve the MScriptUtil objects in some way,
  such as passing them back to the caller as well:

  \code
  # RIGHT!
  def getUVPtrs():
      u_util = maya.OpenMaya.MScriptUtil(0.0)
      u_ptr = u_util.asFloatPtr()
      v_util = maya.OpenMaya.MScriptUtil(0.0)
      v_ptr = v_util.asFloatPtr()
      return [(u_ptr, u_util), (v_ptr, v_util)]

  uvPtrs = getUVPtrs()
  meshFn.getUV(0, uvPtrs[0][0], uvPtrs[1][0])
  \endcode

  This class is admittedly cumbersome to use but it provides a way of building
  parameters and accessing return values for methods which would not otherwise
  be accessible from Python.
*/
class OPENMAYA_EXPORT MScriptUtil
{
public:

	MScriptUtil();
	~MScriptUtil();

	MScriptUtil( int value );
	MScriptUtil( short value );
	MScriptUtil( float value );
	MScriptUtil( double value );
	MScriptUtil( unsigned int value );
	MScriptUtil( bool value );

	MScriptUtil( const int* value );
	MScriptUtil( const short* value );
	MScriptUtil( const float* value );
	MScriptUtil( const double* value );
	MScriptUtil( const unsigned int* value );
	MScriptUtil( const bool* value );

	MScriptUtil( const MIntArray& array );
	MScriptUtil( const MDoubleArray& array );
	MScriptUtil( const MUintArray& array );
	MScriptUtil( const MUint64Array& array );

	void createFromInt( int x, int y=0, int z=0, int w=0 );
	void createFromDouble( double x, double y=0, double z=0, double w=0 );

	bool createFromList( void *pythonList, unsigned int length );

	int asInt();
	short asShort();
	float asFloat();
	double asDouble();
	unsigned int asUint();
	bool asBool();

	int *asIntPtr();
	short *asShortPtr();
	unsigned short *asUshortPtr();
	float *asFloatPtr();
	double *asDoublePtr();
	unsigned int *asUintPtr();
	bool *asBoolPtr();
	char *asCharPtr();
	unsigned char *asUcharPtr();

	Mint2 *asInt2Ptr();
	Mint3 *asInt3Ptr();
	Mint4 *asInt4Ptr();

	Mshort2 *asShort2Ptr();
	Mshort3 *asShort3Ptr();
	Mshort4 *asShort4Ptr();

	Mfloat2 *asFloat2Ptr();
	Mfloat3 *asFloat3Ptr();
	Mfloat4 *asFloat4Ptr();

	Mdouble2 *asDouble2Ptr();
	Mdouble3 *asDouble3Ptr();
	Mdouble4 *asDouble4Ptr();

	Muint2 *asUint2Ptr();
	Muint3 *asUint3Ptr();
	Muint4 *asUint4Ptr();

	static void setInt( int& var, int value );
	static void setShort( short& var, int value  );
	static void setFloat( float& var, double value );
	static void setDouble( double& var, double value );
	static void setUint( unsigned int& var, int value  );
	static void setBool( bool& var, int value  );
	static void setChar( char& var, int value  );
	static void setUchar( unsigned char& var, int value  );

	static int getInt( int& var );
	static int getShort( short& var );
	static double getFloat( float& var );
	static double getDouble( double& var );
	static int getUint( unsigned int& var );
	static int getBool( bool& var );
	static int getChar( char& var );
	static int getUchar( unsigned char& var );

	static bool setIntArray( int* var, unsigned int index, int value );
	static bool setShortArray( short* var, unsigned int index, int value  );
	static bool setFloatArray( float* var, unsigned int index, double value );
	static bool setDoubleArray( double* var, unsigned int index, double value );
	static bool setUintArray( unsigned int* var, unsigned int index, int value  );
	static bool setUshortArray( unsigned short* var, unsigned int index, int value );
	static bool setBoolArray( bool* var, unsigned int index, int value  );
	static bool setCharArray( char* var, unsigned int index, int value  );
	static bool setUcharArray( unsigned char* var, unsigned int index, int value  );

	static int getIntArrayItem( int* var, unsigned int index );
	static int getShortArrayItem( short* var, unsigned int index  );
	static double getFloatArrayItem( float* var, unsigned int index );
	static double getDoubleArrayItem( double* var, unsigned int index );
	static int getUintArrayItem( unsigned int* var, unsigned int index  );
	static int getUshortArrayItem( unsigned short* var, unsigned int index );
	static int getBoolArrayItem( bool* var, unsigned int index  );
	static int getCharArrayItem( char* var, unsigned int index  );
	static int getUcharArrayItem( unsigned char* var, unsigned int index  );

	static bool createMatrixFromList( void *pythonList, MMatrix& matrix );
	static bool createFloatMatrixFromList( void *pythonList, MFloatMatrix& matrix );

	static bool createIntArrayFromList( void *pythonList, MIntArray& array );
	static bool createFloatArrayFromList( void *pythonList, MFloatArray& array );

	static int getInt2ArrayItem( int (*var)[2], unsigned int r, unsigned int c);
	static bool setInt2ArrayItem( int (*var)[2], unsigned int r, unsigned int c, int value );
	static int getInt3ArrayItem( int (*var)[3], unsigned int r, unsigned int c);
	static bool setInt3ArrayItem( int (*var)[3], unsigned int r, unsigned int c, int value );
	static int getInt4ArrayItem( int (*var)[4], unsigned int r, unsigned int c);
	static bool setInt4ArrayItem( int (*var)[4], unsigned int r, unsigned int c, int value );

	static short getShort2ArrayItem( short (*var)[2], unsigned int r, unsigned int c);
	static bool setShort2ArrayItem( short (*var)[2], unsigned int r, unsigned int c, short value );
	static short getShort3ArrayItem( short (*var)[3], unsigned int r, unsigned int c);
	static bool setShort3ArrayItem( short (*var)[3], unsigned int r, unsigned int c, short value );
	static short getShort4ArrayItem( short (*var)[4], unsigned int r, unsigned int c);
	static bool setShort4ArrayItem( short (*var)[4], unsigned int r, unsigned int c, short value );

	static float getFloat2ArrayItem( float (*var)[2], unsigned int r, unsigned int c);
	static bool setFloat2ArrayItem( float (*var)[2], unsigned int r, unsigned int c, float value );
	static float getFloat3ArrayItem( float (*var)[3], unsigned int r, unsigned int c);
	static bool setFloat3ArrayItem( float (*var)[3], unsigned int r, unsigned int c, float value );
	static float getFloat4ArrayItem( float (*var)[4], unsigned int r, unsigned int c);
	static bool setFloat4ArrayItem( float (*var)[4], unsigned int r, unsigned int c, float value );

	static double getDouble2ArrayItem( double (*var)[2], unsigned int r, unsigned int c);
	static bool setDouble2ArrayItem( double (*var)[2], unsigned int r, unsigned int c, double value );
	static double getDouble3ArrayItem( double (*var)[3], unsigned int r, unsigned int c);
	static bool setDouble3ArrayItem( double (*var)[3], unsigned int r, unsigned int c, double value );
	static double getDouble4ArrayItem( double (*var)[4], unsigned int r, unsigned int c);
	static bool setDouble4ArrayItem( double (*var)[4], unsigned int r, unsigned int c, double value );

	static unsigned int getUint2ArrayItem( unsigned int (*var)[2], unsigned int r, unsigned int c);
	static bool setUint2ArrayItem( unsigned int (*var)[2], unsigned int r, unsigned int c, unsigned int value );
	static unsigned int getUint3ArrayItem( unsigned int (*var)[3], unsigned int r, unsigned int c);
	static bool setUint3ArrayItem( unsigned int (*var)[3], unsigned int r, unsigned int c, unsigned int value );
	static unsigned int getUint4ArrayItem( unsigned int (*var)[4], unsigned int r, unsigned int c);
	static bool setUint4ArrayItem( unsigned int (*var)[4], unsigned int r, unsigned int c, unsigned int value );

protected:
// No protected members
private:
	MDoubleArray _data;
	MUint64Array _data64;
	char* _ptr;
};

OPENMAYA_NAMESPACE_CLOSE

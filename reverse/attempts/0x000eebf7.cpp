// ?addProp@W3DPropBuffer@@QAEXHUCoord3D@@MMABVAsciiString@@_N@Z
// partial score=0.9897452314259036 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?addProp@W3DPropBuffer@@QAEXHUCoord3D@@MMABVAsciiString@@_N@Z
// partial score=0.89 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /ICode/Libraries/Include/Lib /MD /EHsc /DNDEBUG
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// W3DPropBuffer::addPropType and addProp, ported from Zero Hour's
// GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBuffer.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference) onto the BFME 2
// layout. The ZH layout holds: TProp is 0x30 bytes at +0x04 (m_robj, id,
// location, propType, ss, visible, bounds), m_numProps +0x2EE04,
// m_initialized +0x2EE09, TPropType 0x18 bytes at +0x2EE18 (m_robj,
// m_robjName, m_bounds), m_numPropTypes +0x2F718, MAX_PROPS 4000 and
// MAX_TYPES 96.
//
// BFME 2 differences: both take one more flag (cleared, it zeroes byte +0xBD
// of the new type's render object), addProp first checks a TheGlobalData
// flag at +0x1C, and new props start visible.

typedef int Int;
typedef bool Bool;
typedef float Real;

extern "C" double __cdecl cos( double x );
extern "C" double __cdecl sin( double x );
inline float cosf( float x ) { return (float)cos( (double)x ); }
inline float sinf( float x ) { return (float)sin( (double)x ); }

#include "ascii_string.h"

#include "Coord3D.h"
class Vector3
{
public:
	__forceinline Vector3( float x, float y, float z ) { X = x; Y = y; Z = z; }
	__forceinline Vector3( const Vector3 &v ) { X = v[0]; Y = v[1]; Z = v[2]; }
	__forceinline Vector3 &operator = ( const Vector3 &v ) { X = v[0]; Y = v[1]; Z = v[2]; return *this; }
	float &operator [] ( int i ) { return (&X)[i]; }
	const float &operator [] ( int i ) const { return (&X)[i]; }
	__forceinline Vector3 &operator += ( const Vector3 &v ) { X += v.X; Y += v.Y; Z += v.Z; return *this; }
	float X;
	float Y;
	float Z;
};

class Vector4
{
public:
	__forceinline void Set( float x, float y, float z, float w ) { X = x; Y = y; Z = z; W = w; }
	float &operator [] ( int i ) { return (&X)[i]; }
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline explicit Matrix3D( bool init ) { if (init) Make_Identity(); }
	__forceinline void Make_Identity( void )
	{
		Row[0].Set(1.0f,0.0f,0.0f,0.0f);
		Row[1].Set(0.0f,1.0f,0.0f,0.0f);
		Row[2].Set(0.0f,0.0f,1.0f,0.0f);
	}
	__forceinline void Rotate_Z( float theta )
	{
		float tmp1,tmp2;
		float c; float s;

		c = cosf(theta);
		_ReadWriteBarrier();
		double sinValue=sin((double)theta); s=(float)sinValue;

		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( c*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
	}
	__forceinline void Scale( float scale )
	{	// uniform scale all 3 axis
		// X
		Row[0][0] *= scale;
		Row[1][0] *= scale;
		Row[2][0] *= scale;
		// Y
		Row[0][1] *= scale;
		Row[1][1] *= scale;
		Row[2][1] *= scale;
		// Z
		Row[0][2] *= scale;
		Row[1][2] *= scale;
		Row[2][2] *= scale;
	}
	__forceinline void Set_Translation( const Vector3 &t ) { Row[0][3] = t[0]; Row[1][3] = t[1];Row[2][3] = t[2]; }
private:
	Vector4 Row[3];
};

class SphereClass
{
public:
	Vector3 Center;
	float Radius;
};

// BFME 2 RenderObjClass slots used here (vftable 0x00BD2F68).
class RenderObjClass
{
public:
	virtual void v00();
	virtual void v01();
	virtual RenderObjClass *Clone( void ) const;															///< slot 2
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void Set_Transform( const Matrix3D &m );													///< slot 21
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
	virtual void v46();
	virtual void v47();
	virtual void v48();
	virtual void v49();
	virtual void v50();
	virtual void v51();
	virtual void v52();
	virtual void v53();
	virtual void v54();
	virtual void v55();
	virtual void v56();
	virtual void v57();
	virtual void v58();
	virtual void v59();
	virtual void v60();
	virtual void v61();
	virtual void v62();
	virtual void v63();
	virtual void v64();
	virtual const SphereClass &Get_Bounding_Sphere( void ) const;						///< slot 65
	virtual void v66();
	virtual void v67();
	virtual void v68();
	virtual void v69();
	virtual void v70();
	virtual void v71();
	virtual void v72();
	virtual void v73();
	virtual void v74();
	virtual void v75();
	virtual void v76();
	virtual void v77();
	virtual void v78();
	virtual void v79();
	virtual void v80();
	virtual void v81();
	virtual void v82();
	virtual void v83();
	virtual void v84();
	virtual void v85();
	virtual void v86();
	virtual void v87();
	virtual void v88();
	virtual void v89();
	virtual void v90();
	virtual void v91();
	virtual void v92();
	virtual void Set_ObjectScale( float scale );															///< slot 93

	char m_unrecovered04[ 0xBD - 0x04 ];
	Bool m_bfmePropFlagBD;																										///< 0xBD
};

RenderObjClass *Create_Render_Obj( const char *name );

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID
};

struct GlobalData
{
	char m_unrecovered00[ 0x1C ];
	Bool m_bfmeGlobal1C;																											///< 0x1C
};
extern GlobalData *TheGlobalData;

struct TProp
{
	RenderObjClass *m_robj;
	Int id;
	Coord3D location;
	Int propType;
	ObjectShroudStatus ss;
	Bool visible;
	SphereClass bounds;
};

struct TPropType
{
	RenderObjClass *m_robj;
	AsciiString m_robjName;
	SphereClass m_bounds;
};

class W3DPropBuffer
{
public:
	virtual ~W3DPropBuffer( void );
	void addProp( Int id, Coord3D location, Real angle, Real scale, const AsciiString &modelName, Bool bfmeFlag );
	Int addPropType( const AsciiString &modelName, Bool bfmeFlag );

protected:
	enum { MAX_PROPS=4000};
	enum {MAX_TYPES = 96};

	TProp	m_props[MAX_PROPS];			///< The prop buffer.  All props are stored here.
	Int			m_numProps;						///< Number of props in m_props.
	Bool		m_anythingChanged;	///< Set to true if visibility or sorting changed.
	Bool		m_initialized;		///< True if the subsystem initialized.
	Bool		m_doCull;
	char		m_unrecovered2EE0B[ 0x2EE18 - 0x2EE0B ];
	TPropType m_propTypes[MAX_TYPES];	///< Info about a kind of prop.
	Int			m_numPropTypes;						///< Number of entries in m_propTypes.
};

//=============================================================================
// W3DPropBuffer::addPropType
//=============================================================================
/** Adds a type of prop (model & texture).  */
//=============================================================================
void W3DPropBuffer::addProp(Int id, Coord3D location, Real angle,Real scale, const AsciiString &modelName, Bool bfmeFlag)
{
	if (!TheGlobalData->m_bfmeGlobal1C) {
		return;
	}
	if (m_numProps >= MAX_PROPS) {
		return;
	}
	if (!m_initialized) {
		return;
	}
	Int propType = -1;
	Int i;
	for (i=0; i<m_numPropTypes; i++) {
		if (m_propTypes[i].m_robjName.compareNoCase(modelName)==0) {
			propType = i;
			break;
		}
	}
	if (propType<0) {
		propType = addPropType(modelName, bfmeFlag);
		if (propType<0) {
			return;
		}
	}

	Matrix3D mtx(true);
	mtx.Rotate_Z(angle);
	mtx.Scale(scale);
	mtx.Set_Translation(Vector3(location.x, location.y, location.z));

	m_props[m_numProps].location = location;
	m_props[m_numProps].id = id;
	m_props[m_numProps].ss = OBJECTSHROUD_INVALID;
	m_props[m_numProps].m_robj = m_propTypes[propType].m_robj->Clone();
	m_props[m_numProps].m_robj->Set_Transform(mtx);
	m_props[m_numProps].m_robj->Set_ObjectScale(scale);
	m_props[m_numProps].propType = propType;
	// Translate the bounding sphere of the model.
	m_props[m_numProps].bounds = m_propTypes[propType].m_bounds;
	m_props[m_numProps].bounds.Center += Vector3(location.x, location.y, location.z);
	// BFME 2: new props start visible.
	m_props[m_numProps].visible = true;

	m_numProps++;
}

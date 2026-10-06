// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
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

// W3DPropBuffer::addPropType, ported from Zero Hour's
// GameEngineDevice/Source/W3DDevice/GameClient/W3DPropBuffer.cpp (GeneralsMD
// tree vendored under reference/open-bfme-1/inputs/reference) onto the BFME 2
// layout. The ZH layout holds: TProp is 0x30 bytes at +0x04 (m_robj, id,
// location, propType, ss, visible, bounds), m_numProps +0x2EE04,
// m_initialized +0x2EE09, TPropType 0x18 bytes at +0x2EE18 (m_robj,
// m_robjName, m_bounds), m_numPropTypes +0x2F718, MAX_PROPS 4000 and
// MAX_TYPES 96.
//
// BFME 2 takes one more flag (cleared, it zeroes byte +0xBD of the new type's
// render object). The bounding-sphere copy inlines the WWMath Vector3 copy.

typedef int Int;
typedef bool Bool;
typedef float Real;

#include "ascii_string.h"

#include "../../../../Libraries/Include/Lib/Coord3D.h"

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
	virtual void v02();
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
	virtual void v21();
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

	char m_unrecovered04[ 0xBD - 0x04 ];
	Bool m_bfmePropFlagBD;																										///< 0xBD
};

RenderObjClass *Create_Render_Obj( const char *name );

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID
};

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
Int W3DPropBuffer::addPropType(const AsciiString &modelName, Bool bfmeFlag)
{
	if (m_numPropTypes>=MAX_TYPES) {
		return 0;
	}

	m_propTypes[m_numPropTypes].m_robj = Create_Render_Obj(modelName.str());
	if (m_propTypes[m_numPropTypes].m_robj==0) {
		return -1;
	}
	if (!bfmeFlag) {
		m_propTypes[m_numPropTypes].m_robj->m_bfmePropFlagBD = false;
	}
	m_propTypes[m_numPropTypes].m_robjName = modelName;

	SphereClass bounds = m_propTypes[m_numPropTypes].m_robj->Get_Bounding_Sphere();
	m_propTypes[m_numPropTypes].m_bounds = bounds;
	m_numPropTypes++;
	return m_numPropTypes-1;
}

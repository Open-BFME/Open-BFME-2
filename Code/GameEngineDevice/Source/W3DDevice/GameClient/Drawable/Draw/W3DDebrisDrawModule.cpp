// cl: /MD /EHsc /DNDEBUG
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

// W3DDebrisDraw::doDrawModule, ported from Zero Hour's GameEngineDevice/
// Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDraw.cpp (GeneralsMD tree
// vendored under reference/open-bfme-1/inputs/reference) onto the BFME 2
// layout, together with the Thing::isAboveTerrain inline it emits.
//
// BFME 2 layout (constructor 0x000B1C41, reactToTransformChange 0x000B1A14):
// drawable +0x08, m_renderObject +0x24, m_anims[3] +0x28, m_fxFinal +0x34,
// m_state +0x38, m_frames +0x3C, m_finalStop +0x40. The drawable keeps its
// object at +0xFC and its instance scale at +0x200. BFME 2's static
// FXList::doFXPos has lost ZH's trailing override radius and doDrawModule
// null-checks m_fxFinal. Drawable::getPosition is out of line in BFME 2: the
// interpolating getter at 0x002763E6 (rowed from its BFME 1 donor as
// BFMERopeDrawable::getPosition).

typedef int Int;
typedef bool Bool;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Vector4
{
public:
	__forceinline Vector4 &operator = ( const Vector4 &v ) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	float &operator [] ( int i ) { return (&X)[i]; }
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	Matrix3D( void ) {}
	__forceinline Matrix3D &operator = ( const Matrix3D &m )
	{
		Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2];
		return *this;
	}
	void Scale( float scale )
	{
		Row[0][0] *= scale; Row[1][0] *= scale; Row[2][0] *= scale;
		Row[0][1] *= scale; Row[1][1] *= scale; Row[2][1] *= scale;
		Row[0][2] *= scale; Row[1][2] *= scale; Row[2][2] *= scale;
	}
private:
	Vector4 Row[3];
};

class HAnimClass;

// BFME 2 RenderObjClass slots used here (vftable 0x00BD2F68).
class RenderObjClass
{
public:
	enum { CLASSID_HLOD = 0x19 };
	enum AnimMode
	{
		ANIM_MODE_MANUAL = 0,
		ANIM_MODE_LOOP,
		ANIM_MODE_ONCE,
	};
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual int Class_ID( void ) const;																				///< slot 3
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
	virtual void Set_Animation( HAnimClass *motion, float frame, int anim_mode = ANIM_MODE_MANUAL );	///< slot 45
	virtual void v46();
	virtual HAnimClass *Peek_Animation( void );																///< slot 47
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
	virtual void v65();
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
	virtual void v94();
	virtual void v95();
	virtual void v96();
	virtual void v97();
	virtual void v98();
	virtual void v99();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual void v111();
	virtual void v112();
	virtual void v113();
	virtual void v114();
	virtual void v115();
	virtual void v116();
	virtual void v117();
	virtual void v118();
	virtual void v119();
	virtual void v120();
	virtual void v121();
	virtual void v122();
	virtual void v123();
	virtual void v124();
	virtual void v125();
	virtual void v126();
	virtual void v127();
	virtual void v128();
};

// BFME 2 HLodClass (Animatable3DObjClass) makes Is_Animation_Complete a
// virtual at slot 131 of its table.
class HLodClass : public RenderObjClass
{
public:
	virtual void v129();
	virtual void v130();
	virtual bool Is_Animation_Complete( void ) const;													///< slot 131
};

class FXList
{
public:
	static void doFXPos( const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx, const Real primarySpeed, const Coord3D *secondary );
};

class Thing
{
public:
	Real getHeightAboveTerrain( void ) const;
	Bool isAboveTerrain( void ) const { return getHeightAboveTerrain() > 0.0f; }
};

class Object : public Thing
{
};

class Drawable
{
public:
	Object *getObject( void ) { return m_object; }
	const Matrix3D *getTransformMatrix( void ) const;
	Real getInstanceScale( void ) const { return m_instanceScale; }
	const Coord3D *getPosition( void ) const;
private:
	char m_unrecovered00[ 0xFC ];
	Object *m_object;																													///< 0xFC
	char m_unrecovered100[ 0x200 - 0x100 ];
	Real m_instanceScale;																											///< 0x200
};

class W3DDebrisDraw
{
public:
	virtual void doDrawModule( const Matrix3D *transformMtx );
protected:
	Drawable *getDrawable( void ) const { return m_drawable; }
private:
	enum { INITIAL, FLYING, FINAL, STATECOUNT };
	void *m_moduleData;																												///< 0x04
	Drawable *m_drawable;																											///< 0x08
	char m_unrecovered0C[ 0x24 - 0x0C ];
	RenderObjClass *m_renderObject;																						///< 0x24
	HAnimClass *m_anims[ STATECOUNT ];																				///< 0x28
	const FXList *m_fxFinal;																									///< 0x34
	Int m_state;																															///< 0x38
	Int m_frames;																															///< 0x3C
	Bool m_finalStop;																													///< 0x40
};

//-------------------------------------------------------------------------------------------------
static Bool isAnimationComplete(RenderObjClass* r)
{
	if (r->Class_ID() == RenderObjClass::CLASSID_HLOD)
	{
		HLodClass *hlod = (HLodClass*)r;
		return hlod->Is_Animation_Complete();
	}

	return true;
}

//-------------------------------------------------------------------------------------------------
void W3DDebrisDraw::doDrawModule(const Matrix3D* transformMtx)
{
	if (m_renderObject)
	{

		Matrix3D scaledTransform;
		if (getDrawable()->getInstanceScale() != 1.0f)
		{	//do custom scaling of the W3D model.
			scaledTransform=*transformMtx;
			scaledTransform.Scale(getDrawable()->getInstanceScale());
			transformMtx = &scaledTransform;
			m_renderObject->Set_ObjectScale(getDrawable()->getInstanceScale());
		}
		m_renderObject->Set_Transform(*transformMtx);

		static const RenderObjClass::AnimMode TheAnimModes[STATECOUNT] =
		{
			RenderObjClass::ANIM_MODE_ONCE,
			RenderObjClass::ANIM_MODE_LOOP,
			RenderObjClass::ANIM_MODE_ONCE
		};

		Int oldState = m_state;
		Object* obj = getDrawable()->getObject();
		const Int MIN_FINAL_FRAMES = 3;
		if (m_state != FINAL && obj != 0 && !obj->isAboveTerrain() && m_frames > MIN_FINAL_FRAMES)
		{
			m_state = FINAL;
		}
		else if (m_state < FINAL && (isAnimationComplete(m_renderObject)))
		{
			++m_state;
		}
		HAnimClass* hanim = m_anims[m_state];
		if (hanim != 0 && (hanim != m_renderObject->Peek_Animation() || oldState != m_state))
		{
			RenderObjClass::AnimMode m = TheAnimModes[m_state];
			if (m_state == FINAL)
			{
				if (m_fxFinal)
					FXList::doFXPos(m_fxFinal, getDrawable()->getPosition(), getDrawable()->getTransformMatrix(), 0.0f, 0);
				if (m_finalStop)
					m = RenderObjClass::ANIM_MODE_MANUAL;
			}
			m_renderObject->Set_Animation(hanim, 0, m);
		}
		++m_frames;
	}
}

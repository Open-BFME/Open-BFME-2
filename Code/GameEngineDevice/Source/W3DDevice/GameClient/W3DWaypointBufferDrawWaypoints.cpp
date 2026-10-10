// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
//
// ?drawWaypoints@W3DWaypointBuffer@@QAEXAAVRenderInfoClass@@@Z
// retail 0x000DFE31 (588B)
//
// W3DWaypointBuffer::drawWaypoints, ported from Open-BFME-1 b03e2952c
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DWaypointBufferDrawWaypoints.cpp
// (BFME 1 retail 0x00746A30; Zero Hour twin W3dWaypointBuffer.cpp, rally-point
// branch compiled out, see below). BFME 2 target facts: the height map
// render 0x000E2FBD calls it with its RenderInfoClass; TheInGameUI's waypoint flag is +0x8B0 and
// getAllSelectedDrawables is slot 73; Object's AI is +0x258 and the template's
// kind-of mask is tested as a byte (+0x10D bit 7, KINDOF_IGNORED_IN_GUI) with
// no override walk; the goal-path size and position helpers are the rowed
// 0x00265143 and 0x00346FA5.

#include <list>
#include <bitset>

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

#define MAX_DISPLAY_NODES 512

enum KindOfType
{
	KINDOF_IGNORED_IN_GUI = 47
};

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class Vector3
{
public:
	Vector3(void) {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	void Set(const Vector3 &that) { X = that.X; Y = that.Y; Z = that.Z; }

	float X;
	float Y;
	float Z;
};

class Matrix3D;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rendobj.h
class RenderObjClass
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void Render(class RenderInfoClass &rinfo);
	virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void Validate_Transform(void) const;
	virtual void slot21();
	virtual void Set_Position(const Vector3 &v);

	const Matrix3D &Get_Transform(void) const
	{
		Validate_Transform();
		return *(const Matrix3D *)m_transform;
	}

	unsigned char m_unreconstructed_04[0x18 - 4];
	unsigned char m_transform[0x30];
};

class CameraClass : public RenderObjClass {};

class SegmentedLineClass : public RenderObjClass
{
public:
	void Set_Points(unsigned int num_points, Vector3 *locs);
};

// Size 0x228 from LightEnvironmentClassConstructor.cpp (retail 0x0094AAF0).
class BfmeVecHF;
class Gen_0094AC70 { public: void bfmeSetPair(const BfmeVecHF *center, const BfmeVecHF *ambient); };

class LightEnvironmentClass
{
public:
	LightEnvironmentClass(void);
	~LightEnvironmentClass(void);
	// Rowed as Gen_0094AC70::bfmeSetPair (0x0013F620).
	void Reset(const Vector3 &object_center, const Vector3 &scene_ambient)
	{
		reinterpret_cast<Gen_0094AC70 *>(this)->bfmeSetPair(
			reinterpret_cast<const BfmeVecHF *>(&object_center), reinterpret_cast<const BfmeVecHF *>(&scene_ambient));
	}
	void Pre_Render_Update(const Matrix3D &camera_tm);

private:
	unsigned char m_unreconstructed_000[0x228];
};

// BFME 2 RenderInfoClass: 0x148 bytes (ctor 0x00142EE0, dtor 0x00142FE0);
// the fog colour sits at +0x08 and light_environment at +0x28.
class RenderInfoClass
{
public:
	RenderInfoClass(CameraClass &cam);
	~RenderInfoClass(void);

	CameraClass &Camera;
	float fog_scale;
	float FogColor[3];
	float fog_start;
	float fog_end;
	float alphaOverride;
	float materialPassAlphaOverride;
	float materialPassEmissiveOverride;
	LightEnvironmentClass *light_environment;
	unsigned char m_unreconstructed_2C[0x148 - 0x2C];
};

class WW3D
{
public:
	static bool Render(RenderObjClass &obj, RenderInfoClass &rinfo);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
};

// m_kindof: BFME 2 tests the kind-of mask at +0x108 as bytes (bit 47 is
// +0x10D bit 7), with no override walk from Object.
class ThingTemplate
{
public:
	Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }

	unsigned char m_unreconstructed_000[0x108];
	unsigned char m_kindof[12];
};

// Rva0016F770Path is the ledger's address-derived name for the goal-path
// lookup at 0x0016F770 reached through AIUpdateInterface+0x30 (ZH:
// getStateMachine()->getGoalPathPosition(index)).
struct Rva0016F770Coord3D
{
	float x;
	float y;
	float z;
};

// BFME 2's goal-path position lookup is rowed as 0x00346FA5.
class Rva00346FA5
{
public:
	void *rva00346FA5(int index) const;
};

class AIUpdateInterface
{
public:
	// retail 0x00271AE0 via ILT 0x0000BD84: ZH AIUpdate.cpp body (state id vs
	// AI_FOLLOW_PATH=6 with INVALID_STATE_ID 999999, then goal-path size / 12).
	// BFME 2: rowed 0x00265143 (ZH friend_getWaypointGoalPathSize).
	Int rva00265143();
	Int friend_getWaypointGoalPathSize() { return rva00265143(); }
	Int friend_getCurrentGoalPathIndex() const { return m_nextGoalPathIndex; }
	const Rva0016F770Coord3D *friend_getGoalPathPosition(Int index) const { return (const Rva0016F770Coord3D *)m_stateMachine->rva00346FA5(index); }

	unsigned char m_unreconstructed_000[0x30];
	Rva00346FA5 *m_stateMachine;
	unsigned char m_unreconstructed_034[0x194 - 0x34];
	Int m_nextGoalPathIndex;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	__forceinline Bool isKindOf(KindOfType t) const { return (m_template->m_kindof[t >> 3] & (1 << (t & 7))) != 0; }
	const Coord3D *getPosition() const { return &m_cachedPos; }
	AIUpdateInterface *getAI() { return m_ai; }

	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_cachedPos;
	unsigned char m_unreconstructed_044[0x258 - 0x44];
	AIUpdateInterface *m_ai;
};

class Drawable
{
public:
	Object *getObject() { return m_object; }

	unsigned char m_unreconstructed_000[0xFC];
	Object *m_object;
};

typedef _STL::list<Drawable *> DrawableList;
typedef DrawableList::const_iterator DrawableListCIt;

class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n() = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27)
	BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(30) BFME_UI_SLOT(31)
	BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34) BFME_UI_SLOT(35)
	BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38) BFME_UI_SLOT(39)
	BFME_UI_SLOT(40) BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43)
	BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46) BFME_UI_SLOT(47)
	BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(50) BFME_UI_SLOT(51)
	BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54) BFME_UI_SLOT(55)
	BFME_UI_SLOT(56) BFME_UI_SLOT(57) BFME_UI_SLOT(58) BFME_UI_SLOT(59)
	BFME_UI_SLOT(60) BFME_UI_SLOT(61) BFME_UI_SLOT(62) BFME_UI_SLOT(63)
	BFME_UI_SLOT(64) BFME_UI_SLOT(65) BFME_UI_SLOT(66) BFME_UI_SLOT(67)
	BFME_UI_SLOT(68) BFME_UI_SLOT(69) BFME_UI_SLOT(70) BFME_UI_SLOT(71)
	BFME_UI_SLOT(72)
	virtual const DrawableList *getAllSelectedDrawables() const = 0;
#undef BFME_UI_SLOT

	Bool isInWaypointMode() const { return m_waypointMode; }

	unsigned char m_pad004[0x8B0 - 0x04];
	Bool m_waypointMode;
};

extern InGameUI *TheInGameUI;

class W3DWaypointBuffer
{
public:
	void drawWaypoints(RenderInfoClass &rinfo);

private:
	RenderObjClass *m_waypointNodeRobj;
	SegmentedLineClass *m_line;
};

void W3DWaypointBuffer::drawWaypoints(RenderInfoClass &rinfo)
{
	if( TheInGameUI && TheInGameUI->isInWaypointMode() )
	{
		LightEnvironmentClass lightEnv;
		lightEnv.Reset(Vector3(0,0,0), Vector3(1.0f,1.0f,1.0f));
		lightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		RenderInfoClass localRinfo(rinfo.Camera);
		localRinfo.light_environment=&lightEnv;
		Vector3 points[ MAX_DISPLAY_NODES + 1 ];

		const DrawableList *selected = TheInGameUI->getAllSelectedDrawables();
		Drawable *draw;
		for( DrawableListCIt it = selected->begin(); it != selected->end(); ++it )
		{
			draw = *it;
			Object *obj = draw->getObject();
			Int numPoints = 1;
			if( obj && ! obj->isKindOf( KINDOF_IGNORED_IN_GUI ))
			{
				AIUpdateInterface *ai = obj->getAI();
				Int goalSize = ai ? ai->friend_getWaypointGoalPathSize() : 0;
				Int gpIdx = ai ? ai->friend_getCurrentGoalPathIndex() : 0;
				if( ai && gpIdx >= 0 && gpIdx < goalSize )
				{
					const Coord3D *pos = obj->getPosition();
					points[ 0 ].Set( Vector3( pos->x, pos->y, pos->z ) );

					for( int i = gpIdx; i < goalSize; i++ )
					{
						const Rva0016F770Coord3D *waypoint = ai->friend_getGoalPathPosition( i );
						if( waypoint )
						{
							if( numPoints < MAX_DISPLAY_NODES + 1 )
							{
								points[ numPoints ].Set( Vector3( waypoint->x, waypoint->y, waypoint->z ) );
								numPoints++;
							}

							m_waypointNodeRobj->Set_Position(Vector3(waypoint->x,waypoint->y,waypoint->z));
							WW3D::Render(*m_waypointNodeRobj,localRinfo);
						}
					}
					m_line->Set_Points( numPoints, points );
					m_line->Render( localRinfo );
				}
			}
		}
	}
	else if (0) // retail compiles the rally-point branch out
	{
		// Zero Hour's twin draws rally points in this else-branch, opening with
		// the light environment and RenderInfoClass below. Retail's unwind map
		// (FuncInfo 0x009069CC) keeps three action-less states chained under no
		// live object (2 -> -1, 3 -> 2, 4 -> 3) after the waypoint branch's two:
		// the discarded branch's locals. The third is not in Zero Hour and its
		// type is unknown; a third RenderInfoClass reproduces only its EH shape.
		LightEnvironmentClass lightEnv;
		lightEnv.Reset(Vector3(0,0,0), Vector3(1.0f,1.0f,1.0f));
		lightEnv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		RenderInfoClass localRinfo(rinfo.Camera);
		localRinfo.light_environment=&lightEnv;
		RenderInfoClass rallyRinfo(rinfo.Camera);
		m_line->Render( rallyRinfo );
	}
}

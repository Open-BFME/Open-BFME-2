// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /ICode/Libraries/Include /ICode/GameEngine/Source/Common /O1 /G7 /arch:SSE
// Notes kept from the earlier banks of this body:
// The bit-flag word block at Object+0x110 (591 bits, 0x114..0x11F).
// Object: only the members this function touches, at the retail offsets.
	// +0x110: model condition flags
	// +0x274: AIUpdateInterface *
	// +0x438: status bits
// Thing: base of Object with the transform helpers.
// Path / Locomotor / Pathfinder / TerrainLogic stubs.
// AIUpdateInterface: the class we are defining.
	// vtable slots touched by the retail body.
	// +0x20: AICommandInterface base
	// +0x30: locomotor
	// +0x34
	// +0x140: Path *
	// +0x168
	// +0x1DC
	// +0x1F0: locomotor
	// +0x1FC
	// +0x200: destination
	// +0x3E0
// AICommandInterface.
// Globals.
// Body.
	// Clear five model condition bits.
	// If the object is idle and has no path, just idle the command interface.
	// Path / locomotion update.
//
// ?quickHordeUpdate@AIUpdateInterface@@QAEXXZ, retail 0x0026C4EB, 2598 bytes.
// Reconstructed from the retail disassembly plus the WorldBuilder debug twin
// (game.dat rva 0x0026C4EB / WB va 0xe3b6d0).  The body clears five model
// condition bits on the controlled object, then drives the horde locomotion
// state machine (idle / tighten-to-position / path following).
//
// Earlier farm-draft section notes (that body is replaced): "Clear five model
// condition bits." "If the object is idle and has no path, just idle the command
// interface." "Path / locomotion update." "The bit-flag word block at Object+0x110
// (591 bits, 0x114..0x11F)." "Object: only the members this function touches, at
// the retail offsets." "+0x110: model condition flags" "+0x274: AIUpdateInterface *"
// "+0x438: status bits" "Thing: base of Object with the transform helpers."
// "Path / Locomotor / Pathfinder / TerrainLogic stubs." "AIUpdateInterface: the
// class we are defining." "vtable slots touched by the retail body." "+0x20:
// AICommandInterface base" "+0x30: locomotor" "+0x34" "+0x140: Path *" "+0x168"
// "+0x1DC" "+0x1F0: locomotor" "+0x1FC" "+0x200: destination" "+0x3E0"
// "AICommandInterface." "Globals." "Body."
//
// AIUpdateInterface::quickHordeUpdate, retail 0x0026C4EB..0x0026CF11 (2598 bytes),
// returning UpdateSleepTime (the symbols.csv pin of the update 0x0026E267 callee).
// Identity: WorldBuilder 0x00E3B6D0 callgraph name; the only caller is the rowed
// AIUpdateInterface::update 0x0026E267. Every callee is rowed or pinned.
// Structure read from retail: five model-condition clears; an idle short-cut
// (vslot 113, no container, 0x002931F5) to aiIdle; 0x00265AAB; dead objects fall
// by TheGlobalData+0xC4 * 5 to the layer height; the Object+0x25C/+0x5C gate;
// the +0x3E0-bracketed state machine update under vslot 111; then goal type
// 2/4 (step toward the goal clamped by locomotor speed, validated as a horde
// member; type 4 with a path runs doLocomotor on the path for one frame) or 3
// (turn toward the goal angle). Field and slot names beyond Zero Hour's are
// address-derived.
//
// Shapes the retail bytes need (WB twin statement order): the goal step goes
// through inline Coord3D member mutators (Set / Sub / Scale / Add on the C3
// view, as the twin's member calls), with Coord3D::GetLength / normalize
// visible in this unit so the scaled delta stores die; setModelConditionState
// is an early-return inline (byte-narrowed test/or); the z rotation is
// WWMath's Rotate_Z over Vector4 rows.

#include <math.h>
#include "Lib/Coord3D.h"

typedef float Real;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum KindOfType
{
	KINDOF_9 = 9,
	KINDOF_156 = 156
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1,
	LAYER_16 = 16
};

enum LocomotorGoalType
{
	NONE = 0,
	POSITION_ON_PATH = 1,
	POSITION_EXPLICIT = 2,
	ANGLE = 3,
	POSITION_EXPLICIT_HORDE = 4
};

enum ModelConditionFlagType
{
	MODELCONDITION_61 = 1 * 32 + 29,
	MODELCONDITION_103 = 3 * 32 + 7,
	MODELCONDITION_133 = 4 * 32 + 5,
	MODELCONDITION_134 = 4 * 32 + 6,
	MODELCONDITION_137 = 4 * 32 + 9,
	MODELCONDITION_138 = 4 * 32 + 10,
	MODELCONDITION_156 = 4 * 32 + 28
};

#ifndef NULL
#define NULL 0
#endif

#define PI 3.14159265359f
#define REAL_EPSILON 1.1920929e-07f

template<int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template<>
class BfmeVirtualSlots<0>
{
};

__declspec(noinline) inline float Coord3D::GetLength() const
{
	float x_value = x;
	float y_value = y;
	float z_value = z;

	return (float)sqrt(x_value * x_value + y_value * y_value + z_value * z_value);
}

inline float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

__declspec(noinline) inline void Coord3D::normalize()
{
	float len = length();
	if (len != 0.0f) {
		float scale = 1.0f / len;
		x *= scale;
		y *= scale;
		z *= scale;
	}
}

inline void coordSub(Coord3D *a, const Coord3D *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

inline void coordAdd(Coord3D *a, const Coord3D *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

inline void coordScale(Coord3D *a, Real scale)
{
	a->x *= scale;
	a->y *= scale;
	a->z *= scale;
}


struct C3 : Coord3D
{
	C3 &Sub(const Coord3D &c) { x -= c.x; y -= c.y; z -= c.z; return *this; }
	C3 &Add(const Coord3D &c) { x += c.x; y += c.y; z += c.z; return *this; }
	C3 &Scale(Real s) { x *= s; y *= s; z *= s; return *this; }
	void Set(const Coord3D &c) { x = c.x; y = c.y; z = c.z; }
};

template <class T>
inline const T &maxOf(const T &a, const T &b)
{
	return a < b ? b : a;
}

class Vector4R
{
public:
	float X, Y, Z, W;
	__forceinline float &operator[](int i) { return (&X)[i]; }
	__forceinline const float &operator[](int i) const { return (&X)[i]; }
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
};
class Matrix3D
{
public:
	__declspec(dllimport) __forceinline Matrix3D(bool init)
	{
		if (init)
		{
			Row[0].X = 1.0f; Row[0].Y = 0.0f; Row[0].Z = 0.0f; Row[0].W = 0.0f;
			Row[1].X = 0.0f; Row[1].Y = 1.0f; Row[1].Z = 0.0f; Row[1].W = 0.0f;
			Row[2].X = 0.0f; Row[2].Y = 0.0f; Row[2].Z = 1.0f; Row[2].W = 0.0f;
		}
	}
	__forceinline void rotateZ(float theta)
	{
		float tmp1, tmp2;
		float c, s;
		c = cosf(theta);
		s = sinf(theta);
		tmp1 = Row[0].X; tmp2 = Row[0].Y;
		Row[0].X = (float)( c*tmp1 + s*tmp2);
		Row[0].Y = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[1].X; tmp2 = Row[1].Y;
		Row[1].X = (float)( c*tmp1 + s*tmp2);
		Row[1].Y = (float)(-s*tmp1 + c*tmp2);
		tmp1 = Row[2].X; tmp2 = Row[2].Y;
		Row[2].X = (float)( c*tmp1 + s*tmp2);
		Row[2].Y = (float)(-s*tmp1 + c*tmp2);
	}
	void setTranslation(const Coord3D &t)
	{
		Row[0][3] = t.x;
		Row[1][3] = t.y;
		Row[2][3] = t.z;
	}
private:
	Vector4R Row[3];
};

class ModelConditionFlags
{
public:
	UnsignedInt test(UnsignedInt bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(UnsignedInt bit)
	{
		m_words[bit >> 5] |= (1U << (bit & 0x1f));
	}
	void clear(UnsignedInt bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	UnsignedInt m_words[19];
};

class ThingTemplate
{
public:
	__forceinline UnsignedInt isKindOf(UnsignedInt bit) const
	{
		return m_kindOf[bit >> 5] & (1U << (bit & 0x1f));
	}
private:
	unsigned char m_pad000[0x108];
	UnsignedInt m_kindOf[8]; // +0x108
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_angle; }
	void setPositionZ(Real z);
	void setOrientation(Real angle);
	void setTransformMatrix(const Matrix3D *mx);
private:
	void *m_vtbl;
	const ThingTemplate *m_template; // +0x04
	unsigned char m_pad08[0x38 - 0x08];
	Coord3D m_pos; // +0x38
	Real m_angle; // +0x44
};

class AIUpdateInterface;
class Object;

// The object reached through Object +0x250 slot 31 (slot 105 is a bool query).
class Rva0026C4EBRider : public BfmeVirtualSlots<105>
{
public:
	virtual Bool slot105();
};

class Rva0026C4EBContain : public BfmeVirtualSlots<31>
{
public:
	virtual Rva0026C4EBRider *slot31();
};

// Object +0x25C; its +0x5C flag stops all horde movement.
struct Rva0026C4EBGate
{
	unsigned char m_pad00[0x5C];
	Bool m_5C;
};

// Retail 0x0028B525 stores the pathfind layer at Object +0x40C.
// Use the rowed displacement view without claiming an Object method name.
class Rva0028B525DwordSlot
{
public:
	void set(int value);
};

class Object : public Thing
{
public:
	Bool isKindOf(KindOfType t) const;
	void rva0028AE6D(); // model-condition change notifier
	Int rva0028B511() const; // the pathfind layer
	Object *rva002931F5(Bool arg);
	Real GetRelativeAngle(const Coord3D *pos) const;

	Object *getContainedBy() const { return m_containedBy; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Rva0026C4EBContain *getContain() const { return m_contain; }
	Bool isEffectivelyDead() const { return (m_438 & 1) != 0; }

	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc))
			return;
		m_modelConditionFlags.set(mc);
		rva0028AE6D();
	}

	unsigned char m_pad048[0x10C - 0x48];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x250 - 0x158];
	Rva0026C4EBContain *m_contain; // +0x250
	unsigned char m_pad254[0x258 - 0x254];
	AIUpdateInterface *m_ai; // +0x258
	Rva0026C4EBGate *m_25C; // +0x25C
	unsigned char m_pad260[0x274 - 0x260];
	Object *m_containedBy; // +0x274
	unsigned char m_pad278[0x438 - 0x278];
	unsigned char m_438; // +0x438, bit 0 set once effectively dead
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView
{
	unsigned char m_pad00[0xC4];
	Real m_C4;
};

struct Rva001E3E6DArg;
class Rva001E3E6D
{
public:
	Real rva001E3E6D(Rva001E3E6DArg *obj);
};

class Locomotor
{
public:
	Real getMaxSpeed(Object *obj) const;
	Real getMaxTurnRate(Object *obj) const;
	void rva001E9083(Object *obj, const Coord3D *goal, Real onPathDistToGoal, Real desiredSpeed);
};

class Rva001E46E1
{
public:
	void rva001E53D8(Real speed, Object *obj);
};

class Rva0008BB38FloatField;

struct Rva003642DFNode
{
	unsigned char m_pad00[0x08];
	void *m_08; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
	Int m_20; // +0x20
};

#include "../../../../../Include/GameLogic/Rva003642DFResult.h"


class Rva001E3591
{
public:
	Bool rva001E3591();
};

struct PathNodeView
{
	unsigned char m_pad00[0x0C];
	Coord3D m_pos; // +0x0C
};

class Path
{
public:
	~Path();
	Rva003642DFResult rva00364521(const Rva0008BB38FloatField *locomotor);
	unsigned char m_pad00[0x08];
	PathNodeView *m_08; // +0x08
};

#include "../../../../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

#include "../../../../../Include/GameLogic/AIPathfind.h"

#include "../../../../../Include/GameLogic/AI.h"

extern AI *TheAI;

extern int BfmeLogicFramesPerSecond; // logic frames per second

Real normalizeAngle(Real angle);

#include "../../../../../Include/Common/StateMachineClass.h"

#include "../../../../../Include/GameLogic/AIStateMachineClass.h"

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);
private:
	void *m_vtbl;
};

struct Object00265AAB;
class Rva00265AAB
{
public:
	void rva00265AAB(Object00265AAB *object, int *sleep);
};

class AIUpdateInterface : public BfmeVirtualSlots<111>
{
public:
	virtual Bool slot111();
	virtual void slot112();
	virtual Bool slot113();
	virtual void slot114(); virtual void slot115(); virtual void slot116();
	virtual void slot117(); virtual void slot118(); virtual void slot119();
	virtual void slot120(); virtual void slot121(); virtual void slot122();
	virtual void slot123(); virtual void slot124(); virtual void slot125();
	virtual void slot126(); virtual void slot127(); virtual void slot128();
	virtual void slot129(); virtual void slot130(); virtual void slot131();
	virtual void slot132(); virtual void slot133(); virtual void slot134();
	virtual void slot135(); virtual void slot136(); virtual void slot137();
	virtual void slot138(); virtual void slot139(); virtual void slot140();
	virtual void slot141(); virtual void slot142(); virtual void slot143();
	virtual void slot144(); virtual void slot145(); virtual void slot146();
	virtual void slot147(); virtual void slot148();
	virtual UpdateSleepTime doLocomotor();

	Bool isMoving() const;
	UpdateSleepTime quickHordeUpdate();

	Object *getObject() const { return m_object; }
	AIStateMachine *getStateMachine() const { return m_stateMachine; }
	Real getPathExtraDistance() const { return m_pathExtraDistance; }
	Int getValidSurfaces() const { return m_1DC; }
private:
	unsigned char m_pad04[0x08 - 0x04];
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x20 - 0x0C];
	AICommandInterface m_commands; // +0x20
	unsigned char m_pad24[0x30 - 0x24];
	AIStateMachine *m_stateMachine; // +0x30
	void *m_34; // +0x34
	unsigned char m_pad38[0x140 - 0x38];
	Path *m_path; // +0x140
	unsigned char m_pad144[0x168 - 0x144];
	Real m_pathExtraDistance; // +0x168
	unsigned char m_pad16C[0x1DC - 0x16C];
	Int m_1DC; // +0x1DC
	unsigned char m_pad1E0[0x1F0 - 0x1E0];
	Rva001E46E1 *m_curLocomotor; // +0x1F0
	unsigned char m_pad1F4[0x1FC - 0x1F4];
	Int m_locomotorGoalType; // +0x1FC
	Coord3D m_locomotorGoalData; // +0x200
	unsigned char m_pad20C[0x3E0 - 0x20C];
	Bool m_3E0; // +0x3E0, set while the state machine updates
};

UpdateSleepTime AIUpdateInterface::quickHordeUpdate()
{
	Object *obj = getObject();
	obj->clearModelConditionState(MODELCONDITION_103);
	obj->clearModelConditionState(MODELCONDITION_133);
	obj->clearModelConditionState(MODELCONDITION_134);
	obj->clearModelConditionState(MODELCONDITION_137);
	obj->clearModelConditionState(MODELCONDITION_138);

	if (slot113() && obj->getContainedBy() == NULL && obj->rva002931F5(false) == NULL)
	{
		m_commands.aiIdle(CMD_FROM_AI);
		return UPDATE_SLEEP_NONE;
	}

	{
		int sleep;
		((Rva00265AAB *)this)->rva00265AAB((Object00265AAB *)obj, &sleep);
	}
	if (m_locomotorGoalType == NONE)
		return (UpdateSleepTime)BfmeLogicFramesPerSecond;

	if (obj->isEffectivelyDead())
	{
		obj->clearModelConditionState(MODELCONDITION_156);
		Coord3D pos;
		pos.x = obj->getPosition()->x;
		pos.y = obj->getPosition()->y;
		pos.z = obj->getPosition()->z;
		Real groundZ = TheTerrainLogic->getLayerHeight(pos.x, pos.y, (PathfindLayerEnum)obj->rva0028B511());
		if (pos.z > groundZ)
		{
			pos.z += ((GlobalDataView *)TheWritableGlobalData)->m_C4 * 5.0f;
			if (pos.z < groundZ)
				pos.z = groundZ;
			obj->setPositionZ(pos.z);
			return UPDATE_SLEEP_NONE;
		}
		return (UpdateSleepTime)BfmeLogicFramesPerSecond;
	}

	if (obj->m_25C && obj->m_25C->m_5C)
	{
		obj->clearModelConditionState(MODELCONDITION_156);
		return (UpdateSleepTime)BfmeLogicFramesPerSecond;
	}

	if (slot111())
	{
		m_3E0 = m_34 != NULL;
		getStateMachine()->updateStateMachine();
		m_3E0 = false;
	}
	obj->clearModelConditionState(MODELCONDITION_156);

	Object *container = obj->getContainedBy();
	if (m_locomotorGoalType == POSITION_EXPLICIT || m_locomotorGoalType == POSITION_EXPLICIT_HORDE)
	{
		Real maxSpeed = 99999.0f;
		if (container && container->getContain() && container->getContain()->slot31()
			&& container->getContain()->slot31()->slot105())
		{
			obj->setModelConditionState(MODELCONDITION_156);
		}
		Rva001E46E1 *loco = m_curLocomotor;
		if (loco)
		{
			if (obj->isKindOf(KINDOF_156))
				maxSpeed = ((Rva001E3E6D *)loco)->rva001E3E6D((Rva001E3E6DArg *)obj);
			else
				maxSpeed = ((Locomotor *)loco)->getMaxSpeed(obj);
		}

		Coord3D pos;
		static_cast<C3 &>(pos).Set(*obj->getPosition());
		Coord3D oldPos;
		static_cast<C3 &>(oldPos).Set(pos);
		if (m_locomotorGoalType != POSITION_EXPLICIT_HORDE || m_path == NULL)
		{
			const Coord3D *goal = &m_locomotorGoalData;
			Coord3D delta;
			static_cast<C3 &>(delta).Set(*goal);
			static_cast<C3 &>(delta).Sub(pos);
			delta.z = 0.0f;
			Real dist = delta.GetLength();
			if (dist > 4.0f * maxSpeed && container && container->getAI()
				&& container->getAI()->slot111() && container->getAI()->isMoving())
			{
				maxSpeed *= 1.5f;
			}
			if (dist > maxSpeed)
			{
				delta.normalize();
				static_cast<C3 &>(delta).Scale(maxSpeed);
				static_cast<C3 &>(pos).Add(delta);
				obj->setModelConditionState(MODELCONDITION_61);
			}
			else
			{
				pos = m_locomotorGoalData;
			}

			if (TheAI->pathfinder()->IsValidMovementPositionForObject(obj->getPosition(), obj->rva0028B511(), getValidSurfaces(), obj)
				&& !TheAI->pathfinder()->IsValidHordeMemberRegularMovement(obj, obj->getPosition(), &pos, &m_locomotorGoalData))
			{
				if (m_path)
				{
					delete m_path;
					m_path = NULL;
				}
				TheAI->pathfinder()->AdjustLayer(obj);
				m_path = TheAI->pathfinder()->GetHordeUnitPath(obj, &m_locomotorGoalData);
				if (m_path == NULL)
					pos = m_locomotorGoalData;
			}
		}

		if (m_locomotorGoalType == POSITION_EXPLICIT_HORDE && m_path)
		{
			Rva003642DFResult info = m_path->rva00364521((const Rva0008BB38FloatField *)m_curLocomotor);
			if (((Rva001E3591 *)m_path)->rva001E3591())
			{
				m_locomotorGoalType = POSITION_ON_PATH;
				doLocomotor();
				m_locomotorGoalType = POSITION_EXPLICIT_HORDE;
				if (m_path)
					((Rva0028B525DwordSlot *)obj)->set(TheTerrainLogic->getLayerForDestination(obj, &m_path->m_08->m_pos));
			}
			else
			{
				TheAI->pathfinder()->AdjustLayer(obj);
				((Locomotor *)m_curLocomotor)->rva001E9083(obj, &info.m_pos,
					getPathExtraDistance() + ((Rva00363D20 *)&info)->rva00363D20(), maxSpeed * 1.5f);
			}
			obj->setModelConditionState(MODELCONDITION_61);
			if (info.m_node == NULL || info.m_node->m_08 == NULL)
			{
				delete m_path;
				m_path = NULL;
			}
			return UPDATE_SLEEP_NONE;
		}

		Matrix3D mtx(true);
		Real angle = obj->getOrientation() + obj->GetRelativeAngle(&m_locomotorGoalData);
		if (obj->getTemplate()->isKindOf(KINDOF_9))
		{
			Real relAngle = obj->GetRelativeAngle(&m_locomotorGoalData);
			Coord3D offset;
			offset.x = obj->getPosition()->x;
			offset.y = obj->getPosition()->y;
			offset.z = obj->getPosition()->z;
			coordSub(&offset, &m_locomotorGoalData);
			Real factor = offset.GetLength2D() * 0.05f;
			if (factor < 1.0f)
			{
				relAngle *= factor;
				angle = obj->getOrientation() + relAngle;
			}
		}
		if (obj->isKindOf(KINDOF_156))
		{
			Object *goal = obj->getContainedBy()->getAI()->getStateMachine()->getGoalObject();
			if (goal)
				angle = obj->getOrientation() + obj->GetRelativeAngle(goal->getPosition());
			else
				angle += PI;
		}
		mtx.rotateZ(angle);
		((Rva0028B525DwordSlot *)obj)->set(TheTerrainLogic->getLayerForDestination(obj, &pos));

		if (m_locomotorGoalType != POSITION_EXPLICIT_HORDE || m_path == NULL)
		{
			if (TheAI->pathfinder()->IsValidMovementPositionForObject(&pos, obj->rva0028B511(), getValidSurfaces(), getObject()))
			{
				Real groundZ = TheTerrainLogic->getLayerHeight(pos.x, pos.y, (PathfindLayerEnum)obj->rva0028B511());
				if (groundZ > pos.z)
				{
					pos.z = groundZ;
				}
				else if (obj->rva0028B511() == LAYER_16 && pos.z - groundZ < 20.0f)
				{
					pos.z = maxOf(pos.z - 9.0f, groundZ);
				}
				if (obj->rva0028B511() == LAYER_GROUND && container && container->rva0028B511() == LAYER_GROUND)
					pos.z = groundZ;
			}
		}

		mtx.setTranslation(pos);
		obj->setTransformMatrix(&mtx);
		{
			Coord3D moved;
			moved.x = pos.x;
			moved.y = pos.y;
			moved.z = pos.z;
			coordSub(&moved, &oldPos);
			Real dist = moved.GetLength();
			if (dist > maxSpeed)
				dist = maxSpeed;
			m_curLocomotor->rva001E53D8(dist, obj);
		}
		return UPDATE_SLEEP_NONE;
	}
	else if (m_locomotorGoalType == ANGLE)
	{
		Real angle = obj->getOrientation();
		Real goalAngle = m_locomotorGoalData.x;
		Real angleDiff = normalizeAngle(angle - goalAngle);
		if (angleDiff > -REAL_EPSILON && angleDiff < REAL_EPSILON)
		{
			obj->clearModelConditionState(MODELCONDITION_61);
			obj->clearModelConditionState(MODELCONDITION_134);
			obj->clearModelConditionState(MODELCONDITION_133);
			m_locomotorGoalType = NONE;
			return UPDATE_SLEEP_NONE;
		}
		obj->setModelConditionState(MODELCONDITION_61);
		if (m_curLocomotor)
		{
			Real turnRate = ((Locomotor *)m_curLocomotor)->getMaxTurnRate(obj);
			if (angleDiff > turnRate / 2.0f)
				obj->setModelConditionState(MODELCONDITION_134);
			else if (angleDiff < -turnRate / 2.0f)
				obj->setModelConditionState(MODELCONDITION_133);
		}
		obj->setOrientation(m_locomotorGoalData.x);
		return UPDATE_SLEEP_NONE;
	}
	return (UpdateSleepTime)BfmeLogicFramesPerSecond;
}

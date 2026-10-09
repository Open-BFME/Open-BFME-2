// ?rva00344249@AIMoveToStateSA@@QAE_NPAUCoord3D@@PAVObject@@@Z
// partial score=0.978899 date=2026-10-10
// ?rva00344249@AIMoveToStateSA@@QAE_NPAUCoord3D@@PAVObject@@@Z
// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include
//
// ?rva00344249@AIMoveToStateSA@@QAE_NPAUCoord3D@@PAVObject@@@Z
// retail 0x00344249..0x003444CE (645 bytes) thiscall RET 8; this unused.
//
// NEAR (helper draft, not under Code/): compiles to 645 bytes and matches
// retail except an xmm1/xmm3 swap for direction.x/z across the scale(20) and
// the step loop (11 instructions differ only in the register field). Tried
// without effect: scale/sub operand order and form (Scale/operator*=/
// operator-=/field-wise), Coord3DBase base, inline dtor, loop shapes,
// declaration order, flags /G5 /G6 /G7 /arch:SSE2.
//
// Identity: BFME 1 donor Rva0016EE00::method (Open-BFME-1
// game/GameEngine/Source/GameLogic/AI/Rva0016EE00.cpp) -- step the goal back
// toward the unit by 20 until QuickDoesPathExist passes, pull it in by the
// AI clearance (AIData +0xD4) plus the object's +0xB8 radius and accept it
// only if that is at least 20 closer, then adjustToPossibleDestination /
// adjustDestination on the AI locomotor set (+0x1CC). BFME 2 calls Coord3D's
// out-of-line GetLength/length/Normalize/normalize (rowed 0x5A26 0x3571
// 0x5A70 0x35B6). Caller: AIMoveToStateSA::computePath 0x00347959 (vtable
// 0x00811F00 slot 17, slot-2 name "AIMoveToStateSA") with ECX = this.
// Twin 0x00344749 has the same body as a static helper (EBX = goal).
typedef bool Bool;
typedef float Real;
typedef int Int;

#include "Lib/Coord3D.h"
// Three-float transient with explicit copy, not a replacement class view.
struct MoveGoalCoord {
 Real x,y,z;
 MoveGoalCoord() {}
 MoveGoalCoord(const Coord3D &p){x=p.x;y=p.y;z=p.z;}
 void sub(const Coord3D*p){x-=p->x;y-=p->y;z-=p->z;}
 void scale(Real s){x*=s;y*=s;z*=s;}
 __forceinline Real GetLength()const{return reinterpret_cast<const Coord3D*>(this)->GetLength();}
 __forceinline Real length()const{return reinterpret_cast<const Coord3D*>(this)->length();}
 __forceinline Real Normalize(){return reinterpret_cast<Coord3D*>(this)->Normalize();}
 __forceinline void normalize(){reinterpret_cast<Coord3D*>(this)->normalize();}
};

class LocomotorSet;

class AIUpdateInterface
{
public:
	LocomotorSet &getLocomotorSet() { return *(LocomotorSet *)m_locomotorSet; }

private:
	char m_pad000[0x1CC];
	char m_locomotorSet[4];				// +0x1CC
};

class Object
{
public:
	Int rva0028B511() const;
	const Coord3D *getPosition() const { return &m_pos; }
	AIUpdateInterface *getAI() const { return m_ai; }
	Real getBfmeRadiusB8() const { return m_radiusB8; }

private:
	char m_pad000[0x38];
	Coord3D m_pos;						// +0x38
	char m_pad044[0xB8 - 0x44];
	Real m_radiusB8;					// +0xB8
	char m_padBC[0x258 - 0xBC];
	AIUpdateInterface *m_ai;			// +0x258
};

class Pathfinder
{
public:
	Bool QuickDoesPathExist(Object *obj, const Coord3D *from, const Coord3D *to, Int flags);
	Bool adjustToPossibleDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);
	Bool adjustDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest, const Coord3D *groupDest);
};

struct AIData
{
	char m_pad000[0xD4];
	Real m_clearanceD4;					// +0xD4
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	AIData *getAiData() { return m_aiData; }

private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;			// +0x10
	char m_pad14[4];
	AIData *m_aiData;					// +0x18
};
extern AI *TheAI;

class AIMoveToStateSA
{
public:
	Bool rva00344249(Coord3D *destination, Object *obj);
};

Bool AIMoveToStateSA::rva00344249(Coord3D *destination, Object *obj)
{
	if (obj->rva0028B511() > 1)
		return true;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return false;
	MoveGoalCoord direction(*destination);
	direction.sub(obj->getPosition());
	direction.z = 0.0f;
	Real distance = direction.GetLength();
	direction = *reinterpret_cast<MoveGoalCoord*>(destination);
	MoveGoalCoord candidate(*destination);
	direction.sub(obj->getPosition());
	direction.z = 0.0f;
	Int count = -(Int)(direction.length() * -0.05f) - 1;
	direction.Normalize();
	direction.scale(20.0f);
	Bool found = false;
	for (Int i = 0; i < count; ++i)
	{
		candidate.sub(reinterpret_cast<Coord3D*>(&direction));
		if (TheAI->pathfinder()->QuickDoesPathExist(obj, obj->getPosition(), reinterpret_cast<Coord3D*>(&candidate), 0))
		{
			found = true;
			break;
		}
	}
	if (!found)
		return false;
	Real clearance = TheAI->getAiData()->m_clearanceD4 + obj->getBfmeRadiusB8();
	direction.normalize();
	direction.scale(clearance);
	candidate.sub(reinterpret_cast<Coord3D*>(&direction));
	direction = *reinterpret_cast<MoveGoalCoord*>(destination);
	direction.sub(reinterpret_cast<Coord3D*>(&candidate));
	direction.z = 0.0f;
	if (direction.GetLength() + 20.0f > distance)
		return false;
	TheAI->pathfinder()->adjustToPossibleDestination(obj, ai->getLocomotorSet(), reinterpret_cast<Coord3D*>(&candidate));
	TheAI->pathfinder()->adjustDestination(obj, ai->getLocomotorSet(), reinterpret_cast<Coord3D*>(&candidate), 0);
	*destination = *reinterpret_cast<Coord3D*>(&candidate);
	return true;
}

// ?rva00344749@@YA_NPAVObject@@@Z
// partial score=0.95 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva00344749@@YA_NPAUCoord3D@@PAVObject@@@Z (static; internal linkage)
// retail 0x00344749..0x003449C5 (636 bytes): custom convention -- goal in
// EBX, object as the one cdecl stack argument, plain RET.
//
// DRAFT for the unit that will hold its only caller,
// AIAttackApproachTargetState::computePath 0x0034804E (vtable 0x00812610
// slot 17; call at 0x003482AA: push obj; lea ebx,[goal]; call; pop ecx). cl
// only gives a static helper this register convention when the caller is in
// the same TU. With a throwaway caller in a scratch TU it reproduced the
// convention and all 636 bytes except the same xmm1/xmm3 swap as
// 0x00344249 (see 0x00344249.cpp, same body).
typedef bool Bool;
typedef float Real;
typedef int Int;

// class-gate: allow Coord3D the canonical data-only header cannot declare BFME 2's out-of-line GetLength (rowed 0x00005A26) and Normalize (rowed 0x00005A70) or the user copy constructor that copies the candidate field by field; same three floats
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Coord3D() {}
	Coord3D(const Coord3D &p) { x = p.x; y = p.y; z = p.z; }
	void sub(const Coord3D *p) { x -= p->x; y -= p->y; z -= p->z; }
	void scale(Real s) { x *= s; y *= s; z *= s; }
	Real GetLength() const;
	Real length() const;
	Real Normalize();
	void normalize();
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

static Bool rva00344749(Coord3D *destination, Object *obj)
{
	if (obj->rva0028B511() > 1)
		return true;
	AIUpdateInterface *ai = obj->getAI();
	if (!ai)
		return false;
	Coord3D direction(*destination);
	direction.sub(obj->getPosition());
	direction.z = 0.0f;
	Real distance = direction.GetLength();
	direction = *destination;
	Coord3D candidate(*destination);
	direction.sub(obj->getPosition());
	direction.z = 0.0f;
	Int count = -(Int)(direction.length() * -0.05f) - 1;
	direction.Normalize();
	direction.scale(20.0f);
	Bool found = false;
	for (Int i = 0; i < count; ++i)
	{
		candidate.sub(&direction);
		if (TheAI->pathfinder()->QuickDoesPathExist(obj, obj->getPosition(), &candidate, 0))
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
	candidate.sub(&direction);
	direction = *destination;
	direction.sub(&candidate);
	direction.z = 0.0f;
	if (direction.GetLength() + 20.0f > distance)
		return false;
	TheAI->pathfinder()->adjustToPossibleDestination(obj, ai->getLocomotorSet(), &candidate);
	TheAI->pathfinder()->adjustDestination(obj, ai->getLocomotorSet(), &candidate, 0);
	*destination = candidate;
	return true;
}


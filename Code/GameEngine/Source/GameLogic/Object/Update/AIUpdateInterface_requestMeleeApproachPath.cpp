// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?requestMeleeApproachPath@AIUpdateInterface@@QAE_NPBUCoord3D@@_N@Z
// retail 0x00263C06, 668 bytes (ret 8).
//
// Identity: WorldBuilder AIUpdate.cpp AIUpdateInterface::requestMeleeApproachPath
// (wb 0x00E39180; callees Coord3D::length/normalize, getLayerForDestination,
// Pathfinder::AdjustToMeleeDestination, Object 0x0028ACDC, queueForPath,
// setQueueForPathTime, destroyPath) plus the CritterDesync
// requestMeleeApproachPath1 string referenced only from this body. The tail is
// the sibling requestApproachPath 0x00263B33.
//
// Target evidence: unless the bool argument is set the offset from the goal
// to the object is clamped to the AI data float at +0x94 and added to the goal,
// which is abandoned when its layer height (TheTerrainLogic vtable +0x1C)
// differs from the goal's by more than 10 (fabs through the msvcr71 import);
// Pathfinder 0x002ED7F7 (pinned from this call) then adjusts it for the object with the
// locomotor set at +0x1CC; a destination closer than 20 to the object refuses
// the path.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

// class-gate: allow Coord3D the canonical data-only header cannot declare the member-wise user copy constructor; retail copy-constructs the object position and the goal with three movss pairs while assigning with movsd
struct Coord3D
{
	Coord3D() {}
	Coord3D(const Coord3D &o) { x = o.x; y = o.y; z = o.z; }
	Real x, y, z;
	Real length() const;
	void normalize();
};

#include <math.h>

extern unsigned char g_00E03745;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);

extern int g_Va00DBA4E4;
#define LogicFramesPerSecond g_Va00DBA4E4

#include "../../../Common/GameLogicObjectLookupView.h"

enum PathfindLayerEnum
{
	LAYER_INVALID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_pos; }
	void rva0028ACDC(Int pos);
private:
	char m_pad00[0x38];
	Coord3D m_pos;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
};

class TerrainLogic
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02(); virtual void vslot03();
	virtual void vslot04(); virtual void vslot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal = 0) const;
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) const;
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

extern GameLogic *TheGameLogic;

class LocomotorSet;

class Pathfinder
{
public:
	bool queueForPath(ObjectID id);
	Bool adjustToMeleeDestination(Object *obj, const LocomotorSet &locomotorSet, Coord3D *dest);
};

class AIData
{
public:
	char m_pad00[0x94];
	Real m_meleeApproachDistance;
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }
	const AIData *getAiData() { return m_aiData; }
private:
	char m_pad00[0x10];
	Pathfinder *m_pathfinder;
	char m_pad14[0x18 - 0x14];
	AIData *m_aiData;
};
extern class AI *TheAI;

class Path;

class AIUpdateInterface
{
public:
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032();
	virtual void vslot033();
	virtual void vslot034();
	virtual void vslot035();
	virtual void vslot036();
	virtual void vslot037();
	virtual void vslot038();
	virtual void vslot039();
	virtual void vslot040();
	virtual void vslot041();
	virtual void vslot042();
	virtual void vslot043();
	virtual void vslot044();
	virtual void vslot045();
	virtual void vslot046();
	virtual void vslot047();
	virtual void vslot048();
	virtual void vslot049();
	virtual void vslot050();
	virtual void vslot051();
	virtual void vslot052();
	virtual void vslot053();
	virtual void vslot054();
	virtual void vslot055();
	virtual void vslot056();
	virtual void vslot057();
	virtual void vslot058();
	virtual void vslot059();
	virtual void vslot060();
	virtual void vslot061();
	virtual void vslot062();
	virtual void vslot063();
	virtual void vslot064();
	virtual void vslot065();
	virtual void vslot066();
	virtual void vslot067();
	virtual void vslot068();
	virtual void vslot069();
	virtual void vslot070();
	virtual void vslot071();
	virtual void vslot072();
	virtual void vslot073();
	virtual void vslot074();
	virtual void vslot075();
	virtual void vslot076();
	virtual void vslot077();
	virtual void vslot078();
	virtual void vslot079();
	virtual void vslot080();
	virtual void vslot081();
	virtual void vslot082();
	virtual void vslot083();
	virtual void vslot084();
	virtual void vslot085();
	virtual void vslot086();
	virtual void vslot087();
	virtual void vslot088();
	virtual void vslot089();
	virtual void vslot090();
	virtual void vslot091();
	virtual void vslot092();
	virtual void vslot093();
	virtual void vslot094();
	virtual void vslot095();
	virtual void vslot096();
	virtual void vslot097();
	virtual void vslot098();
	virtual void vslot099();
	virtual void vslot100();
	virtual void vslot101();
	virtual void vslot102();
	virtual void vslot103();
	virtual void vslot104();
	virtual void vslot105();
	virtual void vslot106();
	virtual void vslot107();
	virtual void vslot108();
	virtual void vslot109();
	virtual void vslot110();
	virtual void vslot111();
	virtual void vslot112();
	virtual void vslot113();
	virtual void vslot114();
	virtual void vslot115();
	virtual void vslot116();
	virtual void vslot117();
	virtual void vslot118();
	virtual void vslot119();
	virtual void vslot120();
	virtual void vslot121();
	virtual void vslot122();
	virtual void vslot123();
	virtual void vslot124();
	virtual void vslot125();
	virtual void vslot126();
	virtual void vslot127();
	virtual void vslot128();
	virtual void vslot129();
	virtual void vslot130();
	virtual void vslot131();
	virtual void vslot132();
	virtual void vslot133();
	virtual void vslot134();
	virtual void vslot135();
	virtual void setLocomotorGoalNone();

	Bool requestMeleeApproachPath(const Coord3D *destination, Bool exact);
	void setQueueForPathTime(Int frames);
	void destroyPath();

private:
	Object *getObject() const { return m_object; }

	char m_pad04[0x08 - 0x04];
	Object *m_object;
	char m_pad0C[0x140 - 0x0C];
	Path *m_path;
	ObjectID m_requestedVictimID;
	Coord3D m_requestedDestination;
	char m_pad154[0x160 - 0x154];
	UnsignedInt m_pathTimestamp;
	char m_pad164[0x1CC - 0x164];
	char m_locomotorSet[1];
	char m_pad1CD[0x3B1 - 0x1CD];
	Bool m_waitingForPath;
	Bool m_isAttackPath;
	Bool m_isFinalGoal;
	Bool m_isApproachPath;
	Bool m_isSafePath;
};

Bool AIUpdateInterface::requestMeleeApproachPath(const Coord3D *destination, Bool exact)
{
	Coord3D objPos = *getObject()->getPosition();
	Coord3D delta;
	delta.x = objPos.x - destination->x;
	delta.y = objPos.y - destination->y;
	delta.z = 0.0f;

	if (!exact && delta.length() > TheAI->getAiData()->m_meleeApproachDistance)
	{
		delta.normalize();
		const AIData *data = TheAI->getAiData();
		delta.x *= data->m_meleeApproachDistance;
		delta.y *= data->m_meleeApproachDistance;
	}

	Coord3D dest = *destination;
	if (!exact)
	{
		dest.x += delta.x;
		dest.y += delta.y;
		PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(getObject(), destination);
		Real heightDelta = fabs(TheTerrainLogic->getLayerHeight(dest.x, dest.y, layer) - TheTerrainLogic->getLayerHeight(destination->x, destination->y, layer));
		if (heightDelta > 10.0f)
			dest = *destination;
	}

	if (TheAI->pathfinder()->adjustToMeleeDestination(getObject(), *(const LocomotorSet *)m_locomotorSet, &dest))
	{
		getObject()->rva0028ACDC((Int)&dest);
		delta = objPos;
		delta.x -= dest.x;
		delta.y -= dest.y;
		delta.z = 0.0f;
		if (!(delta.length() < 20.0f))
		{
			if (g_00E03745)
			{
				void *log = theLogicRandomLogFile;
				if (log != 0)
					fprintf(log, "CritterDesync: requestMeleeApproachPath1 -- m_requestedDestination changing from %g,%g,%g to %g,%g,%g",
						m_requestedDestination.x, m_requestedDestination.y, m_requestedDestination.z,
						dest.x, dest.y, dest.z);
			}

			m_requestedDestination = dest;
			m_requestedVictimID = INVALID_OBJECT_ID;
			m_isFinalGoal = true;
			m_isAttackPath = false;
			m_isApproachPath = true;
			m_isSafePath = false;

			if (m_pathTimestamp > TheGameLogic->getFrame() - 2)
			{
				setQueueForPathTime(LogicFramesPerSecond + LogicFramesPerSecond);
				destroyPath();
				return true;
			}

			m_waitingForPath = true;
			TheAI->pathfinder()->queueForPath(getObject()->getID());
			return true;
		}
	}
	return false;
}

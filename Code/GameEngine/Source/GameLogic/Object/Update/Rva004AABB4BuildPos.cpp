// class-gate: allow AsciiString one-pointer str() view proved by the 426B body
// ?rva004AABB4@Rva004AABB4@@QAEPAVObject@@PAV2@0PAUCoord3D@@@Z @0x004AABB4 426B.
// Worker build-or-repair position. Bit 0x40 selects the four tower scan
// and the nearest squared distance under 1e10. Otherwise the 0x004AA4FE
// helper runs once and the target is returned. The 0x00E03CA8 flag gates
// the three log lines.

#include "../../../../../Libraries/Include/Lib/Coord3D.h"

struct _iobuf;
typedef struct _iobuf FILE;
extern "C" int __cdecl fprintf(FILE *stream, const char *format, ...);

extern unsigned char g_00E03CA8;
extern void *g_00DFEFF0;

enum ObjectID
{
	INVALID_OBJECTID = 0
};

class AsciiString
{
public:
	const char *str() const { return m_data ? m_data + 8 : ""; }
	char *m_data;
};

class Rva004AABB4Info
{
public:
	char m_pad00[0x64];
	AsciiString m_name;
	char m_pad68[0x10a - 0x68];
	unsigned char m_bits;
};

class AIUpdateInterface
{
public:
	bool isPathAvailable(const Coord3D *point) const;
};

class Object
{
public:
	char m_pad00[4];
	Rva004AABB4Info *m_info;
	char m_pad08[0x38 - 8];
	Coord3D m_pos;
	char m_pad44[0x74 - 0x44];
	int m_id;
	char m_pad78[0x258 - 0x78];
	AIUpdateInterface *m_checker;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

extern GameLogic *TheGameLogic;

class BridgeBehaviorInterface
{
public:
	virtual void gap0() = 0;
	virtual ObjectID endpoint(int index) = 0;
};

class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *object);
};

class Rva004AABB4
{
public:
	Object *rva004AABB4(Object *me, Object *target, Coord3D *out);
	bool rva004AA4FE(Object *me, Object *other, Coord3D *out);
};

Object *Rva004AABB4::rva004AABB4(Object *me, Object *target, Coord3D *out)
{
	if (g_00E03CA8 && g_00DFEFF0)
	{
		int targetId;
		const char *targetName;
		if (target)
			targetId = target->m_id;
		else
			targetId = 0;
		if (target)
			targetName = target->m_info->m_name.str();
		else
			targetName = "NULL";
		int meId = me->m_id;
		const char *meName = me->m_info->m_name.str();
		fprintf((FILE *)g_00DFEFF0,
			"  WorkerAIUpdate::findGoodBuildOrRepairPositionAndTarget() BEGIN: Object %s(%d) with target %s(%d)",
			meName, meId, targetName, targetId);
	}

	Object *result = target;
	if ((target->m_info->m_bits & 0x40) != 0)
	{
		if (g_00E03CA8 && g_00DFEFF0)
			fprintf((FILE *)g_00DFEFF0, "  target is a bridge case");
		BridgeBehaviorInterface *bridge =
			BridgeBehavior::getBridgeBehaviorInterfaceFromObject(target);
		if (bridge != 0)
		{
			if (g_00E03CA8 && g_00DFEFF0)
				fprintf((FILE *)g_00DFEFF0, "  target has a bridge behavior");
			AIUpdateInterface *checker = me->m_checker;
			float best = 10000000000.0f;
			result = 0;
			for (int index = 0; index < 4; ++index)
			{
				Object *found = TheGameLogic->findObjectByID(bridge->endpoint(index));
				if (found == 0)
					continue;
				Coord3D pos;
				if (!rva004AA4FE(me, found, &pos))
					continue;
				if (!checker->isPathAvailable(&pos))
					continue;
				float dx = me->m_pos.x - pos.x;
				float dy = me->m_pos.y - pos.y;
				float dist = dx * dx + dy * dy;
				if (dist < best)
				{
					*out = pos;
					best = dist;
					result = found;
				}
			}
			return result;
		}
	}
	rva004AA4FE(me, target, out);
	return result;
}

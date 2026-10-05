// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /G7 /DNDEBUG /MD /arch:SSE
// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z @0x002F314A 544B
// Evidence: LINK BONUS 2 files wait for this name; callers isViewBlockedByObstacle 0x002F3B92 and forwarder 0x002F3BAB; donor ZH AIPathfind.cpp isAttackViewBlockedByObstacle plus BFME1 bridge-layer TerrainLogic query; neighbours share /O1 /G7.
typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;
	float Normalize2D();
};

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

enum WeaponSlotType
{
	WEAPONSLOT_PRIMARY = 0
};

struct ThingTemplate
{
	unsigned char m_pad[0x108];
	unsigned char m_byte108;
	unsigned char m_pad109[0x10F - 0x109];
	unsigned char m_byte10F;
	unsigned char m_pad110[0x122 - 0x110];
	unsigned char m_byte122;
};

class Object
{
public:
	const class Weapon *getCurrentWeapon(WeaponSlotType *slot) const;
	Int rva0028B511() const;
private:
	char m_pad00[4];
public:
	ThingTemplate *m_template;
};

class Weapon
{
public:
	Int rva002CB9BD(const Object *source, const Coord3D *pos, const Object *victim);
};

struct TAiData
{
	unsigned char m_pad[0x67];
	unsigned char m_attackUsesLineOfSight;
};

class AI
{
public:
	const TAiData *getAiData() const { return m_aiData; }
private:
	char m_pad00[0x18];
	TAiData *m_aiData;
};
extern AI *g_Va009FF0F8;

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

extern float g_00BC4EB8;

class Rva002E73D4
{
public:
	Rva002E73D4(Int a, Int b, Int c);
	Int m_00;
	Int m_04;
	Int m_08;
	Int m_0C;
	Bool m_10;
	Int m_14;
	Int m_18;
};

struct Rva002F18D4Info
{
	Int cellCallback(void *a, void *b, Int x, Int y);
};

Int __cdecl Rva002E6E6CGet(Int v);

class Pathfinder
{
public:
	Bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D &sourcePos, const Object *victim, const Coord3D &victimPos);
	void *rva001E3647Pos(Int layer, const Coord3D *pos);
	Int iterateCellsAlongLine(const Coord3D *start, const Coord3D *end, PathfindLayerEnum layer, Rva002F18D4Info *info);
};

// ?isAttackViewBlockedByObstacle@Pathfinder@@QAE_NPBVObject@@ABUCoord3D@@01@Z present-unmatched
Bool Pathfinder::isAttackViewBlockedByObstacle(const Object *source, const Coord3D &sourcePos, const Object *victim, const Coord3D &victimPos)
{
	if (!g_Va009FF0F8->getAiData()->m_attackUsesLineOfSight)
		return false;
	if (victim == 0)
		return false;
	if ((source->m_template->m_byte10F & 8) == 0)
	{
		if ((source->m_template->m_byte122 & 0x40) == 0)
			return false;
	}
	Weapon *w = (Weapon *)source->getCurrentWeapon((WeaponSlotType *)0);
	if ((source->m_template->m_byte108 & 4) != 0)
		w = 0;
	if (w != 0)
	{
		Bool viewBlocked = !w->rva002CB9BD(source, &sourcePos, victim);
		if (viewBlocked)
			return true;
	}
	Int attackerLayer = source->rva0028B511();
	Int layer = victim->rva0028B511();
	if (attackerLayer != layer)
	{
		if ((attackerLayer >= 2 && attackerLayer <= 15) || (layer >= 2 && layer <= 15))
		{
			Real z = sourcePos.z;
			if (victimPos.z > z)
				z = victimPos.z;
			Coord3D tmp;
			tmp.x = sourcePos.x;
			tmp.y = sourcePos.y;
			tmp.z = z;
			PathfindLayerEnum attackerTerrainLayer = TheTerrainLogic->getLayerForDestination((Object *)0, &tmp);
			tmp.x = victimPos.x;
			tmp.y = victimPos.y;
			tmp.z = z;
			PathfindLayerEnum victimTerrainLayer = TheTerrainLogic->getLayerForDestination((Object *)0, &tmp);
			if (attackerTerrainLayer == victimTerrainLayer)
				return true;
		}
	}
	void *cell = rva001E3647Pos(layer, &victimPos);
	Rva002E73D4 info((Int)source, (Int)victim, (Int)cell);
	if (!Rva002E6E6CGet(source->rva0028B511()))
	{
		info.m_0C = 3;
		if (layer == LAYER_GROUND)
			layer = source->rva0028B511();
	}
	Coord3D tmp;
	tmp.x = sourcePos.x - victimPos.x;
	tmp.y = sourcePos.y - victimPos.y;
	tmp.z = sourcePos.z - victimPos.z;
	tmp.Normalize2D();
	tmp.x *= g_00BC4EB8;
	tmp.y *= g_00BC4EB8;
	tmp.z *= g_00BC4EB8;
	tmp.x += victimPos.x;
	tmp.y += victimPos.y;
	tmp.z += victimPos.z;
	Int ret = iterateCellsAlongLine(&sourcePos, &tmp, (PathfindLayerEnum)layer, (Rva002F18D4Info *)&info);
	return ret != 0;
}

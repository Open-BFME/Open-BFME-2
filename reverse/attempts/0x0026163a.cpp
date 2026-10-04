// ?rva0026163A@Rva0026163A@@QAE_NPBUCoord3D@@@Z
// partial score=0.95 date=2026-10-04
// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
// ?rva0026163A@Rva0026163A@@QAE_NPBUCoord3D@@@Z RVA 0x0026163A 151B
// Evidence: calls GeometryInfo::getMaxHeightAbovePosition 0x006BD7C0, TheTerrainLogic virtual +0x3c,
//   Pathfinder::isAttackViewBlockedByObstacle(Object*,Coord3D*) 0x002F3B9C; donor ZH PartitionManager
//   PartitionFilterLineOfSight::allow pattern with BFME2 height adjustment.

struct Coord3D
{
	float x;
	float y;
	float z;
};

class GeometryInfo
{
public:
	float getMaxHeightAbovePosition() const;
};

class Object
{
public:
	unsigned char _00[0x38];
	Coord3D m_pos;
	unsigned char _44[0xa8 - 0x44];
	GeometryInfo m_geom;
};

class Pathfinder
{
public:
	bool isAttackViewBlockedByObstacle(const Object *source, const Coord3D *targetPosition);
};

class AI
{
public:
	unsigned char _00[0x10];
	Pathfinder *m_pathfinder;
};

class TerrainLogic
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
	virtual bool checkClear(const Coord3D *a, const Coord3D *b);
};

extern TerrainLogic *TheTerrainLogic;
extern AI *g_Va009FF0F8;

class Rva0026163A
{
public:
	unsigned char _00[8];
	Object *m_obj;
	bool rva0026163A(const Coord3D *target);
};

// ?rva0026163A@Rva0026163A@@QAE_NPBUCoord3D@@@Z present-unmatched
bool Rva0026163A::rva0026163A(const Coord3D *target)
{
	Coord3D sourcePos;
	sourcePos.x = m_obj->m_pos.x;
	sourcePos.y = m_obj->m_pos.y;
	sourcePos.z = m_obj->m_pos.z;
	Coord3D targetPos;
	targetPos.x = target->x;
	targetPos.y = target->y;
	targetPos.z = target->z;
	sourcePos.z += m_obj->m_geom.getMaxHeightAbovePosition();
	if (!TheTerrainLogic->checkClear(&sourcePos, &targetPos))
		return false;
	AI *ai = g_Va009FF0F8;
	if (!ai)
		return true;
	Pathfinder *pf = ai->m_pathfinder;
	unsigned char blocked = pf->isAttackViewBlockedByObstacle(m_obj, &targetPos);
	if (blocked)
		return false;
	return true;
}

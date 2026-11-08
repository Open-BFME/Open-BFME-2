// cl: /DNDEBUG /MD /EHsc
// ?rva0026163A@Rva0026163A@@QAE_NPBUCoord3D@@@Z RVA 0x0026163A 151B
// Evidence: calls GeometryInfo::getMaxHeightAbovePosition 0x006BD7C0, TheTerrainLogic virtual +0x3c,
//   Pathfinder::isAttackViewBlockedByObstacle(Object*,Coord3D*) 0x002F3B9C; donor ZH PartitionManager
//   PartitionFilterLineOfSight::allow pattern with BFME2 height adjustment.

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../Include/Common/Geometry.h"

class Object
{
public:
	unsigned char _00[0x38];
	Coord3D m_pos;
	unsigned char _44[0xa8 - 0x44];
	GeometryInfo m_geom;
};

#include "../../Include/GameLogic/AIPathfind.h"

#include "../../Include/GameLogic/AI.h"

#include "../../Include/GameLogic/TerrainLogic.h"

extern TerrainLogic *TheTerrainLogic;

class Rva0026163A
{
public:
	unsigned char _00[8];
	Object *m_obj;
	bool rva0026163A(const Coord3D *target);
};

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
	if (!TheTerrainLogic->isClearLineOfSight(sourcePos, targetPos))
		return false;
	AI *ai = TheAI;
	if (ai != 0)
	{
		Pathfinder *pf = ai->m_pathfinder;
		bool blocked = pf->isAttackViewBlockedByObstacle(m_obj, &targetPos);
		if (blocked)
			return false;
	}
	return true;
}

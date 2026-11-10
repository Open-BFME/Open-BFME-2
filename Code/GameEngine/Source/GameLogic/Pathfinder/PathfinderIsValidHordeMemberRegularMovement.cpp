// cl: /O1  /DNDEBUG /MD /EHsc
// Native 002F06A3..002F07F5, 338B RET16; WB D60E80 names this method.
// Canonical by-value ABI provider: PathfinderSameCellRva002EE49B.cpp.
#include "../AI/PathfinderPositionValue.h"
#include "../../../../Libraries/Include/Lib/ICoord2D.h"
typedef bool Bool;
typedef int Int;
enum PathfindLayerEnum { PATHFIND_LAYER_UNKNOWN=0, PATHFIND_LAYER_GROUND=1 };
struct Rva002F06A3Template { char pad0[0x56c]; Int m_slopeLimitIndex; char pad570[0x634-0x570]; unsigned char m_canPathThroughGates; };
class Object {
public:
 bool rva0028AFBB() const;
 char *getAI() const { return m_ai; }
 void *vtable; Rva002F06A3Template *m_template;
 char pad8[0x258-8]; char *m_ai;
};
struct Rva002E8BCFSrc;
class Rva002E8BCF { public: Rva002E8BCF(const Rva002E8BCFSrc *,Bool,Int,Bool); Int surfaces;Bool field4,field5;Int maxLayer;Bool fieldC; };
#include "../../../Include/Common/Rva002E6DC4.h"
#include "../../../Include/GameLogic/PathfindCell.h"
#include "../../../Include/GameLogic/TerrainLogic.h"
extern TerrainLogic *TheTerrainLogic;
ICoord2D *Rva002EBC14Cell(ICoord2D *,void *,const Coord3D *);
int Rva002E6E8AGet(int);
#include "../../../Include/GameLogic/AIPathfind.h"
Bool Pathfinder::IsValidHordeMemberRegularMovement(Object *obj, const Coord3D *from,
	const Coord3D *to, const Coord3D *other)
{
 {
	if (rva002EE49B(obj, *to, *other))
		goto success;
	Int count = obj->m_template->m_slopeLimitIndex;
	unsigned char flag = obj->m_template->m_canPathThroughGates;
	char *ai = (char *)obj->getAI();
	Rva002E8BCF locomotors((const Rva002E8BCFSrc *)(ai + 0x1CC),
		flag == 0, count - 1, obj->rva0028AFBB());
	{
	PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, to);
	ICoord2D cell;
	Rva002EBC14Cell(&cell, obj, to);
	PathfindCell *toCell = getCell(layer, cell.x, cell.y);
	if (!((Rva002E6DC4 *)this)->rva002E6DC4(&locomotors, toCell))
		goto failure;
	PathfindLayerEnum fromLayer = TheTerrainLogic->getLayerForDestination(obj, from);
	if (fromLayer == layer)
		goto success;
	Rva002EBC14Cell(&cell, obj, from);
	PathfindCell *fromCell = getCell(fromLayer, cell.x, cell.y);
	unsigned int toInfo = toCell->m_0C;
	unsigned int fromInfo = fromCell->m_0C;
	if (((toInfo >> 6) ^ fromInfo) & 0x3f0)
	{
		if (!(((fromInfo >> 6) ^ toInfo) & 0x3f0))
			goto failure;
	}
	if (fromLayer != PATHFIND_LAYER_GROUND)
	{
		if (fromLayer == 16)
			goto success;
		if (!(unsigned char)Rva002E6E8AGet(fromLayer))
			goto success;
	}
if (layer != 16) goto failure;
	}
 }
 success: return true;
 failure: return false;
}

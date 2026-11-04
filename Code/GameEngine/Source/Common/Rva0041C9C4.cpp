// cl: /MD
// ?rva0041C9C4@ActionManager@@QAE_NPBVObject@@PBUCoord3D@@PBVSpecialPowerTemplate@@@Z, retail 0x0041C9C4, 52 bytes.
// Caller evidence: canDoSpecialPowerAtLocation at RVA 0x0041D6ED loads
// ECX=ActionManager before passing (object, location, special-power template).
// The implementation ignores its this pointer; RET 0xC alone did not prove
// the former free-stdcall declaration. The original helper name is unknown.
// The template override's flag bit 6 gates Pathfinder::QuickDoesPathExist.
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Object
{
public:
	char m_pad00[0x38];
	Coord3D m_pos38;
};

class Pathfinder;

#include "../../Include/GameLogic/AI.h"

extern AI *TheAI;

#include "../../Include/GameLogic/AIPathfind.h"

#include "../../Include/Common/Overridable.h"
#include "../../Include/Common/SpecialPower.h"
#include "../../Include/GameLogic/ActionManager.h"

bool ActionManager::rva0041C9C4(const Object *obj, const Coord3D *coord, const SpecialPowerTemplate *over)
{
	if ((((unsigned char)(over->getFO()->m_flags >> 6)) & 1) == 0)
		return true;
	Pathfinder *pf = TheAI->m_pathfinder;
	return pf->QuickDoesPathExist((Object *)obj, &obj->m_pos38, coord, 0);
}

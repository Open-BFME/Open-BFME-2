// cl: /MD
// ?rva0041C9C4@ActionManager@@QAE_NPBVObject@@PBUCoord3D@@PBVSpecialPowerTemplate@@@Z, retail 0x0041C9C4, 52 bytes.
// Caller evidence: canDoSpecialPowerAtLocation at RVA 0x0041D6ED loads
// ECX=ActionManager before passing (object, location, special-power template).
// The implementation ignores its this pointer; RET 0xC alone did not prove
// the former free-stdcall declaration. The original helper name is unknown.
// The template override's flag bit 6 gates Pathfinder::QuickDoesPathExist.
#include "../../../Libraries/Include/Lib/Coord3D.h"

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;
	void *m_vptr00;
	Overridable *m_next04;
	unsigned char m_alloc08;
	char m_pad09[0x18 - 0x09];
	unsigned int m_18;
};

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

class SpecialPowerTemplate : public Overridable {};
#include "../../Include/GameLogic/ActionManager.h"

bool ActionManager::rva0041C9C4(const Object *obj, const Coord3D *coord, const SpecialPowerTemplate *over)
{
	const Overridable *final = over->friend_getFinalOverride();
	if ((((unsigned char)(final->m_18 >> 6)) & 1) == 0)
		return true;
	Pathfinder *pf = TheAI->m_pathfinder;
	return pf->QuickDoesPathExist((Object *)obj, &obj->m_pos38, coord, 0);
}

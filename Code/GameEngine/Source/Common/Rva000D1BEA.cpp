// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva000D1BEA@Rva000D1BEA@@QAEEH@Z @0x000D1BEA 38B
// Shroud-gated bool helper: returns false when TheShroudManager is null,
// else whether PartitionManager::getShroudStatusForPlayer(playerIndex,
// this+0x48) >= 1. Evidence: retail mov eax,[0x00DFE74C] test/je, add ecx,0x48,
// push pair, mov ecx,eax, call rowed 0x007397F0, cmp eax,1 jl to xor al,al,
// else mov al,1; caller 0x000D252F in 0x000D2301; global 0x00DFE74C is
// TheShroudManager per PartitionManagerRva003BCFC9.cpp.

#include "../../../Libraries/Include/Lib/Coord3D.h"

enum CellShroudStatus
{
	CELLSHROUD_CLEAR = 0
};

class PartitionManager
{
public:
	CellShroudStatus getShroudStatusForPlayer(int playerIndex, const Coord3D *pos) const;
};
extern PartitionManager *TheShroudManager;


class Rva000D1BEA
{
public:
	unsigned char rva000D1BEA(int playerIndex);

private:
	unsigned char m_pad[0x48];
	Coord3D m_pos; // +0x48
};

unsigned char Rva000D1BEA::rva000D1BEA(int playerIndex)
{
	if (TheShroudManager != 0)
	{
		if ((int)TheShroudManager->getShroudStatusForPlayer(playerIndex, &m_pos) >= 1)
			return 1;
	}
	return 0;
}

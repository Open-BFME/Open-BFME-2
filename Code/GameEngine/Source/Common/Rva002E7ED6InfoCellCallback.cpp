// cl: /O1 /DNDEBUG /MD
// ?cellCallback@Rva002E7ED6Info@@QAEHPAVPathfindCell@@0HH@Z @0x002E7ED6 72B
// Banked attempt reverse/attempts/0x002e7ed6.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
//
// ?cellCallback@Rva002E7ED6Info@@QAEHPAVPathfindCell@@0HH@Z @0x002E7ED6 72B
// Evidence: pin cellCallback; rowed Rva002E6E8AGet 0x002E6E8A; pinned rva002E79A8 0x002E79A8 returns pointer in eax per retail mov esi eax but pin types it void; probe uses int return to reproduce mov; caller Pathfinder::iterateCellsAlongLine 0x002E8B0C.
// Finish from stash 0x002e7ed6.cpp score 0.98; fix lea esi ebp-0c vs mov esi eax.

class PathfindCell
{
public:
	char m_pad[0x0C];
	unsigned int m_0C;
};

int __cdecl Rva002E6E8AGet(int v);
int __cdecl rva002E79A8_ret(int a1, unsigned char a2, int a3, int a4, int a5);

struct Rva002E7ED6Info
{
	float m_x;
	float m_y;
	float m_z;
	int cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, int cellX, int cellY);
};

int Rva002E7ED6Info::cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, int cellX, int cellY)
{
	int v = (currentCell->m_0C >> 4) & 0x3F;
	if ((unsigned char)Rva002E6E8AGet(v))
		return 0;
	Rva002E7ED6Info tmp;
	Rva002E7ED6Info *p = (Rva002E7ED6Info *)rva002E79A8_ret((int)&tmp, 1, cellX, cellY, v);
	*this = *p;
	return 1;
}

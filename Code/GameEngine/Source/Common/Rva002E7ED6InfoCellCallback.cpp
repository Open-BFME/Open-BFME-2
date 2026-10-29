// cl: /ICode/Libraries/Include /O1 /DNDEBUG /MD
// ?cellCallback@Rva002E7ED6Info@@QAEHPAVPathfindCell@@0HH@Z @0x002E7ED6 72B
// Banked attempt reverse/attempts/0x002e7ed6.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
//
// ?cellCallback@Rva002E7ED6Info@@QAEHPAVPathfindCell@@0HH@Z @0x002E7ED6 72B
// Evidence: pin cellCallback; rowed Rva002E6E8AGet 0x002E6E8A; rowed rva002E79A8 0x002E79A8 returns its centre by value (retail copies from the EAX it returns: mov esi eax); caller Pathfinder::iterateCellsAlongLine 0x002E8B0C.
// Finish from stash 0x002e7ed6.cpp score 0.98; fix lea esi ebp-0c vs mov esi eax.

#include "Lib/Coord3D.h"

class PathfindCell
{
public:
	char m_pad[0x0C];
	unsigned int m_0C;
};

int __cdecl Rva002E6E8AGet(int v);
struct PathfinderCellPoint : Coord3D {};
enum PathfindLayerEnum { LAYER_INVALID = 0 };
PathfinderCellPoint rva002E79A8(bool centerInCell, int cellX, int cellY, PathfindLayerEnum layer);

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
	*(Coord3D *)this = rva002E79A8(true, cellX, cellY, (PathfindLayerEnum)v);
	return 1;
}

// Native 0x002E7D6D..0x002E7DF5, RET16. Same consumed PathfindCell
// flags +C and four-argument callback ABI as the rowed sibling above.
// The original context type and method name remain unproven. Retail
// consumes provider +0, Coord3D output +4, layer +8, 16-byte query +C,
// and the predicate-enable byte +1C. Only output X/Y are changed.
// The full rowed 2E6DC4 predicate consumes the query and current cell;
// rowed 2E6E8A supplies the byte-range predicate. No new pins are needed.
class Rva002E6DC4
{
public:
	bool rva002E6DC4(void *a_raw, void *b_raw);
	char m_pad00[0x48];
private:
	void *m_48; // +0x48
};

#include "Rva002E7D6DInfo.h"

int Rva002E7D6DInfo::cellCallback(PathfindCell *previousCell,
                               PathfindCell *currentCell, int cellX, int cellY)
{
 unsigned int flags=currentCell->m_0C;
 unsigned int kind=flags&0xF;
 if (kind==5 || kind==2 || kind==4)
  return 1;
 if (m_check && !m_provider->rva002E6DC4(&m_query,currentCell))
  return 1;
 if (m_layer==1 && (unsigned char)Rva002E6E8AGet((flags>>4)&0x3F))
  return 1;
 m_layer=(flags>>4)&0x3F;
 m_result->x=(float)(cellX*10);
 m_result->y=(float)(cellY*10);
 return 0;
}

// Native 2E7B29..2E7BB8 RET16; matched line walk8448 proves callback ABI.
// Native context: Pathfinder pointer +0, requested footprint +4, Coord3D +8.
// The rowed 2EDFBD caller initializes this via 2E7B02(this,4,*position),
// passes it to the rowed 2EB3D7/2E8448 line walk and copies the output back.
// 2E7749 has a native RET24 contract and returns an achieved footprint;
// its purpose is inferred from its square-cell checks, not a recovered name.
// 2E79A8 returns the coordinate temporary through EAX, as the rowed sibling
// above already establishes. Original callback/context names remain unknown.
class Pathfinder
{
public:
 int rva002E7749(void *object, int x, int y, int layer, int clearance, bool exact);
};
bool Rva001E3679(int value);
struct Rva002E7B29Info
{
 Pathfinder *provider;
 int clearance;
 Coord3D result;
 int cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, int cellX, int cellY);
};
int Rva002E7B29Info::cellCallback(PathfindCell *previousCell, PathfindCell *currentCell, int cellX, int cellY)
{
 if (previousCell) {
  int layer=(currentCell->m_0C>>4)&0x3F;
  if (Rva001E3679(layer) && ((previousCell->m_0C>>4)&0x3F)==layer)
   return 0;
 }
 if (provider->rva002E7749(0,cellX,cellY,(currentCell->m_0C>>4)&0x3F,clearance,true)==clearance) {
  result=rva002E79A8(true,cellX,cellY,(PathfindLayerEnum)((currentCell->m_0C>>4)&0x3F));
  return 0;
 }
 return 1;
}

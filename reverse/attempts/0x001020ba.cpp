// ??4?$vector@URva00111B25Record@@V?$allocator@URva00111B25Record@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z
// partial score=0.883495 date=2026-10-04
// cl: /O1 -GX-
// stlport
// BFME1 donor 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/R4VectorDtorWideElems.cpp, Gen00425060.
// Whole donor family /O1: assignment 0x001020BA/206B is the lead.
// Target: Ghidra 206B, vector stride28; allocation/copy 0x00101F5C,
// clear 0x000B0298, copy wrapper 0x00101F89, destroy 0x000AFF52,
// uninitialized copy 0x00101ECF. Destroy reaches rowed 0x00111B25,
// the two-string teardown (+0x18 then +0). Original record identity unknown.
// The existing BfmeStringRecord00111ACF name must not be reused blindly:
// its pinned destructor 0x003F60C8 destroys a buffer and vector, whereas
// this target calls the two-string destructor. The existing home unit
// also has unresolved/default-constructor and wrong-selected blockers.
// No relocation masking is full-byte proof. Helpers require native name
// reconciliation and exact linking before this can be a matched row.
#include <vector>

struct Rva00111B25Record
{
	Rva00111B25Record();
	Rva00111B25Record(const Rva00111B25Record &);
	~Rva00111B25Record();
	Rva00111B25Record &operator=(const Rva00111B25Record &);
	char body[28];
};

template _STL::vector<Rva00111B25Record> &
_STL::vector<Rva00111B25Record>::operator=(const _STL::vector<Rva00111B25Record> &);

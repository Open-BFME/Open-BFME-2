// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ??0PolygonTrigger@@QAE@H@Z, retail 0x002e3eb8, 166 bytes. Banked partial (score 0.9) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native constructor 0x2E3EB8..0x2E3F5E; WB 0xAB9AE0.
// Native secondary interface has one pure virtual at C1C780 and trivial destruction;
// native derived entry C04C78 points to this-38 thunk002E37C3 ->002E37B1.
// Primary vtable C04C7C has13 entries; this provisional base declaration is incomplete.
// Native 330C50..330CC2: primary vptr +0, vbptr +4, container +8,
// flag +34, vtordisp +38, seven-slot virtual interface +3C.
// The vbtable contains {-4, 0x38}; interface thunks 2E3E80..2E3EB0
// each subtract the vtordisp before dispatching the corresponding member.
#include "../../../Libraries/Include/Lib/Region2D.h"
struct Rva0030B72CPoint {
 Rva0030B72CPoint() {}
 __forceinline Rva0030B72CPoint(const Rva0030B72CPoint &p):x(p.x),y(p.y) {}
 float x,y;
};

#include "../../Include/GameLogic/PolygonTrigger.h"
PolygonTrigger::PolygonTrigger(int n):id(s_currentID++) { rva002E36B7(n); }

// The class's destructor: this unit's constructor row stores the vftable whose slot 0 is the
// deleting destructor at 0x002E424F, and its body calls 0x002E4049, where the destructor row lives.
#pragma comment(linker, "/alternatename:??1PolygonTrigger@@UAE@XZ=??1Rva002E4049@@UAE@XZ")

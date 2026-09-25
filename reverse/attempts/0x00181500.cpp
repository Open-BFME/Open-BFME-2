// ??$_M_allocate_and_copy@PAUAngleFXInfo@@@?$vector@UAngleFXInfo@@V?$allocator@UAngleFXInfo@@@_STL@@@_STL@@IAEPAUAngleFXInfo@@IPAU2@0@Z
// partial score=0.95 date=2026-09-25
// cl: /O2 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<AngleFXInfo>::_M_allocate_and_copy at 0x00181500, the
// reallocation path of StructureToppleUpdate's angle-FX list. Split out of
// AngleFXInfoVectorInsertOverflow.cpp because that unit's flags emit an
// indexed 8-byte copy loop (79B) while retail uses a pointer-chase loop
// (76B). Best variant is /O2 /G7 (n*8 via three adds matches retail) but the
// loop stays indexed under every tried flag set (-O2 /G6 /G7 /G7+SSE /Oa
// /Ox /Os /O1; /O1 and /Os outline to a 45B worker call; /Og- explodes).
// Likely a newer-STLport __copy_ptrs source than vendored 4.5.3; the twin
// pair<int,int> body at 0x00627960 shows the same chase shape with shl.

#include <vector>

class FXList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
struct AngleFXInfo
{
	float angle;
	FXList *fxList;
};

template class _STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> >;

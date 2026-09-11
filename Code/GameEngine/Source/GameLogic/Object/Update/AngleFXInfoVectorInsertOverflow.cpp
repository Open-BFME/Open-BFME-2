// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<AngleFXInfo>::_M_insert_overflow at 0x00626150, the
// growth path of StructureToppleUpdate's angle-FX list.  Split out of
// StructureToppleUpdate.cpp because retail built this body without /G7 --
// dec ecx and a byte load plus test where that unit writes sub ecx,1 and a
// compare against memory -- and with the bfmealloc allocator (two-argument
// allocate at 0x000307F0, one-argument _free at 0x00030830).

#include <vector>

class FXList;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/StructureToppleUpdate.h
struct AngleFXInfo
{
	float angle;
	FXList *fxList;
};

template class _STL::vector<AngleFXInfo, _STL::allocator<AngleFXInfo> >;

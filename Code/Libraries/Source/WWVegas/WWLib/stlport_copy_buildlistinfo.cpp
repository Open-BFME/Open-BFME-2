// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__copy@PAVBuildListInfo@@PAV1@H@_STL@@YAPAVBuildListInfo@@PAV1@00ABUrandom_access_iterator_tag@0@PAH@Z @0x00329D64 52B
// ??$copy@PAVBuildListInfo@@PAV1@@_STL@@YAPAVBuildListInfo@@PAV1@00@Z @0x0032A40E 29B
// STLport copy/__copy for BuildListInfo (0x80 bytes, sar 7, operator= loop).
// Evidence: __copy calls rowed ??4BuildListInfo@@QAEAAV0@ABV0@@Z at 0x003299AD;
// copy calls __copy; both byte-exact via explicit instantiation of copy.
// Layout matches BuildListInfoAssign.cpp (3 AsciiStrings, Coord3D+Coord2D+Real,
// 9 bools, ObjectID/timestamp, 10 gatherers, desired/current).

#include <algorithm>

#include "ascii_string.h"


#include "../../../Include/Lib/Coord3D.h"

#include "../../../Include/Lib/Coord2D.h"

#include "../../../../GameEngine/Include/GameLogic/Bfme2BuildListInfo.h"

// ??$__copy_ptrs@PAVBuildListInfo@@PAV1@@_STL@@YAPAVBuildListInfo@@PAV1@00U__false_type@0@@Z present-unmatched
// ??$__copy_aux@PAVBuildListInfo@@PAV1@@_STL@@YAPAVBuildListInfo@@PAV1@00U__true_type@0@@Z present-unmatched
// ?_Ret@?$_BothPtrType@PAVBuildListInfo@@PAV1@@_STL@@SA?AU__true_type@2@XZ present-unmatched
// ?_Ret@?$_OKToMemCpy@VBuildListInfo@@V1@@_STL@@SA?AU__false_type@2@XZ present-unmatched
// ??$_IsOKToMemCpy@VBuildListInfo@@V1@@_STL@@YA?AU?$_OKToMemCpy@VBuildListInfo@@V1@@0@PAVBuildListInfo@@0@Z present-unmatched
template BuildListInfo *_STL::copy<BuildListInfo *, BuildListInfo *>(BuildListInfo *, BuildListInfo *, BuildListInfo *);

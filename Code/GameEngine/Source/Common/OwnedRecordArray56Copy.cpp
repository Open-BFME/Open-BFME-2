// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// The target copies 56 eight-byte records with established copy/cleanup callbacks.
// Each record owns a reference at +4; original array and owner names are unknown.
#include <vector>

#include "../../Include/Common/Rva002390CB.h"

class BfmeOwnedRecordArray56 {
    Rva002390CB m_records[56];
public:
    BfmeOwnedRecordArray56();
};

typedef char RecordStride[sizeof(Rva002390CB) == 8 ? 1 : -1];
typedef char RecordArrayExtent[sizeof(BfmeOwnedRecordArray56) == 448 ? 1 : -1];

template void _STL::_Construct<BfmeOwnedRecordArray56, BfmeOwnedRecordArray56>(
    BfmeOwnedRecordArray56 *, const BfmeOwnedRecordArray56 &);

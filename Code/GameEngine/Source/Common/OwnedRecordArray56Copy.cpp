// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// The target copies 56 eight-byte records with established copy/cleanup callbacks.
// Each record owns a reference at +4; original array and owner names are unknown.
#include <vector>

class Rva002390CB {
    void *m_unknown;
    void *m_owner;
public:
    __declspec(nothrow) Rva002390CB(const Rva002390CB &);
    ~Rva002390CB();
};

class BfmeOwnedRecordArray56 {
    Rva002390CB m_records[56];
public:
    BfmeOwnedRecordArray56();
};

typedef char RecordStride[sizeof(Rva002390CB) == 8 ? 1 : -1];
typedef char RecordArrayExtent[sizeof(BfmeOwnedRecordArray56) == 448 ? 1 : -1];

template void _STL::_Construct<BfmeOwnedRecordArray56, BfmeOwnedRecordArray56>(
    BfmeOwnedRecordArray56 *, const BfmeOwnedRecordArray56 &);

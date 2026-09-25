// ??0?$_Vector_base@VSaveMapPreview@@V?$allocator@VSaveMapPreview@@@_STL@@@_STL@@QAE@IABV?$allocator@VSaveMapPreview@@@1@@Z
// partial score=0.95 date=2026-09-25
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// _STL::_Vector_base<SaveMapPreview> sizing constructor at 0x004FF36C, the
// 60-byte three-pointer plus count*20 allocation prologue of the
// SaveMapPreview vector family. Split out of SaveMapPreviewCopy.cpp because
// retail multiplies the count with imul (P4 codegen) while that unit builds
// the neighboring allocate_and_copy without /G7. The allocator call resolves
// through the pinned SaveMapPreview allocator at 0x00395960 and the proxy
// call through the harvested twin pin at 0x0014F3C4. Model matches
// SaveMapPreviewCopy.cpp (Snapshot vptr plus 16 payload bytes, 20 total).
#include <vector>
class Xfer;
class Snapshot {
public:
    __forceinline virtual ~Snapshot() {}
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
class SaveMapPreview : public Snapshot {
public:
    unsigned int word04;
    struct Words { unsigned int a,b,c; } words08;
    virtual ~SaveMapPreview();
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
typedef char SaveMapPreviewSizeCheck[sizeof(SaveMapPreview)==20 ? 1 : -1];
// ??0?$_Vector_base@VSaveMapPreview@@V?$allocator@VSaveMapPreview@@@_STL@@@_STL@@QAE@IABV?$allocator@VSaveMapPreview@@@1@@Z present-unmatched
template _STL::_Vector_base<SaveMapPreview, _STL::allocator<SaveMapPreview> >::_Vector_base(unsigned int, const _STL::allocator<SaveMapPreview> &);

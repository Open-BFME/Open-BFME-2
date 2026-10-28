// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva0052CD81@@QAE@ABV0@@Z @ 0x0052CD81 96B. STLport vector<SaveMapPreview>
// copy constructor: _Vector_base(count, get_allocator()) then the 20-byte-stride
// __uninitialized_copy pinned at 0x0052C987 (call site 0x52CDC4). Retail vtable
// 0xBE7258 and the 20-byte SaveMapPreview layout are established by the landed
// SaveMapPreviewCopy.cpp; the non-const range instantiation is an ICF twin of the
// Rva004E194E pin at the same address.
#include <vector>
// Suppress this TU's non-retail copy of ??$_Construct@VSaveMapPreview@@V1@@_STL@@YAXPAVSaveMapPreview@@ABV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class SaveMapPreview;
namespace _STL { template <> void _Construct<SaveMapPreview,SaveMapPreview>(SaveMapPreview *,SaveMapPreview const &); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAVSaveMapPreview@@V1@V?$allocator@VSaveMapPreview@@@_STL@@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class SaveMapPreview;
namespace _STL { template <> SaveMapPreview * _STLP_alloc_proxy<SaveMapPreview *,SaveMapPreview,allocator<SaveMapPreview> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VSaveMapPreview@@@_STL@@QBEXPAVSaveMapPreview@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class SaveMapPreview;
namespace _STL { template <> void allocator<SaveMapPreview>::deallocate(SaveMapPreview *,unsigned int) const; }
// The copy constructor calls _Vector_base(n, alloc) out of line; this unit's
// /O1 copy of it is not retail's (Rva0054103EVectorInsertOverflow.cpp's is).
namespace _STL { template <> _Vector_base<SaveMapPreview, allocator<SaveMapPreview> >::_Vector_base(unsigned int, allocator<SaveMapPreview> const &); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
class Xfer;
class Rva002262E7SnapshotBase {
public:
    virtual ~Rva002262E7SnapshotBase();
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
class SaveMapPreview : public Rva002262E7SnapshotBase {
public:
    unsigned int word04;
    struct Words { unsigned int a,b,c; } words08;
    SaveMapPreview(const SaveMapPreview &o);
    virtual ~SaveMapPreview();
    virtual void crc(Xfer *);
    virtual const char *typeName() const;
    virtual void xfer(Xfer *);
};
class AsciiString;
class Rva0052CD81 : public _STL::_Vector_base<SaveMapPreview, _STL::allocator<SaveMapPreview> >
{
public:
    Rva0052CD81(const Rva0052CD81 &x);
};
Rva0052CD81::Rva0052CD81(const Rva0052CD81 &x)
    : _STL::_Vector_base<SaveMapPreview, _STL::allocator<SaveMapPreview> >(x._M_finish - x._M_start, *(const _STL::allocator<SaveMapPreview> *)&((const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &)x).get_allocator())
{
    _M_finish = (SaveMapPreview *)_STL::__uninitialized_copy(x._M_start, x._M_finish, _M_start, _STL::__false_type());
}

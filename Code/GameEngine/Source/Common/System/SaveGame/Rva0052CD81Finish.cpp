// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ??0Rva0052CD81@@QAE@ABV0@@Z @ 0x0052CD81 96B. STLport vector<SaveMapPreview>
// copy constructor: _Vector_base(count, get_allocator()) then the 20-byte-stride
// __uninitialized_copy pinned at 0x0052C987 (call site 0x52CDC4). Retail vtable
// 0xBE7258 and the 20-byte SaveMapPreview layout are established by the landed
// SaveMapPreviewCopy.cpp; the non-const range instantiation is an ICF twin of the
// Rva004E194E pin at the same address.
#include <vector>
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

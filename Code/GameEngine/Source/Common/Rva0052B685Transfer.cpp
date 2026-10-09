// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <memory>

// Native52B685..52B6AC transfers the four-byte owning pointer into
// an auto_ptr result. WB131BB10 independently shows clearing the receiver
// and copying a local owner into the hidden return buffer; its moved-from
// local deletes through virtual slot0 with flag1. The two-step transfer is
// the same vendored STLport operation recovered at42C23A and42C993.
// The original holder and pointee identities remain unknown.
class Rva0052B685Pointee
{
public:
    virtual ~Rva0052B685Pointee();
};

class Rva0052B685Holder
{
public:
    _STL::auto_ptr<Rva0052B685Pointee> release();
    Rva0052B685Pointee *ptr;
};

_STL::auto_ptr<Rva0052B685Pointee> Rva0052B685Holder::release()
{
    _STL::auto_ptr<Rva0052B685Pointee> result(ptr);
    ptr = 0;
    return result;
}


// cl: /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <memory>

// Retail42C261 and WB12BC370 CreateTurnPhaseBehavior show a four-byte
// pooled owner transferring its pointer into an STLport auto_ptr. The native
// helper42C23A..42C261 clears the owner and constructs the return buffer;
// the factory then uses auto_ptr_ref's two-word release and virtual deletion.
// The pointee and holder retain address-derived names pending their contract.
class Rva0042C23APointee
{
public:
    virtual ~Rva0042C23APointee();
};

class Rva0042C23AHolder
{
public:
    _STL::auto_ptr<Rva0042C23APointee> release();
    Rva0042C23APointee *ptr;
};

_STL::auto_ptr<Rva0042C23APointee> Rva0042C23AHolder::release()
{
    _STL::auto_ptr<Rva0042C23APointee> result(ptr);
    ptr = 0;
    return result;
}

// Native42C993..42C9BA is a distinct transfer instantiation for the factory
// at42C9BA. That factory allocates the eight-byte Rva00577838, whose rowed
// constructor and vtable differ from the three turn-phase allocations above.
class Rva0042C993Pointee
{
public:
    virtual ~Rva0042C993Pointee();
};

class Rva0042C993Holder
{
public:
    _STL::auto_ptr<Rva0042C993Pointee> release();
    Rva0042C993Pointee *ptr;
};

_STL::auto_ptr<Rva0042C993Pointee> Rva0042C993Holder::release()
{
    _STL::auto_ptr<Rva0042C993Pointee> result(ptr);
    ptr = 0;
    return result;
}

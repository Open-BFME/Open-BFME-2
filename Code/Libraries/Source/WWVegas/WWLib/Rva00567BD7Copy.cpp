// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00567BD7@@QAE@ABV0@@Z @0x00567BD7 38B
// Evidence: __thiscall copy ctor (ret 4, returns this); copies +0 dword, +4 byte, +8 refptr with inc [edx+4], +0xC byte.
// Caller 0x00567F91 conditionally copy-constructs; unblocks 0x00567F91.
// The existing 38-byte copy constructor fixes the 16-byte record layout.
// Its vector constructor at 568182 is called by the named stance-button Impl
// constructor. The prototype writes action+0, reference+8 and active+C;
// the byte at +4 remains unspecified. Original record/type names are unknown.
//
// Keep the complete copy/fill chain visible: the compiler proves its calls
// cannot throw. The owning prototype destructor tests its zero reference;
// that path vanishes after EH setup, leaving retail's frame and unused unwind
// entry but eliminating the saved-this and state-0 stores. Declaring the fill
// opaque adds those stores; removing ownership eliminates the whole EH frame.
// No shared vendor header is changed.
#include <vector>
#include "../../Apt/AptRefTarget.h"
class Rva00567BD7
{
public:
    int action;
    unsigned char unused;
    TargetRef00217D4C *ref;
    bool active;

    Rva00567BD7() : action(0), ref(0), active(false) {}
    Rva00567BD7(const Rva00567BD7 &);
    // ?Rva00567BD7::~Rva00567BD7 present-unmatched
    ~Rva00567BD7()
    {
        if (ref)
            ReleaseTreeHintRef00217D4C(ref);
    }
};
namespace _STL {
 template<> Rva00567BD7 *uninitialized_fill_n<Rva00567BD7*,unsigned,Rva00567BD7>(Rva00567BD7*,unsigned,const Rva00567BD7 &);
}

__declspec(noinline) Rva00567BD7::Rva00567BD7(const Rva00567BD7 &s)
{
    action = s.action;
    unused = s.unused;
    ref = s.ref;
    if (ref)
        ++ref->references;
    active = s.active;
}

inline __declspec(noinline) void Rva00567F91Copy(Rva00567BD7 *dst, const Rva00567BD7 *src)
{
    if (dst)
        new(dst) Rva00567BD7(*src);
}
namespace _STL {
template<> inline __declspec(noinline) Rva00567BD7 *__uninitialized_fill_n<Rva00567BD7*,unsigned,Rva00567BD7>(Rva00567BD7 *first,unsigned n,const Rva00567BD7 &v,const __false_type &) {
    Rva00567BD7 *cur = first;
    for (; n > 0; --n, ++cur)
        Rva00567F91Copy(cur, &v);
    return cur;
}
template<> inline __declspec(noinline) Rva00567BD7 *uninitialized_fill_n<Rva00567BD7*,unsigned,Rva00567BD7>(Rva00567BD7 *first,unsigned n,const Rva00567BD7 &v) {
    return __uninitialized_fill_n(first, n, v, __false_type());
}
}
class Rva005681CE : public _STL::_Vector_base<Rva00567BD7, _STL::allocator<Rva00567BD7> >
{
public:
    explicit Rva005681CE(unsigned n);
    ~Rva005681CE();
};
Rva005681CE::Rva005681CE(unsigned n)
    : _STL::_Vector_base<Rva00567BD7, _STL::allocator<Rva00567BD7> >(n, _STL::allocator<Rva00567BD7>())
{
    _M_finish = _STL::uninitialized_fill_n(_M_start, n, Rva00567BD7());
}

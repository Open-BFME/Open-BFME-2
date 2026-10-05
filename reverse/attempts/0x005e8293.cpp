// ?insert@?$vector@URva005E71C6Ref@@V?$allocator@URva005E71C6Ref@@@_STL@@@_STL@@QAEPAURva005E71C6Ref@@PAU3@ABU3@@Z
// partial score=0.94 date=2026-10-05
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?insert@?$vector@URva005E71C6Ref@@V?$allocator@URva005E71C6Ref@@@_STL@@@_STL@@QAEPAURva005E71C6Ref@@PAU3@ABU3@@Z @0x005E8293 189B
// STLport 4.5.3 vector<Rva005E71C6Ref>::insert single-element. Evidence: _Construct 0x005E71C6 pinned alias of rowed Assign,
// operator= 0x005E7198 rowed, overflow 0x005E818E rowed, copy_backward forwarder 0x005E7470 rowed as Forward to loop 0x005E7256,
// Release 0x0007DEEF rowed; caller unclaimed at 0x005E868F; prev push_back 0x005E825C same family.
#include <stl/_algobase.h>
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
struct TargetRef00217D4C {
    virtual void *destroy(unsigned int flags);
    int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct Rva005E7198Object {
    unsigned char m_pad[0x24];
    TargetRef00217D4C m_ref;
};
class Rva005E7198 {
public:
    Rva005E7198 &operator=(const Rva005E7198 &other);
private:
    Rva005E7198Object *m_object;
};
struct Rva005E71C6Ref {
    Rva005E7198Object *m_object;
    Rva005E71C6Ref(const Rva005E71C6Ref &other) {
        m_object = other.m_object;
        if (m_object)
            ++m_object->m_ref.references;
    }
    ~Rva005E71C6Ref() {
        if (m_object)
            ReleaseTreeHintRef00217D4C(&m_object->m_ref);
    }
    Rva005E71C6Ref &operator=(const Rva005E71C6Ref &other) {
        ((Rva005E7198 *)this)->operator=(*(const Rva005E7198 *)&other);
        return *this;
    }
};
namespace _STL {
template <> __declspec(nothrow) void _Construct<Rva005E71C6Ref, Rva005E71C6Ref>(Rva005E71C6Ref *__p, const Rva005E71C6Ref &__val);
}
Rva005E7198 *__cdecl Rva005E7470Forward(Rva005E7198 *first, Rva005E7198 *last, Rva005E7198 *result, void *tag);
namespace _STL {
inline Rva005E71C6Ref *__copy_backward_ptrs(Rva005E71C6Ref *__first, Rva005E71C6Ref *__last, Rva005E71C6Ref *__result, const __false_type &) {
    char __tag;
    return (Rva005E71C6Ref *)Rva005E7470Forward((Rva005E7198 *)__first, (Rva005E7198 *)__last, (Rva005E7198 *)__result, &__tag);
}
}
// ?insert@?$vector@URva005E71C6Ref@@V?$allocator@URva005E71C6Ref@@@_STL@@@_STL@@QAEPAURva005E71C6Ref@@PAU3@ABU3@@Z present-unmatched
template _STL::vector<Rva005E71C6Ref>::iterator _STL::vector<Rva005E71C6Ref>::insert(Rva005E71C6Ref *, const Rva005E71C6Ref &);

// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
//
// ?rva004F92E3@Rva004F92E3@@QAEXPAX@Z, retail 0x004f92e3, 149 bytes. Banked partial (score 0.92) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAURva004F8D92Element@@PAU1@@_STL@@YAPAURva004F8D92Element@@PAU1@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004F8D92Element;
namespace _STL { template <> Rva004F8D92Element * __uninitialized_copy<Rva004F8D92Element *,Rva004F8D92Element *>(Rva004F8D92Element *,Rva004F8D92Element *,Rva004F8D92Element *,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAURva004F8D92Element@@IU1@@_STL@@YAPAURva004F8D92Element@@PAU1@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> Rva004F8D92Element * __uninitialized_fill_n<Rva004F8D92Element *,unsigned int,Rva004F8D92Element>(Rva004F8D92Element *,unsigned int,Rva004F8D92Element const &,__false_type const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@URva004F8D92Element@@V?$allocator@URva004F8D92Element@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004F8D92Element;
namespace _STL { template <> void vector<Rva004F8D92Element,allocator<Rva004F8D92Element> >::_M_insert_overflow(Rva004F8D92Element *,Rva004F8D92Element const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ?push_back@?$vector@URva004F8D92Element@@V?$allocator@URva004F8D92Element@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004F8D92Element;
namespace _STL { template <> void vector<Rva004F8D92Element,allocator<Rva004F8D92Element> >::push_back(Rva004F8D92Element const &); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAURva004F8D92Element@@U1@V?$allocator@URva004F8D92Element@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004F8D92Element;
namespace _STL { template <> Rva004F8D92Element * _STLP_alloc_proxy<Rva004F8D92Element *,Rva004F8D92Element,allocator<Rva004F8D92Element> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@URva004F8D92Element@@@_STL@@QBEXPAURva004F8D92Element@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004F8D92Element;
namespace _STL { template <> void allocator<Rva004F8D92Element>::deallocate(Rva004F8D92Element *,unsigned int) const; }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva004F8D92Element@@@_STL@@YAXPAURva004F8D92Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva004F8D92Element;
namespace _STL { template <> void _Destroy<Rva004F8D92Element *>(Rva004F8D92Element *,Rva004F8D92Element *); }
// Suppress this TU's non-retail copy: the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<Rva004F8D92Element, allocator<Rva004F8D92Element> >::_M_clear(); }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
    if (m_ptr)
        ReleaseTreeHintRef00217D4C(m_ptr);
}



struct Rva004F8D92Element
{
    TargetRef00217D4C *m_ptr;
};

class Rva004F830BVector
{
    void *m_start;
    void *m_finish;
    void *m_end;
public:
    void reserve(unsigned int n);
};

class Rva004F92E3
{
    char m_pad[12];
    void *m_src0_start;
    void *m_src0_finish;
    void *m_src0_end;
    void *m_src1_start;
    void *m_src1_finish;
    void *m_src1_end;
public:
    void rva004F92E3(void *out);
};

void Rva004F92E3::rva004F92E3(void *out)
{
    typedef _STL::vector<TreeHintRef00217D4C> SrcVec;
    typedef _STL::vector<TreeHintRef00217D4C> DestEraseVec;
    typedef _STL::vector<Rva004F8D92Element> DestPushVec;

    DestEraseVec *dest = (DestEraseVec *)out;
    SrcVec *src = (SrcVec *)((char *)this + 12);

    int n = 2;
    do {
        // Codegen: same-valued PHI on the destination pointer closes the native register roles.
        DestEraseVec &destErase = *(dest?dest:dest);
        SrcVec &srcVec = *src;
        DestPushVec &destPush = *(DestPushVec *)dest;

        destErase.erase(destErase.begin(), destErase.end());
        ((Rva004F830BVector &)destErase).reserve(srcVec.size());

        TreeHintRef00217D4C *end = srcVec.end();
        for (TreeHintRef00217D4C *p = srcVec.begin(); p != end; ++p) {
            TreeHintRef00217D4C tmp = *p;
            destPush.push_back((Rva004F8D92Element &)tmp);
        }

        ++dest;
        ++src;
    } while (--n != 0);
}

// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?GetEntries@ArmySummary@@QAEXAAV?$vector@URva0040DC56Element@@V?$allocator@URva0040DC56Element@@@_STL@@@_STL@@@Z @0x0040E88B 70B
// Copies 8-byte source range [+0x40,+0x44) second fields into dest vector:
// dest.erase(begin,end), dest.reserve(count), push_back each [esi+4].
// Evidence: unlock lane; callees rowed erase 0x0040DC56 reserve 0x0040DC89 push_back 0x003F7B22; callers at 0x002BBF61 0x004FA26F.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ?reserve@?$vector@URva0040DC56Element@@V?$allocator@URva0040DC56Element@@@_STL@@@_STL@@QAE:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0040DC56Element;
namespace _STL { template <> void vector<Rva0040DC56Element,allocator<Rva0040DC56Element> >::reserve(unsigned int); }
// Suppress this TU's non-retail copy of ?erase@?$vector@URva0040DC56Element@@V?$allocator@URva0040DC56Element@@@_STL@@@_STL@@QAEPA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0040DC56Element;
namespace _STL { template <> Rva0040DC56Element * vector<Rva0040DC56Element,allocator<Rva0040DC56Element> >::erase(Rva0040DC56Element *,Rva0040DC56Element *); }
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@URva0040DC56Element@@V?$allocator@URva0040DC56Element@@@_STL@@@_STL@@IA:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0040DC56Element;
namespace _STL { template <> void vector<Rva0040DC56Element,allocator<Rva0040DC56Element> >::_M_clear(); }
// Suppress this TU's non-retail copy of ??$_Destroy@PAURva0040DC56Element@@@_STL@@YAXPAURva0040DC56Element@@0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva0040DC56Element;
namespace _STL { template <> void _Destroy<Rva0040DC56Element *>(Rva0040DC56Element *,Rva0040DC56Element *); }
// Suppress this TU's non-retail copy of ??$__uninitialized_fill_n@PAURva003F7B22Element@@IU1@@_STL@@YAPAURva003F7B22Element@@PAU1@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003F7B22Element;
namespace _STL { template <> Rva003F7B22Element * __uninitialized_fill_n<Rva003F7B22Element *,unsigned int,Rva003F7B22Element>(Rva003F7B22Element *,unsigned int,Rva003F7B22Element const &,__false_type const &); }
// Suppress this TU's non-retail copy of ??$__uninitialized_copy@PAURva003F7B22Element@@PAU1@@_STL@@YAPAURva003F7B22Element@@PAU1@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003F7B22Element;
namespace _STL { template <> Rva003F7B22Element * __uninitialized_copy<Rva003F7B22Element *,Rva003F7B22Element *>(Rva003F7B22Element *,Rva003F7B22Element *,Rva003F7B22Element *,__false_type const &); }
// Suppress this TU's non-retail copy of ?push_back@?$vector@URva003F7B22Element@@V?$allocator@URva003F7B22Element@@@_STL@@@_STL@@Q:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003F7B22Element;
namespace _STL { template <> void vector<Rva003F7B22Element,allocator<Rva003F7B22Element> >::push_back(Rva003F7B22Element const &); }
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@URva003F7B22Element@@V?$allocator@URva003F7B22Element@@@_STL@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva003F7B22Element;
namespace _STL { template <> void vector<Rva003F7B22Element,allocator<Rva003F7B22Element> >::_M_insert_overflow(Rva003F7B22Element *,Rva003F7B22Element const &,__false_type const &,unsigned int,bool); }

// Erase and reserve bind their existing STLport family providers.
namespace _STL {
template <> Rva0040DC56Element *vector<Rva0040DC56Element, allocator<Rva0040DC56Element> >::erase(Rva0040DC56Element *, Rva0040DC56Element *);
template <> void vector<Rva0040DC56Element, allocator<Rva0040DC56Element> >::reserve(unsigned int);
}

// Holder copies retain the reference at +0xB0; assignment uses its native owner.
#include "../../Apt/AptRefTarget.h"
#include "../../../../GameEngine/Include/Common/Rva002B2F97Target.h"
class Rva002B2F97
{
public:
    Rva002B2F97 &operator=(const Rva002B2F97 &other);
private:
    Rva002B2F97Target *m_ptr;
};

struct Rva0040DC56Element
{
    Rva002B2F97Target *m_ptr;
    Rva0040DC56Element(const Rva0040DC56Element &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr)
            ++m_ptr->m_ac.references;
    }
    __declspec(dllimport) __forceinline Rva0040DC56Element &operator=(const Rva0040DC56Element &other)
    {
        *reinterpret_cast<Rva002B2F97 *>(this) = *reinterpret_cast<const Rva002B2F97 *>(&other);
        return *this;
    }
};

// Keep the copy worker and placement construction available to their callers.
template Rva0040DC56Element *_STL::__copy<Rva0040DC56Element *, Rva0040DC56Element *, int>(Rva0040DC56Element *, Rva0040DC56Element *, Rva0040DC56Element *, const _STL::random_access_iterator_tag &, int *);
template void _STL::_Construct<Rva0040DC56Element, Rva0040DC56Element>(Rva0040DC56Element *, const Rva0040DC56Element &);

struct Rva003F7B22Element
{
	int a[1];
};

struct Rva0040E88BSrc
{
	int m_first;
	Rva003F7B22Element m_second;
};

#include "../../../../GameEngine/Include/GameLogic/ArmySummary.h"

void ArmySummary::GetEntries(_STL::vector<Rva0040DC56Element> &dst)
{
	dst.erase(dst.begin(), dst.end());
	dst.reserve(unsigned int(field44 - field40));
	_STL::vector<Rva003F7B22Element> &dst2 = (_STL::vector<Rva003F7B22Element> &)dst;
	Rva0040E88BSrc *first = field40;
	Rva0040E88BSrc *last = field44;
	for (Rva0040E88BSrc *p = first; p != last; ++p)
		dst2.push_back(p->m_second);
}

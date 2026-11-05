// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /DBFME_ASCII_DTOR_DECL /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfmealloc
// platformsdk
// stlport

// Native224D80..224DFF127B returns the local lazy owning holder's pointer.
// WB B8FC20 has the same static guard, allocation, constructor and slot08 call;
// named AptPlayer constructor B8F880 calls it at AptPlayer.cpp251. The callee
// constructor names AptButtonTooltipMap. Its original accessor spelling is unknown.
// Native allocation proves32B; the constructor declaration is an opaque ABI view.
// A real local static generates retail guard, atexit cleanup and EH state; no
// hand-coded guard global or callback pin is needed. All providers are owned.
class Object { public: virtual void *destroy(int); virtual void slot04(); virtual void slot08(); };
#include "../../../Include/Common/Rva00575674.h"
#include "../../../Include/Common/Rva000AD6F4.h"
class Rva00224CDC {public: Rva00224CDC(); char data[0x20];};
class AptTooltipHolder {
public:
 Object *ptr;
 // ?AptTooltipHolder::AptTooltipHolder present-unmatched
 AptTooltipHolder():ptr(0){}
 // ?AptTooltipHolder::~AptTooltipHolder present-unmatched
 ~AptTooltipHolder(){ ((Rva000AD6F4*)this)->clear(); }
};
Rva00224CDC *rva00224D80() {
 static AptTooltipHolder holder;
 if(!holder.ptr) {
  ((Rva00575674*)&holder)->rva00575674((Object*)new Rva00224CDC);
  holder.ptr->slot08();
 }
 return (Rva00224CDC*)holder.ptr;
}

// ??0AptPlayer@@QAE@XZ retail 0x00224E10 (320B). WB B8F880 names the
// AptPlayer constructor (AptPlayer.cpp:251); vtable 0x00BE6E80 is the one the
// rowed destructor 0x00224A90 reinstalls. Target facts: base
// SubsystemInterface 0x001B4E63; ten twenty-byte tables at +0x0C..+0xB8 built
// through hash_map ctor 0x00224C76 except the twelve-byte tree at +0x84
// (0x000D3A71); fourteen 0x28-byte level slots at +0xCC (element ctor 0x00224C95,
// dtor 0x00224252); the empty vector header at +0x2FC (0x00211E58); then the
// start time and the flag/word block to +0x329. The first player becomes the
// global at 0x009FE4CC and builds the tooltip map. Member element types are
// the existing rows' spellings; their original types are unproven.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include <set>
#include <vector>

// map/set<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); a declaration-only specialization
// stops this TU emitting its copy so callers bind the kept copy.
// Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const;
}

// vector<int> destruction otherwise instantiates the proxy<int>
// deallocate COMDAT (one byte shape per TU flags); a declaration-only
// member specialization suppresses this TU's copy so callers bind the
// kept copy. Plain (non-dllimport) form: no __imp_ reference is emitted.
namespace _STL {
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}
typedef bool Bool;
#include "subsystem_interface.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
}
#include <windows.h>
struct Rva00224C76Element {Rva00224C76Element();Rva00224C76Element(const Rva00224C76Element&);Rva00224C76Element&operator=(const Rva00224C76Element&);~Rva00224C76Element(){}char bytes[8]; bool operator==(const Rva00224C76Element&)const;};
typedef _STL::hash_map<int, Rva00224C76Element> AptPlayerTable;
// Retail destroys these through the row at 0x00224252 (call in AptPlayer's constructor at +0xA4); it takes this object in ecx.
extern "C" { void __identifier("??1DetailedArchivedDirectoryInfo@@QAE@XZ")(); }
class Rva00224C95 { public: Rva00224C95(); __declspec(noinline) ~Rva00224C95() { __identifier("??1DetailedArchivedDirectoryInfo@@QAE@XZ")(); } private: char m_bytes[0x28]; };
class AptPlayer : public SubsystemInterface
{
public:
 AptPlayer();
 virtual ~AptPlayer();
 virtual void init() = 0;
 virtual void reset() = 0;
 virtual void update() = 0;
private:
 AptPlayerTable m_0C, m_20, m_34, m_48, m_5C, m_70;
 _STL::set<AsciiString> m_84;
 AptPlayerTable m_90, m_A4, m_B8;
 Rva00224C95 m_levels[14];
 _STL::vector<int> m_2FC;
 int m_308;
 unsigned long m_startTime;
 bool m_310, m_311, m_312;
 int m_314, m_318, m_31C, m_320;
 int m_324;
 bool m_328, m_329;
};
// One native manager datum at VA DFE4CC; cast to this unit's receiver view.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
AptPlayer::AptPlayer() : m_startTime(timeGetTime()), m_310(false), m_311(false), m_312(false),
 m_314(0), m_318(0), m_31C(0), m_320(0), m_324(-1), m_328(false), m_329(false)
{
 if (reinterpret_cast<AptPlayer *>(g_bfmeAptWindowManager) == 0) {
  g_bfmeAptWindowManager = reinterpret_cast<BfmeAptWindowManager *>(this);
  rva00224D80();
 }
}

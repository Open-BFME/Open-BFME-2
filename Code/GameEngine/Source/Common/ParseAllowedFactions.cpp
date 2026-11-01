// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// parseAllowedFactions, retail 0x00534FFB (140 bytes). Built from the banked
// attempt reverse/attempts/0x00534ffb.cpp, which was already byte-exact; its
// set<AsciiString> swap callee is the ICF-folded tree swap at 0x0032AC92,
// now pinned as an alias. Uses the shared ascii_string.h so the emitted
// ??_GAsciiString copy calls releaseBuffer like the kept WOLBuddyOverlay copy;
// drops /Oy- (EH keeps the body framed, and /Oy- forced a framed ??_G).
// stlport
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include "ascii_string.h"

// Declaration-only: the rowed set<AsciiString> tree members are bound,
// this TU emits no per-flag copy of them or of their allocator leaves.
namespace _STL {
typedef _Rb_tree<AsciiString, AsciiString, _Identity<AsciiString>, less<AsciiString>, allocator<AsciiString> > Lk6AsciiSetTree;
template <> Lk6AsciiSetTree::~_Rb_tree();
template <> set<AsciiString, less<AsciiString>, allocator<AsciiString> >::set();
template <> pair<Lk6AsciiSetTree::iterator, bool> Lk6AsciiSetTree::insert_unique(const AsciiString&);
template <> Lk6AsciiSetTree::iterator Lk6AsciiSetTree::insert_unique(Lk6AsciiSetTree::iterator, const AsciiString&);
template <> _Rb_tree_node<AsciiString> *Lk6AsciiSetTree::_M_create_node(const AsciiString&);
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
bool operator<(const AsciiString &, const AsciiString &);
#include "../../Include/Common/INI/INI.h"
struct SideFlags { unsigned char human,computer,ai; int team; _STL::set<AsciiString> factions; };
void parseAllowedFactions(INI *ini, void *instance, void *, const void *)
{
    _STL::vector<AsciiString> names;
    INI::parseAsciiStringVector(ini,0,&names,0);
    _STL::set<AsciiString> factions;
    _STL::copy(names.begin(),names.end(),_STL::inserter(factions,factions.begin()));
    ((SideFlags *)instance)->factions.swap(factions);
}

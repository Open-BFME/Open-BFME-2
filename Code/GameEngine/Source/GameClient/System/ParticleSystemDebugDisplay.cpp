// partial score=0.98 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// BF1 readonly9cbfb551 ParticleSystemDebugDisplay semantic donor.
// Native001FA04B..001FA4401013B has identical statistics literals and
// list/template-tree purpose, with target slots and layout witnessed below.
// This unit retains only independently verified STL helper instantiations.
// The1013B caller is banked at reverse/attempts/0x001fa04b.cpp.
#define _STLP_BFME_RB_MINMAX_IMPORT  // inline _Rb_tree_node_base::_S_minimum/_S_maximum without a COMDAT copy (vendor/stlport/stl/_tree.h)
#include "ascii_string.h"
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _STLP_USE_STATIC_LIB
#include <map>

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}
bool operator<(const AsciiString &,const AsciiString &);
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString &a,const AsciiString &b) const { return a<b; } }; }

class DebugDisplayInterface;
struct _iobuf;
class ParticleSystemManager;
class GlobalData;
extern ParticleSystemManager *TheParticleSystemManager;
extern GlobalData *TheWritableGlobalData;

// Address-derived views: only slots/offsets used by this retail body are asserted.
namespace FXParticleSystem { class ParticleSystemTemplate { public: AsciiString getName() const; }; }
struct Rva001FA04BParticleModule {
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();
 virtual void slot4();virtual void slot5();virtual void slot6();virtual int getCount();
};
#include "../../../Include/GameClient/ParticleSystemClass.h"
ParticleSystem *Make001FCBD7();
#include "../../../Include/Common/RvaSmartPtr12.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/Rva0004CCFF.h"
// Native list clear1F65AF destroys the12B value through4CCFF(flags0).
// Keep this observed cleanup ABI without claiming a virtual pointer layout.
namespace _STL {static __forceinline void _Destroy(RvaSmartPtr12 *p){((Rva0004CCFF *)p)->destroyDelete(0);}}
#include <list>
template<> _STL::list<RvaSmartPtr12>::list(const _STL::list<RvaSmartPtr12>&);
typedef _STL::list<RvaSmartPtr12> ParticleDebugList;

// Native1013B statistics caller proves these typed int/float map and
// handle-list instantiations. Their full bodies and every call target are
// byte-and-relocation twins of the existing owners; zero unique-byte gain.
// The calling diagnostic body remains banked while its print register differs.
// This TU's class instantiation below would otherwise emit a second
// map<AsciiString,float>::operator[] COMDAT differing from the rowed
// 0x5B67C provider in AsciiStringTableSubscripts.cpp; a declaration-only
// member specialization keeps this TU's copy out so callers bind retail's.
namespace _STL {
template <> float &map<AsciiString, float, less<AsciiString>, allocator<pair<const AsciiString, float> > >::operator[](const AsciiString &);
}
template class _STL::map<AsciiString,int>;
template class _STL::map<AsciiString,float>;
template class _STL::_List_base<RvaSmartPtr12,_STL::allocator<RvaSmartPtr12> >;
template class _STL::pair<AsciiString,int>;
template class _STL::pair<AsciiString,float>;
template class _STL::pair<const AsciiString,int>;
template class _STL::pair<const AsciiString,float>;
template _STL::pair<AsciiString,int> _STL::make_pair(const AsciiString&,const int&);
template _STL::pair<AsciiString,float> _STL::make_pair(const AsciiString&,const float&);
template _STL::pair<const AsciiString,int>::pair(const _STL::pair<AsciiString,int>&);
template _STL::pair<const AsciiString,float>::pair(const _STL::pair<AsciiString,float>&);

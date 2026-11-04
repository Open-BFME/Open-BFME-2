// ?HostValidateColors@AptMpGameSetup@@QAEXXZ
// ?HostValidateColors@AptMpGameSetup@@QAEXXZ
// ?HostValidateColors@AptMpGameSetup@@QAEXXZ
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /arch:SSE /Op
// stlport
// Near-exact 0x004422DD..0x004424E7 (522B), WB HostValidateColors lead.
// Native facts: host gate at owner vslot +4, GameInfo pointer via +5C;
// GameSlot color +C/state +4, offered vector<bool> +3C4, optional colors +3DC.
// The local map uses native ctor 33C432 (25B) / unsigned find 357180 (56B),
// subscript 2077D6 (69B), and clear/free dtor 43FE62 (56B). The Rva-named
// destructor owner is retained; no application class inheritance is inferred.
// The int/void map supplies only its proven 12-byte physical storage and ctor;
// unsigned-key and GameSlot pointer access use the existing native facades.
// BFME1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f MpGameSetup and
// SkirmishScreenState reference units provided semantic leads; native WB and
// retail accesses, calls and control flow establish the target deltas above.
// Corrected Oct13 attempt: assignment and SetColor execute before exiting the
// available-color search, as retail 0x0044249E..0x004424BC proves. The previous
// bank had an unreachable assignment after break and its 0.96 score was stale.
// This unsigned search emits507B with native0x28 frame; receiver/slot registers,
// saved-pointer/key homes and success-block placement still differ from522B.
// No matched source, global owner, pin or compiler escape hatch was changed.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <map>
#include <vector>
#include <new>

// Preserve the existing inline allocator/compare operations without competing
// external providers, as in the shared Image-map insertion unit.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<unsigned>::operator()(const unsigned &a, const unsigned &b) const { return a < b; }
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t n)
{ void *r = malloc(n); if (!r) r = _S_oom_malloc(n); return r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *p, size_t) { free((char *)p); }
typedef _Rb_tree<int, pair<const int, void *>, _Select1st<pair<const int, void *> >,
    less<int>, allocator<pair<const int, void *> > > HostReservedTree;
template <> HostReservedTree::~_Rb_tree();
}

#include "../../../Include/GameNetwork/GameInfo.h"
class Rva0043DA65 {public: int rva0043DA65(); char data[12];};
class ColorSetupOwner {public: virtual void slot0(); virtual bool amIHost();
 virtual void slot2(); virtual void slot3(); virtual void SetColor(GameSlot*,int);};
namespace _STL {template<> map<int,void*>::map();}
class Rva0043EA9C {public:
 _STL::map<int,void*> storage;
 ~Rva0043EA9C();
};
class Image;
typedef _STL::map<unsigned, void *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, void *> > > RespawnPtrMap;
typedef _STL::map<unsigned, Image *, _STL::less<unsigned>, _STL::allocator<_STL::pair<const unsigned, Image *> > > ImageNameMap;
namespace _STL {
typedef _Rb_tree<unsigned, pair<const unsigned, Image *>, _Select1st<pair<const unsigned, Image *> >,
    less<unsigned>, allocator<pair<const unsigned, Image *> > > HostImageTree;
template <> _Rb_tree_node<pair<const unsigned, Image *> > *HostImageTree::_M_create_node(const HostImageTree::value_type &);
}
#include "../../../Include/GameClient/ImageSubscriptMap.h"
// The canonical class owns the twelve-byte map storage. Keep this TU's
// established STL operations as a view of that storage.
inline __declspec(noinline) Image *&ImageSubscriptMap::operator[](const unsigned &key)
{
	ImageNameMap &map = *(ImageNameMap *)this;
	ImageNameMap::iterator i = map.lower_bound(key);
	if (i == map.end() || map.key_comp()(key, (*i).first))
		i = map.insert(i, ImageNameMap::value_type(key, (Image *)0));
	return (*i).second;
}
#include "../../../Include/GameClient/AptMpGameSetup.h"
// The canonical panel leaves +0x3C4 opaque; retail constructs a bit vector
// there. Access that storage through this TU's established STL view.
void AptMpGameSetup::HostValidateColors() {
 if(!((ColorSetupOwner *)field58)->amIHost()) return;
 GameInfo *info=(GameInfo*)field5c->rva0043DA65();
 if((info == 0)) return;
 unsigned i;
 Rva0043EA9C reserved;
 unsigned char repair=false;
 for(i=0;i<8;i++) {
  GameSlot *slot=info->getSlot(i);
  if(!slot) continue;
  int color=slot->m_color;
  if(color<0) {
   if(!field3dc && !slot->isObserver() && slot->m_state != 1) repair=true;
   continue;
  }
  ImageSubscriptMap *map=(ImageSubscriptMap*)&reserved;
  const RespawnPtrMap *lookup=(RespawnPtrMap*)&reserved;
  if(lookup->find((unsigned)color)!=lookup->end()) {
   repair=true;
   if(((GameSlot*)((*map)[(unsigned)color]))->isHuman()) continue;
  }
  (*map)[(unsigned)color]=(Image*)slot;
 }
 if(repair) {
  for(i=0;8 > i;++i) {
   GameSlot *slot=info->getSlot(i);
   if((0 == slot)) continue;
   ImageSubscriptMap *map=(ImageSubscriptMap*)&reserved;
   int color=(i ? slot->m_color : slot->m_color);
   if(color<0 && (field3dc || slot->isObserver() || slot->m_state==1)) continue;
    if((GameSlot*)(*map)[(unsigned)color]==slot) continue;
   if(field3dc) ((ColorSetupOwner *)field58)->SetColor(slot,-1);
   else {
    int c;
    for(c=0;(unsigned)c<((_STL::vector<bool> *)field3c4)->size();++c) {
        _ReadWriteBarrier();
     RespawnPtrMap *lookup=(RespawnPtrMap*)&reserved;
     if((*(_STL::vector<bool> *)field3c4)[c] && lookup->find((unsigned)c)==lookup->end()) goto colorFound;
    }
    goto colorDone;
colorFound:
    (*map)[c]=(Image*)slot;
    ((ColorSetupOwner *)field58)->SetColor(slot,c);
colorDone:;
   }
  }
 }
}

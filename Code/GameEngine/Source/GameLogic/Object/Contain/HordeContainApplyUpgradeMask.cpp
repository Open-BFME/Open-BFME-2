// cl: /O1 /G7 /arch:SSE /DNDEBUG /Ireference/shims/bfmealloc /MD /EHs /EHc- /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva00472444@Rva00472444@@UAEXABURva00472444Mask@@PBVAsciiString@@@Z,
// retail 0x00472444..0x004725D5 (401 B, RET 8), on the horde contain's +0x20
// interface: collects the upgrade templates of every set bit of a 1024-bit
// mask, then applies each one an object still lacks to every contained
// object and every live +0x170 member, optionally limited to objects whose
// record matches name (0x004723F2). The pair helper 0x0046247D is visible
// here (byte-identical noinline copy) as in HordeContainIface11CSlots.cpp;
// the temporary vector's erase is the folded pointer erase at 0x0031BD55.
#include <vector>
#include <list>
#include <set>
class AsciiString;
class UpgradeTemplate;
class Object {public:bool affectedByUpgrade(const UpgradeTemplate *) const;void rva00293077(const void *);};
#include "../../../Common/GameLogicObjectLookupView.h"
namespace _STL {
// Keep the inlined node comparisons local instead of emitting competing
// out-of-line base-iterator definitions with this unit's /G7 settings.
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b) {
    return a._M_node != b._M_node;
}
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b) {
    return a._M_node != b._M_node;
}
// Retail's vector growth (_M_insert_overflow, 0x002DFCF6) expands max<unsigned
// int>; dllimport + __forceinline expands it here too and emits no copy.
template <> __declspec(dllimport) __forceinline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b) { return a < b ? b : a; }
}
extern GameLogic *TheGameLogic;
class UpgradeCenter {public:const UpgradeTemplate *rva0026EEA0(int)const;};
extern UpgradeCenter *TheUpgradeCenter;
struct Rva0046247DPair {void *first;const _STL::list<Object *> *second;};
class Rva0046247D {public:__declspec(noinline) void rva0046247D(Rva0046247DPair &p){void *base=this;char *field=(char *)base+0x20;p.first=base?field:0;p.second=(const _STL::list<Object *> *)((char *)base+0x54);}};
class HordeContain {public:bool rva004723F2(Object *,const AsciiString &);};
struct Rva00472444Mask {unsigned int words[32];__forceinline bool test(unsigned int bit)const{return (words[bit>>5] & (1U<<(bit&31)))!=0;}};
class Rva00472444 {public:
// virtual: also reached through the this-0xFC thunk 0x00474142.
virtual void rva00472444(const Rva00472444Mask &,const AsciiString *);
private:char unknown[0x150 - 4];_STL::set<int> m_ids;
};
void Rva00472444::rva00472444(const Rva00472444Mask &mask,const AsciiString *name){
 Rva0046247DPair pair;
 ((Rva0046247D *)((char *)this-0x20))->rva0046247D(pair);
 _STL::list<Object *> &members=*const_cast<_STL::list<Object *> *>(pair.second);
 _STL::list<Object *>::iterator it=members.begin();
 _STL::vector<const UpgradeTemplate *> upgrades;
 for(int i=0;i<1024;++i)if(mask.test(i)){const UpgradeTemplate *upgrade=TheUpgradeCenter->rva0026EEA0(i);upgrades.push_back(upgrade);}
 while(it!=members.end()){
  Object *obj=*it;
  if(name && !((HordeContain *)((char *)this-0x20))->rva004723F2(obj,*name)){++it;continue;}
  for(unsigned i=0;i<upgrades.size();++i){const UpgradeTemplate *upgrade=upgrades[i];if(obj->affectedByUpgrade(upgrade))obj->rva00293077(upgrade);}
  ++it;
 }
 for(_STL::set<int>::iterator entry=m_ids.begin();entry!=m_ids.end();++entry){
  Object *obj=TheGameLogic->findObjectByID((ObjectID)*entry);if(!obj)continue;
  if(name && !((HordeContain *)((char *)this-0x20))->rva004723F2(obj,*name))continue;
  for(unsigned i=0;i<upgrades.size();++i){const UpgradeTemplate *upgrade=upgrades[i];if(obj->affectedByUpgrade(upgrade))obj->rva00293077(upgrade);}
 }
 upgrades.clear();
}

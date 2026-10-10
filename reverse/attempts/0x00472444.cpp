// ?rva00472444@Rva00472444@@QAEXABURva00472444Mask@@PBVAsciiString@@@Z
// partial score=0.8553459119496856 date=2026-10-10
// BANKED: native472444..4725D5 complete401B RET8; WB10C03B0 is a
// full953B unnamed body polluted by inlined BitFlags.h metadata. It
// independently proves the1024-bit upgrade vector, contained-list and
// member-ID passes, optional record-name filter and native calls.
// BFME1 575ba2b0 Rva00236CA0HordeContain.cpp supplies the two-pass upgrade
// traversal guide; BFME2 replaces one upgrade with a mask and adds the
// filter, omitting donor color flashes. Existing HordeContain constructor
// and assignSpotToUnit prove the set at full170 and owner+20 receiver.
// This is an incomplete address-derived receiver view, with no claimed
// original member name, virtual slot or complete class layout.
// Exact82B filter4723F2 is sealed separately (packet A-horde-member-name-
// filter-82-8c51e0ab82); that mapped scratch call is not a new ledger pin.
// 34 compiler/control/container shapes remain394B O1 EHs versus native401.
// List iterator livesESI and indexEDI instead of native listESI/iteratorEDI
// and stack-homed mask index; rest of traversal closely follows retail.
// Const-upgrade vector ctor/erase remain unresolved and need whole-owner
// fold proof and normal admission, not assumed addresses or alias wrappers.
// No Code, ledger, header, baseline or pin mutation was made.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /Ireference/shims/bfmealloc /MD /EHs /EHc- /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>
#include <list>
#include <set>
class AsciiString;
class UpgradeTemplate;
class Object {public:bool rva002940B9(const UpgradeTemplate *);void rva00293077(const void *);};
enum ObjectID { INVALID_OBJECT_ID=0 };
class GameLogic {public:Object *findObjectByID(ObjectID);};
extern GameLogic *TheGameLogic;
class UpgradeCenter {public:const UpgradeTemplate *rva0026EEA0(int)const;};
extern UpgradeCenter *TheUpgradeCenter;
struct Rva0046247DPair {void *first;const _STL::list<Object *> *second;};
class Rva0046247D {public:void rva0046247D(Rva0046247DPair &);};
class HordeContain {public:bool rva004723F2(Object *,const AsciiString &);};
struct Rva00472444Mask {unsigned int words[32];__forceinline bool test(unsigned int bit)const{return (words[bit>>5] & (1U<<(bit&31)))!=0;}};
class Rva00472444 {public:void rva00472444(const Rva00472444Mask &,const AsciiString *);
private:char unknown[0x150];_STL::set<int> m_ids;
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
  for(unsigned i=0;i<upgrades.size();++i){const UpgradeTemplate *upgrade=upgrades[i];if(obj->rva002940B9(upgrade))obj->rva00293077(upgrade);}
  ++it;
 }
 for(_STL::set<int>::iterator entry=m_ids.begin();entry!=m_ids.end();++entry){
  Object *obj=TheGameLogic->findObjectByID((ObjectID)*entry);if(!obj)continue;
  if(name && !((HordeContain *)((char *)this-0x20))->rva004723F2(obj,*name))continue;
  for(unsigned i=0;i<upgrades.size();++i){const UpgradeTemplate *upgrade=upgrades[i];if(obj->rva002940B9(upgrade))obj->rva00293077(upgrade);}
 }
 upgrades.clear();
}

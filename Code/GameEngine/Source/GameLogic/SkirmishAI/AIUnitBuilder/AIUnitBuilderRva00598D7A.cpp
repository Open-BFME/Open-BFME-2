// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
// stlport
// Native598052..5980F3 is161B, RET0; WB152E690 has the same seven calls.
// The independently rowed AIUnitBuilder598D7A tail-calls this body with
// this unchanged, establishing the receiver. The original method name
// remains unknown. Retail proves owner30/playerId3AC and metadata78,
// state2C/id1C; their wider layouts and original identities are unresolved.
// Traverses the current battle's nested collection and forwards ids whose
// metadata word2C is3. Mode114 suppresses traversal when it is3.
// The canonical GameLogic view and existing named living-world singleton
// preserve their providers; no new globals, pins or aliases are introduced.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <list>
#include <map>
#include <vector>
#include "ascii_string.h"

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
struct Rva00598052Owner {char unknown00[0x3AC];int playerId;};
class Rva002E2903Player;
class Rva002BA8F1Logic {public: Rva002E2903Player *find(int,unsigned int *);};
class Rva003F468D;
class Rva0020E6B7RegionManager {public: Rva003F468D *rva0020E6B7();};
class LivingWorldLogic {public: char unknown00[0xB0]; Rva0020E6B7RegionManager *manager;};
extern LivingWorldLogic *TheLivingWorldLogic;
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class LivingWorldBattle {
public:
    int rva003F4752(void *);
    int rva003F4FAA(int,void *);
    int rva003F48FE(int,int,int);
};
class Rva003F4DCA {public: int rva003F4DCA(int,int);};
struct Rva00598052Metadata {char unknown00[0x1C];int id;char unknown20[12];int state;};
struct Rva00598052Entry {char unknown00[0x78]; Rva00598052Metadata *metadata;};

struct Rva00598961Config {char pad00[4]; _STL::vector<AsciiString *> unitNames; char pad10[0x1C-0x10];float field1C;};
struct Rva002A8AB1Record {char pad00[0x160];Rva00598961Config *config160;};
class Rva00598007 {public:Rva002A8AB1Record *rva00598007();bool rva0059802E();};
class Player;
class ThingTemplate {public:int rva0033A69A(const Player*,int,int)const;};
class ThingFactory {public:const ThingTemplate *findTemplate(const AsciiString &name);};
extern ThingFactory *TheThingFactory;
struct Rva00598961Template {char pad00[0x113];unsigned char field113;};
class Rva00506FE9Hit {public:void rva0055ADBA(void*);};
class Rva00598C3AItem
{
public:
	virtual ~Rva00598C3AItem();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6(int value, int flags);
	virtual void slot7(int);
	float field04;
	char pad08[4];
	AsciiString name0C;
	int state10;
};

enum NameKeyType { NAMEKEY_INVALID=0 };
class Rva005983EE;
class NameKeyGenerator {
public:
 NameKeyType nameToKey(const AsciiString&);
 class KeyToBucketMap {
  friend class ::Rva005983EE;
 public:
  struct Slot {void *node;KeyToBucketMap *table;};
  struct value_type {int first;void *second;};
  Slot *find(Slot &,const int *);
 private:
  int *insertNode(const value_type &);
 };
};
extern NameKeyGenerator *TheNameKeyGenerator;
class Rva005982EAInterface {
public:
#define UNUSED_SLOT(n) virtual void slot##n();
 UNUSED_SLOT(0) UNUSED_SLOT(1) UNUSED_SLOT(2) UNUSED_SLOT(3) UNUSED_SLOT(4) UNUSED_SLOT(5) UNUSED_SLOT(6) UNUSED_SLOT(7) UNUSED_SLOT(8) UNUSED_SLOT(9) UNUSED_SLOT(10) UNUSED_SLOT(11) UNUSED_SLOT(12) UNUSED_SLOT(13) UNUSED_SLOT(14) UNUSED_SLOT(15) UNUSED_SLOT(16)
 virtual int slot17();
 UNUSED_SLOT(18) UNUSED_SLOT(19) UNUSED_SLOT(20) UNUSED_SLOT(21) UNUSED_SLOT(22) UNUSED_SLOT(23) UNUSED_SLOT(24)
 virtual bool slot25();
#undef UNUSED_SLOT
};
class Object {
public:
 void *rva0028BC58(int);
 char pad00[0x74]; ObjectID id74; char pad78[0x438-0x78]; unsigned int status438;
};
// The native bounds use signed NameKey order directly. Explicit member
// specializations preserve the STLport search algorithm and avoid emitting
// unrelated comparator bodies with incompatible shared definitions.
typedef _STL::pair<const NameKeyType,ObjectID> AIObjectKeyValue;
typedef _STL::_Rb_tree_node<AIObjectKeyValue> AIObjectKeyNode;
typedef _STL::_Rb_tree<NameKeyType,AIObjectKeyValue,_STL::_Select1st<AIObjectKeyValue>,_STL::less<NameKeyType>,_STL::allocator<AIObjectKeyValue> > AIObjectKeyTree;
namespace _STL {
template<> AIObjectKeyNode *AIObjectKeyTree::_M_lower_bound(const NameKeyType &key) const {
 AIObjectKeyNode *y=this->_M_header._M_data;
 AIObjectKeyNode *x=_M_root();
 while(x) {
  if(!(x->_M_value_field.first<key)) {y=x; x=_S_left(x);} else x=_S_right(x);
 }
 return y;
}
template<> AIObjectKeyNode *AIObjectKeyTree::_M_upper_bound(const NameKeyType &key) const {
 AIObjectKeyNode *y=this->_M_header._M_data;
 AIObjectKeyNode *x=_M_root();
 while(x) {
  if(key<x->_M_value_field.first) {y=x; x=_S_left(x);} else x=_S_right(x);
 }
 return y;
}
}
class AIUnitBuilder
{
public:
	void rebuildArmyPercentages();
	void manageConstructingList();
	void build();
	void Rva00598052();
	void Rva00598D7A();
	Object *Rva005982EA(const AsciiString*,_STL::vector<ObjectID>*,bool);
	Rva00598C3AItem *createBestHeroToBuild();
	Rva00598C3AItem *createBestUnitToMake();
 int getHeroIndex();
 bool Rva00598738(const AsciiString *);
 void registerUnitFactory(ObjectID);
 AsciiString decideWhichTemplateToMake();

private:
	unsigned char m_pad00[8];
	_STL::multimap<NameKeyType,ObjectID> m_objects; // +8,12B includes comparator storage
	_STL::list<Rva00598C3AItem *> m_items; // +0x14
	unsigned char m_pad18[0x2C - 0x18];
	bool m_2C; // +0x2C, read and cleared by target bytes
	unsigned char m_pad2D[0x30 - 0x2D];
	Rva00598052Owner *m_30; // +0x30
	bool m_34; // +0x34
 char pad35[3]; int heroIndex; _STL::vector<int> removedHeroes; int cost48; _STL::vector<AsciiString> heroNames;
};

void AIUnitBuilder::Rva00598052()
{
    if (TheGameLogic->m_114 != 3) {
        int playerId=m_30->playerId;
        Rva002E2903Player *player=((Rva002BA8F1Logic *)TheLivingWorldLogic)->find(playerId,0);
        LivingWorldBattle *battle=(LivingWorldBattle *)TheLivingWorldLogic->manager->rva0020E6B7();
        int outer=battle->rva003F4752(player);
        int middle=battle->rva003F4FAA(outer,player);
        int count=((Rva003F4DCA *)battle)->rva003F4DCA(outer,middle);
        for (int i=0;i<count;++i) {
            Rva00598052Metadata *metadata=((Rva00598052Entry *)battle->rva003F48FE(outer,middle,i))->metadata;
            if(metadata->state==3)
                TheGameLogic->rva0023D08B(metadata->id);
        }
    }
}

// Native598D7A..598DA2: flag2C update, build, then tail to598052.
void AIUnitBuilder::Rva00598D7A()
{
	if (m_2C)
	{
		rebuildArmyPercentages();
		m_2C = false;
	}
	manageConstructingList();
	build();
	return Rva00598052();
}

// Native5982EA..5983DA is240B RET12; WB152E7A0 follows the same flow.
// AIUnitBuilder's observed +8 equal-key tree supplies ObjectID bit patterns
// to the canonical object lookup. NameKeyType/ObjectID STLport storage is a
// semantic view established by the two providers; original typedef is unknown. Full Object
// layout is not claimed: id74/status438 and module getter28BC58 are observed.
// Interface slots25/17 and the optional excluded-ID vector are target facts;
// their original names remain unresolved. Exclusion end is read before begin.
Object *AIUnitBuilder::Rva005982EA(const AsciiString *name, _STL::vector<ObjectID> *excluded, bool includeBusy)
{
 if (!m_objects.empty()) {
 NameKeyType key=TheNameKeyGenerator->nameToKey(*name);
 for (_STL::multimap<NameKeyType,ObjectID>::iterator i=m_objects.lower_bound(key);i._M_node!=m_objects.upper_bound(key)._M_node;++i) {
  Object *obj=TheGameLogic->findObjectByID((ObjectID)i->second);
  if (!obj || (obj->status438&1)) continue;
  Rva005982EAInterface *iface=(Rva005982EAInterface*)obj->rva0028BC58(0);
  if (!iface) continue;
  if (!includeBusy && (iface->slot25() || iface->slot17())) continue;
  bool found=false;
  if (excluded) {
   _STL::vector<ObjectID>::iterator end=excluded->end();
   for (_STL::vector<ObjectID>::iterator e=excluded->begin();e!=end&&!found;++e) {
    if(obj->id74==*e)found=true;
   }
  }
  if (!found)return obj;
 }
 }
 return 0;
}

// WB152E310 names manageConstructingList at AIUnitBuilder.cpp:440.
// Native598961..598A3D is220B. Item float04/name0C/state10 and slots0/7
// are observed; slot0 follows scalar deleting-dtor ABI. Global ::delete
// preserves the native flags0 call and separate operator delete. Template
// byte113 bit04 clears builder34; its full type and flag meaning are open.
// The observed500 float sentinel and config160/word1C are preserved.
void AIUnitBuilder::manageConstructingList()
{
 for (_STL::list<Rva00598C3AItem*>::iterator i=m_items.begin();i._M_node!=m_items.end()._M_node;) {
  Rva00598C3AItem *item=*i;
  switch(item->state10) {
  case 0:
   if (!Rva005982EA(&item->name0C,0,true)) item->slot7(3);
   else if(item->field04==500.0f&&!((Rva00598007*)this)->rva0059802E())
    item->field04=((Rva00598007*)this)->rva00598007()->config160->field1C;
   ++i;
   break;
  case 1: ++i;break;
  case 2: case 3:
   Rva00598961Template *thing=(Rva00598961Template*)TheThingFactory->findTemplate(item->name0C);
   if(thing->field113&4)m_34=false;
   ((Rva00506FE9Hit*)item)->rva0055ADBA(m_30);
   ::delete item;
   i=m_items.erase(i);
   break;
  }
 }
}

// Existing factory result uses the neutral callback-prefix view Rva00598C3AItem.
// Provider constructor 0x005DAC38 and allocation44 establish this accessed layout.
class AIBuildableUnit : public Rva00598C3AItem {
public:
 AIBuildableUnit(int);
 char pad14[0x38-0x14]; int quantity; int productionId; int context;
};
struct BuildableUnitTemplateView {char pad[0x618];int quantity;int getQuantity()const{return quantity;}};
// WB 0x0152CFC0 names createBestUnitToMake and assert180.
// Native REL32 at598B8E returns the AsciiString from399B RET4 hidden-result
// decideWhichTemplateToMake 5987D2; WB152DCA0 asserts354..399 prove the name.
Rva00598C3AItem *AIUnitBuilder::createBestUnitToMake()
{
 AIBuildableUnit *unit=0;
 AsciiString name=decideWhichTemplateToMake();
 if (name != AsciiString::TheEmptyString) {
   unit=new AIBuildableUnit((int)m_30);
   unit->name0C=name;
   unit->quantity=((BuildableUnitTemplateView *)TheThingFactory->findTemplate(name))->quantity;
   unit->field04=((Rva00598007 *)this)->rva0059802E() ? 500.0f : ((Rva00598007 *)this)->rva00598007()->config160->field1C;
 }
 return unit;
}





class Player;
class Rva002A8F24 { public: void *rva002A8F24(Player *); };
extern Rva002A8F24 *g_00DFEEF8;
// Native51B at4DFBED returns the keyed count at node+8 or0; RET4.
// WB129B860 reads the same AsciiString reference; identity stays address-named.
struct HeroEconomyStatsView {char pad[0x14];unsigned int available;};
class Rva004DFBED {public:char pad[0x0c];HeroEconomyStatsView*economy;int rva004DFBED(const AsciiString&);};
class Rva00598192 { public: int rva00598192(const AsciiString &); };
int GetGameLogicRandomValue(int,int,char *,int);
// WB152D170 names getHeroIndex; assertions200..225 and native165B agree.
int AIUnitBuilder::getHeroIndex()
{
 Rva004DFBED *stats=(Rva004DFBED *)g_00DFEEF8->rva002A8F24((Player *)m_30);
 if (!removedHeroes.empty()) {
   _STL::vector<int>::iterator i=removedHeroes.begin(),end=removedHeroes.end();
   while (i!=end) {
     int index=*i;
     AsciiString *name=&heroNames[index];
     if (!stats->rva004DFBED(*name) && !((Rva00598192 *)this)->rva00598192(*name)) {
       ((_STL::vector<void *> *)&removedHeroes)->erase((void **)i);
       heroIndex=index;
       break;
     }
     ++i;
   }
 }
 if (heroIndex==-1) heroIndex=GetGameLogicRandomValue(0,heroNames.size()-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUnitBuilder\\AIUnitBuilder.cpp",225);
 return heroIndex;
}


class ThingTemplate;
class Rva0037EE4C { public: int rva0037EE4C(const ThingTemplate *,int,int); };
class Rva00A027B8 {
public:
#define SLOT(n) virtual void s##n();
 SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24)
#undef SLOT
 virtual bool slot25(Object *,const ThingTemplate *,int);
};
extern Rva00A027B8 *g_00A027B8;
// WB152CB70 explicitly names registerUnitFactory and assert127.
// The native call4FF876 uses the existing int/int tree provider for these
// 32-bit enum payloads; the home lower/upper bounds prove signed key ordering.
void AIUnitBuilder::registerUnitFactory(ObjectID id)
{
 Object *object=TheGameLogic->findObjectByID(id);
 if (!object) return;
 Rva00598961Config *config=((Rva00598007 *)this)->rva00598007()->config160;
 for (_STL::vector<AsciiString *>::iterator i=config->unitNames.begin();i!=config->unitNames.end();++i) {
   AsciiString name=**i;
   const ThingTemplate *thing=TheThingFactory->findTemplate(name);
   if (g_00A027B8->slot25(object,thing,-1)) {
     _STL::pair<int,int> item(TheNameKeyGenerator->nameToKey(name),id);
     ((_STL::multimap<int,int> *)&m_objects)->insert(item);
   }
 }
 for (_STL::vector<AsciiString>::iterator i=heroNames.begin();i!=heroNames.end();++i) {
   AsciiString name=*i;
   const ThingTemplate *thing=TheThingFactory->findTemplate(name);
   int count=((Rva0037EE4C *)((char *)m_30+0x738))->rva0037EE4C(thing,-1,0);
   if (g_00A027B8->slot25(object,thing,count)) {
     _STL::pair<int,int> item(TheNameKeyGenerator->nameToKey(name),id);
     ((_STL::multimap<int,int> *)&m_objects)->insert(item);
   }
 }
 m_2C=true;
}


// Retail598738..5987D2: EH prologue, RET4, followed by decideWhichTemplateToMake.
// Same receiver/list14 and lookup5982EA as matched manageConstructingList.
// Excludes objects already serving state0 requests, then tests the supplied
// name. ObjectID storage follows lookup's canonical ID; original name unknown.
bool AIUnitBuilder::Rva00598738(const AsciiString *name)
{
 _STL::vector<ObjectID> excluded;
 _STL::list<Rva00598C3AItem *>::iterator end=m_items.end();
 for (_STL::list<Rva00598C3AItem *>::iterator i=m_items.begin();i!=end;++i) {
  Rva00598C3AItem *item=*i;
  if (item->state10==0) {
   Object *object=Rva005982EA(&item->name0C,&excluded,false);
   if (object) { ObjectID id=object->id74; excluded.push_back(id); }
  }
 }
 return Rva005982EA(name,&excluded,false)!=0;
}

// Existing Armor-valued provider is a read-only key-lookup ABI view; no
// construction or mapped ArmorTemplate access occurs for the float table.
class ArmorTemplate;
namespace rts { template<class T> struct hash; template<class T>struct equal_to; }
namespace _STL {
template<class V> struct _Hashtable_node;
template<class V,class Traits,class K,class H,class X,class E,class A> struct _Ht_iterator {
 void *node;void *table;
 _Ht_iterator &operator++();
};
template<class T> struct hash;

struct ArmyFindNodePrefix {ArmyFindNodePrefix *next;unsigned int key;};
template<class V,class K,class H,class X,class E,class A> class hashtable {
 friend class ::AIUnitBuilder;
 template<class VV,class KK,class HH,class XX,class EE,class AA> friend class hashtable;
 friend class ::Rva004DFBED;
public:
 typedef _Ht_iterator<V,_Nonconst_traits<V>,K,H,X,E,A> iterator;
 template<class T> __declspec(noinline) iterator find(const T &);
 iterator begin();
private:
 unsigned int unknown00;
 vector<_Hashtable_node<V>*> buckets;
 unsigned int unknown10;
 template<class T> __declspec(noinline) _Hashtable_node<V> *_M_find(const T &key) const {
  unsigned int bucket=(unsigned int)key%buckets.size();
  ArmyFindNodePrefix *node=(ArmyFindNodePrefix*)buckets[bucket];
  for(;node;node=node->next) if(node->key==(unsigned int)key) break;
  return (_Hashtable_node<V>*)node;
 }
};
}
typedef _STL::pair<const NameKeyType,ArmorTemplate> ArmyLookupProviderValue;
typedef _STL::hashtable<ArmyLookupProviderValue,NameKeyType,rts::hash<NameKeyType>,_STL::_Select1st<ArmyLookupProviderValue>,rts::equal_to<NameKeyType>,_STL::allocator<ArmyLookupProviderValue> > ArmyLookupProvider;
namespace _STL {
template<class V,class K,class H,class X,class E,class A> template<class T>
typename hashtable<V,K,H,X,E,A>::iterator hashtable<V,K,H,X,E,A>::find(const T &key) {
 iterator result={((const ArmyLookupProvider*)this)->_M_find(*(const NameKeyType*)&key),this};
 return result;
}
}
struct ArmyPercentageNodeView {void *next;NameKeyType key;float percentage;};
class Rva00598016 {public:void *rva00598016();};
class Rva002A7461 {public:int rva002A7461();int rva002A7548(int);};
struct BuildableTemplateQuantityView {char pad[0x618];int quantity;};
// Retail calls the canonical empty vector-header provider (BfmeE16 at211E58)
// and the existing ModuleData pointer-vector push provider (4DFCB0).
// The empty POD vector owns only the12-byte header; selected AsciiString
// pointers use the independently verified4-byte pointer-storage view.
// No BfmeE16 or ModuleData element identity is attributed to these names.
struct BfmeE16 {float x,y,z,w;};
class ModuleData;

// Identity: WB152DCA0 and native filename/assert399; names from config160,
// quantities from template618, player capacity at60, pending build list14.
// Native hash lookup reads node key4 and percentage8; unrelated fields opaque.
AsciiString AIUnitBuilder::decideWhichTemplateToMake()
{
 _STL::vector<BfmeE16> storage;
 _STL::vector<const ModuleData*> &candidates=*(_STL::vector<const ModuleData*>*)&storage;
 Rva00598961Config *config=((Rva00598007*)this)->rva00598007()->config160;
 for (_STL::vector<AsciiString*>::iterator i=config->unitNames.begin();i!=config->unitNames.end();++i) {
  AsciiString *name=*i;
  if (!Rva00598738(name)) continue;
  BuildableTemplateQuantityView *thing=(BuildableTemplateQuantityView*)TheThingFactory->findTemplate(*name);
  int count=((Rva004DFBED*)((Rva00598016*)this)->rva00598016())->rva004DFBED(*name);
  for (_STL::list<Rva00598C3AItem*>::iterator j=m_items.begin();j!=m_items.end();++j)
   if (((StringBase<char>*)&(*j)->name0C)->compare(*(StringBase<char>*)name)==0) ++count;
  float percentage=(float)(thing->quantity*count)/(float)((Rva002A7461*)((char*)m_30+0x60))->rva002A7461()*100.0f;
  NameKeyType key=TheNameKeyGenerator->nameToKey(*name);
  const ArmyLookupProvider &lookup=*(const ArmyLookupProvider*)m_pad18;
  ArmyPercentageNodeView *node=(ArmyPercentageNodeView*)lookup._M_find(key);
  if (node->percentage-percentage>0.0f)
   candidates.push_back((const ModuleData *const &)name);
 }
 if(!candidates.empty()) {
 int index=GetGameLogicRandomValue(0,candidates.size()-1,"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIUnitBuilder\\AIUnitBuilder.cpp",399);
 return *(AsciiString*)candidates[index];
 }
 return AsciiString::TheEmptyString;
}

// Target4DFBED..4DFC20: keyed count table at receiver14; node value8 or0.
// WB129B860 establishes string argument; wider receiver identity stays unknown.
int Rva004DFBED::rva004DFBED(const AsciiString &name)
{
 NameKeyType key=TheNameKeyGenerator->nameToKey(name);
 const ArmyLookupProvider &table=*(const ArmyLookupProvider*)((char*)this+0x14);
 ArmyPercentageNodeView *node=(ArmyPercentageNodeView*)table._M_find(key);
 return node?*(int*)((char*)node+8):0;
}

// Existing canonical integer-key find provider reads only node/table pointers.
// Its payload stays incomplete; no payload identity is inferred for this table.
struct Rva00148B27Element;
typedef _STL::pair<const int,Rva00148B27Element> IntegerLookupProviderValue;
typedef _STL::hashtable<IntegerLookupProviderValue,int,_STL::hash<int>,_STL::_Select1st<IntegerLookupProviderValue>,_STL::equal_to<int>,_STL::allocator<IntegerLookupProviderValue> > IntegerLookupProvider;
class Rva005983EE {public:float &lookup(const NameKeyType &);};
// Native5983EE..598431: hash-map subscript over key4/percentage8, RET4.
// Existing find148B27 returns node/table; blind insertion53F3B1 copies8 bytes
// and returns the key slot. The float payload uses that storage ABI by bits.
float &Rva005983EE::lookup(const NameKeyType &key)
{
 NameKeyGenerator::KeyToBucketMap *table=(NameKeyGenerator::KeyToBucketMap*)this;
 IntegerLookupProvider::iterator it=((IntegerLookupProvider*)this)->find(*(const int*)&key);
 if (!it.node) {
  struct FloatValue {NameKeyType first;float second;} value={key,0.0f};
  return *(float*)(table->insertNode(*(const NameKeyGenerator::KeyToBucketMap::value_type*)&value)+1);
 }
 return ((ArmyPercentageNodeView*)it.node)->percentage;
}

struct HeroBuildableFieldsView : Rva00598C3AItem {
 char pad14[0x21-0x14]; bool flag21; char pad22[0x38-0x22];
 int quantity; AsciiString extraName; int context;
 int getQuantity() const { return quantity; }
};
Rva00598C3AItem *AIUnitBuilder::createBestHeroToBuild()
{
 Rva004DFBED *stats=(Rva004DFBED *)g_00DFEEF8->rva002A8F24((Player *)m_30);
 int used=0;
 for (_STL::list<Rva00598C3AItem *>::const_iterator i=m_items.begin();i!=m_items.end();) { HeroBuildableFieldsView *item=(HeroBuildableFieldsView*)*i; ++i; used+=item->getQuantity(); }
 AIBuildableUnit *result=0;
 int cap=((Rva002A7461 *)((char *)m_30+0x60))->rva002A7548(0)-used;
 if (!heroNames.empty()) {
   int index=getHeroIndex();
   AsciiString *name=&heroNames[index];
   BuildableUnitTemplateView *thing=(BuildableUnitTemplateView *)TheThingFactory->findTemplate(*name);
   Object *factory=Rva005982EA(name,0,true);
   bool fits=thing->getQuantity()<cap;
   bool existing=stats->rva004DFBED(*name)!=0 || ((Rva00598192 *)this)->rva00598192(*name)!=0;
   bool found=factory!=0;
   if (!existing && found) {
     ThingTemplate *costTemplate=(ThingTemplate *)TheThingFactory->findTemplate(*name);
     cost48=costTemplate->rva0033A69A((const Player *)m_30,(int)factory,-1);
     Rva004DFBED *current=(Rva004DFBED *)g_00DFEEF8->rva002A8F24((Player *)m_30);
     if (current->economy->available>=(unsigned int)cost48 && fits) {
       result=new AIBuildableUnit((int)m_30);
       result->name0C=*name;
       result->field04=-1.0f;
       ((HeroBuildableFieldsView *)result)->flag21=true;
       heroIndex=-1;
       cost48=-1;
       ((_STL::vector<const ModuleData *> *)&removedHeroes)->push_back((const ModuleData *const &)index);
     }
   } else heroIndex=-1;
   if (result) {
     ((HeroBuildableFieldsView *)result)->quantity=((BuildableUnitTemplateView *)TheThingFactory->findTemplate(result->name0C))->quantity;
     ((HeroBuildableFieldsView *)result)->extraName=result->name0C;
     m_34=true;
     return result;
   }
 }
 return 0;
}

// Native59858C..598738 RET0; WB152D310 createBestHeroToBuild.
// Quantity accessor leaves BL for fits; advancing the pending iterator
// before accumulation retains ECX item/EDX end and the native 14-byte frame.

class GameWindow;class WindowVideo;
class WindowVideoManager {public:struct hashConstGameWindowPtr;};
typedef _STL::pair<const GameWindow *const,WindowVideo*> WindowProviderValue;
typedef _STL::hashtable<WindowProviderValue,const GameWindow*,WindowVideoManager::hashConstGameWindowPtr,_STL::_Select1st<WindowProviderValue>,_STL::equal_to<const GameWindow*>,_STL::allocator<WindowProviderValue> > WindowProvider;
namespace _STL {
template<> struct _Ht_iterator<WindowProviderValue,_Nonconst_traits<WindowProviderValue>,const GameWindow*,WindowVideoManager::hashConstGameWindowPtr,_Select1st<WindowProviderValue>,equal_to<const GameWindow*>,allocator<WindowProviderValue> > {
 void *node; void *table;
 _Ht_iterator(void *n,void *t):node(n),table(t){}
 _Ht_iterator &operator++();
};
}
class ArmyMemberDefinition {public:float getInterpolatedPercentageOfArmy(void*);};
// WB152EA20 identifies rebuildArmyPercentages; native598A3D..598B2A
// calls the keyed lookup over percentage8 and normalizes by total. The
// existing window-table iterator providers access only the node/table ABI;
// no GameWindow or WindowVideo payload identity is inferred here. Its
// constructor preserves the native hidden-output iterator return convention.
void AIUnitBuilder::rebuildArmyPercentages()
{
 float total=0.0f;
 _STL::vector<AsciiString*> &names=((Rva00598007*)this)->rva00598007()->config160->unitNames;
 
 for(_STL::vector<AsciiString*>::iterator i=names.begin();i!=names.end();++i) {
  // Retain the map receiver inside the guarded iteration: the equal-arm
  // expression reproduces retail's post-guard materialization under VC7.1.
  Rva005983EE &lookup=*(i!=names.end()?(Rva005983EE*)m_pad18:(Rva005983EE*)m_pad18);
  AsciiString *name=*i;
  NameKeyType key=TheNameKeyGenerator->nameToKey(*name);
  if(Rva005982EA(name,0,true)) {
   float percentage=((ArmyMemberDefinition*)name)->getInterpolatedPercentageOfArmy(m_30);
   lookup.lookup(key)=percentage;
   total+=percentage;
  } else lookup.lookup(key)=0.0f;
 }
 if(total>0.0f) {
  float scale=100.0f/total;
  WindowProvider *table=(WindowProvider*)m_pad18;
  for(WindowProvider::iterator it=table->begin();it.node;++it)
   ((ArmyPercentageNodeView*)it.node)->percentage*=scale;
 }
}

// ArmyPercentageMap::operator[]
// partial score=1.0 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /D_STLP_NO_EXCEPTIONS /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
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
#include <list>
#include <map>
#include <hash_map>
#include <vector>
#include "ascii_string.h"
struct Rva00598052Owner {char unknown00[0x3AC];int playerId;};
class Rva002E2903Player;
class Rva002BA8F1Logic {public: Rva002E2903Player *find(int,unsigned int *);};
class Rva003F468D;
class Rva0020E6B7RegionManager {public: Rva003F468D *rva0020E6B7();};
class LivingWorldLogic {public: char unknown00[0xB0]; Rva0020E6B7RegionManager *manager;};
extern LivingWorldLogic *TheLivingWorldLogic;
#include "C:/Users/franz/.codex/worktrees/ec82/openbfme2/Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
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

class ArmyMemberDefinition {public:AsciiString name;float getInterpolatedPercentageOfArmy(void*);};
struct Rva00598961Config {char pad00[4];_STL::vector<ArmyMemberDefinition*> members;char pad10[12];float field1C;};
struct Rva002A8AB1Record {char pad00[0x160];Rva00598961Config *config160;};
class Rva00598007 {public:Rva002A8AB1Record *rva00598007();bool rva0059802E();};
class Rva002D06CA {public:void *rva002D06CA(const AsciiString*);};
extern Rva002D06CA *TheThingFactory;
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
namespace rts {template<class T>struct hash {unsigned operator()(const T&x)const{return (unsigned)x;}};}
typedef _STL::hash_map<NameKeyType,float,rts::hash<NameKeyType> > ArmyPercentageMap;
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString&); };
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
	void Rva00598A3D();
	void manageConstructingList();
	void build();
	void Rva00598052();
	void Rva00598D7A();
	Object *Rva005982EA(const AsciiString*,_STL::vector<ObjectID>*,bool);
	Rva00598C3AItem *createBestHeroToBuild();
	Rva00598C3AItem *createBestUnitToMake();

private:
	unsigned char m_pad00[8];
	_STL::multimap<NameKeyType,ObjectID> m_objects; // +8,12B includes comparator storage
	_STL::list<Rva00598C3AItem *> m_items; // +0x14
	ArmyPercentageMap m_percentages; // +18,20B
	bool m_2C; // +0x2C, read and cleared by target bytes
	unsigned char m_pad2D[0x30 - 0x2D];
	Rva00598052Owner *m_30; // +0x30
	bool m_34; // +0x34
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
		Rva00598A3D();
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
   Rva00598961Template *thing=(Rva00598961Template*)TheThingFactory->rva002D06CA(&item->name0C);
   if(thing->field113&4)m_34=false;
   ((Rva00506FE9Hit*)item)->rva0055ADBA(m_30);
   ::delete item;
   i=m_items.erase(i);
   break;
  }
 }
}


template float &ArmyPercentageMap::operator[](const NameKeyType&);

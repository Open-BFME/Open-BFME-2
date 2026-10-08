// ?createBestHeroToBuild@AIUnitBuilder@@QAEPAVRva00598C3AItem@@XZ
// partial score=0.86 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/GameEngine/Source/Common
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
#include <vector>
#include "ascii_string.h"
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

struct Rva00598961Config {char pad00[0x1C];float field1C;};
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
 int getHeroIndex();
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



// Native598D7A..598DA2: flag2C update, build, then tail to598052.


// Native5982EA..5983DA is240B RET12; WB152E7A0 follows the same flow.
// AIUnitBuilder's observed +8 equal-key tree supplies ObjectID bit patterns
// to the canonical object lookup. NameKeyType/ObjectID STLport storage is a
// semantic view established by the two providers; original typedef is unknown. Full Object
// layout is not claimed: id74/status438 and module getter28BC58 are observed.
// Interface slots25/17 and the optional excluded-ID vector are target facts;
// their original names remain unresolved. Exclusion end is read before begin.


// WB152E310 names manageConstructingList at AIUnitBuilder.cpp:440.
// Native598961..598A3D is220B. Item float04/name0C/state10 and slots0/7
// are observed; slot0 follows scalar deleting-dtor ABI. Global ::delete
// preserves the native flags0 call and separate operator delete. Template
// byte113 bit04 clears builder34; its full type and flag meaning are open.
// The observed500 float sentinel and config160/word1C are preserved.


// Existing factory result uses the neutral callback-prefix view Rva00598C3AItem.
// Provider constructor 0x005DAC38 and allocation44 establish this accessed layout.
class AIBuildableUnit : public Rva00598C3AItem {
public:
 AIBuildableUnit(int);
 char pad14[0x38-0x14]; int quantity; int productionId; int context;
};
struct BuildableUnitTemplateView { char pad[0x618]; int quantity; };
// WB 0x0152CFC0 names createBestUnitToMake and assert180.
// Native REL32 at598B8E returns the AsciiString from399B RET4 hidden-result
// decideWhichTemplateToMake 5987D2; WB152DCA0 asserts354..399 prove the name.






class Player;
class Rva002A8F24 { public: void *rva002A8F24(Player *); };
extern Rva002A8F24 *g_00DFEEF8;
// Native51B at4DFBED returns the keyed count at node+8 or0; RET4.
// WB129B860 reads the same AsciiString reference; identity stays address-named.
struct HeroEconomyStatsView { char pad[0x14]; unsigned int available; };
class Rva004DFBED { public: char pad[0x0c]; HeroEconomyStatsView *economy; int rva004DFBED(const AsciiString &); };
class Rva00598192 { public: int rva00598192(const AsciiString &); };
int GetGameLogicRandomValue(int,int,char *,int);
// WB152D170 names getHeroIndex; assertions200..225 and native165B agree.



class Rva002A7461 { public: int rva002A7548(int); };
class ThingTemplate { public: int rva0033A69A(const Player *,int,int) const; };
class ModuleData;
struct HeroBuildableFieldsView : Rva00598C3AItem {
 char pad14[0x21-0x14]; bool flag21; char pad22[0x38-0x22];
 int quantity; AsciiString extraName; int context;
 int getQuantity() const { return quantity; }
};
Rva00598C3AItem *AIUnitBuilder::createBestHeroToBuild()
{
 Rva004DFBED *stats=(Rva004DFBED *)g_00DFEEF8->rva002A8F24((Player *)m_30);
 int used=0;
 for (_STL::list<Rva00598C3AItem *>::const_iterator i=m_items.begin();i!=m_items.end();++i) used+=((HeroBuildableFieldsView *)*i)->getQuantity();
 AIBuildableUnit *result=0;
 int cap=((Rva002A7461 *)((char *)m_30+0x60))->rva002A7548(0)-used;
 if (!heroNames.empty()) {
   int index=getHeroIndex();
   AsciiString *name=&heroNames[index];
   BuildableUnitTemplateView *thing=(BuildableUnitTemplateView *)TheThingFactory->rva002D06CA(name);
   Object *factory=Rva005982EA(name,0,true);
   bool fits=thing->quantity<cap;
   bool existing=stats->rva004DFBED(*name)!=0 || ((Rva00598192 *)this)->rva00598192(*name)!=0;
   bool found=factory!=0;
   if (!existing && found) {
     ThingTemplate *costTemplate=(ThingTemplate *)TheThingFactory->rva002D06CA(name);
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
     ((HeroBuildableFieldsView *)result)->quantity=((BuildableUnitTemplateView *)TheThingFactory->rva002D06CA(&result->name0C))->quantity;
     ((HeroBuildableFieldsView *)result)->extraName=result->name0C;
     m_34=true;
     return result;
   }
 }
 return 0;
}

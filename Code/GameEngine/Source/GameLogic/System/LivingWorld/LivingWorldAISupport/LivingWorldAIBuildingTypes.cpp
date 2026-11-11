// cl: /O1 /G7 /arch:SSE /MD /EHs /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// LivingWorldAIBuildingTypes initialization, native 00502FE9..00503554 (1387B), RET4.
// The receiver identity comes from WB12FC460/12FC890/12FC560 named consumers
// of the +38/+44 maps (LivingWorldAIInformation.cpp), and caller4FB222's +18
// subobject. The initializer's original method name remains unknown; retain
// its existing address-derived ABI spelling instead of inventing a name.
// WB12FB830 and native calls establish the building/SpawnArmy/template graph.
// SpawnArmy is the 88B SpawnArmy record (WB128AFA0, native virtual4E30C6).
// StrengthenKey is a 16B lookup record: WB local40..34 precedes iterator30.
// Only its minCount word is initialized/read here. The three bonus field
// types come from the independently recovered table entry/caller3F777F and
// LivingWorldAutoResolveBattleBonus.cpp; their use in this initializer is not
// inferred from the byte match. A scalar int key wrongly shifts all stack homes.
// Container adapters retain existing verified provider ABIs. They are access
// views, not new assertions of original template identities or complete types.
// PairCopy expresses the two distinct live 92B objects proved by native EH.
// Visible insertion workers are required for the native compiler stack layout;
// their complete136/59/250B bodies and29B pair/map wrappers were also verified.
// Parent: complete bytes/relocations and16-state EH graph independently EXACT.
// Retail spells _Rb_tree::insert_unique(const value_type&)'s leftmost fast path
// as `if (__comp && __j == begin())`; the vendored STLport carries it behind this switch.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "ascii_string.h"
#include <vector>
#include <map>
#include <set>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> bool less<int>::operator()(int const &, int const &) const; }
// bfme link decl-only end
enum ScienceType {SCIENCE_NONE=0};
enum NameKeyType {NAMEKEY_NONE=0};
class Rva0022C0CDSubsystem;extern Rva0022C0CDSubsystem*TheLivingWorldBuildingTemplateStore;
class LivingWorldLogic;extern LivingWorldLogic*TheLivingWorldLogic;
class Rva00E02D6C;extern Rva00E02D6C*TheCampaignManager;
class ArmorTemplate;class Rva002B6498 {public:ArmorTemplate*rva002B6498(NameKeyType);};
class Rva002E02F0 {public:void rva002E02F0(int,_STL::vector<ScienceType>*);};
class Rva002E2903Player {public:char gap[0x40];int score;};
#include "../../../../../Include/GameLogic/Rva002BA8F1Logic.h"
class BuildingNuggetView {public:char gap[8];int type;int amount;};
#include "../../../../../Include/GameLogic/LivingWorldBuildingTemplate.h"
struct Rva003F751ANode {char gap[0x18];int value;};
class Rva003F751A {public:Rva003F751ANode*rva003F751A(const int*);};
struct StrengthenKey {int minCount;float weaponBonus,armorBonus,experienceBonus;};
struct StrengthenNugget {char gap[16];Rva003F751ANode*header;};
class Rva003B8E89 {public:void*rva003B8E89(void*);};
#include "../../../../../Include/GameLogic/Rva0040CB2CIndexedField.h"
class BfmeY1038 {public:int bfmeVal1038();};
class Rva0033A674 {public:void*rva0033A674();};
class ThingTemplate;class ThingFactory {public:const ThingTemplate*findTemplate(const AsciiString&);};extern ThingFactory*TheThingFactory;
struct TemplateView {char gap[0x5c4];int category;};
struct SummaryView {char gap[0x40];_STL::vector<_STL::pair<int,int> >entries;};
#include "../../../../../Include/Common/SpawnArmy.h"
class Rva00500500 {public:Rva00500500(void*&,const SpawnArmy&);Rva00500500(const Rva00500500&);void*key;SpawnArmy value;};
struct SpawnView {char gap[8];_STL::vector<SpawnArmy>entries;};
struct BfmePod88 {char body[88];};
typedef _STL::vector<BfmePod88> PodVector;
typedef _STL::vector<PodVector> PodVectors;
struct Rva00500EFARecord {char bytes[12];};
namespace _STL {template<> void vector<Rva00500EFARecord>::reserve(unsigned);}
namespace _STL {template<> void PodVectors::push_back(const PodVector&);}
struct Rva004FABE2 {
 _STL::_Vector_base<BfmePod88,_STL::allocator<BfmePod88> > data;
 Rva004FABE2():data(_STL::allocator<BfmePod88>()){}
 ~Rva004FABE2();
};
struct Rva00500E3D {
 _STL::_Vector_base<PodVector,_STL::allocator<PodVector> > data;
 Rva00500E3D():data(_STL::allocator<PodVector>()){}
 ~Rva00500E3D();
 PodVector&operator[](int i){return ((PodVectors*)this)->operator[](i);}
 void reserve(unsigned n){((_STL::vector<Rva00500EFARecord>*)this)->reserve(n);}
 void push_back(const Rva004FABE2&v){((PodVectors*)this)->push_back((const PodVector&)v);}
};
struct Rva004FFE96Element {char bytes[8];};
typedef _STL::set<Rva004FFE96Element> NativeSet;
namespace _STL {template<> NativeSet::set();}
struct Rva004FF582 {NativeSet data;~Rva004FF582();};
struct Rva005020AFSub:public Rva004FF582 {Rva005020AFSub(){};Rva005020AFSub(const Rva005020AFSub&);};
struct Rva0050245DElement {int key;Rva005020AFSub value;Rva0050245DElement(const int&,const Rva005020AFSub&);};
struct Rva00502667Element {int key;Rva005020AFSub value;Rva00502667Element(const Rva00502667Element&);};
struct Rva00502BCDMapped {char data[12];};
typedef _STL::map<int,Rva00502BCDMapped> SetMap;
namespace _STL {
template<> struct pair<const int,PodVectors> {typedef const int first_type;typedef PodVectors second_type;const int first;Rva00500E3D second;pair(const int&,const PodVectors&);pair(const pair&);};
template<> void vector<ScienceType>::push_back(const ScienceType&);
template<> void PodVector::push_back(const BfmePod88&);
// Node creation is the rowed bodies 0x00501DB2 and 0x005028E7; this unit's own
// copies would construct the pair differently from retail's.
typedef _Rb_tree<int,pair<const int,PodVectors>,_Select1st<pair<const int,PodVectors> >,less<int>,allocator<pair<const int,PodVectors> > > VectorMapTree;
typedef _Rb_tree<int,pair<const int,Rva00502BCDMapped>,_Select1st<pair<const int,Rva00502BCDMapped> >,less<int>,allocator<pair<const int,Rva00502BCDMapped> > > SetMapTree;
template<> VectorMapTree::_Link_type VectorMapTree::_M_create_node(const pair<const int,PodVectors>&);
template<> SetMapTree::_Link_type SetMapTree::_M_create_node(const pair<const int,Rva00502BCDMapped>&);

template<> inline __declspec(noinline) SetMap::iterator SetMap::insert(SetMap::iterator p,const SetMap::value_type&v){return _M_t.insert_unique(p,v);}
}
typedef _STL::map<int,PodVectors> VectorMap;
namespace _STL {template<> inline __declspec(noinline) VectorMap::iterator VectorMap::insert(VectorMap::iterator p,const VectorMap::value_type&v){return _M_t.insert_unique(p,v);}}
struct Rva00500BF5Node
{
    bool color;
    unsigned char color_padding[3];
    Rva00500BF5Node *parent;
    Rva00500BF5Node *left;
    Rva00500BF5Node *right;
    unsigned key;
};

class Rva00500BF5Tree {public:typedef _STL::_Rb_tree_iterator<Rva00500500,_STL::_Nonconst_traits<Rva00500500> >Iterator;Iterator insertEqual(Iterator,const Rva00500500&);void*createNode(const Rva00500500&);Iterator insertWorker(Rva00500BF5Node*,Rva00500BF5Node*,const Rva00500500&,Rva00500BF5Node*);Iterator insertEqualWorker(const Rva00500500&);__forceinline Iterator insert(Iterator p,const Rva00500500&v){return insertEqual(p,v);}private:Rva00500BF5Node*m_header;unsigned m_count;};
inline __declspec(noinline) Rva00500BF5Tree::Iterator Rva00500BF5Tree::insertEqual(
    Iterator position, const Rva00500500 &value)
{
    Rva00500BF5Node *pos = reinterpret_cast<Rva00500BF5Node *>(position._M_node);
    if (pos == m_header->left) {
        if (m_count <= 0)
            return insertEqualWorker(value);
        if (!(pos->key < *reinterpret_cast<const unsigned *>(&value)))
            return insertWorker(pos, pos, value, 0);
        if (pos->left == pos)
            return insertWorker(0, pos, value, 0);

        Iterator after = position;
        ++after;
        Rva00500BF5Node *next = reinterpret_cast<Rva00500BF5Node *>(after._M_node);
        if (next == m_header || !(next->key < *reinterpret_cast<const unsigned *>(&value))) {
            if (pos->right == 0)
                return insertWorker(0, pos, value, pos);
            return insertWorker(next, next, value, 0);
        }
        return insertEqualWorker(value);
    } else if (pos == m_header) {
        if (!(*reinterpret_cast<const unsigned *>(&value) < m_header->right->key))
            return insertWorker(0, m_header->right, value, pos);
        return insertEqualWorker(value);
    } else {
        Iterator before = position;
        --before;
        bool pos_less = pos->key < *reinterpret_cast<const unsigned *>(&value);
        Rva00500BF5Node *prev = reinterpret_cast<Rva00500BF5Node *>(before._M_node);
        if (!pos_less && !(*reinterpret_cast<const unsigned *>(&value) < prev->key)) {
            if (prev->right == 0)
                return insertWorker(0, prev, value, prev);
            return insertWorker(pos, pos, value, 0);
        }
        Iterator after = position;
        ++after;
        Rva00500BF5Node *next = reinterpret_cast<Rva00500BF5Node *>(after._M_node);
        if (pos_less &&
            (next == m_header || !(next->key < *reinterpret_cast<const unsigned *>(&value)))) {
            if (pos->right == 0)
                return insertWorker(0, pos, value, pos);
            return insertWorker(next, next, value, 0);
        }
        return insertEqualWorker(value);
    }
}


inline __declspec(noinline) Rva00500BF5Tree::Iterator Rva00500BF5Tree::insertWorker(Rva00500BF5Node *x,
                           Rva00500BF5Node *y, const Rva00500500 &value,
                           Rva00500BF5Node *known_order)
{
    Rva00500BF5Node *node;
    if (y != m_header &&
        (known_order != 0 ||
         (x == 0 && *reinterpret_cast<const unsigned *>(&value) >= y->key))) {
        node = reinterpret_cast<Rva00500BF5Node *>(createNode(value));
        y->right = node;
        Rva00500BF5Node *header = m_header;
        if (y == header->right)
            header->right = node;
    } else {
        node = reinterpret_cast<Rva00500BF5Node *>(createNode(value));
        y->left = node;
        Rva00500BF5Node *header = m_header;
        if (y == header) {
            header->parent = node;
            m_header->right = node;
        } else if (y == header->left) {
            header->left = node;
        }
    }
    node->left = 0;
    node->right = 0;
    node->parent = y;
    _STL::_Rb_global<bool>::_Rebalance(
        reinterpret_cast<_STL::_Rb_tree_node_base *>(node),
        reinterpret_cast<_STL::_Rb_tree_node_base *&>(m_header->parent));
    ++m_count;
    return Iterator((_STL::_Rb_tree_node<Rva00500500>*)node);
}

inline __declspec(noinline) Rva00500BF5Tree::Iterator Rva00500BF5Tree::insertEqualWorker(const Rva00500500 &value)
{
    Rva00500BF5Node *y = m_header;
    Rva00500BF5Node *x = m_header->parent;
    while (x != 0) {
        y = x;
        x = *reinterpret_cast<const unsigned *>(&value) < x->key ? x->left : x->right;
    }
    return insertWorker(x, y, value, 0);
}


class Rva00501F2D {public:void rva0050247A();};class Rva005007CF {public:void rva00500AA6();};
static __forceinline const Rva00500500&AsReference(const Rva00500500&v){return v;}
struct PairCopy{Rva00500500 value;__forceinline PairCopy(const Rva00500500&v):value(v){} operator const Rva00500500&()const{return value;} const Rva00500500&get()const{return value;}};
// The Rva00500500 ctor is defined in Rva00500500Ctors.cpp.
void Rva005020CCBuildRegionDistances();
class Rva00502FE9 {public:void rva00502FE9(int);int commandBuilding,spawnBuilding,strengthBuilding,upgradeBuilding;_STL::vector<ScienceType>spawnBuildings;int commandPoints;float average;char gap24[12];int strengthenAmount,upgradeAmount;VectorMap vectors;SetMap sets;};
void Rva00502FE9::rva00502FE9(int playerID) {
 _STL::vector<ScienceType> buildings;
 int playerScore=((Rva002BA8F1Logic*)TheLivingWorldLogic)->find(playerID,0)->score;
 ((Rva002E02F0*)TheLivingWorldBuildingTemplateStore)->rva002E02F0(playerScore,&buildings);
 for(unsigned i=0;i<buildings.size();++i) {
  BuildingNuggetView*command=((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)buildings[i]))->findNugget(AsciiString("IncreaseCommandPoints"));
  BuildingNuggetView*spawn=((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)buildings[i]))->findNugget(AsciiString("SpawnArmy"));
  BuildingNuggetView*strengthen=((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)buildings[i]))->findNugget(AsciiString("StrengthenArmy"));
  BuildingNuggetView*upgrade=((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)buildings[i]))->findNugget(AsciiString("UpgradeTroops"));
  if(command && command->type!=1)command=0;
  if(command){commandBuilding=buildings[i];commandPoints=command->amount;}
  else if(strengthen){strengthBuilding=buildings[i];StrengthenKey key;key.minCount=1;StrengthenNugget*strengthenNugget=(StrengthenNugget*)strengthen;Rva003F751ANode*it=((Rva003F751A*)&strengthenNugget->header)->rva003F751A(&key.minCount);if(it!=strengthenNugget->header)strengthenAmount=it->value;}
  else if(upgrade){upgradeBuilding=buildings[i];upgradeAmount=10;}
  if(spawn){if(!command&&!strengthen&&!upgrade)spawnBuilding=buildings[i];spawnBuildings.push_back(buildings[i]);}
 }
 ((Rva00501F2D*)&vectors)->rva0050247A();((Rva005007CF*)&sets)->rva00500AA6();
 for(unsigned i=0;i<spawnBuildings.size();++i){
  int count=0;Rva00500E3D byCategory;byCategory.reserve(8);Rva004FABE2 empty;
  for(int j=0;j<8;++j)byCategory.push_back(empty);
  Rva005020AFSub ordered;
  SpawnView*spawn=(SpawnView*)((LivingWorldBuildingTemplate*)((Rva002B6498*)TheLivingWorldBuildingTemplateStore)->rva002B6498((NameKeyType)spawnBuildings[i]))->findNugget(AsciiString("SpawnArmy"));
  if(spawn){_STL::vector<SpawnArmy>&entries=spawn->entries;for(unsigned j=0;j<entries.size();++j){
   SpawnArmy&entry=entries[j];
   if(((SpawnArmy*)&entry)->rva00319CED()){
    SummaryView*summary=(SummaryView*)((Rva003B8E89*)TheCampaignManager)->rva003B8E89((char*)&entry+0x2c);
    int size=summary->entries.size();
    for(int k=0;k<size;++k){
     int row=((Rva0040CB2CIndexedField*)summary)->get(k);AsciiString name(*(AsciiString*)(row+4));
     const ThingTemplate*thing=TheThingFactory->findTemplate(name);
     byCategory[((TemplateView*)thing)->category].push_back((const BfmePod88&)entry);
     void*key=((Rva0033A674*)thing)->rva0033A674();
     ((Rva00500BF5Tree*)&ordered)->insert(Rva00500BF5Tree::Iterator((_STL::_Rb_tree_node<Rva00500500>*)*(void**)&ordered),PairCopy(Rva00500500(key,entry)).value);
    }
    average+=(float)((BfmeY1038*)summary)->bfmeVal1038();++count;
   }
  }
  }
  _STL::pair<const int,PodVectors> vectorPair(reinterpret_cast<const int&>(spawnBuildings[i]),(const PodVectors&)byCategory);
  { _STL::pair<const int,PodVectors> copied(vectorPair);vectors.insert(vectors.begin(),copied); }
  Rva0050245DElement setPair(reinterpret_cast<const int&>(spawnBuildings[i]),ordered);
  { Rva00502667Element copied((const Rva00502667Element&)setPair);sets.insert(sets.begin(),(const SetMap::value_type&)copied); }
  if(count>0)average/=count;else average=0;
 }
 Rva005020CCBuildRegionDistances();
}

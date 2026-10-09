// cl: /O1 /Oy- /G7 /arch:SSE /MD /GX- /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// Target callbacks: science4138C7120B/WB12E6D90 and resource414009120B/WB12E8610.
// Each builds twelve-byte bonus {minimum=-1; two floats=1}, parses through
// its owned65B member and inserts key+copied twelve-byte data into store.
// The existing 134B scalar-key insertion and168B raw-POD node insertion
// name ModuleFactory::ModuleTemplate as an emitter view. These callbacks
// use that exact field-blind provider as an explicit twelve-byte ABI view;
// their real mapped payloads are the independently parsed bonus records.
// INIException uses its actual8B owning layout and existing copy/destructor;
// the normal C++ throw emits the real exception metadata, no synthetic anchor.
// Scope the returned iterator/bool before throwing so its8B slot is reused.
// Preserve retail's resource diagnostic typo "MinResounceBonus" verbatim.
#include <map>
class INI;
class INIException { public: char *message; int count; INIException(int,const char *,...); INIException(const INIException &); ~INIException(); };
class LivingWorldAutoResolveSciencePurchasePointBonus {
public:
 LivingWorldAutoResolveSciencePurchasePointBonus():minimum(-1),firstMultiplier(1.0f),secondMultiplier(1.0f) {}
 void parseBonusIniSubBlock(INI *);
 int minimum;float firstMultiplier,secondMultiplier;
};
class LivingWorldAutoResolveResourceBonus {
public:
 LivingWorldAutoResolveResourceBonus():minimum(-1),firstMultiplier(1.0f),secondMultiplier(1.0f) {}
 void parseBonusIniSubBlock(INI *);
 int minimum;float firstMultiplier,secondMultiplier;
};
enum NameKeyType { NAMEKEY_0 };
class ModuleFactory { public: class ModuleTemplate { public: void *createProc,*createDataProc;int whichInterfaces; }; };
typedef _STL::pair<const NameKeyType,ModuleFactory::ModuleTemplate> InsertValue;
typedef _STL::_Rb_tree<NameKeyType,InsertValue,_STL::_Select1st<InsertValue>,_STL::less<NameKeyType>,_STL::allocator<InsertValue> > InsertTree;
template<> _STL::pair<InsertTree::iterator,bool> InsertTree::insert_unique(const InsertValue &);
void Rva004138C7Parse(INI *ini,void *,void *store,const void *) {
 LivingWorldAutoResolveSciencePurchasePointBonus bonus;
 bonus.parseBonusIniSubBlock(ini);
 int minimum=bonus.minimum;
 InsertValue entry((NameKeyType)minimum,*reinterpret_cast<const ModuleFactory::ModuleTemplate *>(&bonus));
 {
 _STL::pair<InsertTree::iterator,bool> inserted=reinterpret_cast<InsertTree *>(store)->insert_unique(entry);
 if(inserted.second) return;
 }
 throw INIException(3,"Duplicate MinSciencePurchasePointsForBonus %d",minimum);
}

void Rva00414009Parse(INI *ini,void *,void *store,const void *) {
 LivingWorldAutoResolveResourceBonus bonus;
 bonus.parseBonusIniSubBlock(ini);
 int minimum=bonus.minimum;
 InsertValue entry((NameKeyType)minimum,*reinterpret_cast<const ModuleFactory::ModuleTemplate *>(&bonus));
 {
 _STL::pair<InsertTree::iterator,bool> inserted=reinterpret_cast<InsertTree *>(store)->insert_unique(entry);
 if(inserted.second) return;
 }
 throw INIException(3,"Duplicate MinResounceBonus %d",minimum);
}

// cl: /Ob2 /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /ICode/Libraries/Source/debug
// stlport
// Native40ADDD..40ADFA and40BAAA..40BAD0. Award trigger records
// occupy16B, and their key-list prefixes are compared by rowed40AD5A.
// The389B INI award parser40BAF7 uses these contains/add operations.
namespace _STL { void __cdecl free(void *); }
#include <vector>
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
#include "debug.h"
class Rva0040A7D5;
struct Rva0040ABA5Item;
const Rva0040ABA5Item *Rva0040AD5AFind(const Rva0040ABA5Item *,const Rva0040ABA5Item *,const Rva0040A7D5 *);

enum NameKeyType { NAMEKEY_INVALID=0 };
namespace _STL {
template<> inline void allocator<NameKeyType>::deallocate(pointer p,size_type) const { if(p) _STL::free(static_cast<void *>(p)); }
template<> __declspec(noinline) _Vector_base<NameKeyType,allocator<NameKeyType> >::_Vector_base(const allocator<NameKeyType> &a)
 : _M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
}
class Rva0040AECC {
public:__declspec(noinline) Rva0040AECC();
public:_STL::vector<NameKeyType> keys;unsigned threshold;
};
Rva0040AECC::Rva0040AECC() : threshold(0) {}

class Rva0040AEE3;
namespace _STL {
template<> void vector<Rva0040AEE3>::push_back(const Rva0040AEE3 &);
}

class Rva0040ADDD {
public:
 unsigned char rva0040ADDD(const Rva0040A7D5 *) const;
 bool rva0040BAAA(const Rva0040AEE3 *);
public:
 NameKeyType name;char prefix[0x1C-4];
 const Rva0040ABA5Item *first,*last,*limit;
};
unsigned char Rva0040ADDD::rva0040ADDD(const Rva0040A7D5 *trigger) const
{
 const Rva0040ABA5Item *end=last;
 return Rva0040AD5AFind(first,end,trigger)!=end;
}
bool Rva0040ADDD::rva0040BAAA(const Rva0040AEE3 *trigger)
{
 if(!rva0040ADDD(reinterpret_cast<const Rva0040A7D5 *>(trigger))) {
  reinterpret_cast<_STL::vector<Rva0040AEE3,_STL::allocator<Rva0040AEE3> > *>(&first)->push_back(*trigger);
  return true;
 }
 return false;
}

class Rva0014921EVector;
void rva00149002(int,int,Rva0014921EVector *,int);
struct FieldParse;
class INI {public:
 void initFromINI(void *,const FieldParse *);
 static void dup_002EF72(INI *,void *,void *,const void *);
 static void parseAsciiString(INI *,void *,void *,const void *);
};
typedef void (*AwardFieldParser)(INI *,void *,void *,const void *);
struct FieldParse {const char *name;AwardFieldParser parse;const void *userData;unsigned offset;};
extern const char BfmeAwardTriggerStatField[]="Stat";
extern const char BfmeAwardTriggerThresholdField[]="Threshold";
extern const FieldParse BfmeAwardTriggerFields[3]={
 {BfmeAwardTriggerStatField,reinterpret_cast<AwardFieldParser>(&rva00149002),0,0},
 {BfmeAwardTriggerThresholdField,&INI::dup_002EF72,0,12},
 {0,0,0,0}
};
class NameKeyGenerator {public:
 const AsciiString &keyToName(NameKeyType);
 NameKeyType nameToKey(const char *);
 static void parseStringAsNameKeyType(INI *,void *,void *,const void *);
};
extern NameKeyGenerator *TheNameKeyGenerator;
class INIException {public:
 char *mFailureMessage;int mErrorCode;
 INIException(int,const char *,...);
 INIException(const INIException &);
 ~INIException();
};
class Rva0040A7D5 {public:int rva0040A7D5(int) const;};
namespace _STL {template<class I> void sort(I,I);}
struct Rva0040C0C7Element {char bytes[40];};
class Rva0040AF66 {char bytes[104];};
namespace _STL {
template<> void _Destroy(Rva0040AF66 *);
template<> void _Destroy(Rva0040AF66 *,Rva0040AF66 *);
template<> __declspec(noinline) _Vector_base<Rva0040C0C7Element,allocator<Rva0040C0C7Element> >::_Vector_base(const allocator<Rva0040C0C7Element> &a)
 : _M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
template<> __declspec(noinline) _Vector_base<Rva0040AF66,allocator<Rva0040AF66> >::_Vector_base(const allocator<Rva0040AF66> &a)
 : _M_start(0),_M_finish(0),_M_end_of_storage(a,0) {}
}
struct Rva0040BEBA : public _STL::vector<Rva0040C0C7Element> {
 __forceinline Rva0040BEBA() : _STL::vector<Rva0040C0C7Element>() {}
 ~Rva0040BEBA();
};
struct Rva0040B59F : public _STL::vector<Rva0040AF66> {
 __forceinline Rva0040B59F() : _STL::vector<Rva0040AF66>() {}
 ~Rva0040B59F();
};
class AwardSystemManager : public SubsystemInterface {public:
 AwardSystemManager();
 virtual ~AwardSystemManager();
 virtual void init();
 virtual Bool loadIniFilesFromLegend() { return true; }
 virtual void reset() {}
 virtual void update() {}
 static void parseTrigger(INI *,void *,void *,const void *);
 static void parseThingStat(INI *,void *,void *,const void *);
private:
 Rva0040BEBA awards;
 Rva0040B59F statistics;
};
void AwardSystemManager::parseTrigger(INI *ini,void *instance,void *,const void *)
{
 Rva0040AECC trigger;
 ini->initFromINI(&trigger,BfmeAwardTriggerFields);
 _STL::sort(reinterpret_cast<int *>(trigger.keys.begin()),reinterpret_cast<int *>(trigger.keys.end()));
 Rva0040ADDD *award=static_cast<Rva0040ADDD *>(instance);
 if(award->rva0040ADDD(reinterpret_cast<const Rva0040A7D5 *>(&trigger))) {
  AsciiString name=TheNameKeyGenerator->keyToName(award->name);
  throw INIException(3,"Duplicate trigger in the %s award.",reinterpret_cast<const StringBase<char> *>(&name)->str());
 }
 for(unsigned i=0;i<trigger.keys.size();++i) {
  NameKeyType key=static_cast<NameKeyType>(reinterpret_cast<const Rva0040A7D5 *>(&trigger)->rva0040A7D5(i));
  static NameKeyType noneKey=TheNameKeyGenerator->nameToKey("None");
  static NameKeyType emptyKey=TheNameKeyGenerator->nameToKey("");
  if(key==NAMEKEY_INVALID || key==noneKey || key==emptyKey)
   throw INIException(3,"No award name specified while parsing Award.");
 }
 if(!trigger.threshold)
  throw INIException(3,"No threshold set for tigger in AwardSystemManager::parseTrigger.");
 award->rva0040BAAA(reinterpret_cast<const Rva0040AEE3 *>(&trigger));
}

// Native ObjectAward block callback40C125. The constructor/destructor
// providers independently establish the40B record extent and string homes.
class Rva0040B77E {
public:
 ~Rva0040B77E();
 NameKeyType name;
 _STL::vector<NameKeyType> upgradeAwards;
 AsciiString nameTag,descriptionTag,imageName;
 _STL::vector<Rva0040AECC> triggers;
};
class Rva0040B6D4 : public Rva0040B77E {public:Rva0040B6D4();};
struct BfmePod40 {int words[10];};
struct Rva0040C0C7Element;
class Rva0040AAD5 {public:
 BfmePod40 *rva0040AAD5(int);
 bool rva0040C0FE(const Rva0040C0C7Element &);
};
extern Rva0040AAD5 *g_00E02F74;
class Image;
class ImageCollection {public:const Image *findImageByName(const AsciiString &);};
extern ImageCollection *TheMappedImageCollection;
extern const char BfmeObjectAwardNameField[]="AwardName";
extern const char BfmeObjectAwardImageField[]="ImageName";
extern const char BfmeObjectAwardNameTagField[]="NameTag";
extern const char BfmeObjectAwardDescriptionField[]="DescriptionTag";
extern const char BfmeObjectAwardUpgradesField[]="UpgradeAwards";
extern const char BfmeObjectAwardTriggerField[]="Trigger";
extern const FieldParse BfmeObjectAwardFields[7]={
 {BfmeObjectAwardNameField,&NameKeyGenerator::parseStringAsNameKeyType,0,0},
 {BfmeObjectAwardImageField,&INI::parseAsciiString,0,24},
 {BfmeObjectAwardNameTagField,&INI::parseAsciiString,0,16},
 {BfmeObjectAwardDescriptionField,&INI::parseAsciiString,0,20},
 {BfmeObjectAwardUpgradesField,reinterpret_cast<AwardFieldParser>(&rva00149002),0,4},
 {BfmeObjectAwardTriggerField,&AwardSystemManager::parseTrigger,0,28},
 {0,0,0,0}
};
void Rva0040C125Parse(INI *ini)
{
 Rva0040B6D4 award;
 ini->initFromINI(&award,BfmeObjectAwardFields);
 NameKeyType key=award.name;
 static NameKeyType noneKey=TheNameKeyGenerator->nameToKey("None");
 static NameKeyType emptyKey=TheNameKeyGenerator->nameToKey("");
 if(key==NAMEKEY_INVALID || key==noneKey || key==emptyKey)
  throw INIException(3,"No award name specified while parsing Award.");
 BfmePod40 *existing=g_00E02F74->rva0040AAD5(key);
 if(existing) {
  AsciiString name=TheNameKeyGenerator->keyToName(static_cast<NameKeyType>(existing->words[0]));
  throw INIException(3,"An Award with the name %s already exists.",reinterpret_cast<const StringBase<char> *>(&name)->str());
 }
 AsciiString text=award.imageName;
 if(text.isNone() || text.isEmpty())
  throw INIException(3,"No image name specified while parsing Award.");
 if(!TheMappedImageCollection->findImageByName(award.imageName))
  reinterpret_cast<StringBase<char> *>(&award.imageName)->set("BuildingNoArt");
 text.setCopyInline(award.nameTag);
 if(text.isNone() || text.isEmpty())
  throw INIException(3,"No name tag specified while parsing Award.");
 text.setCopyInline(award.descriptionTag);
 if(text.isNone() || text.isEmpty())
  throw INIException(3,"No description tag specified while parsing Award.");
 g_00E02F74->rva0040C0FE(reinterpret_cast<const Rva0040C0C7Element &>(award));
}
AwardSystemManager *BfmeAwardSystemManagerInstance=0;
AwardSystemManager::AwardSystemManager()
{
 if(BfmeAwardSystemManagerInstance) {
  Debug::SkipNext(true);
  theDebug->SkipNext();
  (theDebug->CrashBegin(0,0,0)<<"Instance of AwardSystemManager already exists!!").CrashDone(true);
 }
 BfmeAwardSystemManagerInstance=this;
}

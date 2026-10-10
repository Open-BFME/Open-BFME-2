// cl: /Ob2 /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Native40ADDD..40ADFA and40BAAA..40BAD0. Award trigger records
// occupy16B, and their key-list prefixes are compared by rowed40AD5A.
// The389B INI award parser40BAF7 uses these contains/add operations.
namespace _STL { void __cdecl free(void *); }
#include <vector>
#include "ascii_string.h"
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
class AwardSystemManager {public:
 static void parseTrigger(INI *,void *,void *,const void *);
 static void parseThingStat(INI *,void *,void *,const void *);
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

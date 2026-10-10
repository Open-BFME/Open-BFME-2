// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Clean BF1 FXEventParser007764E0.cpp donor at9cbfb551, adapted to target
// C48DB..C4B61 (646B). Native proves token separator420, buffer64 (donor and frame-layout inference),
// 20-byte base with FireWhenSkipped byteC and AsciiString10, raw/shared
// payload14 and cloned FXList refcount28/2C. Original parser name unknown.
// Dependencies retain existing owned names; layouts are target facts.
#include "ascii_string.h"
#include <string.h>
#include <list>
#include <vector>
#include <new>
class INI {public: const char*getNextTokenOrNull(const char*);int scanInt(const char*);};
class FXList;
class FXListStore {public:const FXList*findFXList(const char*)const;};extern FXListStore*TheFXListStore;
class Rva000B6A67 {public:
 Rva000B6A67();int first,frame,third;bool fireWhenSkipped;char padD[3];AsciiString name;
};
struct TargetRef00217D4C {virtual void*destroy(unsigned);int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C*);
struct Rva000B3F15Payload {char pad[0x28];TargetRef00217D4C ref;};
class Rva000B3F15 {public:
 Rva000B3F15():pointer(0){}
 ~Rva000B3F15(){if(pointer)ReleaseTreeHintRef00217D4C(&pointer->ref);}
 Rva000B3F15&operator=(const Rva000B3F15&);
 Rva000B3F15Payload*pointer;
};
class Rva001E2BB0 {public:Rva000B3F15 rva001E2BB0(const char*);};
class Rva000BB491:public Rva000B6A67 {public:const FXList*fx;};
class Rva00B9AC2:public Rva000B6A67 {public:~Rva00B9AC2();Rva000B3F15 fx;};
class Rva000BB4AC {char bytes[24];};
struct Rva000BC0DBElement {double words[1];};
class Rva00704980 {public:
 Rva00704980();int m_00,m_04,m_08,m_0C,m_10,m_14,m_18;char m_1C,m_1D,m_1E,m_1F;
};
// Keep the owned37B zero initializer visible: native preserves the nugget
// pointer in EDX across it, instead of reloading the list element.
Rva00704980::Rva00704980(){m_00=0;m_04=0;m_08=0;m_0C=0;m_10=0;m_14=0;m_18=0;m_1C=0;m_1D=0;m_1E=0;m_1F=0;}
struct BfmePod32:public Rva00704980 {
 ~BfmePod32(){((StringBase<char>*)&m_00)->clear();}
};
void Rva000B9887Init(void*,BfmePod32*);
namespace _STL {
 template<>list<Rva000BC0DBElement,allocator<Rva000BC0DBElement> >::list(const list<Rva000BC0DBElement,allocator<Rva000BC0DBElement> >&);
 template<>_List_base<int,allocator<int> >::~_List_base();
 template<>void vector<Rva000BB491,allocator<Rva000BB491> >::push_back(const Rva000BB491&);
 template<>void vector<Rva000BB4AC,allocator<Rva000BB4AC> >::push_back(const Rva000BB4AC&);
 template<>void list<BfmePod32,allocator<BfmePod32> >::push_back(const BfmePod32&);
}
struct FxNuggetC48DB {int first,kind;};
struct FxNodeC48DB {FxNodeC48DB*next,*prev;FxNuggetC48DB*value;int remainingWord;};
// Payload-independent native4EC395 cleanup owns the same next/prev head.
namespace _STL {
 template<> __forceinline _List_base<Rva000BC0DBElement,allocator<Rva000BC0DBElement> >::~_List_base(){((_List_base<int,allocator<int> >*)this)->~_List_base();}
}
static const char*nextToken(INI*ini){const char*seps=*(const char**)((char*)ini+0x420);return ini->getNextTokenOrNull(seps);}
void rva000C48DB(void*one,void*two,void*three,void*four){
 INI*ini=(INI*)one;
 Rva000BB491 event;char fxName[64];fxName[0]=0;
 const char*token=nextToken(ini);
 while(token){
  if(strcmp(token,"Frame")==0){token=nextToken(ini);if(token)event.frame=ini->scanInt(token);}
  else if(strcmp(token,"FrameStep")==0){token=nextToken(ini);if(token)event.first=ini->scanInt(token);}
  else if(strcmp(token,"FrameStop")==0){token=nextToken(ini);if(token)event.third=ini->scanInt(token);}
  else if(strcmp(token,"FireWhenSkipped")==0){event.fireWhenSkipped=true;}
  else if(strcmp(token,"Name")==0){token=nextToken(ini);strcpy(fxName,token);if(token)event.fx=TheFXListStore->findFXList(token);}
  else if(strcmp(token,"Bone")==0){token=nextToken(ini);((StringBase<char>&)event.name).set(token);}
  token=nextToken(ini);
 }
 if(*((const char*)event.fx+8)){
  Rva00B9AC2 shared;
  shared.frame=event.frame;shared.name=event.name;shared.first=event.first;shared.third=event.third;shared.fireWhenSkipped=event.fireWhenSkipped;
  shared.fx=((Rva001E2BB0*)TheFXListStore)->rva001E2BB0(fxName);
  _STL::list<Rva000BC0DBElement> list(*(const _STL::list<Rva000BC0DBElement>*)((char*)shared.fx.pointer+4));
  for(FxNodeC48DB*it=(*(FxNodeC48DB**)&list)->next;it!=(*(FxNodeC48DB**)&list);it=it->next){
   FxNuggetC48DB*nugget=it->value;
   if(nugget->kind==9){BfmePod32 record;Rva000B9887Init(nugget,&record);((_STL::list<BfmePod32>*)four)->push_back(record);}
  }
  ((_STL::vector<Rva000BB4AC>*)three)->push_back((const Rva000BB4AC&)shared);
 }else{((_STL::vector<Rva000BB491>*)two)->push_back(event);}
}

// The two "FXEvent" FieldParse parsers that feed the reader above, as the
// clean BF1 ParseFXEvent.cpp donor (575ba2b0) shapes them: reject a null
// block, then pass three interior slots. 0x000C4B8A is the animation-state
// table's entry (beside "Animation", "ParticleSysBone", "LuaEvent"), the
// donor's parseFXEvent: slots +0x78, +0x84 and +0x74. 0x000C4B61 is the
// model-condition-state table's (beside "ParticleSysBone", "OverrideTooltip",
// "RetainSubObjects"): the same three slots at +0xB8, +0xC4 and +0xB4.
void rva000C4B61(INI *ini, void *instance, void *store, const void *userData)
{
 char *state=(char *)instance;
 if(state==0)
  return;
 rva000C48DB(ini,state+0xB8,state+0xC4,state+0xB4);
}

void parseFXEvent(INI *ini, void *instance, void *store, const void *userData)
{
 char *state=(char *)instance;
 if(state==0)
  return;
 rva000C48DB(ini,state+0x78,state+0x84,state+0x74);
}

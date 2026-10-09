// ?rva001E2BB0@Rva001E2BB0@@QAE?AVRva000B3F15@@PBD@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Target1E2BB0..1E2C92; findFXList and named base construction establish
// FX-list clone semantics; the original method spelling is unproven.
#include "ascii_string.h"
struct TargetRef00217D4C {virtual void *destroy(unsigned);int references;};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva000B3F15Payload {public:char opaque00[0x28];TargetRef00217D4C ref28;};
class Rva000B3F15 {public:
 Rva000B3F15():value(0){}
 explicit Rva000B3F15(Rva000B3F15Payload *p):value(p){if(p)++p->ref28.references;}
 Rva000B3F15(const Rva000B3F15 &p):value(p.value){if(value)++value->ref28.references;}
 ~Rva000B3F15(){if(value)ReleaseTreeHintRef00217D4C(&value->ref28);}
 Rva000B3F15 &operator=(const Rva000B3F15 &);
 Rva000B3F15Payload *value;
};
class Rva0005548FNativeList {public:void append(void *const &);};
struct FxNode {FxNode *next,*previous;void *nugget;};
class FXList {public:char opaque00[4];FxNode *head04;};
class FXListStore {public:const FXList *findFXList(const char *)const;};
class Rva001E28B8 {public:Rva001E28B8(const AsciiString &);char opaque00[0x30];};
class Rva001E2BB0:public FXListStore {public:Rva000B3F15 rva001E2BB0(const char *);};
Rva000B3F15 Rva001E2BB0::rva001E2BB0(const char *name){
 const FXList *original=findFXList(name);
 if(!original)return Rva000B3F15();
 Rva000B3F15 result((Rva000B3F15Payload *)new Rva001E28B8(AsciiString(name)));
 for(FxNode *it=original->head04->next;it!=original->head04;it=it->next){
  // Preserve null explicitly in the value argument. This yields retail
  //'s stack copy while keeping the local handle in its native slot.
  ((Rva0005548FNativeList *)((char *)result.value+4))->append(it->nugget?it->nugget:0);
 }
 return result;
}

typedef char FxCloneSizeCheck[sizeof(Rva001E28B8)==0x30 ? 1 : -1];
typedef char FxCloneHandleSizeCheck[sizeof(Rva000B3F15)==4 ? 1 : -1];

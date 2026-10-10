// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /Ireference/shims/moduledata
// stlport
// Fresh target collector at 4EE7ED..4EE8B8, complete203B RET8. The original
// owner and virtual input methods are unknown; the input get/fill slots and
// receiver map+7C/type+D4 are independently witnessed in the native body.
// Existing SpawnArmy ctor/dtor prove the 88-byte temporary. The BF1 575ba2
// SpawnArmy/ThingTemplate count-map sources guide ownership and count storage;
// all target call bindings are owned. The key is the actual template returned
// by the matched 37DC52 ThingFactory lookup, and the mapped word is an integer.
// Use the established TemplateCountKey ABI view and existing insert_unique
// fold from ThingTemplateCountMap.cpp, without claiming an Image payload.
// Typed eight-byte array entries preserve SAR3 pointer distance. A temporary
// pair preserves retail key/result homes and the zero count outside the loop.
#include <map>
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class ThingTemplate;
struct TemplateCountKey {
 const ThingTemplate *pointer;
 __forceinline TemplateCountKey() {}
 __forceinline TemplateCountKey(const ThingTemplate *p):pointer(p) {}
 __forceinline bool operator<(const TemplateCountKey &other)const {return pointer<other.pointer;}
};
class Rva004E3184:public Snapshot {public:
 Rva004E3184(int);virtual ~Rva004E3184();
 virtual void loadPostProcess();virtual const char *GetSnapshotName()const;virtual void xfer(Xfer*);
 char payload[0x54];
};
class Rva004E06FBPtrChase32Field {public:int get()const;};
class Rva00319CED {public:void *rva004E23C1();};
class Rva0040CB2CIndexedField {public:int get(int)const;};
class Rva0037DCA5 {public:void *rva0037DC52();};
class CountInputPrefix {public:virtual void *get();virtual void slot1();virtual void slot2();virtual void slot3();virtual bool fill(void*,Rva004E3184*);};
struct CountInputObjectPrefix {char prefix[4];Rva004E06FBPtrChase32Field *type;};
struct CountArrayEntry {int first;void *second;};
struct CountArrayPrefix {char prefix[0x40];CountArrayEntry *begin;CountArrayEntry *end;};
struct CountEntryPrefix {char prefix[0x90];int count;};
class Rva004EE7EDTemplateCounts {public:void collect(CountInputPrefix *,void *);private:char prefix[0x7C];_STL::map<TemplateCountKey,int> counts;char unused[0xD4-0x7C-12];int type;};
void Rva004EE7EDTemplateCounts::collect(CountInputPrefix *input,void *arg) {
 CountInputObjectPrefix *object=(CountInputObjectPrefix*)input->get();
 if (!object || object->type->get()!=type) return;
 Rva004E3184 temp(0);
 if (input->fill(arg,&temp)) {
  CountArrayPrefix *array=(CountArrayPrefix*)((Rva00319CED*)&temp)->rva004E23C1();
  if (array) {
   int i=array->end-array->begin-1;
   for(;i>=0;--i) {
    CountEntryPrefix *entry=(CountEntryPrefix*)((Rva0040CB2CIndexedField*)array)->get(i);
    TemplateCountKey key((const ThingTemplate *)((Rva0037DCA5*)entry)->rva0037DC52());
    counts.insert(_STL::pair<const TemplateCountKey,int>(key,0)).first->second+=entry->count;
   }
  }
 }
}

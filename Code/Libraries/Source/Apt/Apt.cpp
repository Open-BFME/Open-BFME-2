// cl: /O2 /MD /D_CRTIMP= /EHsc

class Rva006DB160 {public:void *allocBlock(int);};
#include "../../../GameEngine/Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;
#define POOL_ALLOC static void *operator new(unsigned n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);} static void operator delete(void*p,unsigned n){g_pChainBlockAllocator->freeBlock(p,n);}

// WorldBuilder174F1C0 identifies AptSetInternalVariable in Apt.cpp through
// its own debug refcount label. Native6CCA50..6CCAE1 is 145 bytes.
// Retail passes seven interpreter arguments; _AptGetAnimationAtLevel(0)
// is a separate one-argument cdecl call. Both helpers have existing owners.
// The string wrapper owns one data pointer and is destroyed on scope exit.
#include "EAStringC.h"
#include "AptValue.h"
#include "AptCIHClass.h"
class AptString : public AptValue {public:static AptString *Create();
 // AptValue::SetString's body (rowed out of line at 0x006CBF70), which the
 // string-argument call helper 0x006CCB80 inlines.
 void setStringInline(const char *text) {EAStringC temp(text); m_string=temp;}
 EAStringC m_string;};
class BfmeAptValue006DCD20;
#include "AptBasePtrStack.h"
struct AptInitParmsT;
struct AptActionInterpreter {
 void rva006FEAF0(const AptInitParmsT &);
 AptBasePtrStack stack;
 AptValue *getVariable(AptValue *,AptValue *,const EAStringC *,int,int,int);
 bool setVariable(AptValue *,AptValue *,const EAStringC *,AptValue *,int,int,int);
 void callFunction(AptValue *,AptValue *,int);
};
extern AptActionInterpreter g_aptDateInterpreter;
AptCIH *_AptGetAnimationAtLevel(int);
void AptSetInternalVariable(const char *name, const char *text) {
 AptString *value=AptString::Create();
 value->AddRef();
 value->SetString(text);
 EAStringC key(name);
 g_aptDateInterpreter.setVariable(_AptGetAnimationAtLevel(0),0,&key,value,1,1,0);
 value->Release();
}

// Native6CCAF0..6CCB7B; WB174F2E0's AptGetInternalVariable label.
// The two caller arguments are the source key and a mutable output buffer.
// Native6DE870 converts the AptValue to EAStringC and copies into that buffer.
void AptGetInternalVariable(const char *name,char *out) {
 EAStringC key(name);
 AptValue *value=g_aptDateInterpreter.getVariable(_AptGetAnimationAtLevel(0),0,&key,1,1,0);
 value->AddRef();
 value->rva006DE870(out);
 value->Release();
}

// Native6CBC40..6CBC46 is the standalone allocation-hook forwarder called
// by allocator setup6CC380. Keep its call boundary; the next pool's allocation
// is separately inlined in retail. Original function identity is unresolved.
extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int);
__declspec(noinline) void *Rva006CBC40Allocate(unsigned int bytes) {
 return g_bfmeAptAllocAtE17728(bytes);
}

// Native6CC380..6CC498, WB174D320 allocator initialization. Four arguments:
// value-pool size/count followed by chain-pool size/count. Both allocate28B.
// Keep the constructor provider's field layout and alignment. WB174D470
// is the derived two-argument constructor inlined into retail's second new;
// WB174D430 belongs to AptValueGCAllocator.h and forwards its allocation.
// The address-derived class names preserve unresolved original identities.
extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptInitAtE17700,g_bfmeAptBreakOnAssertAtDDC01C;
extern unsigned char g_00E177E0,g_minValueSize,g_00E177E2,g_00E177E8;
extern int g_maxValueSize;
void initValueSizes();
void *Rva006CBC40Allocate(unsigned);
void rva006CBC50(void *,unsigned);
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DAEB0 {
 void *m_table;
 void *m_firstPool;
 int m_unk08;
 unsigned int m_maxSize;
 union {unsigned int m_cfg;struct {unsigned char m_b0,m_b1,m_b2,m_b3;};};
 int m_used,m_count;
public:
 Rva006DAEB0(unsigned,int,int,unsigned,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char);
 static void *operator new(unsigned size) {return Rva006CBC40Allocate(size);}
 static void operator delete(void *ptr,unsigned size) {rva006CBC50(ptr,size);}
};
class Rva006CC380ValuePool : public Rva006DAEB0 {
public:
 // The out-of-line copy is also retail6CBC60..6CBCA6 (RET8), surrounded
 // by padding. WB174D470 proves the same two-argument constructor and
 // nine-argument base initialization; place_bodies found all70 bytes.
 Rva006CC380ValuePool(unsigned size,int count) : Rva006DAEB0(size,count,g_minValueSize,g_maxValueSize,g_00E177E2,1,g_00E177E0,0,g_00E177E8) {}
 static void *operator new(unsigned size) {return g_bfmeAptAllocAtE17728(size);}
 static void operator delete(void *ptr,unsigned size) {rva006CBC50(ptr,size);}
};
class Rva006DB270;class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
void Rva006CC380Initialize(unsigned valueSize,int valueCount,unsigned chainSize,int chainCount) {
 if(g_bfmeAptInitAtE17700) {
  g_bfmeAptAssertAtE17734("bInitialized == 0 && \"Apt Allocator must be initialized before Apt Core!\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x273);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 initValueSizes();
 g_pChainBlockAllocator=(Rva006DB270 *)new Rva006DAEB0(chainSize,chainCount,4,0x100,0,0,0,0,0);
 g_pChainBlockAllocatorF4=(Rva006D2A60 *)new Rva006CC380ValuePool(valueSize,valueCount);
}

// Native6CD7A0..6CD98D:493B, WB174E690 Apt.cpp tick loop. The unsigned
// elapsed accumulator is EAX on entry because this is a file-static helper;
// its real caller6CF040 below preserves that compiler-selected convention.
// WB identifies tickIntervalTimers; its argument is signed (FILD DWORD at
// WB1758339, with no unsigned correction). Other unrowed callees retain
// address names. Pool+30 owns a list whose first node has CIH+54; the
// checked animation state has remainder+30 and movie+0C/interval+24.
// isTickAnimation is forced inline because all three checks are inlined
// in the complete native493B body. No private-register asm is used.
// The complete355B caller stays declared until its separate ledger commit.
extern int g_bfmeAptFlagAtE176D4,g_rva00891FA0Value,g_rva00891FA0Ready;
extern AptActionInterpreter g_aptDateInterpreter;
#include "../../../GameEngine/Include/Common/Rva006DBB30SarDwordField.h"
#include "BfmeAptValue006DCD20.h"
#include "Rva006CD650.h"
struct TickMovie {char pad[0x24];unsigned interval;};
struct TickState {char pad[0xc];TickMovie *movie;char pad10[0x20];unsigned remainder;};
struct TickNode {char pad[0x54];void *cih;};
class Rva006E34D0 {public:void rva006E34D0(int);char pad[0x30];TickNode **nodes;char pad34[8];int count;};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
#include "AptAnimationPoolData.h"
#include "AptDisplayList.h"
class AptLinker {public:void rva006D17F0();void Load(const EAStringC &a,EAStringC b);};
// VA 0x00E176F8 (RVA 0x00A176F8): the Apt linker this unit creates in its
// first tick (g_bfmeAptLinkerAtE176F8 = new Rva008947A0Owner below), so the
// definition lives here, in the assigning unit, and is zero-initialised: four
// units read the object through the name and retail only ever holds the
// pointer the tick stores. Until now nothing defined it, which was the sole
// unresolved name family-2's largest row carried.
AptLinker *g_bfmeAptLinkerAtE176F8;
inline void tickAssert(int good,const char *test,const char *file,int line) {
 if(!good){g_bfmeAptAssertAtE17734(test,file,line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
}
__forceinline bool isTickAnimation(void *p) {
 tickAssert(p!=0,"this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xd3);
 return ((Rva006DBB30SarDwordField *)p)->get()==0x12 && !((BfmeAptValue006DCD20 *)p)->isUndefined();
}
inline void *currentTickCIH(){return (*g_bfmeAptPtrAtE176D0->nodes)->cih;}
inline void tickStackAssert(int line) {
 if(g_aptDateInterpreter.stack.m_nElements) {g_bfmeAptAssertAtE17734("gAptActionInterpreter.stack.GetSize() == 0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
}
static int Rva006CD7A0Tick(unsigned elapsed) {
 int advanced=0;
 if(!isTickAnimation(currentTickCIH()))return advanced;
 TickState *state=(TickState *)((Rva006CD650 *)currentTickCIH())->rva006CD650();
 elapsed+=state->remainder;
 unsigned interval=state->movie->interval;
 while(elapsed>=interval) {
  tickStackAssert(0x369);
  ((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->tickIntervalTimers(interval);
  ((AptDisplayList *)&g_bfmeAptPtrAtE176D0->nodes)->rva006F7A30();
  ((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->rva006E6540();
  ((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->rva006FB910();
  g_bfmeAptLinkerAtE176F8->rva006D17F0();
  tickStackAssert(0x371);
  elapsed-=interval;
  g_rva00891FA0Value+=interval;
  advanced=1;
  if(!isTickAnimation(currentTickCIH()))return advanced;
  if(g_rva00891FA0Ready)break;
 }
 if(isTickAnimation(currentTickCIH())) {
  TickState *state=(TickState *)((Rva006CD650 *)currentTickCIH())->rva006CD650();
  state->remainder=elapsed;
 }
 return advanced;
}
// Native6CC740..6CC7B0: Ghidra-unlisted body between the rowed 6CC600 and
// 6CC7C0. While the diagnostics channel is ready (VA E17708) it sends an
// 8-byte header {current value E176F0, kind 7, 16-bit size} and then the
// caller's buffer through the E17740 record callback; the Apt.cpp 0x33B
// assert (retail text) bounds the size. Owners of those cells are rowed in
// Rva00891FA0Diagnostics.cpp; the header view and name are address-derived.
extern int g_rva00891FA0Ready,g_rva00891FA0Value;
extern "C" void (__cdecl *Rva00891FA0SendRecord)(const void *,unsigned);
struct SavedEventHeader {int value;unsigned short kind,size;};
void Rva006CC740SendSavedEvent(const void *data,unsigned nSize) {
 if(!g_rva00891FA0Ready)return;
 SavedEventHeader header;
 header.value=g_rva00891FA0Value;
 header.kind=7;
 if(!(nSize<=0xFFFF && "Saved Custom Event handler cannot handle a buffer of this size!")) {
  g_bfmeAptAssertAtE17734("nSize <= 0xFFFF && \"Saved Custom Event handler cannot handle a buffer of this size!\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x33B);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 header.size=(unsigned short)nSize;
 Rva00891FA0SendRecord(&header,8);
 Rva00891FA0SendRecord(data,nSize);
}
// Native6CD990..6CDA31: three Ghidra-unlisted level accessors after the tick
// helper. Each looks up _AptGetAnimationAtLevel(level) and reads the
// animation instance that the rowed rva006CD650 returns: +18 when the CIH has
// its +4C resource (else -1), the +0C movie's +08 word (else 0), and bit 25
// of +1C when the level is a defined movie clip (type 0x12, not undefined;
// else -1). Field meanings and original names are unresolved: address names.
struct LevelMovieView {char pad[8];int value08;};
struct LevelInstView {char pad[0xc];LevelMovieView *movie;char pad10[8];int value18;unsigned flags1C;};
int Rva006CD990LevelValue(int level) {
 AptCIH *cih=_AptGetAnimationAtLevel(level);
 if(cih && *(void **)((char *)cih+0x4c))
  return ((LevelInstView *)((Rva006CD650 *)cih)->rva006CD650())->value18;
 return -1;
}
int Rva006CD9C0LevelMovieValue(int level) {
 AptCIH *cih=_AptGetAnimationAtLevel(level);
 if(cih)
  return ((LevelInstView *)((Rva006CD650 *)cih)->rva006CD650())->movie->value08;
 return 0;
}
int Rva006CD9F0LevelFlag(int level) {
 AptCIH *cih=_AptGetAnimationAtLevel(level);
 if(cih && ((Rva006DBB30SarDwordField *)cih)->get()==0x12 && !((BfmeAptValue006DCD20 *)cih)->isUndefined())
  return (((LevelInstView *)((Rva006CD650 *)cih)->rva006CD650())->flags1C>>25)&1;
 return -1;
}
class BfmeRefVGO {unsigned *value;public:BfmeRefVGO():value(0){} ~BfmeRefVGO();};
class Rva004A9DF3Element : public BfmeRefVGO {public:Rva004A9DF3Element(){} ~Rva004A9DF3Element();};
class Rva00893030Manager {int head;public:Rva00893030Manager():head(0){} POOL_ALLOC void rva006CDE50(Rva004A9DF3Element *,int);};
extern Rva00893030Manager *g_rva00893030Manager;
class AptValueVector {int capacity,count;AptValue **values;int high;public:AptValueVector(int);void ReleaseValues();POOL_ALLOC
 int GetNumValues() const;
 __declspec(dllimport) __declspec(nothrow) __forceinline AptValue *operator[](int iPos) const {
  if(!(iPos>=0 && iPos<count)){g_bfmeAptAssertAtE17734("iPos >= 0 && iPos < mCurrentNum","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptValue/AptValueVector.h",0x39);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
  return values[iPos];
 }
};
extern AptValueVector *g_releaseVectorAtE17710;
void Rva006CEC90Tick();
void d_00891fa0();
void Rva006E6E20Collect();





// Native6CEC90..6CF02B RET:923 code bytes; four-entry jump table at6CF030
// maps cases0/1 to6CED8D,2 to6CEDA9,3 to6CEE24. WB174E830 Apt.cpp912..986.
// WB174EE80/174EEA0 prove readiness states4/2; WB1750C60 stores the iterator
// cursor/begin/end pointers. Its compatibility and dereference checks call
// WB1750B80, an empty5B function even in debug. Preserve those expressions:
// removing them changes compiler loop/register allocation despite no runtime
// work. WB1750B30/1750B90 supply the exact diagnostic strings.
// Native6CF956..6CF9A3 allocates28B: count/capacity/data and two8B entries;
// checkpoint6CEB43 calls EAStringC::IsEqualTo on each entry and state is+4.
// Existing playback-word providers are retained; the pointer reference views
// reflect native cursor arithmetic and do not introduce duplicate storage.
#define tickAssert(good,test,file,line) do {if(!(good)){g_bfmeAptAssertAtE17734(test,file,line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}} while(0)
#include <string.h>
#include <stdio.h>
struct Rva00891FA0Record {int value,kind;};
extern "C" void (__cdecl *Rva00891FA0SendRecord)(Rva00891FA0Record *,int);
extern "C" void (__cdecl *Rva00891FA0SendText)(const char *);
void Rva006CC110Log(int,const char *,...);
extern unsigned g_rva00A176D8,g_rva00A176DC,g_rva00A176E4;
// Native6CF96D/6CF972 use the existing AptValueNameEntry destructor/constructor.
// Its shared EAStringC+0/int+4 layout is also used by the checkpoint lookup.
class AptValueNameEntry {public:AptValueNameEntry();~AptValueNameEntry();EAStringC m_name;int m_value;};
typedef AptValueNameEntry PlaybackItem;
inline void iteratorCheck(bool,const char *){}
class PlaybackIterator {
 PlaybackItem *cur,*first,*last;
public:
 PlaybackIterator(PlaybackItem *playbackItem,PlaybackItem *f,PlaybackItem *l):cur(playbackItem),first(f),last(l){}
 PlaybackIterator &operator++(){++cur;return *this;}
 PlaybackItem &operator*(){iteratorCheck(cur>=first && cur<last,"Trying to dereference an invalid iterator");return *cur;}
 bool operator!=(const PlaybackIterator &other){iteratorCheck(first==other.first && last==other.last,"Iterators are not in same range");return cur!=other.cur;}
};
class PlaybackRange {
 PlaybackItem *first,*last;
public:
 PlaybackRange(PlaybackItem *playbackItem,PlaybackItem *l):first(playbackItem),last(l){}
 PlaybackIterator begin(){return PlaybackIterator(first,first,last);}
 PlaybackIterator end(){return PlaybackIterator(last,first,last);}
};
// The checkpoint container is the rowed Rva006CE660Vec (same 28-byte
// layout); its 0x006CEB10 member is called through that view.
#include "Rva006CE660Vec.h"
class Rva006CEB10Playback {
public:
 int size,capacity;PlaybackItem *items;PlaybackItem inlineItems[2];
 Rva006CEB10Playback():size(0),capacity(0),items(inlineItems){} POOL_ALLOC
 PlaybackIterator begin(){return PlaybackRange(items,items+size).begin();}
 PlaybackIterator end(){return PlaybackRange(items,items+size).end();}
 __forceinline bool readyFor(int a,int b) {
  for(PlaybackIterator it=begin();it!=end();++it)
   if((*it).m_value!=a && (*it).m_value!=b)return false;
  return true;
 }
 __forceinline bool ready(){return readyFor(4,2);}
};
// Native6CF9A3 stores the new28B checkpoint container in this four-byte
// cell. Retail E176EC initially contains00000000; no existing owner found.
Rva006CEB10Playback *g_aptPlaybackCheckpoints=0;
#define PLAYCUR reinterpret_cast<char *&>(g_rva00A176D8)
#define PLAYBASE reinterpret_cast<char *&>(g_bfmeAptFlagAtE176D4)
void Rva006CEC90Tick() {
 unsigned target=g_rva00A176E4+1;
 while(PLAYBASE) {
  tickAssert(g_rva00A176E4<=target,"gSIPlayback.nCurTick <= nTargetTime","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x390);
  if(g_rva00A176E4==target)break;
  if(g_aptPlaybackCheckpoints->ready())while(true) {
   unsigned tick=*(unsigned *)PLAYCUR;
   if(tick>g_rva00A176E4)break;
   tickAssert(tick==g_rva00A176E4,"nTick == gSIPlayback.nCurTick","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x39a);
   PLAYCUR+=4;
   switch(*(unsigned char *)PLAYCUR & 3) {
    case 0:case 1:{unsigned input=*(unsigned *)PLAYCUR;PLAYCUR+=4;g_bfmeAptPtrAtE176D0->rva006E34D0(input);break;}
    case 2:{
     tickAssert((*(unsigned char *)PLAYCUR & 3)==2,"INPUT_IS_CHECKPOINT(&*gSIPlayback.pCurSavedInput)","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x3ab);
     ++PLAYCUR;const char *name=PLAYCUR;PLAYCUR+=strlen(name)+1;
     ((Rva006CE660Vec *)g_aptPlaybackCheckpoints)->rva006CEB10(EAStringC(name));break;
    }
    case 3:{
     ++PLAYCUR;
     if(!g_rva00891FA0Ready){char text[16];sprintf(text,"%06d",g_rva00A176E4);Rva00891FA0SendText(text);}break;
    }
    default:tickAssert(0,"false && \"Unknown Saved Input Type Reached!!!\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x3d6);break;
   }
   tickAssert(PLAYCUR-PLAYBASE<=(int)g_rva00A176DC,"(gSIPlayback.pCurSavedInput - gSIPlayback.pSavedInputs) <= gSIPlayback.nInputFileSize","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x3da);
  }
  if(PLAYCUR-PLAYBASE>=(int)g_rva00A176DC) {
   Rva006CC110Log(0,"Playback of inputs completed.\n");PLAYBASE=0;PLAYCUR=0;
   if(g_rva00891FA0Ready){Rva006CC110Log(0,"  Turning off saved inputs too.\n");g_rva00891FA0Ready=0;}break;
  }
  void *p;
  if(g_aptPlaybackCheckpoints->ready() && (p=currentTickCIH())!=0 && ((Rva006DBB30SarDwordField *)p)->get()==0x12 && !((BfmeAptValue006DCD20 *)p)->isUndefined()) {
   if(Rva006CD7A0Tick(1) && g_rva00891FA0Ready) {
    char text[16];Rva00891FA0Record record;
    sprintf(text,"%06d",g_rva00891FA0Value);Rva00891FA0SendText(text);
    record.value=g_rva00891FA0Value;record.kind=3;Rva00891FA0SendRecord(&record,5);
   }
   ++g_rva00A176E4;
  }else{g_bfmeAptLinkerAtE176F8->rva006D17F0();break;}
 }
}






#undef tickAssert
#undef PLAYCUR
#undef PLAYBASE

// Native6CF369 installs6CC150 in the size-aware free callback atE17730.
// DogmaPool::freeBlock6DB2C3..6DB2CB passes size then pointer and cleans8B.
// WB174CEA0 forwards only the pointer to the unsized free callback.
// This resolves the earlier lack of ABI evidence for the ignored second arg.
// NativeE1772C is an unowned four-byte zero-filled writable callback slot.
void (__cdecl *g_aptFreeCallback)(void *) = 0;
void Rva006CC150FreeWithSize(void *block,unsigned int) {
 g_aptFreeCallback(block);
}

// Native6CF230..6CFA2E is the complete2046B initializer; WB174C390 gives
// Apt.cpp357..438. The existing89B parameter constructor supplies14 ints and
// two flags. Original initializer/type names remain unresolved. Its optional
// vector cellE17714, flagsE1771C/1D and new callback cells below are native
// zero-filled storage. Callback assertion strings establish their roles;
// opaque slots do not claim callable signatures that this body never uses.
struct Rva00222343 {Rva00222343();int fields[14];bool flag38,flag39;};
#define CHECK(e,s,l) do{if(!(e)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}}while(0)
extern void *g_eaStringAtE177D4Storage;
unsigned char g_00E1771C=0;
unsigned char g_aptInitFlag39=0;
// VA 0x00E17718 (zero-filled): the Apt emit/transform flags between the
// optional vector cellE17714 and flag38 atE1771C. BFME1 owns the same image
// slot as g_bfmeExtra1282Flags at VA 0x01337818 -- the whole Apt global run
// matches BFME2's at a constant +0x520100 offset (0x01337708->E17708
// g_rva00891FA0Ready, 0x01337810->E17710 GcRoots, 0x0133781C->E1771C flag38,
// 0x0133781D->E1771D flag39, 0x01337828/2C->E17728/2C alloc/free slots) --
// and BFME1's node walk picks the transform callback over the walk callback
// from bit 2 and skips an emit from bit 1. This target's 0x00224296
// initializer sets bit 1 the same way BFME1's WindowManager::init does and
// 0x006F7720 tests bit 2 to choose its pool-flush callback. Retail holds four
// loader-zero bytes here.
unsigned int g_bfmeExtra1282Flags=0;
extern void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void*,unsigned);
extern void (__cdecl *g_aptBackgroundCallback)(int);
extern "C" void (__cdecl *g_bfmeAptLogAtE1773C)(const char*,const char*);
extern void (__cdecl *g_bfmeAptCommandAtE17758)(const char*,const char*);
extern AptValue *(__cdecl *g_bfmeAptLoadVariablesAtE1775C)(const char*);
extern void (__cdecl *g_bfmeAptSetExternAtE17764)(const char*,const char*);
extern AptValue *(__cdecl *g_bfmeAptGetExternAtE17768)(const char*);
// VA 0x00E17774 (zero-filled: installed at run time). This is the Apt host's
// function-table slot the CHECK block below names "gAptFuncs.pfnDeallocateString";
// the string allocate/free pair either side of it already live at VA 0x00E17768
// and VA 0x00E17784. Four units call through this slot, so it is defined once here
// in the unit that carries the table's CHECK block.
void (__cdecl *g_00E17774)(void*,int) = 0;
extern void (__cdecl *g_bfmeAptFreeAtE17784)(void*,int);
extern void (__cdecl *g_AptBindTexture)(void*,int,void*);
struct AptMatrix;
extern void (__cdecl *g_bfmeAptMatrixCallbackAtE177A0)(AptMatrix*);
extern "C" void (__cdecl *bfmeNotify1209Callback)(void*);
void DX8_Assert();
void Rva006D37E0Set(int);
void Rva0070B670Initialize(int);
AptValueVector *g_aptOptionalValueVector=0;
void Rva006DF470Initialize();
// Preserve the existing constructor provider's full24B/alignment4 layout.
class Rva008947A0Elem {public:Rva008947A0Elem();~Rva008947A0Elem();int m_data;};
class Rva008947A0Head {public:Rva008947A0Head();~Rva008947A0Head();int m_a;};
class Rva008947A0Owner {
public:Rva008947A0Owner();POOL_ALLOC
 Rva008947A0Head m_head;int m_b,m_c;Rva008947A0Elem *m_items;Rva008947A0Elem m_array[2];
};
// Opaque B4-byte root allocation; only size/alignment and constructor ABI
// are modeled here. Its native constructor returns this with RET4.
class Rva006E6060Root {union{unsigned alignment;char bytes[0xb4];};public:Rva006E6060Root(const Rva00222343*);POOL_ALLOC};
class AptMath {public:static void ClipStackInit(unsigned);};
void *g_aptLoadAnimationSlot=0; // Native00E17748; callback ABI unmodeled.
void *g_aptFreeConstantTableSlot=0; // Native00E17750; callback ABI unmodeled.
void *g_aptFreeAnimationSlot=0; // Native00E1774C; callback ABI unmodeled.
// Native00E17754: the gAptFuncs slot after pfnFreeConstantTable that init does
// not check; Bfme5ThirtyFour.cpp (6D1A54) calls it with two strings when set.
void (__cdecl *g_rva00A17754)(const char *, const char *)=0;
void *g_aptAllocateStringSlot=0; // Native00E17770; callback ABI unmodeled.
void *g_aptDrawStringSlot=0; // Native00E17778; callback ABI unmodeled.
void *g_aptLoadSoundSlot=0; // Native00E1777C; callback ABI unmodeled.
void *g_aptFreeSoundSlot=0; // Native00E17780; callback ABI unmodeled.
void *g_aptStartSoundStreamSlot=0; // Native00E17788; callback ABI unmodeled.
void *g_aptLoadTextureSlot=0; // Native00E1778C; callback ABI unmodeled.
void *g_aptFreeTextureSlot=0; // Native00E17790; callback ABI unmodeled.
void *g_aptLoadRenderingUnitSlot=0; // Native00E17798; callback ABI unmodeled.
void *g_aptFreeRenderingUnitSlot=0; // Native00E1779C; callback ABI unmodeled.
void *g_aptDrawRenderingUnitSlot=0; // Native00E177A8; callback ABI unmodeled.
void *g_aptCustomControlRenderSlot=0; // Native00E177AC; callback ABI unmodeled.
void *g_aptGetStageHeightSlot=0; // Native00E177C8; callback ABI unmodeled.
void *g_aptGetStageWidthSlot=0; // Native00E177CC; callback ABI unmodeled.
void Rva006CF230Initialize(const Rva00222343 *input) {
 CHECK(!g_bfmeAptInitAtE17700,"!bInitialized",357);
 Rva00222343 defaults;
 const Rva00222343 *parms=input?input:&defaults;
 CHECK(parms->fields[12]>4,"(initParms.iRegArraySize > 4) && \"Register Array Size must be at least 4. Flash regularly uses these\"",362);
 if(!(*reinterpret_cast<EAStringC *>(&g_eaStringAtE177D4Storage)).rva006CD4A0())(*reinterpret_cast<EAStringC *>(&g_eaStringAtE177D4Storage)).rva006D3C60();
 g_00E1771C=parms->flag38;g_aptInitFlag39=parms->flag39;
 CHECK(g_bfmeAptAssertAtE17734,"gAptFuncs.pfnAssertFail",375);
 CHECK(g_bfmeAptAllocAtE17728,"gAptFuncs.pfnMemAlloc",376);
 CHECK(g_aptFreeCallback,"gAptFuncs.pfnMemFree",377);
 if(!g_bfmeAptFreeSizeAtE17730)g_bfmeAptFreeSizeAtE17730=Rva006CC150FreeWithSize;
 CHECK(g_aptBackgroundCallback,"gAptFuncs.pfnSetBackgroundColour",382);
 CHECK(g_bfmeAptLogAtE1773C,"gAptFuncs.pfnDebugPrint",383);
 CHECK(Rva00891FA0SendRecord,"gAptFuncs.pfnDebugAddSavedInput",384);
 CHECK(Rva00891FA0SendText,"gAptFuncs.pfnDebugSetScreenGrabPending",385);
 CHECK(g_aptLoadAnimationSlot,"gAptFuncs.pfnLoadAnimation",386);
 CHECK(g_aptFreeConstantTableSlot,"gAptFuncs.pfnFreeConstantTable",387);
 CHECK(g_aptFreeAnimationSlot,"gAptFuncs.pfnFreeAnimation",388);
 CHECK(g_bfmeAptCommandAtE17758,"gAptFuncs.pfnCommand",389);
 CHECK(g_bfmeAptLoadVariablesAtE1775C,"gAptFuncs.pfnLoadVariables",390);
 CHECK(g_bfmeAptSetExternAtE17764,"gAptFuncs.pfnSetExternVariable",391);
 CHECK(g_bfmeAptGetExternAtE17768,"gAptFuncs.pfnGetExternVariable",392);
 CHECK(g_aptAllocateStringSlot,"gAptFuncs.pfnAllocateString",393);
 CHECK(g_00E17774,"gAptFuncs.pfnDeallocateString",394);
 CHECK(g_aptDrawStringSlot,"gAptFuncs.pfnDrawString",395);
 CHECK(g_aptLoadSoundSlot,"gAptFuncs.pfnLoadSound",397);
 CHECK(g_aptFreeSoundSlot,"gAptFuncs.pfnFreeSound",398);
 CHECK(g_bfmeAptFreeAtE17784,"gAptFuncs.pfnStartSound",399);
 CHECK(g_aptStartSoundStreamSlot,"gAptFuncs.pfnStartSoundStream",400);
 CHECK(g_aptLoadTextureSlot,"gAptFuncs.pfnLoadTexture",402);
 CHECK(g_aptFreeTextureSlot,"gAptFuncs.pfnFreeTexture",403);
 CHECK(g_AptBindTexture,"gAptFuncs.pfnBindTexture",404);
 CHECK(g_bfmeAptMatrixCallbackAtE177A0,"gAptFuncs.pfnSetVertexMatrix",405);
 CHECK(bfmeNotify1209Callback,"gAptFuncs.pfnSetColourTransform",406);
 CHECK(g_aptLoadRenderingUnitSlot,"gAptFuncs.pfnLoadRenderingUnit",407);
 CHECK(g_aptFreeRenderingUnitSlot,"gAptFuncs.pfnFreeRenderingUnit",408);
 CHECK(g_aptDrawRenderingUnitSlot,"gAptFuncs.pfnDrawRenderingUnit",409);
 CHECK(g_aptCustomControlRenderSlot,"gAptFuncs.pfnCustomControlRender",410);
 CHECK(g_aptGetStageHeightSlot,"gAptFuncs.pfnGetStageHeight",411);
 CHECK(g_aptGetStageWidthSlot,"gAptFuncs.pfnGetStageWidth",412);
 DX8_Assert();
 Rva006D37E0Set((int)&g_bfmeAptAllocAtE17728);
 Rva0070B670Initialize(parms->fields[11]);
 g_releaseVectorAtE17710=new AptValueVector(parms->fields[10]);
 if(!parms->fields[13])g_aptOptionalValueVector=0;
 else g_aptOptionalValueVector=new AptValueVector(parms->fields[13]);
 Rva006DF470Initialize();
 g_aptDateInterpreter.rva006FEAF0(*(const AptInitParmsT*)parms);
 g_rva00893030Manager=new Rva00893030Manager;
 g_bfmeAptLinkerAtE176F8=(AptLinker*)new Rva008947A0Owner;
 g_aptPlaybackCheckpoints=new Rva006CEB10Playback;
 CHECK(g_bfmeAptPtrAtE176D0==0,"gpPool == 0",438);
 g_bfmeAptPtrAtE176D0=(Rva006E34D0*)new Rva006E6060Root(parms);
 AptMath::ClipStackInit(0x80);
 g_bfmeAptInitAtE17700=1;
}
#undef CHECK
#undef POOL_ALLOC

// ?rva006cc940@@YAXXZ @0x006CC940 5B: tail jump to the matched Apt shutdown
// tail 0x006CC880; retail calls it from the rowed 0x0022244D.
void rva006cc880();
void rva006cc940()
{
 rva006cc880();
}

// ?_AptValidate@@YA_NXZ @0x001826C0 3B: the interpreter validation hook,
// which returns true in this build; /OPT:ICF folded it onto the STLport
// codecvt do_always_noconv body there. Sole retail caller: the queued-action
// run 0x006E6540 (AptAnimation.cpp assert 0x3AC "_AptValidate()"). Its
// WorldBuilder copy 0x174DF60 (7B return-true) lies between Apt.cpp bodies.
bool _AptValidate()
{
 return true;
}

// ?Rva006CC600@@YAXPBDPAD@Z @0x006CC600: Apt.cpp's import-target guard
// (assert file/lines 802/805 name it): refuse a target suffix of "#import",
// then forward (path,target) to the linker Load at 0x006D1F80.
// The temporary inequality and literal conjunction retain native EH tracking. The byte at
// 0x00E176FC is the ledger-owned g_aptBackgroundSet (AptMovieFrameControls),
// cleared here.
extern bool g_aptBackgroundSet;


// Native6CC530..6CC5F0: level lookup walks the existing pool's +30 list;
// on a miss it constructs a96B type19 CIH, roots it, and inserts by level.
// Original one-int ABI is independently named by retail callers and the pin.
// Throwing-new cleanup7A8080 calls the native value-pool free twin6F12F0:
// both normal allocation and exceptional release use the existingF4 owner.
// Native allocation-failure cleanup frees directly through the F4 pool.
// Keep its complete22B implementation consistent with Rva006F6A50Cluster.
class Rva006CBDE0 {
public:
 void *vptr;unsigned flags;EAStringC name;
 int fields0c[15];AptValue *value;void *displayList;
 Rva006CBDE0 *prev,*next;unsigned level,extra;
 Rva006CBDE0(int,void*,AptValue*);
 static void *operator new(unsigned n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void *p,unsigned n){g_pChainBlockAllocatorF4->freeBlock(p,(int)n);}
};
class BfmeQuery1279 {public:Rva006CBDE0 *root;void rva006F6FB0(int,AptCIH*);};
AptCIH *_AptGetAnimationAtLevel(int key) {
 Rva006E34D0 *apt=g_bfmeAptPtrAtE176D0;
 if(apt && apt->nodes) {
  BfmeQuery1279 *query=(BfmeQuery1279*)apt->nodes;
  Rva006CBDE0 *cur=query->root;
  if(cur) do {
   if((int)(cur->level<<15)>>15==key) return (AptCIH*)cur;
   cur=cur->next;
  } while(cur);
  Rva006CBDE0 *p=new Rva006CBDE0(0x13,0,0);
  ((BfmeAptValue006DCD20*)p)->setGCRootCount(1);
  ((BfmeQuery1279*)g_bfmeAptPtrAtE176D0->nodes)->rva006F6FB0(key,(AptCIH*)p);
  return (AptCIH*)p;
 }
 return 0;
}

// Native 6CDF60..6CE07C: allocator shutdown with no arguments; WB174D4C0
// Apt.cpp lines 666..691. Both pool allocations are 28B. WB's two deleting
// helpers receive flags 1; inline delete views retain the native operand copy.
class DOGMA_PoolManager {public:unsigned GetTotalBytesUsed();};
class Rva006DAFA0Walk {public:void rva006DAFA0();};
void rva006CBC50(void *,unsigned);
class Rva006CD6C0SizedDeleting {
public:
 __declspec(noinline) ~Rva006CD6C0SizedDeleting();
 static void operator delete(void *storage,unsigned size) {g_bfmeAptFreeSizeAtE17730(storage,size);}
 unsigned m_fields[7];
};
struct ShutdownPoolStats {char pad[0x14];int allocated,freeCount;};
class ShutdownChainPoolDelete {
 char bytes[28];
public:
 ~ShutdownChainPoolDelete(){((Rva006DAFA0Walk *)this)->rva006DAFA0();}
 static void operator delete(void *p,unsigned n){rva006CBC50(p,n);}
};
class ShutdownValuePoolDelete {
 char bytes[28];
public:
 ~ShutdownValuePoolDelete(){((Rva006CD6C0SizedDeleting *)this)->Rva006CD6C0SizedDeleting::~Rva006CD6C0SizedDeleting();}
 static void operator delete(void *p,unsigned n){g_bfmeAptFreeSizeAtE17730(p,n);}
};
void Rva006CDF60() {
 if(g_bfmeAptInitAtE17700) {
  g_bfmeAptAssertAtE17734("bInitialized == 0 && \"Apt Allocator must be shutdown after Apt Core!\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x29a);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 Rva006CC110Log(0,"--+-Apt NonGC Items Pool Shutdown\n");
 Rva006CC110Log(0,"  +- Items In Free Lists:0x%X\n",((ShutdownPoolStats *)g_pChainBlockAllocator)->freeCount);
 if(((ShutdownPoolStats *)g_pChainBlockAllocator)->allocated)
  Rva006CC110Log(0,"  +- Items Allocated    :0x%X   <-- !Warning! Shutting down with items allocated!!!\n",((ShutdownPoolStats *)g_pChainBlockAllocator)->allocated);
 Rva006CC110Log(0,"  +- Total Bytes Used   :0x%X\n",((DOGMA_PoolManager *)g_pChainBlockAllocator)->GetTotalBytesUsed());
 Rva006CC110Log(0,"--+-Apt Garbage Collected Items Pool Shutdown\n");
 Rva006CC110Log(0,"  +- Items In Free Lists:0x%X\n",((ShutdownPoolStats *)g_pChainBlockAllocatorF4)->freeCount);
 if(((ShutdownPoolStats *)g_pChainBlockAllocatorF4)->allocated)
  Rva006CC110Log(0,"  +- Items Allocated    :0x%X   <-- !Warning! Shutting down with items allocated!!!\n",((ShutdownPoolStats *)g_pChainBlockAllocatorF4)->allocated);
 Rva006CC110Log(0,"  +- Total Bytes Used   :0x%X\n",((DOGMA_PoolManager *)g_pChainBlockAllocatorF4)->GetTotalBytesUsed());
 delete (ShutdownChainPoolDelete *)g_pChainBlockAllocator;
 delete (ShutdownValuePoolDelete *)g_pChainBlockAllocatorF4;
}

// Native6CC4C0..6CC4C5 is the complete pool-destructor forwarding wrapper.
// Its real caller above retains the native call boundary.
Rva006CD6C0SizedDeleting::~Rva006CD6C0SizedDeleting() {
 ((Rva006DAFA0Walk *)this)->rva006DAFA0();
}

// The break is EA's inline-asm int 3; __debugbreak() moves 0x006CCB80's stack homes.
#define GAPCHECK(e,s,l) do{if(!(e)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}}while(0)
// Native6CD0B0..6CD0F4: Ghidra-unlisted body after the numeric parser. Asserts
// bInitialized (Apt.cpp 0x65A, retail text) and, unless the E176D4 flag is set,
// clears the +3C count of the E176D0 animation pool. Address name.
void Rva006CD0B0ResetPoolCount() {
 if (!g_bfmeAptInitAtE17700) {
  g_bfmeAptAssertAtE17734("bInitialized", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp", 0x65A);
  if (g_bfmeAptBreakOnAssertAtDDC01C)
   __debugbreak();
 }
 if(!g_bfmeAptFlagAtE176D4 && g_bfmeAptPtrAtE176D0)
  g_bfmeAptPtrAtE176D0->count=0;
}

// Native6CD350..6CD38A: asserts pMCInfo (Apt.cpp 0x7C0) and applies it to the
// E176D0 pool's +30 child list through the rowed rva006F7AF0. Address name.
class Rva006F7AC0List {public:bool rva006F7AC0();void rva006F7AF0(int);};
void Rva006CD350ApplyChild(void *pMCInfo) {
 if (!pMCInfo) {
  g_bfmeAptAssertAtE17734("pMCInfo", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp", 0x7C0);
  if (g_bfmeAptBreakOnAssertAtDDC01C)
   __debugbreak();
 }
 ((Rva006F7AC0List *)g_bfmeAptPtrAtE176D0->nodes)->rva006F7AF0((int)pMCInfo);
}

// Native6CD3A0..6CD3BD zeroes an eight-dword record in retail's store order
// (+0,+4,+10,+14,+8,+C,+18,+1C). Record meaning unresolved: address names.
struct Rva006CD3A0Record {int a0,a4,a8,aC,a10,a14,a18,a1C;};
void Rva006CD3A0Clear(Rva006CD3A0Record *r) {
 r->a0=0;r->a4=0;r->a10=0;r->a14=0;r->a8=0;r->aC=0;r->a18=0;r->a1C=0;
}

// Native6CD120..6CD1E7: Ghidra-unlisted registration of a global extension
// object. Asserts pExtObject (Apt.cpp 0x685, retail texts), builds its name
// from virtual slot 15, calls slot 16, asserts the global extension table
// (E18360) does not already hold that name (0x68C) and adds the object under
// it. Table calls are the rowed rva0070A5C0 lookup and rva006FBB90 add; the
// extension object view and this function's name are address-derived.
class Rva006CD120ExtObject {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual const char *name();virtual void registered();};
class BfmeN1034;
#include "Rva0070A5C0.h"
class Rva8D0D80String;class Rva8D0D80Value;
#include "Rva8D0D80Result.h"
extern AptValue *g_shutdownAtE18360;
void Rva006CD120AddGlobalExtension(Rva006CD120ExtObject *pExtObject) {
 if (!pExtObject) {
  g_bfmeAptAssertAtE17734("pExtObject != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp", 0x685);
  if (g_bfmeAptBreakOnAssertAtDDC01C)
   __debugbreak();
 }
 EAStringC sObjName(pExtObject->name());
 pExtObject->registered();
 if (((Rva0070A5C0 *)g_shutdownAtE18360)->rva0070A5C0((int)&sObjName) != 0) {
  g_bfmeAptAssertAtE17734("NULL == gpGlobalExtensionObject->Lookup(&sObjName)", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp", 0x68C);
  if (g_bfmeAptBreakOnAssertAtDDC01C)
   __debugbreak();
 }
 ((Rva8D0D80Result *)g_shutdownAtE18360)->rva006FBB90((Rva8D0D80String *)&sObjName,(Rva8D0D80Value *)pExtObject);
}

// Native6CCF30..6CD00D: Ghidra-unlisted focus-by-path helper. A null path
// clears the E176D0 pool's slot through the rowed setter 0x006E3700 and
// succeeds; otherwise the path is resolved like AptGetInternalVariable above
// (rowed getVariable from level 0) and a CIH result is stored through the
// same setter, else it fails. Address-derived name.
class Rva006E3700DwordSlot {public:void set(int);};
bool Rva006CCF30SetFocusPath(const char *path) {
 if(!path) {
  ((Rva006E3700DwordSlot *)g_bfmeAptPtrAtE176D0)->set((int)path);
  return true;
 }
 EAStringC key(path);
 AptValue *value=g_aptDateInterpreter.getVariable(_AptGetAnimationAtLevel(0),0,&key,1,1,0);
 if(!value)
  return false;
 if(!value->isCIH(false))
  return false;
 ((Rva006E3700DwordSlot *)g_bfmeAptPtrAtE176D0)->set((int)value->c_cih(false));
 return true;
}

// Native6CCD90..6CCF20: Ghidra-unlisted host-side script call. Resolves the
// target (a path from level 0 through the rowed getVariable, or level 0
// itself), pushes the nArgs variadic AptValue arguments last-first onto the
// interpreter stack, asserts pContext (Apt.cpp 0x53C, retail texts), looks up
// the named function on the target, runs it through the rowed callFunction
// inside the rowed static-data push/pop, copies the stack-top result into the
// optional C buffer (rowed rva006DE870) and pops it. Address-derived name.
#include <stdarg.h>
// Same TU alias of the rowed AptScriptFunctionBase::PushStaticData that
// AptActionInterpreterConstantHandlers.cpp binds (the class has a shared header).
void *AptPushStaticData();
void rva007097B0(void *);
// Native6CCB80..6CCD81, WB174F390: the string-argument twin of the call below.
// Each variadic C string goes into a fresh AptString before the same push and call.
void Rva006CCB80CallFunction(const char *function,char *result,const char *target,int nNumParams,...) {
 GAPCHECK(nNumParams>=0 && nNumParams<32,"nNumParams >= 0 && nNumParams < APT_ARRAYSIZE(apStrings)",0x4E8);
 AptValue *context;
 if(target) {
  EAStringC path(target);
  context=g_aptDateInterpreter.getVariable(_AptGetAnimationAtLevel(0),0,&path,1,1,0);
 } else {
  context=_AptGetAnimationAtLevel(0);
 }
 AptString *apStrings[32];
 va_list list;
 va_start(list,nNumParams);
 for(int i=0;i<nNumParams;i++) {
  apStrings[i]=AptString::Create();
  apStrings[i]->setStringInline(va_arg(list,const char *));
 }
 va_end(list);
 for(int j=nNumParams-1;j>=0;j--)
  g_aptDateInterpreter.stack.Push((BfmeAptValue006DCD20 *)apStrings[j]);
 GAPCHECK(context,"pContext",0x504);
 EAStringC name(function);
 AptValue *value=g_aptDateInterpreter.getVariable(context,0,&name,1,1,0);
 void *saved=AptPushStaticData();
 g_aptDateInterpreter.callFunction(context,value,nNumParams);
 rva007097B0(saved);
 if(result) {
  AptValue *top=(AptValue *)g_aptDateInterpreter.stack.At(0);
  top->rva006DE870(result);
 }
 g_aptDateInterpreter.stack.rva006FE920();
}

void Rva006CCD90CallFunction(const char *function,char *result,const char *target,int nArgs,...) {
 AptValue *context;
 if(target) {
  EAStringC path(target);
  context=g_aptDateInterpreter.getVariable(_AptGetAnimationAtLevel(0),0,&path,1,1,0);
 } else {
  context=_AptGetAnimationAtLevel(0);
 }
 AptValue *args[32];
 va_list list;
 va_start(list,nArgs);
 for(int i=0;i<nArgs;i++)
  args[i]=va_arg(list,AptValue *);
 va_end(list);
 for(int j=nArgs-1;j>=0;j--)
  g_aptDateInterpreter.stack.Push((BfmeAptValue006DCD20 *)args[j]);
 GAPCHECK(context,"pContext",0x53C);
 EAStringC name(function);
 AptValue *value=g_aptDateInterpreter.getVariable(context,0,&name,1,1,0);
 void *saved=AptPushStaticData();
 g_aptDateInterpreter.callFunction(context,value,nArgs);
 rva007097B0(saved);
 if(result) {
  AptValue *top=(AptValue *)g_aptDateInterpreter.stack.At(0);
  top->rva006DE870(result);
 }
 g_aptDateInterpreter.stack.rva006FE920();
}

// Retail 0x006CDB70 (46 B): constructor of an owner with a two-handle inline
// buffer. It zeroes the count and used fields, points the items pointer at
// the inline storage at +0xC, and builds the two Rva004A9DF3Element handles
// there through the EH vector constructor iterator (constructor 0x00013260,
// destructor 0x000A9DF3), as the 96-handle table above does. Owner and field
// names are address-derived.
// Native6CDA40..6CDB02: Ghidra-unlisted zombie-vector report over the E17714
// optional value vector (owned above): count line, then for each entry from
// the last down its CIH name, the instance resource file and size (+34 ->
// +08/+04) and the +5C low word, plus the coreforge advisory line, all through
// the rowed log 0x006CC110. Retail text; address name. The reload of the
// global into a local inside the loop is what retail's per-iteration load of
// E17714 at the same spot compiles as; a direct ternary read left an extra
// branch (+2B).
struct ZombieResource {int pad;unsigned size;EAStringC file;};
struct ZombieInst {char pad[0x34];ZombieResource *resource;};
struct ZombieCIH {char pad[8];EAStringC name;char pad0C[0x50];unsigned refs;};
void Rva006CDA40ReportZombies() {
 if(!g_aptOptionalValueVector)return;
 int i=g_aptOptionalValueVector->GetNumValues()-1;
 Rva006CC110Log(4,"ZOMBIE VECTOR HAS %d ITEMS IN IT\n",i+1);
 for(;i>=0;--i) { AptValueVector *vec=g_aptOptionalValueVector;
  ZombieCIH *cih=(ZombieCIH *)((BfmeAptValue006DCD20 *)(*vec)[i])->rva006DCF60(false);
  ZombieInst *inst=(ZombieInst *)((Rva006CD650 *)cih)->rva006CD650();
  Rva006CC110Log(4,"%d :: ZOMBIE SPRITE[name %s  file = %s.swf  size = %d bytes] HAS %d EXTERNAL REFERENCES\n",i+1,cih->name.rva00620090(),inst->resource->file.rva00620090(),(inst->resource->size ? (inst->resource->size) : (inst->resource->size)),cih->refs&0xffff);
  Rva006CC110Log(4,"      REFER TO BUG253 ON COREFORGE FOR MORE INFORMATION [http://coreforge.eac.ad.ea.com/tracker/index.php?func=detail&aid=253&group_id=41&atid=247].  EVALUATION OF YOUR SWF FILES IS HIGHLY RECOMMENDED\n");
 }
}

// Native6CD080..6CD091: when the Apt root object at E176D0 exists, tail-call
// the rowed AptDisplayList walk 0x006F76B0 on its +0x30 display-list
// sub-object (the same +0x30 slot the tick above hands to rva006F7A30).
// Callers unrecovered; address name.
void Rva006CD080ClearDisplayList() {
 if(g_bfmeAptPtrAtE176D0)((AptDisplayList *)&g_bfmeAptPtrAtE176D0->nodes)->rva006F76B0();
}

// Native6CD0A0..6CD0AD: install a non-null AptXml implementation into
// gpAptXmlImpl (E17720, named by the AptXml.cpp assert that reads it);
// a null argument leaves the current one. Address name.
class AptXmlImpl;
AptXmlImpl *gpAptXmlImpl = 0;	// retail RVA 0x00A17720, zero at load
void Rva006CD0A0SetXmlImpl(AptXmlImpl *impl) {
 if(impl)gpAptXmlImpl=impl;
}

// Native6CD3C0..6CD3E1: format the value's rowed sar-dword field 0x006DBB30
// as "0x%X" into the static text buffer at E177D8 and return the buffer.
// Address name; the buffer (E177D8, eight bytes below the E177E0 flags) is
// only declared here.
extern char g_aptFormattedFieldText[];


// Native6CD060..6CD069: store the argument into the Apt word at E176C8
// (beside the E176D0 root and E176D4 suppression flag). Address names.
int g_aptWordAtE176C8 = 0;	// retail RVA 0x00A176C8, zero at load
void Rva006CD060SetWord(int value) {
 g_aptWordAtE176C8=value;
}

// Native6CD390..6CD39C: tail-call the rowed Rva006F7AC0List::rva006F7AC0
// (any node reporting rva006E24E0) on the list the Apt root holds at +0x30.
bool Rva006CD390AnyActive() {
 return ((Rva006F7AC0List *)g_bfmeAptPtrAtE176D0->nodes)->rva006F7AC0();
}

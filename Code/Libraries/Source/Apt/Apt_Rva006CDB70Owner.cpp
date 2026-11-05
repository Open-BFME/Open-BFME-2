// cl: /O2 /MD /D_CRTIMP= /EHsc
// Split from Apt.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.

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
class AptCIH;
#include "AptValue.h"
#include "AptCIHClass.h"
class BfmeAptValue006DCD20;
class AptBasePtrStack {public:int count,capacity;BfmeAptValue006DCD20 **elements;void Push(BfmeAptValue006DCD20 *);BfmeAptValue006DCD20 *At(int);void rva006FE920();};
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
void AptSetInternalVariable(const char *name, const char *text);

void AptGetInternalVariable(const char *name,char *out);


// Native6CBC40..6CBC46 is the standalone allocation-hook forwarder called
// by allocator setup6CC380. Keep its call boundary; the next pool's allocation
// is separately inlined in retail. Original function identity is unresolved.
extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int);
__declspec(noinline) void *Rva006CBC40Allocate(unsigned int bytes);


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
void Rva006CC380Initialize(unsigned valueSize,int valueCount,unsigned chainSize,int chainCount);


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
extern unsigned char g_Va00E1770C;
extern AptActionInterpreter g_aptDateInterpreter;
class Rva006DBB30SarDwordField {public:int get() const;};
#include "BfmeAptValue006DCD20.h"
class Rva006CD650 {public:void *rva006CD650();};
struct TickMovie {char pad[0x24];unsigned interval;};
struct TickState {char pad[0xc];TickMovie *movie;char pad10[0x20];unsigned remainder;};
struct TickNode {char pad[0x54];void *cih;};
class Rva006E34D0 {public:void rva006E34D0(int);char pad[0x30];TickNode **nodes;char pad34[8];int count;};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class AptAnimationPoolData {public:void tickIntervalTimers(int);void rva006E6540();void rva006FB910();};
class AptDisplayList {public:void rva006F7A30();void rva006F76B0();};
class AptLinker {public:void rva006D17F0();void Load(const EAStringC &a,EAStringC b);};
// VA 0x00E176F8 (RVA 0x00A176F8): the Apt linker this unit creates in its
// first tick (g_bfmeAptLinkerAtE176F8 = new Rva008947A0Owner below), so the
// definition lives here, in the assigning unit, and is zero-initialised: four
// units read the object through the name and retail only ever holds the
// pointer the tick stores. Until now nothing defined it, which was the sole
// unresolved name family-2's largest row carried.
extern AptLinker *g_bfmeAptLinkerAtE176F8;
inline void tickAssert(int good,const char *test,const char *file,int line) {
 if(!good){g_bfmeAptAssertAtE17734(test,file,line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
}
__forceinline bool isTickAnimation(void *p) {
 tickAssert(p!=0,"this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xd3);
 return ((Rva006DBB30SarDwordField *)p)->get()==0x12 && !((BfmeAptValue006DCD20 *)p)->isUndefined();
}
inline void *currentTickCIH(){return (*g_bfmeAptPtrAtE176D0->nodes)->cih;}
inline void tickStackAssert(int line) {
 if(g_aptDateInterpreter.stack.count) {g_bfmeAptAssertAtE17734("gAptActionInterpreter.stack.GetSize() == 0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
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
void Rva006CC740SendSavedEvent(const void *data,unsigned nSize);

// Native6CD990..6CDA31: three Ghidra-unlisted level accessors after the tick
// helper. Each looks up _AptGetAnimationAtLevel(level) and reads the
// animation instance that the rowed rva006CD650 returns: +18 when the CIH has
// its +4C resource (else -1), the +0C movie's +08 word (else 0), and bit 25
// of +1C when the level is a defined movie clip (type 0x12, not undefined;
// else -1). Field meanings and original names are unresolved: address names.
int Rva006CD990LevelValue(int level);

int Rva006CD9C0LevelMovieValue(int level);

int Rva006CD9F0LevelFlag(int level);

// ModuleTagStringSwap.cpp's view: a default-argument ctor and no destructible subobject, so
// the EH vector constructor iterator takes the zeroing default ctor closure (retail 0x00013260).
class Rva004A9DF3Element {public:Rva004A9DF3Element(unsigned int *count=0):m_count(count){} ~Rva004A9DF3Element();unsigned int *m_count;};
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
void Rva006CF040Tick(unsigned elapsed) {
 tickAssert(g_bfmeAptInitAtE17700,"bInitialized","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x422);
 Rva004A9DF3Element entries[96];
 g_rva00893030Manager->rva006CDE50(entries,96);
 if(g_bfmeAptFlagAtE176D4)Rva006CEC90Tick();
 else {
  void *p=currentTickCIH();
  if(p && ((Rva006DBB30SarDwordField *)p)->get()==0x12 && !((BfmeAptValue006DCD20 *)p)->isUndefined()) {
   if(Rva006CD7A0Tick(elapsed))d_00891fa0();
  }else{g_bfmeAptLinkerAtE176F8->rva006D17F0();g_bfmeAptPtrAtE176D0->count=0;}
 }
 g_releaseVectorAtE17710->ReleaseValues();
 if(g_Va00E1770C){Rva006E6E20Collect();g_Va00E1770C=0;}
 tickStackAssert(0x453);
}




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
class Rva006CE660Vec {public:void rva006CEB10(const EAStringC &);};
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
extern Rva006CEB10Playback *g_aptPlaybackCheckpoints;
#define PLAYCUR reinterpret_cast<char *&>(g_rva00A176D8)
#define PLAYBASE reinterpret_cast<char *&>(g_bfmeAptFlagAtE176D4)
void Rva006CEC90Tick();







#undef tickAssert
#undef PLAYCUR
#undef PLAYBASE

// Native6CF369 installs6CC150 in the size-aware free callback atE17730.
// DogmaPool::freeBlock6DB2C3..6DB2CB passes size then pointer and cleans8B.
// WB174CEA0 forwards only the pointer to the unsized free callback.
// This resolves the earlier lack of ABI evidence for the ignored second arg.
// NativeE1772C is an unowned four-byte zero-filled writable callback slot.
extern void (__cdecl *g_aptFreeCallback)(void *);
void Rva006CC150FreeWithSize(void *block,unsigned int);


// Native6CF230..6CFA2E is the complete2046B initializer; WB174C390 gives
// Apt.cpp357..438. The existing89B parameter constructor supplies14 ints and
// two flags. Original initializer/type names remain unresolved. Its optional
// vector cellE17714, flagsE1771C/1D and new callback cells below are native
// zero-filled storage. Callback assertion strings establish their roles;
// opaque slots do not claim callable signatures that this body never uses.
struct Rva00222343 {Rva00222343();int fields[14];bool flag38,flag39;};
#define CHECK(e,s,l) do{if(!(e)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}}while(0)
extern void *g_eaStringAtE177D4Storage;
extern unsigned char g_00E1771C;
extern unsigned char g_aptInitFlag39;
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
extern unsigned int g_bfmeExtra1282Flags;
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
extern void (__cdecl *g_00E17774)(void*,int);
extern void (__cdecl *g_bfmeAptFreeAtE17784)(void*,int);
extern void (__cdecl *g_AptBindTexture)(void*,int,void*);
struct AptMatrix;
extern void (__cdecl *g_bfmeAptMatrixCallbackAtE177A0)(AptMatrix*);
extern "C" void (__cdecl *bfmeNotify1209Callback)(void*);
void DX8_Assert();
void Rva006D37E0Set(int);
void Rva0070B670Initialize(int);
extern AptValueVector *g_aptOptionalValueVector;
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
extern void *g_aptLoadAnimationSlot; // Native00E17748; callback ABI unmodeled.
extern void *g_aptFreeConstantTableSlot; // Native00E17750; callback ABI unmodeled.
extern void *g_aptFreeAnimationSlot; // Native00E1774C; callback ABI unmodeled.
extern void *g_aptAllocateStringSlot; // Native00E17770; callback ABI unmodeled.
extern void *g_aptDrawStringSlot; // Native00E17778; callback ABI unmodeled.
extern void *g_aptLoadSoundSlot; // Native00E1777C; callback ABI unmodeled.
extern void *g_aptFreeSoundSlot; // Native00E17780; callback ABI unmodeled.
extern void *g_aptStartSoundStreamSlot; // Native00E17788; callback ABI unmodeled.
extern void *g_aptLoadTextureSlot; // Native00E1778C; callback ABI unmodeled.
extern void *g_aptFreeTextureSlot; // Native00E17790; callback ABI unmodeled.
extern void *g_aptLoadRenderingUnitSlot; // Native00E17798; callback ABI unmodeled.
extern void *g_aptFreeRenderingUnitSlot; // Native00E1779C; callback ABI unmodeled.
extern void *g_aptDrawRenderingUnitSlot; // Native00E177A8; callback ABI unmodeled.
extern void *g_aptCustomControlRenderSlot; // Native00E177AC; callback ABI unmodeled.
extern void *g_aptGetStageHeightSlot; // Native00E177C8; callback ABI unmodeled.
extern void *g_aptGetStageWidthSlot;void Rva006CF230Initialize(const Rva00222343 *input);

#undef CHECK
#undef POOL_ALLOC

// ?rva006cc940@@YAXXZ @0x006CC940 5B: tail jump to the matched Apt shutdown
// tail 0x006CC880; retail calls it from the rowed 0x0022244D.
void rva006cc880();
void rva006cc940();

bool _AptValidate();


// ?Rva006CC600@@YAXPBDPAD@Z @0x006CC600: Apt.cpp's import-target guard
// (assert file/lines 802/805 name it): refuse a target suffix of "#import",
// then forward (path,target) to the linker Load at 0x006D1F80.
// The temporary inequality and literal conjunction retain native EH tracking. The byte at
// 0x00E176FC is the ledger-owned g_aptBackgroundSet (AptMovieFrameControls),
// cleared here.
extern bool g_aptBackgroundSet;
void Rva006CC600(const char *path,char *suffix)
{
 tickAssert(g_bfmeAptInitAtE17700,"bInitialized","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x322);
 EAStringC target(suffix);
 bool isImport = !(target.rva006D30D0(&EAStringC("#import")) && "Please use AptPreloadFile instead of a target of '#import' now.");
 if (isImport) {
  g_bfmeAptAssertAtE17734("sTarget != AptNativeString(\"#import\") && \"Please use AptPreloadFile instead of a target of \x27#import\x27 now.\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x325);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 g_aptBackgroundSet = false;
 g_bfmeAptLinkerAtE176F8->Load(EAStringC(path),target);
}

// Native6CC530..6CC5F0: level lookup walks the existing pool's +30 list;
// on a miss it constructs a96B type19 CIH, roots it, and inserts by level.
// Original one-int ABI is independently named by retail callers and the pin.
// Throwing-new cleanup7A8080 calls the native value-pool free twin6F12F0:
// both normal allocation and exceptional release use the existingF4 owner.
// Native allocation-failure cleanup frees directly through the F4 pool.
// Keep its complete22B implementation consistent with Rva006F6A50Cluster.
AptCIH *_AptGetAnimationAtLevel(int key);


// Native 6CDF60..6CE07C: allocator shutdown with no arguments; WB174D4C0
// Apt.cpp lines 666..691. Both pool allocations are 28B. WB's two deleting
// helpers receive flags 1; inline delete views retain the native operand copy.
void rva006CBC50(void *,unsigned);
void Rva006CDF60();



#define GAPCHECK(e,s,l) do{if(!(e)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}}while(0)
void Rva006CD0B0ResetPoolCount();


// Native6CD350..6CD38A: asserts pMCInfo (Apt.cpp 0x7C0) and applies it to the
// E176D0 pool's +30 child list through the rowed rva006F7AF0. Address name.
void Rva006CD350ApplyChild(void *pMCInfo);


// Native6CD3A0..6CD3BD zeroes an eight-dword record in retail's store order
// (+0,+4,+10,+14,+8,+C,+18,+1C). Record meaning unresolved: address names.
struct Rva006CD3A0Record {int a0,a4,a8,aC,a10,a14,a18,a1C;};
void Rva006CD3A0Clear(Rva006CD3A0Record *r);


// Native6CD120..6CD1E7: Ghidra-unlisted registration of a global extension
// object. Asserts pExtObject (Apt.cpp 0x685, retail texts), builds its name
// from virtual slot 15, calls slot 16, asserts the global extension table
// (E18360) does not already hold that name (0x68C) and adds the object under
// it. Table calls are the rowed rva0070A5C0 lookup and rva006FBB90 add; the
// extension object view and this function's name are address-derived.
class Rva006CD120ExtObject {public:virtual void s0();virtual void s1();virtual void s2();virtual void s3();virtual void s4();virtual void s5();virtual void s6();virtual void s7();virtual void s8();virtual void s9();virtual void s10();virtual void s11();virtual void s12();virtual void s13();virtual void s14();virtual const char *name();virtual void registered();};
class BfmeN1034;
class Rva8D0D80String;class Rva8D0D80Value;
extern AptValue *g_shutdownAtE18360;
void Rva006CD120AddGlobalExtension(Rva006CD120ExtObject *pExtObject);


// Native6CCF30..6CD00D: Ghidra-unlisted focus-by-path helper. A null path
// clears the E176D0 pool's slot through the rowed setter 0x006E3700 and
// succeeds; otherwise the path is resolved like AptGetInternalVariable above
// (rowed getVariable from level 0) and a CIH result is stored through the
// same setter, else it fails. Address-derived name.
bool Rva006CCF30SetFocusPath(const char *path);


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
void Rva006CCD90CallFunction(const char *function,char *result,const char *target,int nArgs,...);


// Retail 0x006CDB70 (46 B): constructor of an owner with a two-handle inline
// buffer. It zeroes the count and used fields, points the items pointer at
// the inline storage at +0xC, and builds the two Rva004A9DF3Element handles
// there through the EH vector constructor iterator (default constructor closure
// 0x00013260, destructor 0x000A9DF3), as the 96-handle table above does. Owner and field
// names are address-derived.
class Rva006CDB70Owner
{
public:
	Rva006CDB70Owner();
private:
	int m_count;
	int m_used;
	Rva004A9DF3Element *m_items;
	Rva004A9DF3Element m_inline[2];
};

Rva006CDB70Owner::Rva006CDB70Owner() : m_count(0), m_used(0), m_items(m_inline)
{
}

// Native6CDA40..6CDB02: Ghidra-unlisted zombie-vector report over the E17714
// optional value vector (owned above): count line, then for each entry from
// the last down its CIH name, the instance resource file and size (+34 ->
// +08/+04) and the +5C low word, plus the coreforge advisory line, all through
// the rowed log 0x006CC110. Retail text; address name. The reload of the
// global into a local inside the loop is what retail's per-iteration load of
// E17714 at the same spot compiles as; a direct ternary read left an extra
// branch (+2B).
void Rva006CDA40ReportZombies();

void Rva006CD080ClearDisplayList();


// Native6CD0A0..6CD0AD: install a non-null AptXml implementation into
// gpAptXmlImpl (E17720, named by the AptXml.cpp assert that reads it);
// a null argument leaves the current one. Address name.
class AptXmlImpl;
extern AptXmlImpl *gpAptXmlImpl;void Rva006CD0A0SetXmlImpl(AptXmlImpl *impl);


// Native6CD3C0..6CD3E1: format the value's rowed sar-dword field 0x006DBB30
// as "0x%X" into the static text buffer at E177D8 and return the buffer.
// Address name; the buffer (E177D8, eight bytes below the E177E0 flags) is
// defined here, beside its only writer.
char g_aptFormattedFieldText[8];	// retail RVA 0x00A177D8, zero at load
const char *Rva006CD3C0FormatField(const Rva006DBB30SarDwordField *value) {
 sprintf(g_aptFormattedFieldText,"0x%X",value->get());
 return g_aptFormattedFieldText;
}

// Native6CD060..6CD069: store the argument into the Apt word at E176C8
// (beside the E176D0 root and E176D4 suppression flag). Address names.
extern int g_aptWordAtE176C8;void Rva006CD060SetWord(int value);



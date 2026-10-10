// cl: /O2 /MD /EHsc

class Rva006DB160 {public:void *allocBlock(int);};
class Rva006DB270 {public:void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
#define POOL_ALLOC static void *operator new(unsigned n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);} static void operator delete(void*p,unsigned n){g_pChainBlockAllocator->freeBlock(p,n);}

// WorldBuilder174F1C0 identifies AptSetInternalVariable in Apt.cpp through
// its own debug refcount label. Native6CCA50..6CCAE1 is 145 bytes.
// Retail passes seven interpreter arguments; _AptGetAnimationAtLevel(0)
// is a separate one-argument cdecl call. Both helpers have existing owners.
// The string wrapper owns one data pointer and is destroyed on scope exit.
class EAStringC {
 void *data;
public:
 EAStringC();
 bool rva006CD4A0() const;
 void rva006D3C60();
 EAStringC(const char *);
 ~EAStringC();
};
class AptValue {
public:
 virtual void AddRef();
 virtual void Release();
 void SetString(const char *);
};
class AptCIH : public AptValue {};
class AptString : public AptValue {public:static AptString *Create();};
class BfmeAptValue006DCD20;
class AptBasePtrStack {public:int count,capacity;BfmeAptValue006DCD20 **elements;};
struct AptInitParmsT;
struct AptActionInterpreter {
 void rva006FEAF0(const AptInitParmsT &);
 AptBasePtrStack stack;
 AptValue *getVariable(AptValue *,AptValue *,const EAStringC *,int,int,int);
 bool setVariable(AptValue *,AptValue *,const EAStringC *,AptValue *,int,int,int);
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
class Rva006DCD20 {public:void rva006DE870(char *);};
void AptGetInternalVariable(const char *name,char *out) {
 EAStringC key(name);
 AptValue *value=g_aptDateInterpreter.getVariable(_AptGetAnimationAtLevel(0),0,&key,1,1,0);
 value->AddRef();
 ((Rva006DCD20 *)value)->rva006DE870(out);
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
extern unsigned char g_00E177E0,g_00E177E1,g_00E177E2,g_00E177E8;
extern int g_00E177E4;
void rva006D2D90();
void *Rva006CBC40Allocate(unsigned);
class Rva006CC4A0;
void rva00ACBC50(Rva006CC4A0 *,int);
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
 static void operator delete(void *ptr,unsigned size) {rva00ACBC50((Rva006CC4A0 *)ptr,size);}
};
class Rva006CC380ValuePool : public Rva006DAEB0 {
public:
 // The out-of-line copy is also retail6CBC60..6CBCA6 (RET8), surrounded
 // by padding. WB174D470 proves the same two-argument constructor and
 // nine-argument base initialization; place_bodies found all70 bytes.
 Rva006CC380ValuePool(unsigned size,int count) : Rva006DAEB0(size,count,g_00E177E1,g_00E177E4,g_00E177E2,1,g_00E177E0,0,g_00E177E8) {}
 static void *operator new(unsigned size) {return g_bfmeAptAllocAtE17728(size);}
 static void operator delete(void *ptr,unsigned size) {rva00ACBC50((Rva006CC4A0 *)ptr,size);}
};
class Rva006DB270;class Rva006D2A60;
extern Rva006DB270 *g_pChainBlockAllocator;
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
void Rva006CC380Initialize(unsigned valueSize,int valueCount,unsigned chainSize,int chainCount) {
 if(g_bfmeAptInitAtE17700) {
  g_bfmeAptAssertAtE17734("bInitialized == 0 && \"Apt Allocator must be initialized before Apt Core!\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\Apt.cpp",0x273);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 rva006D2D90();
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
extern unsigned char g_Va00E1770C;
extern AptActionInterpreter g_aptDateInterpreter;
class Rva006DBB30SarDwordField {public:int get() const;};
class BfmeAptValue006DCD20 {public:bool isUndefined() const;};
class Rva006CD650 {public:void *rva006CD650();};
struct TickMovie {char pad[0x24];unsigned interval;};
struct TickState {char pad[0xc];TickMovie *movie;char pad10[0x20];unsigned remainder;};
struct TickNode {char pad[0x54];void *cih;};
class Rva006E34D0 {public:void rva006E34D0(int);char pad[0x30];TickNode **nodes;char pad34[8];int count;};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class AptAnimationPoolData {public:void tickIntervalTimers(int);void rva006E6540();};
class Rva006F7A30 {public:void rva006F7A30();};
class Rva006FB860 {public:void rva006FB910();};
class AptLinker {public:void rva006D17F0();};
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
  ((Rva006F7A30 *)&g_bfmeAptPtrAtE176D0->nodes)->rva006F7A30();
  ((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->rva006E6540();
  ((Rva006FB860 *)g_bfmeAptPtrAtE176D0)->rva006FB910();
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
class BfmeRefVGO {unsigned *value;public:BfmeRefVGO():value(0){} ~BfmeRefVGO();};
class Rva004A9DF3Element : public BfmeRefVGO {public:Rva004A9DF3Element(){} ~Rva004A9DF3Element();};
class Rva00893030Manager {int head;public:Rva00893030Manager():head(0){} POOL_ALLOC void rva006CDE50(Rva004A9DF3Element *,int);};
extern Rva00893030Manager *g_rva00893030Manager;
class AptValueVector {int capacity,count;AptValue **values;int high;public:AptValueVector(int);void ReleaseValues();POOL_ALLOC};
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
extern "C" unsigned strlen(const char *);
extern "C" int sprintf(char *,const char *,...);
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
 PlaybackIterator(PlaybackItem *c,PlaybackItem *f,PlaybackItem *l):cur(c),first(f),last(l){}
 PlaybackIterator &operator++(){++cur;return *this;}
 PlaybackItem &operator*(){iteratorCheck(cur>=first && cur<last,"Trying to dereference an invalid iterator");return *cur;}
 bool operator!=(const PlaybackIterator &other){iteratorCheck(first==other.first && last==other.last,"Iterators are not in same range");return cur!=other.cur;}
};
class PlaybackRange {
 PlaybackItem *first,*last;
public:
 PlaybackRange(PlaybackItem *f,PlaybackItem *l):first(f),last(l){}
 PlaybackIterator begin(){return PlaybackIterator(first,first,last);}
 PlaybackIterator end(){return PlaybackIterator(last,first,last);}
};
class Rva006CEB10Playback {
public:
 int size,capacity;PlaybackItem *items;PlaybackItem inlineItems[2];
 Rva006CEB10Playback():size(0),capacity(0),items(inlineItems){} POOL_ALLOC
 void rva006CEB10(const EAStringC &);
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
     g_aptPlaybackCheckpoints->rva006CEB10(EAStringC(name));break;
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
extern EAStringC g_eaStringAtE177D4;
unsigned char g_00E1771C=0;
unsigned char g_aptInitFlag39=0;
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
void Rva006CF852FoldedEmptyInit();
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
 if(!g_eaStringAtE177D4.rva006CD4A0())g_eaStringAtE177D4.rva006D3C60();
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
 Rva006CF852FoldedEmptyInit();
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

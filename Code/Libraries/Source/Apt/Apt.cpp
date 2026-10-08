// cl: /O2 /MD /EHsc
// WorldBuilder174F1C0 identifies AptSetInternalVariable in Apt.cpp through
// its own debug refcount label. Native6CCA50..6CCAE1 is 145 bytes.
// Retail passes seven interpreter arguments; _AptGetAnimationAtLevel(0)
// is a separate one-argument cdecl call. Both helpers have existing owners.
// The string wrapper owns one data pointer and is destroyed on scope exit.
class EAStringC {
 void *data;
public:
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
struct AptActionInterpreter {
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
class Rva006E34D0 {public:char pad[0x30];TickNode **nodes;char pad34[8];int count;};
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
class Rva00893030Manager {public:void rva006CDE50(Rva004A9DF3Element *,int);};
extern Rva00893030Manager *g_rva00893030Manager;
class AptValueVector {public:void ReleaseValues();};
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




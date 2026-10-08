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
struct AptActionInterpreter {
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

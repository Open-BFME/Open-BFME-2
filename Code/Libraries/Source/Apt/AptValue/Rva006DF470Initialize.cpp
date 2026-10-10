// cl: /O2 /arch:IA32 /MD /EHsc
// Native 006DF470..006DF999, 1321B, RET; WB twin 0176C430 names
// AptValueInitialize in AddRef debug arguments (AptValue.cpp 732..800).
// Existing Rva006DF470Initialize spelling serves the matched Apt.cpp caller.
// Target proves allocation sizes 8/960/8, six32B value types and seven36B
// native functions, each constructor/callback operand and the global sequence.
// Class identities of the address-named constructors remain unknown. The
// local layouts expose only their proven allocation extents and AptValue +4.
// Existing global providers are reused with their exact COFF spellings; the
// E18650 provider's one-pointer EAStringC view represents the global object
// slot, not another string allocation. Color transform32B and counter16B
// storage are independently sized and initially zero in retail; the 16B
// counter memset is corroborated by WB, and retains retail's zero scheduling.
// Callback names remain addresses; native construction operands plus the
// established AptNativeFunction context/count ABI prove entry/signature.
extern "C" void *memset(void*,int,unsigned);
class AptValue{public:virtual void AddRef();virtual void Release();virtual void ForceDelete();virtual void *GetNativeHashVirtual(); unsigned mnLowBits:18;unsigned mnGCRootCount:7;unsigned mnType:7;};
class Rva006DB160{public:void *allocBlock(int);};
class Rva006DB270{public:void freeBlock(void*,int);};
class Rva006D2A60{public:void *allocBlock(int);void freeBlock(void*,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
#define POOL_E8 static void *operator new(unsigned n){return ((Rva006DB160*)g_pChainBlockAllocator)->allocBlock(n);} static void operator delete(void*p,unsigned n){g_pChainBlockAllocator->freeBlock(p,n);}
#define POOL_F4 static void *operator new(unsigned n){return g_pChainBlockAllocatorF4->allocBlock(n);} static void operator delete(void*p,unsigned n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
class Rva006DE2C0:public AptValue{public:Rva006DE2C0();POOL_E8};
class Rva006DE390:public AptValue{public:Rva006DE390();POOL_E8};
class Rva008D2B10{public:Rva008D2B10();float m00[14];char gap[0x3b8-0x38];float m3b8,m3bc;POOL_E8};
class Rva006DE480:public AptValue{public:Rva006DE480();char body[0x20-8];POOL_F4};
class Rva006DE510:public AptValue{public:Rva006DE510();char body[0x20-8];POOL_F4};
class Rva006DE5A0:public AptValue{public:Rva006DE5A0();char body[0x20-8];POOL_F4};
class Rva006DE790:public AptValue{public:Rva006DE790();char body[0x20-8];POOL_F4};
class Rva006DE630:public AptValue{public:Rva006DE630();char body[0x20-8];POOL_F4};
class Rva006DE6D0:public AptValue{public:Rva006DE6D0();char body[0x20-8];POOL_F4};
typedef AptValue*(__cdecl*AptNativeCallback)(AptValue*,int);
class AptNativeFunction:public AptValue{public:AptNativeFunction(AptNativeCallback);char body[0x24-8];POOL_F4};
class AptString:public AptValue{public:static AptString *Create();};
class AptValueVector{public:void ReleaseValues();};extern AptValueVector*g_releaseVectorAtE17710;
class BfmeAptValue006DCD20;extern BfmeAptValue006DCD20*g_aptUndefinedAtE18078;
class AptRenderingContext;extern AptRenderingContext*g_aptRenderingContextAtE180C0;
struct BfmeM1208{float m_w[6];};extern BfmeM1208 g_aptBoxAtE180C4;
struct AptColorTransformWords{float m_w[8];};AptColorTransformWords g_aptIdentityColorTransform;
class Rva00898D60Target;extern Rva00898D60Target*g_Rva01337A20;class EAStringC{void *data;};extern EAStringC g_00E18650;
extern AptValue*g_shutdownAtE18070,*g_shutdownAtE180B8,*g_shutdownAtE18068,*g_shutdownAtE180BC,*g_shutdownAtE18360,*g_shutdownAtE180AC;
class AptNativeHash;extern AptNativeHash*g_bfmeAptHashAtE180E4;
extern AptValue *g_shutdownAtE180A8,*g_shutdownAtE18080,*g_shutdownAtE18084,*g_shutdownAtE180B4,*g_shutdownAtE18074,*g_shutdownAtE1806C,*g_shutdownAtE180E8;
int g_aptInitializerCounters[4];
void _constructBuiltInObjects();
AptValue *callback006FEFF0(AptValue*,int);
AptValue *callback006FF400(AptValue*,int);
AptValue *callback006FF660(AptValue*,int);
AptValue *callback006FF750(AptValue*,int);
struct AptActionInterpreter;AptValue *rva006ff850(AptActionInterpreter*,int);
AptValue *callback006FD2D0(AptValue*,int);
struct AptActionInterpreter;AptValue *rva006ff5d0(AptActionInterpreter*,int);
void Rva006DF470Initialize(){
g_aptUndefinedAtE18078=(BfmeAptValue006DCD20*)new Rva006DE2C0;
g_aptRenderingContextAtE180C0=(AptRenderingContext*)new Rva008D2B10;
((AptValue*&)g_Rva01337A20)=new Rva006DE390;
g_shutdownAtE18070=new Rva006DE480;g_shutdownAtE18070->AddRef();
g_shutdownAtE180B8=new Rva006DE510;g_shutdownAtE180B8->AddRef();
g_shutdownAtE18068=new Rva006DE5A0;g_shutdownAtE18068->AddRef();
g_shutdownAtE180BC=new Rva006DE790;g_shutdownAtE180BC->AddRef();
((AptValue*&)g_00E18650)=new Rva006DE630;((AptValue*&)g_00E18650)->AddRef();
g_shutdownAtE18360=new Rva006DE6D0;g_shutdownAtE18360->AddRef();
g_shutdownAtE180AC=AptString::Create();g_shutdownAtE180AC->mnGCRootCount=1;g_shutdownAtE180AC->AddRef();
g_bfmeAptHashAtE180E4=0;
_constructBuiltInObjects();
g_aptIdentityColorTransform.m_w[0]=1.0f;
g_aptIdentityColorTransform.m_w[1]=1.0f;
g_aptIdentityColorTransform.m_w[2]=1.0f;
g_aptIdentityColorTransform.m_w[3]=1.0f;
g_aptIdentityColorTransform.m_w[4]=0.0f;
g_aptIdentityColorTransform.m_w[5]=0.0f;
g_aptIdentityColorTransform.m_w[6]=0.0f;
g_aptIdentityColorTransform.m_w[7]=0.0f;
g_aptBoxAtE180C4.m_w[0]=1.0f;
g_aptBoxAtE180C4.m_w[1]=0.0f;
g_aptBoxAtE180C4.m_w[2]=0.0f;
g_aptBoxAtE180C4.m_w[3]=1.0f;
g_aptBoxAtE180C4.m_w[4]=0.0f;
g_aptBoxAtE180C4.m_w[5]=0.0f;
g_shutdownAtE180A8=new AptNativeFunction(callback006FEFF0);g_shutdownAtE180A8->mnGCRootCount=1;g_shutdownAtE180A8->AddRef();
g_shutdownAtE18080=new AptNativeFunction(callback006FF400);g_shutdownAtE18080->mnGCRootCount=1;g_shutdownAtE18080->AddRef();
g_shutdownAtE18084=new AptNativeFunction((AptNativeCallback)rva006ff5d0);g_shutdownAtE18084->mnGCRootCount=1;g_shutdownAtE18084->AddRef();
g_shutdownAtE180B4=new AptNativeFunction(callback006FF660);g_shutdownAtE180B4->mnGCRootCount=1;g_shutdownAtE180B4->AddRef();
g_shutdownAtE18074=new AptNativeFunction(callback006FF750);g_shutdownAtE18074->mnGCRootCount=1;g_shutdownAtE18074->AddRef();
g_shutdownAtE1806C=new AptNativeFunction((AptNativeCallback)rva006ff850);g_shutdownAtE1806C->mnGCRootCount=1;g_shutdownAtE1806C->AddRef();
g_shutdownAtE180E8=new AptNativeFunction(callback006FD2D0);g_shutdownAtE180E8->mnGCRootCount=1;g_shutdownAtE180E8->AddRef();
memset(g_aptInitializerCounters,0,16);
g_releaseVectorAtE17710->ReleaseValues();
}

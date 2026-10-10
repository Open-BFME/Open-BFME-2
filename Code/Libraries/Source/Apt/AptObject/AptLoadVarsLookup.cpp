// cl: /O2 /MD /EHsc
// Original EA AptMiscObjects.cpp31ceb5bf2d6e4f60 supplies LoadVars callback
// semantics. Named WB177CA50/native6EA700 dispatch independently selects these
// callbacks; native asserts1222/1228 name both runtime slots and prove enum3.
// Scoped receiver views: no AptValue object is constructed here. Native virtual
// hash slot3 and original source supply the calls; EAStringC owns the sole local
// class lifetime, independently proven4B by existing providers and retail EH.
// AptLoadVars itself is never constructed: only its established const lookup
// ABI and native loaded+20 field are used, not a complete class/vtable layout.
// Runtime slots E1776C/E177BC/E177C0 are proven4B zero-filled storage, owned in
// data_rows.csv; the latter two keep prior consumers' existing symbol names.
// Six native-function caches retain the real Rva008B2BD0ReleaseGlobals owner.
// Original source has a null-send check, absent in native: native sends directly
// after its assertion; all source behavior follows the witnessed retail body.
class EAStringC {void *data;public:__declspec(nothrow) EAStringC &clear();~EAStringC();const char *rva00620090()const;bool IsEqualTo(const EAStringC *)const;unsigned int rva006D3750()const;bool rva006D3510(const char *)const;};
// The retail clear16B is a plain singleton store/increment: it cannot throw.
// A TU-local lifetime wrapper avoids emitting the legacy divergent external
// EAStringC default-ctor COMDAT; native bytes and every unwind state stay exact.
namespace {
class LoadVarsScopedString : public EAStringC {
public:__forceinline LoadVarsScopedString(){clear();}
};
}
class AsciiString;
class AptNativeHash {public:struct Entry;AsciiString *rva0070AA40();Entry *rva0070AAA0(Entry *);};
class AptValue {public:virtual void slot0();virtual void slot1();virtual void slot2();virtual AptNativeHash *GetNativeHashVirtual();void SetString(const char *);void toString(EAStringC &)const;EAStringC rva006ddde0();};
class BfmeAptValue006DCD20 {public:void setGCRootCount(unsigned int);BfmeAptValue006DCD20 *rva006DD2E0();};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;void loadVariables(AptValue *,AptValue *,const EAStringC *);};
extern AptActionInterpreter g_aptDateInterpreter;
class AptBoolean {public:static AptValue *Create(bool);};
void (__cdecl *g_bfmeAptSendVariablesAtE1776C)(const char *,const char *,const char *,const char *,int)=0;

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
int (__cdecl *g_rva00A177BC)(const char *,int)=0;
int (__cdecl *g_rva00A177C0)(const char *,int)=0;
AptValue *__cdecl Rva008A4EA0MakeFloat(float);
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void *,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6500 {
 unsigned char storage[36];
public:Rva006D6500(int);
 static void *operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
};
class Rva008B2BD0Item {public:virtual void unused0();virtual void release();};
extern Rva008B2BD0Item *g_rva008B2BD0_0,*g_rva008B2BD0_1,*g_rva008B2BD0_2,*g_rva008B2BD0_3,*g_rva008B2BD0_4,*g_rva008B2BD0_5;
struct R4Word {const char *name;int value;};
const R4Word *Rva008A44A0(const char *,unsigned int);
void Rva006CC110Log(int,const char *,...);
AptValue *rva006e9730(AptValue *);
class AptString;
// The existing pooled string factory returns AptString; SetString has the
// actual AptValue provider. No complete string layout is assumed here.
class AptString {public:static AptString *Create();};
class AptLoadVars {
public:
 virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const)const;
 static AptValue *sMethod_load(AptValue *,int);static AptValue *sMethod_send(AptValue *,int);static AptValue *sMethod_sendAndLoad(AptValue *,int);
 static AptValue *sMethod_getBytesTotal(AptValue *,int);
 static AptValue *sMethod_getBytesLoaded(AptValue *,int);
};
AptValue *AptLoadVars::sMethod_getBytesTotal(AptValue *,int)
{
 if(!g_rva00A177BC) {
  g_bfmeAptAssertAtE17734("gAptFuncs.pfnGetBytesTotal","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1222);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 float byteCount=(float)g_rva00A177BC(0,3);
 return Rva008A4EA0MakeFloat(byteCount);
}
AptValue *AptLoadVars::sMethod_getBytesLoaded(AptValue *,int)
{
 if(!g_rva00A177C0) {
  g_bfmeAptAssertAtE17734("gAptFuncs.pfnGetBytesLoaded","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1228);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 float byteCount=(float)g_rva00A177C0(0,3);
 return Rva008A4EA0MakeFloat(byteCount);
}

AptValue *AptLoadVars::sMethod_send(AptValue *value,int nParams)
{
 if(nParams<=0||nParams>3)return AptBoolean::Create(false);
 AptValue *arg=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(0));
 LoadVarsScopedString url;
 arg->toString(url);
 LoadVarsScopedString target;
 if(nParams>1) {
  AptValue *targetValue=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(1));
  targetValue->toString(target);
 }
 LoadVarsScopedString method;
 if(nParams>2) {
  AptValue *methodValue=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(2));
  methodValue->toString(method);
 }
 EAStringC properties=value->rva006ddde0();
 if(!g_bfmeAptSendVariablesAtE1776C) {
  g_bfmeAptAssertAtE17734("gAptFuncs.pfnSendVariables","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1164);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 g_bfmeAptSendVariablesAtE1776C(url.rva00620090(),target.rva00620090(),method.rva00620090(),properties.rva00620090(),0);
 return AptBoolean::Create(true);
}

struct BfmeKey1279;
class BfmeLookup1279 {public:void bfmeErase1279(BfmeKey1279 &);};
EAStringC *Rva0070B4F0GetString(int);
AptValue *AptLoadVars::sMethod_sendAndLoad(AptValue *value,int nParams)
{
 *reinterpret_cast<int *>(reinterpret_cast<char *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD2E0())+0x20)=0;
 if(nParams<=0||nParams>3)return AptBoolean::Create(false);
 AptValue *arg=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(0));
 LoadVarsScopedString url;
 arg->toString(url);
 AptValue *targetValue=0;
 LoadVarsScopedString target;
 if(nParams>1)targetValue=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(1));
 LoadVarsScopedString method;
 if(nParams>2) {
  AptValue *methodValue=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(2));
  methodValue->toString(method);
 }
 EAStringC properties=value->rva006ddde0();
 if(!g_bfmeAptSendVariablesAtE1776C) {
  g_bfmeAptAssertAtE17734("gAptFuncs.pfnSendVariables","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",1196);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 g_bfmeAptSendVariablesAtE1776C(url.rva00620090(),target.rva00620090(),method.rva00620090(),properties.rva00620090(),1);
 AptNativeHash *hash=value->GetNativeHashVirtual();
 if(!hash)return AptBoolean::Create(false);
 for(AsciiString *key=hash->rva0070AA40();key;key=reinterpret_cast<AsciiString *>(hash->rva0070AAA0(reinterpret_cast<AptNativeHash::Entry *>(key)))) {
  EAStringC *str=reinterpret_cast<EAStringC *>(key);
  if(str->IsEqualTo(Rva0070B4F0GetString(0))||str->IsEqualTo(Rva0070B4F0GetString(0x78)))continue;
  reinterpret_cast<BfmeLookup1279 *>(hash)->bfmeErase1279(*reinterpret_cast<BfmeKey1279 *>(key));
 }
 g_aptDateInterpreter.loadVariables(targetValue,0,0);
 *reinterpret_cast<int *>(reinterpret_cast<char *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD2E0())+0x20)=1;
 return AptBoolean::Create(true);
}

AptValue *AptLoadVars::sMethod_load(AptValue *value,int nParams)
{
 *reinterpret_cast<int *>(reinterpret_cast<char *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD2E0())+0x20)=0;
 if(nParams<=0||nParams>1)return AptBoolean::Create(false);
 AptValue *arg=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(0));
 LoadVarsScopedString url;
 arg->toString(url);
 AptNativeHash *hash=value->GetNativeHashVirtual();
 if(!hash)return AptBoolean::Create(false);
 for(AsciiString *key=hash->rva0070AA40();key;key=reinterpret_cast<AsciiString *>(hash->rva0070AAA0(reinterpret_cast<AptNativeHash::Entry *>(key)))) {
  EAStringC *str=reinterpret_cast<EAStringC *>(key);
  if(str->IsEqualTo(Rva0070B4F0GetString(0))||str->IsEqualTo(Rva0070B4F0GetString(0x78)))continue;
  reinterpret_cast<BfmeLookup1279 *>(hash)->bfmeErase1279(*reinterpret_cast<BfmeKey1279 *>(key));
 }
 g_aptDateInterpreter.loadVariables(value,0,&url);
 *reinterpret_cast<int *>(reinterpret_cast<char *>(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->rva006DD2E0())+0x20)=1;
 return AptBoolean::Create(true);
}


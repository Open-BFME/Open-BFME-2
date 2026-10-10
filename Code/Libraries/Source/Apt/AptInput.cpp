// cl: /O2 /G6 /EHsc /MD /DNDEBUG
// ?rva006FACA0@Rva006FB860@@QAE_NHHPAPAX@Z, retail 0x006FACA0..0x006FAF73.
// WB 0x017999A0 explicitly identifies AptAnimationPoolData::HandleFocusButton,
// AptInput.cpp:1207..1304. Target instructions occupy 687 bytes; their aligned
// five-target jump table and fifteen-byte case map extend the body to 723.
// The target map sends 1/2/14/15 to string IDs 10/13/19/3 respectively.
// Retail independently proves ECX=this, RET12, AL result, current+6C,
// CIH parent+48/instance+4C, instance hash+10, and checked-string name+8.
// Partial ABI views retain the already pinned neutral method and class name.
// The BFME1 AptInput.cpp donor at 575ba2b04 supplies the related suffix-search
// semantics, but its clean compiled bodies do not place this handler; the
// complete string-resolution and interpreter paths here follow WB and retail.
// No donor layout or complete class identity is asserted by byte matching.
class EAStringC {
    void *data;
public:
    EAStringC();
    ~EAStringC();
    const char *rva00620090() const;
    unsigned int rva006D3750() const;
};
class AptValue;
class BfmeAptValue006DCD20 {
public:
    bool isString() const;
    int isScriptFunction() const;
    bool isCIH(bool) const;
    bool rva006DCC60(bool) const;
    BfmeAptValue006DCD20 *rva006DCF60(bool);
    BfmeAptValue006DCD20 *checkedString();
};
class AptCIH {public:bool rva006CFCD0()const;void *rva006E1170()const;};
class AptValue {public:virtual void AddRef();virtual void Release();};
class Rva0070B380 {public:void *lookup(const EAStringC&);};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);void rva006FE920();};
struct AptActionSetup {AptValue *context,*value;const char *name;int action;};
struct AptActionInterpreter {public:void *PrepareForExecution(AptActionSetup*);void CleanupAfterExecution(void*,AptActionSetup*);void callFunction(AptValue*,AptValue*,int);};
extern AptActionInterpreter g_aptDateInterpreter;
class Rva006E34D0;extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
struct Rva006E3710Node;class Rva006E3710 {public:bool rva006E3710(Rva006E3710Node*);};
extern void(__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
EAStringC *__cdecl Rva0070B4F0GetString(int);
unsigned char __cdecl rva006FEC00(int,int,EAStringC*,int*,EAStringC*);
class Rva006FB860 {public:char pad[0x6C];AptCIH *current;bool rva006FACA0(int,int,void**);};
bool Rva006FB860::rva006FACA0(int event,int transition,void **out)
{
 if (!out) {
  g_bfmeAptAssertAtE17734("ppNewButton","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x4B7);
  if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
 }
 *out=0;if (!current) return false;
 if (transition) return false;
 EAStringC *key;
 switch(event) {
 case 14:key=Rva0070B4F0GetString(0x13);break;
 case 15:key=Rva0070B4F0GetString(3);break;
 case 1:key=Rva0070B4F0GetString(10);break;
 case 2:key=Rva0070B4F0GetString(13);break;
 default:return false;
 }
 AptCIH *context=*(AptCIH**)((char*)current+0x48);
 Rva0070B380 *hash=*(Rva0070B380**)((char*)context->rva006E1170()+0x10);
 BfmeAptValue006DCD20 *value=(BfmeAptValue006DCD20*)hash->lookup(*key);if(!value)return false;
 if(value->isString()) {
  EAStringC rest;BfmeAptValue006DCD20 *resolved;
  EAStringC *source=(EAStringC*)((char*)value->checkedString()+8);
  rva006FEC00((int)context,0,source,(int*)&resolved,&rest);
  if(resolved) {
   BfmeAptValue006DCD20 *node=resolved->rva006DCF60(false);
   if(rest.rva006D3750()==0 && (node->rva006DCC60(false)||((AptCIH*)node)->rva006CFCD0())) *out=node;
   else if((int)rest.rva006D3750()>0 && ((AptCIH*)node)->rva006CFCD0()) {
    Rva0070B380 *members=*(Rva0070B380**)((char*)*(void**)((char*)node+0x4C)+0x10);
    BfmeAptValue006DCD20 *found=(BfmeAptValue006DCD20*)members->lookup(rest);if(found)value=found;
   }
  }
 }
 if((unsigned char)value->isScriptFunction()) {
  AptActionSetup setup;const char *text=key->rva00620090();setup.context=(AptValue*)context;setup.value=(AptValue*)value;setup.name=text;setup.action=0x400000;
  void *saved=g_aptDateInterpreter.PrepareForExecution(&setup);
  g_aptDateInterpreter.callFunction((AptValue*)context,(AptValue*)value,0);
  g_aptDateInterpreter.CleanupAfterExecution(saved,&setup);
  BfmeAptValue006DCD20 *result=(BfmeAptValue006DCD20*)((AptBasePtrStack*)&g_aptDateInterpreter)->At(0);
  if(result->isCIH(false)){((AptValue*)result)->AddRef();((AptBasePtrStack*)&g_aptDateInterpreter)->rva006FE920();value=result;}
  else {
   ((AptBasePtrStack*)&g_aptDateInterpreter)->rva006FE920();
   return true;
  }
 } else ((AptValue*)value)->AddRef();
 if(value->rva006DCF60(false)->rva006DCC60(false)||((AptCIH*)value->rva006DCF60(false))->rva006CFCD0()) {
  if(!((Rva006E3710*)g_bfmeAptPtrAtE176D0)->rva006E3710((Rva006E3710Node*)value->rva006DCF60(false))) *out=value->rva006DCF60(false);
 }
 ((AptValue*)value)->Release();return false;
}

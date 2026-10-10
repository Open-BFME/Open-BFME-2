// ?sMethod_getAnalogStickInfo@AptKey@@SAPAVAptValue@@PAV2@H@Z
// partial score=0.8422764227642277 date=2026-10-10
// cl: /O2 /MD /EHsc
// Source guide31ceb5bf2d6e4f60 AptMiscObjects.cpp (later APT); WB177C7D0
// independently names lookup and native literal dispatch identifies callbacks.
// Existing canonical Apt base types, native tagged providers and data owners
// are retained; the animation/listener prefix remains a scoped receiver view.
#include "../Code/Libraries/Source/Apt/AptObject/AptScriptFunction.h"
class BfmeAptValue006DCD20 {
public: bool isCIH(bool=false) const; void setGCRootCount(unsigned int);
};
class Rva006DBB60ShrNAndField { public: bool get()const; };
class Rva008A4570Owner { public: bool nameEquals(const char *); };
class AptBasePtrStack {public: BfmeAptValue006DCD20 *At(int);int count,capacity;BfmeAptValue006DCD20 **elements;};
struct AptActionInterpreter { AptBasePtrStack stack; };
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
template<class T> class AptValueSet {public: bool has(T)const;};
class Rva006E9A40List {public:void add(AptCIH *);};
class Rva006E0DE0 {public:int rva006E0DE0(AptValue *);};
class Rva006E34D0 {public:unsigned char unaccessed00[0x18];AptValueSet<AptValue *> listenerSet;};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class AptBoolean {public:static AptValue *Create(bool);};
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void *,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
// Constructor storage view only; rowed native ctor initializes all36 bytes.
class Rva006D6500 {
 unsigned char storage[36];
public:
 Rva006D6500(int callback);
 static void *operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
};
class BfmeC1062 {public:virtual void bfmeSlot1062C_0();virtual void bfmeSlot1062C_1();};
extern BfmeC1062 *g_bfmeC1062,*g_bfmeD1062;
extern unsigned int Rva008A5250LastKey;
extern const int Rva008A5250KeyTable[20];
extern "C" int __cdecl toupper(int);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptKey : public AptObject {
public:
 static AptValue *sMethod_getAnalogStickInfo(AptValue *,int);
 static AptValue *sMethod_isDown(AptValue *,int);
 static AptValue *sMethod_isToggled(AptValue *,int);
 static AptValue *sMethod_addListener(AptValue *,int);
 static AptValue *sMethod_removeListener(AptValue *,int);
};
AptValue *AptKey::sMethod_addListener(AptValue *,int nParams)
{
 if(nParams!=1)return gpUndefinedValue;
 AptValue *value=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(0));
 if(reinterpret_cast<Rva006DBB60ShrNAndField *>(value)->get()) {
  if(reinterpret_cast<BfmeAptValue006DCD20 *>(value)->isCIH()) {
   if((*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(value)+0x5c)&0xc0000)!=0)return gpUndefinedValue;
  }
  AptValueSet<AptValue *> *set=&g_bfmeAptPtrAtE176D0->listenerSet;
  if(!set->has(value)) reinterpret_cast<Rva006E9A40List *>(set)->add(reinterpret_cast<AptCIH *>(value));
 }
 return gpUndefinedValue;
}
AptValue *AptKey::sMethod_removeListener(AptValue *,int nParams)
{
 if(nParams!=1)return AptBoolean::Create(false);
 AptValue *value=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(0));
 if(reinterpret_cast<Rva006DBB60ShrNAndField *>(value)->get()) {
  AptValueSet<AptValue *> *set=&g_bfmeAptPtrAtE176D0->listenerSet;
  if(set->has(value)) {
   reinterpret_cast<Rva006E0DE0 *>(set)->rva006E0DE0(value);
   return AptBoolean::Create(true);
  }
 }
 return AptBoolean::Create(false);
}

AptValue *AptKey::sMethod_isDown(AptValue *,int)
{
 AptValue *pValue=reinterpret_cast<AptValue *>(g_aptDateInterpreter.stack.At(0));
 if((Rva008A5250LastKey&3)==1) {
  int code=Rva008A5250LastKey>>17;
  if(code>=32&&code<=126)code=toupper(code);
  else if(code<20)code=Rva008A5250KeyTable[code];
  return AptBoolean::Create(code==pValue->toInteger());
 }
 return AptBoolean::Create(false);
}
AptValue *AptKey::sMethod_isToggled(AptValue *,int)
{
 g_bfmeAptAssertAtE17734("false","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",656);
 if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 return AptBoolean::Create(false);
}

// ?AptValueGC::AptValueGC present-unmatched
inline AptValueGC::AptValueGC(AptVirtualFunctionTable_Indices type):AptValue(type){}
// ?AptValueWithHash::AptValueWithHash present-unmatched
inline AptValueWithHash::AptValueWithHash(AptVirtualFunctionTable_Indices type,int n):AptValueGC(type),mNativeHash(n){}
// ?AptObject::AptObject present-unmatched
inline AptObject::AptObject(AptVirtualFunctionTable_Indices type,int n):AptValueWithHash(type,n){mnImplementedObjects=0;mbHasClass=0;mbIsInMainInst=0;}
enum KeyObjectAllocation {keyObjectAllocation};
// ?operator new absent-from-retail
inline void *operator new(unsigned int n,KeyObjectAllocation){return g_pChainBlockAllocatorF4->allocBlock(n);}
// ?operator delete absent-from-retail
inline void operator delete(void *p,KeyObjectAllocation){g_pChainBlockAllocatorF4->freeBlock(p,32);}
class EAStringC {void *data;public:EAStringC(const char *);~EAStringC();EAStringC &operator=(const EAStringC &);};
EAStringC *Rva0070B4F0GetString(int);
class AptInteger {public:static AptValue *Create(int);};
AptValue *Rva008A4EA0MakeFloat(float);
struct KeyAnimationAnalog {unsigned char prefix[0x7c];float leftX,leftY;unsigned char unused[8];float rightX,rightY;};
AptValue *AptKey::sMethod_getAnalogStickInfo(AptValue *,int)
{
 int controller=0;
 int type=503;
 if(Rva008A5250LastKey!=0) {
  unsigned int input=Rva008A5250LastKey;
  if(!(((input&3)==1&&(input&0xfffe0000)==0x3ec0000)||(input&0xfffe0000)==0x3ea0000)) {
   g_bfmeAptAssertAtE17734("INPUT_IS_ANALOG(&gAptActionInterpreter.input)","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",839);
   if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
  }
  type=Rva008A5250LastKey>>17;
  controller=(Rva008A5250LastKey>>2)&255;
 }
 int controller0=controller-2;
 AptObject *obj=new(keyObjectAllocation) AptObject((AptVirtualFunctionTable_Indices)27);
 AptValue *controllerValue=AptInteger::Create(controller0);
 reinterpret_cast<AptNativeHash *>(reinterpret_cast<char *>(obj)+8)->Set(Rva0070B4F0GetString(47),controllerValue);
 EAStringC temp("fXAxisValue");
 if(type==501) {
  AptValue *x=Rva008A4EA0MakeFloat(reinterpret_cast<KeyAnimationAnalog *>(g_bfmeAptPtrAtE176D0)->leftX);
  AptValue *y=Rva008A4EA0MakeFloat(reinterpret_cast<KeyAnimationAnalog *>(g_bfmeAptPtrAtE176D0)->leftY);
  reinterpret_cast<AptNativeHash *>(reinterpret_cast<char *>(obj)+8)->Set(&temp,x);
  temp="fYAxisValue";
  reinterpret_cast<AptNativeHash *>(reinterpret_cast<char *>(obj)+8)->Set(&temp,y);
  return obj;
 } else if(type==502) {
  AptValue *x=Rva008A4EA0MakeFloat(reinterpret_cast<KeyAnimationAnalog *>(g_bfmeAptPtrAtE176D0)->rightX);
  AptValue *y=Rva008A4EA0MakeFloat(reinterpret_cast<KeyAnimationAnalog *>(g_bfmeAptPtrAtE176D0)->rightY);
  temp="fXAxisValue";
  reinterpret_cast<AptNativeHash *>(reinterpret_cast<char *>(obj)+8)->Set(&temp,x);
  temp="fYAxisValue";
  reinterpret_cast<AptNativeHash *>(reinterpret_cast<char *>(obj)+8)->Set(&temp,y);
 }
 return obj;
}

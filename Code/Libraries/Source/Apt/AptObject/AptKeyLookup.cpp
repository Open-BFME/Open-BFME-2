// cl: /O2 /MD /EHsc
// Source guide31ceb5bf2d6e4f60 AptMiscObjects.cpp (later APT); WB177BA90
// independently names Key lookup. Its native word dispatch proves the callbacks.
// Listener set is independently witnessed at animation+18 (Mouse uses+20).
// Native Key lookup1723B includes code through6EB2A2,27-entry target table
// at6EB2A4..6EB310 and107-byte sparse map ending6EB37B, beforeMouse6EB380.
// Existing canonical Apt base types, native tagged providers and data owners
// are retained; the animation/listener prefix remains a scoped receiver view.
#include "AptScriptFunction.h"
class BfmeAptValue006DCD20 {
public: int isKey() const;bool isCIH(bool=false) const; void setGCRootCount(unsigned int);
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
 virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const)const;
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

class EAStringC {void *data;public:const char *rva00620090()const;unsigned int rva006D3750()const;};
struct BfmeW1229 {const char *name;int value;};
const BfmeW1229 *bfmeFind1229(const char *,unsigned int);
class AptInteger {public:static AptValue *Create(int);};
AptValue *aptKeyValue();
AptValue *aptKeyCode();
AptInteger *aptPackedKeyFieldAt008A5360();
class Rva008A47B0Item {public:virtual void unused0();virtual void release();};
extern Rva008A47B0Item *g_rva008A47B0_0;
extern Rva008A47B0Item *g_rva008A47B0_1;
extern Rva008A47B0Item *g_rva008A47B0_2;
extern Rva008A47B0Item *g_rva008A47B0_3;
extern Rva008A47B0Item *g_rva008A47B0_4;
extern Rva008A47B0Item *g_rva008A47B0_5;
extern Rva008A47B0Item *g_rva008A47B0_6;
extern Rva008A47B0Item *g_rva008A47B0_7;
AptValue *AptKey::objectMemberLookup(AptValue *const context,const EAStringC *const name)const
{
 const BfmeW1229 *prop=context&&static_cast<unsigned char>(reinterpret_cast<BfmeAptValue006DCD20 *>(context)->isKey())?bfmeFind1229(name->rva00620090(),name->rva006D3750()):0;
 if(prop) {
  switch(prop->value) {
case 1:return AptInteger::Create(8);
case 2:return AptInteger::Create(20);
case 3:return AptInteger::Create(17);
case 4:return AptInteger::Create(46);
case 5:return AptInteger::Create(40);
case 6:return AptInteger::Create(35);
case 7:return AptInteger::Create(13);
case 8:return AptInteger::Create(27);
case 9:return AptInteger::Create(36);
case 10:return AptInteger::Create(45);
case 11:return AptInteger::Create(37);
case 12:return AptInteger::Create(34);
case 13:return AptInteger::Create(33);
case 14:return AptInteger::Create(39);
case 15:return AptInteger::Create(16);
case 16:return AptInteger::Create(32);
case 17:return AptInteger::Create(9);
case 18:return AptInteger::Create(38);
case 100:
   if(!g_rva008A47B0_0) {
    g_rva008A47B0_0=reinterpret_cast<Rva008A47B0Item *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_isDown)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A47B0_0)->setGCRootCount(1);
    g_rva008A47B0_0->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A47B0_0);
case 101:
   if(!g_rva008A47B0_1) {
    g_rva008A47B0_1=reinterpret_cast<Rva008A47B0Item *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_isToggled)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A47B0_1)->setGCRootCount(1);
    g_rva008A47B0_1->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A47B0_1);
case 102:
   if(!g_rva008A47B0_2) {
    g_rva008A47B0_2=reinterpret_cast<Rva008A47B0Item *>(new Rva006D6500(reinterpret_cast<int>(&aptKeyValue)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A47B0_2)->setGCRootCount(1);
    g_rva008A47B0_2->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A47B0_2);
case 103:
   if(!g_rva008A47B0_3) {
    g_rva008A47B0_3=reinterpret_cast<Rva008A47B0Item *>(new Rva006D6500(reinterpret_cast<int>(&aptPackedKeyFieldAt008A5360)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A47B0_3)->setGCRootCount(1);
    g_rva008A47B0_3->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A47B0_3);
case 104:
   if(!g_rva008A47B0_4) {
    g_rva008A47B0_4=reinterpret_cast<Rva008A47B0Item *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_addListener)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A47B0_4)->setGCRootCount(1);
    g_rva008A47B0_4->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A47B0_4);
case 105:
   if(!g_rva008A47B0_5) {
    g_rva008A47B0_5=reinterpret_cast<Rva008A47B0Item *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_removeListener)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A47B0_5)->setGCRootCount(1);
    g_rva008A47B0_5->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A47B0_5);
case 106:
   if(!g_rva008A47B0_6) {
    g_rva008A47B0_6=reinterpret_cast<Rva008A47B0Item *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getAnalogStickInfo)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A47B0_6)->setGCRootCount(1);
    g_rva008A47B0_6->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A47B0_6);
case 107:
   if(!g_rva008A47B0_7) {
    g_rva008A47B0_7=reinterpret_cast<Rva008A47B0Item *>(new Rva006D6500(reinterpret_cast<int>(&aptKeyCode)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A47B0_7)->setGCRootCount(1);
    g_rva008A47B0_7->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A47B0_7);
  }
 }
 return 0;
}

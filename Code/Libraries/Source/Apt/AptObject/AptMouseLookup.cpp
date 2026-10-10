// cl: /O2 /MD /EHsc
// Source guide31ceb5bf2d6e4f60 AptMiscObjects.cpp (later APT); WB177C7D0
// independently names lookup and native literal dispatch identifies callbacks.
// Existing canonical Apt base types, native tagged providers and data owners
// are retained; the animation/listener prefix remains a scoped receiver view.
#include "AptScriptFunction.h"
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
class Rva006E34D0 {public:unsigned char unaccessed00[0x20];AptValueSet<AptValue *> listenerSet;};
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
class AptMouse : public AptObject {
public:
 virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const)const;
 static AptValue *sMethod_addListener(AptValue *,int);
 static AptValue *sMethod_removeListener(AptValue *,int);
};
AptValue *AptMouse::sMethod_addListener(AptValue *,int nParams)
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
AptValue *AptMouse::sMethod_removeListener(AptValue *,int nParams)
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
AptValue *AptMouse::objectMemberLookup(AptValue *const,const EAStringC *const name)const
{
 if(reinterpret_cast<Rva008A4570Owner *>(const_cast<EAStringC *>(name))->nameEquals("addListener")) {
  if(!g_bfmeC1062) {
   g_bfmeC1062=reinterpret_cast<BfmeC1062 *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_addListener)));
   reinterpret_cast<BfmeAptValue006DCD20 *>(g_bfmeC1062)->setGCRootCount(1);
   g_bfmeC1062->bfmeSlot1062C_0();
  }
  return reinterpret_cast<AptValue *>(g_bfmeC1062);
 } else if(reinterpret_cast<Rva008A4570Owner *>(const_cast<EAStringC *>(name))->nameEquals("removeListener")) {
  if(!g_bfmeD1062) {
   g_bfmeD1062=reinterpret_cast<BfmeC1062 *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_removeListener)));
   reinterpret_cast<BfmeAptValue006DCD20 *>(g_bfmeD1062)->setGCRootCount(1);
   g_bfmeD1062->bfmeSlot1062C_0();
  }
  return reinterpret_cast<AptValue *>(g_bfmeD1062);
 }
 return 0;
}

// cl: /O2 /DNDEBUG /MD /EHsc
// Native 6EDBD0..6EDF11 RET0; following15CC bytes are padding.
// AptCharacter callback: resolves a depth/CIH/name argument then swaps the
// two17-bit signed depths and relinks the parent's display list. Actual
// query/unlink/insert providers and parent+48/instance+4C layout are shared
// with AptCharacterByteCounts.cpp and AptDisplayList.cpp. Original callback
// name is not asserted. Preserve native's unusual count/CIH guard polarity.
// The sprite() assert break is __asm int 3 (the owner AptCharacter units'
// spelling): the __debugbreak intrinsic plus barriers left the body 0.99.
class EAStringC {
public:class StringDataC {public:unsigned short refs,size,capacity,hash;};
private:StringDataC *data;
public:EAStringC();~EAStringC();
};
extern EAStringC::StringDataC g_eaEmptyStringData;
__declspec(noinline) inline EAStringC::EAStringC() {
 data=&g_eaEmptyStringData;++data->refs;
}
class AptValue {public:bool getIsDefined() const;void toString(EAStringC &)const;};
class BfmeAptValue006DCD20 {public:
 bool isCIH(bool)const;int isString()const;int isInteger()const;
 BfmeAptValue006DCD20 *rva006DCF60(bool);int toInteger()const;
};
class AptBasePtrStack {public:BfmeAptValue006DCD20 *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;};
extern AptActionInterpreter g_aptDateInterpreter;
extern AptValue *gpUndefinedValue;
class AptCIH;
class BfmeQuery1279 {public:void bfmeQuery1279(int,int,void **,void **);void rva006F6FB0(int,AptCIH *);};
struct SwapSprite {char pad[0x24];BfmeQuery1279 *list;};
class AptCIH {
public:
 virtual void slot0();virtual void changed();
 char pad04[0x44];AptCIH *parent;SwapSprite *instance;char pad50[8];
 signed int depth:17;unsigned int flags17:15;
 void *rva006CFF40()const;
};
class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline SwapSprite *sprite(AptCIH *aptCIH) {
 if(!((Rva006CFCD0 *)aptCIH)->isSpriteInstBase()) {
  g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7d);
  if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
 return aptCIH->instance;
}
class BfmeNestedBE;
BfmeNestedBE *bfmeUnlinkNestedBE(BfmeNestedBE *);
AptValue *Rva006EDBD0SwapDepths(AptValue *self,int count) {
 if(count!=1 && ((BfmeAptValue006DCD20 *)self)->isCIH(false))return gpUndefinedValue;
 AptCIH *cih=(AptCIH*)((BfmeAptValue006DCD20*)self)->rva006DCF60(false);
 BfmeAptValue006DCD20 *arg=g_aptDateInterpreter.stack.At(0);
 AptCIH *other=0;void *previous=0;
 if(arg->isCIH(false))other=(AptCIH *)arg->rva006DCF60(false);
 else if((unsigned char)arg->isString()) {
  EAStringC name;
  ((AptValue*)arg)->toString(name);
  sprite(cih->parent)->list->bfmeQuery1279(0,(int)&name,&previous,(void **)&other);
 } else if((unsigned char)arg->isInteger()) {
  ((SwapSprite*)cih->parent->rva006CFF40())->list->bfmeQuery1279(arg->toInteger(),0,&previous,(void **)&other);
 }
 if(other && ((AptValue*)other)->getIsDefined()) {
  int depth=((AptCIH*)((BfmeAptValue006DCD20*)other)->rva006DCF60(false))->depth;
  ((AptCIH*)((BfmeAptValue006DCD20*)other)->rva006DCF60(false))->depth=cih->depth;
  cih->depth=depth;
  sprite(cih->parent);bfmeUnlinkNestedBE((BfmeNestedBE*)other);
  sprite(cih->parent);bfmeUnlinkNestedBE((BfmeNestedBE*)cih);
  sprite(cih->parent)->list->rva006F6FB0(cih->depth,cih);
  sprite(cih->parent)->list->rva006F6FB0(other->depth,other);
  cih->changed();other->changed();
 } else if((unsigned char)arg->isInteger()) {
  sprite(cih->parent);bfmeUnlinkNestedBE((BfmeNestedBE*)cih);
  sprite(cih->parent)->list->rva006F6FB0(arg->toInteger(),cih);
  cih->changed();
 }
 return gpUndefinedValue;
}

// cl: /O2 /MD /D_CRTIMP= /EHsc
// AptArray default constructor: target InitArray702860 allocates44B and calls
// 6D91B0. Native ctor103B sets type22, native hash+8, array vtableCEA778,
// capacity+24, pointer+20 and length+28. Existing array accessors independently
// confirm these fields; later AptArray.cpp4416f7dfadc1781e supplies initializer
// order. Original AptValue.h504032fc6593aab6 gives protected value constructors.
// Reuse canonical base layouts. Inline base initializers reproduce the target
// compiler's inlining, including the temporary native-hash-base vtable store.
#include "AptScriptFunction.h"
// ?AptValueGC::AptValueGC present-unmatched
inline AptValueGC::AptValueGC(AptVirtualFunctionTable_Indices type) : AptValue(type) {}
// ?AptValueWithHash::AptValueWithHash present-unmatched
inline AptValueWithHash::AptValueWithHash(AptVirtualFunctionTable_Indices type,int n) : AptValueGC(type),mNativeHash(n) {}
// ?AptObject::AptObject present-unmatched
inline AptObject::AptObject(AptVirtualFunctionTable_Indices type,int n) : AptValueWithHash(type,n)
{
    mnImplementedObjects=0;
    mbHasClass=0;
    mbIsInMainInst=0;
}
#include "../Rva006D2A60.h"
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
extern AptValue *gpUndefinedValue;
class AptArray : public AptObject {
public:
    AptArray();
    void set(int,AptValue*);
    void _reserve(int);
    void toString(EAStringC &,const char * = ",");
    void rva006DA590(char *out,const char *szSeparator);
    void SetAt(int,AptValue*);
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static AptValue *sMethod_concat(AptValue *,int);
    static AptValue *sMethod_join(AptValue *,int);
    static AptValue *sMethod_pop(AptValue *,int);
    static AptValue *sMethod_push(AptValue *,int);
    static AptValue *sMethod_shift(AptValue *,int);
    static AptValue *sMethod_unshift(AptValue *,int);
    static AptValue *sMethod_reverse(AptValue *,int);
    static AptValue *sMethod_sort(AptValue *,int);
    static AptValue *sMethod_splice(AptValue *,int);
    static AptValue *sMethod_slice(AptValue *,int);
    static AptValue *sMethod_sortOn(AptValue *,int);

    AptValue *At(int);
    AptValue *get(int i) { if(i>=0 && i<mnLength) { AptValue *aptValue=At(i); if(!aptValue) aptValue=gpUndefinedValue; return aptValue; } return gpUndefinedValue; }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
    virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const) const;
    virtual bool objectMemberSet(AptValue *const,const EAStringC *const,AptValue *const);
    virtual void RegisterReferences() const;
    virtual void DestroyGCPointers();
protected:
    virtual ~AptArray();
private:
    AptValue **mpValues;
    int mnCapacity,mnLength;
};

typedef char AptArrayNativeSize[sizeof(AptArray)==44?1:-1];

// Native CEA778 slots and existing matched providers establish these exact
// ABI bindings; folded leaf providers retain their existing repository names.
#pragma comment(linker, "/alternatename:?GetNativeHashVirtual@AptValueWithHash@@UAEPAUAptNativeHash@@XZ=?GetData@AptValueVector@@QAEPAPAPAVAptValue@@XZ")
#pragma comment(linker, "/alternatename:?ContainsNativeHashVirtual@AptValueWithHash@@UBE_NXZ=?do_always_noconv@?$codecvt@DDH@_STL@@MBE_NXZ")
#pragma comment(linker, "/alternatename:?getHasClass@AptObject@@UBEHXZ=?getBit8@Rva008993E0Owner@@QAEHXZ")
#pragma comment(linker, "/alternatename:?setHasClass@AptObject@@UAEXH@Z=?setBit8@Rva008993E0Owner@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?DeleteThis@AptValue@@UAEXXZ=?rva006CBCF0@Rva006CBCF0@@QAEXXZ")
#pragma comment(linker, "/alternatename:?PreDestroy@AptValue@@UAEXXZ=?DX8_Assert@@YAXXZ")
#pragma comment(linker, "/alternatename:?IsGarbageCollected@AptValueGC@@UBE_NXZ=?do_always_noconv@?$codecvt@DDH@_STL@@MBE_NXZ")

// Lookup6DA630: vtableCEA778 slot7; donor4416f7dfadc1781e AptArray.cpp.
// Target13-entry table follows the1892B body at6DAD94; all destinations checked.
// Native numeric fallback omits the later donor context recheck. Native assert
// line486 and conditional int3 retain existing compiler-barrier convention.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
// Historical ledger identity is retained; object-symbol names this exact provider.
// ?rva006D95E0@BfmeAptValue006DCD20@@QAEXHPAV1@@Z
inline void AptArray::set(int nIndex,AptValue *value) {
 if(nIndex<0)return;
 int newLength=nIndex+1;
 _reserve(newLength);
 if(!(nIndex<mnCapacity)) {
  g_bfmeAptAssertAtE17734("nIndex < mnCapacity","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp",0x10c);
  if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
 }
 SetAt(nIndex,value);
 mnLength=newLength>mnLength?newLength:mnLength;
}

#include "../EAStringC.h"
class AptInteger { public: static AptValue *Create(int); int GetInt() const; };
struct R4Word { const char *name; int nIndex; };
const R4Word *Rva008B8AD0(const char *,unsigned int);
// Existing shutdown6D92E0 owns these11 zero-initialized cached method slots.
// Their original pointer declarations preserve linker identity; each slot holds
// the native function object constructed here, so the reference view is exact.
class Rva008B8B80Releasable;
class AptNativeFunction : public AptObject {
    friend class AptValue;
    void *callback;
public:
    AptNativeFunction(AptValue *(__cdecl *)(AptValue *,int));
    void setGCRootCount(unsigned int);
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); }
};
typedef char AptNativeFunctionNativeSize[sizeof(AptNativeFunction)==36?1:-1];
void Rva006CC110Log(int,const char *,...);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
#include <stdlib.h>
extern Rva008B8B80Releasable *g_rva008B8B80_0;
#define psMethod_concat ((AptNativeFunction *&)g_rva008B8B80_0)
extern Rva008B8B80Releasable *g_rva008B8B80_1;
#define psMethod_join ((AptNativeFunction *&)g_rva008B8B80_1)
extern Rva008B8B80Releasable *g_rva008B8B80_2;
#define psMethod_pop ((AptNativeFunction *&)g_rva008B8B80_2)
extern Rva008B8B80Releasable *g_rva008B8B80_3;
#define psMethod_push ((AptNativeFunction *&)g_rva008B8B80_3)
extern Rva008B8B80Releasable *g_rva008B8B80_4;
#define psMethod_shift ((AptNativeFunction *&)g_rva008B8B80_4)
extern Rva008B8B80Releasable *g_rva008B8B80_5;
#define psMethod_unshift ((AptNativeFunction *&)g_rva008B8B80_5)
extern Rva008B8B80Releasable *g_rva008B8B80_6;
#define psMethod_reverse ((AptNativeFunction *&)g_rva008B8B80_6)
extern Rva008B8B80Releasable *g_rva008B8B80_7;
#define psMethod_sort ((AptNativeFunction *&)g_rva008B8B80_7)
extern Rva008B8B80Releasable *g_rva008B8B80_8;
#define psMethod_splice ((AptNativeFunction *&)g_rva008B8B80_8)
extern Rva008B8B80Releasable *g_rva008B8B80_9;
#define psMethod_slice ((AptNativeFunction *&)g_rva008B8B80_9)
extern Rva008B8B80Releasable *g_rva008B8B80_10;
#define psMethod_sortOn ((AptNativeFunction *&)g_rva008B8B80_10)
#define DISPATCH(n) if(!psMethod_##n) { psMethod_##n=new AptNativeFunction(sMethod_##n); psMethod_##n->setGCRootCount(1); psMethod_##n->AddRef(); } return psMethod_##n;
AptValue *AptArray::objectMemberLookup(AptValue *const context,const EAStringC *const name) const {
 const R4Word *prop=context?Rva008B8AD0(name->rva00620090(),name->rva006D3750()):0;
 if(prop) switch(prop->nIndex) {
 case 1:return AptInteger::Create(mnLength);
 case 2:DISPATCH(concat);break;
 case 3:DISPATCH(join);break;
 case 13:DISPATCH(join);break;
 case 4:DISPATCH(pop);break;
 case 5:DISPATCH(push);break;
 case 6:DISPATCH(shift);break;
 case 7:DISPATCH(unshift);break;
 case 8:DISPATCH(reverse);break;
 case 9:DISPATCH(sort);break;
 case 10:DISPATCH(splice);break;
 case 11:DISPATCH(slice);break;
 case 12:DISPATCH(sortOn);break;
 }
 if(name->rva006D3510("length") || name->rva006D3510("concat") || name->rva006D3510("join") || name->rva006D3510("pop") || name->rva006D3510("push") || name->rva006D3510("shift") || name->rva006D3510("unshift") || name->rva006D3510("reverse") || name->rva006D3510("sort") || name->rva006D3510("splice") || name->rva006D3510("slice") || name->rva006D3510("sortOn") || name->rva006D3510("toString")) {
 Rva006CC110Log(3,"AptArray: Incorrect case for '%s'.\n",name->rva00620090());
 g_bfmeAptAssertAtE17734("0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp",0x1e6);
 if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
 }
 char *end=0;
 int index=strtol(name->rva00620090(),&end,10);
 int length=name->rva006D3750();
 if(length>0 && end==name->rva00620090()+length) return context->c_array()->get(index);
 return mNativeHash.Lookup(name);
}

#pragma comment(linker, "/alternatename:?setGCRootCount@AptNativeFunction@@QAEXI@Z=?setGCRootCount@BfmeAptValue006DCD20@@QAEXI@Z")
#pragma comment(linker, "/alternatename:?At@AptArray@@QAEPAVAptValue@@H@Z=?rva006D8A50@BfmeAptValue006DCD20@@QAEPAV1@H@Z")
#pragma comment(linker, "/alternatename:?sMethod_pop@AptArray@@SAPAVAptValue@@PAV2@H@Z=?Rva006D9B50Pop@@YAPAVBfmeAptValue006DCD20@@PAV1@@Z")
#pragma comment(linker, "/alternatename:?sMethod_unshift@AptArray@@SAPAVAptValue@@PAV2@H@Z=?rva006D9CE0@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z")
#pragma comment(linker, "/alternatename:?sMethod_reverse@AptArray@@SAPAVAptValue@@PAV2@H@Z=?rva006DA130@@YAPAVBfmeAptValue006DCD20@@PAV1@@Z")
#pragma comment(linker, "/alternatename:?sMethod_sort@AptArray@@SAPAVAptValue@@PAV2@H@Z=?rva006D9F00@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z")
#pragma comment(linker, "/alternatename:?sMethod_sortOn@AptArray@@SAPAVAptValue@@PAV2@H@Z=?rva006DA0C0@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z")


#include <string.h>
AptValue *AptArray::sMethod_shift(AptValue *pThis,int nParams) {
 AptValue *result=gpUndefinedValue;
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  if(array->mnLength>0) {
   result=array->get(0);
   --array->mnLength;
   if(array->mnLength) memmove(&array->mpValues[0],&array->mpValues[1],sizeof(AptValue*)*array->mnLength);
   array->mpValues[array->mnLength]=0;
  }
 }
 return result;
}

#pragma comment(linker, "/alternatename:?isArray@AptValue@@QBE_NXZ=?isArray@BfmeAptValue006DCD20@@QBEHXZ")
#pragma comment(linker, "/alternatename:?toInteger@AptValue@@QBEHXZ=?toInteger@BfmeAptValue006DCD20@@QBEHXZ")

#include "../AptBasePtrStack.h"
struct AptActionInterpreter;
extern AptActionInterpreter g_aptDateInterpreter;
#define g_aptValueStackAtE182E0 (*reinterpret_cast<AptBasePtrStack *>(&g_aptDateInterpreter))
AptValue *AptArray::sMethod_slice(AptValue *pThis,int nParams) {
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  AptArray *result=0;
  int start=0,end=array->mnLength;
  if(nParams>0) {start=((AptValue *)g_aptValueStackAtE182E0.At(0))->toInteger();if(start<0)start=array->mnLength+start;}
  if(nParams>1) {end=((AptValue *)g_aptValueStackAtE182E0.At(1))->toInteger();if(end<0)end=array->mnLength+end;else if(end>array->mnLength)end=array->mnLength;}
  if(start>end || start<0 || end<0)return gpUndefinedValue;
  result=new AptArray();
  for(int i=start;i<end;i++)result->set(result->mnLength,array->At(i));
  return result;
 }
 return gpUndefinedValue;
}

#pragma comment(linker, "/alternatename:?rva006D95E0@BfmeAptValue006DCD20@@QAEXHPAV1@@Z=?set@AptArray@@QAEXHPAVAptValue@@@Z")

AptValue *AptArray::sMethod_push(AptValue *pThis,int nParams) {
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  for(int i=0;i<nParams;i++)array->set(array->mnLength,(AptValue *)g_aptValueStackAtE182E0.At(i));
  return AptInteger::Create(array->mnLength);
 }
 return gpUndefinedValue;
}

AptValue *AptArray::sMethod_concat(AptValue *pThis,int nParams) {
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  AptArray *result=new AptArray();
  int i;
  for(i=0;i<array->mnLength;i++)result->set(result->mnLength,array->At(i));
  for(i=0;i<nParams;i++) {
   AptValue *value=(AptValue *)g_aptValueStackAtE182E0.At(i);
   if(value->isArray()) {
    AptArray *other=value->c_array();
    for(int j=0;j<other->mnLength;j++)result->set(result->mnLength,other->At(j));
   } else result->set(result->mnLength,value);
  }
  return result;
 }
 return gpUndefinedValue;
}

#pragma comment(linker, "/alternatename:?_reserve@AptArray@@QAEXH@Z=?rva006D9500@Rva006D9500@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?SetAt@AptArray@@QAEXHPAVAptValue@@@Z=?SetAt@BfmeAptValue006DCD20@@QAEXHPAV1@@Z")

class AptString : public AptValue { public: static AptString *Create(); EAStringC str; };
AptValue *AptArray::sMethod_join(AptValue *pThis,int nParams) {
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  EAStringC buffer;
  EAStringC separator;
  if(nParams>0) {((AptValue *)g_aptValueStackAtE182E0.At(0))->toString(separator);array->toString(buffer,separator.rva00620090());}
  else array->toString(buffer);
  AptString *result=AptString::Create();
  result->str=buffer;
  return result;
 }
 return gpUndefinedValue;
}

void AptArray::toString(EAStringC &buffer,const char *separator) {
 if(!separator) {
  g_bfmeAptAssertAtE17734("szSeparator","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp",0x16b);
  if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
 }
 buffer="";
 for(int i=0;i<mnLength;i++) {
  AptValue *value=At(i);
  if(value) {EAStringC text;value->toString(text);buffer.Rva006D4F00Append(text);}
  if(i<mnLength-1)buffer.Rva006D50A0Append(separator);
 }
}

// Native500B predates the later donor splice fixes: it returns the original
// array, releases removed elements directly, and does not build a deleted-items
// result or perform the later undefined/negative/bounds checks. Native loops
// independently establish these differences; keep target behavior unchanged.
AptValue *AptArray::sMethod_splice(AptValue *pThis,int nParams) {
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  if(nParams>0) {
   int start=((AptValue *)g_aptValueStackAtE182E0.At(0))->toInteger();
   if(start<0)start=array->mnLength+start;
   int count=array->mnLength-start;
   if(nParams>1)count=((AptValue *)g_aptValueStackAtE182E0.At(1))->toInteger();
   if(count>array->mnLength-start)count=array->mnLength-start;
   if(start>=array->mnLength)count=0;
   int i;
   for(i=0;i<count;i++) {AptValue *aptValue=array->At(start+i);if(aptValue)aptValue->Release();}
   memmove(&array->mpValues[start],&array->mpValues[start+count],sizeof(AptValue*)*(array->mnLength-count-start));
   for(i=0;i<count;i++)array->mpValues[array->mnLength-count+i]=0;
   array->mnLength-=count;
   if(nParams>2) {
    int added=nParams-2;
    array->_reserve(array->mnLength+added);
    memmove(&array->mpValues[start+added],&array->mpValues[start],sizeof(AptValue*)*(array->mnLength-start));
    array->mnLength+=added;
    for(i=0;i<added;i++) {
     array->mpValues[start+i]=0;
     array->set(start+i,(AptValue *)g_aptValueStackAtE182E0.At(i+2));
    }
   }
   return pThis;
  }
  return gpUndefinedValue;
 }
 return gpUndefinedValue;
}

class AptBoolean : public AptValue { public: bool GetBool() const; };
#include "../AptFloat.h"
class AptDate : public AptObject { public: void toString(EAStringC &); };
class AptError : public AptObject { public: EAStringC msMessage; };
#include "../AptActionInterpreter.h"
EAStringC *Rva0070B4F0GetString(int);
#include <stdio.h>
#include <math.h>
#pragma intrinsic(fmod)
static __forceinline float apt_fmodf(float x,float y) { return (float)fmod(x,y); }
// Source lead230e7c503b5dbf7e AptValue.cpp; native1430B6DD6C0..6DDC56.
// Native45-tag map and22-entry table independently establish every numeric case
// below; original donor enum numbering differs after type11. Older native code
// clears undefined unconditionally, formats native callback addresses, and
// directly delegates CIH names. Float rounding matches the native fst temporary.
void AptValue::toString(EAStringC &sBuf) const {
 if(isUndefined()) {sBuf.rva006D3470();return;}
 char szTemp[128];
 switch(((int)mnValueData)>>25) {
 case 1:case 42:sBuf=c_string()->str;break;
 case 5:if(((AptBoolean*)this)->GetBool())sBuf=*Rva0070B4F0GetString(168);else sBuf=*Rva0070B4F0GetString(52);break;
 case 7:sprintf(szTemp,"%d",((AptInteger*)this)->GetInt());sBuf=szTemp;break;
 case 6:{AptFloat *pF=(AptFloat*)this;if(apt_fmodf(pF->GetFloat(),1.f)==0.f)sprintf(szTemp,"%d",(int)pF->GetFloat());else sprintf(szTemp,"%f",pF->GetFloat());sBuf=szTemp;break;}
 case 22:{AptArray *pA=c_array();pA->toString(sBuf);break;}
 case 21:sBuf="[sound]";break;
 case 9:sprintf(szTemp,"[native function 0x%08x]",c_nativefunction()->callback);sBuf=szTemp;break;
 case 43:case 44:case 45:sBuf="[function]";break;
 case 23:case 24:case 25:case 26:case 27:case 31:case 35:case 36:case 39:sBuf="[object Object]";break;
 case 32:case 33:case 34:sBuf="[object]";break;
 case 28:sBuf="[object (prototype)]";break;
 case 29:{AptDate *pA=c_date();pA->toString(sBuf);break;}
 case 30:sBuf="[MovieClip]";break;
 case 4:sBuf="[Register]";break;
 case 8:sBuf="[Lookup]";break;
 case 11:sBuf="[Extern]";break;
 case 20:sBuf="[FrameStack]";break;
 case 37:sBuf="[Extension]";break;
 case 38:sBuf="[GlobalExtension]";break;
 case 41:sBuf=((AptError*)this)->msMessage;break;
 case 13:case 14:case 15:case 18:case 19:AptActionInterpreter::getName(c_cih(),sBuf);break;
 default:sprintf(szTemp,"[Type=0x%X]",((int)mnValueData)>>25);sBuf=szTemp;break;
 }
}

#pragma comment(linker, "/alternatename:?c_nativefunction@AptValue@@QBEPAVAptNativeFunction@@XZ=?rva006DCF20@BfmeAptValue006DCD20@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:?c_date@AptValue@@QBEPAVAptDate@@XZ=?rva006DD160@BfmeAptValue006DCD20@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:?c_cih@AptValue@@QBEPAVAptCIH@@_N@Z=?rva006DCF60@BfmeAptValue006DCD20@@QAEPAV1@_N@Z")
#pragma comment(linker, "/alternatename:?GetFloat@AptFloat@@QBEMXZ=?get@Rva00723490FloatField@@QBEMXZ")
#pragma comment(linker, "/alternatename:?getName@AptActionInterpreter@@SAXPAVAptCIH@@AAVEAStringC@@@Z=?rva006ffce0@@YAXPAVAptValue@@AAVEAStringC@@@Z")
#pragma comment(linker, "/alternatename:?rva006DD6C0@BfmeAptValue006DCD20@@QAEXPAVEAStringC@@@Z=?toString@AptValue@@QBEXAAVEAStringC@@@Z")
#pragma comment(linker, "/alternatename:?rva006DD6C0@BfmeAptValue006DCD20@@QAEXAAVEAStringC@@@Z=?toString@AptValue@@QBEXAAVEAStringC@@@Z")

// Native6DA590..6DA62D: Ghidra-unlisted C-buffer join. Asserts szSeparator
// (AptArray.cpp 0x14D, retail texts), joins through the rowed
// toString(EAStringC&,const char*) into a local string and copies its text
// into the caller's buffer with the intrinsic strcpy. Address-derived name.
#pragma intrinsic(strcpy)
void AptArray::rva006DA590(char *out,const char *szSeparator) {
 if(!szSeparator) {
  g_bfmeAptAssertAtE17734("szSeparator","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptArray.cpp",0x14d);
  if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
 }
 EAStringC text;
 toString(text,szSeparator);
 strcpy(out,text.rva00620090());
}

// cl: /O2 /MD /EHsc
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
class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *,int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
extern AptValue *gpUndefinedValue;
class AptArray : public AptObject {
public:
    AptArray();
    void set(int,AptValue*);
    void _reserve(int);
    void toString(EAStringC &,const char * = ",");
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
    AptValue *get(int i) { if(i>=0 && i<mnLength) { AptValue *v=At(i); if(!v) v=gpUndefinedValue; return v; } return gpUndefinedValue; }
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
AptArray::AptArray() : AptObject((AptVirtualFunctionTable_Indices)22)
{
    mnCapacity=0;
    mpValues=0;
    mnLength=0;
}

#pragma comment(linker, "/alternatename:??0AptValue@@IAE@W4AptVirtualFunctionTable_Indices@@@Z=??0BfmeAptValue006DCD20@@QAE@H@Z")
typedef char AptArrayNativeSize[sizeof(AptArray)==44?1:-1];

// Native CEA778 slots and existing matched providers establish these exact
// ABI bindings; folded leaf providers retain their existing repository names.
#pragma comment(linker, "/alternatename:??1AptArray@@MAE@XZ=??1Rva006DA560@@UAE@XZ")
#pragma comment(linker, "/alternatename:?GetNativeHashVirtual@AptValueWithHash@@UAEPAUAptNativeHash@@XZ=?GetData@AptValueVector@@QAEPAPAPAVAptValue@@XZ")
#pragma comment(linker, "/alternatename:?ContainsNativeHashVirtual@AptValueWithHash@@UBE_NXZ=?do_always_noconv@?$codecvt@DDH@_STL@@MBE_NXZ")
#pragma comment(linker, "/alternatename:?getHasClass@AptObject@@UBEHXZ=?getBit8@Rva008993E0Owner@@QAEHXZ")
#pragma comment(linker, "/alternatename:?setHasClass@AptObject@@UAEXH@Z=?setBit8@Rva008993E0Owner@@QAEXH@Z")
#pragma comment(linker, "/alternatename:?objectMemberSet@AptArray@@UAE_NQAVAptValue@@QBVEAStringC@@0@Z=?rva006D9780@BfmeAptValue006DCD20@@QAE_NPAV1@PAVEAStringC@@0@Z")
#pragma comment(linker, "/alternatename:?DeleteThis@AptValue@@UAEXXZ=?rva006CBCF0@Rva006CBCF0@@QAEXXZ")
#pragma comment(linker, "/alternatename:?PreDestroy@AptValue@@UAEXXZ=?DX8_Assert@@YAXXZ")
#pragma comment(linker, "/alternatename:?DestroyGCPointers@AptArray@@UAEXXZ=?rva006D93D0@BfmeAptValue006DCD20@@QAEXXZ")
#pragma comment(linker, "/alternatename:?IsGarbageCollected@AptValueGC@@UBE_NXZ=?do_always_noconv@?$codecvt@DDH@_STL@@MBE_NXZ")
#pragma comment(linker, "/alternatename:?RegisterReferences@AptArray@@UBEXXZ=?rva006D94A0@BfmeAptValue006DCD20@@QAEXXZ")

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

class EAStringC { void *mpData; public: EAStringC(const char *); EAStringC &Rva006D4F00Append(const EAStringC &); EAStringC &Rva006D50A0Append(const char *); EAStringC(); ~EAStringC(); EAStringC &operator=(const EAStringC &); unsigned int rva006D3750() const; const char *rva00620090() const; bool rva006D3510(const char *) const; };
class AptInteger { public: static AptValue *Create(int); };
struct R4Word { const char *name; int nIndex; };
const R4Word *Rva008B8AD0(const char *,unsigned int);
// Existing shutdown6D92E0 owns these11 zero-initialized cached method slots.
// Their original pointer declarations preserve linker identity; each slot holds
// the native function object constructed here, so the reference view is exact.
class Rva008B8B80Releasable;
class AptNativeFunction : public AptObject {
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
extern "C" long __cdecl strtol(const char *,char **,int);
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

#pragma comment(linker, "/alternatename:??0AptNativeFunction@@QAE@P6APAVAptValue@@PAV1@H@Z@Z=??0Rva006D6500@@QAE@H@Z")
#pragma comment(linker, "/alternatename:?setGCRootCount@AptNativeFunction@@QAEXI@Z=?setGCRootCount@BfmeAptValue006DCD20@@QAEXI@Z")
#pragma comment(linker, "/alternatename:?At@AptArray@@QAEPAVAptValue@@H@Z=?rva006D8A50@BfmeAptValue006DCD20@@QAEPAV1@H@Z")
#pragma comment(linker, "/alternatename:?sMethod_pop@AptArray@@SAPAVAptValue@@PAV2@H@Z=?Rva006D9B50Pop@@YAPAVBfmeAptValue006DCD20@@PAV1@@Z")
#pragma comment(linker, "/alternatename:?sMethod_unshift@AptArray@@SAPAVAptValue@@PAV2@H@Z=?rva006D9CE0@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z")
#pragma comment(linker, "/alternatename:?sMethod_reverse@AptArray@@SAPAVAptValue@@PAV2@H@Z=?rva006DA130@@YAPAVBfmeAptValue006DCD20@@PAV1@@Z")
#pragma comment(linker, "/alternatename:?sMethod_sort@AptArray@@SAPAVAptValue@@PAV2@H@Z=?rva006D9F00@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z")
#pragma comment(linker, "/alternatename:?sMethod_sortOn@AptArray@@SAPAVAptValue@@PAV2@H@Z=?rva006DA0C0@@YAPAVBfmeAptValue006DCD20@@PAV1@H@Z")

#pragma comment(linker, "/alternatename:?Lookup@AptNativeHash@@QBEPAVAptValue@@QBVEAStringC@@@Z=?lookup@Rva0070B380@@QAEPAXABVEAStringC@@@Z")

extern "C" void *__cdecl memmove(void *,const void *,unsigned int);
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

class AptBasePtrStack { public: AptValue *At(int); int count,capacity; AptValue **values; };
extern AptBasePtrStack g_aptValueStackAtE182E0;
AptValue *AptArray::sMethod_slice(AptValue *pThis,int nParams) {
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  AptArray *result=0;
  int start=0,end=array->mnLength;
  if(nParams>0) {start=g_aptValueStackAtE182E0.At(0)->toInteger();if(start<0)start=array->mnLength+start;}
  if(nParams>1) {end=g_aptValueStackAtE182E0.At(1)->toInteger();if(end<0)end=array->mnLength+end;else if(end>array->mnLength)end=array->mnLength;}
  if(start>end || start<0 || end<0)return gpUndefinedValue;
  result=new AptArray();
  for(int i=start;i<end;i++)result->set(result->mnLength,array->At(i));
  return result;
 }
 return gpUndefinedValue;
}

#pragma comment(linker, "/alternatename:?At@AptBasePtrStack@@QAEPAVAptValue@@H@Z=?At@AptBasePtrStack@@QAEPAVBfmeAptValue006DCD20@@H@Z")
#pragma comment(linker, "/alternatename:?rva006D95E0@BfmeAptValue006DCD20@@QAEXHPAV1@@Z=?set@AptArray@@QAEXHPAVAptValue@@@Z")
#pragma comment(linker, "/alternatename:?g_aptValueStackAtE182E0@@3VAptBasePtrStack@@A=?g_aptDateInterpreter@@3UAptActionInterpreter@@A")

AptValue *AptArray::sMethod_push(AptValue *pThis,int nParams) {
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  for(int i=0;i<nParams;i++)array->set(array->mnLength,g_aptValueStackAtE182E0.At(i));
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
   AptValue *value=g_aptValueStackAtE182E0.At(i);
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
#pragma comment(linker, "/alternatename:?SetAt@AptArray@@QAEXHPAVAptValue@@@Z=?rva006D8AD0@BfmeAptValue006DCD20@@QAEXHPAV1@@Z")

class AptString : public AptValue { public: static AptString *Create(); EAStringC str; };
AptValue *AptArray::sMethod_join(AptValue *pThis,int nParams) {
 if(pThis->isArray()) {
  AptArray *array=pThis->c_array();
  EAStringC buffer;
  EAStringC separator;
  if(nParams>0) {g_aptValueStackAtE182E0.At(0)->toString(separator);array->toString(buffer,separator.rva00620090());}
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
   int start=g_aptValueStackAtE182E0.At(0)->toInteger();
   if(start<0)start=array->mnLength+start;
   int count=array->mnLength-start;
   if(nParams>1)count=g_aptValueStackAtE182E0.At(1)->toInteger();
   if(count>array->mnLength-start)count=array->mnLength-start;
   if(start>=array->mnLength)count=0;
   int i;
   for(i=0;i<count;i++) {AptValue *v=array->At(start+i);if(v)v->Release();}
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
     array->set(start+i,g_aptValueStackAtE182E0.At(i+2));
    }
   }
   return pThis;
  }
  return gpUndefinedValue;
 }
 return gpUndefinedValue;
}

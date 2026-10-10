// cl: /O2 /MD /EHsc
// EA04ceaafc750a5cb1 supplies37 named Date cases; WB178BE20 independently
// names lookup and native classifier/cache/callback dispatch proves each member.
// Whole5056B includes37 target entries6F643C..6F64D0. Existing getTime
// also serves setTime; UTC retains the actual neutral undefined getter provider.
// No new callback alias or body is asserted. This caller-only Date interface is
// never constructed; the original full Date layout is not needed or claimed.
// The37 cache fields reuse the owned plain-data view from AptDate.cpp.
class AptValue {public:virtual void AddRef();virtual void Release();};
class EAStringC {void *data;public:const char *rva00620090()const;unsigned int rva006D3750()const;bool rva006D3510(const char *)const;};
class BfmeAptValue006DCD20 {public:void setGCRootCount(unsigned int);};
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void *,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6500 {unsigned char storage[36];public:Rva006D6500(int);static void *operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}};
struct R4Word {const char *name;int value;};
const R4Word *Rva008B60B0(const char *,unsigned int);
int Rva006F5100Get();
void Rva006CC110Log(int,const char *,...);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
struct AptDateNativeCache {
    AptValue *getDate;
    AptValue *getDay;
    AptValue *getFullYear;
    AptValue *getHours;
    AptValue *getMilliseconds;
    AptValue *getMinutes;
    AptValue *getMonth;
    AptValue *getSeconds;
    AptValue *getTime;
    AptValue *getTimezoneOffset;
    AptValue *getUTCDate;
    AptValue *getUTCDay;
    AptValue *getUTCFullYear;
    AptValue *getUTCHours;
    AptValue *getUTCMilliseconds;
    AptValue *getUTCMinutes;
    AptValue *getUTCMonth;
    AptValue *getUTCSeconds;
    AptValue *getYear;
    AptValue *setDate;
    AptValue *setFullYear;
    AptValue *setHours;
    AptValue *setMilliseconds;
    AptValue *setMinutes;
    AptValue *setMonth;
    AptValue *setSeconds;
    AptValue *setTime;
    AptValue *setUTCDate;
    AptValue *setUTCFullYear;
    AptValue *setUTCHours;
    AptValue *setUTCMilliseconds;
    AptValue *setUTCMinutes;
    AptValue *setUTCMonth;
    AptValue *setUTCSeconds;
    AptValue *setYear;
    AptValue *toString;
    AptValue *UTC;
};
extern AptDateNativeCache g_aptDateNativeCache;
class AptDate {public:
 virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const)const;
 static AptValue *sMethod_getDate(AptValue *,int);
 static AptValue *sMethod_getDay(AptValue *,int);
 static AptValue *sMethod_getFullYear(AptValue *,int);
 static AptValue *sMethod_getHours(AptValue *,int);
 static AptValue *sMethod_getMilliseconds(AptValue *,int);
 static AptValue *sMethod_getMinutes(AptValue *,int);
 static AptValue *sMethod_getMonth(AptValue *,int);
 static AptValue *sMethod_getSeconds(AptValue *,int);
 static AptValue *sMethod_getTime(AptValue *,int);
 static AptValue *sMethod_getTimezoneOffset(AptValue *,int);
 static AptValue *sMethod_getUTCDate(AptValue *,int);
 static AptValue *sMethod_getUTCDay(AptValue *,int);
 static AptValue *sMethod_getUTCFullYear(AptValue *,int);
 static AptValue *sMethod_getUTCHours(AptValue *,int);
 static AptValue *sMethod_getUTCMilliseconds(AptValue *,int);
 static AptValue *sMethod_getUTCMinutes(AptValue *,int);
 static AptValue *sMethod_getUTCMonth(AptValue *,int);
 static AptValue *sMethod_getUTCSeconds(AptValue *,int);
 static AptValue *sMethod_getYear(AptValue *,int);
 static AptValue *sMethod_setDate(AptValue *,int);
 static AptValue *sMethod_setFullYear(AptValue *,int);
 static AptValue *sMethod_setHours(AptValue *,int);
 static AptValue *sMethod_setMilliseconds(AptValue *,int);
 static AptValue *sMethod_setMinutes(AptValue *,int);
 static AptValue *sMethod_setMonth(AptValue *,int);
 static AptValue *sMethod_setSeconds(AptValue *,int);
 static AptValue *sMethod_setUTCDate(AptValue *,int);
 static AptValue *sMethod_setUTCFullYear(AptValue *,int);
 static AptValue *sMethod_setUTCHours(AptValue *,int);
 static AptValue *sMethod_setUTCMilliseconds(AptValue *,int);
 static AptValue *sMethod_setUTCMinutes(AptValue *,int);
 static AptValue *sMethod_setUTCMonth(AptValue *,int);
 static AptValue *sMethod_setUTCSeconds(AptValue *,int);
 static AptValue *sMethod_setYear(AptValue *,int);
 static AptValue *sMethod_toString(AptValue *,int);
};
AptValue *AptDate::objectMemberLookup(AptValue *const context,const EAStringC *const name)const
{
 const R4Word *prop=context?Rva008B60B0(name->rva00620090(),name->rva006D3750()):0;
 if(prop){
  switch(prop->value){
case 1:
   if(!g_aptDateNativeCache.getDate) {
    g_aptDateNativeCache.getDate=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getDate)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getDate)->setGCRootCount(1);
    g_aptDateNativeCache.getDate->AddRef();
   }
   return g_aptDateNativeCache.getDate;
case 2:
   if(!g_aptDateNativeCache.getDay) {
    g_aptDateNativeCache.getDay=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getDay)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getDay)->setGCRootCount(1);
    g_aptDateNativeCache.getDay->AddRef();
   }
   return g_aptDateNativeCache.getDay;
case 3:
   if(!g_aptDateNativeCache.getFullYear) {
    g_aptDateNativeCache.getFullYear=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getFullYear)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getFullYear)->setGCRootCount(1);
    g_aptDateNativeCache.getFullYear->AddRef();
   }
   return g_aptDateNativeCache.getFullYear;
case 4:
   if(!g_aptDateNativeCache.getHours) {
    g_aptDateNativeCache.getHours=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getHours)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getHours)->setGCRootCount(1);
    g_aptDateNativeCache.getHours->AddRef();
   }
   return g_aptDateNativeCache.getHours;
case 5:
   if(!g_aptDateNativeCache.getMilliseconds) {
    g_aptDateNativeCache.getMilliseconds=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getMilliseconds)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getMilliseconds)->setGCRootCount(1);
    g_aptDateNativeCache.getMilliseconds->AddRef();
   }
   return g_aptDateNativeCache.getMilliseconds;
case 6:
   if(!g_aptDateNativeCache.getMinutes) {
    g_aptDateNativeCache.getMinutes=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getMinutes)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getMinutes)->setGCRootCount(1);
    g_aptDateNativeCache.getMinutes->AddRef();
   }
   return g_aptDateNativeCache.getMinutes;
case 7:
   if(!g_aptDateNativeCache.getMonth) {
    g_aptDateNativeCache.getMonth=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getMonth)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getMonth)->setGCRootCount(1);
    g_aptDateNativeCache.getMonth->AddRef();
   }
   return g_aptDateNativeCache.getMonth;
case 8:
   if(!g_aptDateNativeCache.getSeconds) {
    g_aptDateNativeCache.getSeconds=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getSeconds)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getSeconds)->setGCRootCount(1);
    g_aptDateNativeCache.getSeconds->AddRef();
   }
   return g_aptDateNativeCache.getSeconds;
case 9:
   if(!g_aptDateNativeCache.getTime) {
    g_aptDateNativeCache.getTime=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getTime)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getTime)->setGCRootCount(1);
    g_aptDateNativeCache.getTime->AddRef();
   }
   return g_aptDateNativeCache.getTime;
case 10:
   if(!g_aptDateNativeCache.getTimezoneOffset) {
    g_aptDateNativeCache.getTimezoneOffset=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getTimezoneOffset)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getTimezoneOffset)->setGCRootCount(1);
    g_aptDateNativeCache.getTimezoneOffset->AddRef();
   }
   return g_aptDateNativeCache.getTimezoneOffset;
case 11:
   if(!g_aptDateNativeCache.getUTCDate) {
    g_aptDateNativeCache.getUTCDate=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getUTCDate)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getUTCDate)->setGCRootCount(1);
    g_aptDateNativeCache.getUTCDate->AddRef();
   }
   return g_aptDateNativeCache.getUTCDate;
case 12:
   if(!g_aptDateNativeCache.getUTCDay) {
    g_aptDateNativeCache.getUTCDay=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getUTCDay)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getUTCDay)->setGCRootCount(1);
    g_aptDateNativeCache.getUTCDay->AddRef();
   }
   return g_aptDateNativeCache.getUTCDay;
case 13:
   if(!g_aptDateNativeCache.getUTCFullYear) {
    g_aptDateNativeCache.getUTCFullYear=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getUTCFullYear)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getUTCFullYear)->setGCRootCount(1);
    g_aptDateNativeCache.getUTCFullYear->AddRef();
   }
   return g_aptDateNativeCache.getUTCFullYear;
case 14:
   if(!g_aptDateNativeCache.getUTCHours) {
    g_aptDateNativeCache.getUTCHours=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getUTCHours)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getUTCHours)->setGCRootCount(1);
    g_aptDateNativeCache.getUTCHours->AddRef();
   }
   return g_aptDateNativeCache.getUTCHours;
case 15:
   if(!g_aptDateNativeCache.getUTCMilliseconds) {
    g_aptDateNativeCache.getUTCMilliseconds=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getUTCMilliseconds)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getUTCMilliseconds)->setGCRootCount(1);
    g_aptDateNativeCache.getUTCMilliseconds->AddRef();
   }
   return g_aptDateNativeCache.getUTCMilliseconds;
case 16:
   if(!g_aptDateNativeCache.getUTCMinutes) {
    g_aptDateNativeCache.getUTCMinutes=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getUTCMinutes)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getUTCMinutes)->setGCRootCount(1);
    g_aptDateNativeCache.getUTCMinutes->AddRef();
   }
   return g_aptDateNativeCache.getUTCMinutes;
case 17:
   if(!g_aptDateNativeCache.getUTCMonth) {
    g_aptDateNativeCache.getUTCMonth=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getUTCMonth)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getUTCMonth)->setGCRootCount(1);
    g_aptDateNativeCache.getUTCMonth->AddRef();
   }
   return g_aptDateNativeCache.getUTCMonth;
case 18:
   if(!g_aptDateNativeCache.getUTCSeconds) {
    g_aptDateNativeCache.getUTCSeconds=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getUTCSeconds)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getUTCSeconds)->setGCRootCount(1);
    g_aptDateNativeCache.getUTCSeconds->AddRef();
   }
   return g_aptDateNativeCache.getUTCSeconds;
case 19:
   if(!g_aptDateNativeCache.getYear) {
    g_aptDateNativeCache.getYear=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getYear)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.getYear)->setGCRootCount(1);
    g_aptDateNativeCache.getYear->AddRef();
   }
   return g_aptDateNativeCache.getYear;
case 20:
   if(!g_aptDateNativeCache.setDate) {
    g_aptDateNativeCache.setDate=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setDate)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setDate)->setGCRootCount(1);
    g_aptDateNativeCache.setDate->AddRef();
   }
   return g_aptDateNativeCache.setDate;
case 21:
   if(!g_aptDateNativeCache.setFullYear) {
    g_aptDateNativeCache.setFullYear=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setFullYear)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setFullYear)->setGCRootCount(1);
    g_aptDateNativeCache.setFullYear->AddRef();
   }
   return g_aptDateNativeCache.setFullYear;
case 22:
   if(!g_aptDateNativeCache.setHours) {
    g_aptDateNativeCache.setHours=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setHours)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setHours)->setGCRootCount(1);
    g_aptDateNativeCache.setHours->AddRef();
   }
   return g_aptDateNativeCache.setHours;
case 23:
   if(!g_aptDateNativeCache.setMilliseconds) {
    g_aptDateNativeCache.setMilliseconds=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setMilliseconds)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setMilliseconds)->setGCRootCount(1);
    g_aptDateNativeCache.setMilliseconds->AddRef();
   }
   return g_aptDateNativeCache.setMilliseconds;
case 24:
   if(!g_aptDateNativeCache.setMinutes) {
    g_aptDateNativeCache.setMinutes=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setMinutes)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setMinutes)->setGCRootCount(1);
    g_aptDateNativeCache.setMinutes->AddRef();
   }
   return g_aptDateNativeCache.setMinutes;
case 25:
   if(!g_aptDateNativeCache.setMonth) {
    g_aptDateNativeCache.setMonth=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setMonth)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setMonth)->setGCRootCount(1);
    g_aptDateNativeCache.setMonth->AddRef();
   }
   return g_aptDateNativeCache.setMonth;
case 26:
   if(!g_aptDateNativeCache.setSeconds) {
    g_aptDateNativeCache.setSeconds=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setSeconds)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setSeconds)->setGCRootCount(1);
    g_aptDateNativeCache.setSeconds->AddRef();
   }
   return g_aptDateNativeCache.setSeconds;
case 27:
   if(!g_aptDateNativeCache.setTime) {
    g_aptDateNativeCache.setTime=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_getTime)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setTime)->setGCRootCount(1);
    g_aptDateNativeCache.setTime->AddRef();
   }
   return g_aptDateNativeCache.setTime;
case 28:
   if(!g_aptDateNativeCache.setUTCDate) {
    g_aptDateNativeCache.setUTCDate=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setUTCDate)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setUTCDate)->setGCRootCount(1);
    g_aptDateNativeCache.setUTCDate->AddRef();
   }
   return g_aptDateNativeCache.setUTCDate;
case 29:
   if(!g_aptDateNativeCache.setUTCFullYear) {
    g_aptDateNativeCache.setUTCFullYear=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setUTCFullYear)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setUTCFullYear)->setGCRootCount(1);
    g_aptDateNativeCache.setUTCFullYear->AddRef();
   }
   return g_aptDateNativeCache.setUTCFullYear;
case 30:
   if(!g_aptDateNativeCache.setUTCHours) {
    g_aptDateNativeCache.setUTCHours=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setUTCHours)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setUTCHours)->setGCRootCount(1);
    g_aptDateNativeCache.setUTCHours->AddRef();
   }
   return g_aptDateNativeCache.setUTCHours;
case 31:
   if(!g_aptDateNativeCache.setUTCMilliseconds) {
    g_aptDateNativeCache.setUTCMilliseconds=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setUTCMilliseconds)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setUTCMilliseconds)->setGCRootCount(1);
    g_aptDateNativeCache.setUTCMilliseconds->AddRef();
   }
   return g_aptDateNativeCache.setUTCMilliseconds;
case 32:
   if(!g_aptDateNativeCache.setUTCMinutes) {
    g_aptDateNativeCache.setUTCMinutes=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setUTCMinutes)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setUTCMinutes)->setGCRootCount(1);
    g_aptDateNativeCache.setUTCMinutes->AddRef();
   }
   return g_aptDateNativeCache.setUTCMinutes;
case 33:
   if(!g_aptDateNativeCache.setUTCMonth) {
    g_aptDateNativeCache.setUTCMonth=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setUTCMonth)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setUTCMonth)->setGCRootCount(1);
    g_aptDateNativeCache.setUTCMonth->AddRef();
   }
   return g_aptDateNativeCache.setUTCMonth;
case 34:
   if(!g_aptDateNativeCache.setUTCSeconds) {
    g_aptDateNativeCache.setUTCSeconds=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setUTCSeconds)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setUTCSeconds)->setGCRootCount(1);
    g_aptDateNativeCache.setUTCSeconds->AddRef();
   }
   return g_aptDateNativeCache.setUTCSeconds;
case 35:
   if(!g_aptDateNativeCache.setYear) {
    g_aptDateNativeCache.setYear=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_setYear)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.setYear)->setGCRootCount(1);
    g_aptDateNativeCache.setYear->AddRef();
   }
   return g_aptDateNativeCache.setYear;
case 36:
   if(!g_aptDateNativeCache.toString) {
    g_aptDateNativeCache.toString=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&sMethod_toString)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.toString)->setGCRootCount(1);
    g_aptDateNativeCache.toString->AddRef();
   }
   return g_aptDateNativeCache.toString;
case 37:
   if(!g_aptDateNativeCache.UTC) {
    g_aptDateNativeCache.UTC=reinterpret_cast<AptValue *>(new Rva006D6500(reinterpret_cast<int>(&Rva006F5100Get)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_aptDateNativeCache.UTC)->setGCRootCount(1);
    g_aptDateNativeCache.UTC->AddRef();
   }
   return g_aptDateNativeCache.UTC;
  }
 }
 if(name->rva006D3510("getDate")||name->rva006D3510("getDay")||name->rva006D3510("getFullYear")||name->rva006D3510("getHours")||name->rva006D3510("getMilliseconds")||name->rva006D3510("getMinutes")||name->rva006D3510("getMonth")||name->rva006D3510("getSeconds")||name->rva006D3510("getTime")||name->rva006D3510("getTimezoneOffset")||name->rva006D3510("getUTCDate")||name->rva006D3510("getUTCDay")||name->rva006D3510("getUTCFullYear")||name->rva006D3510("getUTCHours")||name->rva006D3510("getUTCMilliseconds")||name->rva006D3510("getUTCMinutes")||name->rva006D3510("getUTCMonth")||name->rva006D3510("getUTCSeconds")||name->rva006D3510("getYear")||name->rva006D3510("setDate")||name->rva006D3510("setFullYear")||name->rva006D3510("setHours")||name->rva006D3510("setMilliseconds")||name->rva006D3510("setMinutes")||name->rva006D3510("setMonth")||name->rva006D3510("setSeconds")||name->rva006D3510("setTime")||name->rva006D3510("setUTCDate")||name->rva006D3510("setUTCFullYear")||name->rva006D3510("setUTCHours")||name->rva006D3510("setUTCMilliseconds")||name->rva006D3510("setUTCMinutes")||name->rva006D3510("setUTCMonth")||name->rva006D3510("setUTCSeconds")||name->rva006D3510("setYear")||name->rva006D3510("toString")||name->rva006D3510("UTC")) {
  Rva006CC110Log(3,"AptDate: Incorrect case for '%s'.\n",name->rva00620090());
  g_bfmeAptAssertAtE17734("0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptDate.cpp",860);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 return 0;
}

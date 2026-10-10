// cl: /O2 /Ob1 /MD /EHsc
// Native6E6060..6E63C1 and its seven unwind states establish four eight-byte
// counted-slot members and display30 ownership. Existing86B timer initializer
// and135B timer destructor form the native array callbacks. Constructor names
// of those two providers were reconciled with their existing86-byte bodies.
#include <cstring>
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int);
class BfmeAptValue006DCD20;extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;
class Rva006DB160 {public:void*allocBlock(int);};extern Rva006DB160*g_pChainBlockAllocator;
void Rva006D8680Free(void*,int);void*Rva006CD440Alloc(int);void Rva006E31F0Free(void*);
class Rva006E3BF0{public:void rva006E3BF0();};
class RootSlotSet {unsigned short count,capacity;void**array;
public:RootSlotSet(int n){capacity=(unsigned short)n;array=(void**)g_pChainBlockAllocator->allocBlock(capacity*4);count=0;memset(array,0,capacity*4);}
 ~RootSlotSet(){((Rva006E3BF0*)this)->rva006E3BF0();}
};
class AptDisplayList{void*state;public:AptDisplayList();~AptDisplayList();};
class AptActionQueueC{char data[20];public:AptActionQueueC(int);static void*operator new(unsigned size){return g_pChainBlockAllocator->allocBlock(size);}static void operator delete(void*p,unsigned size){Rva006D8680Free(p,size);}};
class AptIntervalTimer{char data[32];public:AptIntervalTimer();~AptIntervalTimer();static void*operator new[](unsigned size){return Rva006CD440Alloc(size);}static void operator delete[](void*p){Rva006E31F0Free(p);}};
struct Rva00222343 {int fields[14];bool flag38,flag39;};
class Rva006E6060Root{
 void**newInsts;int numNew;RootSlotSet a;int numIntervals;void*records28;RootSlotSet b,c,d;AptDisplayList display;AptIntervalTimer*timers;
 int value38,value3C;void**inputs;BfmeAptValue006DCD20*value44;char pad48[0x60-0x48];BfmeAptValue006DCD20*value60,*value64,*value68;
 int value6C;bool value70;char pad71[3];int value74,value78;char pad7C[0x9C-0x7C];int value9C;AptActionQueueC*queue;
 int maxNew,maxTimers,maxInputs,maxRecords;
public:Rva006E6060Root(const Rva00222343*);
};
#define ROOT_CHECK(c,l,s) if(!(c)){g_bfmeAptAssertAtE17734(s,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp",l);if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}}
Rva006E6060Root::Rva006E6060Root(const Rva00222343*p):a(p->fields[0]),b(p->fields[2]),c(p->fields[2]),d(p->fields[1]){
 maxNew=p->fields[6];maxTimers=p->fields[4];maxInputs=p->fields[7];maxRecords=p->fields[5];
 ROOT_CHECK(g_bfmeAptAllocAtE17728,0x278,"gAptFuncs.pfnMemAlloc");
 ROOT_CHECK(maxNew!=0,0x27A,"m_iMaxNewMovieClips != 0");
 newInsts=(void**)g_pChainBlockAllocator->allocBlock(maxNew*4);
 ROOT_CHECK(newInsts!=0,0x27C,"apNewInsts != NULL");
 queue=new AptActionQueueC(p->fields[3]);
 if(maxRecords==0)records28=0;else records28=Rva006CD440Alloc(maxRecords*28);
 timers=new AptIntervalTimer[maxTimers];
 ROOT_CHECK(timers!=0,0x28A,"aIntervalTimers != 0");
 ROOT_CHECK(maxInputs!=0,0x28C,"m_iMaxQueuedInputs != 0");
 inputs=(void**)g_pChainBlockAllocator->allocBlock(maxInputs*4);
 ROOT_CHECK(inputs!=0,0x28E,"aQueuedInputs != NULL");
 numNew=0;value3C=0;value6C=0;value70=false;numIntervals=0;value74=0;value78=0;value38=0;value9C=0;
 value44=g_aptUndefinedAtE18078;value60=g_aptUndefinedAtE18078;value64=g_aptUndefinedAtE18078;value68=g_aptUndefinedAtE18078;
}

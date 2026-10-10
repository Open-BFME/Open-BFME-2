// cl: /O2 /MD /EHsc
// Original EA AptMiscObjects.cpp31ceb5bf2d6e4f60 supplies Math dispatch semantics.
// WB177A5A0 names AptMathObj::objectMemberLookup; native18 cases and assert264.
// Native6E9B80..6EA518 code plus18-entry table6EA518..6EA560 is2528B.
// Ghidra2621B includes the separate93B callback beginning6EA560; it is not
// part of this method. Independent WB, native dispatch calls and all table
// targets corroborate the boundary; normal gates verify the entire extent.
// Existing18 real callback rows and real cache storage owners are reused.
// Rva006D6500 is the established opaque36B native-function allocation view;
// no original concrete constructor spelling or complete AptMath vtable is
// asserted here. The lookup receiver itself is never constructed.
class EAStringC {void *data;public:const char *rva00620090()const;unsigned int rva006D3750()const;bool rva006D3510(const char *)const;};
class AptValue;
class BfmeAptValue006DCD20 {public:void setGCRootCount(unsigned int);};
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void *,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6500 {unsigned char storage[36];public:Rva006D6500(int);static void *operator new(unsigned int n){return g_pChainBlockAllocatorF4->allocBlock(n);}static void operator delete(void *p,unsigned int n){g_pChainBlockAllocatorF4->freeBlock(p,n);}};
class Rva008A4630Item {public:virtual void unused0();virtual void release();};
struct R4Word {const char *name;int value;};
const R4Word *Rva008A3DC0(const char *,unsigned int);
void Rva006CC110Log(int,const char *,...);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptMathObj {public:virtual AptValue *objectMemberLookup(AptValue *const,const EAStringC *const)const;};
extern Rva008A4630Item *g_rva008A4630_0;
AptValue *aptMathSin(void *,int);
extern Rva008A4630Item *g_rva008A4630_1;
AptValue *aptMathCos(void *,int);
extern Rva008A4630Item *g_rva008A4630_2;
AptValue *aptMathAtan2(void *,int);
extern Rva008A4630Item *g_rva008A4630_3;
AptValue *aptMathRound(void *,int);
extern Rva008A4630Item *g_rva008A4630_4;
AptValue *aptMathMin(void *,int);
extern Rva008A4630Item *g_rva008A4630_5;
AptValue *aptMathMax(void *,int);
extern Rva008A4630Item *g_rva008A4630_6;
AptValue *aptMathAbs(void *,int);
extern Rva008A4630Item *g_rva008A4630_7;
AptValue *aptMathAcos(void *,int);
extern Rva008A4630Item *g_rva008A4630_8;
AptValue *aptMathAsin(void *,int);
extern Rva008A4630Item *g_rva008A4630_9;
AptValue *aptMathAtan(void *,int);
extern Rva008A4630Item *g_rva008A4630_10;
AptValue *aptMathCeil(void *,int);
extern Rva008A4630Item *g_rva008A4630_11;
AptValue *aptMathExp(void *,int);
extern Rva008A4630Item *g_rva008A4630_12;
AptValue *aptMathFloor(void *,int);
extern Rva008A4630Item *g_rva008A4630_13;
AptValue *aptMathLog(void *,int);
extern Rva008A4630Item *g_rva008A4630_14;
AptValue *aptMathPow(void *,int);
extern Rva008A4630Item *g_rva008A4630_15;
AptValue *aptMathRandom(void *,int);
extern Rva008A4630Item *g_rva008A4630_16;
AptValue *aptMathSqrt(void *,int);
extern Rva008A4630Item *g_rva008A4630_17;
AptValue *aptMathTan(void *,int);
AptValue *AptMathObj::objectMemberLookup(AptValue *const context,const EAStringC *const name)const
{
 const R4Word *prop=context?Rva008A3DC0(name->rva00620090(),name->rva006D3750()):0;
 if(prop) {
  switch(prop->value) {
case 1:
   if(!g_rva008A4630_0) {
    g_rva008A4630_0=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathSin)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_0)->setGCRootCount(1);
    g_rva008A4630_0->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_0);
case 2:
   if(!g_rva008A4630_1) {
    g_rva008A4630_1=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathCos)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_1)->setGCRootCount(1);
    g_rva008A4630_1->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_1);
case 3:
   if(!g_rva008A4630_2) {
    g_rva008A4630_2=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathAtan2)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_2)->setGCRootCount(1);
    g_rva008A4630_2->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_2);
case 4:
   if(!g_rva008A4630_3) {
    g_rva008A4630_3=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathRound)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_3)->setGCRootCount(1);
    g_rva008A4630_3->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_3);
case 5:
   if(!g_rva008A4630_4) {
    g_rva008A4630_4=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathMin)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_4)->setGCRootCount(1);
    g_rva008A4630_4->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_4);
case 6:
   if(!g_rva008A4630_5) {
    g_rva008A4630_5=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathMax)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_5)->setGCRootCount(1);
    g_rva008A4630_5->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_5);
case 7:
   if(!g_rva008A4630_6) {
    g_rva008A4630_6=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathAbs)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_6)->setGCRootCount(1);
    g_rva008A4630_6->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_6);
case 8:
   if(!g_rva008A4630_7) {
    g_rva008A4630_7=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathAcos)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_7)->setGCRootCount(1);
    g_rva008A4630_7->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_7);
case 9:
   if(!g_rva008A4630_8) {
    g_rva008A4630_8=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathAsin)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_8)->setGCRootCount(1);
    g_rva008A4630_8->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_8);
case 10:
   if(!g_rva008A4630_9) {
    g_rva008A4630_9=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathAtan)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_9)->setGCRootCount(1);
    g_rva008A4630_9->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_9);
case 11:
   if(!g_rva008A4630_10) {
    g_rva008A4630_10=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathCeil)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_10)->setGCRootCount(1);
    g_rva008A4630_10->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_10);
case 12:
   if(!g_rva008A4630_11) {
    g_rva008A4630_11=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathExp)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_11)->setGCRootCount(1);
    g_rva008A4630_11->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_11);
case 13:
   if(!g_rva008A4630_12) {
    g_rva008A4630_12=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathFloor)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_12)->setGCRootCount(1);
    g_rva008A4630_12->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_12);
case 14:
   if(!g_rva008A4630_13) {
    g_rva008A4630_13=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathLog)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_13)->setGCRootCount(1);
    g_rva008A4630_13->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_13);
case 15:
   if(!g_rva008A4630_14) {
    g_rva008A4630_14=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathPow)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_14)->setGCRootCount(1);
    g_rva008A4630_14->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_14);
case 16:
   if(!g_rva008A4630_15) {
    g_rva008A4630_15=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathRandom)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_15)->setGCRootCount(1);
    g_rva008A4630_15->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_15);
case 17:
   if(!g_rva008A4630_16) {
    g_rva008A4630_16=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathSqrt)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_16)->setGCRootCount(1);
    g_rva008A4630_16->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_16);
case 18:
   if(!g_rva008A4630_17) {
    g_rva008A4630_17=reinterpret_cast<Rva008A4630Item *>(new Rva006D6500(reinterpret_cast<int>(&aptMathTan)));
    reinterpret_cast<BfmeAptValue006DCD20 *>(g_rva008A4630_17)->setGCRootCount(1);
    g_rva008A4630_17->unused0();
   }
   return reinterpret_cast<AptValue *>(g_rva008A4630_17);
  }
 }
 if(name->rva006D3510("sin")||name->rva006D3510("cos")||name->rva006D3510("atan2")||name->rva006D3510("round")||name->rva006D3510("min")||name->rva006D3510("max")||name->rva006D3510("abs")||name->rva006D3510("acos")||name->rva006D3510("asin")||name->rva006D3510("atan")||name->rva006D3510("ceil")||name->rva006D3510("exp")||name->rva006D3510("floor")||name->rva006D3510("log")||name->rva006D3510("pow")||name->rva006D3510("random")||name->rva006D3510("sqrt")||name->rva006D3510("tan")) {
  Rva006CC110Log(3,"AptMathObj: Incorrect case for '%s'.\n",name->rva00620090());
  g_bfmeAptAssertAtE17734("0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptMiscObjects.cpp",264);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 return 0;
}

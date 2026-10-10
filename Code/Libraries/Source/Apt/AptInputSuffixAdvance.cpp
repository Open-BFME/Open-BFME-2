// cl: /O2 /G6 /DNDEBUG /MD
// Semantic guide reviewed at BFME1 575ba2b04; original transfer f98983a7d game/Libraries/Source/Apt/AptInput.cpp,
// bfmeParseSuffix1285 and bfmeAdvance1285. Target parser6F97F0 uses the
// owned EAStringC emptiness/buffer/size getters and native isdigit/atoi thunks.
// Native advance6FA340 replaces donor fixed512 table with count8/capacityA/
// pointerC and current6C; CIH name8, state code via6E1F00 and event6FA100.
// Static parser remains in the callers' TU for MSVC's register convention.
extern "C" int __cdecl isdigit(int);
extern "C" int __cdecl atoi(const char*);
class EAStringC {void *data;public:bool IsEmpty()const;const char *rva00620090()const;unsigned int rva006D3750()const;};
class AsciiString;
class BfmeAptValue006DCD20 {public:bool isCIH(bool)const;BfmeAptValue006DCD20 *rva006DCF60(bool);bool isUndefined()const;};
class Rva006DBB30SarDwordField {public:int get()const;};
class AptNativeHash {public:struct Entry {EAStringC key;BfmeAptValue006DCD20 *value;};AsciiString *rva0070AA40();Entry *rva0070AAA0(Entry*);};
struct AptInputInst {char unknown00[0x10];AptNativeHash *hash;};
class AptCIH {public:virtual void AddRef();virtual void Release();char unknown04[4];EAStringC name;char unknown0C[0x3C];AptCIH *parent;AptInputInst *inst;bool rva006CFCD0()const;void rva006E1F00(int);};
struct Rva006E3710Node;
class Rva006E3710 {public:bool rva006E3710(Rva006E3710Node*);};
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#define INPUT_ASSERT(test,text,line) if(!(test)){g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
class Rva006FB860 {public:char unknown00[8];unsigned short count,capacity;AptCIH **entries;char unknown10[0x5C];AptCIH *current;void rva006FA100(AptCIH*,int);void rva006FA340();};
static __declspec(noinline) bool rva006F97F0Parse(EAStringC *value,int *first,int *second)
{
 if(value->IsEmpty())return false;
 const char *base=value->rva00620090();
 const char *cursor=base+value->rva006D3750()-1;
 if(!isdigit(*cursor))return false;
 while(isdigit(*cursor))--cursor;
 if(second)*second=atoi(cursor+1);
 if(*cursor--!='_')return false;
 if(!isdigit(*cursor))return false;
 while(isdigit(*cursor))--cursor;
 if(first)*first=atoi(cursor+1);
 return true;
}
void Rva006FB860::rva006FA340()
{
 int first,second;
 if(current && rva006F97F0Parse(&current->name,&first,&second))return;
 if(current) {current->rva006E1F00(1);rva006FA100(current,2);}
 if(current)current->Release();
 current=0;
 int seen=0;
 for(int i=0;i<capacity;++i) {
  if(seen==count)break;
  AptCIH *item=entries[i];
  if(item) {
   if(!item->name.IsEmpty() && rva006F97F0Parse(&entries[i]->name,&first,&second)) {
    current=entries[i];current->AddRef();break;
   }
   ++seen;
  }
 }
 if(current){current->rva006E1F00(2);rva006FA100(current,1);}
}

// BFME1 AptInput directional-score/search semantic guide; native 6F98C0/6F99D0
// retain assertions and call the BFME2 CIH predicates/checked cast/hash API.
// Native reads prove CIH parent48/instance4C and instance hash10. Donor
// class names are semantic leads; neutral target method names remain.
// Full score271 includes the switch dispatch table; focus search is604.
// The static helpers stay in this TU to reproduce retail register calls.
static __forceinline int inputAbs(int x){return x<0?-x:x;}
static __declspec(noinline) float rva006F98C0Score(int direction,int referenceFirst,int referenceSecond,int candidateFirst,int candidateSecond)
{
 int dx=candidateSecond-referenceSecond;
 int dy=candidateFirst-referenceFirst;
 switch(direction){
 case 14:
  if(dx>=0)return -1.0f;
  {int primary=inputAbs(dx);int perpendicular=inputAbs(dy);return (float)perpendicular*10.0f+primary;}
 case 15:
  if(dx<=0)return -1.0f;
  return (float)inputAbs(dy)*10.0f+dx;
 case 1:
  if(dy>=0)return -1.0f;
  {int primary=inputAbs(dy);int perpendicular=inputAbs(dx);return (float)perpendicular*10.0f+primary;}
 case 2:
  if(dy<=0)return -1.0f;
  return (float)inputAbs(dx)*10.0f+dy;
 default:INPUT_ASSERT(false,"NOT_REACHED",0x92);
 }
 return -1.0f;
}
AptCIH *rva006F99D0(int direction,AptCIH *current,AptCIH *reference)
{
 AptCIH *bestNode;
 for(;;){if(!current)goto empty;
  float bestScore=1000000000.0f;
  int referenceFirst=0,referenceSecond=0;
  bestNode=0;
  INPUT_ASSERT(current->rva006CFCD0(),"pCIH->isSpriteInstBase()",0xA3);
  if(reference){bool bRet=rva006F97F0Parse(&reference->name,&referenceFirst,&referenceSecond);INPUT_ASSERT(bRet,"bRet",0xAB);}
  for(AptNativeHash::Entry *iterator=(AptNativeHash::Entry*)current->inst->hash->rva0070AA40();iterator;iterator=current->inst->hash->rva0070AAA0(iterator)){
   BfmeAptValue006DCD20 *value=iterator->value;
   if(!value->isCIH(false))continue;
   AptCIH *candidate=(AptCIH*)value->rva006DCF60(false);
   if(reference==candidate)continue;
   if(!candidate->rva006CFCD0()){
    if(!candidate){g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xB5);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
    if(((Rva006DBB30SarDwordField*)candidate)->get()!=14 || ((BfmeAptValue006DCD20*)candidate)->isUndefined())continue;
   }
   int candidateSecond,candidateFirst;
   if(!rva006F97F0Parse((EAStringC*)iterator,&candidateFirst,&candidateSecond))continue;
   if(((Rva006E3710*)g_bfmeAptPtrAtE176D0)->rva006E3710((Rva006E3710Node*)candidate))continue;
   if(!reference){bestNode=candidate;break;}
   INPUT_ASSERT(referenceFirst!=candidateFirst || referenceSecond!=candidateSecond,"nFocusX != nX || nFocusY != nY",0xC3);
   float score=rva006F98C0Score(direction,referenceFirst,referenceSecond,candidateFirst,candidateSecond);
   if(score>=0.0f && score<bestScore){bestScore=score;bestNode=candidate;}
  }
  if(bestNode){
   if(((Rva006DBB30SarDwordField*)bestNode)->get()!=13 || ((BfmeAptValue006DCD20*)bestNode)->isUndefined())goto found;
   reference=0;current=bestNode;
  }else{reference=current;current=current->parent;}
 }
 empty:return 0;
 found:return bestNode;
}

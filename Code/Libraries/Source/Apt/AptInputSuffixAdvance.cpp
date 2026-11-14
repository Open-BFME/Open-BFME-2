// cl: /O2 /G6 /DNDEBUG /MD /D_CRTIMP=
// Semantic guide reviewed at BFME1 575ba2b04; original transfer f98983a7d game/Libraries/Source/Apt/AptInput.cpp,
// bfmeParseSuffix1285 and bfmeAdvance1285. Target parser6F97F0 uses the
// owned EAStringC emptiness/buffer/size getters and native isdigit/atoi thunks.
// Native advance6FA340 replaces donor fixed512 table with count8/capacityA/
// pointerC and current6C; CIH name8, state code via6E1F00 and event6FA100.
// Static parser remains in the callers' TU for MSVC's register convention.
#include <ctype.h>
#include <stdlib.h>
#include "EAStringC.h"
class AsciiString;
#include "BfmeAptValue006DCD20.h"
#include "../../../GameEngine/Include/Common/Rva006DBB30SarDwordField.h"
struct Rva0070AA40InputEntry {EAStringC key;BfmeAptValue006DCD20 *value;};
#include "AptNativeHash.h"
struct AptInputInst {char unknown00[0x10];AptNativeHash *hash;};
#include "AptCIHClass.h"
static __forceinline EAStringC *cihName(AptCIH *cih){return &cih->field08;}
struct Rva006E3710Node;
#include "Rva006E3710.h"
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#define INPUT_ASSERT(test,text,line) if(!(test)){g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();}
struct BfmeMesh1290;struct BfmeTransform2_1290;
class AptAnimationPoolData {public:AptCIH *rva006FA420(int,int);bool bfmeMeshHitTest1290(BfmeMesh1290 *,const BfmeTransform2_1290 *,int,int);char unknown00[8];unsigned short count,capacity;AptCIH **entries;char unknown10[0x5C];AptCIH *current;void rva006FA100(AptCIH*,int);void setValidFocusButton();};
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
void AptAnimationPoolData::setValidFocusButton()
{
 int first,second;
 if(current && rva006F97F0Parse(cihName(current),&first,&second))return;
 if(current) {current->rva006E1F00(1);rva006FA100(current,2);}
 if(current)current->Release();
 current=0;
 int seen=0;
 for(int i=0;i<capacity;++i) {
  if(seen==count)break;
  AptCIH *item=entries[i];
  if(item) {
   if(!cihName(item)->IsEmpty() && rva006F97F0Parse(cihName(entries[i]),&first,&second)) {
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
  if(reference){bool bRet=rva006F97F0Parse(cihName(reference),&referenceFirst,&referenceSecond);INPUT_ASSERT(bRet,"bRet",0xAB);}
  for(Rva0070AA40InputEntry *iterator=(Rva0070AA40InputEntry*)((AptInputInst *)current->field4C)->hash->rva0070AA40();iterator;iterator=(Rva0070AA40InputEntry*)((AptInputInst *)current->field4C)->hash->rva0070AAA0((AptNativeHash::Entry*)iterator)){
   BfmeAptValue006DCD20 *value=iterator->value;
   if(!(unsigned char)value->isCIH(false))continue;
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
  }else{reference=current;current=current->field48;}
 }
 empty:return 0;
 found:return bestNode;
}

// Native 6FA420..6FDDD (957B, RET8): button-instance hit test over the global
// button pool (WB AptInput.cpp asserts 0x1F0..0x1FB): per instance, per hit
// record, either the mesh hit test (shape type 1) or the transformed
// rectangle test (type 2). The two redundant self-compares of nButtonInstances
// in the first assert condition fold away (no bytes) but change cl's operand
// orientation for the later [base+index] record addressing (the bank was three
// commuted SIB encodings off).
struct BfmeM1208 {float m[6];};
void __cdecl bfmeMul1208(const BfmeM1208 *,const BfmeM1208 *,BfmeM1208 *);
struct BfmeMesh1290;
struct BfmeTransform2_1290;
struct AptButtonShape {int eType;int unknown04;float x0,y0,x1,y1;};
struct AptButtonHitRecord {unsigned int flags;AptButtonShape *shape;int unknown08;BfmeM1208 matrix;char unknown24[0x44-0x24];};
struct AptButtonHitDescriptor {char pad[0x24];int recordCount;AptButtonHitRecord *records;};
struct AptButtonHitCharacter {int eType;char pad04[4];AptButtonHitDescriptor desc;};
struct AptButtonHitCharInst {char pad[0xc];AptButtonHitCharacter *pCharacter;};
class AptButtonHitCIH {
public:
 __forceinline bool isButtonInst() const {
  if (!this) {
   g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xB5);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  return ((const Rva006DBB30SarDwordField*)this)->get()==0xE && !((const BfmeAptValue006DCD20*)this)->isUndefined();
 }
 __forceinline bool isCharacterInst() const {
  return ((const Rva006DBB30SarDwordField*)this)->get()>=0xC && ((const Rva006DBB30SarDwordField*)this)->get()<=0x13 && !((const BfmeAptValue006DCD20*)this)->isUndefined();
 }
 __forceinline AptButtonHitCharInst *getCharacterInst() const {
  if (!this) {
   g_bfmeAptAssertAtE17734("this","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xB0);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  if (!isCharacterInst()) {
   g_bfmeAptAssertAtE17734("isCharacterInst()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0xA5);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  return inst;
 }
 char pad[0x4c];
 AptButtonHitCharInst *inst;
};
struct AptButtonInstance {AptButtonHitCIH *pCIH;BfmeM1208 matrix;};
struct AptButtonPoolView {char pad[0x10];int nButtonInstances;AptButtonInstance *aButtonInstanceList;};
#define gpButtonPool ((AptButtonPoolView*)g_bfmeAptPtrAtE176D0)
AptCIH *AptAnimationPoolData::rva006FA420(int x,int y)
{
 int checked=0;
 for (int i=gpButtonPool->nButtonInstances-1;i>=0;i--) {
  if ((gpButtonPool->aButtonInstanceList[i].pCIH==0) && gpButtonPool->nButtonInstances==gpButtonPool->nButtonInstances && gpButtonPool->nButtonInstances==gpButtonPool->nButtonInstances) {
   g_bfmeAptAssertAtE17734("gpPool->aButtonInstanceList[i].pCIH != NULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x1F0);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  if (((BfmeAptValue006DCD20*)gpButtonPool->aButtonInstanceList[i].pCIH)->isUndefined()) continue;
  if (!gpButtonPool->aButtonInstanceList[i].pCIH->isButtonInst()) {
   g_bfmeAptAssertAtE17734("gpPool->aButtonInstanceList[i].pCIH->isButtonInst()","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x1F8);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  AptButtonHitDescriptor *desc=&gpButtonPool->aButtonInstanceList[i].pCIH->getCharacterInst()->pCharacter->desc;
  if (gpButtonPool->aButtonInstanceList[i].pCIH->getCharacterInst()->pCharacter->eType!=4) {
   g_bfmeAptAssertAtE17734("gpPool->aButtonInstanceList[i].pCIH->getCharacterInst()->pCharacter->eType == AptCharacterType_Button","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp",0x1FB);
   if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
  }
  for (int j=0;j<desc->recordCount;j++) {
   if (!(desc->records[j].flags&8)) continue;
   BfmeM1208 matrix=desc->records[j].matrix;
   bfmeMul1208(&gpButtonPool->aButtonInstanceList[i].matrix,&matrix,&matrix);
   AptButtonShape *shape=desc->records[j].shape;
   if (shape->eType==1) {
    if (bfmeMeshHitTest1290((BfmeMesh1290*)desc,(const BfmeTransform2_1290*)&matrix,x,y))
     return (AptCIH*)gpButtonPool->aButtonInstanceList[i].pCIH;
   } else if (shape->eType==2) {
    float x0=shape->x0,x1=shape->x1,y0=shape->y0,y1=shape->y1;
    if ((float)x>matrix.m[0]*x0+matrix.m[1]*y0+matrix.m[4] && (float)x<matrix.m[0]*x1+matrix.m[1]*y1+matrix.m[4]
     && (float)y>matrix.m[2]*x0+matrix.m[3]*y0+matrix.m[5] && (float)y<matrix.m[2]*x1+matrix.m[3]*y1+matrix.m[5])
     return (AptCIH*)gpButtonPool->aButtonInstanceList[i].pCIH;
   }
  }
  if (++checked==gpButtonPool->nButtonInstances) break;
 }
 return 0;
}

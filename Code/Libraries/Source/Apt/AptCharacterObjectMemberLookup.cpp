// cl:  /O2 /DNDEBUG /MD /EHsc
//
// ?Rva006EFBC0ObjectMemberLookup@@YAPAVAptValue@@PAV1@PBVEAStringC@@@Z,
// retail 0x006EFBC0..0x006F113C (cdecl, C++ EH frame, handler 0x007A9AD5)
// followed by its switch tables 0x006F1140..0x006F12EF: the AptCharacter.cpp
// property-get worker, AptCharacterInst::objectMemberLookup per the WorldBuilder
// twin 0x01784910 (semantic and structure guide only; all offsets below are
// measured from native accesses, not WB's +4 CIH view).
//
// Lever: the return blocks. cl merges a `goto label; ... label: return result;`
// block with the shared `done` return when the label is placed before `done`
// at the end of the function, and keeps its own epilogue copy when the label
// follows `done`. Retail merges cases 18-20 into done (case 10's block) and
// keeps separate epilogues for the scroll, textColor and two float window
// words (11, 13, 14, 15), so their labels follow `done`.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline void aptAssert(const char *test,const char *file,int line){
 g_bfmeAptAssertAtE17734(test,file,line);
 if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
}
#define CHARACTER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp"
#define CIH_FILE "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"
class EAStringC {
 void *data;
public:
 EAStringC(); ~EAStringC(); EAStringC &clear();
 EAStringC &operator=(const EAStringC&);
 bool IsEmpty()const; const char *rva00620090()const;
 unsigned int rva006D3750()const;
 bool IsEqualTo(const EAStringC*)const;
 bool rva006D30D0(const EAStringC*)const;
 bool rva006D3510(const char*)const;
 EAStringC &MakeLower();
};
class AptCIH;
class Rva006DBB30SarDwordField {public:int get() const;};
class AptValue {
public:
 bool isCIH(bool)const; AptCIH *c_cih(bool);
 bool isUndefined()const; int getVtblIndex()const;
 int toInteger()const; float toFloat()const;
 void toString(EAStringC&)const;void SetString(const char*);
};
class BfmeAptValue006DCD20 {
public:BfmeAptValue006DCD20 *rva006DCF60(bool); bool isCIH(bool) const; bool isUndefined() const; virtual void AddRef();unsigned flags;int rva006E02B0()const; void *rva006E0F40()const;int isCharacterInst()const;void setGCRootCount(unsigned);
};
class AptString:public AptValue {
public:static AptString *Create();
 __forceinline EAStringC &value(){return *(EAStringC*)((char*)this+8);}
};
struct AptNativeHash {void Set(const EAStringC *const,AptValue *const);};
class AptCIH {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual AptNativeHash *slot3();
 char unknown04[8]; float matrix[6];
 char unknown24[0x44-0x24]; float *properties; AptCIH *parent;
 void *instance;char unknown50[0x60-0x50];
 bool rva006CFCD0()const;
 bool IsSpriteInst(bool)const; bool IsAnimationInst(bool)const;
 void factorySetProperty(int,float,bool);
 void factoryEnsureProperties();void *rva006CFF40()const;bool IsCharacterInst()const; void rva006E1DD0(void*);
 void SetEventHandler(int); void RemoveEventHandler(int);
 bool rva006E1F90(int);
};
static __forceinline AptCIH *lookupCheckedCIH(AptValue *v,bool b){return (AptCIH*)((BfmeAptValue006DCD20*)v)->rva006DCF60(b);}

static __forceinline bool isText(AptCIH *cih){
 if(!cih)aptAssert("this",CIH_FILE,0xC4);
 const AptValue *v=(const AptValue*)cih;
 return ((const Rva006DBB30SarDwordField*)v)->get()==15 && !((const BfmeAptValue006DCD20*)v)->isUndefined();
}
static __forceinline bool isButton(AptCIH *cih){
 if(!cih)aptAssert("this",CIH_FILE,0xB5);
 const AptValue *v=(const AptValue*)cih;
 return ((const Rva006DBB30SarDwordField*)v)->get()==14 && !((const BfmeAptValue006DCD20*)v)->isUndefined();
}
class Rva006EBFF0 {public:void rva006EBE60(AptValue*);void rva006EBFF0(AptValue*);};
class Rva006E1260 {public:void call(void*);};
class Rva006E9A40List {public:void add(AptCIH*);};
class Rva006E0DE0 {public:int rva006E0DE0(AptValue*);};
template<class T>class AptValueSet {public:unsigned short reserved,count;T *items;bool has(T)const;};
class Rva006E34D0 {public:
 char unknown00[0x20]; AptValueSet<AptValue*> contexts,cihs;
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
static __forceinline void addSet(AptValueSet<AptValue*> *set,AptValue *v){((Rva006E9A40List*)set)->add((AptCIH*)v);}
struct AptActionInterpreter {bool setVariable(AptValue*,AptValue*,const EAStringC*,AptValue*,int,int,int);};
extern AptActionInterpreter g_aptDateInterpreter;
struct R4Word {const char*name;int id;};
const R4Word *Rva008ABF40(const char*,unsigned int);
const R4Word *Rva008D48F0(const char*,unsigned int);
EAStringC *Rva0070B4F0GetString(int);
void __cdecl Rva006CC110Log(int,const char*,...);
struct TextDefinition {char unknown00[0x2C];int multiline,wordWrap;const char*defaultText;};
struct TextInstance {
 char unknown00[0xC]; TextDefinition *definition;
 char unknown10[8]; EAStringC text,variable; int unknown20;
 unsigned textColor; int maxScroll,scroll; unsigned backgroundColor,borderColor;
 int autoSize; char unknown3C[0x50-0x3C]; float left,top,right,bottom;
 char unknown60[0xC]; unsigned dirty; int unknown70;
 unsigned reserved0:1,border:1,background:1,mouseWheel:1,reserved4:28;
};
struct Rect {float left,top,right,bottom;};

class AptInteger {public:static AptValue *Create(int);};
class AptBoolean {public:static AptValue *Create(bool);};
AptValue *Rva008A4EA0MakeFloat(float);
extern AptValue *gpUndefinedValue;
struct BfmeM1208 {float a,b,c,d,e,f;};
void bfmeMul1208(const BfmeM1208*,const BfmeM1208*,BfmeM1208*);
struct BfmeQ1206 {int m_bfme00,m_bfme04,m_bfme08,m_bfme0c,m_bfme10,m_bfme14;};
extern "C" BfmeQ1206 g_bfmeD1206;
struct LookupMouse {char pad[0x74];int x,y;};

struct CharacterInstance {char pad[12];struct Definition {int a,b;int frames;};Definition *definition;};
void rva006ffc30(AptValue*,EAStringC&);
void rva006ffce0(AptValue*,EAStringC&);
class Rva006D2A60 {public:void *allocBlock(int);void freeBlock(void*,int);};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class Rva006D6500:public BfmeAptValue006DCD20 {
 char rest[28];
 public:Rva006D6500(int);
 static void *operator new(unsigned n){return g_pChainBlockAllocatorF4->allocBlock(n);}
 static void operator delete(void *p,unsigned n){g_pChainBlockAllocatorF4->freeBlock(p,n);}
};
class Acac0Releaseable;
extern AptValue *g_shutdownAtE180A8; // lookup property 24; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE18080; // lookup property 25; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE18084; // lookup property 26; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE180B4; // lookup property 27; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE18074; // lookup property 28; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern AptValue *g_shutdownAtE1806C; // lookup property 29; owned by Code/Libraries/Source/Apt/AptValueShutdownBFME2.cpp
extern Acac0Releaseable *g_Va00E181A0; // lookup property 100; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181AC; // lookup property 101; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E1819C; // lookup property 103; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E18198; // lookup property 104; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181A4; // lookup property 105; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181D8; // lookup property 106; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181E0; // lookup property 107; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181E8; // lookup property 108; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181B0; // lookup property 109; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181DC; // lookup property 110; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181F0; // lookup property 111; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181EC; // lookup property 112; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181E4; // lookup property 113; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181B8; // lookup property 114; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181BC; // lookup property 115; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181D4; // lookup property 116; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181C8; // lookup property 117; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181D0; // lookup property 118; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181B4; // lookup property 119; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181C0; // lookup property 120; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181A8; // lookup property 121; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181C4; // lookup property 122; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181F8; // lookup property 123; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181FC; // lookup property 124; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181F4; // lookup property 125; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E181CC; // lookup property 126; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
extern Acac0Releaseable *g_Va00E18200; // lookup property 127; owned by Code/GameEngine/Source/Common/Rva008ACAC0GlobalReleases.cpp
AptValue *Rva006EC3E0LoadMovie(AptValue *self,int nParams);
AptValue *Rva006EC590UnloadMovie(AptValue *self,int nParams);
BfmeAptValue006DCD20 *rva006ec670(BfmeAptValue006DCD20 *pValue, int nParams);
AptValue *Rva006EC6F0Depth(AptValue *context,int unusedArgumentCount);
AptValue *__cdecl Rva006EC730GetBounds(AptValue *,int);
AptValue *__cdecl Rva006EC900StartDrag(AptValue *self,int count);
AptValue *__cdecl Rva006ECA70PointHitTest(void *self,int count);
AptValue *Rva006ECC20LoadVariables(AptValue *self,int count);
AptValue *__cdecl Rva006ECCB0LocalToGlobal(AptValue *,int);
AptValue *aptHelperClearFlag008AE450(void *entry, int count);
AptValue *aptHelperSetFlag008AE470(void *entry, int count);
AptValue *__cdecl attachMovie(AptValue *,int);
AptValue *Rva006ED770RemoveMovieClip(AptValue *self,int);
AptValue *__cdecl Rva006ED810CreateTextField(AptValue *,int);
AptValue *__cdecl Rva006EDBD0SwapDepths(AptValue *,int);
AptValue *Rva006EDF20SwapDepths(AptValue *self,int count);
AptValue *__cdecl Rva006EDFF0CreateEmptyMovieClip(AptValue *,int);
AptValue *stop(BfmeAptValue006DCD20 *entry);
AptValue *rva006ee210(BfmeAptValue006DCD20 *entry);
AptValue *nextFrame(BfmeAptValue006DCD20 *entry);
AptValue *PrevFrame(BfmeAptValue006DCD20 *entry);
AptValue *__cdecl rva006ee3b0(AptValue *value);
AptValue *__cdecl rva006ee540(AptValue *value);
AptValue *__cdecl Rva006EF570ApplyTextFormat(AptValue *,int);
AptValue *__cdecl Rva006EF6D0TextFormat(AptValue *,int);
AptValue *__cdecl Rva006EF920TextFormat(AptValue *,int);

static __forceinline void refreshText(AptValue *context,TextInstance *text){
 if(text->dirty&4){AptCIH *parent=lookupCheckedCIH(context,false)->parent;((Rva006E1260*)lookupCheckedCIH(context,false))->call(parent);}
}
static __forceinline AptValue *makeLookupString(const EAStringC &s){AptString *v=AptString::Create();v->value()=s;return v;}
AptValue *__cdecl Rva006EFBC0ObjectMemberLookup(AptValue *context,const EAStringC *name){

 float number;
 AptValue *result;

 AptCIH *initial=((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false));

 if(isText(initial)){

  const R4Word *word=Rva008ABF40(name->rva00620090(),name->rva006D3750());

  if(word){

   TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)context)->rva006E0F40();

   switch(word->id){

   case 1:{
AptString *v=AptString::Create();
switch(text->autoSize){
case 0:v->value()=*Rva0070B4F0GetString(0x56);
break;
case 1:v->value()=*Rva0070B4F0GetString(0x7E);
break;
case 2:v->value()=*Rva0070B4F0GetString(0x29);
break;
case 3:v->value()=*Rva0070B4F0GetString(0x61);
break;
default:v->value()=*Rva0070B4F0GetString(0x61);
break;
}
return v;
}

   case 2:return AptBoolean::Create(text->background);

   case 3:return AptInteger::Create(text->backgroundColor&0xFFFFFF);

   case 4:return AptBoolean::Create(text->border);

   case 5:return AptInteger::Create(text->borderColor&0xFFFFFF);

   case 7:((Rva006EBFF0*)text)->rva006EBFF0((AptValue*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)));
return AptInteger::Create(text->text.rva006D3750());

   case 8:goto undef8;

   case 9:if(text->dirty&4)((Rva006E1260*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)))->call(((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false))->parent);
return AptInteger::Create(text->maxScroll);

   case 10:{result=AptBoolean::Create((text->definition->multiline&0xFFFFFF)!=0);goto done;}

   case 11:if(text->dirty&4)((Rva006E1260*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)))->call(((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false))->parent);
{result=AptInteger::Create(text->scroll);goto d11;}

   case 12:((Rva006EBFF0*)text)->rva006EBFF0((AptValue*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)));
return makeLookupString(text->text);

   case 13:{result=AptInteger::Create(text->textColor&0xFFFFFF);goto d13;}

   case 14:if(text->dirty&4)((Rva006E1260*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)))->call(((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false))->parent);
{result=Rva008A4EA0MakeFloat(*(float*)((char*)text+0x48));goto d14;}

   case 15:if(text->dirty&4)((Rva006E1260*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)))->call(((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false))->parent);
{result=Rva008A4EA0MakeFloat(*(float*)((char*)text+0x44));goto d15;}

   case 16:{
AptString *v=AptString::Create();
v->SetString("dynamic");
return v;
}

   case 17:if(!text->variable.IsEmpty())return makeLookupString(text->variable);
return gpUndefinedValue;

   case 18:{result=AptBoolean::Create((text->definition->wordWrap&0xFFFFFF)!=0);goto d18;}

   case 19:{
if(text->dirty&4)((Rva006E1260*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)))->call(((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false))->parent);
Rect r;
((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false))->rva006E1DD0(&r);
float n=r.bottom-r.top;
if(n<0)n=0;
result=Rva008A4EA0MakeFloat(n);goto d19;
}

   case 20:{
if(text->dirty&4)((Rva006E1260*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)))->call(((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false))->parent);
Rect r;
((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false))->rva006E1DD0(&r);
float n=r.right-r.left;
if(n<0)n=0;
result=Rva008A4EA0MakeFloat(n);goto d20;
}

   case 21:return AptBoolean::Create(text->mouseWheel);

   }

  }

 }

 const R4Word *word=context && ((BfmeAptValue006DCD20*)context)->isCIH(false)?Rva008D48F0(name->rva00620090(),name->rva006D3750()):0;

 if(!word)return 0;

 AptCIH *cih=((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false));

 if(!(unsigned char)((BfmeAptValue006DCD20*)cih)->isCharacterInst())aptAssert("isCharacterInst()",CIH_FILE,0xA5);

 CharacterInstance *inst=(CharacterInstance*)cih->instance;

 switch(word->id){

 case 1:{
if((unsigned char)((BfmeAptValue006DCD20*)cih)->rva006E02B0()){
TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)cih)->rva006E0F40();
if(text->autoSize!=3 && text->autoSize!=0 && text->dirty&4)((Rva006E1260*)cih)->call(cih->parent);
}
number=cih->matrix[4];
break;
}

 case 2:number=cih->matrix[5];
break;

 case 3:number=cih->properties?cih->properties[2]:cih->matrix[0]*100.0f;
break;

 case 4:number=cih->properties?cih->properties[3]:cih->matrix[3]*100.0f;
break;

 case 7:number=cih->properties?cih->properties[7]:*(float*)((char*)cih+0x24)*100.0f;
break;

 case 8:number=cih->properties?cih->properties[11]:1.0f;
break;

 case 5:number=(float)(*(int*)((char*)cih->rva006CFF40()+0x18)+1);
break;

 case 24:return g_shutdownAtE180A8;

 case 25:return g_shutdownAtE18080;

 case 26:return g_shutdownAtE18084;

 case 27:return g_shutdownAtE180B4;

 case 28:return g_shutdownAtE18074;

 case 29:return g_shutdownAtE1806C;

 case 12:{
EAStringC s;
rva006ffc30((AptValue*)cih,s);
return makeLookupString(s);
}

 case 9:{
Rect r;
cih->rva006E1DD0(&r);
number=r.right-r.left;
if(number<0)number=0;
break;
}

 case 10:{
Rect r;
cih->rva006E1DD0(&r);
number=r.bottom-r.top;
if(number<0)number=0;
break;
}

 case 11:cih->factoryEnsureProperties();
number=cih->properties[6];
break;

 case 6:number=(float)inst->definition->frames;
break;

 case 13:number=(float)inst->definition->frames;
break;

 case 21:{
BfmeM1208 m=*(const BfmeM1208*)&g_bfmeD1206;
for(AptCIH *p=cih;
p;
p=p->parent)bfmeMul1208(&m,(BfmeM1208*)p->matrix,&m);
number=((float)((LookupMouse*)g_bfmeAptPtrAtE176D0)->x-m.e)*m.a-((float)((LookupMouse*)g_bfmeAptPtrAtE176D0)->y-m.f)*m.b;
break;
}

 case 22:{
BfmeM1208 m=*(const BfmeM1208*)&g_bfmeD1206;
for(AptCIH *p=cih;
p;
p=p->parent)bfmeMul1208(&m,(BfmeM1208*)p->matrix,&m);
number=((float)((LookupMouse*)g_bfmeAptPtrAtE176D0)->x-m.e)*m.c+((float)((LookupMouse*)g_bfmeAptPtrAtE176D0)->y-m.f)*m.d;
break;
}

 case 118:if(!g_Va00E181D0){
g_Va00E181D0=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ECA70PointHitTest);
((Rva006D6500*)g_Va00E181D0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181D0)->AddRef();
}
return (AptValue*)g_Va00E181D0;

 case 126:if(!g_Va00E181CC){
g_Va00E181CC=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC900StartDrag);
((Rva006D6500*)g_Va00E181CC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181CC)->AddRef();
}
return (AptValue*)g_Va00E181CC;

 case 106:if(!g_Va00E181D8){
g_Va00E181D8=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ECC20LoadVariables);
((Rva006D6500*)g_Va00E181D8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181D8)->AddRef();
}
return (AptValue*)g_Va00E181D8;

 case 103:if(!g_Va00E1819C){
g_Va00E1819C=(Acac0Releaseable*)new Rva006D6500((int)&aptHelperSetFlag008AE470);
((Rva006D6500*)g_Va00E1819C)->setGCRootCount(1);
((Rva006D6500*)g_Va00E1819C)->AddRef();
}
return (AptValue*)g_Va00E1819C;

 case 104:if(!g_Va00E18198){
g_Va00E18198=(Acac0Releaseable*)new Rva006D6500((int)&aptHelperClearFlag008AE450);
((Rva006D6500*)g_Va00E18198)->setGCRootCount(1);
((Rva006D6500*)g_Va00E18198)->AddRef();
}
return (AptValue*)g_Va00E18198;

 case 100:if(!g_Va00E181A0){
g_Va00E181A0=(Acac0Releaseable*)new Rva006D6500((int)&attachMovie);
((Rva006D6500*)g_Va00E181A0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181A0)->AddRef();
}
return (AptValue*)g_Va00E181A0;

 case 107:if(!g_Va00E181E0){
g_Va00E181E0=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee210);
((Rva006D6500*)g_Va00E181E0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181E0)->AddRef();
}
return (AptValue*)g_Va00E181E0;

 case 110:if(!g_Va00E181DC){
g_Va00E181DC=(Acac0Releaseable*)new Rva006D6500((int)&stop);
((Rva006D6500*)g_Va00E181DC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181DC)->AddRef();
}
return (AptValue*)g_Va00E181DC;

 case 108:if(!g_Va00E181E8){
g_Va00E181E8=(Acac0Releaseable*)new Rva006D6500((int)&PrevFrame);
((Rva006D6500*)g_Va00E181E8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181E8)->AddRef();
}
return (AptValue*)g_Va00E181E8;

 case 113:if(!g_Va00E181E4){
g_Va00E181E4=(Acac0Releaseable*)new Rva006D6500((int)&nextFrame);
((Rva006D6500*)g_Va00E181E4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181E4)->AddRef();
}
return (AptValue*)g_Va00E181E4;

 case 112:if(!g_Va00E181EC){
g_Va00E181EC=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee3b0);
((Rva006D6500*)g_Va00E181EC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181EC)->AddRef();
}
return (AptValue*)g_Va00E181EC;

 case 111:if(!g_Va00E181F0){
g_Va00E181F0=(Acac0Releaseable*)new Rva006D6500((int)&rva006ee540);
((Rva006D6500*)g_Va00E181F0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181F0)->AddRef();
}
return (AptValue*)g_Va00E181F0;

 case 101:if(!g_Va00E181AC){
g_Va00E181AC=(Acac0Releaseable*)new Rva006D6500((int)&rva006ec670);
((Rva006D6500*)g_Va00E181AC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181AC)->AddRef();
}
return (AptValue*)g_Va00E181AC;

 case 109:if(!g_Va00E181B0){
g_Va00E181B0=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ED770RemoveMovieClip);
((Rva006D6500*)g_Va00E181B0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181B0)->AddRef();
}
return (AptValue*)g_Va00E181B0;

 case 105:if(!g_Va00E181A4){
g_Va00E181A4=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC3E0LoadMovie);
((Rva006D6500*)g_Va00E181A4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181A4)->AddRef();
}
return (AptValue*)g_Va00E181A4;

 case 121:if(!g_Va00E181A8){
g_Va00E181A8=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC590UnloadMovie);
((Rva006D6500*)g_Va00E181A8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181A8)->AddRef();
}
return (AptValue*)g_Va00E181A8;

 case 114:if(!g_Va00E181B8){
g_Va00E181B8=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ED810CreateTextField);
((Rva006D6500*)g_Va00E181B8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181B8)->AddRef();
}
return (AptValue*)g_Va00E181B8;

 case 119:if(!g_Va00E181B4){
g_Va00E181B4=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ED770RemoveMovieClip);
((Rva006D6500*)g_Va00E181B4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181B4)->AddRef();
}
return (AptValue*)g_Va00E181B4;

 case 115:if(!g_Va00E181BC){
g_Va00E181BC=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC6F0Depth);
((Rva006D6500*)g_Va00E181BC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181BC)->AddRef();
}
return (AptValue*)g_Va00E181BC;

 case 117:if(!g_Va00E181C8){
g_Va00E181C8=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EC730GetBounds);
((Rva006D6500*)g_Va00E181C8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181C8)->AddRef();
}
return (AptValue*)g_Va00E181C8;

 case 116:if(!g_Va00E181D4){
g_Va00E181D4=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EDFF0CreateEmptyMovieClip);
((Rva006D6500*)g_Va00E181D4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181D4)->AddRef();
}
return (AptValue*)g_Va00E181D4;

 case 120:if(!g_Va00E181C0){
g_Va00E181C0=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EDBD0SwapDepths);
((Rva006D6500*)g_Va00E181C0)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181C0)->AddRef();
}
return (AptValue*)g_Va00E181C0;

 case 122:if(!g_Va00E181C4){
g_Va00E181C4=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EDF20SwapDepths);
((Rva006D6500*)g_Va00E181C4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181C4)->AddRef();
}
return (AptValue*)g_Va00E181C4;

 case 127:if(!g_Va00E18200){
g_Va00E18200=(Acac0Releaseable*)new Rva006D6500((int)&Rva006ECCB0LocalToGlobal);
((Rva006D6500*)g_Va00E18200)->setGCRootCount(1);
((Rva006D6500*)g_Va00E18200)->AddRef();
}
return (AptValue*)g_Va00E18200;

 case 14:return makeLookupString(*(EAStringC*)((char*)cih+8));

 case 16:{
AptString *v=AptString::Create();
EAStringC s;
rva006ffce0((AptValue*)((AptCIH*)((BfmeAptValue006DCD20*)context)->rva006DCF60(false)),s);
v->SetString(s.rva00620090());
return v;
}

 case 124:if(!g_Va00E181FC){
g_Va00E181FC=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EF920TextFormat);
((Rva006D6500*)g_Va00E181FC)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181FC)->AddRef();
}
return (AptValue*)g_Va00E181FC;

 case 123:if(!g_Va00E181F8){
g_Va00E181F8=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EF6D0TextFormat);
((Rva006D6500*)g_Va00E181F8)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181F8)->AddRef();
}
return (AptValue*)g_Va00E181F8;

 case 125:if(!g_Va00E181F4){
g_Va00E181F4=(Acac0Releaseable*)new Rva006D6500((int)&Rva006EF570ApplyTextFormat);
((Rva006D6500*)g_Va00E181F4)->setGCRootCount(1);
((Rva006D6500*)g_Va00E181F4)->AddRef();
}
return (AptValue*)g_Va00E181F4;

 default:return 0;

 }

 return Rva008A4EA0MakeFloat(number);
d20:
 return result;
d19:
 return result;
d18:
 return result;
done:
 return result;
d11:
 return result;
d13:
 return result;
d14:
 return result;
d15:
 return result;
undef8:
 return gpUndefinedValue;

}

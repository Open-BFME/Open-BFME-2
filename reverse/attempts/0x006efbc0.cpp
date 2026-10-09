// ?Rva006EFBC0ObjectMemberLookup@@YAPAVAptValue@@PAV1@PBVEAStringC@@@Z
// partial score=0.671748132 date=2026-10-09
// cl:  /O2 /DNDEBUG /MD /EHsc
// AptCharacterInst::objectMemberLookup. Native EFBC0..F113C code
// and F1140..F12EF dispatch tables; WB1784910 is the semantic guide.
// All offsets below are measured from native accesses, not WB's +4 CIH view.
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
 EAStringC(){clear();} ~EAStringC(); EAStringC &clear();
 EAStringC &operator=(const EAStringC&);
 bool IsEmpty()const; const char *rva00620090()const;
 unsigned int rva006D3750()const;
 bool IsEqualTo(const EAStringC*)const;
 bool rva006D30D0(const EAStringC*)const;
 bool rva006D3510(const char*)const;
 EAStringC &MakeLower();
};
class AptCIH;
class AptValue {
public:
 bool isCIH(bool)const; AptCIH *c_cih(bool);
 bool isUndefined()const; int getVtblIndex()const;
 int toInteger()const; float toFloat()const;
 void toString(EAStringC&)const;void SetString(const char*);
};
class BfmeAptValue006DCD20 {
public:virtual void AddRef();unsigned flags;bool rva006E02B0()const; void *rva006E0F40()const;bool isCharacterInst()const;void setGCRootCount(unsigned);
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
static __forceinline bool isText(AptCIH *cih){
 if(!cih)aptAssert("this",CIH_FILE,0xC4);
 const AptValue *v=(const AptValue*)cih;
 return v->getVtblIndex()==15 && !v->isUndefined();
}
static __forceinline bool isButton(AptCIH *cih){
 if(!cih)aptAssert("this",CIH_FILE,0xB5);
 const AptValue *v=(const AptValue*)cih;
 return v->getVtblIndex()==14 && !v->isUndefined();
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
extern BfmeM1208 lookupIdentity;
struct LookupMouse {char pad[0x74];int x,y;};
extern LookupMouse *lookupMouse;
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
static AptValue *lookupSingleton24;
static AptValue *lookupSingleton25;
static AptValue *lookupSingleton26;
static AptValue *lookupSingleton27;
static AptValue *lookupSingleton28;
static AptValue *lookupSingleton29;
static Rva006D6500 *lookupCache100;
static Rva006D6500 *lookupCache101;
static Rva006D6500 *lookupCache103;
static Rva006D6500 *lookupCache104;
static Rva006D6500 *lookupCache105;
static Rva006D6500 *lookupCache106;
static Rva006D6500 *lookupCache107;
static Rva006D6500 *lookupCache108;
static Rva006D6500 *lookupCache109;
static Rva006D6500 *lookupCache110;
static Rva006D6500 *lookupCache111;
static Rva006D6500 *lookupCache112;
static Rva006D6500 *lookupCache113;
static Rva006D6500 *lookupCache114;
static Rva006D6500 *lookupCache115;
static Rva006D6500 *lookupCache116;
static Rva006D6500 *lookupCache117;
static Rva006D6500 *lookupCache118;
static Rva006D6500 *lookupCache119;
static Rva006D6500 *lookupCache120;
static Rva006D6500 *lookupCache121;
static Rva006D6500 *lookupCache122;
static Rva006D6500 *lookupCache123;
static Rva006D6500 *lookupCache124;
static Rva006D6500 *lookupCache125;
static Rva006D6500 *lookupCache126;
static Rva006D6500 *lookupCache127;
void __cdecl lookupCallback006EC3E0(); // measured callback RVA0x006EC3E0; signature pending
void __cdecl lookupCallback006EC590(); // measured callback RVA0x006EC590; signature pending
void __cdecl lookupCallback006EC670(); // measured callback RVA0x006EC670; signature pending
void __cdecl lookupCallback006EC6F0(); // measured callback RVA0x006EC6F0; signature pending
void __cdecl lookupCallback006EC730(); // measured callback RVA0x006EC730; signature pending
void __cdecl lookupCallback006EC900(); // measured callback RVA0x006EC900; signature pending
void __cdecl lookupCallback006ECA70(); // measured callback RVA0x006ECA70; signature pending
void __cdecl lookupCallback006ECC20(); // measured callback RVA0x006ECC20; signature pending
void __cdecl lookupCallback006ECCB0(); // measured callback RVA0x006ECCB0; signature pending
void __cdecl lookupCallback006ED450(); // measured callback RVA0x006ED450; signature pending
void __cdecl lookupCallback006ED470(); // measured callback RVA0x006ED470; signature pending
void __cdecl lookupCallback006ED580(); // measured callback RVA0x006ED580; signature pending
void __cdecl lookupCallback006ED770(); // measured callback RVA0x006ED770; signature pending
void __cdecl lookupCallback006ED810(); // measured callback RVA0x006ED810; signature pending
void __cdecl lookupCallback006EDBD0(); // measured callback RVA0x006EDBD0; signature pending
void __cdecl lookupCallback006EDF20(); // measured callback RVA0x006EDF20; signature pending
void __cdecl lookupCallback006EDFF0(); // measured callback RVA0x006EDFF0; signature pending
void __cdecl lookupCallback006EE1B0(); // measured callback RVA0x006EE1B0; signature pending
void __cdecl lookupCallback006EE210(); // measured callback RVA0x006EE210; signature pending
void __cdecl lookupCallback006EE270(); // measured callback RVA0x006EE270; signature pending
void __cdecl lookupCallback006EE310(); // measured callback RVA0x006EE310; signature pending
void __cdecl lookupCallback006EE3B0(); // measured callback RVA0x006EE3B0; signature pending
void __cdecl lookupCallback006EE540(); // measured callback RVA0x006EE540; signature pending
void __cdecl lookupCallback006EF570(); // measured callback RVA0x006EF570; signature pending
void __cdecl lookupCallback006EF6D0(); // measured callback RVA0x006EF6D0; signature pending
void __cdecl lookupCallback006EF920(); // measured callback RVA0x006EF920; signature pending

static __forceinline void refreshText(AptValue *context,TextInstance *text){
 if(text->dirty&4){AptCIH *parent=context->c_cih(false)->parent;((Rva006E1260*)context->c_cih(false))->call(parent);}
}
static __forceinline AptValue *makeLookupString(const EAStringC &s){AptString *v=AptString::Create();v->value()=s;return v;}
AptValue *__cdecl Rva006EFBC0ObjectMemberLookup(AptValue *context,const EAStringC *name){
 float number;
 AptCIH *initial=context->c_cih(false);
 if(isText(initial)){
  const R4Word *word=Rva008ABF40(name->rva00620090(),name->rva006D3750());
  if(word){
   TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)context)->rva006E0F40();
   switch(word->id){
   case 1:{AptString *v=AptString::Create();switch(text->autoSize){case 0:v->value()=*Rva0070B4F0GetString(0x56);break;case 1:v->value()=*Rva0070B4F0GetString(0x7E);break;case 2:v->value()=*Rva0070B4F0GetString(0x29);break;case 3:v->value()=*Rva0070B4F0GetString(0x61);break;default:v->value()=*Rva0070B4F0GetString(0x61);break;}return v;}
   case 2:return AptBoolean::Create(text->background);
   case 3:return AptInteger::Create(text->backgroundColor&0xFFFFFF);
   case 4:return AptBoolean::Create(text->border);
   case 5:return AptInteger::Create(text->borderColor&0xFFFFFF);
   case 7:((Rva006EBFF0*)text)->rva006EBFF0((AptValue*)context->c_cih(false));return AptInteger::Create(text->text.rva006D3750());
   case 8:return gpUndefinedValue;
   case 9:refreshText(context,text);return AptInteger::Create(text->maxScroll);
   case 10:return AptBoolean::Create((text->definition->multiline&0xFFFFFF)!=0);
   case 11:refreshText(context,text);return AptInteger::Create(text->scroll);
   case 12:((Rva006EBFF0*)text)->rva006EBFF0((AptValue*)context->c_cih(false));return makeLookupString(text->text);
   case 13:return AptInteger::Create(text->textColor&0xFFFFFF);
   case 14:refreshText(context,text);return Rva008A4EA0MakeFloat(*(float*)((char*)text+0x48));
   case 15:refreshText(context,text);return Rva008A4EA0MakeFloat(*(float*)((char*)text+0x44));
   case 16:{AptString *v=AptString::Create();v->SetString("dynamic");return v;}
   case 17:if(text->variable.IsEmpty())return gpUndefinedValue;return makeLookupString(text->variable);
   case 18:return AptBoolean::Create((text->definition->wordWrap&0xFFFFFF)!=0);
   case 19:{refreshText(context,text);Rect r;context->c_cih(false)->rva006E1DD0(&r);float n=r.bottom-r.top;if(n<0)n=0;return Rva008A4EA0MakeFloat(n);}
   case 20:{refreshText(context,text);Rect r;context->c_cih(false)->rva006E1DD0(&r);float n=r.right-r.left;if(n<0)n=0;return Rva008A4EA0MakeFloat(n);}
   case 21:return AptBoolean::Create(text->mouseWheel);
   }
  }
 }
 const R4Word *word=context && context->isCIH(false)?Rva008D48F0(name->rva00620090(),name->rva006D3750()):0;
 if(!word)return 0;
 AptCIH *cih=context->c_cih(false);
 if(!cih->IsCharacterInst())aptAssert("isCharacterInst()",CIH_FILE,0xA5);
 CharacterInstance *inst=(CharacterInstance*)cih->instance;
 switch(word->id){
 case 1:{if(((BfmeAptValue006DCD20*)cih)->rva006E02B0()){TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)cih)->rva006E0F40();if(text->autoSize!=3 && text->autoSize!=0 && text->dirty&4)((Rva006E1260*)cih)->call(cih->parent);}number=cih->matrix[4];break;}
 case 2:number=cih->matrix[5];break;
 case 3:number=cih->properties?cih->properties[2]:cih->matrix[0]*100.0f;break;
 case 4:number=cih->properties?cih->properties[3]:cih->matrix[3]*100.0f;break;
 case 5:number=(float)(*(int*)((char*)cih->rva006CFF40()+0x18)+1);break;
 case 6:number=(float)inst->definition->frames;break;
 case 7:number=cih->properties?cih->properties[7]:*(float*)((char*)cih+0x24)*100.0f;break;
 case 8:number=cih->properties?cih->properties[11]:1.0f;break;
 case 9:{Rect r;cih->rva006E1DD0(&r);number=r.right-r.left;if(number<0)number=0;break;}
 case 10:{Rect r;cih->rva006E1DD0(&r);number=r.bottom-r.top;if(number<0)number=0;break;}
 case 11:cih->factoryEnsureProperties();number=cih->properties[6];break;
 case 12:{EAStringC s;rva006ffc30((AptValue*)cih,s);return makeLookupString(s);}
 case 13:number=(float)inst->definition->frames;break;
 case 21:{BfmeM1208 m=lookupIdentity;for(AptCIH *p=cih;p;p=p->parent)bfmeMul1208(&m,(BfmeM1208*)p->matrix,&m);number=((float)lookupMouse->x-m.e)*m.a-((float)lookupMouse->y-m.f)*m.b;break;}
 case 22:{BfmeM1208 m=lookupIdentity;for(AptCIH *p=cih;p;p=p->parent)bfmeMul1208(&m,(BfmeM1208*)p->matrix,&m);number=((float)lookupMouse->y-m.f)*m.d+((float)lookupMouse->x-m.e)*m.c;break;}
 case 24:return lookupSingleton24;
 case 25:return lookupSingleton25;
 case 26:return lookupSingleton26;
 case 27:return lookupSingleton27;
 case 28:return lookupSingleton28;
 case 29:return lookupSingleton29;
 case 118:if(!lookupCache118){lookupCache118=new Rva006D6500((int)&lookupCallback006ECA70);lookupCache118->setGCRootCount(1);lookupCache118->AddRef();}return (AptValue*)lookupCache118;
 case 126:if(!lookupCache126){lookupCache126=new Rva006D6500((int)&lookupCallback006EC900);lookupCache126->setGCRootCount(1);lookupCache126->AddRef();}return (AptValue*)lookupCache126;
 case 106:if(!lookupCache106){lookupCache106=new Rva006D6500((int)&lookupCallback006ECC20);lookupCache106->setGCRootCount(1);lookupCache106->AddRef();}return (AptValue*)lookupCache106;
 case 103:if(!lookupCache103){lookupCache103=new Rva006D6500((int)&lookupCallback006ED470);lookupCache103->setGCRootCount(1);lookupCache103->AddRef();}return (AptValue*)lookupCache103;
 case 104:if(!lookupCache104){lookupCache104=new Rva006D6500((int)&lookupCallback006ED450);lookupCache104->setGCRootCount(1);lookupCache104->AddRef();}return (AptValue*)lookupCache104;
 case 100:if(!lookupCache100){lookupCache100=new Rva006D6500((int)&lookupCallback006ED580);lookupCache100->setGCRootCount(1);lookupCache100->AddRef();}return (AptValue*)lookupCache100;
 case 107:if(!lookupCache107){lookupCache107=new Rva006D6500((int)&lookupCallback006EE210);lookupCache107->setGCRootCount(1);lookupCache107->AddRef();}return (AptValue*)lookupCache107;
 case 110:if(!lookupCache110){lookupCache110=new Rva006D6500((int)&lookupCallback006EE1B0);lookupCache110->setGCRootCount(1);lookupCache110->AddRef();}return (AptValue*)lookupCache110;
 case 108:if(!lookupCache108){lookupCache108=new Rva006D6500((int)&lookupCallback006EE310);lookupCache108->setGCRootCount(1);lookupCache108->AddRef();}return (AptValue*)lookupCache108;
 case 113:if(!lookupCache113){lookupCache113=new Rva006D6500((int)&lookupCallback006EE270);lookupCache113->setGCRootCount(1);lookupCache113->AddRef();}return (AptValue*)lookupCache113;
 case 112:if(!lookupCache112){lookupCache112=new Rva006D6500((int)&lookupCallback006EE3B0);lookupCache112->setGCRootCount(1);lookupCache112->AddRef();}return (AptValue*)lookupCache112;
 case 111:if(!lookupCache111){lookupCache111=new Rva006D6500((int)&lookupCallback006EE540);lookupCache111->setGCRootCount(1);lookupCache111->AddRef();}return (AptValue*)lookupCache111;
 case 101:if(!lookupCache101){lookupCache101=new Rva006D6500((int)&lookupCallback006EC670);lookupCache101->setGCRootCount(1);lookupCache101->AddRef();}return (AptValue*)lookupCache101;
 case 109:if(!lookupCache109){lookupCache109=new Rva006D6500((int)&lookupCallback006ED770);lookupCache109->setGCRootCount(1);lookupCache109->AddRef();}return (AptValue*)lookupCache109;
 case 105:if(!lookupCache105){lookupCache105=new Rva006D6500((int)&lookupCallback006EC3E0);lookupCache105->setGCRootCount(1);lookupCache105->AddRef();}return (AptValue*)lookupCache105;
 case 121:if(!lookupCache121){lookupCache121=new Rva006D6500((int)&lookupCallback006EC590);lookupCache121->setGCRootCount(1);lookupCache121->AddRef();}return (AptValue*)lookupCache121;
 case 114:if(!lookupCache114){lookupCache114=new Rva006D6500((int)&lookupCallback006ED810);lookupCache114->setGCRootCount(1);lookupCache114->AddRef();}return (AptValue*)lookupCache114;
 case 119:if(!lookupCache119){lookupCache119=new Rva006D6500((int)&lookupCallback006ED770);lookupCache119->setGCRootCount(1);lookupCache119->AddRef();}return (AptValue*)lookupCache119;
 case 115:if(!lookupCache115){lookupCache115=new Rva006D6500((int)&lookupCallback006EC6F0);lookupCache115->setGCRootCount(1);lookupCache115->AddRef();}return (AptValue*)lookupCache115;
 case 117:if(!lookupCache117){lookupCache117=new Rva006D6500((int)&lookupCallback006EC730);lookupCache117->setGCRootCount(1);lookupCache117->AddRef();}return (AptValue*)lookupCache117;
 case 116:if(!lookupCache116){lookupCache116=new Rva006D6500((int)&lookupCallback006EDFF0);lookupCache116->setGCRootCount(1);lookupCache116->AddRef();}return (AptValue*)lookupCache116;
 case 120:if(!lookupCache120){lookupCache120=new Rva006D6500((int)&lookupCallback006EDBD0);lookupCache120->setGCRootCount(1);lookupCache120->AddRef();}return (AptValue*)lookupCache120;
 case 122:if(!lookupCache122){lookupCache122=new Rva006D6500((int)&lookupCallback006EDF20);lookupCache122->setGCRootCount(1);lookupCache122->AddRef();}return (AptValue*)lookupCache122;
 case 127:if(!lookupCache127){lookupCache127=new Rva006D6500((int)&lookupCallback006ECCB0);lookupCache127->setGCRootCount(1);lookupCache127->AddRef();}return (AptValue*)lookupCache127;
 case 14:return makeLookupString(*(EAStringC*)((char*)cih+8));
 case 16:{AptString *v=AptString::Create();EAStringC s;rva006ffce0((AptValue*)context->c_cih(false),s);v->SetString(s.rva00620090());return v;}
 case 124:if(!lookupCache124){lookupCache124=new Rva006D6500((int)&lookupCallback006EF920);lookupCache124->setGCRootCount(1);lookupCache124->AddRef();}return (AptValue*)lookupCache124;
 case 123:if(!lookupCache123){lookupCache123=new Rva006D6500((int)&lookupCallback006EF6D0);lookupCache123->setGCRootCount(1);lookupCache123->AddRef();}return (AptValue*)lookupCache123;
 case 125:if(!lookupCache125){lookupCache125=new Rva006D6500((int)&lookupCallback006EF570);lookupCache125->setGCRootCount(1);lookupCache125->AddRef();}return (AptValue*)lookupCache125;
 default:return 0;
 }
 return Rva008A4EA0MakeFloat(number);
}

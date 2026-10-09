// ?rva006EE6C0@@YA_NPAVAptValue@@PBVEAStringC@@0@Z
// partial score=0.8481689388 date=2026-10-09
// cl: /O2 /DNDEBUG /MD /EHsc
// AptCharacter.cpp property-set worker. Target EE6C0..EF404, then native
// switch tables EF408..EF564. WB17838A0 is a semantic/structure guide only.
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
 void toString(EAStringC&)const;
};
class BfmeAptValue006DCD20 {
public:bool rva006E02B0()const; void *rva006E0F40()const;
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
 char unknown4C[0x60-0x4C];
 bool rva006CFCD0()const;
 bool IsSpriteInst(bool)const; bool IsAnimationInst(bool)const;
 void factorySetProperty(int,float,bool);
 void factoryEnsureProperties(); void rva006E1DD0(void*);
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
class Rva006EBFF0 {public:void rva006EBE60(AptValue*);};
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
// Native event property masks at VA CEC648; populated from retail data below.
static const unsigned int eventMasks[218]={
0x0,0x424154,0x6E617461,0x0,0x6E697361,0x0,0x6E6174,0x6E696D,0x676F6C,0x6E617461,0x32,0x6E6973,
0x736F6361,0x0,0x736261,0x74727173,0x0,0x78616D,0x646E6172,0x6D6F,0x707865,0x6E756F72,0x64,0x6C696563,
0x0,0x736F63,0x6F6F6C66,0x72,0x776F70,0x646E6573,0x4C646E41,0x64616F,0x42746567,0x73657479,0x64616F4C,0x6465,
0x42746567,0x73657479,0x61746F54,0x6C,0x746E6F63,0x54746E65,0x657079,0x646E6573,0x0,0x64616F6C,0x6465,0x64616F6C,
0x0,0x0,0x705C3A43,0x656A6F72,0x5C737463,0x656D6662,0x74617032,0x30316863,0x66625C33,0x5C32656D,0x65646F43,0x62694C5C,
0x69726172,0x535C7365,0x6372756F,0x70415C65,0x70415C74,0x73694D74,0x6A624F63,0x73746365,0x7070632E,0x0,0x78415966,0x61567369,
0x65756C,0x78415866,0x61567369,0x65756C,0x55504E49,0x53495F54,0x414E415F,0x28474F4C,0x70416726,0x74634174,0x496E6F69,0x7265746E,
0x74657270,0x692E7265,0x7475706E,0x29,0xADCAC0,0xADCB20,0xACBCD0,0xACBFD0,0x5826C0,0xAD6460,0xAD6440,0xAEA700,
0xAC8770,0xACBCF0,0xA9E440,0xB0DFE0,0x5826C0,0xB0DFD0,0xAE9B20,0x74704167,0x636E7546,0x66702E73,0x6E65536E,0x72615664,
0x6C626169,0x7365,0x74704167,0x636E7546,0x66702E73,0x7465476E,0x65747942,0x746F5473,0x6C61,0x74704167,0x636E7546,0x66702E73,
0x7465476E,0x65747942,0x616F4C73,0x646564,0x45747041,0x726F7272,0x6E49203A,0x72726F63,0x20746365,0x65736163,0x726F6620,0x73252720,
0xA2E27,0xADCAC0,0xADCB20,0xACBCD0,0xACBFD0,0x5826C0,0xAD6460,0xAD6440,0xAEAB30,0xAE9580,0xACBCF0,0xA9E440,
0xB0DFE0,0x5826C0,0xB0DFD0,0xAE9B50,0x4D747041,0x4F687461,0x203A6A62,0x6F636E49,0x63657272,0x61632074,0x66206573,0x2720726F,
0x2E277325,0xA,0x6C616373,0x646F4D65,0x65,0x74646977,0x68,0x67696568,0x7468,0x67696C61,0x6E,0x736C6166,
0x26262065,0x65722220,0x65766F6D,0x7473694C,0x72656E65,0x20736920,0x20746F6E,0x70707573,0x2074726F,0x22746579,0x0,0x736C6166,
0x26262065,0x64612220,0x73694C64,0x656E6574,0x73692072,0x746F6E20,0x70757320,0x74726F70,0x79206465,0x227465,0x4C747041,0x5664616F,
0x3A737261,0x636E4920,0x6572726F,0x63207463,0x20657361,0x20726F66,0x27732527,0xA2E,0x100,0x10000,0x8000,0x2,
0x40,0x80,0xFFFFFFFF,0x1,0x10,0x8,0x20,0x400,0x800,0x1000,0x4000,0x2000,
0xFFFFFFFF,0x4
};
bool __cdecl rva006EE6C0(AptValue *context,const EAStringC *name,AptValue *value)
{
 float number;
 if(!context->isCIH(false))aptAssert("pContext->isCIH()",CHARACTER_FILE,0x669);
 AptCIH *cih=context->c_cih(false);
 if(isText(cih)) {
  const R4Word *word=Rva008ABF40(name->rva00620090(),name->rva006D3750());
  if(word){
   TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E0F40();
   switch(word->id){
   case 1:{
    EAStringC s;value->toString(s);s.MakeLower();
    if(text->autoSize==3 && (s.rva006D30D0(Rva0070B4F0GetString(0x34)) || s.rva006D30D0(Rva0070B4F0GetString(0x61)))) text->dirty|=8;
    else text->dirty|=0x10;
    if(s.IsEqualTo(Rva0070B4F0GetString(0x56)) || s.IsEqualTo(Rva0070B4F0GetString(0xA8)))text->autoSize=0;
    else if(s.IsEqualTo(Rva0070B4F0GetString(0x29)))text->autoSize=2;
    else if(s.IsEqualTo(Rva0070B4F0GetString(0x7E)))text->autoSize=1;
    else if(s.IsEqualTo(Rva0070B4F0GetString(0x34)) || s.IsEqualTo(Rva0070B4F0GetString(0x61)))text->autoSize=3;
    text->dirty=(text->dirty&~1u)|4u;return true;
   }
   case 2:text->background=value->toInteger();text->dirty=(text->dirty&~1u)|0x20;return true;
   case 3:text->backgroundColor=value->toInteger()|0xFF000000;text->dirty=(text->dirty&~1u)|0x40;return true;
   case 4:text->border=value->toInteger();text->dirty=(text->dirty&~1u)|0x80;return true;
   case 5:text->borderColor=value->toInteger()|0xFF000000;text->dirty=(text->dirty&~1u)|0x100;return true;
   case 6:case 8:case 16:return true;
   case 10:text->definition->multiline=value->toInteger();break;
   case 11:{int n=value->toInteger();int old=text->scroll;
    if(text->dirty&4){AptCIH *parent=context->c_cih(false)->parent;((Rva006E1260*)context->c_cih(false))->call(parent);}
    text->scroll=n;if(text->scroll>text->maxScroll)text->scroll=text->maxScroll;if(text->scroll<1)text->scroll=1;
    if(old!=text->scroll)text->dirty=0x204;break;
   }
   case 12:{EAStringC s;value->toString(s);if(text->text.rva006D30D0(&s)){
    text->text=s;
    if(!text->variable.IsEmpty()){
     AptCIH *parent=context->c_cih(false);
     while(parent && !parent->rva006CFCD0() && parent->parent)parent=parent->parent;
     AptString *created=AptString::Create();created->value()=s;
     g_aptDateInterpreter.setVariable((AptValue*)parent,0,&text->variable,created,1,1,0);
    }
    text->dirty=0x204;
   }return true;}
   case 13:text->textColor=value->toInteger()|0xFF000000;text->dirty=(text->dirty&~1u)|0x400;return true;
   case 17:{EAStringC s;value->toString(s);if(text->variable.rva006D30D0(&s)){
    text->variable=s;AptCIH *parent=context->c_cih(false);((Rva006EBFF0*)text)->rva006EBE60((AptValue*)parent);text->dirty=(text->dirty&~1u)|0x204;
   }return true;}
   case 18:text->definition->wordWrap=value->toInteger();text->dirty=(text->dirty&~1u)|0x1004;return true;
   case 19:{float n=value->toFloat();if(!(n<0)){text->bottom=n+text->top;text->dirty=(text->dirty&~1u)|0x2004;}return true;}
   case 20:{float n=value->toFloat();if(!(n<0)){text->right=n+text->left;text->dirty=(text->dirty&~1u)|0x4004;}return true;}
   case 21:{int n=value->toInteger();text->mouseWheel=n;
    if(n==1&&!g_bfmeAptPtrAtE176D0->contexts.has(context)){
     addSet(&g_bfmeAptPtrAtE176D0->contexts,context);
     addSet(&g_bfmeAptPtrAtE176D0->cihs,(AptValue*)context->c_cih(false));
    }break;
   }
   }
  }
 }
 if(context->c_cih(false)->rva006CFCD0() || isButton(context->c_cih(false)) || ((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0()){
  const R4Word *word=Rva008D48F0(name->rva00620090(),name->rva006D3750());
  if(word){
   cih=context->c_cih(false);
   switch(word->id){
   case 1:if(value->isUndefined())return false;number=value->toFloat();cih->factorySetProperty(0,number,true);return true;
   case 2:if(value->isUndefined())return false;number=value->toFloat();cih->factorySetProperty(1,number,true);return true;
   case 3:number=value->toFloat();cih->factorySetProperty(2,number,true);return true;
   case 4:number=value->toFloat();cih->factorySetProperty(3,number,true);return true;
   case 11:{number=value->toFloat();if(number>180.0f)number-=360.0f;cih->factorySetProperty(6,number,true);return true;}
   case 7:number=value->toFloat();cih->factorySetProperty(7,number,true);return true;
   case 8:number=value->toFloat();cih->factorySetProperty(11,number,false);return true;
   case 9:{number=value->toFloat();if(number<0)return true;if(number==0)number=.0001f;
    Rect r;cih->rva006E1DD0(&r);float extent=r.right-r.left;
    if(extent!=0){cih->factoryEnsureProperties();float scale;
     if(cih->properties[6]!=0)scale=((number-extent)/extent)*100.0f+cih->properties[2];
     else {extent=number/extent;if(extent<.0001f)extent=.0001f;scale=extent*cih->matrix[0]*100.0f;}
     if(scale<1.1322573f)scale=1.1322573f;cih->factorySetProperty(2,scale,true);
    }return true;
   }
   case 10:{number=value->toFloat();if(number<0)return true;if(number==0)number=.0001f;
    Rect r;cih->rva006E1DD0(&r);float extent=r.bottom-r.top;
    if(extent!=0){cih->factoryEnsureProperties();float scale;
     if(cih->properties[6]!=0)scale=((number-extent)/extent)*100.0f+cih->properties[3];
     else {extent=number/extent;if(extent<.0001f)extent=.0001f;scale=extent*cih->matrix[3]*100.0f;}
     if(scale<1.1322573f)scale=1.1322573f;cih->factorySetProperty(3,scale,true);
    }return true;
   }
   case 200:case 203:case 207:case 217:{
    if(((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0())return false;
    int mask=eventMasks[word->id];AptNativeHash *hash=cih->slot3();hash->Set(name,value);
    if(!value || value->isUndefined())cih->RemoveEventHandler(mask);else cih->SetEventHandler(mask);
    return true;
   }
   case 201:case 202:case 204:case 205:case 208:case 209:case 210:case 211:case 212:case 213:case 214:case 215:{
    if(((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0())return false;
    int mask=eventMasks[word->id];AptNativeHash *hash=cih->slot3();hash->Set(name,value);
    if(!value || value->isUndefined()){
     cih->RemoveEventHandler(mask);
     if(context->c_cih(false)->IsSpriteInst(false) && !cih->rva006E1F90(0xBFCF8) && g_bfmeAptPtrAtE176D0->cihs.has((AptValue*)cih))
      ((Rva006E0DE0*)&g_bfmeAptPtrAtE176D0->cihs)->rva006E0DE0((AptValue*)cih);
    }else{
     cih->SetEventHandler(mask);
     if((context->c_cih(false)->IsSpriteInst(false)||context->c_cih(false)->IsAnimationInst(false))&&!g_bfmeAptPtrAtE176D0->cihs.has((AptValue*)cih))
      addSet(&g_bfmeAptPtrAtE176D0->cihs,(AptValue*)cih);
    }return true;
   }
   default:
    if(name->rva006D3510("x")||name->rva006D3510("y")||name->rva006D3510("rotation")||name->rva006D3510("alpha")||name->rva006D3510("xscale")||name->rva006D3510("yscale")||name->rva006D3510("visible")||name->rva006D3510("width")||name->rva006D3510("height")){
     Rva006CC110Log(3,"AptCharacterInst (MovieClip): Incorrect case for '%s'.\number",name->rva00620090());aptAssert("",CHARACTER_FILE,0x859);
    }return false;
   }
  }
  if(name->rva006D3510("this"))aptAssert("NOT_REACHED",CHARACTER_FILE,0x862);
 }
 return false;
}

// cl: /O2 /DNDEBUG /MD /EHsc
//
// ?rva006EE6C0@@YA_NPAVAptValue@@PBVEAStringC@@0@Z,
// retail 0x006EE6C0..0x006EF405 (3749 bytes, cdecl, C++ EH frame) followed by
// its switch tables 0x006EF408..0x006EF564: the AptCharacter.cpp
// property-set worker (assert strings name AptCharacter.cpp, lines 0x669,
// 0x859, 0x862). WB 0x017838A0 is a semantic and structure guide only; all
// offsets below are measured from native accesses, not WB's +4 CIH view.
//
// A text instance takes the text-field words (text, html, border, colors,
// variable, scroll, autoSize, ...). A movie clip, button or flagged instance
// takes the transform words through AptCIH::factorySetProperty, the
// width/height words through the bounds rectangle, and the event-handler
// words through its native hash; anything else returns false.
//
// Lever: movie-clip word 1 (factory property 0) ends with break and the function
// returns true after the switch. cl keeps the LAST return-true in source order
// as the shared target of the early returns in the _width/_height cases, so
// that post-switch return puts their four jnp targets on the word-1 return
// copy as retail does; written in place, they land on the event-case join.
// The asserts break through an inline __asm int 3, which keeps cl from
// cross-jumping the 0x859/0x862 assert tails.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
// The verified seven-byte provider at 0x006DBB30 returns the signed type index.
class Rva006DBB30SarDwordField { public: int get() const; };
class AptCIH;
class EAStringC;
class AptValue

{
 public:
 AptCIH *c_cih(bool bUndefinedOK);
 bool isCIH(bool bUndefinedOK) const;
 bool isUndefined() const;
 float toFloat() const;
 int toInteger() const;
 void toString(EAStringC &) const;
 
}
;
struct AptNativeHash;
class AptCIH 
{
 public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual AptNativeHash *slot3();
 char unknown04[8];
 float matrix[6];
 char unknown24[0x44-0x24];
 float *properties;
 AptCIH *volatile parent;
 void *volatile member4C;
 char unknown50[8];
 signed int depth:17;
 unsigned int unknownDepth17:15;
 int unknown5c;
 bool rva006CFCD0()const;
 bool IsSpriteInst(bool)const;
 bool IsAnimationInst(bool)const;
 void factorySetProperty(int,float,bool);
 void factoryEnsureProperties();
 void rva006E1DD0(void*);
 void SetEventHandler(int);
 void RemoveEventHandler(int);
 int rva006E1F90(int);
 
}
;
class EAStringC

{
 public:
 class StringDataC
 
 {
  public:
  unsigned short m_uRefCount;
  unsigned short m_uSize;
  unsigned short m_uMaxSize;
  unsigned short m_uHash;
  
 }
 ;
 private:
 StringDataC *data;
 public:
 EAStringC();
 static void FreeData(StringDataC *);
 EAStringC &clear();
 EAStringC &operator=(const EAStringC&);
 ~EAStringC();
 int GetAt(int)const;
 bool IsEmpty()const;
 unsigned int rva006D3750()const;
 bool IsEqualTo(const EAStringC*)const;
 bool rva006D30D0(const EAStringC*)const;
 bool rva006D3510(const char*)const;
 EAStringC &MakeLower();
 EAStringC &Rva006D4F00Append(const EAStringC &other);
 const char *rva00620090() const;
 
}
;
extern EAStringC::StringDataC g_eaEmptyStringData;
// Native callers invoke this 16-byte constructor at 0x006D2F90, folded with
// clear; it roots the string at the empty singleton (RVA 0x009DC020 / VA
// 0x00DDC020) and takes one reference. Keep the native call boundary.
__declspec(noinline) inline EAStringC::EAStringC()

{
 data = &g_eaEmptyStringData;
 ++data->m_uRefCount;
 
}
class Rva006CD650

{
 public:
 void *rva006CD650();
 
}
;
// Retail preserves the unsigned-address addition before the resource load.
// Using direct pointer arithmetic folds these two instructions in MSVC 7.1.
AptValue *__cdecl Rva008A4EA0MakeFloat(float value);
// ?rva006ee3b0@@YAPAVAptValue@@PAV1@@Z @0x006EE3B0, 393B.
// ?rva006ee540@@YAPAVAptValue@@PAV1@@Z @0x006EE540, 373B.
class AptInteger 
{
 public:static AptValue *Create(int);
 
}
;
class AptBasePtrStack 
{
 public:AptValue *At(int);
 
}
;
struct AptActionInterpreter 
{
 AptBasePtrStack stack;
 bool setVariable(AptValue*,AptValue*,const EAStringC*,AptValue*,int,int,int);
 
}
;
extern AptActionInterpreter g_aptDateInterpreter;
// 006ECA70: target gAptFuncs.pfnPointHitTest assertion identifies the callback
// slot; its retail data word is initially zero. This is a private typed view
// of that unclaimed slot, not a claim about the original global's scope.
// Native At calls use the interpreter's stack prefix at offset zero. The
// two bounds rectangles form one aggregate to preserve the measured slots:
// other +8 and receiver +18. All four bounds tests are inclusive and ordered.
struct Rect 
{
 float left,top,right,bottom;
 
}
;
class Rva008A4570Owner 
{
 public:bool nameEquals(const char*);
 
}
;
class Rva006EB4B0 
{
 public:EAStringC font;
 float size;
 int color;
 int align;
 unsigned flags;
 int indent;
 int left;
 int right;
 Rva006EB4B0(AptValue*,float,int,int,int,int,int,int,AptValue*,int,int,int,int);
 Rva006EB4B0(const Rva006EB4B0&);
 
}
;
// Native C6F0..C72A: signed17-bit depth at CIH+58 biased by0x4000.
// WB1782970 confirms the same operation with its independent +5C layout.
// Callback identity remains address-derived; no inferred original name.
extern AptValue *gpUndefinedValue;
// Native CE30..CEB4 copies the same32B format state; -1 leaves three
// destination fields untouched exactly as native. Reference signature is
// structural inference; all field reads/writes and conditional copies are
// target facts, and the constructor name remains address-derived.
// AptCharacter.cpp property-set worker. Target EE6C0..EF404, then native
// switch tables EF408..EF564. WB17838A0 is a semantic/structure guide only.
// All offsets below are measured from native accesses, not WB's +4 CIH view.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline void aptAssert(const char *test,const char *file,int line)
{
 g_bfmeAptAssertAtE17734(test,file,line);
 if(g_bfmeAptBreakOnAssertAtDDC01C)
 {
  __asm int 3
 }
 
}
#define CHARACTER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp"
#define CIH_FILE "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"
class AptCIH;
class BfmeAptValue006DCD20 
{
 virtual void vtableSlot0();
 public:unsigned int m_flags;
 bool isUndefined()const;
 BfmeAptValue006DCD20 *checkedString();
 int toInteger()const;
 int rva006E02B0()const;
 void *rva006E0F40()const;
 
}
;
class AptString:public AptValue 
{
 public:static AptString *Create();
 __forceinline EAStringC &value()
 {
  return *(EAStringC*)((char*)this+8);
  
 }
 
}
;
struct AptNativeHash 
{
 void Set(const EAStringC *const,AptValue *const);
 
}
;
static __forceinline bool isText(AptCIH *cih)
{
 if(!cih)aptAssert("this",CIH_FILE,0xC4);
 const AptValue *v=(const AptValue*)cih;
 return ((const Rva006DBB30SarDwordField *)v)->get()==15 && !v->isUndefined();
 
}
static __forceinline bool isButton(AptCIH *cih)
{
 if(!cih)aptAssert("this",CIH_FILE,0xB5);
 const AptValue *v=(const AptValue*)cih;
 return ((const Rva006DBB30SarDwordField *)v)->get()==14 && !v->isUndefined();
 
}
class Rva006EBFF0 
{
 public:void rva006EBE60(AptValue*);
 
}
;
class Rva006E1260 
{
 public:void call(void*);
 
}
;
class Rva006E9A40List 
{
 public:void add(AptCIH*);
 
}
;
class Rva006E0DE0 
{
 public:int rva006E0DE0(AptValue*);
 
}
;
template<class T>class AptValueSet 
{
 public:unsigned short reserved,count;
 T *items;
 bool has(T)const;
 
}
;
class Rva006E34D0 
{
 public:
 char unknown00[0x20];
 AptValueSet<AptValue*> contexts,cihs;
 
}
;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
static __forceinline void addSet(AptValueSet<AptValue*> *set,AptValue *v)
{
 ((Rva006E9A40List*)set)->add((AptCIH*)v);
 
}
extern AptActionInterpreter g_aptDateInterpreter;
struct R4Word 
{
 const char*name;
 int id;
 
}
;
const R4Word *Rva008ABF40(const char*,unsigned int);
const R4Word *Rva008D48F0(const char*,unsigned int);
EAStringC *Rva0070B4F0GetString(int);
void __cdecl Rva006CC110Log(int,const char*,...);
struct TextDefinition 
{
 char unknown00[0x2C];
 int multiline;
 int wordWrap;
 const char*defaultText;
 
}
;
struct TextInstance 
{
 char unknown00[0xC];
 TextDefinition *definition;
 char unknown10[8];
 EAStringC text,variable;
 int unknown20;
 unsigned textColor;
 int maxScroll;
 int scroll;
 unsigned backgroundColor;
 unsigned borderColor;
 int autoSize;
 char unknown3C[0x50-0x3C];
 float left,top,right,bottom;
 char unknown60[0xC];
 unsigned dirty;
 int unknown70;
 unsigned reserved0:1,border:1,background:1,mouseWheel:1,reserved4:28;
 
}
;
// Native event property masks at VA CEC648; populated from retail data below.
static const unsigned int eventMasks[18]=
{
 0x100,0x10000,0x8000,0x2,0x40,0x80,0xFFFFFFFF,0x1,0x10,0x8,0x20,0x400,0x800,0x1000,0x4000,0x2000,0xFFFFFFFF,0x4
}
;
extern "C" int __cdecl atoi(const char*);
extern "C" long __cdecl strtol(const char*,char**,int);
class Rva006D89D0ByteField 
{
 public:unsigned char get()const;
 
}
;
class Rva00723490FloatField 
{
 public:float get()const;
 
}
;
class Rva00144010Opaque 
{
 public:int rva00144010();
 
}
;
bool __cdecl rva006EE6C0(AptValue *context,const EAStringC *name,AptValue *value)

{
 float number;
 if(!context->isCIH(false))aptAssert("pContext->isCIH()",CHARACTER_FILE,0x669);
 AptCIH *cih=context->c_cih(false);
 if(isText(cih)) 
 {
  const R4Word *word=Rva008ABF40(name->rva00620090(),name->rva006D3750());
  if(word)
  {
   TextInstance *text=(TextInstance*)((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E0F40();
   switch(word->id)
   {
    case 1:
    {
     EAStringC s;
     value->toString(s);
     s.MakeLower();
     if(text->autoSize==3 && (s.rva006D30D0(Rva0070B4F0GetString(0x34)) || s.rva006D30D0(Rva0070B4F0GetString(0x61)))) text->dirty|=8;
     else text->dirty|=0x10;
     if(s.IsEqualTo(Rva0070B4F0GetString(0x56)) || s.IsEqualTo(Rva0070B4F0GetString(0xA8)))text->autoSize=0;
     else if(s.IsEqualTo(Rva0070B4F0GetString(0x29)))text->autoSize=2;
     else if(s.IsEqualTo(Rva0070B4F0GetString(0x7E)))text->autoSize=1;
     else if(s.IsEqualTo(Rva0070B4F0GetString(0x34)) || s.IsEqualTo(Rva0070B4F0GetString(0x61)))text->autoSize=3;
     text->dirty=(text->dirty&~1u)|4u;
     return true;
     
    }
    case 2:text->background=((BfmeAptValue006DCD20*)value)->toInteger();
    text->dirty=(text->dirty&~1u)|0x20;
    return true;
    case 3:text->backgroundColor=((BfmeAptValue006DCD20*)value)->toInteger()|0xFF000000;
    text->dirty=(text->dirty&~1u)|0x40;
    return true;
    case 4:text->border=((BfmeAptValue006DCD20*)value)->toInteger();
    text->dirty=(text->dirty&~1u)|0x80;
    return true;
    case 5:text->borderColor=((BfmeAptValue006DCD20*)value)->toInteger()|0xFF000000;
    text->dirty=(text->dirty&~1u)|0x100;
    return true;
    case 6:case 8:case 16:return true;
    case 10:text->definition->multiline=((BfmeAptValue006DCD20*)value)->toInteger();
    break;
    case 11:
    {
     int n=((BfmeAptValue006DCD20*)value)->toInteger();
     int old=text->scroll;
     if(text->dirty&4)
     {
      ((Rva006E1260*)context->c_cih(false))->call(context->c_cih(false)->parent);
      
     }
     text->scroll=n;
     if(text->scroll>text->maxScroll)text->scroll=text->maxScroll;
     if(text->scroll<1)text->scroll=1;
     if(old!=text->scroll)text->dirty=0x204;
     break;
     
    }
    case 12:
    {
     EAStringC s;
     value->toString(s);
     if(text->text.rva006D30D0(&s))
     {
      text->text=s;
      if(!text->variable.IsEmpty())
      {
       AptCIH *parent=context->c_cih(false);
       while(parent && !parent->rva006CFCD0() && const_cast<AptCIH*&>(parent->parent))parent=const_cast<AptCIH*&>(parent->parent);
       AptString *created=AptString::Create();
       created->value()=s;
       g_aptDateInterpreter.setVariable((AptValue*)parent,0,&text->variable,created,1,1,0);
       
      }
      text->dirty=0x204;
      
     }
     return true;
     
    }
    case 13:text->textColor=((BfmeAptValue006DCD20*)value)->toInteger()|0xFF000000;
    text->dirty=(text->dirty&~1u)|0x400;
    return true;
    case 17:
    {
     EAStringC s;
     value->toString(s);
     if(text->variable.rva006D30D0(&s))
     {
      text->variable=s;
      AptCIH *parent=context->c_cih(false);
      ((Rva006EBFF0*)text)->rva006EBE60((AptValue*)parent);
      text->dirty=(text->dirty&~1u)|0x204;
      
     }
     return true;
     
    }
    case 18:text->definition->wordWrap=((BfmeAptValue006DCD20*)value)->toInteger();
    text->dirty=(text->dirty&~1u)|0x1004;
    return true;
    case 19:
    {
     float n=value->toFloat();
     if(n<0)return true;
     text->bottom=n+text->top;
     text->dirty=(text->dirty&~1u)|0x2004;
     return true;
     
    }
    case 20:
    {
     float n=value->toFloat();
     if(n<0)return true;
     text->right=n+text->left;
     text->dirty=(text->dirty&~1u)|0x4004;
     return true;
     
    }
    case 21:
    {
     int n=((BfmeAptValue006DCD20*)value)->toInteger();
     text->mouseWheel=n;
     if(n==1)
     {
      AptValueSet<AptValue*> *set=&g_bfmeAptPtrAtE176D0->contexts;
      if(!set->has(context))
      {
       addSet(set,context);
       addSet(&g_bfmeAptPtrAtE176D0->cihs,(AptValue*)context->c_cih(false));
       
      }
      
     }
     break;
     
    }
    
   }
   
  }
  
 }
 if(context->c_cih(false)->rva006CFCD0() || isButton(context->c_cih(false)) || (unsigned char)((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0())
 {
  const R4Word *word=Rva008D48F0(name->rva00620090(),name->rva006D3750());
  if(word)
  {
   cih=context->c_cih(false);
   switch(word->id)
   {
    case 1:if(value->isUndefined())return false;
    number=value->toFloat();
    cih->factorySetProperty(0,number,true);
    break;
    case 2:if(value->isUndefined())return false;
    number=value->toFloat();
    cih->factorySetProperty(1,number,true);
    return true;
    case 11:
    {
     number=value->toFloat();
     if(number>180.0f)number-=360.0f;
     cih->factorySetProperty(6,number,true);
     return true;
     
    }
    case 7:number=value->toFloat();
    cih->factorySetProperty(7,number,true);
    return true;
    case 3:number=value->toFloat();
    cih->factorySetProperty(2,number,true);
    return true;
    case 4:number=value->toFloat();
    cih->factorySetProperty(3,number,true);
    return true;
    case 8:number=value->toFloat();
    cih->factorySetProperty(11,number,false);
    return true;
    case 9:
    {
     number=value->toFloat();
     if(number<0)return true;
     if(number==0)number=.0001f;
     Rect r;
     cih->rva006E1DD0(&r);
     float extent=r.right-r.left;
     if(extent==0) return true;
     {
      cih->factoryEnsureProperties();
      float scale;
      if(cih->properties[6]!=0)scale=((number-extent)/extent)*100.0f+cih->properties[2];
      else 
      {
       extent=number/extent;
       if(extent<.0001f)extent=.0001f;
       scale=extent*cih->matrix[0]*100.0f;
       
      }
      if(scale<1.1322573f)scale=1.1322573f;
      cih->factorySetProperty(2,scale,true);
      
     }
     return true;
     
    }
    case 10:
    {
     number=value->toFloat();
     if(number<0)return true;
     if(number==0)number=.0001f;
     Rect r;
     cih->rva006E1DD0(&r);
     float extent=r.bottom-r.top;
     if(extent==0) return true;
     {
      cih->factoryEnsureProperties();
      float scale;
      if(cih->properties[6]!=0)scale=((number-extent)/extent)*100.0f+cih->properties[3];
      else 
      {
       extent=number/extent;
       if(extent<.0001f)extent=.0001f;
       scale=extent*cih->matrix[3]*100.0f;
       
      }
      if(scale<1.1322573f)scale=1.1322573f;
      cih->factorySetProperty(3,scale,true);
      
     }
     return true;
     
    }
    case 200:case 203:case 207:case 217:
    {
     if((unsigned char)((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0())return false;
     int mask=eventMasks[word->id-200];
     AptNativeHash *hash=cih->slot3();
     hash->Set(name,value);
     if(!value || value->isUndefined())cih->RemoveEventHandler(mask);
     else cih->SetEventHandler(mask);
     return true;
     
    }
    case 201:case 202:case 204:case 205:case 208:case 209:case 210:case 211:case 212:case 213:case 214:case 215:
    {
     if((unsigned char)((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0())return false;
     int mask=eventMasks[word->id-200];
     AptNativeHash *hash=cih->slot3();
     hash->Set(name,value);
     if(!value || value->isUndefined())
     {
      cih->RemoveEventHandler(mask);
      if(context->c_cih(false)->IsSpriteInst(false) && !cih->rva006E1F90(0xBFCF8))
      {
       AptValueSet<AptValue*> *set=&g_bfmeAptPtrAtE176D0->cihs;
       if(set->has((AptValue*)cih))((Rva006E0DE0*)set)->rva006E0DE0((AptValue*)cih);
       
      }
      
     }
     else
     {
      cih->SetEventHandler(mask);
      if(context->c_cih(false)->IsSpriteInst(false)||context->c_cih(false)->IsAnimationInst(false))
      {
       AptValueSet<AptValue*> *set=&g_bfmeAptPtrAtE176D0->cihs;
       if(!set->has((AptValue*)cih))addSet(set,(AptValue*)cih);
       
      }
      
     }
     return true;
     
    }
    default:
    if(name->rva006D3510("x")||name->rva006D3510("y")||name->rva006D3510("rotation")||name->rva006D3510("alpha")||name->rva006D3510("xscale")||name->rva006D3510("yscale")||name->rva006D3510("visible")||name->rva006D3510("width")||name->rva006D3510("height"))
    {
     Rva006CC110Log(3,"AptCharacterInst (MovieClip): Incorrect case for '%s'.\n",name->rva00620090());
     aptAssert("0",CHARACTER_FILE,0x859);
     
    }
    return false;
    
   }
   return true;
   
  }
  if(name->rva006D3510("this"))aptAssert("NOT_REACHED",CHARACTER_FILE,0x862);
  
 }
 return false;
 
}

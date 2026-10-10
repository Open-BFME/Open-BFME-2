// ?rva006EE6C0@@YA_NPAVAptValue@@PBVEAStringC@@0@Z
// partial score=0.9142912937368378 date=2026-10-10
void __debugbreak();
#pragma intrinsic(__debugbreak)
// cl: /O2 /DNDEBUG /MD /EHsc
// Target 0x006EE3B0 (393B) and 0x006EE540 (373B), with entry/return boundaries
// confirmed in game.dat. reverse/string_xrefs.tsv names their callback slots
// gAptFuncs.pfnGetBytesTotal and gAptFuncs.pfnGetBytesLoaded; the matching
// ActionScript property names are also in R4PerfectHashWordSets.cpp. The
// target calls through those slots with a String path and converts the
// returned byte count to an Apt float. Slot identity is table evidence; the
// address-derived global names below do not claim an original source name.
// The +0x34 resource pointer and +8 EAStringC field follow the target loads.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class AptCIH;
class EAStringC;
class AptValue
{
public:
    AptCIH *c_cih(bool bUndefinedOK);
    bool isCIH(bool bUndefinedOK) const;
    int getVtblIndex() const;
    bool isUndefined() const;
    float toFloat() const;
    int toInteger() const;
    void toString(EAStringC &) const;
};

struct AptNativeHash;
class AptCIH {
public:
 virtual void slot0(); virtual void slot1(); virtual void slot2();
 virtual AptNativeHash *slot3();
 char unknown04[8]; float matrix[6];
 char unknown24[0x44-0x24]; float *properties; AptCIH *parent;
 void *member4C;char unknown50[8];
 signed int depth:17;unsigned int unknownDepth17:15;int unknown5c;
 bool rva006CFCD0()const;
 bool IsSpriteInst(bool)const; bool IsAnimationInst(bool)const;
 void factorySetProperty(int,float,bool);
 void factoryEnsureProperties(); void rva006E1DD0(void*);
 void SetEventHandler(int); void RemoveEventHandler(int);
 int rva006E1F90(int);
};

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
    };
private:
    StringDataC *data;
public:
    EAStringC();
    static void FreeData(StringDataC *);
    EAStringC &clear();
    EAStringC &operator=(const EAStringC&);
    ~EAStringC();
    int GetAt(int)const;bool IsEmpty()const;unsigned int rva006D3750()const;
 bool IsEqualTo(const EAStringC*)const;bool rva006D30D0(const EAStringC*)const;
 bool rva006D3510(const char*)const;EAStringC &MakeLower();
 EAStringC &Rva006D4F00Append(const EAStringC &other);
    const char *rva00620090() const;
};
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
};

// Retail preserves the unsigned-address addition before the resource load.
// Using direct pointer arithmetic folds these two instructions in MSVC 7.1.
static __forceinline EAStringC &rva006EECharacterUrl(void *character)
{
    unsigned int address = (unsigned int)character;
    address += 0x34;
    void *resource = *(void **)address;
    return *(EAStringC *)((char *)resource + 8);
}
extern int (__cdecl *g_rva00A177BC)(const char *, int);
extern int (__cdecl *g_rva00A177C0)(const char *, int);
AptValue *__cdecl Rva008A4EA0MakeFloat(float value);

static __forceinline bool rva006EEIsDefinedMovieClip(AptCIH *cih)
{
    if (!cih) {
        g_bfmeAptAssertAtE17734(
            "this",
            "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",
            0xD3);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    const AptValue *value = (const AptValue *)cih;
    return value->getVtblIndex() == 0x12 && !value->isUndefined();
}

// ?rva006ee3b0@@YAPAVAptValue@@PAV1@@Z @0x006EE3B0, 393B.
AptValue *__cdecl rva006ee3b0(AptValue *value)
{
    EAStringC url;

    AptCIH *initial = value->c_cih(false);
    if (!initial->member4C)
        return Rva008A4EA0MakeFloat(0.0f);
    if (value->isCIH(false)) {
        AptCIH *cih = value->c_cih(false);
        if (rva006EEIsDefinedMovieClip(cih)) {
            cih = value->c_cih(false);
            url.Rva006D4F00Append(rva006EECharacterUrl(
                ((Rva006CD650 *)cih)->rva006CD650()));
        }
    }

    if (!g_rva00A177BC) {
        g_bfmeAptAssertAtE17734("gAptFuncs.pfnGetBytesTotal",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",
            0x636);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    float byteCount = 0.0f;
    AptCIH *cih = value->c_cih(false);
    if (rva006EEIsDefinedMovieClip(cih))
        byteCount = (float)g_rva00A177BC(url.rva00620090(), 0);
    return Rva008A4EA0MakeFloat(byteCount);
}

// ?rva006ee540@@YAPAVAptValue@@PAV1@@Z @0x006EE540, 373B.
AptValue *__cdecl rva006ee540(AptValue *value)
{
    EAStringC url;

    if (value->isCIH(false)) {
        AptCIH *cih = value->c_cih(false);
        if (rva006EEIsDefinedMovieClip(cih)) {
            cih = value->c_cih(false);
            url.Rva006D4F00Append(rva006EECharacterUrl(
                ((Rva006CD650 *)cih)->rva006CD650()));
        }
    }

    if (!g_rva00A177C0) {
        g_bfmeAptAssertAtE17734("gAptFuncs.pfnGetBytesLoaded",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",
            0x64B);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    float byteCount = 0.0f;
    AptCIH *cih = value->c_cih(false);
    if (rva006EEIsDefinedMovieClip(cih))
        byteCount = (float)g_rva00A177C0(url.rva00620090(), 0);
    return Rva008A4EA0MakeFloat(byteCount);
}

class AptInteger {public:static AptValue *Create(int);};
class AptBasePtrStack {public:AptValue *At(int);};
struct AptActionInterpreter {AptBasePtrStack stack;bool setVariable(AptValue*,AptValue*,const EAStringC*,AptValue*,int,int,int);};
extern AptActionInterpreter g_aptDateInterpreter;
static int (__cdecl *pointHitTestCallback)(float,float,void*);
// 006ECA70: target gAptFuncs.pfnPointHitTest assertion identifies the callback
// slot; its retail data word is initially zero. This is a private typed view
// of that unclaimed slot, not a claim about the original global's scope.
// Native At calls use the interpreter's stack prefix at offset zero. The
// two bounds rectangles form one aggregate to preserve the measured slots:
// other +8 and receiver +18. All four bounds tests are inclusive and ordered.
struct Rect {float left,top,right,bottom;};
AptValue *__cdecl Rva006ECA70PointHitTest(void *self,int count)
{
 struct {Rect otherRect,ownRect;} bounds;
 if(count==1){
  AptValue *other=g_aptDateInterpreter.stack.At(0);
  if(other->isCIH(true)){
   AptCIH *cih=other->c_cih(false);
   ((AptValue*)self)->c_cih(false)->rva006E1DD0(&bounds.ownRect);
   cih->rva006E1DD0(&bounds.otherRect);
   if(bounds.otherRect.left<=bounds.ownRect.right && bounds.otherRect.right>=bounds.ownRect.left && bounds.otherRect.bottom>=bounds.ownRect.top && bounds.otherRect.top<=bounds.ownRect.bottom)return AptInteger::Create(1);
  }
 }else if(count>1){
  float x=g_aptDateInterpreter.stack.At(0)->toFloat();
  float y=g_aptDateInterpreter.stack.At(1)->toFloat();
  int shape=0;
  if(count>2)shape=g_aptDateInterpreter.stack.At(2)->toInteger();
  if(shape){
   if(!pointHitTestCallback){
    g_bfmeAptAssertAtE17734("gAptFuncs.pfnPointHitTest","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",0x58C);
    if(g_bfmeAptBreakOnAssertAtDDC01C){__debugbreak();}
   }
   return AptInteger::Create(pointHitTestCallback(x,y,self));
  }
  ((AptValue*)self)->c_cih(false)->rva006E1DD0(&bounds.ownRect);
  if(x>=bounds.ownRect.left && x<=bounds.ownRect.right && y>=bounds.ownRect.top && y<=bounds.ownRect.bottom)return AptInteger::Create(1);
 }
 return AptInteger::Create(0);
}

class Rva008A4570Owner {public:bool nameEquals(const char*);};
class Rva006EB4B0 {
public:EAStringC font;float size;int color,align;unsigned flags;int indent,left,right;
 Rva006EB4B0(AptValue*,float,int,int,int,int,int,int,AptValue*,int,int,int,int);
 Rva006EB4B0(const Rva006EB4B0&);
};
Rva006EB4B0::Rva006EB4B0(AptValue *fontValue,float sizeValue,int colorValue,int bold,int italic,int underline,int unused6,int unused7,AptValue *alignValue,int leftValue,int rightValue,int indentValue,int unused12)
: size(sizeValue),color(colorValue)
{
 flags=0;
 if(bold==0)flags|=0x10000;
 if(bold==1)flags|=0x10001;
 if(italic==0)flags|=0x100000;
 if(italic==1)flags|=0x100010;
 if(underline==0)flags|=0x1000000;
 if(underline==1)flags|=0x1000100;
 indent=indentValue;left=leftValue;right=rightValue;
 if(!fontValue->isUndefined())fontValue->toString(font);
 if(!alignValue->isUndefined()){
  EAStringC str;alignValue->toString(str);
  Rva008A4570Owner *s=(Rva008A4570Owner*)&str;
  if(s->nameEquals("left")||s->nameEquals("true"))align=0;
  else if(s->nameEquals("center"))align=2;
  else if(s->nameEquals("right"))align=1;
  else align=3;
 }else align=3;
}

// Native C6F0..C72A: signed17-bit depth at CIH+58 biased by0x4000.
// WB1782970 confirms the same operation with its independent +5C layout.
// Callback identity remains address-derived; no inferred original name.
extern AptValue *gpUndefinedValue;
AptValue *Rva006EC6F0Depth(AptValue *context,int unusedArgumentCount){
 if(context->isCIH(false))return AptInteger::Create(context->c_cih(false)->depth-0x4000);
 return gpUndefinedValue;
}

// Native CE30..CEB4 copies the same32B format state; -1 leaves three
// destination fields untouched exactly as native. Reference signature is
// structural inference; all field reads/writes and conditional copies are
// target facts, and the constructor name remains address-derived.
Rva006EB4B0::Rva006EB4B0(const Rva006EB4B0 &other){
 align=other.align;color=other.color;font=other.font;size=other.size;flags=other.flags;
 if(other.indent!=-1)indent=other.indent;
 if(other.left!=-1)left=other.left;
 if(other.right!=-1)right=other.right;
}

// AptCharacter.cpp property-set worker. Target EE6C0..EF404, then native
// switch tables EF408..EF564. WB17838A0 is a semantic/structure guide only.
// All offsets below are measured from native accesses, not WB's +4 CIH view.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char*,const char*,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
static __forceinline void aptAssert(const char *test,const char *file,int line){
 g_bfmeAptAssertAtE17734(test,file,line);
 if(g_bfmeAptBreakOnAssertAtDDC01C){__debugbreak();}
}
#define CHARACTER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp"
#define CIH_FILE "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"

class AptCIH;

class BfmeAptValue006DCD20 {
virtual void vtableSlot0();
public:unsigned int m_flags;
 bool isUndefined()const;BfmeAptValue006DCD20 *checkedString();int toInteger()const;
 bool rva006E02B0()const; void *rva006E0F40()const;
};
class AptString:public AptValue {
public:static AptString *Create();
 __forceinline EAStringC &value(){return *(EAStringC*)((char*)this+8);}
};
struct AptNativeHash {void Set(const EAStringC *const,AptValue *const);};

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

// Native event property masks at VA CEC648; populated from retail data below.
static const unsigned int eventMasks[18]={0x100,0x10000,0x8000,0x2,0x40,0x80,0xFFFFFFFF,0x1,0x10,0x8,0x20,0x400,0x800,0x1000,0x4000,0x2000,0xFFFFFFFF,0x4};




extern "C" int __cdecl atoi(const char*);
extern "C" long __cdecl strtol(const char*,char**,int);
class Rva006D89D0ByteField {public:unsigned char get()const;};
class Rva00723490FloatField {public:float get()const;};
class Rva00144010Opaque {public:int rva00144010();};
extern BfmeAptValue006DCD20 *g_aptUndefinedAtE18078;


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
    EAStringC s;(value?value:value)->toString(s);s.MakeLower();
    if(text->autoSize==3 && (s.rva006D30D0(Rva0070B4F0GetString(0x34)) || s.rva006D30D0(Rva0070B4F0GetString(0x61)))) text->dirty|=8;
    else text->dirty|=0x10;
    if(s.IsEqualTo(Rva0070B4F0GetString(0x56)) || s.IsEqualTo(Rva0070B4F0GetString(0xA8)))text->autoSize=0;
    else if(s.IsEqualTo(Rva0070B4F0GetString(0x29)))text->autoSize=2;
    else if(s.IsEqualTo(Rva0070B4F0GetString(0x7E)))text->autoSize=1;
    else if(s.IsEqualTo(Rva0070B4F0GetString(0x34)) || s.IsEqualTo(Rva0070B4F0GetString(0x61)))text->autoSize=3;
    text->dirty=(text->dirty&~1u)|4u;return true;
   }
   case 2:text->background=((BfmeAptValue006DCD20*)(value?value:value))->toInteger();text->dirty=(text->dirty&~1u)|0x20;return true;
   case 3:text->backgroundColor=((BfmeAptValue006DCD20*)(value?value:value))->toInteger()|0xFF000000;text->dirty=(text->dirty&~1u)|0x40;return true;
   case 4:text->border=((BfmeAptValue006DCD20*)(value?value:value))->toInteger();text->dirty=(text->dirty&~1u)|0x80;return true;
   case 5:text->borderColor=((BfmeAptValue006DCD20*)(value?value:value))->toInteger()|0xFF000000;text->dirty=(text->dirty&~1u)|0x100;return true;
   case 6:case 8:case 16:return true;
   case 10:text->definition->multiline=((BfmeAptValue006DCD20*)(value?value:value))->toInteger();break;
   case 11:{int n=((BfmeAptValue006DCD20*)(value?value:value))->toInteger();int old=(text?text:text)->scroll;
    if(text->dirty&4){AptCIH *parent=context->c_cih(false)->parent;((Rva006E1260*)context->c_cih(false))->call(parent);}
    text->scroll=n;if(text->scroll>text->maxScroll)text->scroll=text->maxScroll;if(text->scroll<1)text->scroll=1;
    if(old!=text->scroll)text->dirty=0x204;break;
   }
   case 12:{EAStringC s;(value?value:value)->toString(s);if(text->text.rva006D30D0(&s)){
    text->text=s;
    if(!text->variable.IsEmpty()){
     AptCIH *parent=context->c_cih(false);
     while(parent && !parent->rva006CFCD0() && parent->parent)parent=parent->parent;
     AptString *created=AptString::Create();created->value()=s;
     g_aptDateInterpreter.setVariable((AptValue*)parent,0,&text->variable,created,1,1,0);
    }
    text->dirty=0x204;
   }return true;}
   case 13:text->textColor=((BfmeAptValue006DCD20*)(value?value:value))->toInteger()|0xFF000000;text->dirty=(text->dirty&~1u)|0x400;return true;
   case 17:{EAStringC s;(value?value:value)->toString(s);if(text->variable.rva006D30D0(&s)){
    text->variable=s;AptCIH *parent=context->c_cih(false);((Rva006EBFF0*)text)->rva006EBE60((AptValue*)parent);text->dirty=(text->dirty&~1u)|0x204;
   }return true;}
   case 18:text->definition->wordWrap=((BfmeAptValue006DCD20*)(value?value:value))->toInteger();text->dirty=(text->dirty&~1u)|0x1004;return true;
   case 19:{float n=(value?value:value)->toFloat();if(n<0)return true;text->bottom=n+text->top;text->dirty=(text->dirty&~1u)|0x2004;return true;}
   case 20:{float n=(value?value:value)->toFloat();if(n<0)return true;text->right=n+text->left;text->dirty=(text->dirty&~1u)|0x4004;return true;}
   case 21:{int n=((BfmeAptValue006DCD20*)(value?value:value))->toInteger();text->mouseWheel=n;
    if(n==1){
     AptValueSet<AptValue*> *set=&g_bfmeAptPtrAtE176D0->contexts;
     if(!set->has(context)){
     addSet(set,context);
     addSet(&g_bfmeAptPtrAtE176D0->cihs,(AptValue*)context->c_cih(false));
    }}break;
   }
   }
  }
 }
 if(context->c_cih(false)->rva006CFCD0() || isButton(context->c_cih(false)) || ((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0()){
  const R4Word *word=Rva008D48F0(name->rva00620090(),name->rva006D3750());
  if(word){
   cih=context->c_cih(false);
   switch(word->id){
   case 1:if((value?value:value)->isUndefined())return false;number=(value?value:value)->toFloat();cih->factorySetProperty(0,number,true);return true;
   case 2:if((value?value:value)->isUndefined())return false;number=(value?value:value)->toFloat();cih->factorySetProperty(1,number,true);return true;
   case 11:{number=(value?value:value)->toFloat();if(number>180.0f)number-=360.0f;cih->factorySetProperty(6,number,true);return true;}
   case 3:number=(value?value:value)->toFloat();cih->factorySetProperty(2,number,true);return true;
   case 4:number=(value?value:value)->toFloat();cih->factorySetProperty(3,number,true);return true;
   case 7:number=(value?value:value)->toFloat();cih->factorySetProperty(7,number,true);return true;
   case 8:number=(value?value:value)->toFloat();cih->factorySetProperty(11,number,false);return true;
   case 9:{number=(value?value:value)->toFloat();if(number<0)return true;if(number==0)number=.0001f;
    Rect r;cih->rva006E1DD0(&r);float extent=r.right-r.left;
    if(extent!=0){cih->factoryEnsureProperties();float scale;
     if(cih->properties[6]!=0)scale=((number-extent)/extent)*100.0f+cih->properties[2];
     else {extent=number/extent;if(extent<.0001f)extent=.0001f;scale=extent*cih->matrix[0]*100.0f;}
     if(scale<1.1322573f)scale=1.1322573f;cih->factorySetProperty(2,scale,true);
    }return true;
   }
   case 10:{number=(value?value:value)->toFloat();if(number<0)return true;if(number==0)number=.0001f;
    Rect r;cih->rva006E1DD0(&r);float extent=r.bottom-r.top;
    if(extent!=0){cih->factoryEnsureProperties();float scale;
     if(cih->properties[6]!=0)scale=((number-extent)/extent)*100.0f+cih->properties[3];
     else {extent=number/extent;if(extent<.0001f)extent=.0001f;scale=extent*cih->matrix[3]*100.0f;}
     if(scale<1.1322573f)scale=1.1322573f;cih->factorySetProperty(3,scale,true);
    }return true;
   }
   case 200:case 203:case 207:case 217:{
    if(((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0())return false;
    int mask=eventMasks[word->id-200];AptNativeHash *hash=cih->slot3();hash->Set(name,value);
    if(!value || (value?value:value)->isUndefined())cih->RemoveEventHandler(mask);else cih->SetEventHandler(mask);
    return true;
   }
   case 201:case 202:case 204:case 205:case 208:case 209:case 210:case 211:case 212:case 213:case 214:case 215:{
    if(((BfmeAptValue006DCD20*)context->c_cih(false))->rva006E02B0())return false;
    int mask=eventMasks[word->id-200];AptNativeHash *hash=cih->slot3();hash->Set(name,value);
    if(!value || (value?value:value)->isUndefined()){
     cih->RemoveEventHandler(mask);
     if(context->c_cih(false)->IsSpriteInst(false) && !cih->rva006E1F90(0xBFCF8)){
      AptValueSet<AptValue*> *set=&g_bfmeAptPtrAtE176D0->cihs;
      if(set->has((AptValue*)cih))((Rva006E0DE0*)set)->rva006E0DE0((AptValue*)cih);
     }
    }else{
     cih->SetEventHandler(mask);
     if(context->c_cih(false)->IsSpriteInst(false)||context->c_cih(false)->IsAnimationInst(false)){
      AptValueSet<AptValue*> *set=&g_bfmeAptPtrAtE176D0->cihs;
      if(!set->has((AptValue*)cih))addSet(set,(AptValue*)cih);
     }
    }return true;
   }
   default:
    if(name->rva006D3510("x")||name->rva006D3510("y")||name->rva006D3510("rotation")||name->rva006D3510("alpha")||name->rva006D3510("xscale")||name->rva006D3510("yscale")||name->rva006D3510("visible")||name->rva006D3510("width")||name->rva006D3510("height")){
     Rva006CC110Log(3,"AptCharacterInst (MovieClip): Incorrect case for '%s'.\n",name->rva00620090());aptAssert("0",CHARACTER_FILE,0x859);
    }return false;
   }
  }
  if(name->rva006D3510("this"))aptAssert("NOT_REACHED",CHARACTER_FILE,0x862);
 }
 return false;
}

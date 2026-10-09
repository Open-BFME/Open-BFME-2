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

class AptCIH
{
public:
    unsigned char prefix[0x4c];
    void *member4C;
    char unknown50[8];
    signed int depth:17;
    unsigned int unknownDepth17:15;
    void rva006E1DD0(void *);
};

class EAStringC
{
    void *data;
public:
    EAStringC(){clear();}
    EAStringC &clear();
    EAStringC &operator=(const EAStringC&);
    ~EAStringC();
    EAStringC &Rva006D4F00Append(const EAStringC &other);
    const char *rva00620090() const;
};

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
struct AptActionInterpreter {AptBasePtrStack stack;};
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
    if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
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

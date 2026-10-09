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
class AptValue
{
public:
    AptCIH *c_cih(bool bUndefinedOK);
    bool isCIH(bool bUndefinedOK) const;
    int getVtblIndex() const;
    bool isUndefined() const;
    float toFloat() const;
    int toInteger() const;
};

class AptCIH
{
public:
    unsigned char prefix[0x4c];
    void *member4C;
    void rva006E1DD0(void *);
};

class EAStringC
{
    void *data;
public:
    EAStringC(){clear();}
    EAStringC &clear();
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

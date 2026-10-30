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
class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

class AptValue
{
public:
    AptCIH *c_cih(bool bUndefinedOK);
    bool isCIH(bool bUndefinedOK) const;
    bool isUndefined() const;
    bool getIsDefined() const;
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
    void *rva006E1170() const;
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
    EAStringC(const char *);
    EAStringC(const EAStringC &);
    EAStringC &clear();
    EAStringC &operator=(const EAStringC&);
    ~EAStringC();
    EAStringC &Rva006D4F00Append(const EAStringC &other);
    const char *rva00620090() const;
    int GetAt(int) const;
    unsigned int rva006D3750() const;
    int rva006D54B0(int,int);
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
    // AptValue::getVtblIndex (donor identity, pinned at 0x006DBB30) is rowed as
    // Rva006DBB30SarDwordField::get; call it by the ledger's name.
    return ((const Rva006DBB30SarDwordField *)value)->get() == 0x12 && !value->isUndefined();
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
struct AptActionInterpreter {AptBasePtrStack stack;void loadVariables(AptValue *,AptValue *,const EAStringC *);};
extern AptActionInterpreter g_aptDateInterpreter;
extern "C" { int (__cdecl *pointHitTestCallback)(float,float,void*) = 0; }
// 006ECA70: target gAptFuncs.pfnPointHitTest assertion identifies the callback
// slot at VA 0x00E177B4; its retail data word is initially zero. Export the
// ledger-owned slot for the W3D Apt callback installer in Rva000ABA2F.cpp.
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

// Native CC20..CCA5: Ghidra-unlisted gap body between the hit-test and format
// callbacks. With at least one argument it converts stack argument 0 to a
// string and hands it to the interpreter's rowed loadVariables 0x00706370
// with the receiver and a null target; always returns the undefined value.
// The count slot is reused for the string local, as native. Callback name
// remains address-derived.
AptValue *Rva006ECC20LoadVariables(AptValue *self,int count){
 if(count>0){
  AptValue *aptValue=g_aptDateInterpreter.stack.At(0);
  EAStringC url;
  aptValue->toString(url);
  g_aptDateInterpreter.loadVariables(self,0,&url);
 }
 return gpUndefinedValue;
}

class AptLinker {public:void Load(const EAStringC &a,EAStringC b);};
extern AptLinker *g_bfmeAptLinkerAtE176F8;
void rva006ffce0(AptValue *,EAStringC &);
void __debugbreak();
#pragma intrinsic(__debugbreak)

// Native D770..D803: Ghidra-unlisted callback beside the rowed walk at
// 0x006ED490. Resolves the target through the rowed rva007065e0 lookup with
// the receiver, and when that yields a CIH, removes it from its parent
// sprite's display list (+0x4C instance, list at +0x24) through the rowed
// AptDisplayList::removeClonedObject after the AptCIH.h 0x7D
// isSpriteInstBase() assert on the parent (+0x48): the removeMovieClip shape.
// Callback name remains address-derived.
class BfmeAptValue006DCD20;
void rva007065e0(int,int,BfmeAptValue006DCD20 *,BfmeAptValue006DCD20 **);
class Rva006CFCD0
{
public:
	bool isSpriteInstBase() const;
};
class AptDisplayList
{
public:
	AptDisplayList();
	~AptDisplayList();
	void removeClonedObject(AptCIH *);
private:
	void *list; // +0x00
};
AptValue *Rva006ED770RemoveMovieClip(AptValue *self,int){
 BfmeAptValue006DCD20 *found=0;
 rva007065e0((int)self->c_cih(false),0,(BfmeAptValue006DCD20 *)self->c_cih(false),&found);
 if(found && ((AptValue *)found)->isCIH(false)){
  AptCIH *cih=((AptValue *)found)->c_cih(false);
  AptCIH *parent=*(AptCIH **)((char *)cih+0x48);
  if(!((const Rva006CFCD0 *)parent)->isSpriteInstBase()){
   g_bfmeAptAssertAtE17734("isSpriteInstBase()","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",0x7D);
   if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
  }
  ((AptDisplayList *)((char *)parent->member4C+0x24))->removeClonedObject(cih);
 }
 return gpUndefinedValue;
}


// 006EC900 (356 B): the startDrag native. It calls the receiver's first
// virtual slot, makes it the drag target of the drag context at 0xE176D0,
// clears the drag offset and sets the four bounds to -9999.0f. Unless the
// first argument (lock centre) is true, the offset is the context's mouse
// position (+0x74/+0x78, ints) minus the target's x/y (+0x1C/+0x20 of its
// character instance). A second..fifth argument set left/top/right/bottom,
// tested against count > 0..3 as retail does (the lock-centre slot shifts
// the indices); the first bound clears the other three. Returns undefined.
// Names of the context type, its fields and the native are not proved.
class BfmeAptValue006DCD20 {public:BfmeAptValue006DCD20 *rva006DCEA0();BfmeAptValue006DCD20 *rva006DD0E0();BfmeAptValue006DCD20 *checkedFloat();};
class Rva006E34D0
{
public:
 char m_pad0[0x44];
 AptValue *m_dragTarget;
 float m_left,m_top,m_right,m_bottom;
 float m_offsetX,m_offsetY;
 char m_pad60[0x14];
 int m_mouseX,m_mouseY;
};
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class BfmeAptSlot0Target {public:virtual void slot00();};
AptValue *__cdecl Rva006EC900StartDrag(AptValue *self,int count)
{
 ((BfmeAptSlot0Target*)self)->slot00();
 g_bfmeAptPtrAtE176D0->m_dragTarget=self;
 g_bfmeAptPtrAtE176D0->m_offsetX=0;
 g_bfmeAptPtrAtE176D0->m_offsetY=0;
 g_bfmeAptPtrAtE176D0->m_left=-9999.0f;
 g_bfmeAptPtrAtE176D0->m_top=-9999.0f;
 g_bfmeAptPtrAtE176D0->m_right=-9999.0f;
 g_bfmeAptPtrAtE176D0->m_bottom=-9999.0f;
 if(count==0||!((AptValue*)((BfmeAptValue006DCD20*)g_aptDateInterpreter.stack.At(0))->rva006DCEA0())->toInteger()){
  g_bfmeAptPtrAtE176D0->m_offsetX=(float)g_bfmeAptPtrAtE176D0->m_mouseX-((float*)self->c_cih(false))[7];
  g_bfmeAptPtrAtE176D0->m_offsetY=(float)g_bfmeAptPtrAtE176D0->m_mouseY-((float*)self->c_cih(false))[8];
 }
 if(count>0){
  g_bfmeAptPtrAtE176D0->m_left=g_aptDateInterpreter.stack.At(1)->toFloat();
  g_bfmeAptPtrAtE176D0->m_top=0;
  g_bfmeAptPtrAtE176D0->m_right=0;
  g_bfmeAptPtrAtE176D0->m_bottom=0;
 }
 if(count>1)g_bfmeAptPtrAtE176D0->m_top=g_aptDateInterpreter.stack.At(2)->toFloat();
 if(count>2)g_bfmeAptPtrAtE176D0->m_right=g_aptDateInterpreter.stack.At(3)->toFloat();
 if(count>3)g_bfmeAptPtrAtE176D0->m_bottom=g_aptDateInterpreter.stack.At(4)->toFloat();
 return gpUndefinedValue;
}

// Native DF20..DFEA: Ghidra-unlisted depth swap callback. With one argument
// (or a non-CIH receiver) it reads stack argument 0: a defined CIH trades its
// signed 17-bit +0x58 depth for the receiver's, and the receiver's rowed
// rva006E1170 character instance stores the other's old depth plus one at
// +4; an undefined argument stores -1 there. Name remains address-derived.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
class AptFloat {public:float GetFloat() const;};
class AptNativeHash {public:AptValue *Lookup(const EAStringC *const) const;void Set(const EAStringC *const,AptValue *const);};
class BfmeAptObject006DD0E0 {public:char m_pad0[8];AptNativeHash m_hash;};
struct BfmeM1208;
void bfmeMul1208(const BfmeM1208 *,const BfmeM1208 *,BfmeM1208 *);
AptValue *Rva008A4EA0MakeFloat(float);
// Retail 0x006ECCB0 (381 B), Apt Point-like localToGlobal: the barrier before the
// c_cih walk keeps the point.y store ahead of the receiver load.
AptValue *__cdecl Rva006ECCB0LocalToGlobal(AptValue *self,int count)
{
 if(count>=2){
  g_bfmeAptAssertAtE17734("nParams < 2","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",0xB63);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 if(count==0)return gpUndefinedValue;
 BfmeAptObject006DD0E0 *object=(BfmeAptObject006DD0E0*)((BfmeAptValue006DCD20*)g_aptDateInterpreter.stack.At(0))->rva006DD0E0();
 EAStringC xName("x");
 EAStringC yName("y");
 AptValue *xValue=object->m_hash.Lookup(&xName);
 AptValue *yValue=object->m_hash.Lookup(&yName);
 AptFloat *xFloat=(AptFloat*)((BfmeAptValue006DCD20*)xValue)->checkedFloat();
 AptFloat *yFloat=(AptFloat*)((BfmeAptValue006DCD20*)yValue)->checkedFloat();
 struct {float m[4];float x,y;} point;
 point.x=xFloat->GetFloat();
 point.y=(xFloat ? (yFloat->GetFloat()) : (yFloat->GetFloat()));
 _ReadWriteBarrier();
 for(char *cih=(char*)self->c_cih(false);cih;cih=*(char**)(cih+0x48))
  bfmeMul1208((const BfmeM1208*)(cih+0xC),(const BfmeM1208*)&point,(BfmeM1208*)&point);
 object->m_hash.Set(&xName,Rva008A4EA0MakeFloat(point.x));
 object->m_hash.Set(&yName,Rva008A4EA0MakeFloat(point.y));
 return gpUndefinedValue;
}

AptValue *Rva006EDF20SwapDepths(AptValue *self,int count){
 if(count!=1 && self->isCIH(false))return gpUndefinedValue;
 AptCIH *mine=self->c_cih(false);
 AptValue *aptValue=g_aptDateInterpreter.stack.At(0);
 if(aptValue->isCIH(false)){
  AptCIH *other=aptValue->c_cih(false);
  if(other && ((AptValue *)other)->getIsDefined()){
   int depth=((AptValue *)other)->c_cih(false)->depth;
   ((AptValue *)other)->c_cih(false)->depth=mine->depth;
   ((int *)mine->rva006E1170())[1]=depth+1;
  }
  return gpUndefinedValue;
 }
 if(aptValue!=gpUndefinedValue)return gpUndefinedValue;
 ((int *)mine->rva006E1170())[1]=-1;
 return gpUndefinedValue;
}

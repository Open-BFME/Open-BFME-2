// ?rva00710810@Rva006ECFC0Owner@@QAE_NPAVAptValue@@PBVEAStringC@@0@Z
// partial score=1.0 date=2026-10-10
// Native ECFC0 destructor and ECFC0Owner vtable CECB54 establish this
// family. Native ECEC0..ECF89 and FE4C0..FE57C construct a 0x20-byte
// format state at +0x20 after the D6470 base, then install CECB54.
// Representing that state as a non-polymorphic second base preserves the
// measured intermediate CEA264 store and constructor order. This is a
// structural inference; the offsets, call ABI and repeated copy are target
// facts. The copy-taking constructor accepts a format state, not an Owner.
// Its extra copy follows the same ordered fields and -1 sentinel checks as
// the independently verified CE30 format constructor. No original class
// names are claimed. The old destructor-only pad is replaced by the full
// measured 0x40-byte layout; pool release and both destructor rows retained.
// cl:  /O2 /DNDEBUG /MD /EHsc
// Native 006FE4C0 constructor. Layout from native, base declarations from
// the byte-verified Rva006D6360/Rva006D6470Owner family. WB1760610 guide.
class Rva006D2A60 {
public:
  void freeBlock(void *, int);
};
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class BfmeAptValue006DCD20 {
  virtual void vtableSlot0();
  unsigned int flags;

public:
  BfmeAptValue006DCD20(int);
  virtual ~BfmeAptValue006DCD20();
  int toInteger() const;
  float rva006DD460();
};
class AptValue;
class AptNativeHash {
  int count;
  void *items;
  AptValue *proto, *prototype;
  unsigned int events;

public:
  AptNativeHash(int);
  ~AptNativeHash();
};
class Rva006D6360 : public BfmeAptValue006DCD20 {
  AptNativeHash hash;

public:
  Rva006D6360(int type, int size) : BfmeAptValue006DCD20(type), hash(size) {}
  virtual ~Rva006D6360();
};
class Rva006D6470Owner : public Rva006D6360 {
  unsigned int bits;

public:
  Rva006D6470Owner(int type, int size) : Rva006D6360(type, size) {
    *(unsigned char *)&bits = 0;
    bits &= 0xFFFFFCFF;
  }
  virtual ~Rva006D6470Owner();
  static void operator delete(void *p, unsigned int size) {
    g_pChainBlockAllocatorF4->freeBlock(p, size);
  }

};
class EAStringC {
  void *data;

public:
  EAStringC() { clear(); }
  EAStringC &clear();
  ~EAStringC();
  EAStringC &operator=(const EAStringC &);
  const char *rva00620090() const;
  unsigned int rva006D3750() const;
  bool rva006D3510(const char *) const;
};
class Rva006EB4B0 {
public:
  EAStringC font;
  float size;
  int color, align;
  unsigned flags;
  int indent, left, right;

public:
  Rva006EB4B0(AptValue *, float, int, int, int, int, int, int, AptValue *, int,
              int, int, int);
  Rva006EB4B0(const Rva006EB4B0 &);
  void assign(const Rva006EB4B0 &other) {
    align = other.align;
    color = other.color;
    font = other.font;
    size = other.size;
    flags = other.flags;
    if (other.indent != -1)
      indent = other.indent;
    if (other.left != -1)
      left = other.left;
    if (other.right != -1)
      right = other.right;
  }
};
class Rva006ECFC0Owner : public Rva006D6470Owner, public Rva006EB4B0 {
public:
  Rva006ECFC0Owner(AptValue *, float, int, int, int, int, int, int, AptValue *,
                   int, int, int, int);
  Rva006ECFC0Owner(const Rva006EB4B0 &);
  virtual ~Rva006ECFC0Owner();
  bool rva00710810(AptValue *, const EAStringC *, AptValue *);
};
Rva006ECFC0Owner::Rva006ECFC0Owner(AptValue *font, float size, int color,
                                   int bold, int italic, int underline,
                                   int unused6, int unused7, AptValue *align,
                                   int left, int right, int indent,
                                   int unused12)
    : Rva006D6470Owner(0x24, 8),
      Rva006EB4B0(font, size, color, bold, italic, underline, unused6, unused7,
                  align, left, right, indent, unused12) {}

Rva006ECFC0Owner::Rva006ECFC0Owner(const Rva006EB4B0 &other)
    : Rva006D6470Owner(0x24, 8), Rva006EB4B0(other) {
  Rva006EB4B0::assign(other);
}

Rva006ECFC0Owner::~Rva006ECFC0Owner() {}

class AptValue {public:void toString(EAStringC &) const;};
struct Rva008A4570Owner { void *data; bool nameEquals(const char *); };
struct R4Word { const char *name; int value; };
const R4Word *Rva008D4F80(const char *, unsigned int);
void Rva006CC110Log(int,const char *,...);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
bool Rva006ECFC0Owner::rva00710810(AptValue *context,const EAStringC *name,AptValue *value) {
 const R4Word *word=context?Rva008D4F80(name->rva00620090(),name->rva006D3750()):0;
 if(word) {
  switch(word->value) {
  case 1:{
   EAStringC text;
   value->toString(text);
   if(((Rva008A4570Owner *)&text)->nameEquals("left")||((Rva008A4570Owner *)&text)->nameEquals("true"))align=0;
   else if(((Rva008A4570Owner *)&text)->nameEquals("center"))align=2;
   else if(((Rva008A4570Owner *)&text)->nameEquals("right"))align=1;
   else if(((Rva008A4570Owner *)&text)->nameEquals("false")||((Rva008A4570Owner *)&text)->nameEquals("none"))align=3;
   return true;
  }
  case 5:color=((BfmeAptValue006DCD20 *)value)->toInteger();return true;
  case 6:value->toString(font);return true;
  case 3:{
   EAStringC text;value->toString(text);
   if(((Rva008A4570Owner *)&text)->nameEquals("true"))Rva006EB4B0::flags|=0x10001;
   if(((Rva008A4570Owner *)&text)->nameEquals("false")) {
    Rva006EB4B0::flags|=0x10000;
    if(Rva006EB4B0::flags&1)Rva006EB4B0::flags^=1;
   }
   return true;
  }
  case 7:indent=((BfmeAptValue006DCD20 *)value)->toInteger();return true;
  case 8:{
   EAStringC text;value->toString(text);
   if(((Rva008A4570Owner *)&text)->nameEquals("true"))Rva006EB4B0::flags|=0x100010;
   if(((Rva008A4570Owner *)&text)->nameEquals("false")) {
    Rva006EB4B0::flags|=0x100000;
    if(Rva006EB4B0::flags&0x10)Rva006EB4B0::flags^=0x10;
   }
   return true;
  }
  case 10:left=((BfmeAptValue006DCD20 *)value)->toInteger();return true;
  case 11:right=((BfmeAptValue006DCD20 *)value)->toInteger();return true;
  case 15:{
   EAStringC text;value->toString(text);
   if(((Rva008A4570Owner *)&text)->nameEquals("true"))Rva006EB4B0::flags|=0x1000100;
   if(((Rva008A4570Owner *)&text)->nameEquals("false")) {
    Rva006EB4B0::flags|=0x1000000;
    if(Rva006EB4B0::flags&0x100)Rva006EB4B0::flags^=0x100;
   }
   return true;
  }
  case 14:size=((BfmeAptValue006DCD20 *)value)->rva006DD460();return true;
  case 2:case 4:case 9:case 12:case 13:case 16:return true;
  }
 }
 if(name->rva006D3510("blockIndent")||name->rva006D3510("bullet")||name->rva006D3510("leading")||name->rva006D3510("tabStops")||name->rva006D3510("target")||name->rva006D3510("url")) {
  Rva006CC110Log(3,"AptDate: Incorrect case for '%s'.\n",name->rva00620090());
  g_bfmeAptAssertAtE17734("0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptTextFormat.cpp",393);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 return false;
}

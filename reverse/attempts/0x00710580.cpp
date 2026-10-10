// ?rva00710580@Rva006ECFC0Owner@@QBEPAVAptValue@@PAV2@PBVEAStringC@@@Z
// partial score=0.993865 date=2026-10-10
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
  bool IsEmpty() const;
  bool rva006D3510(const char *) const;
};
class Rva006EB4B0 {
public:
  EAStringC font;
  union { float size; unsigned int sizeBits; };
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
  AptValue *rva00710580(AptValue *,const EAStringC *) const;
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

class AptValue {public:void SetString(const char *);};
class AptString { unsigned char unknown00[8]; public:EAStringC string; static AptString *Create();};
class AptInteger {public:static AptValue *Create(int);};
class AptBoolean {public:static AptValue *Create(bool);};
AptValue *Rva008A4EA0MakeFloat(float);
EAStringC *Rva0070B4F0GetString(int);
struct R4Word {const char *name;int value;};
const R4Word *Rva008D4F80(const char *,unsigned int);
void Rva006CC110Log(int,const char *,...);
extern AptValue *gpUndefinedValue;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

AptValue *Rva006ECFC0Owner::rva00710580(AptValue *context,const EAStringC *name)const {
 const R4Word *word=context?Rva008D4F80(name->rva00620090(),name->rva006D3750()):0;
 if(word) {
  switch(word->value) {
  case 1:{
   AptString *value=AptString::Create();
   EAStringC *text;
   switch(align) {
   case 0:text=Rva0070B4F0GetString(0x56);break;
   case 1:text=Rva0070B4F0GetString(0x7e);break;
   case 2:text=Rva0070B4F0GetString(0x29);break;
   case 3:return gpUndefinedValue;
   default:return gpUndefinedValue;
   }
   value->string=*text;
   return (AptValue *)value;
  }
  case 3:{
   if(!(Rva006EB4B0::flags&0x10000))return gpUndefinedValue;
   bool value=false;if(Rva006EB4B0::flags&1)value=true;
   return AptBoolean::Create(value);
  }
  case 5:
   if(color==-1)return gpUndefinedValue;
   return AptInteger::Create(color&0xffffff);
  case 6:{
   if(font.IsEmpty())return gpUndefinedValue;
   AptString *value=AptString::Create();
   ((AptValue *)value)->SetString(font.rva00620090());
   return (AptValue *)value;
  }
  case 7:
   if(indent==-1)return gpUndefinedValue;
   return AptInteger::Create(indent);
  case 8:{
   if(!(Rva006EB4B0::flags&0x100000))return gpUndefinedValue;
   bool value=false;if(Rva006EB4B0::flags&0x10)value=true;
   return AptBoolean::Create(value);
  }
  case 10:
   if(left==-1)return gpUndefinedValue;
   return AptInteger::Create(left);
  case 11:
   if(right==-1)return gpUndefinedValue;
   return AptInteger::Create(right);
  case 14:
   if(sizeBits==0xbf800000u)return gpUndefinedValue;
   return Rva008A4EA0MakeFloat(size);
  case 15:{
   if(!(Rva006EB4B0::flags&0x1000000))return gpUndefinedValue;
   bool value=false;if(Rva006EB4B0::flags&0x100)value=true;
   return AptBoolean::Create(value);
  }
  }
 }
 if(name->rva006D3510("blockIndent")||name->rva006D3510("bullet")||name->rva006D3510("leading")||name->rva006D3510("tabStops")||name->rva006D3510("target")||name->rva006D3510("url")) {
  Rva006CC110Log(3,"AptDate: Incorrect case for '%s'.\n",name->rva00620090());
  g_bfmeAptAssertAtE17734("0","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptTextFormat.cpp",196);
  if(g_bfmeAptBreakOnAssertAtDDC01C)__debugbreak();
 }
 return 0;
}

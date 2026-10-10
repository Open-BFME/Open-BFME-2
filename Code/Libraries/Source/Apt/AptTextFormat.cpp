// cl: /O2 /arch:SSE /G6 /DNDEBUG /MD /EHsc
// AptTextFormat.cpp: the retail assertion inside the property setter below
// names this file (bfme2patch103 Code/Libraries/Source/Apt/AptTextFormat.cpp,
// line 393); WorldBuilder 0x1760610 carries the same lead.
//
// Native 00710810..00710C64 (1108 bytes, RET 0xC) is slot 8 of the
// Rva006ECFC0Owner vtable at 0x00CECB54. It looks the property name up in
// the gperf word set rowed at 0x007104F0, dispatches through a 16-entry jump
// table onto the 32-byte format state at +0x20, and warns about mis-cased
// TextFormat property names. Target facts: offsets, call ABI, strings and
// the table. The class layout (Rva006D6470Owner base plus the format state
// as a second base) is carried from the byte-verified constructors in
// Code/GameEngine/Source/Common/Rva006ECFC0Siblings.cpp; original class and
// member spellings remain unknown.
//
// This unit only declares the class family: it defines no constructor,
// destructor or inline base body, so it emits no vftable, no scalar deleting
// destructor and no base-constructor COMDAT that could compete with the
// providers other units already own.
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
  Rva006D6360(int type, int size);
  virtual ~Rva006D6360();
};
class Rva006D6470Owner : public Rva006D6360 {
  unsigned int bits;

public:
  Rva006D6470Owner(int type, int size);
  virtual ~Rva006D6470Owner();
};
class EAStringC {
  void *data;

public:
  EAStringC();
  ~EAStringC();
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
};
class Rva006ECFC0Owner : public Rva006D6470Owner, public Rva006EB4B0 {
public:
  Rva006ECFC0Owner(const Rva006EB4B0 &);
  virtual ~Rva006ECFC0Owner();
  bool rva00710810(AptValue *, const EAStringC *, AptValue *);
};

class AptValue {
public:
  void toString(EAStringC &) const;
};
struct Rva008A4570Owner {
  void *data;
  bool nameEquals(const char *);
};
struct R4Word {
  const char *name;
  int value;
};
const R4Word *Rva008D4F80(const char *, unsigned int);
void Rva006CC110Log(int, const char *, ...);
extern void(__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

bool Rva006ECFC0Owner::rva00710810(AptValue *context, const EAStringC *name,
                                   AptValue *value) {
  const R4Word *word =
      context ? Rva008D4F80(name->rva00620090(), name->rva006D3750()) : 0;
  if (word) {
    switch (word->value) {
    case 1: {
      EAStringC text;
      value->toString(text);
      if (((Rva008A4570Owner *)&text)->nameEquals("left") ||
          ((Rva008A4570Owner *)&text)->nameEquals("true"))
        align = 0;
      else if (((Rva008A4570Owner *)&text)->nameEquals("center"))
        align = 2;
      else if (((Rva008A4570Owner *)&text)->nameEquals("right"))
        align = 1;
      else if (((Rva008A4570Owner *)&text)->nameEquals("false") ||
               ((Rva008A4570Owner *)&text)->nameEquals("none"))
        align = 3;
      return true;
    }
    case 5:
      color = ((BfmeAptValue006DCD20 *)value)->toInteger();
      return true;
    case 6:
      value->toString(font);
      return true;
    case 3: {
      EAStringC text;
      value->toString(text);
      if (((Rva008A4570Owner *)&text)->nameEquals("true"))
        Rva006EB4B0::flags |= 0x10001;
      if (((Rva008A4570Owner *)&text)->nameEquals("false")) {
        Rva006EB4B0::flags |= 0x10000;
        if (Rva006EB4B0::flags & 1)
          Rva006EB4B0::flags ^= 1;
      }
      return true;
    }
    case 7:
      indent = ((BfmeAptValue006DCD20 *)value)->toInteger();
      return true;
    case 8: {
      EAStringC text;
      value->toString(text);
      if (((Rva008A4570Owner *)&text)->nameEquals("true"))
        Rva006EB4B0::flags |= 0x100010;
      if (((Rva008A4570Owner *)&text)->nameEquals("false")) {
        Rva006EB4B0::flags |= 0x100000;
        if (Rva006EB4B0::flags & 0x10)
          Rva006EB4B0::flags ^= 0x10;
      }
      return true;
    }
    case 10:
      left = ((BfmeAptValue006DCD20 *)value)->toInteger();
      return true;
    case 11:
      right = ((BfmeAptValue006DCD20 *)value)->toInteger();
      return true;
    case 15: {
      EAStringC text;
      value->toString(text);
      if (((Rva008A4570Owner *)&text)->nameEquals("true"))
        Rva006EB4B0::flags |= 0x1000100;
      if (((Rva008A4570Owner *)&text)->nameEquals("false")) {
        Rva006EB4B0::flags |= 0x1000000;
        if (Rva006EB4B0::flags & 0x100)
          Rva006EB4B0::flags ^= 0x100;
      }
      return true;
    }
    case 14:
      size = ((BfmeAptValue006DCD20 *)value)->rva006DD460();
      return true;
    case 2:
    case 4:
    case 9:
    case 12:
    case 13:
    case 16:
      return true;
    }
  }
  if (name->rva006D3510("blockIndent") || name->rva006D3510("bullet") ||
      name->rva006D3510("leading") || name->rva006D3510("tabStops") ||
      name->rva006D3510("target") || name->rva006D3510("url")) {
    Rva006CC110Log(3, "AptDate: Incorrect case for '%s'.\n",
                   name->rva00620090());
    g_bfmeAptAssertAtE17734(
        "0",
        "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptTextFormat.cpp",
        393);
    if (g_bfmeAptBreakOnAssertAtDDC01C)
      __debugbreak();
  }
  return false;
}

// cl: /O2 /arch:SSE /G6 /DNDEBUG /MD /EHsc
// AptTextFormat.cpp: the retail assertions inside the property getter and
// setter below name this file (bfme2patch103
// Code/Libraries/Source/Apt/AptTextFormat.cpp, lines 196 and 393);
// WorldBuilder 0x1760610 carries the same lead.
//
// Native 00710580..0071080C (652 bytes, RET 8) is slot 7 of the same
// vtable: the property getter. It uses the same gperf lookup, dispatches
// through a 15-entry jump table (plus a 4-entry alignment table) and returns
// a fresh AptString, AptInteger, AptBoolean or float value, or
// gpUndefinedValue when the state holds no explicit setting (-1 / unset
// flag bit). Each alignment case assigns its own pool string and breaks;
// writing the pool lookup once through a shared pointer schedules the
// operator= receiver after its argument push instead of before it.
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
#include "AptNativeHash.h"
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
#include "EAStringC.h"
class Rva006EB4B0 {
public:
  EAStringC font;
  union {
    float size;
    unsigned int sizeBits;
  };
  int color, align;
  unsigned flags;
  int indent, left, right;
};
class Rva006ECFC0Owner : public Rva006D6470Owner, public Rva006EB4B0 {
public:
  Rva006ECFC0Owner(const Rva006EB4B0 &);
  virtual ~Rva006ECFC0Owner();
  AptValue *rva00710580(AptValue *, const EAStringC *) const;
  bool rva00710810(AptValue *, const EAStringC *, AptValue *);
};

#include "AptValue.h"
class AptString {
  unsigned char unknown00[8];

public:
  EAStringC string;
  static AptString *Create();
};
#include "../../../GameEngine/Include/Common/AptInteger.h"
#include "AptBoolean.h"
AptValue *Rva008A4EA0MakeFloat(float);
EAStringC *Rva0070B4F0GetString(int);
extern AptValue *gpUndefinedValue;
#include "../../../GameEngine/Include/Common/Rva008A4570Owner.h"
#include "../../../GameEngine/Include/Common/R4Word.h"
const R4Word *Rva008D4F80(const char *, unsigned int);
void Rva006CC110Log(int, const char *, ...);
extern void(__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

AptValue *Rva006ECFC0Owner::rva00710580(AptValue *context,
                                        const EAStringC *name) const {
  const R4Word *word =
      context ? Rva008D4F80(name->rva00620090(), name->rva006D3750()) : 0;
  if (word) {
    switch (word->value) {
    case 1: {
      AptString *value = AptString::Create();
      switch (align) {
      case 0:
        value->string = *Rva0070B4F0GetString(0x56);
        break;
      case 1:
        value->string = *Rva0070B4F0GetString(0x7e);
        break;
      case 2:
        value->string = *Rva0070B4F0GetString(0x29);
        break;
      case 3:
        return gpUndefinedValue;
      default:
        return gpUndefinedValue;
      }
      return (AptValue *)value;
    }
    case 3: {
      if (!(Rva006EB4B0::flags & 0x10000))
        return gpUndefinedValue;
      bool value = false;
      if (Rva006EB4B0::flags & 1)
        value = true;
      return AptBoolean::Create(value);
    }
    case 5:
      if (color == -1)
        return gpUndefinedValue;
      return AptInteger::Create(color & 0xffffff);
    case 6: {
      if (font.IsEmpty())
        return gpUndefinedValue;
      AptString *value = AptString::Create();
      ((AptValue *)value)->SetString(font.rva00620090());
      return (AptValue *)value;
    }
    case 7:
      if (indent == -1)
        return gpUndefinedValue;
      return AptInteger::Create(indent);
    case 8: {
      if (!(Rva006EB4B0::flags & 0x100000))
        return gpUndefinedValue;
      bool value = false;
      if (Rva006EB4B0::flags & 0x10)
        value = true;
      return AptBoolean::Create(value);
    }
    case 10:
      if (left == -1)
        return gpUndefinedValue;
      return AptInteger::Create(left);
    case 11:
      if (right == -1)
        return gpUndefinedValue;
      return AptInteger::Create(right);
    case 14:
      if (sizeBits == 0xbf800000u)
        return gpUndefinedValue;
      return Rva008A4EA0MakeFloat(size);
    case 15: {
      if (!(Rva006EB4B0::flags & 0x1000000))
        return gpUndefinedValue;
      bool value = false;
      if (Rva006EB4B0::flags & 0x100)
        value = true;
      return AptBoolean::Create(value);
    }
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
        196);
    if (g_bfmeAptBreakOnAssertAtDDC01C)
      __debugbreak();
  }
  return 0;
}

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

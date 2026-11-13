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
#include "../../../Libraries/Source/Apt/Rva006D2A60.h"
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class AptValue
{
public:
    virtual void AddRef();
    virtual void Release();
};
// Retail vtable 0x008EA228 starts with the rowed AptValue::AddRef (0x006DCAC0) and Release.
class BfmeAptValue006DCD20 : public AptValue
{
  unsigned int flags;

public:
  BfmeAptValue006DCD20(int);
  virtual ~BfmeAptValue006DCD20();
};
class AptValue;
#include "../../../Libraries/Source/Apt/AptNativeHash.h"
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
#include "../../../Libraries/Source/Apt/EAStringC.h"
#include "../../../Libraries/Source/Apt/Rva006EB4B0.h"
class Rva006ECFC0Owner : public Rva006D6470Owner, public Rva006EB4B0 {
public:
  Rva006ECFC0Owner(AptValue *, float, int, int, int, int, int, int, AptValue *,
                   int, int, int, int);
  Rva006ECFC0Owner(const Rva006EB4B0 &);
  virtual ~Rva006ECFC0Owner();
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

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x006D6470 -> ??1Rva006D6470Owner@@UAE@XZ

// ?rva002AF236@Player@@QAEXPAVXfer@@PAVRva001FDE3F@@@Z
// partial score=0.8959090347299469 date=2026-10-10
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?rva002AF236@Player@@QAEXPAVXfer@@PAVRva001FDE3F@@@Z
// partial score=0.9 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// Native 2AF236..2AF33B,261B RET8; WB C22860 is an unnamed Player helper.
// stlport
// Caller Player::DoXfer passes the name/float tables at +294 and +2A8.
// Table count+10, node name+4/value+8 and two-word iterator are native evidence.
// Keep existing helper identities; complete table/Player layouts are unproven.
// The established pointer-map specialization is an ABI view of the native
// four-byte mapped slot; no pointer value is read or object constructed here.
// Only its already-owned begin/increment providers are called. The actual
// mapped value is accessed as the float proven by the native MOVSS operations.
#include "ascii_string.h"
#include <hash_map>
namespace rts {
 template<class T> struct hash;
 template<> struct hash<AsciiString> { unsigned int operator()(AsciiString) const; };
}
class Rva00409FFA;
typedef _STL::hash_map<AsciiString, Rva00409FFA *, rts::hash<AsciiString>,
 _STL::equal_to<AsciiString> > ExistingNameMap;
typedef _STL::pair<const AsciiString, Rva00409FFA *> ExistingNamePair;
typedef _STL::hashtable<ExistingNamePair, AsciiString, rts::hash<AsciiString>,
 _STL::_Select1st<ExistingNamePair>, _STL::equal_to<AsciiString>,
 _STL::allocator<ExistingNamePair> > ExistingNameTable;
namespace _STL {
 template<> ExistingNameTable::iterator ExistingNameTable::begin();
 template<> ExistingNameTable::iterator &ExistingNameTable::iterator::operator++();
}
class Xfer;
class NameMapXferView {
public:
 virtual void s0(); virtual void s1(); virtual bool saving();
 virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
 virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
 virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
 virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
 virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
 virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
 virtual void ascii(AsciiString *); virtual void real(float *); virtual void s29();
 virtual void word(unsigned int *);
};
class Rva001FDE3F { public: float &rva001FDE3F(const AsciiString &); };
struct NameFloatTablePrefix { char pad[0x10]; unsigned int count; };
class Player { public: void rva002AF236(Xfer *, Rva001FDE3F *); };

void Player::rva002AF236(Xfer *raw, Rva001FDE3F *table)
{
 (this?_ReadWriteBarrier():_ReadWriteBarrier());
 NameMapXferView *xfer = reinterpret_cast<NameMapXferView *>(raw);
 if (xfer->saving()) {
  unsigned int count = reinterpret_cast<NameFloatTablePrefix *>(table)->count;
  xfer->word(&count);
  ExistingNameTable *view = reinterpret_cast<ExistingNameTable *>(table);
  ExistingNameTable::iterator it;
  it = view->begin();
  for (; it != view->end(); ++it) {
   AsciiString name(it->first);
   float value = *reinterpret_cast<const float *>(&it->second);
   xfer->ascii(&name);
   xfer->real(&value);
  }
 } else {
  unsigned int count = 0;
  xfer->word(&count);
  AsciiString name;
  for (unsigned int i = 0; i < count; ++i) {
   float value;
   xfer->ascii(&name);
   xfer->real(&value);
   table->rva001FDE3F(name) = value;
  }
 }
}
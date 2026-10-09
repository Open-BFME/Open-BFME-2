// cl: /O1 /G7 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/bfme2_ascii
// stlport
// Native2B0A05..2B0B32,301B RET4; WB C235A0 unnamed record transfer.
// Player::DoXfer serializes 36-byte elements through this exact boundary.
// Native fields: AsciiString0, unsigned4, float-vector8, name-vector14,
// trailing float20. Receiver/method identity remains address-derived.
#include <vector>
#include "ascii_string.h"
class Xfer;
struct RecordVersion { RecordVersion() : value(1), limit(1) {} unsigned char value, limit; };
class RecordXferView {
public:
 virtual void s0(); virtual bool loading(); virtual void s2();
 virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
 virtual void s7(); virtual void s8(); virtual void s9();
 virtual void version(RecordVersion *);
 virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
 virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
 virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
 virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26();
 virtual void ascii(AsciiString *); virtual void real(float *); virtual void s29();
 virtual void word(unsigned int *);
};
class ModuleData;
namespace _STL {
 template<> void vector<const ModuleData *>::push_back(const ModuleData * const &);
 template<> void vector<AsciiString>::push_back(const AsciiString &);
}
class Rva002B0A05 {
public:
 void rva002B0A05(Xfer *);
 AsciiString name;
 unsigned int value;
 _STL::vector<float> values;
 _STL::vector<AsciiString> names;
 float finalValue;
};
void Rva002B0A05::rva002B0A05(Xfer *raw)
{
 RecordXferView *xfer = reinterpret_cast<RecordXferView *>(raw);
 RecordVersion version;
 xfer->version(&version);
 xfer->ascii(&name);
 xfer->word(&value);
 unsigned int i;
 unsigned int count = values.size();
 xfer->word(&count);
 for (i = 0; i < count; ++i) {
  if (xfer->loading()) {
   float v;
   xfer->real(&v);
   // Existing 49-byte word-vector provider copies the native four-byte slot.
   // No ModuleData pointer is read; both views use the same three pointers.
   reinterpret_cast<_STL::vector<const ModuleData *> *>(&values)->push_back(
    *reinterpret_cast<const ModuleData *const *>(&v));
  } else xfer->real(&values[i]);
 }
 count = names.size();
 xfer->word(&count);
 for (i = 0; i < count; ++i) {
  if (xfer->loading()) {
   AsciiString s;
   xfer->ascii(&s);
   names.push_back(s);
  } else xfer->ascii(&names[i]);
 }
 xfer->real(&finalValue);
}

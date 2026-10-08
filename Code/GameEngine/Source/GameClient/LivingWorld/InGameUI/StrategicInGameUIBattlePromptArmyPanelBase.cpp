// cl: /O1 /G7 /arch:SSE /MD /EHs /EHc- /D_CRTIMP= /Ireference/shims/bfme2_ascii
// WB ArmyPanelBase.cpp:122 identifies this predicate constructor; retail
// 0x005FEF11 supplies the 84-byte boundary and ABI. Original predicate names
// remain unknown. The +0x78 army summary visits this through vtable slot 0;
// retail vtable 0x00C7A460 names the existing 24-byte callback 0x005FED99.
// Constructor clears eight counters and calls 0x005FEE8C with the same
// stack argument and ECX receiver; that helper is still unrowed.
#include "ascii_string.h"
struct Rva005FED99Arg { char pad04[4]; AsciiString key; char pad90[0x90-8]; int count; };
class Rva005FED61 { public: void rva005FED61(const AsciiString*,int); };
class Rva0040CFC7Pred { public: virtual // ?check@Rva005FEF11@@UAE_NPBURva005FED99Arg@@@Z present-unmatched
 bool check(const Rva005FED99Arg*)=0; // ?Rva0040CFC7Pred::~Rva0040CFC7Pred present-unmatched
 ~Rva0040CFC7Pred() {} };
class Rva0040CFC7 { public: void rva0040CFC7(Rva0040CFC7Pred*); };
struct Rva005FEF11Arg { char pad78[0x78]; Rva0040CFC7 *summary; };
class Rva005FEF11 : public Rva0040CFC7Pred {
public:
 Rva005FEF11(Rva005FEF11Arg*);
 bool check(const Rva005FED99Arg*arg) { ((Rva005FED61*)this)->rva005FED61(&arg->key,arg->count); return true; }
 void rva005FEE8C(Rva005FEF11Arg*);
 int counts[8];
};
// ?Rva005FEF11::Rva005FEF11 present-unmatched
Rva005FEF11::Rva005FEF11(Rva005FEF11Arg*arg) {
 Rva0040CFC7 *summary=arg->summary;
 for(int *p=counts; p!=counts+8; ++p) *p=0;
 summary->rva0040CFC7(this);
 rva005FEE8C(arg);
}

// cl: /O1 /G7 /MD /EHsc /arch:SSE /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// Native 0x005E29CD..0x005E2A40 and the rowed scalar deleting destructor
// 0x005E2AF2/vtable C77B2C prove this complete virtual destructor entry.
// An earlier refusal describes a different boundary; this entry starts with
// the EH prologue and finishes with RET0. Target reads establish a listener
// at +10, three-pointer vector at +14, reset field +20 and counted ref +28.
// The listener comparison uses a snapshot of the counted ref across slot3;
// a matching listener is cleared through slot1. Ordinary member/base
// destruction reproduces all three native EH states and their transitions.
// Address names retain the existing deleting-destructor contract. The vector
// record and base names are ABI views of existing providers, not recovered
// application identities or a claim about the true vector element type.
#include <vector>
struct Rva005E2857Record { char bytes[1]; };
namespace _STL { template<> vector<Rva005E2857Record>::~vector(); }
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
class Rva005CB265 { public: virtual int rva005CB265(); };
class Rva005CB260 { public: void rva005CB260(); };
class Rva005F1749 { public: virtual ~Rva005F1749(); };
struct RegionIconRef { TargetRef00217D4C *pointer; ~RegionIconRef() { if(pointer) ReleaseTreeHintRef00217D4C(pointer); } };
class Rva005E29CD : public Rva005F1749 {
public: virtual ~Rva005E29CD();
private:
 char unknown04[0x10-4]; Rva005CB265 *observer;
 _STL::vector<Rva005E2857Record> items;
 int index; int unknown24; RegionIconRef ref;
};
Rva005E29CD::~Rva005E29CD() {
 TargetRef00217D4C *reference = ref.pointer;
 if(reference && observer->Rva005CB265::rva005CB265() == (int)reference)
   ((Rva005CB260 *)observer)->rva005CB260();
 index = -1;
}

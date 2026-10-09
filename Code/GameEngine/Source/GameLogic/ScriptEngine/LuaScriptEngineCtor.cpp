// cl: /O1 /MD /EHs /EHc- /arch:SSE /D_CRTIMP= /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Target3379FD..337AA2: canonical 17-slot subsystem view; 17x8 record array
// calls the owned16B Rva002E2680 constructor. Four12B vector headers are
// established by both ctor and reset337C8C; original element names remain
// uncertain. B0/BC/C8 use current owned erase-provider element footprints.
// Complete E0-byte view; the native array stride independently fixes the
// three alignment bytes absent from the S1 constructor's smaller view.
#include "ascii_string.h"
typedef bool Bool;
#include "subsystem_interface.h"
class Rva002E2680 { public: Rva002E2680(); char prefix[4]; bool value; char alignment5[3]; };
class Rva003371B1 { char data[20]; public: ~Rva003371B1(); };
struct BfmeOpaqueRecord156 { char data[156]; };
struct BfmeStringRecord00063BE4 { unsigned words[7]; AsciiString text; unsigned char tail0,tail1; BfmeStringRecord00063BE4(); BfmeStringRecord00063BE4(const BfmeStringRecord00063BE4 &); };
// Use the existing home-unit destructor instead of emitting a second copy.
namespace _STL { template<> vector<BfmeStringRecord00063BE4>::~vector(); }
class Rva00337AA8 : public SubsystemInterface {
public:
 Rva00337AA8(); virtual ~Rva00337AA8();
 virtual void init(); virtual void reset(); virtual void update() {}
 virtual void slot14() {} virtual const char *slot15(); virtual void rva00306A9B(Xfer *);
private:
 void *lua0C,*lua10;
 Rva002E2680 callbacks[17]; void *drawable9C;
 _STL::vector<unsigned> vecA0; bool flagAC;
 _STL::vector<Rva003371B1> vecB0;
 _STL::vector<BfmeOpaqueRecord156> vecBC;
 _STL::vector<BfmeStringRecord00063BE4> vecC8;
 void *wordD4; bool flagD8; void *wordDC;
};
typedef char LuaSizeE0[sizeof(Rva00337AA8)==0xE0 ? 1 : -1];
Rva00337AA8::Rva00337AA8():lua0C(0),lua10(0),drawable9C(0),flagAC(false),wordD4(0),flagD8(false),wordDC(0) {}

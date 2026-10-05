// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BFME1 revision 6583b3c1 supplies the sawMatchbot purpose and value-string ABI.
// Target 0x38AD81..0x38ADC6 (69 bytes) is called by enum callback 0x38B5DB:
// it sets +0x48D and assigns the string at +0x490 then destroys the argument.
// Fields before +0x48C remain opaque. This declaration supplies only the method
// ABI; it does not claim a complete PeerThreadClass layout. Native _free and
// the unwind-state store require the established BFME STL allocator settings.
#include <string>
struct BfmePeerEnumState { unsigned char unknown[0x48c]; bool sawEnd; bool sawMatchbot; unsigned char alignment[2]; std::string name; };
class PeerThreadClass { public: void sawMatchbot(std::string bot); };
void PeerThreadClass::sawMatchbot(std::string bot) { BfmePeerEnumState *state = reinterpret_cast<BfmePeerEnumState *>(this); state->sawMatchbot = true; state->name = bot; }
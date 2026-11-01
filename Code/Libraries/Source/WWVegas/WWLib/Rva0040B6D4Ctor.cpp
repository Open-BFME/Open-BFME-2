// cl: /Ob2 /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /ICode/Libraries/Source/debug
// stlport
// ??0Rva0040B6D4@@QAE@XZ @ 0x0040B6D4 (51B). Default ctor with two BfmeE16 vectors plus four ints.
// Evidence: retail zeroes +0 +10 +14 +18 then constructs rowed _Vector_base E16 0x00211E58 at +4 and +1C; caller 0x0040C137 in 0x0040C125; neighbours share E16 vector and ascii shims.
#include <vector>
#include "ascii_string.h"

#include "../../../Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::~_Vector_base(); }
namespace _STL { template <> vector<BfmeE16,_STL::allocator<BfmeE16> >::~vector(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

enum NameKeyType { NAMEKEY_INVALID=0 };

class AwardTrigger {
public:__declspec(noinline) AwardTrigger();
public:_STL::vector<NameKeyType> keys;unsigned threshold;
};

class Rva0040B77E {
public:
 __forceinline Rva0040B77E() : name(NAMEKEY_INVALID) {}
 ~Rva0040B77E();
 NameKeyType name;
 _STL::vector<NameKeyType> upgradeAwards;
 AsciiString nameTag,descriptionTag,imageName;
 _STL::vector<AwardTrigger> triggers;
};

class Rva0040B6D4 : public Rva0040B77E {public:Rva0040B6D4();};

Rva0040B6D4::Rva0040B6D4()
{
}

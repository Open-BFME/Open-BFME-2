// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>
// STLport 4.5.3 range destruction, native 0x00214B09..0x00214B22.
// Each 20-byte element calls the matched destructor 0x00214ADC, which
// destroys vector<AsciiString> at +8. This is not the two-string record
// whose copy constructor is at 0x002CF4C6; masking the call hid that mismatch.
class Rva00214ADC { char bytes[20]; public: ~Rva00214ADC(); };
namespace _STL {
template void __destroy_aux<Rva00214ADC *>(Rva00214ADC *, Rva00214ADC *, const __false_type &);
}

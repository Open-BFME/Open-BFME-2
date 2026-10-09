// cl: /O1 /Oy- /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3, pristine find<bool> and its random-access helper.
// Native2D3978..2D3993 passes a begin/end range and value reference, as
// independently witnessed in WB F4A4F0 and Palantir::Impl::UpdatePlayerStats.
// Its89-byte callee at2D3489 equals the existing byte-search owner, including
// every relocation (none). This is a genuine primitive algorithm fold.
// The replaced stable_sort instantiation used a count in argument2 and a
// fill helper pin at the search address; equal wrapper bytes did not establish
// its semantics. No optimization pragmas or new pins are needed here.
#include <algorithm>
template bool *_STL::find(bool *,bool *,const bool &);

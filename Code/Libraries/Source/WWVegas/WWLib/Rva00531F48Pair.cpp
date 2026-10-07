// Retail establishes a two-field 16-bit pair through the exact constructor and copy bodies.
// Field meaning and signedness are not proven; keep both names address-derived.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <utility>

struct Rva00531F48First { short value; };
struct Rva00531F48Second { short value; };

template struct _STL::pair<const Rva00531F48First, Rva00531F48Second>;

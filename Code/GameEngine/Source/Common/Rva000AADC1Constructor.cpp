// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native AA83B..AA867: 44B constructor, RET0; WB container allocation40.
// Existing Rva000AADC1 destructor and BC942C vtable establish this neutral owner.
// Target fixes vptr0, pointer-storage header4..F and24 zero bytes10..27.
// Model the STL storage base directly: native calls its29B initializer rather
// than the empty15B vector forwarding wrapper. The donor575 GeometryParser
// supplies the six-float matrix view and owning-pointer semantics; target element tag
// and matrix meanings remain unasserted. This constructor performs identical
// empty-header initialization and zeroing without guessing another element size.
#include <vector>
#include <string.h>
class Rva000AADC1Entry {public:virtual ~Rva000AADC1Entry();};
class Rva000AADC1 {public:Rva000AADC1()throw();virtual ~Rva000AADC1();
_STL::_Vector_base<Rva000AADC1Entry*,_STL::allocator<Rva000AADC1Entry*> > entries;float matrix[6];};
Rva000AADC1::Rva000AADC1()throw():entries(_STL::allocator<Rva000AADC1Entry*>())
{ memset(matrix,0,24); }

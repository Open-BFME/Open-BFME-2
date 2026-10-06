// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 vector copy at 0x2CFAB9. Retail allocates a four-byte-element
// range, then uses the established __copy_trivial helper at 0x179B0.
// unsigned int represents the observed scalar width; application enum/signed
// identity is not established. This operation preserves raw scalar values.
// The state-free allocator getter is a complete seven-byte alias at 21983A.
// The called base at 4F62A4 is the established ScienceType vector base: three
// pointer fields, count*4 allocation, initial begin==end and capacity=begin+n.
// Its retail allocator includes the allocation-hint argument. The base pin
// follows that independently decoded ABI/behavior, not a masked-call guess.
#include <vector>
template _STL::vector<unsigned int>::vector(const _STL::vector<unsigned int>&);

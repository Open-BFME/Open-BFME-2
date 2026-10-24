// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// 0x000B6569 is the 29-byte __copy_ptrs forwarder (__false_type tag) into
// __copy: retail's REL32 lands on the forward 12-byte copy loop at
// 0x000CA157 (three movsd per element), and the vector erases at 0x002A7644
// and 0x002A75DA reach it as __copy_ptrs. Retail folds every 12-byte element's
// instantiation onto it; BfmePod12 is the erase-family's code-generation view
// of one such element (implicit member-wise assignment), not a recovered type.
#include <vector>

struct BfmePod12 { int m_00; int m_04; int m_08; };

template BfmePod12 * _STL::__copy_ptrs<BfmePod12 *, BfmePod12 *>(BfmePod12 *, BfmePod12 *, BfmePod12 *, _STL::__false_type const &);

// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 copy / copy_backward wrappers over non-trivially assignable
// element types: the 27-byte copy[_backward] forwards to the 29-byte
// __copy[_backward]_ptrs(..., __false_type) which calls the element-wise
// __copy[_backward] loop with a null distance (same pair as the rowed
// copy_backward 0x004F76A1 / __copy_backward_ptrs 0x004F70A5 in
// stlport_rva004f6352_sort.cpp). Element types are size-only views named
// after the ledger spelling of the loop each pair reaches:
//
//   wrapper     _ptrs        loop         element
//   0x002B5944  0x002B4623   0x002B3049   Rva002B3049Record (copy_backward)
//   0x0032E8F9  0x0032E51B   0x0032DD81   SidesInfo         (copy)
//   0x001EBACF  0x001EBA13   0x001EB86E   BfmeAssignRecord172 (copy)
#include <algorithm>

struct Rva002B3049Record {
	int m_value;
	Rva002B3049Record &operator=(const Rva002B3049Record &);
};

struct BfmeAssignRecord172 {
	char m_opaque[0xAC];
	BfmeAssignRecord172 &operator=(const BfmeAssignRecord172 &);
};

class SidesInfo {
public:
	SidesInfo &operator=(const SidesInfo &);
private:
	char m_opaque[0x60];
};

template Rva002B3049Record *_STL::copy_backward<Rva002B3049Record *, Rva002B3049Record *>(Rva002B3049Record *, Rva002B3049Record *, Rva002B3049Record *);
template SidesInfo *_STL::copy<SidesInfo *, SidesInfo *>(SidesInfo *, SidesInfo *, SidesInfo *);
template BfmeAssignRecord172 *_STL::copy<BfmeAssignRecord172 *, BfmeAssignRecord172 *>(BfmeAssignRecord172 *, BfmeAssignRecord172 *, BfmeAssignRecord172 *);

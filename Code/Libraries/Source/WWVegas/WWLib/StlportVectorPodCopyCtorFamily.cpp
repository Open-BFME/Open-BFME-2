// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::vector(const vector &) for trivially copyable
// element views: the 68/71-byte body without an EH frame (out-of-line
// get_allocator, _Vector_base(n, alloc), then __uninitialized_copy with the
// [ebp+0Bh] tag temp), the shape of the rowed vector<BfmeE8> copy in
// stlport_vector_e8_allocate_copy.cpp, whose flags these are.  A trivial
// element makes the copy loop nothrow, which is what drops the EH frame the
// StlportVectorCopyCtorFamily.cpp members carry.  Stride comes from each
// body's own sar/idiv and _Vector_base; element names reuse the spelling the
// ledger gives the same vector's other helpers.  Callees spelled differently
// in the ledger are pinned at the addresses the retail REL32s prove.
//
//   ctor        stride  _Vector_base  __uninitialized_copy  element
//   0x0015350A   0x08   0x000B6378    0x00153425            Rva00153A27Element (push_back 0x00153A27 / overflow 0x001538C9 type)
//   0x0040D868   0x08   0x000B6378    0x004F6AD3            Rva0040CB11Entry (rowed _Construct / uninitialized_copy type)
//   0x0054147B   0x14   0x004FF36C    0x005411EE            Rva0054103E (rowed _Vector_base / uninitialized_copy type)
#include <vector>

struct Rva00153A27Element
{
	unsigned int m_data[2];
};

class Rva0040CB11Entry
{
public:
	unsigned int m_data[2];
};

class Rva0054103E
{
public:
	unsigned int m_data[5];
};

template _STL::vector<Rva00153A27Element>::vector(const _STL::vector<Rva00153A27Element> &);
template _STL::vector<Rva0040CB11Entry>::vector(const _STL::vector<Rva0040CB11Entry> &);
template _STL::vector<Rva0054103E>::vector(const _STL::vector<Rva0054103E> &);

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::vector(const vector &) for element types whose
// 96-byte copy constructor sits unclaimed in retail.  Same recipe as the
// rowed Rva00500DA0VectorCopy.cpp / vector<PrereqUnitRec> copy at 0x002CFE45:
// a non-trivial element (user-declared dtor) selects the EH-guarded path with
// out-of-line get_allocator, _Vector_base(n, alloc) and __uninitialized_copy.
// Element size is read from each body's own idiv; element names reuse the
// spelling the ledger already gives the same vector's helpers (push_back,
// _Construct or __uninitialized_copy rows); no layout beyond size is claimed.
// Callees spelled differently in the ledger are pinned at the addresses the
// retail REL32s prove.
//
//   ctor        stride  _Vector_base  __uninitialized_copy  element
//   0x002B9247   0x14   0x004FF36C    0x002B8385            Rva002B72C9 (_Construct 0x002B8226 inside the copy)
//   0x0032BF6B   0x0C   0x005C8C37    0x0032B5C5            vector<BfmeE8> (rowed uninitialized_copy type)
//   0x004244EE   0x0C   0x005C8C37    0x00423ED1            Rva00423A4A (rowed uninitialized_copy type)
//   0x0052CBC5   0x0C   0x005C8C37    0x0052C93B            Rva0052BDE6 (_Construct 0x0052C34D inside the copy)
//   0x0052CC64   0x14   0x004FF36C    0x0052C961            Rva0052BE33 (_Construct 0x0052C392 inside the copy)
//   0x0052CE7D   0x0C   0x005C8C37    0x0052C9D3            Rva0052BEF0 (_Construct 0x0052C431 inside the copy)
//   0x0052D417   0x0C   0x005C8C37    0x0052D3F1            Rva005668E9Element (rowed uninitialized_copy type)
#include <vector>

struct Rva002B72C9
{
	unsigned int m_data[5];
	~Rva002B72C9() {}
};

struct BfmeE8
{
	unsigned int m_data[2];
	~BfmeE8() {}
};

struct Rva00423A4A
{
	unsigned int m_data[3];
	~Rva00423A4A() {}
};

class Rva0052BDE6
{
public:
	unsigned int m_data[3];
	~Rva0052BDE6() {}
};

class Rva0052BE33
{
public:
	unsigned int m_data[5];
	~Rva0052BE33() {}
};

class Rva0052BEF0
{
public:
	unsigned int m_data[3];
	~Rva0052BEF0() {}
};

struct Rva005668E9Element
{
	unsigned int m_data[3];
	~Rva005668E9Element() {}
};

template _STL::vector<Rva002B72C9>::vector(const _STL::vector<Rva002B72C9> &);
template _STL::vector<_STL::vector<BfmeE8> >::vector(const _STL::vector<_STL::vector<BfmeE8> > &);
template _STL::vector<Rva00423A4A>::vector(const _STL::vector<Rva00423A4A> &);
template _STL::vector<Rva0052BDE6>::vector(const _STL::vector<Rva0052BDE6> &);
template _STL::vector<Rva0052BE33>::vector(const _STL::vector<Rva0052BE33> &);
template _STL::vector<Rva0052BEF0>::vector(const _STL::vector<Rva0052BEF0> &);
template _STL::vector<Rva005668E9Element>::vector(const _STL::vector<Rva005668E9Element> &);

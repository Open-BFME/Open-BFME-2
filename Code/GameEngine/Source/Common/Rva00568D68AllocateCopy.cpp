// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// vector<Rva00568A20>::_M_allocate_and_copy, retail 0x00568D68, 45 bytes.
// Allocates n slots through the end-of-storage proxy (12-byte allocator
// pinned for Rva00568A20 at 0x00395928 as ICF twin of rowed BfmeE12 allocate)
// and copies the range with the rowed __uninitialized_copy at 0x00568C95.
// Spelled after the STLport _Vector_base shape: _M_start at +0 _M_finish
// at +4 the allocating proxy at +8. Callers at 0x00569E57 become ready
// with idiv 0xC stride.

class Rva00568A20
{
	char _m[0xC];

public:
	Rva00568A20(const Rva00568A20 &that);
};

// 12-byte stand-in whose allocator row (0x00395928) retail reuses for every
// 12-byte vector element; same size as Rva00568A20 so the call folds.
struct BfmeE12
{
	int a[3];
};

namespace _STL
{

struct __false_type
{
	__false_type()
	{
	}
};

template <class Type>
class allocator
{
public:
	Type *allocate(unsigned int n, const void *hint) const;
};

struct RvaAllocProxy
{
	allocator<Rva00568A20> m_alloc;
	Rva00568A20 *m_data;
};

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *pointer;
	typedef unsigned int size_type;

protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first,
		ForwardIter last);

private:
	pointer m_start;
	pointer m_finish;
	RvaAllocProxy m_endOfStorage;
};

template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last,
	OutputIter result, const __false_type &tag);

}

template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n,
	ForwardIter first, ForwardIter last)
{
	Type *result = (Type *)reinterpret_cast<const allocator< ::BfmeE12> &>(m_endOfStorage.m_alloc).allocate(n, 0);
	__uninitialized_copy(first, last, result, __false_type());
	return result;
}

template Rva00568A20 *_STL::vector<Rva00568A20, _STL::allocator<Rva00568A20> >::_M_allocate_and_copy<const Rva00568A20 *>(unsigned int, const Rva00568A20 *, const Rva00568A20 *);

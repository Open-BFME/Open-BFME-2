// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// vector<Rva004F6352>::_M_allocate_and_copy, retail 0x004F6C05, 45 bytes.
// Allocates n slots through the end-of-storage proxy (12-byte allocator
// pinned for Rva004F6352 at 0x00395928 as ICF twin of rowed BfmeE12 allocate)
// and copies the range with the rowed __uninitialized_copy at 0x004F6B1E.
// Spelled after the STLport _Vector_base shape: _M_start at +0 _M_finish
// at +4 the allocating proxy at +8. Caller at 0x004F8BDC in FUN_008f8ba2
// with idiv 0xC stride.

struct Rva004F6352
{
	char _m[0xC];

public:
	Rva004F6352(const Rva004F6352 &that);
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
	allocator<Rva004F6352> m_alloc;
	Rva004F6352 *m_data;
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
	Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
	__uninitialized_copy(first, last, result, __false_type());
	return result;
}

template Rva004F6352 *_STL::vector<Rva004F6352, _STL::allocator<Rva004F6352> >::_M_allocate_and_copy<Rva004F6352 *>(unsigned int, Rva004F6352 *, Rva004F6352 *);

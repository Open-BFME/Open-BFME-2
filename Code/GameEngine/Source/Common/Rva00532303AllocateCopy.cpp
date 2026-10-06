// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// vector<Rva005334A4Element>::_M_allocate_and_copy, retail 0x00532303, 45 bytes.
// 4-byte non-trivial view used by push_back 0x005334A4. Allocates via the
// folded allocator at 0x00068E15 and copies with __uninitialized_copy at
// 0x005322B8 (primary matched under unsigned-short alias name). Prior
// vector<int> pin at this RVA was a false identity.

struct Rva005334A4Element
{
	char m_pad[4];

public:
	Rva005334A4Element(const Rva005334A4Element &that);
	~Rva005334A4Element();
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
	allocator<Rva005334A4Element> m_alloc;
	Rva005334A4Element *m_data;
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

template Rva005334A4Element *_STL::vector<Rva005334A4Element, _STL::allocator<Rva005334A4Element> >::_M_allocate_and_copy<Rva005334A4Element *>(unsigned int, Rva005334A4Element *, Rva005334A4Element *);

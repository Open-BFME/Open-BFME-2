// cl: /O1
//
// vector<Rva001DAAF2Element>::_M_allocate_and_copy, retail 0x001D9C9F, 45 bytes.
// 8-byte non-trivial view used by push_back 0x001DAAF2. Allocates via
// 0x00523D6C and copies with __uninitialized_copy at 0x001D9B3C.

struct Rva001DAAF2Element
{
	char m_pad[8];

public:
	Rva001DAAF2Element(const Rva001DAAF2Element &that);
	~Rva001DAAF2Element();
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
	allocator<Rva001DAAF2Element> m_alloc;
	Rva001DAAF2Element *m_data;
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

template Rva001DAAF2Element *_STL::vector<Rva001DAAF2Element, _STL::allocator<Rva001DAAF2Element> >::_M_allocate_and_copy<Rva001DAAF2Element *>(unsigned int, Rva001DAAF2Element *, Rva001DAAF2Element *);

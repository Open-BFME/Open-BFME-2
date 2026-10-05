// cl: /O1
//
// vector<Rva002B9062Element>::_M_allocate_and_copy, retail 0x005E25EF, 45 bytes.
// 4-byte non-trivial view used by push_back 0x002B9062. Allocates via 0x00068E15
// and copies with __uninitialized_copy at 0x0007E2FA. Several false Record
// pins previously named this RVA.

struct Rva002B9062Element
{
	char m_pad[4];

public:
	Rva002B9062Element(const Rva002B9062Element &that);
	~Rva002B9062Element();
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
	allocator<Rva002B9062Element> m_alloc;
	Rva002B9062Element *m_data;
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

template Rva002B9062Element *_STL::vector<Rva002B9062Element, _STL::allocator<Rva002B9062Element> >::_M_allocate_and_copy<Rva002B9062Element *>(unsigned int, Rva002B9062Element *, Rva002B9062Element *);

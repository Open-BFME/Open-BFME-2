// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// vector::_M_allocate_and_copy at retail 0x0018C705, 45 bytes.
// Allocates via short allocator 0x000AD722; copies via Rva0018C3C9Copy at
// 0x0018C3C9 (tree-node to short finish walker). Opaque 2-byte element.

struct Rva0018C705Element
{
	char m_pad[2];

public:
	Rva0018C705Element(const Rva0018C705Element &that);
	~Rva0018C705Element();
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
	allocator<Rva0018C705Element> m_alloc;
	Rva0018C705Element *m_data;
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

template Rva0018C705Element *_STL::vector<Rva0018C705Element, _STL::allocator<Rva0018C705Element> >::_M_allocate_and_copy<Rva0018C705Element *>(unsigned int, Rva0018C705Element *, Rva0018C705Element *);

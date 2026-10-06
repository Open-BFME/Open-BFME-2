// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// vector<Rva0008DE1CElement>::_M_allocate_and_copy, retail 0x0008A1D0, 45 bytes.
// 24-byte non-trivial view used by push_back 0x0008DE1C. Allocates via
// 0x00395944 and copies with __uninitialized_copy at 0x0008A185.

struct Rva0008DE1CElement
{
	char m_pad[24];

public:
	Rva0008DE1CElement(const Rva0008DE1CElement &that);
	~Rva0008DE1CElement();
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
	allocator<Rva0008DE1CElement> m_alloc;
	Rva0008DE1CElement *m_data;
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

template Rva0008DE1CElement *_STL::vector<Rva0008DE1CElement, _STL::allocator<Rva0008DE1CElement> >::_M_allocate_and_copy<Rva0008DE1CElement *>(unsigned int, Rva0008DE1CElement *, Rva0008DE1CElement *);

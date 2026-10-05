// cl: /O1
//
// vector<PrereqUnitRec>::_M_allocate_and_copy, retail 0x004EE233, 45 bytes.
// 12-byte nested ProductionPrerequisite::PrereqUnitRec. Allocates via the
// folded 12-byte allocator at 0x00395928 and copies with the rowed
// __uninitialized_copy at 0x004EE1E2. Prior Rva004EE55ERecord pin at this
// RVA was a false identity.

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		char m_pad[0xC];

		PrereqUnitRec(const PrereqUnitRec &that);
		~PrereqUnitRec();
	};
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
	allocator<ProductionPrerequisite::PrereqUnitRec> m_alloc;
	ProductionPrerequisite::PrereqUnitRec *m_data;
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

typedef ProductionPrerequisite::PrereqUnitRec PrereqRec;

template PrereqRec *_STL::vector<PrereqRec, _STL::allocator<PrereqRec> >::_M_allocate_and_copy<PrereqRec *>(unsigned int, PrereqRec *, PrereqRec *);

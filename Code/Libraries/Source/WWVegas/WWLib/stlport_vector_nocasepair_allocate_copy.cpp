// cl: /Ireference/shims/bfme2_ascii
// ??$_M_allocate_and_copy@PBU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@?$vector@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@IAEPAU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@1@IPBU21@0@Z @0x00317D5C 45B: vector allocate-and-copy for 8-byte NoCase pair via allocate 0x00523D6C plus uninitialized_copy 0x00317CF2. Evidence: retail calls rowed allocate plus dup_00317CF2 worker for CopyNoCasePair; caller 0x00317EBB assign path sar 3 stride 8; same 45B ebp-tag shape as 0x0040D077 and 0x000BC72B.
#include "ascii_string.h"
struct NoCaseTreeValue4
{
	char m_body[4];
};
namespace _STL
{
template <class T1, class T2>
struct pair
{
	T1 first;
	T2 second;
	pair();
	pair(const pair &other);
};
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
}
typedef _STL::pair<const AsciiString, NoCaseTreeValue4> CopyNoCasePair;
namespace _STL
{
struct CopyPairAllocProxy
{
	allocator<CopyNoCasePair> m_alloc;
	CopyNoCasePair *m_data;
};
template <class Type, class Allocator>
class vector
{
public:
	typedef Type *pointer;
	typedef const Type *const_pointer;
	typedef unsigned int size_type;
protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
private:
	pointer m_start;
	pointer m_finish;
	CopyPairAllocProxy m_endOfStorage;
};
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}
template <class Type, class Allocator>
template <class ForwardIter>
Type *_STL::vector<Type, Allocator>::_M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last)
{
	Type *result = m_endOfStorage.m_alloc.allocate(n, 0);
	__uninitialized_copy(first, last, result, __false_type());
	return result;
}
template CopyNoCasePair *_STL::vector<CopyNoCasePair, _STL::allocator<CopyNoCasePair> >::_M_allocate_and_copy<const CopyNoCasePair *>(unsigned int, const CopyNoCasePair *, const CopyNoCasePair *);

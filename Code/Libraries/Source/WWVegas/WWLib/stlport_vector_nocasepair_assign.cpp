// cl: /Ireference/shims/bfme2_ascii
// ??4?$vector@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@QAEAAV01@ABV01@@Z @0x00317EBB 180B: vector NoCase pair assign via allocate_and_copy 0x00317D5C plus clear 0x004C3D8B plus copy 0x00255CFA plus destroy 0x0032C0CA plus uninitialized_copy 0x00317CF2. Evidence: retail calls rowed allocate_and_copy plus rowed clear plus pinned copy plus rowed destroy plus pinned uninitialized_copy; sar 3 stride 8 throughout; same 3-path shape as Science assign 0x0021C21B.
#include "ascii_string.h"
struct NoCaseTreeValue4
{
	char m_body[4];
};
struct BfmeStringRecord00426A5B
{
	AsciiString text;
	unsigned char flag0, flag1, flag2;
};
struct FXBoneInfo
{
	AsciiString m_boneName;
	const void *m_particleSystemTemplate;
};
struct RvaPair0032C0CA
{
	AsciiString m_key;
	int m_value;
};
void Rva0032C0CADestroyPairs(RvaPair0032C0CA *first, RvaPair0032C0CA *last);
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
};
typedef pair<const AsciiString, NoCaseTreeValue4> CopyNoCasePair;
template <class Type, class Allocator>
class vector
{
public:
	typedef Type *pointer;
	typedef const Type *const_pointer;
	typedef unsigned int size_type;
	vector &operator=(const vector &x);
	pointer begin() { return m_start; }
	const_pointer begin() const { return m_start; }
	pointer end() { return m_finish; }
	const_pointer end() const { return m_finish; }
	size_type size() const { return size_type(m_finish - m_start); }
	size_type capacity() const { return size_type(m_endOfStorage - m_start); }
protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};
template <>
class vector<BfmeStringRecord00426A5B, allocator<BfmeStringRecord00426A5B> >
{
	friend class vector<CopyNoCasePair, allocator<CopyNoCasePair> >;
protected:
	void _M_clear();
};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
}
_STL::vector<_STL::CopyNoCasePair, _STL::allocator<_STL::CopyNoCasePair> > &_STL::vector<_STL::CopyNoCasePair, _STL::allocator<_STL::CopyNoCasePair> >::operator=(const vector &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		if (xsize > capacity())
		{
			pointer tmp = _M_allocate_and_copy(xsize, x.begin(), x.end());
			reinterpret_cast<_STL::vector<BfmeStringRecord00426A5B, _STL::allocator<BfmeStringRecord00426A5B> > *>(this)->_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			FXBoneInfo *new_finish = _STL::__copy_ptrs(const_cast<FXBoneInfo *>(reinterpret_cast<const FXBoneInfo *>(x.begin())), const_cast<FXBoneInfo *>(reinterpret_cast<const FXBoneInfo *>(x.end())), reinterpret_cast<FXBoneInfo *>(m_start), _STL::__false_type());
			Rva0032C0CADestroyPairs(reinterpret_cast<RvaPair0032C0CA *>(new_finish), reinterpret_cast<RvaPair0032C0CA *>(m_finish));
		}
		else
		{
			_STL::__copy_ptrs(const_cast<FXBoneInfo *>(reinterpret_cast<const FXBoneInfo *>(x.begin())), const_cast<FXBoneInfo *>(reinterpret_cast<const FXBoneInfo *>(x.begin() + size())), reinterpret_cast<FXBoneInfo *>(m_start), _STL::__false_type());
			_STL::__uninitialized_copy(x.begin() + size(), x.end(), m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

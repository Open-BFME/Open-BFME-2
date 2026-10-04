// cl: /Ireference/shims/bfme2_ascii /G7 /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /EHs
// stlport
// ?_M_fill_insert@?$vector@VRva00585B16@@V?$allocator@VRva00585B16@@@_STL@@@_STL@@QAEXPAVRva00585B16@@IABV3@@Z, retail 0x00586EB9 258B.
// Vector Rva00585B16 _M_fill_insert: capacity check via idiv 0x54, temp copy via rowed copy ctor,
// uninitialized_copy 0x585CE0, copy_backward, fill, RvaFill 0x585D06, overflow 0x586C56,
// temp dtor via rowed deque dtor. Evidence: same 258B ret-0x0C shape as AsciiString fill_insert
// 0x000C0697 and StringRecord fill_inserts; callers unclaimed.
#include <vector>
#include <deque>

struct BfmeE12
{
	float x;
	float y;
	float z;
};

class Rva00585B16
{
public:
	Rva00585B16(const Rva00585B16 &other);
	~Rva00585B16() {}
private:
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	int m_10;
	int m_14;
	int m_18;
	unsigned char m_1C;
	char m_pad1D[3];
	int m_20;
	int m_24;
	_STL::deque<BfmeE12, _STL::allocator<BfmeE12> > m_28;
	int m_50;
};

Rva00585B16 *Rva00585D06Fill(Rva00585B16 *first, unsigned int n, const Rva00585B16 &x);

struct Ints12
{
	int m_00;
	int m_04;
	int m_08;
};

struct BfmeAssignRecord84
{
	int m_00;
	Ints12 m_04;
	Ints12 m_10;
	unsigned char m_1C;
	char m_pad1D[3];
	int m_20;
	int m_24;
	_STL::deque<BfmeE12, _STL::allocator<BfmeE12> > m_28;
	int m_50;
	BfmeAssignRecord84 &operator=(const BfmeAssignRecord84 &other);
};

namespace _STL
{
template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);

template <>
inline BfmeAssignRecord84 *__copy_backward_ptrs<BfmeAssignRecord84 *, BfmeAssignRecord84 *>(BfmeAssignRecord84 *__first, BfmeAssignRecord84 *__last, BfmeAssignRecord84 *__result, const __false_type &)
{
	return __copy_backward(__first, __last, __result, random_access_iterator_tag(), (int *)0);
}

template <class ForwardIter, class T>
void fill(ForwardIter first, ForwardIter last, const T &value);

template <>
inline void vector<Rva00585B16, allocator<Rva00585B16> >::_M_fill_insert(
	Rva00585B16 *__position, size_type __n, const Rva00585B16 &__x)
{
	if (__n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= __n) {
			Rva00585B16 __x_copy = __x;
			const size_type __elems_after = this->_M_finish - __position;
			pointer __old_finish = this->_M_finish;
			if (__elems_after > __n) {
				__uninitialized_copy(this->_M_finish - __n, this->_M_finish, this->_M_finish, _IsPODType());
				this->_M_finish += __n;
				__copy_backward_ptrs((BfmeAssignRecord84 *)__position, (BfmeAssignRecord84 *)(__old_finish - __n), (BfmeAssignRecord84 *)__old_finish, _TrivialAss());
				_STLP_STD::fill((BfmeAssignRecord84 *)__position, (BfmeAssignRecord84 *)(__position + __n), *(BfmeAssignRecord84 *)&__x_copy);
			}
			else {
				Rva00585D06Fill(this->_M_finish, __n - __elems_after, __x_copy);
				this->_M_finish += __n - __elems_after;
				__uninitialized_copy(__position, __old_finish, this->_M_finish, _IsPODType());
				this->_M_finish += __elems_after;
				_STLP_STD::fill((BfmeAssignRecord84 *)__position, (BfmeAssignRecord84 *)__old_finish, *(BfmeAssignRecord84 *)&__x_copy);
			}
		}
		else
			_M_insert_overflow(__position, __x, _IsPODType(), __n, false);
	}
}
}

#pragma inline_depth(0)
// ?_bfmeRva00585B16FillInsertAnchor@@YAXXZ absent-from-retail
void _bfmeRva00585B16FillInsertAnchor()
{
	typedef _STL::vector<Rva00585B16, _STL::allocator<Rva00585B16> > RvaVector;
	RvaVector *vec = 0;
	Rva00585B16 *pos = 0;
	const Rva00585B16 *val = 0;
	vec->_M_fill_insert(pos, 0, *val);
}
#pragma inline_depth()

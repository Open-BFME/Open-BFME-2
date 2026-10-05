// ?rva00585257@Rva00585257Iter@@QAEPAXXZ @0x00585257 32B
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Leaf 16-byte deque iterator copy plus _M_decrement 0x00421B47 plus return cur. Evidence: prev 0x00585240 pop_front next 0x00585283 same deque E12 family; callees rowed; callers 0x00586719 0x005867C6 unclaimed.
#define _STLP_NO_EXCEPTIONS 1
#include <deque>

struct BfmeE12
{
	float x, y, z;
};

class Rva00585257Iter : public _STL::_Deque_iterator_base<BfmeE12>
{
public:
	void *rva00585257();
};

void *Rva00585257Iter::rva00585257()
{
	_STL::_Deque_iterator_base<BfmeE12> tmp = *this;
	tmp._M_decrement();
	return tmp._M_cur;
}

// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00584E02@Rva00584E02@@QAEAAV1@XZ @0x00584E02 12B
// Pre-increment wrapper calling rowed _M_increment 0x00421B1E then returning *this.
// Evidence: push esi mov esi ecx call 0x00421B1E mov eax esi pop esi ret;
// same shape as PAX deque operator++ 0x00054B33 12B; no callers; honest address
// name since Const vs Nonconst traits unproven.
#include <deque>

struct BfmeE12
{
	float x, y, z;
};

class Rva00584E02
{
public:
	Rva00584E02 &rva00584E02(void);
};

Rva00584E02 &Rva00584E02::rva00584E02(void)
{
	((_STL::_Deque_iterator_base<BfmeE12> *)this)->_M_increment();
	return *this;
}

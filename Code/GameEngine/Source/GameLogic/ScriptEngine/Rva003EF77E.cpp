// cl: /O1 /Ob2 /GX- /Oy- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva003EF77E@@QAE@XZ, retail 0x003EF77E, 97 bytes.
// Builds the three empty vectors at +0, +0x14 and +0x20 through the rowed empty
// _Vector_base 0x00211E58, zeroes the two counters at +0x0C / +0x10 and then clears each
// vector through the pointer-element erase 0x0031BD55 (the element is a 16-byte POD whose
// erase is shared with void*), returning this. Evidence: target bytes and the rowed callees;
// the class and field names are neutral views.
#include <vector>

struct BfmeE16
{
	float x;
	float y;
	float z;
	float w;
};

// The rowed empty-base constructor stays an out-of-line call in retail.
namespace _STL {
template <> __declspec(noinline) _Vector_base<BfmeE16, allocator<BfmeE16> >::_Vector_base(const allocator<BfmeE16> &a)
	: _M_start(0), _M_finish(0), _M_end_of_storage(a, (BfmeE16 *)0)
{
}
}

class Rva003EF77E
{
public:
	Rva003EF77E();
private:
	_STL::vector<BfmeE16> m_vec0;
	int m_c;
	int m_10;
	_STL::vector<BfmeE16> m_vec14;
	_STL::vector<BfmeE16> m_vec20;
};

Rva003EF77E::Rva003EF77E()
	: m_vec0(_STL::allocator<BfmeE16>()), m_c(0), m_10(0), m_vec14(_STL::allocator<BfmeE16>()), m_vec20(_STL::allocator<BfmeE16>())
{
	_STL::vector<void *> *first = (_STL::vector<void *> *)&m_vec0;
	_STL::vector<void *> *second = (_STL::vector<void *> *)&m_vec14;
	_STL::vector<void *> *third = (_STL::vector<void *> *)&m_vec20;
	first->erase(first->begin(), first->end());
	second->erase(second->begin(), second->end());
	third->erase(third->begin(), third->end());
}

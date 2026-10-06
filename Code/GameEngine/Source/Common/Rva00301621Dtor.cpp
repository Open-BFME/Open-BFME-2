// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// ??1Rva00301621Dtor@@QAE@XZ retail 0x00301621 53B
// Two STLport list<int> members at +0 and +4 torn down in reverse order
// through the rowed ??1?$_List_base@H...@_STL@@QAE@XZ 0x004EC395. Reached
// through gap thunk 0x007B7A9B on global 0x00DFF14C. Names address-derived.

#include <list>

template <> _STL::_List_base<int, _STL::allocator<int> >::~_List_base();

class Rva00301621Dtor
{
public:
	~Rva00301621Dtor();

private:
	_STL::list<int> m_a; // +0x00
	_STL::list<int> m_b; // +0x04
};

Rva00301621Dtor::~Rva00301621Dtor()
{
}

// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?rva002B61DD@Rva002B61DD@@QAEXXZ @0x002B61DD (30B):
// Frameless Destroy+free of Rva0040DC56Element range: pushes finish/start
// and calls rowed _Destroy 0x002B61C5, reloads start, frees via rowed _free
// 0x00030830 when non-null. Same callees as the EH vector dtor 0x002B703F
// (which is 63B with __EH_prolog) and the range erase 0x0040DC56; callers
// 0x002B71DA 0x003F7A36 0x0040DCC4 are insert-overflow-like growers that
// destroy+free the old buffer after 0x0040CAD3 allocates. Honest address
// name: owner unproven, shape is thiscall void with two pointer members.
#include <stddef.h>

extern "C" void __cdecl free(void *block);

struct Rva0040DC56Element
{
	~Rva0040DC56Element();
};

namespace _STL
{
template <class _ForwardIterator>
void _Destroy(_ForwardIterator __first, _ForwardIterator __last);
}

class Rva002B61DD
{
public:
	void rva002B61DD();
private:
	Rva0040DC56Element *m_00;
	Rva0040DC56Element *m_04;
};

void Rva002B61DD::rva002B61DD()
{
	_STL::_Destroy(m_00, m_04);
	Rva0040DC56Element *start = m_00;
	if (start != 0)
		free(start);
}

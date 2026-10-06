// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00601941@Rva00601941@@QAEXXZ @0x00601941 11B
// Vector erase-all wrapper: pushes begin/end at +0/+4 and calls the rowed
// _STL::vector<void*>::erase. Evidence: callees rowed erase at 0x0031BD55;
// callers at 0x002A910B 0x00445E4B 0x005A0696 pass this+0x668 etc; no return used.

#include <vector>

class Rva00601941
{
public:
	void rva00601941();

private:
	_STL::vector<void *> m_vec;
};

void Rva00601941::rva00601941()
{
	m_vec.erase(m_vec.begin(), m_vec.end());
}

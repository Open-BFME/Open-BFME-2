// cl: /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva002401C0@Rva002401C0@@QAE?AV?$vector@IV?$allocator@I@_STL@@@_STL@@XZ @0x002401C0 (29B)
// RVO forward to the inner receiver at +0x184 calling rowed Rva0040DBA9 0x0040DBA9.
// Same thunk shape as rva00389081 (0x00389081, +0x130 receiver).
#include <vector>

class Rva0040DBA9
{
public:
	_STL::vector<unsigned int> rva0040DBA9();
};

class Rva002401C0
{
public:
	_STL::vector<unsigned int> rva002401C0();
private:
	char m_pad[0x184];
	Rva0040DBA9 m_inner;
};

_STL::vector<unsigned int> Rva002401C0::rva002401C0()
{
	return m_inner.rva0040DBA9();
}

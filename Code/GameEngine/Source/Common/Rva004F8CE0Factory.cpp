// cl: /O1
//
// ?rva004F8CE0@@YGPAXABURva004F868AElement@@@Z @0x004F8CE0 34B.
// Element factory: allocate a 0x20 block through rowed STLport
// allocator<char>::allocate 0x000307F0, then run the rowed _Construct
// 0x004F868A in place at +0x10 from the source element, and return the
// block. Both templates are declared but never defined here so the calls
// bind to the rowed copies.
struct Rva004F868AElement
{
	int a;
	Rva004F868AElement(const Rva004F868AElement &that);
};

namespace _STL
{
template<class _T1, class _T2>
void _Construct(_T1 *__p, const _T2 &__val);
template<class _T>
struct allocator
{
	static _T *allocate(unsigned int n, const void *hint);
};
}

struct Rva004F8CE0Rec
{
	char m_pad[0x10];
	Rva004F868AElement m_10;
};

void *rva004307F0(int a, int b);

void *__stdcall rva004F8CE0(const Rva004F868AElement &src)
{
	void *p = _STL::allocator<char>::allocate(0x20, 0);
	_STL::_Construct(&((Rva004F8CE0Rec *)p)->m_10, src);
	return p;
}

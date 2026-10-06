// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva003ED658@@QAE@ABV0@@Z @ 0x003ED658 53B
// Copy ctor of TU-local class with vector<unsigned> at +0 via rowed vector copy 0x002CFAB9.
// Then calls just-landed Rva003ED498Count 0x003ED498 with this; callers 0x0020D8C9/0x0020D9B9 pass this.
// Neighbour StringRecordCopyBFME2.cpp shares /O1 /EHsc STLport flags and vector idioms.
#include <vector>
void __cdecl Rva003ED498Count(void const *);
class Rva003ED658
{
public:
	Rva003ED658(Rva003ED658 const &src);
private:
	_STL::vector<unsigned> m_vec;
};
Rva003ED658::Rva003ED658(Rva003ED658 const &src) : m_vec(src.m_vec)
{
	Rva003ED498Count(this);
}

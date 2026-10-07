// ?rva0040A3D2@Rva0040A3D2@@QAEHPBD0@Z
// partial score=0.95 date=2026-10-07
// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva0040A3D2@Rva0040A3D2@@QAEHPBD0@Z @0x0040A3D2 39B: vector-like +0/+4 of
// bytes searched via rowed _STL::find_if 0x40A366 with Not_within excluded
// range; null/0 when the found end equals the stored end else the dword at
// the found position; caller 0x005B5507 unclaimed.
#include <algorithm>
#include <string>

class Rva0040A3D2
{
public:
	int rva0040A3D2(const char *a, const char *b);

private:
	const char *m_begin;
	const char *m_end;
};

int Rva0040A3D2::rva0040A3D2(const char *a, const char *b)
{
	const char *found = _STL::find_if(m_begin, m_end, _STL::_Not_within_traits<_STL::char_traits<char> >(a, b));
	return (found == m_end) ? 0 : *(const int *)found;
}

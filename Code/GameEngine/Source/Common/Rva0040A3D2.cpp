// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Os
// ?rva0040A3D2@Rva0040A3D2@@QAEHPBD0@Z @0x0040A3D2 39B
// Banked attempt reverse/attempts/0x0040a3d2.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
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

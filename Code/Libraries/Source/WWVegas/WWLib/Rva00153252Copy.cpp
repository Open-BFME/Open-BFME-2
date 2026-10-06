// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??$__copy@PAURva00153252@@PAU1@H@_STL@@YAPAURva00153252@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z, retail 0x00153320, 47 bytes.
// Forward copy of 8-byte Rva00153252 via rowed operator= 0x153252 sar 3 stride 8.
// Evidence: sub sar3 test jle loop push [ebp+8] mov ecx [ebp+0x10] call 0x153252 add 8 dec jne; same shape as 47B __copy at 0x426A82 and 0x2605EB; caller 0x1534C9.
struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
};
struct Rva00153252
{
	TreeHintRef00217D4C m_00;
	int m_04;
	Rva00153252 &operator=(const Rva00153252 &other);
};
#include <vector>
template Rva00153252 *_STL::__copy<Rva00153252 *, Rva00153252 *, int>(Rva00153252 *, Rva00153252 *, Rva00153252 *, const _STL::random_access_iterator_tag &, int *);
Rva00153252 *Rva001534B6Copy(Rva00153252 *first, Rva00153252 *last, Rva00153252 *result)
{
	const _STL::random_access_iterator_tag tag;
	return _STL::__copy(first, last, result, tag, (int *)0);
}

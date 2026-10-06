// cl: /DNDEBUG /MD
// ?Rva0052C987Get@@YAPAXPAX00@Z retail 0x0052C987 38B. Unlock lane:
// uninitialized copy over 0x14-stride elements via rowed _Construct
// ??$_Construct@VRva004E194E@@V1@@_STL@@YAXPAVRva004E194E@@ABV1@@Z at
// 0x0052C3D7 (declared-only specialization so the gate resolves to the row
// address); push-esi/edi loop with late cmp, returns final dest. Callers at
// 0x0052CDC4/0x00565E97/0x00565EE2. Landing unblocks 0x0052CD81 and
// 0x00565E56. Sibling of Rva0052C961 uninit-copy (same void-pointer loop,
// 20-byte stride). Owner unknown so honest address-derived name.
class Rva004E194E
{
public:
	Rva004E194E(const Rva004E194E &other);
};

namespace _STL
{
template <class _T1, class _T2>
void _Construct(_T1 *, const _T2 &);
template <> void _Construct<Rva004E194E, Rva004E194E>(Rva004E194E *, const Rva004E194E &);
}

void *__cdecl Rva0052C987Get(void *first, void *last, void *result)
{
	char *cur = (char *)result;
	for (; first != last; first = (char *)first + 20, cur += 20)
		_STL::_Construct((Rva004E194E *)cur, *(Rva004E194E *)first);
	return cur;
}

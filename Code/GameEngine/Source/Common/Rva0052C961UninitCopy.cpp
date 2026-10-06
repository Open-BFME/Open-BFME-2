// cl: /DNDEBUG /MD
// ?Rva0052C961Get@@YAPAXPAX00@Z retail 0x0052C961 38B. Chain lane:
// uninitialized copy over 0x14-stride elements via rowed _Construct
// ??$_Construct@VRva0052BE33@@V1@@_STL@@YAXPAVRva0052BE33@@ABV1@@Z at
// 0x0052C392 (declared-only specialization so the gate resolves to the row
// address); push-esi/edi loop with late cmp, returns final dest. Callers at
// 0x0052CCA7/0x00565D2C/0x00565D77. Landing unblocks 0x0052CC64 and
// 0x00565CEB. Sibling of Rva0052C9D3 uninit-copy (same void-pointer loop,
// 20-byte stride for Rva0052BE33). Owner unknown so honest
// address-derived name; element is size-only (20 bytes).
class Rva0052BE33
{
public:
	Rva0052BE33(const Rva0052BE33 &other);
};

namespace _STL
{
template <class _T1, class _T2>
void _Construct(_T1 *, const _T2 &);
template <> void _Construct<Rva0052BE33, Rva0052BE33>(Rva0052BE33 *, const Rva0052BE33 &);
}

void *__cdecl Rva0052C961Get(void *first, void *last, void *result)
{
	char *cur = (char *)result;
	for (; first != last; first = (char *)first + 20, cur += 20)
		_STL::_Construct((Rva0052BE33 *)cur, *(Rva0052BE33 *)first);
	return cur;
}

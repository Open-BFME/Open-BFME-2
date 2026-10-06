// cl: /DNDEBUG /MD
// ?Rva0052C9D3Get@@YAPAXPAX00@Z retail 0x0052C9D3 38B. Chain lane:
// uninitialized copy over 0x0C-stride elements via rowed _Construct
// ??$_Construct@VRva0052BEF0@@V1@@_STL@@YAXPAVRva0052BEF0@@ABV1@@Z at
// 0x0052C431 (called through declared-only specialization so the gate
// resolves to the row address); push-esi/edi loop with late cmp, returns
// final dest. Callers at 0x0052CEC0/0x005660B9/0x00566104. Landing unblocks
// 0x0052CE7D and 0x00566078. Sibling of Rva0052C9AD uninit-copy (same
// void-pointer loop, 12-byte stride for Rva0052BEF0). Owner unknown so
// honest address-derived name; element is size-only (12 bytes).
class Rva0052BEF0
{
public:
	Rva0052BEF0(const Rva0052BEF0 &other);
};

namespace _STL
{
template <class _T1, class _T2>
void _Construct(_T1 *, const _T2 &);
template <> void _Construct<Rva0052BEF0, Rva0052BEF0>(Rva0052BEF0 *, const Rva0052BEF0 &);
}

void *__cdecl Rva0052C9D3Get(void *first, void *last, void *result)
{
	char *cur = (char *)result;
	for (; first != last; first = (char *)first + 12, cur += 12)
		_STL::_Construct((Rva0052BEF0 *)cur, *(Rva0052BEF0 *)first);
	return cur;
}

// cl: /DNDEBUG /MD
// ?Rva0052C93BGet@@YAPAXPAX00@Z retail 0x0052C93B 38B. Chain lane:
// uninitialized copy over 0x0C-stride elements via rowed _Construct
// ??$_Construct@VRva0052BDE6@@V1@@_STL@@YAXPAVRva0052BDE6@@ABV1@@Z at
// 0x0052C34D (declared-only specialization so the gate resolves to the row
// address); push-esi/edi loop with late cmp, returns final dest. Callers at
// 0x0052CC08/0x00565C75/0x00565CC0. Landing unblocks 0x0052CBC5 and
// 0x00565C34. Sibling of Rva0052C961 uninit-copy (same void-pointer loop,
// 12-byte stride for Rva0052BDE6). Owner unknown so honest
// address-derived name; element is size-only (12 bytes).
class Rva0052BDE6
{
public:
	Rva0052BDE6(const Rva0052BDE6 &other);
};

namespace _STL
{
template <class _T1, class _T2>
void _Construct(_T1 *, const _T2 &);
template <> void _Construct<Rva0052BDE6, Rva0052BDE6>(Rva0052BDE6 *, const Rva0052BDE6 &);
}

void *__cdecl Rva0052C93BGet(void *first, void *last, void *result)
{
	char *cur = (char *)result;
	for (; first != last; first = (char *)first + 12, cur += 12)
		_STL::_Construct((Rva0052BDE6 *)cur, *(Rva0052BDE6 *)first);
	return cur;
}

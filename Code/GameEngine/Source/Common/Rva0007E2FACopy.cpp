// cl: /MD
// ?Rva0007E2FACopy@@YAPAPAXPAPAX00ABU__false_type@_STL@@@Z @ 0x0007E2FA (38B):
// __uninitialized_copy for 4-byte owning refs; calls rowed Rva00087A5CCopy per
// element. Evidence: chain from 0x00087A5C plus 31 callers including 178B
// overflow bodies; shape matches Ascii/Unicode 38B trio members.

void __cdecl Rva00087A5CCopy(void **dst, void **src);

namespace _STL {
struct __false_type {};
}

void **__cdecl Rva0007E2FACopy(void **first, void **last, void **result, const _STL::__false_type &)
{
	void **cur = result;
	for (; first != last; ++first, ++cur)
		Rva00087A5CCopy(cur, first);
	return cur;
}

// cl: /MD
// ?Rva00577CA0Fill@@YAPAPAXPAPAXIABQAXABU__false_type@_STL@@@Z @ 0x00577CA0 (37B):
// __uninitialized_fill_n for 4-byte owning refs; calls rowed Rva00087A5CCopy per
// element. Evidence: 178B overflow caller 0x0057833B passes result/n/value/false_type
// and cleans 0x10; pair of rowed 38B copy 0x0007E2FA; shape matches 37B fill trio.

void __cdecl Rva00087A5CCopy(void **dst, void **src);

namespace _STL {
struct __false_type {};
}

void **__cdecl Rva00577CA0Fill(void **first, unsigned int n, void *const &x, const _STL::__false_type &)
{
	void **cur = first;
	for (; n > 0; --n, ++cur)
		Rva00087A5CCopy(cur, (void **)&x);
	return cur;
}

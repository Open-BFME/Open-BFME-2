// ?rva000AC4C6@WorldHeightMap@@QAEHH@Z
// cl: /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
//
// 0x000AC4C6 78B binary-search-free interval lookup over the height map's
// per-interval table. Retail walks the table with a pointer anchored on each
// element's start field (lea edx,[ecx+0x80d0] / mov esi,[edx] / mov ebp,[edx+4])
// and fetches the result through a separate base+index access
// (imul eax,eax,0x28 / mov eax,[eax+ecx+0x80cc]) after returning from the
// loop, so the struct is result@+0, start@+4, extent@+8, size 0x28, and the
// array base sits at this+0x80cc with the count at this+0x80c8.
typedef int Int;
class WorldHeightMap
{
public:
	Int rva000AC4C6(Int arg);
private:
	struct E { Int result; Int start; Int extent; unsigned char pad[0x28-12]; };
	unsigned char m_pad0[0x80c8];
	Int m_intervalCount;
	E m_intervals[1];
};
Int WorldHeightMap::rva000AC4C6(Int arg)
{
	arg >>= 2;
	Int n = m_intervalCount;
	for (Int i = 0; i < n; ++i) {
		Int *st = &m_intervals[i].start;
		Int s = st[0];
		if (s >= 0) {
			if (arg >= s) {
				Int top = s + st[1];
				if (arg < top)
					return m_intervals[i].result;
			}
		}
	}
	return -1;
}
// cl: /O1 /DNDEBUG /MD
//
// ?rva004A4580@Rva004A4580@@QAEPAXPAX@Z @0x004A4580 27B.
// Ignores this. Zeroes the first dword of the argument through the rowed
// memset thunk, then sets bit 1 and returns the same pointer.

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

class Rva004A4580
{
public:
	void *rva004A4580(void *p);
};

void *Rva004A4580::rva004A4580(void *p)
{
	ji_006291ae(p, 0, 4);
	*(unsigned int *)p |= 2;
	return p;
}

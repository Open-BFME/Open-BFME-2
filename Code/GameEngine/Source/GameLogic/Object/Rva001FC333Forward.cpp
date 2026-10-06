// cl: /MD
//
// ?rva001FC333@Rva001FC333@@QAEXPAX0@Z @0x001FC333, 36B.
// Forwards two void args to rowed rva001F5C60 on this then rowed rva001FBFC6
// on this+4. Evidence: __thiscall ret 8; callees rowed with PAX signatures;
// chain lane via 0x001FBFC6; prev/next indicate /O1 family.

struct Holder001F5C60;

class Rva001F5C60
{
public:
	void rva001F5C60(void *a, Holder001F5C60 *b);
};

class Rva001FBFC6
{
public:
	void rva001FBFC6(void *a, void *b);
};

class Rva001FC333
{
public:
	void rva001FC333(void *a, void *b);
};

void Rva001FC333::rva001FC333(void *a, void *b)
{
	((Rva001F5C60 *)this)->rva001F5C60(a, (Holder001F5C60 *)b);
	((Rva001FBFC6 *)((char *)this + 4))->rva001FBFC6(a, b);
}

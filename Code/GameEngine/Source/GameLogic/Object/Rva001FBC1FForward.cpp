// cl: /MD
//
// ?rva001FBC1F@Rva001FBC1F@@QAEXPAX0@Z @0x001FBC1F, 36B.
// Forwards two void args to rowed rva001F5CD0 on this then rowed rva001FA529
// on this+0xc. Evidence: __thiscall ret 8; callees rowed with PAX signatures;
// chain lane via 0x001FA529; prev/next indicate /O1 family.

struct Holder001F5CD0;

class Rva001F5CD0
{
public:
	void rva001F5CD0(void *a, Holder001F5CD0 *b);
};

class Rva001FA529
{
public:
	void rva001FA529(void *a, void *b);
};

class Rva001FBC1F
{
public:
	void rva001FBC1F(void *a, void *b);
};

void Rva001FBC1F::rva001FBC1F(void *a, void *b)
{
	((Rva001F5CD0 *)this)->rva001F5CD0(a, (Holder001F5CD0 *)b);
	((Rva001FA529 *)((char *)this + 12))->rva001FA529(a, b);
}

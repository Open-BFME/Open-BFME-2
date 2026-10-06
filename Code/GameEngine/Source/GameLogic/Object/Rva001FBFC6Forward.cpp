// cl: /MD
//
// ?rva001FBFC6@Rva001FBFC6@@QAEXPAX0@Z @0x001FBFC6, 36B.
// Forwards two void args to rowed rva001F5CA9 on this then rowed rva001FBC1F
// on this+4. Evidence: __thiscall ret 8; callees rowed with PAX signatures;
// chain lane via 0x001FBC1F; prev/next indicate /O1 family.

struct Holder001F5CA9;

class Rva001F5CA9
{
public:
	void rva001F5CA9(void *a, Holder001F5CA9 *b);
};

class Rva001FBC1F
{
public:
	void rva001FBC1F(void *a, void *b);
};

class Rva001FBFC6
{
public:
	void rva001FBFC6(void *a, void *b);
};

void Rva001FBFC6::rva001FBFC6(void *a, void *b)
{
	((Rva001F5CA9 *)this)->rva001F5CA9(a, (Holder001F5CA9 *)b);
	((Rva001FBC1F *)((char *)this + 4))->rva001FBC1F(a, b);
}

// cl: /MD
//
// ?rva001FC42D@Rva001FC42D@@QAEXPAX0@Z @0x001FC42D, 36B.
// Forwards two void args to rowed rva001F5C39 on this then rowed rva001FC333
// on this+4. Evidence: __thiscall ret 8; callees rowed with PAX signatures;
// chain lane via 0x001FC333; prev/next indicate /O1 family.

struct Holder001F5C39;

class Rva001F5C39
{
public:
	void rva001F5C39(void *a, Holder001F5C39 *b);
};

class Rva001FC333
{
public:
	void rva001FC333(void *a, void *b);
};

class Rva001FC42D
{
public:
	void rva001FC42D(void *a, void *b);
};

void Rva001FC42D::rva001FC42D(void *a, void *b)
{
	((Rva001F5C39 *)this)->rva001F5C39(a, (Holder001F5C39 *)b);
	((Rva001FC333 *)((char *)this + 4))->rva001FC333(a, b);
}

// cl: /MD
//
// ?rva001FA529@Rva001FA529@@QAEXPAX0@Z @0x001FA529, 36B.
// Forwards two void args to rowed rva001F5D71 on this then rowed rva001F8E45
// on this+4. Evidence: __thiscall ret 8; callees rowed with PAX signatures;
// chain lane via 0x001F8E45; prev/next indicate /O1 family.

struct Holder001F5D71;

class Rva001F5D71
{
public:
	void rva001F5D71(void *a, Holder001F5D71 *b);
};

class Rva001F8E45
{
public:
	void rva001F8E45(void *a, void *b);
};

class Rva001FA529
{
public:
	void rva001FA529(void *a, void *b);
};

void Rva001FA529::rva001FA529(void *a, void *b)
{
	((Rva001F5D71 *)this)->rva001F5D71(a, (Holder001F5D71 *)b);
	((Rva001F8E45 *)((char *)this + 4))->rva001F8E45(a, b);
}

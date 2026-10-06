// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva002E3A39@Rva002E3A39Owner@@QAEXPBX@Z @0x002E3A39 46B: float-pair
// forward (thiscall, 1 ptr arg, void). Copies two floats from the arg into
// an 8-byte ebp pair, then invokes pinned cdecl 0x0030B7C2 with (this+8,
// &pair). Honest address-derived names; pair/callee identities unproven.

struct Rva002E3A39Pair
{
	float a;
	float b;
};

class Rva002E3A39Owner
{
public:
	void rva002E3A39(const void *p);
};

void __cdecl rva0030B7C2(const void *a, void *b);

// ?rva002E3A39@Rva002E3A39Owner@@QAEXPBX@Z
void Rva002E3A39Owner::rva002E3A39(const void *p)
{
	Rva002E3A39Pair t;
	const float *f = (const float *)p;
	t.a = f[0];
	t.b = f[1];
	rva0030B7C2(&t, (char *)this + 8);
}

// cl: /O1
// Eight retail wrappers (23B each) forwarding (a, b, c) to a four-argument
// callee with a zero third argument. Retail bytes prove the shape per member:
// push [esp+0x0C], push 0, push [esp+0x10], push [esp+0x10],
// call <callee>, add esp, 0x10, ret. /O1 keeps the pushes on the stack slots;
// /O2 preloads eax/ecx/edx and breaks the shape. Callee identities unproven;
// the pin names are address-derived. One ledger row per wrapper.

extern "C" int __cdecl Rva0021C777Apply(int a, int b, int c, int d);
extern "C" int __cdecl Rva002B5873Apply(int a, int b, int c, int d);
extern "C" int __cdecl Rva002B641FApply(int a, int b, int c, int d);
extern "C" int __cdecl Rva00331BD7Apply(int a, int b, int c, int d);
extern "C" int __cdecl Rva003B0176Apply(int a, int b, int c, int d);
extern "C" int __cdecl Rva003BE532Apply(int a, int b, int c, int d);
extern "C" int __cdecl Rva004F73B3Apply(int a, int b, int c, int d);
extern "C" int __cdecl Rva004F7780Apply(int a, int b, int c, int d);

int Rva0021D2B6(int a, int b, int c)
{
	return Rva0021C777Apply(a, b, 0, c);
}

int Rva002B6351(int a, int b, int c)
{
	return Rva002B5873Apply(a, b, 0, c);
}

int Rva002B7485(int a, int b, int c)
{
	return Rva002B641FApply(a, b, 0, c);
}

int Rva00331D67(int a, int b, int c)
{
	return Rva00331BD7Apply(a, b, 0, c);
}

int Rva003B02A1(int a, int b, int c)
{
	return Rva003B0176Apply(a, b, 0, c);
}

int Rva003C3AB0(int a, int b, int c)
{
	return Rva003BE532Apply(a, b, 0, c);
}

int Rva004F786C(int a, int b, int c)
{
	return Rva004F73B3Apply(a, b, 0, c);
}

int Rva004F7E61(int a, int b, int c)
{
	return Rva004F7780Apply(a, b, 0, c);
}

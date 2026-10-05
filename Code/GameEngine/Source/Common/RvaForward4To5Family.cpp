// cl: /O1
// Three 4-to-5 const-zero forwarders (27B each): push [esp+0x10],
// push 0, push [esp+0x14] x3, call <callee>, add esp, 0x14, ret. Each
// forwards (a, b, c, d) as callee(a, b, c, 0, d). /O1 keeps the pushes on
// the stack slots. Callee identities unproven (opaque pins); the wrapper
// names are address-derived. One ledger row per forwarder.

extern "C" int __cdecl Rva0021E44BForward(int a, int b, int c, int d, int e);
extern "C" int __cdecl Rva002B92A7Forward(int a, int b, int c, int d, int e);
extern "C" int __cdecl Rva00337999Forward(int a, int b, int c, int d, int e);

int Rva0021E741(int a, int b, int c, int d)
{
	return Rva0021E44BForward(a, b, c, 0, d);
}

int Rva002BAE0F(int a, int b, int c, int d)
{
	return Rva002B92A7Forward(a, b, c, 0, d);
}

int Rva00337C55(int a, int b, int c, int d)
{
	return Rva00337999Forward(a, b, c, 0, d);
}

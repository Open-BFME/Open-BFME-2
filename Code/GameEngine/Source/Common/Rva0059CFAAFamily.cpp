// cl: -GR- -EHsc-
// Twin 4-arg stdcall forwarders: each forwards (a1, a2+1, a3, a4) to a
// callee that cleans its own stack (both callees end ret 0x10). The wrappers
// use no ecx and clean nothing themselves (ret 0x10). Callee signatures are
// unproven beyond arity/convention; pins record the retail REL32 targets.
void __stdcall rva0059CF34_fn(int a1, int a2, int a3, int a4);
void __stdcall rva0059CFAA_fn(int a1, int a2, int a3, int a4);

// ?rva0059D1A9@@YGXHHHH@Z @0x0059D1A9 26B
void __stdcall rva0059D1A9(int a1, int a2, int a3, int a4)
{
	rva0059CF34_fn(a1, a2 + 1, a3, a4);
}

// ?rva0059D1C3@@YGXHHHH@Z @0x0059D1C3 26B
void __stdcall rva0059D1C3(int a1, int a2, int a3, int a4)
{
	rva0059CFAA_fn(a1, a2 + 1, a3, a4);
}

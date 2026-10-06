// cl: /MD
// ?Rva00524EF4AptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2@Z @0x00524EF4 30B
// Free APT call wrapper: forwards Target as `this` plus the three caller args
// and six zeros to the thiscall AptCall twin at 0x00222B19.
// Evidence: retail 8b 4c 24 04 / 33 c0 / six 50 / three ff 74 24 28 / e8 -> 0x00222B19.
// Callers 0x00528389 and 0x0057A805 pass Target plus 3 args; the `mov ecx`
// proves the inner call is thiscall.
//
// The inner callee is the *0x00222B19* twin, not 0x00222C12. Both exist in the
// ledger with the same 9-argument thiscall signature; retail's own rel32 at
// 0x00524F0C resolves to 0x00222B19, and reverse/symbols.csv already pins
// ?rva00222B19@Rva00222A8BTarget@@QAEHPAXPBD1H10000@Z there. Naming the
// 0x00222C12 row instead compiles to the identical instruction shape but a
// wrong rel32, so the row fails byte comparison on that one field.
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function,
		int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3)
{
	return t->rva00222B19(a1, a2, a3, 0, 0, 0, 0, 0, 0);
}

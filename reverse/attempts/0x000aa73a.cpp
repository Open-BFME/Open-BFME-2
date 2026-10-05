// ?rva000AA73A@@YAPBDPAV?$StringBase@D@@PAH_N@Z
// partial score=0.85 date=2026-10-05
// BANKED 0xAA73A path-version probe. Solved: frame via /Oy-, p1 spill via
// pred-local pressure, 2-arity illusion (push edi is reg save), sscanf import
// pattern, dead flag block, "" literal. Open: pred-local lands in ecx not
// ebx (need mov ebx,[global] once + call ebx), and loop precomputes esi
// outside (need jmp-into-test only). Refuted: no-pred-local (p1 in ebx),
// direct g_pred calls. Explicit-spec StringBase<char> gives exact pin name.
// cl: /O1 /MD /EHsc /DNDEBUG /Oy-
// ?rva000AA73A@@YAPBDPBU?$StringBase@D@@PAHM_N@Z @0x000AA73A 120B: path
// version probe. Finds the last backslash then the last dot, walks back
// past predicate characters, sscanf's "%d." into the out param, and returns
// the post-backslash pointer (null when absent). The flag block computes a
// dead fallback string. Honest address-derived name; boundary verified
// (frame at 0xAA73A, leave + ret at end).
template <typename T> class StringBase;
template <> class StringBase<char> {
public:
	const char *reverseFind(char c) const;
};
extern "C" __declspec(dllimport) int __cdecl sscanf(const char *buf, const char *fmt, ...);
static int (__cdecl *g_pred)(int);
const char *rva000AA73A(StringBase<char> *path, int *out, bool flag)
{
	const char *p1 = path->reverseFind('\\');
	if (!p1)
		return 0;
	const char *p2 = path->reverseFind('.');
	if (!p2)
		return p1 + 1;
	int (__cdecl *pred)(int) = g_pred;
	const char *p = p2;
	while (pred(p[-1]))
		--p;
	sscanf(p, "%d.", out);
	if (flag) {
		const char *s = *(const char **)path;
		const char *t = s ? s + 8 : "";
	}
	return p1 + 1;
}

// cl: /MD
// ?Rva0054C83FAptCall@@YAHPAVRva00222A8BTarget@@PAXPBD2PAPBDPA_N@Z @0x0054C83F 56B
// Free APT call wrapper: forwards Target as `this` plus caller args and the
// bool-to-string selector at 0x004E678B to the thiscall AptCall twin at
// 0x00222B19 with argc 2. Evidence: callers at 0x0054CAD6 0x005E2E81
// 0x005E2ED9 0x005E2F35 pass Target plus 5 args; the `mov ecx` proves the
// inner call is thiscall; "SetTabEnabled" string in caller 0x005E2E3A.
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function,
		int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

char ** __cdecl Rva004E678BGet(char **out, bool flag);

int __cdecl Rva0054C83FAptCall(Rva00222A8BTarget *t, void *level, const char *prefix, const char *function, const char **a0, bool *flag)
{
	char *tmp;
	char *s = *Rva004E678BGet(&tmp, *flag);
	const char *a0s = *a0;
	return t->rva00222B19(level, prefix, function, 2, a0s, s, 0, 0, 0);
}

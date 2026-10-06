// cl: /MD
// ?Rva005277D9Fire@@YAXPAVRva00222A8BTarget@@PAXPBD2PA_N@Z @ 0x005277D9 (51B): bool-to-string APT fire via Rva004E678BGet and Rva00222B19AptCall thiscall spelling. Evidence: same shape as Rva004E6816Fire 48B plus one extra prefix arg; callees rowed 0x004E678B 0x00222B19; callers unclaimed APT firers.
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
char ** __cdecl Rva004E678BGet(char **out, bool flag);
void __cdecl Rva005277D9Fire(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, bool *flagPtr)
{
	char *value;
	char *val = *Rva004E678BGet((char **)&value, *flagPtr);
	target->rva00222B19(level, prefix, function, 1, val, 0, 0, 0, 0);
}

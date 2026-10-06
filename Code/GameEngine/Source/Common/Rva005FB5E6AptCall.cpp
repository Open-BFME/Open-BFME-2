// cl: /Oy- /MD
// ?Rva005FB5E6AptCall@@YAHPAVRva00222A8BTarget@@PAXPBD22@Z @0x005FB5E6 33B: free AptCall wrapper via thiscall twin rva00222B19 same 9 stack args. Evidence: thiscall twin pin at 0x00222B19 via call-site mov ecx at 0x005E30E8 precedent Rva005E30E8AptCall plus 40+ callers pushing TheRva00222A8BTarget plus level plus prefix plus function plus _show/_hide plus add esp 0x14.
class Rva00222A8BTarget
{
public:
	int rva00222B19(void *level, const char *prefix, const char *function, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};
int __cdecl Rva005FB5E6AptCall(Rva00222A8BTarget *target, void *level, const char *prefix, const char *function, const char *a0)
{
	return target->rva00222B19(level, prefix, function, 1, a0, 0, 0, 0, 0);
}

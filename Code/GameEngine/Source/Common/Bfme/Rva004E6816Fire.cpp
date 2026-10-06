// cl: /MD
// ?Rva004E6816Fire@@YAXPAVRva00222A8BTarget@@PAXPBDPA_N@Z @ 0x004E6816 (48B): fires a UI callback through Rva00222A8BTarget::invoke with a bool converted to "0"/"1" via Rva004E678BGet. Callers at 0x004E70B6 ("SetIconVisibility") and 0x005B5CE5 ("EnableCustomizeButtons") pass manager in ecx-slot owner name and bool pointer.
class Rva00222A8BTarget
{
public:
	void invoke(void *owner, const char *name, int flag, const char *value, void *a4, void *a5, void *a6, void *a7);
};
char ** __cdecl Rva004E678BGet(char **out, bool flag);
void __cdecl Rva004E6816Fire(Rva00222A8BTarget *target, void *owner, const char *name, bool *flagPtr)
{
	char *value;
	char *val = *Rva004E678BGet((char **)&value, *flagPtr);
	target->invoke(owner, name, 1, val, 0, 0, 0, 0);
}

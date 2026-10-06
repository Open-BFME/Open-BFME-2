// cl: /MD
// ?Rva004E678BGet@@YAPAPADPAPAD_N@Z @ 0x004E678B (24B): bool-to-string selector storing "1" if flag else "0" into *out and returning out. Callers at 0x004E6824 0x004E69B2 0x00511C65 0x005277E7 0x0054C84D 0x00577C4E use return as out pointer then load string for invoke. Data at 0x7BFDDC "0" 0x7BFDE0 "1".
char ** __cdecl Rva004E678BGet(char **out, bool flag)
{
	*out = flag ? "1" : "0";
	return out;
}

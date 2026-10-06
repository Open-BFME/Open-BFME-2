// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// ?Rva00559EDCCompare@@YAHPAH0@Z, retail 0x00559EDC, 34 bytes.
// Free-function 10-dword compare counting mismatches.
// Evidence: callers 0x0040104D 0x0057EA64 0x0059F76C pass two pointers then pop 8B = __cdecl 2 args; caller 0x0057EA0F lea ebp esi+0x8c lea eax edi+0x60 test eax vs 0.
int __cdecl Rva00559EDCCompare(int *a, int *b)
{
	int result = 0;
	for (int i = 0; i < 10; ++i)
		if (a[i] != b[i])
			++result;
	return result;
}

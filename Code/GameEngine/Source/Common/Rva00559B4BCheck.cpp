// cl: /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
// ?Rva00559B4BCheck@@YAEH@Z, retail 0x00559B4B, 25 bytes.
// Free-function check for 3/4/5 returning 1 else 0 as byte.
// Evidence: caller 0x00559CF3 pushes 1 arg then add esp 4 = __cdecl 1 arg and pushes eax result; neighbours share /O1 flags.
unsigned char __cdecl Rva00559B4BCheck(int v)
{
	return v == 3 || v == 4 || v == 5;
}

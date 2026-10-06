// cl: -GR- -EHsc-
int __cdecl rva0059E0C1(int a);

// ?rva0059E0F7@@YAHH@Z @0x0059E0F7 24B: cdecl wrapper; null-checks the pinned
// callee result and returns its +0xBC word, else 0.
int __cdecl rva0059E0F7(int a)
{
	int r = rva0059E0C1(a);
	if (r != 0)
		return *(int*)(r + 0xBC);
	return 0;
}

// cl: /MD
// ?Rva000E007DEqual@@YGHPBURva000E007DPair@@0@Z recurring, retail 0x000E007D, 32B.
// Equality on two-int pairs via two dword compares returning int 0/1.
// Callers 0x000E01DD (tests al) 0x000E02D1. Honest free-function name.
// __stdcall for ret 8 (callee pops 8, no add esp in callers).
struct Rva000E007DPair
{
	int m00;
	int m04;
};

int __stdcall Rva000E007DEqual(const Rva000E007DPair *a, const Rva000E007DPair *b)
{
	if (a->m00 != b->m00 || a->m04 != b->m04)
		return 0;
	return 1;
}

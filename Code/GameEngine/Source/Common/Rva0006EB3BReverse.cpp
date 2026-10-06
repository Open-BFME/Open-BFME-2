// cl: /MD
//
// ?Rva0006EB3BReverse@@YAHH@Z, retail 0x0006EB3B, 50 bytes. Frameless
// __cdecl 4-bit reversal: accumulates reversed low nibble of the single int
// arg via 1<<i masking and conditional shl/sar. Callers at 0x000709C9 and
// 0x00070E01 in FUN_00470841 push one int and consume eax. Evidence:
// loop shape, no callees, 4 iterations (push 3/pop esi). Honest verb
// Reverse describes the proven bit-reversal behavior.

int __cdecl Rva0006EB3BReverse(int x);

int __cdecl Rva0006EB3BReverse(int x)
{
	int r = 0;
	int i = 0;
	int n = 3;
	do {
		if (n > i)
			r |= (((1 << i) & x) << (n - i));
		else
			r |= (((1 << i) & x) >> (i - n));
		++i;
		--n;
	} while (n > -1);
	return r;
}

// cl: /MD
// ?rva002B4623@@YAXHHH@Z @0x002B4623 29B: cdecl 3-arg forwarder into the
// 5-arg cdecl 0x2B3049 worker: pushes 0, the address of the top byte of its
// single dword local, then c, b, a (right-to-left), call, add esp,0x14,
// leave, ret. Evidence: retail
//   push ebp; mov ebp,esp; push ecx; push 0; lea eax,[ebp-1]; push eax
//   push [ebp+0x10]; push [ebp+0xC]; push [ebp+8]; call 0x2B3049
//   add esp,0x14; leave; ret
// The worker never reads args 4-5 (decoded 47B uses only +8/+C/+10), so the
// local is a dead out-slot; only its address ([ebp-1]) matters.
// Boundary: range-table 29B; successor 0x2B4650 opens with push esi.
// Names are address-derived.
void rva002B3049(int a, int b, int c, unsigned char *out, int flag);

void rva002B4623(int a, int b, int c)
{
	unsigned char touched;
	rva002B3049(a, b, c, &touched, 0);
}

// cl: /O1 /MD
// ?rva002B5944@@YAXHHH@Z @0x002B5944 27B: cdecl 3-arg forwarder into the
// rowed 0x2B4623 worker, passing a dead fourth argument (the address of a
// stack byte the callee never reads: its 29B body touches only +8/+C/+10).
// Evidence: retail
//   push ebp; mov ebp,esp; push ecx; lea eax,[ebp-1]; push eax
//   push [ebp+0x10]; push [ebp+0xC]; push [ebp+8]; call 0x2B4623
//   add esp,0x10; leave; ret
// The 4-argument caller view needs its own pin at the rowed address (the
// row keeps the true 3-argument callee spelling).
// Boundary: range-table 27B ending at 0x2B595F (mov eax,ecx). Names are
// address-derived.
void rva002B4623(int a, int b, int c, unsigned char *dead);

void rva002B5944(int a, int b, int c)
{
	unsigned char dead;
	rva002B4623(a, b, c, &dead);
}

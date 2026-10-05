// cl: /O1 /MD
// Static forwarding shims over unrecovered idiv/movsd helpers, range-17 batch.
// ?rva003B015D@@YAXHHH@Z @0x003B015D 24B: forwards (a1,a2,a3,0,0) to pinned
// 0x003AFFBE. Evidence: five pushes with two leading zero constants, caller
// cleans 0x14, ret.
// ?rva003B02A1@@YAXHHH@Z @0x003B02A1 23B: forwards (a1,a2,0,a3) to pinned
// 0x003B0176. Evidence: four pushes with a zero third, caller cleans 0x10,
// ret. Called from rva003B02F4 0x003B02F4.
void rva003AFFBE(int a1, int a2, int a3, int a4, int a5);
void rva003B0176(int p1, int p2, int p3, int p4);

void __cdecl rva003B015D(int a1, int a2, int a3)
{
	rva003AFFBE(a1, a2, a3, 0, 0);
}

void __cdecl rva003B02A1(int a1, int a2, int a3)
{
	rva003B0176(a1, a2, 0, a3);
}

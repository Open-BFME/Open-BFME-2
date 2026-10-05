// cl: /O1 /MD
// Static forwarding shim, range-17 batch.
// ?rva003B015D@@YAXHHH@Z @0x003B015D 24B: forwards (a1,a2,a3,0,0) to pinned
// 0x003AFFBE. Evidence: five pushes with two leading zero constants, caller
// cleans 0x14, ret.
// NOTE: sibling 0x003B02A1 in this TU was removed: the address is rowed on
// master as STLport pop_heap (hansnery chain), which supersedes the
// forwarder identity claimed here. Likewise 0x003B02F4 is STLport pop.
void rva003AFFBE(int a1, int a2, int a3, int a4, int a5);

void __cdecl rva003B015D(int a1, int a2, int a3)
{
	rva003AFFBE(a1, a2, a3, 0, 0);
}

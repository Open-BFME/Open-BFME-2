// cl: /DNDEBUG /MD
//
// ?b_00042a50@@YAXXZ, retail 0x0044BA2A, 9 bytes.
// Pinned name; forwards 0 to pinned cdecl 0x00437E9C. Callers include rowed
// rva00627A50Clear 0x00548B47; BFME1 donors declare b_00042a50 in
// Rva00627A50Clear.cpp and CancelPatchCheckCallback_BFME.cpp.

void Rva00437E9C(int x);
void b_00042a50();

void b_00042a50()
{
	Rva00437E9C(0);
}

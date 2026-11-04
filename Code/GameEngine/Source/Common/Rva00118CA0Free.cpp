// ?free@Rva00118CA0@@QAEXXZ @ 0x00118CA0 (11B): frameless thiscall free wrapper
// mov eax,[ecx]; push eax; call msvcr71!free; pop ecx; ret. Frees the pointer
// at this+0 via the CRT import (IAT 0x00BBA6E8). No ledger callees (IAT only).
// Prev 0x001188C0/202 ?Set_Coordinate_Range@Render2DClass (render2d.cpp) and
// next 0x00118CB0/8 ?disable@Rva00118CB0DwordSetter (Disp8DwordSetters.cpp) are
// different files so not a gap; boundary is proven by ret plus int3 pad (ghidra
// size 11 matches bytes-to-next 11). Callers are 4 jmps from Unwind funclets
// (0x00764CB6 0x00764CC1 0x00764EA6 0x00764EB1) suggesting EH cleanup use.
// Identity unproven so the class and method keep honest Rva names. Default
// optimization is load-bearing: /O1 emits push [ecx] (10B) while defaults
// emit mov eax,[ecx]; push eax (11B exact). /MD only makes <stdlib.h> declare
// free as the msvcr71 import.
// cl: /MD
#include <stdlib.h>

class Rva00118CA0
{
public:
	void free();
	void *m_ptr;
};

void Rva00118CA0::free()
{
	::free(m_ptr);
}

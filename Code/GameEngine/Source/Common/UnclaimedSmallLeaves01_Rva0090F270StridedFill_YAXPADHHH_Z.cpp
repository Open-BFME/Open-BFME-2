// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// One unclaimed leaf body, each alone in a .text gap no ledger row covered.
// It starts 16-byte aligned directly after an int3 pad run and ends on a ret
// followed by int3 padding; it is not reached by a call, ILT stub, table slot
// or code immediate, no pin or dir32 name sits at its address, and it calls
// nothing.
//
// IDENTITY IS NOT RECOVERED.  The name is derived from the BFME 1 address;
// parameter names say only what the bytes do.
//
// Dedicated TU: only the placed body is defined; the donor's other seven
// definitions are omitted.

// 0x0090F270: cdecl strided dword fill.
void Rva0090F270StridedFill( char *dest, int stride, int value, int count )
{
	while ( count-- )
	{
		*(int *)dest = value;
		dest += stride;
	}
}
// cl: /MD
// ?Rva004D933BIs@@YA_NH@Z @0x004D933B (39B):
// Free __cdecl predicate: arg is one of 0x7E6 0x7E7 0x7EC 0x7E8.
// Evidence: unlock lane, 4x cmp-je plus xor-inc shape, caller 0x004D9492
// pushes one dword and uses al, unblocks 0x004D9453 0x004D990E 0x004D9CF3.
bool __cdecl Rva004D933BIs(int v)
{
	return v == 0x7E6 || v == 0x7E7 || v == 0x7EC || v == 0x7E8;
}

// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014F995CopyBackward@@YAXPAURva0014F718@@00@Z @0x0014F995 29B wrapper forwarding to rowed 5-arg 0x0014F718.
// Retail: push ebp / mov ebp esp / push ecx / push 0 / lea eax [ebp-1] / push eax / push [ebp+0x10] / push [ebp+c] / push [ebp+8] / call 0x0014F718 / add esp 0x14 / leave / ret.
// Evidence: forwarder to just-landed ?Rva0014F718CopyBackward 0x0014F718; stride 8; callers 0x00150729 0x00150807 0x001508E5 in 222B insert paths.
// Not established: owning class identity; honest Rva name.
struct Rva0014F718
{
	int m_00;
	int m_04;
};

Rva0014F718 *__cdecl Rva0014F718CopyBackward(Rva0014F718 *first, Rva0014F718 *last, Rva0014F718 *dest, void *tag, int extra);

void __cdecl Rva0014F995CopyBackward(Rva0014F718 *first, Rva0014F718 *last, Rva0014F718 *result)
{
	char tag;
	Rva0014F718CopyBackward(first, last, result, &tag, 0);
}

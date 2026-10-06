// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva00150248Copy@@YAXPAURva0014F718@@00@Z @0x00150248 29B wrapper forwarding to rowed 5-arg 0x0014FA62.
// Retail: push ebp / mov ebp esp / push ecx / push 0 / lea eax [ebp-1] / push eax / push [ebp+0x10] / push [ebp+0xc] / push [ebp+8] / call 0x14FA62 / add esp 0x14 / leave / ret.
// Evidence: 5-arg caller pushes 5 with add esp 0x14; sibling Rva00150265Copy 29B same shape to 5-arg forward 0x0014FA90; chain from 0x0014FA62.
// Not established: owning class identity; name is address-derived.
struct Rva0014F718
{
	int m_00;
	int m_04;
};

Rva0014F718 *__cdecl Rva0014FA62Copy(Rva0014F718 *first, Rva0014F718 *last, Rva0014F718 *dest, void *tag, int extra);

void __cdecl Rva00150248Copy(Rva0014F718 *first, Rva0014F718 *last, Rva0014F718 *result)
{
	char tag;
	Rva0014FA62Copy(first, last, result, &tag, 0);
}

// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0014FA62Copy@@YAPAURva0014F718@@PAU1@00PAXH@Z @0x0014FA62 46B forward copy of dword at +4 for 8-byte entries, sibling of backward 0x0014F718.
// Retail: push ebp / mov ebp esp / sub ecx eax / sar ecx 3 / test / jle / add eax 4 / loop mov edx [eax] / mov esi [ebp+0x10] / add [ebp+0x10] 8 / add eax 8 / dec ecx / mov [esi+4] edx.
// Evidence: stride 8 via sar 3; single-dword +4 copy matches backward 0x0014F718 family (vptr at +0 skipped); 5-arg caller 0x00150248 pushes 5 with add esp 0x14; neighbours Rva0014FA2AFill Rva0014FA90Copy same dir // cl: /O1.
// Not established: owning class identity; honest Rva name.
struct Rva0014F718
{
	int m_00;
	int m_04;
};

Rva0014F718 *__cdecl Rva0014FA62Copy(Rva0014F718 *first, Rva0014F718 *last, Rva0014F718 *dest, void *tag, int extra)
{
	int n = last - first;
	if (n > 0) {
		for (int i = n; i != 0; --i) {
			dest->m_04 = first->m_04;
			++first;
			++dest;
		}
	}
	return dest;
}

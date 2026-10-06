// cl: /Oy-
// ?Rva0014F718CopyBackward@@YAPAURva0014F718@@PAU1@00PAXH@Z @0x0014F718 46B.
// copy_backward for 8-byte entries copying dword at +4 (vptr at +0 skipped).
// Retail: sar 3 count, --last/--dest loop with single mov [esi+4]<-[ecx], 5-arg __cdecl with dummy tag/extra riding dead above frame.
// Evidence: forwarder 0x0014F995 pushes 5 (first last dest tag 0) with add esp 0x14; stride 8 proves 8B entries; single-dword +4 copy matches Rva0014F4A1 family (vptr+int) fill 0x0014F9B2.
// Not established: owning class identity; honest Rva name.
struct Rva0014F718
{
	int m_00;
	int m_04;
};

Rva0014F718 *__cdecl Rva0014F718CopyBackward(Rva0014F718 *first, Rva0014F718 *last, Rva0014F718 *dest, void *tag, int extra)
{
	int n = last - first;
	if (n > 0) {
		for (int i = n; i != 0; --i) {
			--dest;
			--last;
			dest->m_04 = last->m_04;
		}
	}
	return dest;
}

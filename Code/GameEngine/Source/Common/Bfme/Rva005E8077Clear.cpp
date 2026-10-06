// cl: /MD
// ?rva005E8077@Rva005E8077@@QAEXXZ @0x005E8077 30B
// Vector clear-and-free: destroy range [m_start m_finish) via rowed 0x005E7FB0
// then free m_start via rowed _free 0x00030830. No EH frame.
// Evidence: pushes [esi+4] [esi] then calls 0x005E7FB0; reloads [esi] and frees.
struct Rva005E74AA;
void __cdecl Rva005E7FB0Forward(Rva005E74AA *first, Rva005E74AA *last);
extern "C" void __cdecl free(void *block);
struct Rva005E8077
{
	Rva005E74AA *m_start;
	Rva005E74AA *m_finish;
	void rva005E8077();
};
void Rva005E8077::rva005E8077()
{
	Rva005E7FB0Forward(m_start, m_finish);
	Rva005E74AA *start = m_start;
	if (start)
		free(start);
}

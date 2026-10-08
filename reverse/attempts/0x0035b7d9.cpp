// ?rva0035B7D9@CommandButton@@QAEXPAURva0035B7D9View@@_N@Z
// partial score=0.8 date=2026-10-08
// ?rva0035B7D9@CommandButton@@QAEXPAURva0035B7D9View@@_N@Z
// partial score=0.8 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// Retail 0x0035B7D9 (76 bytes): thiscall, two stack arguments, ret 8. Clears the
// ModuleData vector at +0xEC through the void* erase 0x0031BD55, copies every
// element of the source vector (begin +0xEC, end +0xF0) with push_back, then
// sets byte +0x28 of the object behind global 0xE01CFC when flag is set.
// Loop compare must be unsigned '<' (retail jb), which this file shows.
// Blocker: the clear() call resolves to the element-typed erase, not the void*
// erase row that retail calls; a void* stand-in vector is needed for the call.
struct Rva0035B7D9View
{
	char m_pad00[0xEC];
	const ModuleData **m_begin;
	const ModuleData **m_end;
};

extern void *g_00E01CFC;

void CommandButton::rva0035B7D9(Rva0035B7D9View *source, bool flag)
{
	m_ec.clear();
	for (const ModuleData **it = source->m_begin; it < source->m_end; ++it)
		m_ec.push_back(*it);
	if (flag)
		((unsigned char *)g_00E01CFC)[0x28] = 1;
}

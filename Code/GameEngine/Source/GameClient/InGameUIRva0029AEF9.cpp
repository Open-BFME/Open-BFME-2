// cl: /DNDEBUG /MD
// ?Rva0029AEF9Check@@YG_NPAURva0029AEF9Item@@HHHHH@Z 0x0029AEF9 35B: InGameUI-adjacent leaf checking flags at +0x1C bit 0x20 then low 3 bits then second arg non-zero.
// Evidence: called from 0x0042A22E; prev/next InGameUI TUs share /O1 /DNDEBUG; ret 0x18 six stack args; callees none.
struct Rva0029AEF9Item
{
	char m_pad[0x1C];
	int m_1C;
};
bool __stdcall Rva0029AEF9Check(Rva0029AEF9Item *p, int q, int a, int b, int c, int d)
{
	int flags = p->m_1C;
	if (flags & 0x20)
		return true;
	if ((flags & 7) != 0)
		return q != 0;
	return false;
}

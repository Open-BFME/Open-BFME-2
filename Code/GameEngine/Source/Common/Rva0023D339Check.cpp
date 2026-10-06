// cl: /MD
// ?Rva0023D339Get@@YA_NXZ, retail 0x0023D339, 34 bytes.
// mov eax,[g1] mov eax,[eax+0x122c] imul eax,[gInt] mov ecx,[g2] imul 60 cmp [ecx+0x40],eax sbb inc ret.
// Evidence: unlock lane; caller 0x005101EB tests al with no args.
struct Rva0023D339A
{
	char m_00[4652];
	unsigned int m_122C;
};
struct Rva0023D339B
{
	char m_00[64];
	unsigned int m_40;
};
extern Rva0023D339A *g_Rva0023D339A;
extern unsigned int g_bfmeRva42E8C1Add;
extern Rva0023D339B *g_Rva0023D339B;
bool Rva0023D339Get()
{
	unsigned int tmp = g_Rva0023D339A->m_122C;
	tmp *= g_bfmeRva42E8C1Add;
	Rva0023D339B *b = g_Rva0023D339B;
	tmp *= 60;
	return b->m_40 >= tmp;
}
// ?g_Rva0023D339A@@3PAURva0023D339A@@A: the global at VA 0xdfe758 is ?TheGlobalData@@3PAVGlobalData@@A.
#pragma comment(linker, "/alternatename:?g_Rva0023D339A@@3PAURva0023D339A@@A=?TheGlobalData@@3PAVGlobalData@@A")
// ?g_Rva0023D339B@@3PAURva0023D339B@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.
#pragma comment(linker, "/alternatename:?g_Rva0023D339B@@3PAURva0023D339B@@A=?TheGameLogic@@3PAVGameLogic@@A")

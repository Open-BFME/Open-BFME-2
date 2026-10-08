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
extern class GlobalData *TheWritableGlobalData;
extern unsigned int g_bfmeRva42E8C1Add;
extern class GameLogic *TheGameLogic;
bool Rva0023D339Get()
{
	unsigned int tmp = (*(Rva0023D339A **)&TheWritableGlobalData)->m_122C;
	tmp *= g_bfmeRva42E8C1Add;
	Rva0023D339B *b = (*(Rva0023D339B **)&TheGameLogic);
	tmp *= 60;
	return b->m_40 >= tmp;
}

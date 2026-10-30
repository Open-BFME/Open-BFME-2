// cl: /MD
// ?canPlayersTransferMoneyYet@@YA_NXZ, retail 0x0023D339, 34 bytes.
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
extern int BfmeLogicFramesPerSecond;
extern class GameLogic *TheGameLogic;
// WorldBuilder canPlayersTransferMoneyYet, WB VA 0x00D10670 (callsite lead, score 1.0).
bool canPlayersTransferMoneyYet()
{
	unsigned int threshold = (*(Rva0023D339A **)&TheWritableGlobalData)->m_122C;
	threshold *= (*(unsigned int *)&BfmeLogicFramesPerSecond);
	Rva0023D339B *b = (*(Rva0023D339B **)&TheGameLogic);
	threshold *= 60;
	return b->m_40 >= threshold;
}

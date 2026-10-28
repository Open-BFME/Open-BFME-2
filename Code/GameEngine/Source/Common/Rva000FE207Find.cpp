// cl: /DNDEBUG /MD
//
// ?findTrack@WaterTracksRenderSystem@@QAEPAUFeNode@@PBM0H@Z @0x000FE207 137B.
// Evidence: container +0x10 head and +0xb0 next match Rva000FE001Move;
// float pairs +0x60/+0x64 vs arg2 and +0x58/+0x5c vs arg1 via movss/ucomiss;
// dword +0x30 vs arg3; ret 0xC with 3 stack args; caller 0x000FF7C8.

struct FeNode
{
	unsigned char m_pad0[0x30];
	int m_30;
	unsigned char m_pad1[0x3c - 0x34];
	unsigned char m_flag3c;
	unsigned char m_pad2[0x58 - 0x3d];
	float m_58;
	float m_5c;
	float m_60;
	float m_64;
	unsigned char m_pad3[0xb0 - 0x68];
	FeNode *m_next;
	FeNode *m_prev;
};

class WaterTracksRenderSystem
{
public:
	__declspec(noinline) FeNode *findTrack(const float *start, const float *end, int type);

private:
	unsigned char m_pad[0x10];
	FeNode *m_tail10;
	FeNode *m_head14;
};

inline FeNode *WaterTracksRenderSystem::findTrack(const float *start, const float *end, int type)
{
	FeNode *node = m_tail10;
	while (node != 0)
	{
		unsigned char endXMatches = (node->m_60 == end[0]) ? 1 : 0;
		unsigned char endYMatches = (node->m_64 == end[1]) ? 1 : 0;
		if ((endXMatches & endYMatches) != 0)
		{
			unsigned char startXMatches = (node->m_58 == start[0]) ? 1 : 0;
			unsigned char startYMatches = (node->m_5c == start[1]) ? 1 : 0;
			if ((startXMatches & startYMatches) != 0)
			{
				if (node->m_30 == type)
					return node;
			}
		}
		node = node->m_next;
	}
	return 0;
}
// Select-any: W3DWaterTracks.cpp compiles an identical copy; the anchor keeps the rowed body emitted.
// ?bfmeAnchorRva000FE207Find absent-from-retail
void bfmeAnchorRva000FE207Find(WaterTracksRenderSystem *waterTracksRenderSystem) { waterTracksRenderSystem->findTrack(0, 0, 0); }

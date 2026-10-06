// cl: /DNDEBUG /MD
//
// ?rva000FE207@WaterTracksRenderSystem@@QAEPAUFeNode@@PBM0H@Z @0x000FE207 137B.
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
	FeNode *rva000FE207(const float *a, const float *b, int c);

private:
	unsigned char m_pad[0x10];
	FeNode *m_tail10;
	FeNode *m_head14;
};

FeNode *WaterTracksRenderSystem::rva000FE207(const float *a, const float *b, int c)
{
	FeNode *node = m_tail10;
	while (node != 0)
	{
		unsigned char d1 = (node->m_60 == b[0]) ? 1 : 0;
		unsigned char a1 = (node->m_64 == b[1]) ? 1 : 0;
		if ((d1 & a1) != 0)
		{
			unsigned char d2 = (node->m_58 == a[0]) ? 1 : 0;
			unsigned char a2 = (node->m_5c == a[1]) ? 1 : 0;
			if ((d2 & a2) != 0)
			{
				if (node->m_30 == c)
					return node;
			}
		}
		node = node->m_next;
	}
	return 0;
}

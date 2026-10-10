// cl: /DNDEBUG /MD
// ?rva00492FC2@Rva00492FC2@@QAEX_N@Z @0x00492FC2 71B evidence: thiscall void bool; vtable slot2 virtual float; TheGameLogic VA 0x00DFE78C +0x40 frame; members +0x08 accum +0x0C count +0x10 base +0x14 float; unblocks 0x004C4430 0x00493C5A; next Rva00493009Xfer same flags

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_40;
};

extern GameLogic *TheGameLogic;

class Rva00492FC2
{
public:
	virtual void v0();
	virtual void v1();
	virtual float v2();
	void rva00492FC2(bool flag);
private:
	char m_pad04[0x04];
	int m_08;
	int m_0C;
	int m_10;
	float m_14;
};

void Rva00492FC2::rva00492FC2(bool flag)
{
	if (flag)
	{
		if (m_0C == 0)
		{
			m_10 = TheGameLogic->m_40;
			m_14 = v2();
		}
		++m_0C;
	}
	else
	{
		if (m_0C > 0)
		{
			int c = m_0C - 1;
			m_0C = c;
			if (c == 0)
			{
				int f = TheGameLogic->m_40;
				m_08 += f - m_10;
			}
		}
	}
}
// ?g_009FE78C@@3PAUGameLogic@@A: the global at VA 0xdfe78c is ?TheGameLogic@@3PAVGameLogic@@A.

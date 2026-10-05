// ?rva004FB382@Rva004FB382@@QAE_NXZ
// partial score=0.97 date=2026-10-05
// cl: /Ireference/shims/bfme2_ascii /O1
// ?rva004FB382@Rva004FB382@@QAE_NXZ 0x004FB382 112: predicate over LivingWorld players.
// Evidence: callees rowed 0x002B52A8 Rva002BA8F1Logic::rva002B52A8 plus pin 0x002E0BC0
// Rva002E0BC0Helper::rva002E0BC0; caller 0x004FBB25 shares this+0 helper and this+4 state;
// global g_009FEF10 mangled ?g_009FEF10@@3PAVRva002BA8F1Logic@@A; Player +0x14 int and
// +0x3C4 byte match Rva002BA8F1Lookups layout.

class Rva002E2903Player
{
public:
	char m_pad0[0x14];
	int m_14;
	char m_pad1[0x3C4 - 0x18];
	unsigned char m_3C4;
};

class Rva002E0BC0Helper
{
public:
	unsigned char rva002E0BC0(int val);
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *rva002B52A8(int index);
private:
	char m_pad[0x8c];
public:
	struct PlayerVec
	{
		Rva002E2903Player **m_start;
		Rva002E2903Player **m_finish;
		Rva002E2903Player **m_end;
		int size() const { return m_finish - m_start; }
	};
	PlayerVec m_players;
};

extern Rva002BA8F1Logic *g_009FEF10;

class Rva004FB382
{
private:
	Rva002E0BC0Helper *m_0;
public:
	bool rva004FB382();
};

// ?rva004FB382@Rva004FB382@@QAE_NXZ present-unmatched
bool Rva004FB382::rva004FB382()
{
	if (m_0 != 0)
	{
		for (int i = 0; i < g_009FEF10->m_players.size(); ++i)
		{
			int v = g_009FEF10->rva002B52A8(i)->m_14;
			if (!m_0->rva002E0BC0(v))
			{
				if (g_009FEF10->rva002B52A8(i)->m_3C4 == 0)
					return false;
			}
		}
	}
	return true;
}

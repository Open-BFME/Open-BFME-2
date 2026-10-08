// cl: /MD
// ?rva00404781@Rva00404781@@QAEXMHH@Z retail 0x00404781 77B
// Evidence: __thiscall float int int ret 0xC; touches +0x50[i] +0xA4 then +0[i] +0xA0; stride 0xA8 from caller 0x0056C4D3 imul; callers 0x00405180 0x0056C505
// ?rva0040475C@Rva00404781@@QAEXXZ retail 0x0040475C 37B
// Evidence: __thiscall zeroing m_a[20] m_b[20] m_flags0 m_flags1; same layout as 0x00404781; callers 0x00404AA8 0x00404B5B 0x0040553D 0x0056C1EB
class Rva00404781;

// Native 0x00404C26 returns a 0x18-byte parameter record. The member at
// 0x00404927 reads the same two input arrays and returns exactly 0 or 1.
class Rva00404927
{
public:
	int rva00404927(Rva00404781 *cell, int player);
	float unknown00;
	float allyScale;
	float enemyScale;
	float cellRatio;
	float threshold;
	float unknown14;
};

class Rva00404C26
{
public:
	Rva00404927 *rva00404C26(int player);
};

// Owned native VictorySystem pointer, defined by GameStateInit.cpp.
extern void *g_Va00E02F3C;

class Rva00404781
{
public:
	void rva00404781(float v, int i, int j);
	void rva0040475C();
	int rva00404CF5(bool useCellRatio);
private:
	float m_a[20]; // +0x00
	float m_b[20]; // +0x50
	unsigned int m_flags0; // +0xA0
	unsigned int m_flags1; // +0xA4
};

void Rva00404781::rva00404781(float v, int i, int j)
{
	m_b[i] += v;
	m_flags1 |= (1u << i);
	if (i == j)
		return;
	m_a[j] += v;
	m_flags0 |= (1u << j);
}

void Rva00404781::rva0040475C()
{
	for (unsigned int i = 0; i < 20; ++i) {
		m_b[i] = 0.0f;
		m_a[i] = 0.0f;
	}
	m_flags1 = 0;
	m_flags0 = 0;
}

// Primary source lead: Open-BFME-1 ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f,
// game/GameEngine/Source/GameLogic/System/BfmeCellEvaluateVictory.cpp.
// Its semantic labels are donor-derived. BFME2 evidence independently fixes
// twenty entries, +0/+50 arrays, the owned singleton and both native callees.
// The target's original cell class and method names remain unresolved.
int Rva00404781::rva00404CF5(bool useCellRatio)
{
	int result = 0;
	if (useCellRatio)
	{
		for (unsigned int player = 0; player < 20; ++player)
		{
			if (static_cast<unsigned char>(static_cast<Rva00404C26 *>(g_Va00E02F3C)->rva00404C26(player)->rva00404927(this, player)))
				result |= 1 << player;
		}
	}
	else
	{
		for (unsigned int player = 0; player < 20; ++player)
		{
			Rva00404927 *parameters = static_cast<Rva00404C26 *>(g_Va00E02F3C)->rva00404C26(player);
			if (m_a[player] * parameters->enemyScale - m_b[player] * parameters->allyScale > parameters->threshold)
				result |= 1 << player;
		}
	}
	return result;
}

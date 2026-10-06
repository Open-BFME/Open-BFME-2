// cl: /DNDEBUG /MD /EHsc
// ?Rva0058AF47Check@@YG_NPAVRva002A9BF2@@@Z @0x0058AF47 108B, caller 0x004B332D.
// Free stdcall chance test: indexes a 32-byte entry table at +0x888 of the
// g_00DFEEF8 owner by the rowed 0x002A9BF2 difficulty getter (shl eax,5,
// rep movsd of 8 dwords to the stack), and passes outright when the ratio
// num/den (+0xC/+0x10) reaches 1.0; otherwise rolls the rowed
// GetGameLogicRandomValue(0, den - 1) with the AIDifficulty.cpp __FILE__
// literal and line 0x40, and passes when the roll is below num.
// Structural inference: the test is written ratio < 1.0f, which keeps the
// 1.0 constant first in comiss and jumps to the pass tail on jbe as retail.

class Rva002A9BF2
{
public:
	void *rva002A9BF2();
	bool fromGate(Rva002A9BF2 *key);
};

struct AIDiffEntry
{
	char _pad0[4]; // +0x00
	int m_04; // +0x04
	int m_08; // +0x08
	int m_num; // +0x0C
	int m_den; // +0x10
	int m_14; // +0x14
	int m_18; // +0x18
	unsigned int m_1C; // +0x1C
};

struct Rva002A8AB1Record
{
	char _pad0[0xCC]; // +0x00
	unsigned int m_cc; // +0xCC
	unsigned int m_d0; // +0xD0
	char _pad1[0x16C - 0xD4]; // +0xD4
	int m_16C; // +0x16C
};

class Rva002A8F24
{
public:
	char m_pad[0x888];
	AIDiffEntry m_table[4]; // +0x888
	Rva002A8AB1Record *rva002A8AB1(void *key);
};

class AIDifficulty
{
public:
	bool allowEconomyUpgrade(Rva002A9BF2 *p);
	bool allowOffensiveTactic(Rva002A9BF2 *p);
};

extern Rva002A8F24 *g_00DFEEF8;

extern float g_Va00BBB8D8;

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

bool __stdcall Rva0058AF47Check(Rva002A9BF2 *p)
{
	int diff = (int)p->rva002A9BF2();
	AIDiffEntry e = g_00DFEEF8->m_table[diff];
	float num = (float)e.m_num;
	float den = (float)e.m_den;
	float ratio = num / den;
	if (ratio < 1.0f)
	{
		int r = GetGameLogicRandomValue(0, e.m_den - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIDifficulty.cpp", 0x40);
		return r < e.m_num;
	}
	return true;
}

// Same 108 bytes as the stdcall above. The caller at 0x004B332D is thiscall-shaped:
// push the player, call the getter, mov ecx, eax, call. This name is the
// identical-code fold of that call site.
bool Rva002A9BF2::fromGate(Rva002A9BF2 *p)
{
	int diff = (int)p->rva002A9BF2();
	AIDiffEntry e = g_00DFEEF8->m_table[diff];
	float num = (float)e.m_num;
	float den = (float)e.m_den;
	float ratio = num / den;
	if (ratio < 1.0f)
	{
		int r = GetGameLogicRandomValue(0, e.m_den - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIDifficulty.cpp", 0x40);
		return r < e.m_num;
	}
	return true;
}

// AIDifficulty::allowOffensiveTactic @0x0058AFB3 139B, caller 0x00506193.
// Named from WorldBuilder AIDifficulty.cpp: its asserts span lines 79..91 and
// the roll below passes line 91 (0x5b); callees 0x002A9BF2, 0x002A8AB1 and
// GetGameLogicRandomValue agree.
bool AIDifficulty::allowOffensiveTactic(Rva002A9BF2 *key)
{
	int diff = (int)key->rva002A9BF2();
	if (diff == 0)
	{
		Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(key);
		if (rec->m_16C == diff)
			return false;
	}
	AIDiffEntry e = g_00DFEEF8->m_table[diff];
	float num = (float)e.m_14;
	float den = (float)e.m_18;
	float ratio = num / den;
	if (ratio < 1.0f)
	{
		int r = GetGameLogicRandomValue(0, e.m_18 - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIDifficulty.cpp", 0x5b);
		return r < e.m_14;
	}
	return true;
}

// ?allowEconomyUpgrade@AIDifficulty@@QAE_NPAVRva002A9BF2@@@Z @0x0058AEBC 139B, caller 0x004EA88C.
// Free stdcall chance test like 0x0058AF47 but with the +0x04/+0x08 num/den
// columns and a record-gated early-out: fails when rec->m_cc + rec->m_d0
// reaches e.m_1C, passes when num/den reaches 1.0, otherwise rolls the rowed
// GetGameLogicRandomValue(0, den - 1) with the AIDifficulty.cpp __FILE__
// literal and line 0x2d, and passes when the roll is below num.
bool AIDifficulty::allowEconomyUpgrade(Rva002A9BF2 *p)
{
	int diff = (int)p->rva002A9BF2();
	AIDiffEntry e = g_00DFEEF8->m_table[diff];
	Rva002A8AB1Record *rec = g_00DFEEF8->rva002A8AB1(p);
	if (rec->m_cc + rec->m_d0 < e.m_1C)
	{
		float num = (float)e.m_04;
		float den = (float)e.m_08;
		float ratio = num / den;
		if (ratio < 1.0f)
		{
			int r = GetGameLogicRandomValue(0, e.m_08 - 1, "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AIDifficulty.cpp", 0x2d);
			return r < e.m_04;
		}
		return true;
	}
	return false;
}

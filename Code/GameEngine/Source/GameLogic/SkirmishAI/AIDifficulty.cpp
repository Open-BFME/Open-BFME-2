// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE
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
};

struct AIDiffEntry
{
	char _pad0[12];
	int m_num; // +0x0C
	int m_den; // +0x10
	int m_14; // +0x14
	int m_18; // +0x18
	char _pad2[4];
};

struct Rva002A8AB1Record
{
	char m_pad[0x16C];
	int m_16C; // +0x16C
};

class Rva002A8F24
{
public:
	char m_pad[0x888];
	AIDiffEntry m_table[4]; // +0x888
	Rva002A8AB1Record *rva002A8AB1(void *key);
};

class Rva0058AFB3
{
public:
	bool rva0058AFB3(void *key);
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

bool Rva0058AFB3::rva0058AFB3(void *key)
{
	int diff = (int)((Rva002A9BF2 *)key)->rva002A9BF2();
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

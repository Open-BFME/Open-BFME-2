// cl: /O1 /MD
// ?rva0042008F@Rva00420110@@QAE_NXZ, retail 0x0042008F, 60 bytes. Vslot 18
// of vtable 0x00C3BA28: if m_86 set or GameInfo slot 0x50 true then false;
// else bounds-check m_68 in [0,20) and tail-call virtual slot 0x38 with
// m_dword18[m_68]. Evidence: callers none; callees rowed GameInfo 0x00A02EEC
// slot 0x50 plus own slot 0x38; layout +0x18/+0x68/+0x86 matches init 0x0041FE86.

class GameInfo
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void s10() = 0;
	virtual void s11() = 0;
	virtual void s12() = 0;
	virtual void s13() = 0;
	virtual void s14() = 0;
	virtual void s15() = 0;
	virtual void s16() = 0;
	virtual void s17() = 0;
	virtual void s18() = 0;
	virtual void s19() = 0;
	virtual bool s20() = 0;
};
extern GameInfo *TheGameInfo;

class Player
{
public:
	virtual ~Player();
};

class PlayerList
{
public:
	Player *getNthPlayer(int i);
};
extern PlayerList *ThePlayerList;

class RecorderClass
{
public:
	bool isMultiplayer();
};

struct Bfme939Helper : public RecorderClass
{
};
extern Bfme939Helper *g_bfme939Helper;

class Radar
{
public:
	unsigned char m_pad[0x11];
	unsigned char m_11;
};
extern Radar *TheRadar;

class Rva00420110
{
public:
	virtual ~Rva00420110();
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual bool v14(int x) = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual bool v26(Player *p) = 0;
	bool rva0042008F();
	void rva0041FFAD();
private:
	char m_pad04[0x8];
	int m_0C;
	char m_pad10[0x8];
	int m_dword18[0x14];
	int m_68;
	int m_6C;
	unsigned char m_byte70[0x14];
	unsigned char m_84;
	unsigned char m_85;
	unsigned char m_86;
};

bool Rva00420110::rva0042008F()
{
	if (m_86 != 0)
		return false;
	if (TheGameInfo != 0 && TheGameInfo->s20() != false)
		return false;
	int idx = m_68;
	if (idx < 0 || (unsigned int)idx >= 0x14)
		return false;
	return v14(m_dword18[idx]);
}

// ?rva0041FFAD@Rva00420110@@QAEXXZ @0x0041FFAD 106B
// Vslot 17 of vtable 0x00C3BA28 (offset 0x44). If not multiplayer return;
// else poll 20 players via ThePlayerList slot, count true from own slot
// 0x68, zero m_dword18 tail, then if m_68<0 set m_84/m_86 and TheRadar+0x11.
// Evidence: same this as neighbours, layout +0x18/+0x68/+0x84/+0x86 matches
// init 0x0041FE86 and slot 0x0042008F; callees rowed isMultiplayer
// 0x0037B18C getNthPlayer 0x002A7A29 plus own slot 0x68; globals
// g_bfme939Helper ThePlayerList TheRadar as packet annotates.
void Rva00420110::rva0041FFAD()
{
	if (!g_bfme939Helper->isMultiplayer())
		return;
	unsigned int n = 0;
	for (int i = 0; i < 0x14; ++i) {
		Player *p = ThePlayerList->getNthPlayer(i);
		if (v26(p))
			++n;
	}
	if (n < 0x14) {
		for (unsigned int i = n; i < 0x14; ++i)
			m_dword18[i] = 0;
	}
	if (m_68 >= 0)
		return;
	m_84 = 1;
	TheRadar->m_11 = 1;
	m_86 = 1;
}

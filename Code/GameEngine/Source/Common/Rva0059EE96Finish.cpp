// cl: /MD
// AptOnlineCustomMatch (WorldBuilder names 0x0059EEE2 UpdateHostStartGameButton,
// AptOnlineCustomMatch.cpp lines 4429..4432, which calls 0x0059EE96 on the same this).
// ?rva0059EE96 @0x0059EE96 76B: guarded Enable/Disable AptCall.
// If force a1 is clear and flag +0x4C1 already equals value a0 return; else
// store flag, pick literal EnableButtonPlayGame vs DisableButtonPlayGame by a0,
// get prefix via virtual slot 0x28, load level via m58 plus 0x274, then rowed
// 0x00524EF4 AptCall with TheRva00222A8BTarget.
// Evidence: retail cmp/je early plus test/je string select plus call-indirect
// plus three pushes to 0x00524EF4, neighbours Disp32Clearer plus Rva0059EF62Set,
// callers 0x0059EF29 0x005A27DC 0x005A62CF 0x005A655B.
class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

class GameSlot
{
public:
	bool isHuman() const;
};

class GameInfo
{
public:
	GameSlot *getSlot(int slotNum);
};

class GameSpyInfoInterface
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void f26();
	virtual void f27();
	virtual void f28();
	virtual void f29();
	virtual void f30();
	virtual void f31();
	virtual void f32();
	virtual void f33();
	virtual void f34();
	virtual void f35();
	virtual void f36();
	virtual void f37();
	virtual void f38();
	virtual void f39();
	virtual void f40();
	virtual void f41();
	virtual void f42();
	virtual void f43();
	virtual void f44();
	virtual void f45();
	virtual void f46();
	virtual void f47();
	virtual void f48();
	virtual void f49();
	virtual void f50();
	virtual void f51();
	virtual void f52();
	virtual GameInfo *f53();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

struct Mid0059EE96
{
	char m_pad00[0x274];
	void *m_level274;
};

class AptOnlineCustomMatch
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual const char *f10();
	void rva0059EE96(unsigned char a0, unsigned char a1);
	void UpdateHostStartGameButton();
private:
	char m_pad04[0x58 - 4];
	Mid0059EE96 *m_mid58;
	char m_pad5C[0x4C1 - 0x5C];
	unsigned char m_flag4C1;
};

void AptOnlineCustomMatch::rva0059EE96(unsigned char a0, unsigned char a1)
{
	if (!a1)
	{
		if (m_flag4C1 == a0)
			return;
	}
	m_flag4C1 = a0;
	void *lvl;
	if (a0)
	{
		lvl = m_mid58->m_level274;
		Rva00524EF4AptCall(TheRva00222A8BTarget, lvl, f10(), "EnableButtonPlayGame");
	}
	else
	{
		lvl = m_mid58->m_level274;
		Rva00524EF4AptCall(TheRva00222A8BTarget, lvl, f10(), "DisableButtonPlayGame");
	}
}

void AptOnlineCustomMatch::UpdateHostStartGameButton()
{
	if (!TheGameSpyInfo)
		return;
	GameInfo *gi = TheGameSpyInfo->f53();
	if (!gi)
		return;
	int human = 0;
	for (int i = 0; i < 8; ++i)
	{
		GameSlot *slot = gi->getSlot(i);
		if (slot->isHuman())
			++human;
	}
	rva0059EE96(human >= 2, 0);
}

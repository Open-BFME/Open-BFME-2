// cl: -O1 -GR- -EHsc-
// ?Run@Rva005A0D61@@QAEXH@Z @0x005A0D61 97B: flag-gated refresh with time.
// If the byte arg is nonzero goto tail; else if m_4AC is nonzero, snapshot
// timeGetTime, compare m_4AC+0x3E8 against it, and goto tail unless above;
// run the +0x450 sub-object check (rowed 0x580172), and unless it passes,
// run the GameSpyInfo slot-0xB8 virtual; if that is false return, else tail.
// Tail refreshes via pinned 0x5A061B, snapshots timeGetTime, stamps m_4AC.
// timeGetTime via explicit dllimport (mov-ebx CSE, call-ebx twice).
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

class Rva00580172
{
public:
	bool rva00580172();
};

class GameSpyInfoInterface
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual bool SlotB8();
};

extern GameSpyInfoInterface *TheGameSpyInfo;

struct Rva005A0D61
{
	char pad[0x450];
	Rva00580172 m_450;
	char pad2[0x4AC - 0x450 - 4];
	int m_4AC;

	void rva005A061B();
	void Run(int flag);
};

void Rva005A0D61::Run(int flag)
{
	if (((unsigned char *)&flag)[0] != 0)
		goto tail;
	{
		int *slot = &m_4AC;
		if (*slot != 0) {
			unsigned long t = timeGetTime();
			if ((unsigned long)(*slot + 0x3e8) <= t)
				goto tail;
			if (m_450.rva00580172())
				goto tail;
			if (!TheGameSpyInfo->SlotB8())
				return;
		}
	}
tail:
	rva005A061B();
	{
		unsigned long t = timeGetTime();
		m_4AC = (int)t;
	}
}

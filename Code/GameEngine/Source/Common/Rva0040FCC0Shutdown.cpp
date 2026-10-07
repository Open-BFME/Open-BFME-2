// cl: /MD /O1 /arch:SSE /G7
// ?rva0040FCC0@Rva0040FCC0@@QAEXH@Z @0x0040FCC0 92B: GUI shutdown path with focus pop.
// Evidence: ref lane slot neighbours QuickMatchScreenBase/WindowLayout, callees PopFocus 0x00222A33 row AptPlayer, rva0022277D pin Rva00222A8BTarget, shutdownComplete 0x0035C445 row Shell; globals g_bfmeAptWindowManager 0x009FE4CC, TheShell 0x00A01E48; +0x24/+0x28 like prev Rva0040FC79Host, +0x274 owner, vtable +0x10/+0x34. VTABLE Locomotor slot disagrees (Locomotor never touches Apt/Shell), so honest Rva name.
class AptFocusTarget;
class AptPlayer
{
public:
	void PopFocus(AptFocusTarget *t);
};
class Rva00222A8BTarget
{
public:
	// Native provider compares the incoming 32-bit index with 14 and returns AL.
	bool rva0022277D(int index);
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
#define TheAptMgr0040FCC0 (*(AptPlayer **)&g_bfmeAptWindowManager)
#define TheRvaTgt0040FCC0 (*(Rva00222A8BTarget **)&g_bfmeAptWindowManager)

class WindowLayout;
class Shell
{
public:
	void shutdownComplete(WindowLayout *layout, bool b);
};
extern Shell *TheShell;

class Rva0040FCC0Tail
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();

public:
	char m_pad04[0x274 - 0x04];
	AptFocusTarget *m_274; // +0x274
};

class Rva0040FCC0
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04(int v);
	void rva0040FCC0(int dummy);

private:
	char m_pad04[0x24 - 0x04];
	Rva0040FCC0Tail *m_24; // +0x24
	unsigned char m_28; // +0x28
};

void Rva0040FCC0::rva0040FCC0(int /*dummy*/)
{
	if (m_24 == 0)
		return;
	if (m_28 == 0)
		goto shutdown;
	v04(1);
	m_24->v13();
	TheAptMgr0040FCC0->PopFocus(m_24->m_274);
	TheRvaTgt0040FCC0->rva0022277D(reinterpret_cast<int>(m_24->m_274));
	m_28 = 0;
shutdown:
	TheShell->shutdownComplete((WindowLayout *)this, false);
}

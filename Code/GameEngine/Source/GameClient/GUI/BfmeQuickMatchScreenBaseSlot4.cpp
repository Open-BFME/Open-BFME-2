// cl: /O1 /DNDEBUG /MD /EHsc

// ?rva00538AB0@BfmeQuickMatchScreenBase@@UAEX_N@Z, retail 0x00538AB0, 44 bytes.
// Slot 4 (offset 0x10) of vtable 0x00839608 installed by the rowed ctor
// 0x00470620. Head pointer at +0x08 walked via rowed winHide 0x00313C64 plus
// rowed disp getter 0x0052A28E (next at +0x208) then bool arg stored at +0x14.
// Layout from BfmeQuickMatchScreenBaseConstructor.cpp (slot at +0x04 plus
// head at +0x08 plus flag at +0x14). No donor; honest address name.

class GameWindow
{
public:
	int winHide(bool hide);
};

class Rva0052A28EDwordField
{
public:
	int get() const;
};

class BfmeQuickMatchScreenBase
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void rva00538AB0(bool flag);
	virtual void slot5();
	virtual void add(void *payload);

private:
	void *m_04;
	GameWindow *m_head;
	int m_0C;
	int m_10;
	bool m_14;
	char m_pad15[3];
	int m_18;
	int m_1C;
	int m_20;
};

void BfmeQuickMatchScreenBase::rva00538AB0(bool flag)
{
	GameWindow *window = m_head;
	while (window != 0)
	{
		window->winHide(flag);
		window = (GameWindow *)((Rva0052A28EDwordField *)window)->get();
	}
	m_14 = flag;
}

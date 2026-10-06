// cl: /DNDEBUG /MD
// ?rva0057E97A@Rva0057E97A@@QAEXXZ @0x0057E97A 115B
// Toggles a window list: reads holder at +0x58 via rowed 0x0043DA65 (row types
// int but retail uses the return as an object pointer for slot-0x30 bool check;
// cast is required to keep the row mangling), then enables each GameWindow in
// [0x7C,0x80) with (flag && intAtB4[i]==1) via rowed GameWindow::winEnable.
// Evidence: packet disasm with rowed callees 0x0043DA65 and 0x00313BEC;
// callers 0x0057EA0F/0x0057ED2B of the same class; neighbours in Common.
class Rva0043DA65
{
public:
	int rva0043DA65();
};

class GameWindow
{
public:
	int winEnable(bool enable);
};

class Rva0057E97AValidator
{
public:
	virtual void pad0() = 0;
	virtual void pad1() = 0;
	virtual void pad2() = 0;
	virtual void pad3() = 0;
	virtual void pad4() = 0;
	virtual void pad5() = 0;
	virtual void pad6() = 0;
	virtual void pad7() = 0;
	virtual void pad8() = 0;
	virtual void pad9() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual bool checkValid() = 0;
};

class Rva0057E97A
{
public:
	void rva0057E97A();
private:
	char m_pad0[0x58];
	Rva0043DA65 *m_holder;
	char m_pad5C[0x20];
	GameWindow **m_begin;
	GameWindow **m_end;
	char m_pad84[4];
	bool m_updating;
	char m_pad89[0x2B];
	int *m_enableFlags;
};

void Rva0057E97A::rva0057E97A()
{
	int tmp = m_holder->rva0043DA65();
	bool use;
	if (tmp != 0 && ((Rva0057E97AValidator *)tmp)->checkValid())
		use = true;
	else
		use = false;
	GameWindow **begin = m_begin;
	m_updating = false;
	if (begin != m_end)
	{
		unsigned int off = 0;
		do
		{
			GameWindow *w = *begin;
			if (w != 0)
				w->winEnable(use && m_enableFlags[off] == 1);
			++begin;
			++off;
		} while (begin != m_end);
	}
	m_updating = true;
}

// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0056D915@@UAE@XZ @0x0056D915 110B evidence: deleting dtor 0x0056DC2A vtable 0x00C6DB40#0; rowed base 0x005126F5 member 0x005C9B9C callee 0x002BED10; global g_00DFEF18; callers prove start
#include "ascii_string.h"

class GameWindow
{
public:
	GameWindow();
protected:
	virtual ~GameWindow();
private:
	unsigned char unknown[0x218 - 4];
};

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	unsigned char unknown[0x58 - 4];
};

class _bfme_AptGameWindow : public GameWindow, public Rva005248D0
{
public:
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString filename270;
};

class Rva005C9B76
{
public:
	virtual ~Rva005C9B76();
private:
	char m_pad[0x1C - 4];
};

class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

class HostView
{
public:
	virtual void w00();
	virtual void w01();
	virtual void w02();
	virtual void w03();
	virtual void w04();
	virtual void w05();
	virtual void w06();
	virtual void w07();
	virtual void w08();
	virtual void w09();
	virtual void slot10(int v);
	char m_pad[0x14];
	unsigned char m_18;
	unsigned char m_19;
};

class Rva002BED10
{
public:
	void rva002BED10();
};

class Rva0056D915 : public _bfme_AptGameWindow
{
public:
	virtual ~Rva0056D915();
private:
	char m_pad274[8];
	Rva005C9B76 m_member27C;
};

Rva0056D915::~Rva0056D915()
{
	unsigned char flag = ((HostView *)g_00DFEF18)->m_19;
	if (flag)
	{
		((Rva002BED10 *)g_00DFEF18)->rva002BED10();
		((HostView *)g_00DFEF18)->slot10(0);
	}
}

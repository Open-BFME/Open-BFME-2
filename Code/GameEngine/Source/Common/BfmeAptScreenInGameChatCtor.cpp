// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /arch:SSE /G7
//
// ??0BfmeAptScreenInGameChat@@QAE@PAX@Z @0x0056DB9B 143B.
// Ctor via rowed _bfme_AptGameWindow base, vtable 0x00C6DB40 with second base
// vtable 0x00C6DB3C at +0x218, member Rva005C9B76 at +0x27c via rowed ctor,
// zeroes +0x29c/+0x2a0, rowed rva002BED10 plus virtual slots 0x50 and 0x28
// on g_00DFEF18, then pinned SelectCampaign(0). Caller 0x00410284 factory.
// LINK BONUS via 0x005E19CA.
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
	_bfme_AptGameWindow(void *context);
	virtual ~_bfme_AptGameWindow();
private:
	AsciiString filename270;
};

class Rva005C9B76
{
public:
	Rva005C9B76(void *context);
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
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
	virtual void w17();
	virtual void w18();
	virtual void w19();
	virtual void slot20(int v);
	char m_pad[0x14];
	unsigned char m_18;
	unsigned char m_19;
};

class Rva002BED10
{
public:
	void rva002BED10();
};

class AptLivingWorldWindow
{
public:
	void SelectCampaign(int v);
};

class BfmeAptScreenInGameChat : public _bfme_AptGameWindow
{
public:
	BfmeAptScreenInGameChat(void *context);
	virtual ~BfmeAptScreenInGameChat();
private:
	char m_pad274[8];
	Rva005C9B76 m_member27C;
	char m_pad298[0x29C - 0x298];
	int m_29C;
	unsigned char m_2A0;
};

BfmeAptScreenInGameChat::BfmeAptScreenInGameChat(void *context)
	: _bfme_AptGameWindow(context)
	, m_member27C(g_00DFEF18)
	, m_29C(0)
	, m_2A0(0)
{
	((Rva002BED10 *)g_00DFEF18)->rva002BED10();
	((HostView *)g_00DFEF18)->slot20(1);
	((HostView *)g_00DFEF18)->slot10(1);
	((AptLivingWorldWindow *)this)->SelectCampaign(0);
}

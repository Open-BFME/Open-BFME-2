// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ??1AptOnlineLogin@@UAE@XZ @0x0056E79E 171B
// AptOnlineLogin's destructor: WorldBuilder names it (AptOnlineLogin.cpp:215
// s_instance assert) and retail closes the screen through the same
// "AptOnlineLogin::InitGadgets" literal.
// Dtor with AptOnlineLogin::InitGadgets close plus WindowManager/IMEManager plus GameSpy at +0x60 plus AsciiString at +0xd8 plus base 0x005248D0.
// Evidence: vtable stores 0x0086DBBC/0x0086DB78; g_Va00E062EC guard; string literal; _bfme_closeAptScreen pin; TheWindowManager+0xb4 TheIMEManager+0x40; releaseBuffer at +0xd8; GameSpy dtor; base dtor pin.
// Second store 0x0086DB78 is Rva0056DC6B middle (rowed trivial dtor at 0x0056DC6B store+jmp base); inlined here.
#include "ascii_string.h"

class Rva005248D0
{
public:
	virtual ~Rva005248D0();
private:
	char m_pad[0x5C];
};

class Rva0056DC6B : public Rva005248D0
{
public:
	virtual ~Rva0056DC6B();
};

inline Rva0056DC6B::~Rva0056DC6B()
{
}

#include "../../Include/GameClient/GameSpyLoginPreferences.h"

#include "../../Include/GameClient/GameWindowManager.h"

class IMEManager
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
	virtual void w10();
	virtual void w11();
	virtual void w12();
	virtual void w13();
	virtual void w14();
	virtual void w15();
	virtual void w16();
};

class BfmeObjELB; extern BfmeObjELB *g_bfmeObjELB;
extern GameWindowManager *TheWindowManager;
extern IMEManager *TheIMEManager;

void __cdecl _bfme_closeAptScreen(const AsciiString &s);

class AptOnlineLogin : public Rva0056DC6B
{
public:
	virtual ~AptOnlineLogin();
private:
	GameSpyLoginPreferences m_login; // +0x60, 0x44 bytes
	char m_padA4[0xD8 - 0xA4];
	AsciiString m_name; // +0xD8
};

AptOnlineLogin::~AptOnlineLogin()
{
	if ((*(int *)&g_bfmeObjELB) == (int)this)
	{
		{
			AsciiString tmp("AptOnlineLogin::InitGadgets");
			_bfme_closeAptScreen(tmp);
		}
		if (TheWindowManager != 0)
			TheWindowManager->clearTabList();
		TheIMEManager->w16();
		(*(int *)&g_bfmeObjELB) = 0;
	}
}

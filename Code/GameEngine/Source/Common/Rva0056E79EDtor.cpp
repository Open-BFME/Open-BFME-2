// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva0056E79E@@UAE@XZ @0x0056E79E 171B
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

class GameSpyLoginPreferences
{
public:
	virtual ~GameSpyLoginPreferences();
private:
	char m_pad[0x74];
};

class GameWindowManager
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
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
	virtual void v24();
	virtual void v25();
	virtual void v26();
	virtual void v27();
	virtual void v28();
	virtual void v29();
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void v40();
	virtual void v41();
	virtual void v42();
	virtual void v43();
	virtual void v44();
	virtual void v45();
};

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

extern int g_Va00E062EC;
extern GameWindowManager *TheWindowManager;
extern IMEManager *TheIMEManager;

void __cdecl _bfme_closeAptScreen(const AsciiString &s);

class Rva0056E79E : public Rva0056DC6B
{
public:
	virtual ~Rva0056E79E();
private:
	GameSpyLoginPreferences m_login;
	AsciiString m_name;
};

Rva0056E79E::~Rva0056E79E()
{
	if (g_Va00E062EC == (int)this)
	{
		{
			AsciiString tmp("AptOnlineLogin::InitGadgets");
			_bfme_closeAptScreen(tmp);
		}
		if (TheWindowManager != 0)
			TheWindowManager->v45();
		TheIMEManager->w16();
		g_Va00E062EC = 0;
	}
}

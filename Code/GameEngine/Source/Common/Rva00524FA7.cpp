// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
// ?rva00524FA7@Rva00524FA7@@QAEXXZ @0x00524FA7 (70B): combine InGameUI +0x988 scaled
// by g_00DBA500 with TheGameClient slot31 into +0x1DC. Evidence: single caller
// 0x005270EB, TheInGameUI/TheGameClient globals, unsigned x87 fild/fadd/fmul/ftol2
// via g_00BC26EC/g_00DBA500, slot 0x7C, neighbours Disp0DwordImmSetters/Rva00524FEDCheck.
// Honest Rva owner; /O1 like next sibling.
class InGameUI
{
public:
	char m_pad[0x988];
	unsigned m_val;
};

class ClientFrameSubsystem
{
public:
	virtual void c0();
	virtual void c1();
	virtual void c2();
	virtual void c3();
	virtual void c4();
	virtual void c5();
	virtual void c6();
	virtual void c7();
	virtual void c8();
	virtual void c9();
	virtual void c10();
	virtual void c11();
	virtual void c12();
	virtual void c13();
	virtual void c14();
	virtual void c15();
	virtual void c16();
	virtual void c17();
	virtual void c18();
	virtual void c19();
	virtual void c20();
	virtual void c21();
	virtual void c22();
	virtual void c23();
	virtual void c24();
	virtual void c25();
	virtual void c26();
	virtual void c27();
	virtual void c28();
	virtual void c29();
	virtual void c30();
	virtual int slot31();
};

class Rva00524FA7
{
public:
	void rva00524FA7();

private:
	char m_pad[0x1DC];
	int m_1dc;
};

extern InGameUI *TheInGameUI;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;
extern float g_00BC26EC;
extern float g_00DBA500;
// g_00DBA500: matched references place it at VA 0xdba500 (retail .data initial value 0.03f).
float g_00DBA500 = 0.03f;

void Rva00524FA7::rva00524FA7()
{
	unsigned v = TheInGameUI->m_val;
	int t = (int)((float)v * g_00DBA500);
	int u = ((ClientFrameSubsystem *)TheGameClient)->slot31();
	m_1dc = u + t;
}

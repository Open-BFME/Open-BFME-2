// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?bfmeShowDisconnectScreen@@YAXXZ @0x00512DE1 104B: show DisconnectScreen.apt unless up.
// Target evidence: g_Va00A048CC jne ret then (int)AptStrategicMessageBox::s_instance int-as-receiver method 0x0054CBEF then Rva004E400DEnable Rva004E855CClose Rva0051B11CEnable then TheInGameUI slot 0x178 with 1 then TheWindowManager slot 0x80 with DisconnectScreen.apt then slot 0 with 0; caller turnOnScreen 0x004D4179.
#include "ascii_string.h"

class Rva0054CBEFTarget
{
public:
	void method(int arg);
};
class AptStrategicMessageBox {private: static AptStrategicMessageBox *s_instance; friend void __cdecl bfmeShowDisconnectScreen(void);};

void Rva004E400DEnable();
void Rva004E855CClose();
void Rva0051B11CEnable();

class Rva00512C88ObjA
{
public:
	virtual void v0(int);
	virtual void *v1(int);
	virtual void v2(int);
	virtual void v3(int);
};
extern Rva00512C88ObjA *g_Va00A048CC;

class InGameUI
{
public:
#define V(n) virtual void pad##n() = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39)
	V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55)
	V(56) V(57) V(58) V(59) V(60) V(61) V(62) V(63)
	V(64) V(65) V(66) V(67) V(68) V(69) V(70) V(71)
	V(72) V(73) V(74) V(75) V(76) V(77) V(78) V(79)
	V(80) V(81) V(82) V(83) V(84) V(85) V(86) V(87)
	V(88) V(89) V(90) V(91) V(92) V(93)
#undef V
	virtual void v94(int value) = 0;
};
extern InGameUI *TheInGameUI;

class Rva005116C2Screen
{
public:
	virtual void v00(int value) = 0;
};
class GameWindowManager
{
public:
#define W(n) virtual void wpad##n() = 0;
	W(0) W(1) W(2) W(3) W(4) W(5) W(6) W(7)
	W(8) W(9) W(10) W(11) W(12) W(13) W(14) W(15)
	W(16) W(17) W(18) W(19) W(20) W(21) W(22) W(23)
	W(24) W(25) W(26) W(27) W(28) W(29) W(30) W(31)
#undef W
	virtual Rva005116C2Screen *v32(AsciiString filename) = 0;
};
extern GameWindowManager *TheWindowManager;

void __cdecl bfmeShowDisconnectScreen(void)
{
	if (g_Va00A048CC != 0)
		return;
	if ((int)AptStrategicMessageBox::s_instance != 0)
		((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(0);
	Rva004E400DEnable();
	Rva004E855CClose();
	Rva0051B11CEnable();
	TheInGameUI->v94(1);
	g_Va00A048CC = (Rva00512C88ObjA *)(void *)TheWindowManager->v32(AsciiString("DisconnectScreen.apt"));
	g_Va00A048CC->v0(0);
}

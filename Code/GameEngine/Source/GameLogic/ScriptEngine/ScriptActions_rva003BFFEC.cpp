// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?Rva003BFFECDo@@YGXABVAsciiString@@H@Z @0x003BFFEC 97B
// Display fullscreen plus trigger via Display virtual 0x114 check, rowed
// rva002B2466 0x002B2466 with 0 0 1 1, StringBase pin 0x000365F0 temp,
// Display virtual 0x108 with AsciiString plus 0x40 -1 -1.
// Evidence: TheDisplay 0x009FE9D8; caller 0x003CBBB6;
// precedent DisplayRva002B2466 fullscreen 0 0 1 1.
#include "ascii_string.h"

class Display
{
public:
	virtual void _00()=0; virtual void _01()=0; virtual void _02()=0; virtual void _03()=0;
	virtual void _04()=0; virtual void _05()=0; virtual void _06()=0; virtual void _07()=0;
	virtual void _08()=0; virtual void _09()=0; virtual void _10()=0; virtual void _11()=0;
	virtual void _12()=0; virtual void _13()=0; virtual void _14()=0; virtual void _15()=0;
	virtual void _16()=0; virtual void _17()=0; virtual void _18()=0; virtual void _19()=0;
	virtual void _20()=0; virtual void _21()=0; virtual void _22()=0; virtual void _23()=0;
	virtual void _24()=0; virtual void _25()=0; virtual void _26()=0; virtual void _27()=0;
	virtual void _28()=0; virtual void _29()=0; virtual void _30()=0; virtual void _31()=0;
	virtual void _32()=0; virtual void _33()=0; virtual void _34()=0; virtual void _35()=0;
	virtual void _36()=0; virtual void _37()=0; virtual void _38()=0; virtual void _39()=0;
	virtual void _40()=0; virtual void _41()=0; virtual void _42()=0; virtual void _43()=0;
	virtual void _44()=0; virtual void _45()=0; virtual void _46()=0; virtual void _47()=0;
	virtual void _48()=0; virtual void _49()=0; virtual void _50()=0; virtual void _51()=0;
	virtual void _52()=0; virtual void _53()=0; virtual void _54()=0; virtual void _55()=0;
	virtual void _56()=0; virtual void _57()=0; virtual void _58()=0; virtual void _59()=0;
	virtual void _60()=0; virtual void _61()=0; virtual void _62()=0; virtual void _63()=0;
	virtual void _64()=0; virtual void _65()=0;
	virtual void v108(AsciiString name, int a, int b, int c) = 0;
	virtual void _67()=0; virtual void _68()=0;
	virtual bool v114() = 0;
	void rva002B2466(float a, float b, float c, float d);
};

extern Display *TheDisplay;

void __stdcall Rva003BFFECDo(const AsciiString &name, int unused)
{
	(void)unused;
	if (TheDisplay->v114())
		return;
	TheDisplay->rva002B2466(0.0f, 0.0f, 1.0f, 1.0f);
	TheDisplay->v108((AsciiString &)name, 0x40, -1, -1);
}

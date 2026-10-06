// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva005830AE@Rva005830AE@@QAEXH@Z @0x005830AE 115B
// Free-standing progress tooltip updater: null-checked slot 0x40 on 0x9FEA28,
// empty-string Mouse tooltip via 0x37050/0x1EEA6D, then slots 0x5C 0x28 0x28 0x28 0x30.
// Evidence: callers 0x0044C629 0x0044C828 pass ecx+1 stack arg ret4; empty at 0xA0C898.

#include "unicode_string.h"


struct RGBColor { float red, green, blue; };

class Mouse {
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);
};

class Dummy24 {
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
	virtual void v16(int x);
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual void v22();
	virtual void v23();
};

extern Dummy24 *g_Va009FEA28;
extern Mouse *TheMouse;
extern Dummy24 *g_Va009FE710;
extern Dummy24 *g_Va009FEF1C;
extern Dummy24 *g_Va009FE4CC;
extern Dummy24 *g_Va009FE9D8;

class Rva005830AE {
public:
	void rva005830AE(int x);
};

void Rva005830AE::rva005830AE(int x)
{
	(void)x;
	if (g_Va009FEA28 != 0)
		g_Va009FEA28->v16(0);
	TheMouse->rva001EEA6D(UnicodeString::TheEmptyString, -1, 0, 1.0f);
	g_Va009FE710->v23();
	g_Va009FEF1C->v10();
	g_Va009FE4CC->v10();
	g_Va009FE9D8->v10();
	g_Va009FE9D8->v12();
}

// ?g_Va009FEA28@@3PAVDummy24@@A: the global at this VA is ?TheNetwork@@3PAVNetworkInterface@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va009FEA28@@3PAVDummy24@@A=?TheNetwork@@3PAVNetworkInterface@@A")
#pragma comment(linker, "/alternatename:?g_Rva0023D30FTarget@@3PAVRva0023D30FTarget@@A=?TheNetwork@@3PAVNetworkInterface@@A")
// ?g_Va009FE4CC@@3PAVDummy24@@A: the global at VA 0xdfe4cc is ?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE4CC@@3PAVDummy24@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
// ?g_Va009FE9D8@@3PAVDummy24@@A: the global at VA 0xdfe9d8 is ?TheDisplay@@3PAVDisplay@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE9D8@@3PAVDummy24@@A=?TheDisplay@@3PAVDisplay@@A")
// ?g_Va009FEF1C@@3PAVDummy24@@A: the global at VA 0xdfef1c is ?TheWindowManager@@3PAVGameWindowManager@@A.
#pragma comment(linker, "/alternatename:?g_Va009FEF1C@@3PAVDummy24@@A=?TheWindowManager@@3PAVGameWindowManager@@A")
// ?g_Va009FEA28@@3PAVDummy24@@A: the global at VA 0xdfea28 is ?TheNetwork@@3PAVNetworkInterface@@A.
#pragma comment(linker, "/alternatename:?g_Va009FEA28@@3PAVDummy24@@A=?TheNetwork@@3PAVNetworkInterface@@A")
// ?g_Va009FE710@@3PAVDummy24@@A: the global at VA 0xdfe710 is ?TheGameEngine@@3PAVGameEngine@@A.
#pragma comment(linker, "/alternatename:?g_Va009FE710@@3PAVDummy24@@A=?TheGameEngine@@3PAVGameEngine@@A")

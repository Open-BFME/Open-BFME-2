// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Sides-list setter gate at retail 0x00203C21 (89B).
// Decoded from retail bytes (all verified, no E8 calls):
// - App module at [0xDFE158]; SetTheSidesList via kernel32!GetProcAddress
//   import (IAT 0xBBA1F8, dllimport auto).
// - Calls the proc with 11 pushed globals/zeros (caller cleans 0x2C).
// Human-readable names; opaque free function (no this, no stack args).

extern class AudioManager *TheAudio;
extern class GlobalData *TheWritableGlobalData;

extern class GameLogic *TheGameLogic;
extern class NameKeyGenerator *TheNameKeyGenerator;
extern class ScriptEngine *TheScriptEngine;
extern class SidesList *TheSidesList;
extern class View *TheTacticalView;
extern class TerrainLogic *TheTerrainLogic;
extern class ThingFactory *TheThingFactory;

typedef int HMODULE;
extern HMODULE g_00DFE158;

extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *name);

#define TheAppModule g_00DFE158
#define Rva00DFE78C (*(void **)&TheGameLogic)
#define Rva00DFF000 (*(void **)&TheThingFactory)
#define Rva00DFEC50 (*(void **)&TheTerrainLogic)
#define Rva00DFEA3C (*(void **)&TheTacticalView)
#define Rva00DF36A4 (*(void **)&TheNameKeyGenerator)
#define Rva00DFE758 (*(void **)&TheWritableGlobalData)
#define Rva00DFE6E8 (*(void **)&TheAudio)
#define Rva00DFE16C (*(void **)&TheScriptEngine)
#define Rva00E01D58 (*(void **)&TheSidesList)

void rva00203C21()
{
	HMODULE app = TheAppModule;
	if (!app)
		return;

	typedef void (__cdecl *SetSidesProc)(
		void *a1, void *a2, void *a3, void *a4, void *a5, void *a6,
		void *a7, void *a8, void *a9, void *a10, void *a11);
	SetSidesProc proc = (SetSidesProc)GetProcAddress(app, "SetTheSidesList");
	if (!proc)
		return;

	proc(Rva00E01D58, Rva00DFE16C, Rva00DFE6E8, Rva00DFE758, Rva00DF36A4, 0, 0,
		Rva00DFEA3C, Rva00DFEC50, Rva00DFF000, Rva00DFE78C);
}

// ?Rva00203BE9@@YAXXZ @0x00203BE9 56B. Identity is address-derived: packet
// proves the calls, globals, and MessageStream vtable slot; the caller boundary
// is Ghidra's extra-function record. No donor identity is established.
class Rva002034E9Host
{
public:
	bool rva002034E9();
};

class GameLogic : public Rva002034E9Host
{
};

class MessageStream
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void appendType(int type);
};

extern class GameLogic *TheGameLogic;
extern MessageStream *MessageStreamSubsystem;
extern void *g_00E02D6C;

struct Rva00203BE9Mode
{
	char pad[0x2D];
	unsigned char enabled;
};

void rva00203BE9()
{
	if (TheGameLogic->rva002034E9())
	{
		if (((Rva00203BE9Mode *)g_00E02D6C)->enabled)
			MessageStreamSubsystem->appendType(0x7D9);
		else
			MessageStreamSubsystem->appendType(0x7ED);
	}
	else
		MessageStreamSubsystem->appendType(0x1D);
}

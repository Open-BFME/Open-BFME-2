// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ScriptEngine frame setter at retail 0x00204094 (83B).
// Decoded from retail bytes (all verified):
// - Calls rva00203C21 row (SetTheSidesList gate, 89B) then GetProcAddress
//   for SetFrameNumber (kernel32 import, IAT 0xBBA1F8 auto).
// - Calls rva001DCD1C mode gate row (GameLogic +0x110/+0x114, 32B) via
//   TheGameLogic; else virtual slot 0x7C on the object at [0xDFE77C].
// - App module at [0xDFE158]; latch-free early outs.
// Human-readable names; opaque free function (no this, standard ret).

class Rva002BA8F1Logic;
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
extern class ClientFrameSubsystem *TheGameClient;

typedef int HMODULE;
extern HMODULE g_00DFE158;

extern "C" __declspec(dllimport) void *__stdcall GetProcAddress(HMODULE module, const char *name);

class GameLogic
{
public:
	char m_pad00[0x40];
	int m_frameNumber;
	bool rva001DCD1C();
};
extern GameLogic *TheGameLogic;

class LivingWorldLogic
{
public:
	char m_pad00[0xFC];
	int m_frameNumber;
};

extern "C" HMODULE st_DebugDLL;

#define TheAppModule g_00DFE158

void rva00203C21();

class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual int slot1F();
};

#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)
#define TheRva00DFEF10 (*(void **)&(*(Rva002BA8F1Logic **)&TheLivingWorldLogic))

void rva00204094()
{
	if (!TheAppModule)
		return;
	rva00203C21();
	typedef void (__cdecl *SetFrameProc)(int value);
	SetFrameProc proc = (SetFrameProc)GetProcAddress(TheAppModule, "SetFrameNumber");
	if (!proc)
		return;
	int value;
	if (!TheGameLogic->rva001DCD1C())
		value = TheRva00DFE77C->slot1F();
	else
		value = *(int *)((char *)TheRva00DFEF10 + 0xFC);
	proc(value);
}

// ?Rva002040E7GetFrameNumber@@YAXXZ @0x002040E7 79B.
// Evidence: adjacent debug frame setter uses GetProcAddress("SetFrameNumber");
// target bytes select GameLogic::m_frameNumber or
// TheLivingWorldLogic::m_frameNumber after the rowed mode check.
void Rva002040E7GetFrameNumber()
{
	if (!st_DebugDLL)
		return;
	rva00203C21();
	typedef void (__cdecl *SetFrameProc)(int value);
	SetFrameProc proc = (SetFrameProc)GetProcAddress(st_DebugDLL, "SetFrameNumber");
	if (!proc)
		return;
	GameLogic *logic = TheGameLogic;
	int value;
	if (!logic->rva001DCD1C())
		value = logic->m_frameNumber;
	else
		value = TheLivingWorldLogic->m_frameNumber;
	proc(value);
}

// cl: /DNDEBUG /MD
//
// Two small stdcall free functions from the 0x003BD2xx ScriptEngine/GameLogic
// glue area (dump range 18).
//
// ?rva003BD270@@YGXHH@Z @0x003BD270 29B: forwards to the 0x002D36AE host
// method (pinned) on the 0x00DFF028 global with (a, g_00DBA4E8 * b). The
// callee null-guards its inner delegate and tail-jumps, so no return value
// is taken here; void is the honest reading.
//
// ?rva003BD2A6@@YGXH@Z @0x003BD2A6 40B: guarded GameLogic byte setter: when
// GameLogic+0x11C differs from the argument's low byte, calls the rowed
// 0x0023D68E GameLogic walker (pinned; ecx arrives as TheGameLogic, which the
// caller holds across the compare) and then stores the byte. Argument stays
// a full dword in ebx (no movzx), hence int rather than unsigned char.
extern int g_009BA4E8;

class Rva002D36AEHost
{
public:
	void rva002D36AE(int a, int b);
};

extern Rva002D36AEHost *g_00DFF028;

void __stdcall rva003BD270(int a, int b)
{
	g_00DFF028->rva002D36AE(a, g_009BA4E8 * b);
}

class GameLogic
{
public:
	void rva0023D68E(int value);
	char m_pad[0x11C];
	unsigned char m_field11C;
};

extern GameLogic *TheGameLogic;

void __stdcall rva003BD2A6(int value)
{
	if (TheGameLogic->m_field11C != (unsigned char)value) {
		TheGameLogic->rva0023D68E(value);
		TheGameLogic->m_field11C = (unsigned char)value;
	}
}

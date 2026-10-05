// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?rva00062B17@Rva00062B17@@QAEXXZ @0x00062B17 45B. Frameless thiscall init:
// push esi; mov esi,ecx; call 0x0000B3FD0; xorps xmm0,xmm0;
// and [esi+0x18],0; and [esi+0x1C],0; movss [esi+0x1918],xmm0;
// movss xmm0,[g_Va00BBB8D8]; movss [esi+0x191C],xmm0; pop esi; ret.
//
// Target facts (retail bytes, read via the tools): no prologue beyond the
// esi save, no vtable install, no stack frame; two int zeroings at
// +0x18/+0x1C via `and`, two float stores at +0x1918 (zero) and +0x191C
// (global 1.0f); single REL32 call to 0x0000B3FD0 with no preceding lea,
// so ecx already addresses the callee object: the callees host sits at +0.
// 0x0000B3FD0 is the image-wide shared empty ret (rowed Coord/Region dtors,
// EventModuleInfo dtor, BehaviorModule::loadPostProcess tail); the call is
// spelled here as an explicit Coord2D member-dtor call and the original
// callee identity is UNPROVEN. The 1.0f global is the ledger-owned
// g_Va00BBB8D8 (defined once in AudioManagerFocusVolume.cpp; extern here).
// Host name and init role are address-derived; the byte gate is the proof.
// No STL, no header edits, no fallbacks.

typedef int Int;
typedef bool Bool;

class Coord2D
{
public:
	~Coord2D();
	float x;
	float y;
};

extern float g_Va00BBB8D8;

// ?Rva00062B17::rva00062B17 present-unmatched
class Rva00062B17
{
public:
	void rva00062B17();

	Coord2D m_head; ///< +0x00 (explicitly destroyed; shared-empty callee)
	unsigned char m_pad08[0x18 - 0x08];
	Int m_18; ///< +0x18
	Int m_1C; ///< +0x1C
	unsigned char m_pad20[0x1918 - 0x20];
	float m_1918; ///< +0x1918
	float m_191C; ///< +0x191C
};

// ?Rva00062B17::rva00062B17 present-unmatched
void Rva00062B17::rva00062B17()
{
	m_head.~Coord2D();
	m_18 = 0;
	m_1C = 0;
	m_1918 = 0.0f;
	m_191C = g_Va00BBB8D8;
}

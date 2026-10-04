// cl: /O1 /MD /GX /arch:SSE
// AISPecialPower.cpp -- named by retail's own __FILE__ literal at 0x00C70938,
// pushed with line 94 into GetGameLogicRandomValueReal by the body below.
//
// ?rva0058ADD0@Rva0058ADD0@@QAE_NPAX_N1@Z @0x0058ADD0 78B
// A coin flip in front of virtual slot 6: when a game-logic random value in
// [0, 1] exceeds 0.5 (constant 0x00BC26F0), store the two flags at +0x19
// and +0x1A and return slot 6 (+0x18) applied to the first argument;
// otherwise false. Target facts: thiscall, three stack arguments (ret 0xC),
// sole caller 0x004B3314 passes a pointer and two bytes and tests AL.
// Retail compares with fcompi, which MSVC 7.1 emits only under /arch:SSE.
// The class and method names are unknown, hence address-derived.

#define AISPECIALPOWER_FILE "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\SkirmishAI\\AISpecialPowers\\AISPecialPower.cpp"

float GetGameLogicRandomValueReal(float low, float high, char *file, int line);

class Rva0058ADD0
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual bool slot06(void *target);

	bool rva0058ADD0(void *target, bool flag19, bool flag1A);

	char m_pad04[0x19 - 4];
	bool m_flag19;
	bool m_flag1A;
};

bool Rva0058ADD0::rva0058ADD0(void *target, bool flag19, bool flag1A)
{
	if (GetGameLogicRandomValueReal(0.0f, 1.0f, AISPECIALPOWER_FILE, 94) > 0.5f) {
		m_flag19 = flag19;
		m_flag1A = flag1A;
		return slot06(target);
	}
	return false;
}

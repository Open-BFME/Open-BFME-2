// ?bfmeCall939D@BfmeGlob939D@@QAEDXZ, retail 0x0023C6FD, 75 bytes.
// Multiplayer-gate predicate: true when in a multiplayer game, when the mode
// word is 2, or when the helper behind 0x00E02290 answers 1 at +0x1C with a
// state of 1, 2 or 5 at +0xE74. The isInMultiplayerGame call runs on our own
// GameLogic base (retail passes this straight through), so the class derives
// from a TU-local minimal GameLogic (pad plus mode at +0x110, rowed leaf).
// Shard TU: grafting into BfmeConv939_Go939D.cpp gets the body absorbed into
// rowed bfmeGo939D at /O2 (visible-def law holds only at /Od); the home TU
// keeps calling through its pin.

class GameLogic
{
	char m_pad[0x110];
public:
	int m_gameMode;
	bool isInMultiplayerGame();
};

class BfmeGlob939D : public GameLogic
{
public:
	char bfmeCall939D();
};

// Helper behind the 939D gate (global at 0x00E02290): a dword at +0x1C that
// must read 1, plus a state word at +0xE74 answering 1 for 1/2/5. The get
// call reuses the rowed disp8 body through a TU-local alias pin (same
// alias-pin precedent as the STL folds); the state offset is retail-measured.
struct Bfme939Helper
{
	int get() const;
	char m_lead[0x1C];
	int m_value;
	char m_pad[0xE54];
	int m_state;
};

extern Bfme939Helper *g_bfme939Helper;

char BfmeGlob939D::bfmeCall939D()
{
	if (isInMultiplayerGame())
		return 1;
	if (m_gameMode == 2)
		return 1;
	if (g_bfme939Helper != 0 && g_bfme939Helper->get() == 1)
	{
		int state = g_bfme939Helper->m_state;
		if (state == 2)
			return 1;
		if (state != 1 && state != 5)
			return 0;
		return 1;
	}
	return 0;
}

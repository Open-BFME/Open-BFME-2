// cl: /O1 /DNDEBUG /MD
// ControlBar::showPurchaseScience, retail 0x0031AD5A (53 bytes):
// ?showPurchaseScience@ControlBar@@QAEXXZ
// Identity (target): WorldBuilder's debug ControlBar.cpp
// ControlBar::showPurchaseScience tests the script engine field, gets the
// local player (PlayerList +0x10), asks Player::isPlayerActive (0x002AA231)
// and calls 0x0043CB48 after clearing the bar's +0x278 flag, as retail does
// (retail tail-jumps to the last call).
// Body (target): nothing while the script engine's +0x1A104 value is
// non-negative or there is no active local player; otherwise clear the
// +0x278 flag and open the science purchase screen through 0x0043CB48, a
// free function whose name is not recovered.
class Player
{
public:
	bool isPlayerActive() const;
};

class PlayerList
{
public:
	// Matched callers read the local player at +0x10 directly; do not emit
	// a shared getter from this partial target layout.
	unsigned char m_pad00[0x10];
	Player *m_local; // +0x10
};

extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	int getValue1A104() const { return m_value1A104; }

private:
	unsigned char m_pad00000[0x1A104];
	int m_value1A104; // +0x1A104
};

extern ScriptEngine *TheScriptEngine;

void rva0043CB48();

class ControlBar
{
public:
	void showPurchaseScience();

private:
	unsigned char m_pad000[0x278];
	bool m_flag278; // +0x278
};

void ControlBar::showPurchaseScience()
{
	if (TheScriptEngine->getValue1A104() >= 0)
		return;
	Player *player = ThePlayerList->m_local;
	if (!player || !player->isPlayerActive())
		return;
	m_flag278 = false;
	rva0043CB48();
}

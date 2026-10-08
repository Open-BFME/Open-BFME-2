// cl: /DNDEBUG /MD
//
// ?rva0023CD9E@GameLogic@@QAEX_NH0@Z @0x0023CD9E 327B
// BFME2 GameLogic 3-arg pause setter, evolution of BFME1
// BfmeGameLogicPause::setGamePaused (reference/open-bfme-1/game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/BfmeGameLogicPause_setGamePaused.cpp).
// Evidence: this+0x124 matches rowed ?isGamePaused@GameLogic@@QAEEXZ prev row;
// TheGameLogic 0x00DFE78C plus rowed ?isInMultiplayerGame@GameLogic@@QAE_NXZ;
// InGameUI 0x00DFEDF0 bytes +0x15/+0x16 plus rowed ?setEngineInputEnabled@InGameUI@@QAEX_N@Z;
// Mouse 0x00DFDCA0 plus rowed ?rva001EDE26@Mouse@@QBE_NXZ and ?_bfme_setEngineVisibility@Mouse@@QAEX_N@Z plus vtable slot 0x4C setCursor(2);
// Audio 0x00DFE6E8 pause slot 0x40 resume slot 0x44 with audToAffect (mode!=1)+0x1E|0x20.

extern class AudioManager *TheAudio;

class GameLogic
{
public:
	bool isInMultiplayerGame();
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);
	bool rva0023CEE5();
	void rva0023CF3F();
	void rva0023D0E3(bool selfDestruct);

private:
	char m_pad[0x110];
	int m_gameMode; // +0x110
	char m_pad114[0x124 - 0x114];
	bool m_gamePaused; // +0x124
	char m_pad125; // +0x125
	bool m_inputEnabledMemory; // +0x126
	bool m_mouseVisibleMemory; // +0x127
	unsigned char m_128[8]; // +0x128
	int m_timeout[8]; // +0x130, eight target-checked timer values
	bool m_150; // +0x150
};
extern GameLogic *TheGameLogic;
extern "C" __declspec(dllimport) unsigned int __stdcall timeGetTime(void);

class NetworkInterface;
extern NetworkInterface *TheNetwork;

class Rva00210C66CmpBoolField
{
public:
	bool get() const;
};

class InGameUI
{
public:
	void setEngineInputEnabled(bool enabled);

	char m_pad[0x15];
	bool m_inputEnabled; // +0x15
	bool m_inputAllowed; // +0x16
	char m_pad017[0x8C5 - 0x17];
	bool m_clientQuiet; // +0x8C5
};
extern InGameUI *TheInGameUI;

class Mouse
{
public:
	virtual void s00();
	virtual void s04();
	virtual void s08();
	virtual void s0c();
	virtual void s10();
	virtual void s14();
	virtual void s18();
	virtual void s1c();
	virtual void s20();
	virtual void s24();
	virtual void s28();
	virtual void s2c();
	virtual void s30();
	virtual void s34();
	virtual void s38();
	virtual void s3c();
	virtual void s40();
	virtual void s44();
	virtual void s48();
	virtual void setCursor(int cursor);
	bool rva001EDE26() const;
	void _bfme_setEngineVisibility(bool visible);
};
extern Mouse *TheMouse;

class BfmeAudio
{
public:
	virtual void a00();
	virtual void a04();
	virtual void a08();
	virtual void a0c();
	virtual void a10();
	virtual void a14();
	virtual void a18();
	virtual void a1c();
	virtual void a20();
	virtual void a24();
	virtual void a28();
	virtual void a2c();
	virtual void a30();
	virtual void a34();
	virtual void a38();
	virtual void a3c();
	virtual void pauseAudio(unsigned int which, int a, int b);
	virtual void resumeAudio(unsigned int which, int a, int b);
};

#define TheAudio (*(BfmeAudio **)&TheAudio)

void GameLogic::rva0023CD9E(bool paused, int pauseMode, bool affectMouse)
{
	if (paused == m_gamePaused)
		return;
	GameLogic *gameLogic = TheGameLogic;
	if (gameLogic->isInMultiplayerGame())
		return;
	if (((Rva00210C66CmpBoolField *)gameLogic)->get())
		return;

	int audToAffect = (pauseMode != 1);
	m_gamePaused = paused;
	audToAffect += 0x1E;
	audToAffect |= 0x20;

	if (paused)
	{
		m_inputEnabledMemory = TheInGameUI->m_inputEnabled && TheInGameUI->m_inputAllowed;
		m_mouseVisibleMemory = TheMouse->rva001EDE26();
		if (affectMouse)
		{
			TheMouse->_bfme_setEngineVisibility(true);
			TheMouse->setCursor(2);
		}
		if (m_inputEnabledMemory)
			TheInGameUI->setEngineInputEnabled(false);
		if (pauseMode != 2)
		{
			TheAudio->pauseAudio(audToAffect, 3, 0);
			TheAudio->pauseAudio(audToAffect, 4, 1);
		}
	}
	else
	{
		if (affectMouse)
			TheMouse->_bfme_setEngineVisibility(m_mouseVisibleMemory);
		if (m_inputEnabledMemory)
			TheInGameUI->setEngineInputEnabled(true);
		if (pauseMode != 2)
		{
			TheAudio->resumeAudio(audToAffect, 3, 0);
			TheAudio->resumeAudio(audToAffect, 4, 1);
		}
	}
}

bool GameLogic::rva0023CEE5()
{
	if (!isInMultiplayerGame())
		return true;
	if (TheNetwork == 0)
		return true;
	if (m_150)
		return true;
	for (int i = 0; i < 8; i++)
	{
		if (m_128[i] == 0)
			return false;
	}
	return true;
}

// Target 0x0023CF3F checks the eight timer values paired with +0x128 flags
// before setting +0x150. The matched neighboring GameLogic gate supplies the
// shared layout; the operation's name and higher-level purpose remain unknown.
void GameLogic::rva0023CF3F()
{
	if (rva0023CEE5())
		return;

	int now = (int)timeGetTime();
	for (int i = 0; i < 8; ++i)
	{
		if (m_128[i] == 0 && m_timeout[i] + 0x15F90 > now)
			return;
	}
	m_150 = true;
}

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
	void appendBooleanArgument(bool arg);
};

// MessageStreamSubsystem (0x00A00950); appendMessage is vslot 18.
class MessageStream
{
public:
	virtual void m00();
	virtual void m01();
	virtual void m02();
	virtual void m03();
	virtual void m04();
	virtual void m05();
	virtual void m06();
	virtual void m07();
	virtual void m08();
	virtual void m09();
	virtual void m10();
	virtual void m11();
	virtual void m12();
	virtual void m13();
	virtual void m14();
	virtual void m15();
	virtual void m16();
	virtual void m17();
	virtual GameMessage *appendMessage(int type);
};
extern MessageStream *TheMessageStream;

// TheGameInfo (0x00A02EEC); vslot 20 is Zero Hour's isSandbox.
class GameInfo
{
public:
	virtual void g00();
	virtual void g01();
	virtual void g02();
	virtual void g03();
	virtual void g04();
	virtual void g05();
	virtual void g06();
	virtual void g07();
	virtual void g08();
	virtual void g09();
	virtual void g10();
	virtual void g11();
	virtual void g12();
	virtual void g13();
	virtual void g14();
	virtual void g15();
	virtual void g16();
	virtual void g17();
	virtual void g18();
	virtual void g19();
	virtual bool isSandbox();
};
extern GameInfo *TheGameInfo;

// TheTerrainVisual (0x009FDC8C) and its rowed 0x001EB0B1.
class Rva001EB0B1Holder
{
public:
	void rva001EB0B1();
};
class TerrainVisual;
extern TerrainVisual *TheTerrainVisual;	// defined in GameClient.cpp

// The living-world host (0x009FEF18): a war of the ring game.
class Rva002D3627Host;
extern Rva002D3627Host *g_00DFEF18;

// Target 0x0023D0E3: Zero Hour QuitMenu.cpp's exitQuitMenu tail moved
// onto GameLogic, as the quit menu's destructor (0x0051B15E) and restart
// path call it on TheGameLogic. A self-destruct request (0x448) in a
// multiplayer non-skirmish non-sandbox game, then the 0x001EB0B1 reset,
// MSG_CLEAR_GAME_DATA (0x1D, argument 2 in a war of the ring game), the
// unpause outside multiplayer and InGameUI's client-quiet byte. Name
// unknown; the bool's purpose is inferred from the guarded message.
void GameLogic::rva0023D0E3(bool selfDestruct)
{
	if (selfDestruct && isInMultiplayerGame() && m_gameMode != 2 && TheGameInfo && !TheGameInfo->isSandbox())
	{
		GameMessage *msg = TheMessageStream->appendMessage(0x448);
		msg->appendBooleanArgument(true);
	}
	((Rva001EB0B1Holder *)TheTerrainVisual)->rva001EB0B1();
	GameMessage *msg = TheMessageStream->appendMessage(0x1D);
	if (g_00DFEF18)
		msg->appendIntegerArgument(2);
	if (!isInMultiplayerGame())
		rva0023CD9E(false, 0, true);
	TheInGameUI->m_clientQuiet = true;
}

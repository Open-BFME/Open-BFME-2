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

private:
	char m_pad[0x124];
	bool m_gamePaused; // +0x124
	char m_pad125; // +0x125
	bool m_inputEnabledMemory; // +0x126
	bool m_mouseVisibleMemory; // +0x127
	unsigned char m_128[8]; // +0x128
	char m_pad130[0x150 - 0x130]; // +0x130 timeouts
	bool m_150; // +0x150
};
extern GameLogic *TheGameLogic;

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

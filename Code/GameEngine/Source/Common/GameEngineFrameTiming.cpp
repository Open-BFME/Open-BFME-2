// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Ireference/shims/bfme2_ascii
// platformsdk
//
// The GameEngine stores the client-frame period at +0x34, the derived
// client-frame counter at +0x38, and the interpolation ratio at +0x3c.  These timing
// helpers are the small pieces used by the main frame loop around the
// network/logic update path.

extern int BfmeClientFramesPerSecond;
extern int BfmeLogicFramesPerSecond;

extern const double g_bfmeMillisecondsToSeconds;

class Host10
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10();
};
// The nativeA099F8 registry pointer has one existing owner in W3DDisplayDtor.
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;

#include "../../Include/GameLogic/ScriptEngine.h"
extern ScriptEngine *TheScriptEngine;

class Rva00203B08
{
public:
	bool rva00203B08();
};

class ClientFrameSubsystem
{
public:
	char m_pad00[0xC8];
	unsigned char m_c8;
};
class GameClient;
extern GameClient *TheGameClient;

class Debug
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
	virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
	virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
	virtual void d36(); virtual void d37();
};
extern Debug *theDebug;

#include <windows.h>
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

void __cdecl Rva00225A0C(int v);

#define FramesPerSecond BfmeClientFramesPerSecond
#define LogicFramesPerSecond BfmeLogicFramesPerSecond

class GameEngine
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void update(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(int v); virtual void s39();

private:
	void _bfme_updateClientFrameCounter(void);
	void _bfme_updateClientFrameRatio(void);
	char m_gap04[0x34 - 4];
	int m_clientFramePeriod;
	int m_clientFrameCounter;
	float m_clientFrameRatio;
	unsigned char m_40;
	char m_pad41[0x50 - 0x41];
	int m_50;
	unsigned int m_54;
	float m_58;
	int m_5c;
};

void GameEngine::_bfme_updateClientFrameCounter(void)
{
	m_clientFrameCounter = FramesPerSecond / LogicFramesPerSecond;
}

void GameEngine::_bfme_updateClientFrameRatio(void)
{
	float ratio = (float)m_clientFramePeriod / (float)m_clientFrameCounter;
	m_clientFrameRatio = ratio;
	if (ratio < 0.0f)
		ratio = 0.0f;
	else if (ratio > 1.0f)
		ratio = 1.0f;
	m_clientFrameRatio = ratio;
}

void GameEngine::update()
{
	((Host10 *)Rva0134FAA0)->s10();
	TheScriptEngine->_bfme_updateClientDebugFrame();
	bool flag = ((Rva00203B08 *)TheScriptEngine)->rva00203B08();
	s39();
	if (flag) {
		((ClientFrameSubsystem *)TheGameClient)->m_c8 = 0;
		theDebug->d37();
		return;
	}
	((ClientFrameSubsystem *)TheGameClient)->m_c8 = 1;
	int period = m_clientFramePeriod;
	if (period == 6 && m_40 != 0) {
		m_clientFrameCounter = BfmeClientFramesPerSecond / BfmeLogicFramesPerSecond;
		m_40 = 0;
	}
	int next = period + 1;
	m_clientFramePeriod = next;
	int logicFrame = (int)*(unsigned int *)((char *)TheGameLogic + 0x40);
	int scaled = logicFrame * 10 + next - 1;
	Rva00225A0C(scaled);
	_bfme_updateClientFrameRatio();
	int currentPeriod = m_clientFramePeriod;
	if (currentPeriod > 6) {
		if (m_50 % 25 == 0) {
			unsigned int t = timeGetTime();
			unsigned int dt = t - m_54;
			double elapsedSeconds = ((double)(float)dt * g_bfmeMillisecondsToSeconds);
			float den = (float)elapsedSeconds;
			float a = (float)m_50;
			m_50 = 0;
			float b = (float)m_5c;
			m_58 = (b / a) * (a / den);
			m_5c = 0;
			m_54 = timeGetTime();
		}
		m_5c += m_clientFrameCounter;
		int savedPeriod = m_clientFramePeriod;
		m_50++;
		m_clientFramePeriod = 1;
		_bfme_updateClientFrameRatio();
		s38(1);
		if (((ClientFrameSubsystem *)TheGameClient)->m_c8 != 0) {
			m_40 = 1;
		} else {
			m_clientFramePeriod = savedPeriod;
			_bfme_updateClientFrameRatio();
		}
	} else {
		s38(currentPeriod);
	}
	theDebug->d37();
}

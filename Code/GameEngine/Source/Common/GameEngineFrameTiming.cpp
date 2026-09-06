// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX /arch:SSE
//
// The GameEngine stores the client-frame counter at +0x34, the derived
// period at +0x38, and the interpolation ratio at +0x3c.  These timing
// helpers are the small pieces used by the main frame loop around the
// network/logic update path.

#define FramesPerSecond (*(const int *)0x00DBA4E8)
#define LogicFramesPerSecond (*(const int *)0x00DBA4E4)

class GameEngine
{
private:
	void _bfme_updateClientFramePeriod(void);
	void _bfme_updateClientFrameRatio(void);
	char m_gap04[0x34];
	int m_clientFrameCounter;
	int m_clientFramePeriod;
	float m_clientFrameRatio;
};

void GameEngine::_bfme_updateClientFramePeriod(void)
{
	m_clientFramePeriod = FramesPerSecond / LogicFramesPerSecond;
}

void GameEngine::_bfme_updateClientFrameRatio(void)
{
	float ratio = (float)m_clientFrameCounter / (float)m_clientFramePeriod;
	m_clientFrameRatio = ratio;
	if (ratio < 0.0f)
		ratio = 0.0f;
	else if (ratio > 1.0f)
		ratio = 1.0f;
	m_clientFrameRatio = ratio;
}

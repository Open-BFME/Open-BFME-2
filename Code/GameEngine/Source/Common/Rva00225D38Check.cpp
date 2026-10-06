// cl: /DNDEBUG /MD /EHsc
// ?rva00225D38@GameEngine@@AAE_NXZ @0x00225D38 48B frame-period check using
// FramesPerSecond at 0x00DBA4E8 and LogicFramesPerSecond at 0x00DBA4E4 plus
// member m_clientFramePeriod at +0x34. Evidence: same +0x34 and globals as
// GameEngineFrameTiming rows; ten callers use result as condition.

extern int g_009BA4E8;
extern int g_Va00DBA4E4;

#define FramesPerSecond g_009BA4E8
#define LogicFramesPerSecond g_Va00DBA4E4

class GameEngine
{
private:
	bool rva00225D38(void);

private:
	char m_pad00[0x34];
	int m_clientFramePeriod;
};

bool GameEngine::rva00225D38(void)
{
	int counter = FramesPerSecond / LogicFramesPerSecond;
	int six = 6;
	if (counter < six)
		return m_clientFramePeriod == six / counter;
	return m_clientFramePeriod == 1;
}

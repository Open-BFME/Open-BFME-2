// cl: /DNDEBUG /MD
// W3DDisplay.cpp's debug-display placeholder callbacks. Zero Hour has
// StatDebugDisplay(DebugDisplayInterface *, void *, FILE *) as a bare
// DEBUG_CRASH; BFME 2 writes the separator and the placeholder message to the
// file instead (IAT fprintf/fflush) and adds three siblings. Each function's
// name is the one its own message string spells.
//
// ?StatDebugDisplay@@YAXPAVDebugDisplayInterface@@PAXPAU_iobuf@@@Z       @0x00043D0F 45B
// ?SkirmishAIDebugDisplay@@YAXPAVDebugDisplayInterface@@PAXPAU_iobuf@@@Z @0x00043D3C 45B
// ?AnimDebugDisplay@@YAXPAVDebugDisplayInterface@@PAXPAU_iobuf@@@Z       @0x00043D69 45B
// ?NetworkDebugDisplay@@YAXPAVDebugDisplayInterface@@PAXPAU_iobuf@@@Z    @0x00043D96 45B

#include <stdio.h>

class DebugDisplayInterface
{
public:
    enum Color { WHITE, BLACK, YELLOW, RED, GREEN, BLUE, NUM_COLORS };
    virtual ~DebugDisplayInterface();
    virtual void printf(char *, ...);
    virtual void setCursorPos(int, int);
    virtual int getCursorXPos();
    virtual int getCursorYPos();
    virtual int getWidth();
    virtual int getHeight();
    virtual void setTextColor(Color);
    virtual void setRightMargin(int);
    virtual void setLeftMargin(int);
    virtual void reset();
};

void StatDebugDisplay(DebugDisplayInterface *, void *, FILE *fp)
{
	if (fp)
	{
		fprintf(fp, "----------------------------------------------------------------\n");
		fprintf(fp, "StatDebugDisplay should never be called directly, but is just a placeholder for drawDebugStats()");
		fflush(fp);
	}
}

void SkirmishAIDebugDisplay(DebugDisplayInterface *, void *, FILE *fp)
{
	if (fp)
	{
		fprintf(fp, "----------------------------------------------------------------\n");
		fprintf(fp, "SkirmishAIDebugDisplay should never be called directly, but is just a placeholder for drawSkirmishAIStats()");
		fflush(fp);
	}
}

void AnimDebugDisplay(DebugDisplayInterface *, void *, FILE *fp)
{
	if (fp)
	{
		fprintf(fp, "----------------------------------------------------------------\n");
		fprintf(fp, "AnimDebugDisplay(...) should never be called directly, but is just a placeholder for drawDebugStats()");
		fflush(fp);
	}
}

void NetworkDebugDisplay(DebugDisplayInterface *, void *, FILE *fp)
{
	if (fp)
	{
		fprintf(fp, "----------------------------------------------------------------\n");
		fprintf(fp, "NetworkDebugDisplay(...) should never be called directly, but is just a placeholder for drawDebugStats()");
		fflush(fp);
	}
}

// drawCurrentDebugDisplay: BFME 1 donor at 7dff0a4a9e937818d2731f9861ade1815663b9db
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDrawCurrentDebugDisplay.cpp,
// and Zero Hour W3DDisplay.cpp identify the callback dispatch and reset call.
// BFME 2 adds four named modes and clears GlobalData byte +0xBB4 in each path.
// Retail 0x4A3C4..0x4A462 proves receiver fields +0x2C/+0x30/+0x34 and
// DebugDisplayInterface::reset at virtual +0x28 (Zero Hour interface order).
// Native tail REL32 at 0x4A3F9 -> 0x4A1B8 and 0x4A42F -> 0x438CB;
// both callees consume ECX as their receiver and return with RET0. Their
// original method names remain unknown; keep address-derived declarations.
class GlobalData;
extern GlobalData *TheGlobalData;
typedef void DebugDisplayCallback(DebugDisplayInterface *, void *, FILE *);

class W3DDisplay
{
public:
    void rva0004387E();
    void rva000438CB();
    void rva00043BF9();
    void rva0004A1B8();
protected:
    void drawCurrentDebugDisplay();
private:
    char m_unmodelled[0x2c];
    DebugDisplayInterface *m_debugDisplay;
    DebugDisplayCallback *m_debugDisplayCallback;
    void *m_debugDisplayUserData;
};

void W3DDisplay::drawCurrentDebugDisplay()
{
    if (m_debugDisplayCallback == StatDebugDisplay)
    {
        reinterpret_cast<unsigned char *>(TheGlobalData)[0xbb4] = 0;
        rva0004387E();
        return;
    }
    if (m_debugDisplayCallback == SkirmishAIDebugDisplay)
    {
        reinterpret_cast<unsigned char *>(TheGlobalData)[0xbb4] = 0;
        rva0004A1B8();
        return;
    }
    if (m_debugDisplayCallback == AnimDebugDisplay)
    {
        reinterpret_cast<unsigned char *>(TheGlobalData)[0xbb4] = 0;
        rva00043BF9();
        return;
    }
    if (m_debugDisplayCallback == NetworkDebugDisplay)
    {
        reinterpret_cast<unsigned char *>(TheGlobalData)[0xbb4] = 0;
        rva000438CB();
        return;
    }
    if (m_debugDisplay && m_debugDisplayCallback)
    {
        reinterpret_cast<unsigned char *>(TheGlobalData)[0xbb4] = 0;
        m_debugDisplay->reset();
        m_debugDisplayCallback(m_debugDisplay, m_debugDisplayUserData, 0);
    }
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// GameEngine's vtable slot 39 (RVA 0x00225C12) is the client-side half of
// the frame loop.  Its ordering is useful for the later delay investigation:
// the client-frame admission test runs before the input, audio, and network
// update calls, while a skipped frame records the client frame number and
// returns without consuming those queues.

class GameLogic
{
public:
    void deleteLoadScreen(void);
};

class ClientSubsystem
{
public:
    virtual void slot00(void);
    virtual void slot01(void);
    virtual void slot02(void);
    virtual void slot03(void);
    virtual void slot04(void);
    virtual void slot05(void);
    virtual void slot06(void);
    virtual void slot07(void);
    virtual void slot08(void);
    virtual void slot09(void);
    virtual void update(void);
};

struct ClientSubsystemVtable
{
    void *m_slots00[10];
    void (__fastcall *update)(ClientSubsystem *subsystem);
};

class ClientFrameSubsystem
{
public:
    virtual void slot00(void);
    virtual void slot01(void);
    virtual void slot02(void);
    virtual void slot03(void);
    virtual void slot04(void);
    virtual void slot05(void);
    virtual void slot06(void);
    virtual void slot07(void);
    virtual void slot08(void);
    virtual void slot09(void);
    virtual void update(void);
    virtual void slot10(void);
    virtual void slot12(void);
    virtual void slot13(void);
    virtual void setFrame(int frame);
    virtual void slot15(void);
    virtual void slot16(void);
    virtual void slot17(void);
    virtual void slot18(void);
    virtual void slot19(void);
    virtual void slot20(void);
    virtual void slot21(void);
    virtual void slot22(void);
    virtual void slot23(void);
    virtual void slot24(void);
    virtual void slot25(void);
    virtual void slot26(void);
    virtual void slot27(void);
    virtual void slot28(void);
    virtual void slot29(void);
    virtual void slot30(void);
    virtual int getFrame(void);

    char m_gap04[0xc4];
    unsigned char m_advanceFrame;
};

class RadarSubsystem
{
public:
    char m_gap00[4];
    ClientSubsystem m_update;
};

class MessageStream
{
public:
    void propagateMessages(void);
};

class BFMEDesyncCheck
{
public:
    BFMEDesyncCheck(void);
    ~BFMEDesyncCheck(void) { writeReportIfMismatched(); }
    void writeReportIfMismatched(void);

private:
    void *m_context;
};

class NetworkInterface
{
public:
    virtual void slot00(void);
    virtual void slot01(void);
    virtual void slot02(void);
    virtual void slot03(void);
    virtual void slot04(void);
    virtual void slot05(void);
    virtual void slot06(void);
    virtual void slot07(void);
    virtual void slot08(void);
    virtual void slot09(void);
    virtual void slot10(void);
    virtual void slot11(void);
    virtual void slot12(void);
    virtual void slot13(void);
    virtual void slot14(void);
    virtual void liteupdate(int phase);
};

class GameEngine
{
public:
    virtual void _bfme_updateClientSubsystems(void);

private:
    bool _bfme_shouldSkipClientFrame(void);
};

extern GameLogic *TheGameLogic;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;
// TheGameClient (0x009FE77C) is GameClient.cpp's global; this unit reads it through its own view.
extern ClientSubsystem *WindowManagerSubsystem;
extern RadarSubsystem *Radar;
extern MessageStream *TheMessageStream;	// 0x00A00950, MessageStream.cpp's global
extern ClientSubsystem *InputLockSubsystem;
extern class InGameUI *TheInGameUI;
extern class Mouse *TheMouse;
extern ClientSubsystem *AudioSubsystem;
extern NetworkInterface *TheNetwork;
// TheNetwork: matched references place it at VA 0xdfea28 (zero-filled .bss).
NetworkInterface * TheNetwork;
extern int SkippedClientFrames;
// SkippedClientFrames: matched references place it at VA 0xdfe6f0 (zero-filled .bss).
int SkippedClientFrames;
extern int SavedClientFrame;
// SavedClientFrame: matched references place it at VA 0xdfe6f4 (zero-filled .bss).
int SavedClientFrame;
extern int TimedOpInputLocked;
// TimedOpInputLocked: matched references place it at VA 0xdfe71c (zero-filled .bss).
int TimedOpInputLocked;

class InGameUI
{
public:
    void setEngineInputEnabled(bool enabled);
};

class Mouse
{
public:
    void _bfme_setEngineVisibility(bool visible);
};

unsigned int _bfme_updateTimedOps(void);

void GameEngine::_bfme_updateClientSubsystems(void)
{
    TheGameLogic->deleteLoadScreen();

    unsigned char advanceFrame = ((ClientFrameSubsystem *)TheGameClient)->m_advanceFrame;
    if (advanceFrame != 0)
    {
        ((ClientFrameSubsystem *)TheGameClient)->setFrame(((ClientFrameSubsystem *)TheGameClient)->getFrame() + 1);
    }

    WindowManagerSubsystem->update();
    if (_bfme_shouldSkipClientFrame())
    {
        ++SkippedClientFrames;
        SavedClientFrame = ((ClientFrameSubsystem *)TheGameClient)->getFrame();
        return;
    }

    BFMEDesyncCheck desyncCheck;
    Radar->m_update.update();
    ((ClientFrameSubsystem *)TheGameClient)->update();
    TheMessageStream->propagateMessages();

    unsigned int timedOps = _bfme_updateTimedOps();
    int inputLocked = timedOps & 1;
    if (inputLocked)
    {
        InputLockSubsystem->update();
    }

    if (inputLocked != TimedOpInputLocked)
    {
        if (inputLocked)
        {
            TheInGameUI->setEngineInputEnabled(false);
            TheMouse->_bfme_setEngineVisibility(false);
        }
        else
        {
            TheInGameUI->setEngineInputEnabled(true);
            if ((timedOps & 4) == 0)
                TheMouse->_bfme_setEngineVisibility(true);
        }
    }

    ClientSubsystem *audio = AudioSubsystem;
    ClientSubsystemVtable *audioVtable = *(ClientSubsystemVtable **)audio;
    TimedOpInputLocked = inputLocked;
    audioVtable->update(audio);
    if (TheNetwork != 0)
        TheNetwork->liteupdate(0);
}

// ?AudioSubsystem@@3PAVClientSubsystem@@A: the global at this VA is ?TheAudio@@3PAVAudioManager@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?AudioSubsystem@@3PAVClientSubsystem@@A=?TheAudio@@3PAVAudioManager@@A")
#pragma comment(linker, "/alternatename:?TheAudio@@3PAVBfmeAudioVtblIndexed@@A=?TheAudio@@3PAVAudioManager@@A")
// ?Radar@@3PAVRadarSubsystem@@A: the global at this VA is ?TheRadar@@3PAVRadar@@A; this name is an alias for it.
#pragma comment(linker, "/alternatename:?Radar@@3PAVRadarSubsystem@@A=?TheRadar@@3PAVRadar@@A")
#pragma comment(linker, "/alternatename:?TheRadar@@3PAVPartitionManager@@A=?TheRadar@@3PAVRadar@@A")
// ?WindowManagerSubsystem@@3PAVClientSubsystem@@A: the global at VA 0xdfe4cc is ?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A.
#pragma comment(linker, "/alternatename:?WindowManagerSubsystem@@3PAVClientSubsystem@@A=?g_bfmeAptWindowManager@@3PAVBfmeAptWindowManager@@A")
// ?AudioSubsystem@@3PAVClientSubsystem@@A: the global at VA 0xdfe6e8 is ?TheAudio@@3PAVAudioManager@@A.
#pragma comment(linker, "/alternatename:?AudioSubsystem@@3PAVClientSubsystem@@A=?TheAudio@@3PAVAudioManager@@A")
// ?Radar@@3PAVRadarSubsystem@@A: the global at VA 0xdff070 is ?TheRadar@@3PAVRadar@@A.
#pragma comment(linker, "/alternatename:?Radar@@3PAVRadarSubsystem@@A=?TheRadar@@3PAVRadar@@A")
// ?InputLockSubsystem@@3PAVClientSubsystem@@A: the global at VA 0xdfe720 is ?TheKeyboard@@3PAVKeyboard@@A.
#pragma comment(linker, "/alternatename:?InputLockSubsystem@@3PAVClientSubsystem@@A=?TheKeyboard@@3PAVKeyboard@@A")

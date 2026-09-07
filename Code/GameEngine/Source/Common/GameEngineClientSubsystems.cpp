// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX /arch:SSE
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
extern ClientFrameSubsystem *TheGameClient;
extern ClientSubsystem *WindowManagerSubsystem;
extern RadarSubsystem *Radar;
extern MessageStream *MessageStreamSubsystem;
extern ClientSubsystem *InputLockSubsystem;
extern class InGameUI *InGameUISubsystem;
extern class Mouse *MouseSubsystem;
extern ClientSubsystem *AudioSubsystem;
extern NetworkInterface *TheNetwork;
extern int SkippedClientFrames;
extern int SavedClientFrame;
extern int TimedOpInputLocked;

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

    unsigned char advanceFrame = TheGameClient->m_advanceFrame;
    if (advanceFrame != 0)
    {
        TheGameClient->setFrame(TheGameClient->getFrame() + 1);
    }

    WindowManagerSubsystem->update();
    if (_bfme_shouldSkipClientFrame())
    {
        ++SkippedClientFrames;
        SavedClientFrame = TheGameClient->getFrame();
        return;
    }

    BFMEDesyncCheck desyncCheck;
    Radar->m_update.update();
    TheGameClient->update();
    MessageStreamSubsystem->propagateMessages();

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
            InGameUISubsystem->setEngineInputEnabled(false);
            MouseSubsystem->_bfme_setEngineVisibility(false);
        }
        else
        {
            InGameUISubsystem->setEngineInputEnabled(true);
            if ((timedOps & 4) == 0)
                MouseSubsystem->_bfme_setEngineVisibility(true);
        }
    }

    ClientSubsystem *audio = AudioSubsystem;
    ClientSubsystemVtable *audioVtable = *(ClientSubsystemVtable **)audio;
    TimedOpInputLocked = inputLocked;
    audioVtable->update(audio);
    if (TheNetwork != 0)
        TheNetwork->liteupdate(0);
}

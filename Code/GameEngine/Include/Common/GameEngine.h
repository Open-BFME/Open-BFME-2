/* Target facts (code addresses are RVAs, tables are VAs): GameEngine is polymorphic with SubsystemInterface at +0. Constructor 0x0022DA66 calls the parent's 0x001B4E63 at 0x0022DA7A, then installs 0x00BE7188 at 0x0022DA93. Destructor 0x00225B9B installs the same table and tail-calls the parent's 0x001B4E74 at 0x00225BA1; deleting destructor 0x00226333 calls 0x00225B9B. The parent's stores of 0x00BD77A0 at 0x001B4E65/0x001B4E74 belong to the base lifetime. Parent fields are byte +4 and AsciiString +8. The constructor writes dword +0C, bytes +10/+11, dword +14, indexed dwords +18, dwords +34/+38, float +3C, byte +40, floats +44/+48, dwords +4C/+50/+54, float +58 and dword +5C. Constructor 0x00041D41 calls GameEngine then writes its own member at +60 at 0x00041D57; allocation 0x00001D2B requests 0x64 for that derived class. Together these establish sizeof(GameEngine)=0x60; 0x002260F7 indexes process handles from +18 with count +14, bounding seven entries before +34.
   Table 0x00BE7188 has 40 code entries and text at 0x00BE7228. Slots 0-13 are the parent's fourteen slots with 0=226333, 1=0B3FD0, 9=229708 and 10=225DA9; inherited 2=1B5384, 3/8/12=0B3FD0, 4/11=5CB9FF, 5=47A699, 6=0D43D0 and 7/13=47A69C agree with 0x00BD77A0. Slots 14=22E2E4, 15=22D290, 16=225AD5, 17=225AFF, 18=5F69C4, 19=1DB0A8, 20=0D1A7E, 21=1DBA6D, 22=225F76, 23=0B3FD0, 24=041D5E, 25=23C497, 26=23054C, 27=225F44, 28/29/31-37=03B810 (__purecall), 30=225F12, 38=22634F and 39=225C12. Slot 19 reads +0C, 20/21 write/read byte +10, 24/25 read/write byte +11. Call 0x00001D57 uses slot 25. Row 0x00225D38 tests dword +34; 0x00225D68/0x00225D78 write the +38 counter and +3C interpolation ratio. Rowed lifetimes and methods remain out of line; the nonvirtual ledger spelling rva0022D290 is separate from virtual slot 15.
   Names: Zero Hour's Common/GameEngine.h proves init/reset/update, execute, setFramesPerSecondLimit/getFramesPerSecondLimit, setQuitting/getQuitting, isMultiplayerSession, serviceWindowsOS, isActive/setIsActive and m_maxFPS/m_quitting/m_isActive. BFME2 rows prove the constructor/destructor, rva00225AD5 (225AD5), rva00225AFF (225AFF), rva0023054C (23054C), createMessageStream (225F12), _bfme_updateNetworkAndLogic (22634F), _bfme_updateClientSubsystems (225C12), rva0022D290 (22D290), startHeadlessClients (225F81), private stopHeadlessClients (2260F7), _bfme_shouldSkipClientFrame (225BA6), rva00225D38 (225D38) and updateClientFrameCounter/updateClientFrameRatio (225D68/225D78). Other slots and fields retain neutral offset names. */
#pragma once
#ifndef BFME2_GAMEENGINE_H
#define BFME2_GAMEENGINE_H

#if !defined(CANONICAL_SUBSYSTEMINTERFACE_H) && !defined(BFME_SUBSYSTEM_SLOTS)
#define BFME_SUBSYSTEM_SLOTS
#endif
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class MessageStream;
class AptLanLobby;
class BfmeOwnVVD;
class Drawable;
class GameClient;
class MilesAudioManager;
class Rva000B595F;
class Rva000EDB47;
class Rva0049CBDA;
class W3DScriptedModelDraw;
class W3DStatusCircle;

class GameEngine : public SubsystemInterface
{
public:
    GameEngine();
    virtual ~GameEngine();
#ifdef BFME_SUBSYSTEM_SLOTS
    virtual void init();
#else
    virtual void vslot01();
    virtual bool loadIniFilesFromLegend();
    virtual void postProcessLoad();
    virtual bool vslot04(int);
    virtual bool vslot05();
    virtual int vslot06();
    virtual void vslot07(int);
    virtual void vslot08();
#endif
    virtual void reset();
    virtual void update();
#ifndef BFME_SUBSYSTEM_SLOTS
    virtual bool vslot11(int);
    virtual void vslot12();
    virtual void vslot13(int);
#endif
    virtual void init(int argc, char *argv[]);
    virtual void execute();
    virtual bool rva00225AD5();
    virtual bool rva00225AFF();
    virtual void setFramesPerSecondLimit(int fps);
    virtual int getFramesPerSecondLimit();
    virtual void setQuitting(bool quitting);
    virtual bool getQuitting();
    virtual bool isMultiplayerSession();
    virtual void serviceWindowsOS();
    virtual bool isActive();
    virtual void setIsActive(bool active);
    virtual void rva0023054C();
    virtual void *vslot27();
    virtual void *vslot28() = 0;
    virtual void *vslot29() = 0;
protected:
    virtual MessageStream *createMessageStream();
public:
    virtual void *vslot31() = 0;
    virtual void *vslot32() = 0;
    virtual void *vslot33() = 0;
    virtual void *vslot34() = 0;
    virtual void *vslot35() = 0;
    virtual void *vslot36() = 0;
    virtual void *vslot37() = 0;
    virtual void _bfme_updateNetworkAndLogic(int phase);
    virtual void _bfme_updateClientSubsystems();

    void rva0022D290();
    void startHeadlessClients(int numClients);

    int m_maxFPS;
    bool m_quitting;
    bool m_isActive;
    int m_14;
    void *m_18[7];
    int m_34;
    int m_38;
    float m_3C;
    bool m_40;
    float m_44;
    float m_48;
    int m_4C;
    int m_50;
    unsigned int m_54;
    float m_58;
    int m_5C;

private:
    void stopHeadlessClients();
    bool _bfme_shouldSkipClientFrame();
    bool rva00225D38();
    void updateClientFrameCounter();
    void updateClientFrameRatio();

    friend class AptLanLobby;
    friend class BfmeOwnVVD;
    friend class Drawable;
    friend class GameClient;
    friend class MilesAudioManager;
    friend class Rva000B595F;
    friend class Rva000EDB47;
    friend class Rva0049CBDA;
    friend class W3DScriptedModelDraw;
    friend class W3DStatusCircle;
};

extern GameEngine *TheGameEngine;
GameEngine *CreateGameEngine();

#endif

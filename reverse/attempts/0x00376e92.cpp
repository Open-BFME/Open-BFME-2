// ?rva00376E92@GameLogic@@QAEX_N0@Z
// partial score=0.9914 date=2026-10-08
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME1 U4Sink0060D3B0_push.cpp semantic guide, target-native statement order.
#include "../Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
class BfmeDfe6e4 { public: void _M_rva00625699(); };
class Rva0023D46F {
public:
    Rva0023D46F(BfmeDfe6e4*);
    ~Rva0023D46F() { if (counter) counter->_M_rva00625699(); }
private: BfmeDfe6e4 *counter;
};
class Rva00248558Scope {
public: Rva00248558Scope(); ~Rva00248558Scope();
};
extern BfmeDfe6e4 *theBfmeDfe6e4;
#define VS(n) virtual void slot##n();
class AudioManager {
public:
    VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9)
    VS(10) VS(11) VS(12) VS(13) VS(14) VS(15) VS(16) VS(17) VS(18) VS(19)
    virtual void slot20(int); virtual int slot21();
    VS(22) VS(23) VS(24) VS(25) VS(26) VS(27) VS(28) VS(29)
    VS(30) VS(31) VS(32) VS(33) VS(34) VS(35) VS(36) VS(37) VS(38) VS(39)
    VS(40) VS(41) VS(42) VS(43) VS(44) VS(45) VS(46) VS(47) VS(48) VS(49)
    VS(50) VS(51) VS(52) VS(53) VS(54) VS(55) VS(56) VS(57) VS(58) VS(59)
    VS(60) VS(61) VS(62) VS(63) VS(64) VS(65) VS(66) VS(67) VS(68) VS(69)
    VS(70) VS(71) VS(72) VS(73) VS(74) VS(75) VS(76) VS(77) VS(78) VS(79)
    VS(80) VS(81) VS(82) VS(83) VS(84) VS(85) VS(86) VS(87) VS(88) VS(89)
    VS(90) VS(91) VS(92) VS(93) VS(94) VS(95) VS(96) VS(97) VS(98) VS(99)
    VS(100)
};
extern AudioManager *TheAudio;
class Rva00DFEF18Host {
public:
    VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9)
    virtual void slot10(bool);
    char pad[0x18-4]; bool flag;
};
extern Rva00DFEF18Host *g_00DFEF18;
class StatsCollector { public: void writeFileEnd(); };
extern StatsCollector *g_00E032F8;
class ScriptActions {
public:
    VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9)
    VS(10) VS(11) VS(12) VS(13) VS(14) virtual void slot15(bool);
};
extern ScriptActions *TheScriptActions;
class BfmeSelectionState { public: bool isSelectionLocked() const; };
extern BfmeSelectionState *g_009FEF10;
class Shell { public: void rva0035C7CF(bool); };
extern Shell *TheShell;
class Rva0035C194 { public: bool rva0035C194(bool,bool); };
bool rva00520F7D();
class GameEngine {
public:
    VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9)
    VS(10) VS(11) VS(12) VS(13) VS(14) VS(15) VS(16) VS(17) VS(18) VS(19)
    virtual void slot20(bool);
};
extern GameEngine *TheGameEngine;
template<class T> class StringBase { public: bool isEmpty() const; private: friend class GameLogic; void releaseBuffer(); void *data; };
class GlobalData {
public: char pad[0xAB8]; StringBase<char> previousFile, initialFile; char padAC0[4]; bool clearFiles;
};
extern GlobalData *TheWritableGlobalData;
class GameMessage { public: void appendBooleanArgument(bool); };
class MessageStream {
public:
    VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9)
    VS(10) VS(11) VS(12) VS(13) VS(14) VS(15) VS(16) VS(17)
    virtual GameMessage *slot18(int);
};
extern MessageStream *MessageStreamSubsystem;
class InGameUI {
public:
    VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9)
    VS(10) VS(11) VS(12) VS(13) VS(14) VS(15) VS(16) VS(17) VS(18) VS(19)
    VS(20) VS(21) VS(22) VS(23) VS(24) VS(25) VS(26) VS(27) VS(28) VS(29)
    VS(30) VS(31) VS(32) VS(33) VS(34) VS(35) VS(36) VS(37) VS(38) VS(39)
    VS(40) VS(41) VS(42) VS(43) VS(44) VS(45) VS(46) VS(47) VS(48) VS(49)
    VS(50) VS(51) VS(52) VS(53) VS(54) VS(55) VS(56) VS(57) VS(58) VS(59)
    VS(60) VS(61) VS(62) VS(63) VS(64) VS(65) VS(66) VS(67) VS(68)
};
extern InGameUI *TheInGameUI;
class ControlBar { public: VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9) VS(10) };
extern ControlBar *TheControlBar;
void HideControlBar(bool);
class Mouse { public: void _bfme_setEngineVisibility(bool); };
extern Mouse *TheMouse;
extern int SavedClientFrame;
#undef VS
void GameLogic::rva00376E92(bool showScoreScreen, bool arg2)
{
    Rva0023D46F counterRef(theBfmeDfe6e4);
    Rva00248558Scope scope;
    TheAudio->slot100();
    if (g_00DFEF18 && g_00DFEF18->flag) g_00DFEF18->slot10(false);
    if (g_00E032F8) g_00E032F8->writeFileEnd();
    if (TheScriptActions) TheScriptActions->slot15(false);
    if (TheAudio && !TheAudio->slot21()) TheAudio->slot20(2);
    rva00376D49();
    if (rva0042219() || (g_009FEF10 && g_009FEF10->isSelectionLocked())) {
        if (arg2 || showScoreScreen) {
            if (showScoreScreen) {
                TheShell->rva0035C7CF(false);
                if (!rva00520F7D()) showScoreScreen=false;
            }
            if (!showScoreScreen) {
                ((Rva0035C194*)TheShell)->rva0035C194(true,false);
                TheShell->rva0035C7CF(true);
            }
        }
    }
    TheGameEngine->slot9();
    m_110=9;
    GlobalData *data=TheWritableGlobalData;
    if (!data->initialFile.isEmpty()) {
        if (data->clearFiles) {
            data->initialFile.releaseBuffer();
            TheWritableGlobalData->previousFile.releaseBuffer();
        } else TheGameEngine->slot20(true);
    }
    GameMessage *msg=MessageStreamSubsystem->slot18(0x3EC);
    msg->appendBooleanArgument(true);
    TheInGameUI->slot68();
    TheControlBar->slot10();
    HideControlBar(true);
    TheMouse->_bfme_setEngineVisibility(true);
    SavedClientFrame=0;
}

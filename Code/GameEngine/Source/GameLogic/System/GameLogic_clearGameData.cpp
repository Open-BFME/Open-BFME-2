// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I.
// BFME1 U4Sink0060D3B0_push.cpp semantic guide, target-native statement order.
// Retail 0x00376E92 (466 bytes). Calls the unrowed AptTimeLine::OpenScreen (0x00520F7D) through a pin.
#include "Code/GameEngine/Include/Common/MessageStream.h"
#include "Code/GameEngine/Include/Common/GlobalData.h"
#include "Code/GameEngine/Include/GameClient/Mouse.h"
#include "Code/GameEngine/Include/GameClient/Shell.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "../../../Include/Common/BfmeDfe6e4.h"
class Rva0023D46F {
public:
    Rva0023D46F(BfmeDfe6e4*);
    ~Rva0023D46F() { if (counter) counter->_M_rva00625699(); }
private: BfmeDfe6e4 *counter;
};
#include "../../../Include/Common/Rva00248558Scope.h"
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
class LivingWorld; extern LivingWorld *TheLivingWorld;
#include "../../../Include/Common/StatsCollector.h"
extern StatsCollector *g_00E032F8;
class ScriptActions {
public:
    VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9)
    VS(10) VS(11) VS(12) VS(13) VS(14) virtual void slot15(bool);
};
extern ScriptActions *TheScriptActions;
#include "../../../Include/Common/BfmeSelectionState.h"
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
bool rva00520F7D();
class GameEngine {
public:
    VS(0) VS(1) VS(2) VS(3) VS(4) VS(5) VS(6) VS(7) VS(8) VS(9)
    VS(10) VS(11) VS(12) VS(13) VS(14) VS(15) VS(16) VS(17) VS(18) VS(19)
    virtual void slot20(bool);
};
extern GameEngine *TheGameEngine;
extern MessageStream *TheMessageStream;
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
extern int SavedClientFrame;
#undef VS
void GameLogic::clearGameData(bool showScoreScreen, bool arg2)
{
    Rva0023D46F counterRef(theBfmeDfe6e4);
    Rva00248558Scope scope;
    TheAudio->slot100();
    if (((Rva00DFEF18Host *)TheLivingWorld) && ((Rva00DFEF18Host *)TheLivingWorld)->flag) ((Rva00DFEF18Host *)TheLivingWorld)->slot10(false);
    if (g_00E032F8) g_00E032F8->writeFileEnd();
    if (TheScriptActions) TheScriptActions->slot15(false);
    if (TheAudio && !TheAudio->slot21()) TheAudio->slot20(2);
    rva00376D49();
    if (rva0042219() || (TheLivingWorldLogic && ((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked())) {
        if (arg2 || showScoreScreen) {
            if (showScoreScreen) {
                TheShell->showShell(false);
                if (!rva00520F7D()) showScoreScreen=false;
            }
            if (!showScoreScreen) {
                TheShell->showShellMap(true,false);
                TheShell->showShell(true);
            }
        }
    }
    TheGameEngine->slot9();
    m_110=9;
    GlobalData *data=TheWritableGlobalData;
    // Retail calls StringBase<char>::isEmpty (0x00001E2F) out of line here, and
    // StringBase<char>::clear expands to the releaseBuffer call (0x00036410).
    if (!((const StringBase<char> *)&data->m_initialFile)->isEmpty()) {
        if (data->field0AC4) {
            ((StringBase<char> *)&data->m_initialFile)->clear();
            ((StringBase<char> *)&TheWritableGlobalData->field0AB8)->clear();
        } else TheGameEngine->slot20(true);
    }
    GameMessage *msg=TheMessageStream->appendMessage(0x3EC);
    msg->appendBooleanArgument(true);
    TheInGameUI->slot68();
    TheControlBar->slot10();
    HideControlBar(true);
    TheMouse->_bfme_setEngineVisibility(true);
    SavedClientFrame=0;
}

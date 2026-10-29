// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2
// stlport
// Native Ghidra 0031ADAE..0031AE01, 83B, no-argument thiscall.
// Reference lead: GeneralsMD ControlBar::setSquishedControlBarConfig, under
// BFME1 pointer ba7ddda7e8f261163972ddbe23c7e7a12ac5b84f. BFME2 omits
// repopulateBuildTooltipLayout. Retain an RVA method name for that adaptation.
// Target offsets: stage24, default position1C/20, master window48, manager44;
// calls rowed winSetPosition313A9E and canonical scheme setter31FD0D.
// DIR32 globals and the Display height/View setHeight slots are established
// by the surrounding ControlBar and scheme-manager bodies. Local player10
// and its PlayerTemplate34 supply the same argument as the reference lead.
typedef bool Bool;
#include "subsystem_interface.h"

#include "ControlBarSchemeManagerView.h"
#include "../../../../../Libraries/Include/Lib/ICoord2D.h"

class GameWindow
{
public:
    int winSetPosition(int x, int y);
};

class Display
{
public:
#define DISPLAY_SLOT(n) virtual void unknown##n();
    DISPLAY_SLOT(00) DISPLAY_SLOT(01) DISPLAY_SLOT(02) DISPLAY_SLOT(03)
    DISPLAY_SLOT(04) DISPLAY_SLOT(05) DISPLAY_SLOT(06) DISPLAY_SLOT(07)
    DISPLAY_SLOT(08) DISPLAY_SLOT(09) DISPLAY_SLOT(10) DISPLAY_SLOT(11)
    DISPLAY_SLOT(12) DISPLAY_SLOT(13) DISPLAY_SLOT(14) DISPLAY_SLOT(15)
    DISPLAY_SLOT(16)
#undef DISPLAY_SLOT
    virtual int getHeight() const;
};

class View
{
public:
#define VIEW_SLOT(n) virtual void unknown##n();
    VIEW_SLOT(00) VIEW_SLOT(01) VIEW_SLOT(02) VIEW_SLOT(03)
    VIEW_SLOT(04) VIEW_SLOT(05) VIEW_SLOT(06) VIEW_SLOT(07)
    VIEW_SLOT(08) VIEW_SLOT(09) VIEW_SLOT(10) VIEW_SLOT(11)
    VIEW_SLOT(12) VIEW_SLOT(13) VIEW_SLOT(14) VIEW_SLOT(15)
#undef VIEW_SLOT
    virtual void setHeight(int height);
};

struct Rva0031ADAEPlayerView
{
    char unknown00[0x34];
    const PlayerTemplate *playerTemplate;
};
class PlayerList
{
public:
    char unknown00[0x10];
    Player *localPlayer;
};

extern Display *TheDisplay;
extern View *TheTacticalView;
extern PlayerList *ThePlayerList;

#include "ControlBarMemberTypes.h"
class ControlBar : public SubsystemInterface
{
public:
    void rva0031ADAE();
private:
    char m_pad0C[0x1C - 0x0C];
    ICoord2D m_defaultControlBarPosition;
    int m_currentControlBarStage;
    char unknown28[0x44 - 0x28];
    ControlBarSchemeManager *m_controlBarSchemeManager;
    GameWindow *m_contextParent[9]; // [0] is the master window
};

void ControlBar::rva0031ADAE()
{
    if (m_currentControlBarStage == 1)
        return;
    m_currentControlBarStage = 1;
    m_contextParent[0]->winSetPosition(m_defaultControlBarPosition.x, m_defaultControlBarPosition.y);
    TheTacticalView->setHeight(TheDisplay->getHeight());
    m_controlBarSchemeManager->setControlBarSchemeByPlayerTemplate(
        reinterpret_cast<Rva0031ADAEPlayerView *>(ThePlayerList->localPlayer)
            ->playerTemplate, true);
}

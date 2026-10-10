// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /MD /DNDEBUG
// WB13D1610 identifies Impl::Update; native527EAB..527F65 supplies the
// Player local slot10, planning value2 at750 and Impl fields0/4/8.
// States1/2 keep the panel open; state3 follows closing. The unnamed
// effect-installing helper uses a witnessed zero-argument thiscall pin;
// its conflicting record types are not asserted here.
#include "ascii_string.h"
class PlayerList;
extern PlayerList *ThePlayerList;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222A8BTarget;
int Rva00524EF4AptCall(Rva00222A8BTarget *, void *, const char *, const char *);
class Rva001021F7;
Rva001021F7 *Rva00102215Get();
class Rva0010231F { public: void rva0010231F(); };
class Rva0010225F { public: void rva00102284(); };
struct PlanningPlayerView { char unknown00[0x750]; int planningMode; };
struct PlanningPlayerListView { char unknown00[0x10]; PlanningPlayerView *localPlayer; };
namespace InGamePlanningModeInterface {
class Impl {
public:
    void Update();
private:
    void *level;
    AsciiString name;
    int state;
};
}
void InGamePlanningModeInterface::Impl::Update()
{
    PlanningPlayerView *player = reinterpret_cast<PlanningPlayerListView *>(ThePlayerList)->localPlayer;
    if (player && player->planningMode == 2) {
        if (state != 1 && state != 2) {
            Rva00524EF4AptCall(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager), level, name.str(), "Open");
            Rva001021F7 *effect = Rva00102215Get();
            if (effect) reinterpret_cast<Rva0010231F *>(effect)->rva0010231F();
            state = 1;
        }
    } else if (state == 1 || state == 2) {
        Rva00524EF4AptCall(reinterpret_cast<Rva00222A8BTarget *>(g_bfmeAptWindowManager), level, name.str(), "Close");
        Rva001021F7 *effect = Rva00102215Get();
        if (effect) reinterpret_cast<Rva0010225F *>(effect)->rva00102284();
        state = 3;
    }
}

// Native527F65..527F6C: receiver word0 is forwarded to the owned Impl::Update.
// The original wrapper name and enclosing class remain unknown.
struct Rva00527F65PlanningUpdateForward {
    InGamePlanningModeInterface::Impl *implementation;
    void update();
};
void Rva00527F65PlanningUpdateForward::update()
{
    implementation->Update();
}

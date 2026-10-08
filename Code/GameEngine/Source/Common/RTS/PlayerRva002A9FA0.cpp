// cl: /O1 /Oy /DNDEBUG /MD /ICode/Libraries/Include/Lib
// BFME1 ba7ddda7 Player_setRankLevel.cpp and ZH Player::setRankLevel
// guide the rank-change/EVA/point-change notification sequence. BFME2
// outlines the rank core into221B0038037C..00380459 RET4, returning AL0/1;
// that core reads rank14 and adjusts purchase points1C. This108B wrapper
// compares the old1C, tests local-player pointer10, emits event2, and calls
// the independently rowed ControlBar refresh31B5A3 once or twice.
// Receiver is Player+8, proved by target's this-8 local-player comparison
// and refresh argument; address-labelled view retains that adjustment.
#include "Coord3D.h"
class Player;
class Rva00380200 {
public:
    bool rva0038037C(int);
};
class ControlBar {
public:
    void rva0031B5A3(const Player *);
};
class Eva {
public:
    void rva001DE2DA(int, const Coord3D *, int);
};
class PlayerList {
public:
    char unknown00[0x10];
    Player *localPlayer;
};
extern PlayerList *ThePlayerList;
extern ControlBar *TheControlBar;
extern Eva *TheEva;
class Rva002A9FA0 {
public:
    bool rva002A9FA0(int);
    char unknown00[0x1C];
    int points;
};
bool Rva002A9FA0::rva002A9FA0(int level)
{
    int oldPoints = points;
    bool changed = ((Rva00380200 *)this)->rva0038037C(level);
    if (changed && TheControlBar) {
        if ((Player *)((char *)this - 8) == ThePlayerList->localPlayer && TheEva)
            TheEva->rva001DE2DA(2, 0, 0);
        const Player *player = (const Player *)((const char *)this - 8);
        TheControlBar->rva0031B5A3(player);
        if (oldPoints != points)
            TheControlBar->rva0031B5A3(player);
    }
    return changed;
}

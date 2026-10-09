// cl: /O1 /arch:SSE /G7 /MD /Ireference/shims/moduledata /EHsc
// BF1 f98983a7d Player::killPlayer and Zero Hour Player.cpp guide the two
// team passes, dead flag, single-player exception, and emptying the treasury.
// Native 002AB44A..002AB5C7 proves the BFME2 skirmish-manager early path,
// Player fields 32C/734/3BC, Money90/94, and player/UI vslots40/BC.
// WB C18C60 corroborates this relationship; its offsets differ from retail.
// BFME2 also credits the last 20-byte score record to opponent104, scaled by
// GlobalData11B8. Its 37-byte worker at 0039B6A8 tests the canonical scoring
// flag98 and accumulates floatFC. The separately published provider retains
// the established neutral receiver name Rva0039B683.
// Team's multiple-inheritance member-pointer ABI is inherited from the
// already matched PlayerRva002AD93A.cpp and confirmed by callback9C4AF5.
// Cache the range's begin pointer before the count: native keeps it for the
// final record read after signed division by20.
#include "../GameLogicObjectLookupView.h"
#include "Common/Snapshot.h"
extern GameLogic *TheGameLogic;
class Rva0039B683 {
  public:
    char pad[0xFC];
    float score;
    char pad100[4];
    int opponent;
    struct Record {
        float a, b, value, c, d;
    };
    char pad108[0x31C - 0x108];
    struct Range {
        Record *begin, *end, *capacity;
    } range;
    void rva0039B6A8(float);
};
class Player {
  public:
    char pad[0x3BC];
    Rva0039B683 score;
};
struct Rva002A8AB1Record;
class Rva002A8F24 {
  public:
    Rva002A8AB1Record *rva002A8AB1(void *);
};
extern Rva002A8F24 *g_00DFEEF8;
class SkirmishAI {
  public:
    bool isAPartialBrain();
};
class MemoryPoolObject {
  public:
    virtual ~MemoryPoolObject();
};
class Team : public MemoryPoolObject, public Snapshot {
  public:
    Team *dlink_next_TeamInstanceList() const;
    void rva003A1C3A(bool);
    void killTeam();
};
template <class T> class DLINK_ITERATOR {
    T *p;
    T *(T::*next)() const;

  public:
    DLINK_ITERATOR(T *x, T *(T::*n)() const) : p(x), next(n) {}
    bool done() const { return p == 0; }
    T *cur() const { return p; }
    void advance() {
        if (p)
            p = (p->*next)();
    }
};
class TeamPrototype {
  public:
    char pad[0x334];
    Team *head;
    DLINK_ITERATOR<Team> iterate_TeamInstanceList() const {
        return DLINK_ITERATOR<Team>(head, &Team::dlink_next_TeamInstanceList);
    }
};
struct PlayerTeamNode {
    PlayerTeamNode *next, *prev;
    TeamPrototype *value;
};
class PlayerList {
  public:
#define SLOT(n) virtual void slot##n();
    SLOT(0)
    SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11)
        SLOT(12) SLOT(13) SLOT(14) SLOT(15)
#undef SLOT
            virtual void dispatch40();
    char pad[0xC];
    void *local;
    Player *getNthPlayer(int);
};
extern PlayerList *ThePlayerList;
class InGameUI {
  public:
#define SLOT(n) virtual void slot##n();
    SLOT(0)
    SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11)
        SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21)
            SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
                SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
                    SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46)
#undef SLOT
                        virtual void dispatchBC(bool);
};
extern InGameUI *TheInGameUI;
class GlobalData {
  public:
    char pad[0x11B8];
    float factor;
};
extern GlobalData *TheWritableGlobalData;
class Rva0023C666 {
  public:
    int rva0023C666();
};
class Rva0039B795;
class Rva003B0D7C {
  public:
    char pad[4];
    unsigned money;
    unsigned rva003B0CB3(unsigned, Rva0039B795 *, bool);
};
class Rva002AB5C7Player {
  public:
    char pad[0x5C];
    int type;
    char pad60[0x90 - 0x60];
    Rva003B0D7C money;
    char pad98[0x32C - 0x98];
    PlayerTeamNode *teams;
    char pad330[0x3BC - 0x330];
    Rva0039B683 score;
    char pad6E4[0x734 - 0x6E4];
    bool dead;
    void rva002AB44A();
};
void Rva002AB5C7Player::rva002AB44A() {
    SkirmishAI *brain = (SkirmishAI *)g_00DFEEF8->rva002A8AB1(this);
    if (brain && brain->isAPartialBrain())
        dead = true;
    else {
        for (PlayerTeamNode *it = teams->next; it != teams; it = it->next)
            for (DLINK_ITERATOR<Team> iter = it->value->iterate_TeamInstanceList(); !iter.done();
                 iter.advance()) {
                Team *team = iter.cur();
                if (!team)
                    continue;
                team->rva003A1C3A(false);
            }
        dead = true;
        for (PlayerTeamNode *it = teams->next; it != teams; it = it->next)
            for (DLINK_ITERATOR<Team> iter = it->value->iterate_TeamInstanceList(); !iter.done();
                 iter.advance()) {
                Team *team = iter.cur();
                if (!team)
                    continue;
                team->killTeam();
            }
        ThePlayerList->dispatch40();
        money.rva003B0CB3(money.money, 0, true);
    }
    if ((unsigned char)((Rva0023C666 *)TheGameLogic)->rva0023C666() && type == 1) {
        dead = false;
        return;
    }
    if (this == ThePlayerList->local)
        TheInGameUI->dispatchBC(false);
    Rva0039B683 *stats = &score;
    if (stats) {
        Player *other = ThePlayerList->getNthPlayer(stats->opponent);
        if (other) {
            Rva0039B683::Range *array = &stats->range;
            Rva0039B683::Record *begin = array->begin;
            int count = array->end - begin;
            if (count > 0)
                other->score.rva0039B6A8(begin[count - 1].value * TheWritableGlobalData->factor);
        }
    }
}

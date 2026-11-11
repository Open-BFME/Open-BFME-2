// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// CarryoverUnit::createSingleObject: WB F5D930 and native 37DCE8..37DE0E RET4.
// WB CarryoverUnit.cpp lines 99/112 establish the source and object-creation
// role. Native providers are already owned: template lookup 37DC52, factory
// 2D0A23, object cleanup 28CBFD, experience 39B3D1, bitset OR 28C557,
// upgrade refresh 292EEA, record assignment 1EAFC1 and sink lookup 2931F5.
// Scoring is GameLogic+98; player team is +2EC; object tracker/upgrade/record
// views are +264/+284/+468. Slot31 returns a full EAX query, slot68 forwards
// the already owned 37DCCC callback and the 128-byte upgrade bitset. Only
// accessed prefixes and native slot contracts are modeled; no full AI or
// revival-record class identity is asserted. The inline accessors preserve
// the original call setup and separate failure/success scoring restores.
#include <string.h>
class Object;
class Player;
class ThingTemplate;
class Team;
struct CreateMask { unsigned int words[4]; };
enum ObjectID; class ThingFactory {
public: Object *newObject(const ThingTemplate *, Team *, const CreateMask *, ObjectID);
};
extern ThingFactory *TheThingFactory;
class GameLogic;
extern GameLogic *TheGameLogic;
struct CarryoverGameLogicView { char unknown00[0x98]; bool enable; bool get() const { return enable; } void set(bool v) { enable=v; } };
struct CarryoverPlayerView { char unknown00[0x2EC]; Team *team; Team *getTeam() const { return team; } };
class Rva002206F9Sink;
#include "../../../Include/Common/Rva0037DCA5.h"
class Rva0028CBFD { public: void rva0028CBFD(); };
class Rva003BD306Target {
public:
    char unknown00[0x10]; float experience;
    char unknown14[0x20-0x14]; bool flag;
    void rva0039B3D1(float,bool);
};
namespace _STL {
template<unsigned int N> struct _Base_bitset {
    unsigned int words[N];
    void _M_do_or(const _Base_bitset<N> &);
};
}
class Rva001EAFC1 {
public:
    int unknown00, reset04; void setReset(int v) { reset04=v; } void setFlag(bool v) { flag14=v; }
    char unknown08[0x14-8]; bool flag14;
    Rva001EAFC1 &operator=(const Rva001EAFC1 &);
};
#include "../Object/object.h"
class CarryoverAIView {
public:
#define CARRYOVER_SLOT(n) virtual void slot##n() = 0;
    CARRYOVER_SLOT(0) CARRYOVER_SLOT(1) CARRYOVER_SLOT(2) CARRYOVER_SLOT(3)
    CARRYOVER_SLOT(4) CARRYOVER_SLOT(5) CARRYOVER_SLOT(6) CARRYOVER_SLOT(7)
    CARRYOVER_SLOT(8) CARRYOVER_SLOT(9) CARRYOVER_SLOT(10) CARRYOVER_SLOT(11)
    CARRYOVER_SLOT(12) CARRYOVER_SLOT(13) CARRYOVER_SLOT(14) CARRYOVER_SLOT(15)
    CARRYOVER_SLOT(16) CARRYOVER_SLOT(17) CARRYOVER_SLOT(18) CARRYOVER_SLOT(19)
    CARRYOVER_SLOT(20) CARRYOVER_SLOT(21) CARRYOVER_SLOT(22) CARRYOVER_SLOT(23)
    CARRYOVER_SLOT(24) CARRYOVER_SLOT(25) CARRYOVER_SLOT(26) CARRYOVER_SLOT(27)
    CARRYOVER_SLOT(28) CARRYOVER_SLOT(29) CARRYOVER_SLOT(30)
    virtual int slot31() = 0;
    CARRYOVER_SLOT(32) CARRYOVER_SLOT(33) CARRYOVER_SLOT(34) CARRYOVER_SLOT(35)
    CARRYOVER_SLOT(36) CARRYOVER_SLOT(37) CARRYOVER_SLOT(38) CARRYOVER_SLOT(39)
    CARRYOVER_SLOT(40) CARRYOVER_SLOT(41) CARRYOVER_SLOT(42) CARRYOVER_SLOT(43)
    CARRYOVER_SLOT(44) CARRYOVER_SLOT(45) CARRYOVER_SLOT(46) CARRYOVER_SLOT(47)
    CARRYOVER_SLOT(48) CARRYOVER_SLOT(49) CARRYOVER_SLOT(50) CARRYOVER_SLOT(51)
    CARRYOVER_SLOT(52) CARRYOVER_SLOT(53) CARRYOVER_SLOT(54) CARRYOVER_SLOT(55)
    CARRYOVER_SLOT(56) CARRYOVER_SLOT(57) CARRYOVER_SLOT(58) CARRYOVER_SLOT(59)
    CARRYOVER_SLOT(60) CARRYOVER_SLOT(61) CARRYOVER_SLOT(62) CARRYOVER_SLOT(63)
    CARRYOVER_SLOT(64) CARRYOVER_SLOT(65) CARRYOVER_SLOT(66) CARRYOVER_SLOT(67)
    virtual void slot68(void (__cdecl *)(Object *,int), int, bool) = 0;
#undef CARRYOVER_SLOT
};
struct CarryoverObjectView {
    char unknown00[0x250]; CarryoverAIView *ai; CarryoverAIView *getAI() const { return ai; }
    char unknown254[0x264-0x254]; Rva003BD306Target *tracker;
    char unknown268[0x284-0x268]; _STL::_Base_bitset<32> upgrades;
    char unknown304[0x468-0x304]; Rva001EAFC1 record;
};
void __cdecl rva0037DCCC(Object *,int);
class CarryoverUnit {
public:
    char unknown00[8]; float experience;
    char unknown0C[4]; _STL::_Base_bitset<32> upgrades;
    char unknown90[4]; Rva001EAFC1 record;
    Object *createSingleObject(Player *);
};
Object *CarryoverUnit::createSingleObject(Player *player)
{
    const ThingTemplate *thingTemplate = (const ThingTemplate *)((Rva0037DCA5 *)this)->GetThingTemplate();
    if (!thingTemplate) return 0;
    bool old = ((CarryoverGameLogicView *)TheGameLogic)->get();
    ((CarryoverGameLogicView *)TheGameLogic)->set(false);
    CreateMask mask;
    memset(&mask,0,sizeof(mask));
    Object *object = TheThingFactory->newObject(thingTemplate,((CarryoverPlayerView *)player)->getTeam(),&mask,(ObjectID)0);
    if (!object) {
        ((CarryoverGameLogicView *)TheGameLogic)->set(old);
        return 0;
    }
    ((Rva0028CBFD *)object)->rva0028CBFD();
    CarryoverObjectView *view = (CarryoverObjectView *)object;
    float value = experience;
    if (value > view->tracker->experience) {
        view->tracker->rva0039B3D1(value,true);
        view->tracker->flag = false;
    }
    const _STL::_Base_bitset<32> *bits = &upgrades;
    view->upgrades._M_do_or(*bits);
    object->updateUpgradeModules();
    Rva001EAFC1 *rec = &view->record;
    *rec = record;
    rec->setReset(0);
    rec->setFlag(false);
    Object *sink = object->rva002931F5(0);
    if (sink && ((CarryoverObjectView *)sink)->getAI() && ((CarryoverObjectView *)sink)->getAI()->slot31())
        ((CarryoverObjectView *)sink)->getAI()->slot68(rva0037DCCC,(int)bits,true);
    ((CarryoverGameLogicView *)TheGameLogic)->set(old);
    return object;
}

// Native single-slot vtable C18D64 holds the existing callback 37DE70.
// 37E07C constructs this eight-byte visitor and returns its counter at+4;
// the 239-byte iteration provider invokes slot0 once per carried unit.
// Original visitor and method names remain unknown.
class Rva0037DE70 {
public:
    Rva0037DE70() : m_count04(0) {}
    virtual int rva0037DE70(int unused);
    int getCount() const { return m_count04; }
private:
    int m_count04;
};
int Rva0037DE70::rva0037DE70(int) { ++m_count04; return 1; }
class Rva0037E07C { public: int rva0037E07C(); };
int Rva0037E07C::rva0037E07C() {
    Rva0037DE70 visitor;
    ((Rva0037DCA5 *)this)->rva0037DF8D((Rva002206F9Sink *)&visitor);
    return visitor.getCount();
}

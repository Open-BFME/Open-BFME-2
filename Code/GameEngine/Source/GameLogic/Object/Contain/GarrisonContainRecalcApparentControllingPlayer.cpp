// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// GarrisonContain::recalcApparentControllingPlayer (0x00479432, 529 bytes),
// after the BFME1/ZH GarrisonContain.cpp body (BFME1 reference revision
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20).
//
// Target facts: entered through the Contain interface at +0x20 (vtable slot
// +0x50). The original team is kept as an ID at +0xFC: it is refreshed from
// the object's team (+0x304, team ID +0x34) when zero or when
// TeamFactory::findTeamByID 0x0039F761 no longer finds it, and cleared when
// the object has no team. With a positive contain count (slot +0x114, arg 0)
// the first occupant from the pair helper 0x0046247D decides the hidden byte
// at +0x9DD (0x002933CD and status 0x11 versus slot +0x124 against the count)
// and gives the object its controlling player's default team (+0x2EC) through
// Object::setTeam 0x00298AE4; otherwise the original team is restored or its
// ID dropped. With a drawable (0x005508E2) condition bit 0x400 of the object
// word at +0x10C is set (notifier 0x0028AE6D) when that occupant is detected
// or the apparent controller (slot +0x4C, local player at ThePlayerList+0x10)
// is the object's controller; the indicator colour (Drawable 0x002741DE) is
// the apparent controller's +0x284 at TheGlobalData+0x134 == 4, else +0x280;
// finally loadGarrisonPoints 0x0047901B runs on the full object when the
// count is positive and +0x9DC is clear.
//
// Carried from the donor: the method name, the m_originalTeam and
// m_hideGarrisonedStateFromNonallies roles and the order of the tests.
// Structural inference: retail shares one 8-byte pair slot between both list
// reads and reuses its second word for the apparent-controller temporary,
// which MSVC 7.1 does when the pair lives in a forced-inline getter; the
// stealth comparison is written in the donor's operand order.
#include <list>

enum ObjectStatusTypes
{
    OBJECT_STATUS_NONE = 0
};

class Object;
class Drawable
{
public:
    void setIndicatorColor(int color);
};

class Team
{
public:
    unsigned int getID() const { return m_id; }
private:
    unsigned char m_pad00[0x34];
    unsigned int m_id; // +0x34
};

class Player
{
public:
    int getPlayerColor() const { return m_color; }
    int getPlayerNightColor() const { return m_nightColor; }
    Team *getDefaultTeam() const { return m_defaultTeam; }
private:
    unsigned char m_pad00[0x280];
    int m_color; // +0x280
    int m_nightColor; // +0x284
    unsigned char m_pad288[0x2EC - 0x288];
    Team *m_defaultTeam; // +0x2EC
};

class PlayerList
{
public:
    Player *getLocalPlayer() { return m_local; }
private:
    unsigned char m_pad00[0x10];
    Player *m_local; // +0x10
};
extern PlayerList *ThePlayerList;

class TeamFactory
{
public:
    Team *findTeamByID(unsigned int id);
};
extern TeamFactory *TheTeamFactory;

struct GlobalData
{
    unsigned char m_pad00[0x134];
    int m_timeOfDay; // +0x134
};
extern GlobalData *TheGlobalData;

struct Rva0046247DPair
{
    void *m00;
    const _STL::list<Object *> *m04;
};
class Rva0046247D
{
public:
    void rva0046247D(Rva0046247DPair &p);
};

class Thing
{
public:
    Drawable *getDrawable() const;
};

class ConditionBits
{
public:
    unsigned int test(int bit) const
    {
        return m_words[bit >> 5] & (1U << (bit & 0x1f));
    }
    void set(int bit)
    {
        m_words[bit >> 5] |= 1U << (bit & 0x1f);
    }
private:
    unsigned int m_words[1];
};

class Object : public Thing
{
public:
    int rva002933CD();
    bool testStatus(ObjectStatusTypes bit) const;
    Player *getControllingPlayer() const;
    void setTeam(Team *team);
    void rva0028AE6D();
    Team *getTeam() const { return m_team; }
    unsigned char m_pad00[0x10C];
    ConditionBits m_conditionBits; // +0x10C
    unsigned char m_pad110[0x304 - 0x110];
    Team *m_team; // +0x304
};

static __forceinline void setCondition(Object *object, int bit)
{
    if (object->m_conditionBits.test(bit) == 0)
    {
        object->m_conditionBits.set(bit);
        object->rva0028AE6D();
    }
}

class B0
{
public:
    virtual void b00();
    int pad4;
    Object *m_object;
};
class B1 { public: virtual void b1(); };
class B2 { public: virtual void b2(); private: unsigned char pad[12]; };
class B3
{
public:
    virtual void c00(); virtual void c01(); virtual void c02(); virtual void c03();
    virtual void c04(); virtual void c05(); virtual void c06(); virtual void c07();
    virtual void c08(); virtual void c09(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15();
    virtual void c16(); virtual void c17(); virtual void c18();
    virtual const Player *getApparentControllingPlayer(const Player *observingPlayer) const;
    virtual void recalcApparentControllingPlayer();
    virtual void c21(); virtual void c22(); virtual void c23();
    virtual void c24(); virtual void c25(); virtual void c26(); virtual void c27();
    virtual void c28(); virtual void c29(); virtual void c30(); virtual void c31();
    virtual void c32(); virtual void c33(); virtual void c34(); virtual void c35();
    virtual void c36(); virtual void c37(); virtual void c38(); virtual void c39();
    virtual void c40(); virtual void c41(); virtual void c42(); virtual void c43();
    virtual void c44(); virtual void c45(); virtual void c46(); virtual void c47();
    virtual void c48(); virtual void c49(); virtual void c50(); virtual void c51();
    virtual void c52(); virtual void c53(); virtual void c54(); virtual void c55();
    virtual void c56(); virtual void c57(); virtual void c58(); virtual void c59();
    virtual void c60(); virtual void c61(); virtual void c62(); virtual void c63();
    virtual void c64(); virtual void c65(); virtual void c66(); virtual void c67();
    virtual void c68();
    virtual unsigned int getContainCount(int unused) const;
    virtual void c70(); virtual void c71(); virtual void c72();
    virtual unsigned int getStealthUnitsContained() const;
};
class B4 { public: virtual void b4(); };
class B5 { public: virtual void b5(); };
class B6 { public: virtual void b6(); };
class B7 { public: virtual void b7(); };
class B8 { public: virtual void b8(); private: unsigned char pad[0xC8 - 4]; };

class OpenContain : public B0, public B1, public B2, public B3, public B4,
    public B5, public B6, public B7, public B8
{
public:
    virtual ~OpenContain();
    Object *getObject() const { return m_object; }
};

class GarrisonContain : public OpenContain
{
public:
    virtual void recalcApparentControllingPlayer();
protected:
    void loadGarrisonPoints();
    __forceinline const _STL::list<Object *> *getContainList()
    {
        Rva0046247DPair pair;
        ((Rva0046247D *)this)->rva0046247D(pair);
        return pair.m04;
    }
private:
    unsigned int m_originalTeamID; // +0xFC
    unsigned char m_pad100[0x9DC - 0x100];
    bool m_garrisonPointsInitialized; // +0x9DC
    bool m_hideGarrisonedStateFromNonallies; // +0x9DD
};

void GarrisonContain::recalcApparentControllingPlayer()
{
    if (getObject()->getTeam())
    {
        if (m_originalTeamID == 0 || TheTeamFactory->findTeamByID(m_originalTeamID) == 0)
            m_originalTeamID = getObject()->getTeam()->getID();
    }
    if (getObject()->getTeam() == 0)
        m_originalTeamID = 0;

    if (getContainCount(0) > 0)
    {
        const _STL::list<Object *> *list = getContainList();
        _STL::list<Object *>::const_iterator it = list->begin();
        Object *rider = *it;
        if (it != list->end() && rider)
        {
            bool detected = (unsigned char)rider->rva002933CD() || rider->testStatus((ObjectStatusTypes)0x11);
            m_hideGarrisonedStateFromNonallies = !detected && getStealthUnitsContained() == getContainCount(0);
            Player *controller = rider->getControllingPlayer();
            Team *team = controller ? controller->getDefaultTeam() : 0;
            if (team)
                getObject()->setTeam(team);
        }
    }
    else
    {
        Team *team = TheTeamFactory->findTeamByID(m_originalTeamID);
        if (team)
            getObject()->setTeam(team);
        else
            m_originalTeamID = 0;
        m_hideGarrisonedStateFromNonallies = false;
    }

    Drawable *draw = getObject()->getDrawable();
    if (draw)
    {
        if (getContainCount(0) > 0)
        {
            const _STL::list<Object *> *list = getContainList();
            _STL::list<Object *>::const_iterator it = list->begin();
            Object *occupant = *it;
            if (it != list->end() && occupant)
            {
                bool detected = (unsigned char)occupant->rva002933CD() || occupant->testStatus((ObjectStatusTypes)0x11);
                if (detected || getApparentControllingPlayer(ThePlayerList->getLocalPlayer()) == getObject()->getControllingPlayer())
                    setCondition(getObject(), 10);
            }
        }

        const Player *controller = getApparentControllingPlayer(ThePlayerList->getLocalPlayer());
        if (controller)
        {
            if (TheGlobalData->m_timeOfDay == 4)
                draw->setIndicatorColor(controller->getPlayerNightColor());
            else
                draw->setIndicatorColor(controller->getPlayerColor());
        }

        if (getContainCount(0) > 0 && !m_garrisonPointsInitialized)
            loadGarrisonPoints();
    }
}


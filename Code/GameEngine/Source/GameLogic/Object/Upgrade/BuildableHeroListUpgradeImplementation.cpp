extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// cl: /Ireference/shims/bfme2_ascii /O1 /Ireference/shims/moduledata /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// BuildableHeroListUpgrade::upgradeImplementation, retail 0x004B837F (83
// bytes): slot 10 of the +0x10 UpgradeMux vtable 0x00C58F70 (the recipe of
// RemoveUpgradeUpgradeRemovalImplementation.cpp). For every name in the
// list the controlling Player's +0x34 object keeps at +0x198, the template
// TheThingFactory finds for it (the pinned ThingFactory::findTemplate) goes to
// the Player's +0x738 member 0x0037F32F (pinned by address) with the Player;
// then TheControlBar is flagged (+0x28) to rebuild and the UpgradeModule
// condition apply 0x004CE4A0 runs (tail call).
// BuildableHeroListUpgrade::upgradeRemovalImplementation, retail 0x004B8484
// (102 bytes), slot 8: for every listed name, the template goes first to the
// class's 0x004B83D2 (which walks the Player's teams; pinned by address) and
// then to the +0x738 member's 0x0037EEB9 (pinned by address); then the same
// TheControlBar flag and the condition removal 0x004CE4A8 (tail call). It
// does not test whether the upgrade is in effect.
#include "ascii_string.h"
#include <vector>
class TeamPrototype;
typedef bool Bool;
class ModuleData;
class ThingTemplate;
struct PlayerTeamNode;
class Player;
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};
extern ThingFactory *TheThingFactory;
class Rva0037F32F
{
public:
	void rva0037F32F(const ThingTemplate *tmpl, Player *player);
	void rva0037EEB9(const ThingTemplate *tmpl);
};
struct Rva004B837FList
{
	unsigned char m_pad000[0x198];
	_STL::vector<AsciiString> m_names;	// +0x198
};
class Player
{
public:
	unsigned char m_pad000[0x34];
	Rva004B837FList *m_34;			// +0x34
	unsigned char m_pad038[0x32C - 0x38];
	PlayerTeamNode *m_teamHead;
	unsigned char m_pad330[0x738 - 0x330];
	Rva0037F32F m_738;			// +0x738
};
class Object
{
public:
	Player *getControllingPlayer() const;
    void *rva0028BC58(int arg);
    int vptr;
    const ThingTemplate *m_template;
};
class ControlBar
{
public:
	unsigned char m_pad00[0x28];
	Bool m_28;				// +0x28
};
extern ControlBar *TheControlBar;
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	Object *getObject() const { return m_object; }
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
class UpgradeMuxIface
{
public:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void m01() = 0;
	virtual void m02() = 0;
	virtual void m03() = 0;
	virtual void m04() = 0;
	virtual void m05() = 0;
	virtual void m06() = 0;
	virtual void m07() = 0;
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
public:
	void rva004CE4A0();
	void rva004CE4A8();
};
class BuildableHeroListUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
	void rva004B83D2(const ThingTemplate *tmpl);
};
void BuildableHeroListUpgrade::upgradeImplementation()
{
	Player *player = getObject()->getControllingPlayer();
	_STL::vector<AsciiString> &names = player->m_34->m_names;
	for (_STL::vector<AsciiString>::iterator it = names.begin(); it != names.end(); ++it)
	{
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(*it);
		player->m_738.rva0037F32F(tmpl, player);
	}
	TheControlBar->m_28 = true;
	rva004CE4A0();
}
void BuildableHeroListUpgrade::upgradeRemovalImplementation()
{
	Player *player = getObject()->getControllingPlayer();
	_STL::vector<AsciiString> &names = player->m_34->m_names;
	Rva0037F32F *holder = &player->m_738;
	for (_STL::vector<AsciiString>::iterator it = names.begin(); it != names.end(); ++it)
	{
		const ThingTemplate *tmpl = TheThingFactory->findTemplate(*it);
		rva004B83D2(tmpl);
		holder->rva0037EEB9(tmpl);
	}
	TheControlBar->m_28 = true;
	rva004CE4A8();
}

// TeamPrototype and DLINK walks follow the independently matched Player
// force-emotion and TeamPrototype iterator units. Retail establishes +32C
// prototype list and +334 team head; Object iterator is the 24-byte ABI of
// the matched iterate/advance providers (its PMF representation is opaque).
template <class T> class DLINK_ITERATOR
{
public:
    typedef T *(T::*GetNextFunc)() const;
    DLINK_ITERATOR(T *cur, GetNextFunc next) : m_cur(cur), m_next(next) {}
    bool done() const { return m_cur == 0; }
    T *cur() const { return m_cur; }
    void advance() { if (m_cur) m_cur = (m_cur->*m_next)(); }
private:
    T *m_cur;
    GetNextFunc m_next;
};
template <> class DLINK_ITERATOR<Object>
{
public:
    void advance();
    bool done() const { return m_cur == 0; }
    Object *cur() const { return m_cur; }
private:
    Object *m_cur;
    unsigned char m_state[20];
};
class MemoryPoolObject { public: virtual ~MemoryPoolObject(); };
#include "Common/Snapshot.h"
class Team : public MemoryPoolObject, public Snapshot
{
public:
    Team *dlink_next_TeamInstanceList() const;
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
class TeamPrototype
{
public:
    DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
    {
        return DLINK_ITERATOR<Team>(m_head, &Team::dlink_next_TeamInstanceList);
    }
private:
    char pad[0x334];
    Team *m_head;
};
struct PlayerTeamNode
{
    PlayerTeamNode *next, *prev;
    TeamPrototype *value;
};
class ThingTemplate
{
public:
    char pad[0x10C];
    unsigned m_kind[7];
};
template <int N> class Rva004B83D2Slots : public Rva004B83D2Slots<N - 1>
{
public:
    virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004B83D2Slots<0> {};
class Rva004B83D2Query : public Rva004B83D2Slots<13>
{
public:
    virtual void remove(const ThingTemplate *tmpl, bool flag) = 0; // slot34
    virtual void f14() = 0;
    virtual void f15() = 0;
    virtual void f16() = 0;
    virtual unsigned count() const = 0; // slot44
};
// Retail 4B83D2..4B8484, called with each template by matched removal.
// Native condition is template+10C bit31, query(0) then unsigned slot44>0,
// and slot34(template,0). Original query type and its public methods are
// unresolved; the module's established class identity and neutral helper
// name are retained separately from these structural target facts.
void BuildableHeroListUpgrade::rva004B83D2(const ThingTemplate *tmpl)
{
    Player *player = getObject()->getControllingPlayer();
    for (PlayerTeamNode *node = player->m_teamHead->next; node != player->m_teamHead; node = node->next)
    {
        for (DLINK_ITERATOR<Team> teams = node->value->iterate_TeamInstanceList(); !teams.done(); teams.advance())
        {
            Team *team = teams.cur();
            if (!team)
                continue;
            for (DLINK_ITERATOR<Object> objects = team->iterate_TeamMemberList(); !objects.done(); objects.advance())
            {
                Object *obj = objects.cur();
                if (obj->m_template->m_kind[0] & 0x80000000u)
                {
_ReadWriteBarrier();
                    Rva004B83D2Query *query = (Rva004B83D2Query *)obj->rva0028BC58(0);
                    if (query && query->count() > 0)
                        query->remove(tmpl, false);
                }
            }
        }
    }
}

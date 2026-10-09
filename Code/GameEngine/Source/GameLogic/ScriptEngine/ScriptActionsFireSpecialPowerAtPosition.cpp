// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /arch:SSE /G7 /DNDEBUG /MD
// BFME1 f98983a7d ScriptActions_FireSpecialPowerHelper.cpp supplies the
// player/prototype/instance/member traversal and first matching power fire.
// Target 3C069B..3C075B independently proves full int mask, Player list32C,
// prototype instance334, member lookup28BB9E and module slot12(location,40000).
// WB names this FireSpecialPowerAtPosition. Existing BfmeApplierBH spelling
// remains the owner so callers need no competing name/address binding.
#include "ascii_string.h"
#include "../../../../Libraries/Include/Lib/Coord3D.h"
class MemoryPoolObject { public: virtual ~MemoryPoolObject(); };
#include "Common/Snapshot.h"
class SpecialPowerTemplate;
class SpecialPowerModuleInterface
{
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(const Coord3D *position, int options);
};
class Object
{
public:
    SpecialPowerModuleInterface *getSpecialPowerModule(const SpecialPowerTemplate *power) const;
};
// Native rowed member iterator returns24B. Only its current Object is read
// here; its opaque20B callback state is retained for the out-of-line advance.
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
    OBJCLASS *m_cur;
    unsigned char m_state[20];
public:
    void advance();
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};
class Team : public MemoryPoolObject, public Snapshot
{
public:
    Team *dlink_next_TeamInstanceList() const;
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
};
// The target's function word and zero adjustment, also witnessed by
// TeamPrototypeTeamIterators.cpp, are Team's8B multiple-base member pointer.
class Rva003C069BTeamIterator
{
public:
    typedef Team *(Team::*GetNextFunc)() const;
    Rva003C069BTeamIterator(Team *current, GetNextFunc next)
        : m_cur(current), m_next(next) {}
    bool done() const { return m_cur == 0; }
    Team *cur() const { return m_cur; }
    void advance()
    {
        if (m_cur)
            m_cur = (m_cur->*m_next)();
    }
private:
    Team *m_cur;
    GetNextFunc m_next;
};
struct Rva003C069BPrototype
{
    unsigned char pad00[0x334];
    Team *instances;
};
struct Rva003C069BPrototypeNode
{
    Rva003C069BPrototypeNode *next;
    Rva003C069BPrototypeNode *previous;
    Rva003C069BPrototype *prototype;
};
class Player
{
public:
    unsigned char pad00[0x32C];
    Rva003C069BPrototypeNode *teams;
};
class PlayerList
{
public:
    Player *getEachPlayerFromMask(int &mask);
};
extern PlayerList *ThePlayerList;
class ScriptEngine
{
public:
    int rva00357475(const AsciiString &name, bool *special);
};
extern ScriptEngine *TheScriptEngine;
class BfmeSubBH { unsigned char pad00[4]; };
class BfmeApplierBH
{
public:
    bool bfmeApplyBH(void *owner, void *found, BfmeSubBH *position) throw();
};
bool BfmeApplierBH::bfmeApplyBH(void *owner, void *found, BfmeSubBH *position) throw()
{
    int mask = TheScriptEngine->rva00357475(*reinterpret_cast<const AsciiString *>(owner), 0);
    while (mask)
    {
        Player *player = ThePlayerList->getEachPlayerFromMask(mask);
        if (!player)
            continue;
        for (Rva003C069BPrototypeNode *node = player->teams->next;
            node != player->teams; node = node->next)
        {
            Rva003C069BTeamIterator teams(node->prototype->instances, &Team::dlink_next_TeamInstanceList);
            for (; !teams.done(); teams.advance())
            {
                Team *team = teams.cur();
                if (!team)
                    continue;
                for (DLINK_ITERATOR<Object> objects = team->iterate_TeamMemberList();
                    !objects.done(); objects.advance())
                {
                    Object *object = objects.cur();
                    if (!object)
                        continue;
                    SpecialPowerModuleInterface *module = object->getSpecialPowerModule(
                        reinterpret_cast<const SpecialPowerTemplate *>(found));
                    if (module)
                    {
                        module->s12(reinterpret_cast<const Coord3D *>(position), 0x40000);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// ?rva0059A153@Rva0059A153@@QAEXPAVTeamPrototype@@@Z
// partial score=0.85 date=2026-10-08
// cl: /O1 /G7 /Oy- /MD /Ireference/shims/moduledata /D_STLP_USE_STATIC_LIB
// stlport
// Native 0x0059A153..0x0059A1C1 (110 bytes): find a TeamPrototype in the
// pointer vector at receiver+8, mark and disband its Team list, then erase it.
// The forwarder 0x004EC07D establishes the TeamPrototype argument. Team list
// head +0x334, flag bytes +0x5D/+0x5E and member callback are target accesses.
// The owner's name and flag semantics remain unresolved. The two-base
// member-pointer representation follows the already verified Team iterators.
#include <vector>
class MemoryPoolObject { public: virtual ~MemoryPoolObject(); };
#include "Common/Snapshot.h"
class Team : public MemoryPoolObject, public Snapshot
{
public:
    Team *dlink_next_TeamInstanceList() const;
    void disband();
    void mark()
    {
        if (!flag5D) { flag5E=true; flag5D=true; }
    }
private:
    char prefix08[0x5D-8];
    bool flag5D, flag5E;
};
template<class T> class DLINK_ITERATOR
{
    T *current;
    typedef T *(T::*Next)() const;
    Next next;
public:
    DLINK_ITERATOR(T *first,Next fn):current(first),next(fn) {}
    bool done() const { return !current; }
    T *cur() const { return current; }
    void advance() { if(current) current=(current->*next)(); }
};
class TeamPrototype
{
    char prefix[0x334];
    Team *first;
public:
    DLINK_ITERATOR<Team> iterate() const
    { return DLINK_ITERATOR<Team>(first,&Team::dlink_next_TeamInstanceList); }
};
// Existing 4-byte-element search provider; this declaration describes its
// machine ABI without assigning its CreateAHeroData owner identity to teams.
extern int __cdecl rva0020E873(int,int,int *);
class Rva0059A153
{
    char prefix[8];
    _STL::vector<TeamPrototype *> prototypes;
public:
    void rva0059A153(TeamPrototype *prototype);
};
// ?rva0059A153 present-unmatched
void Rva0059A153::rva0059A153(TeamPrototype *prototype)
{
    _STL::vector<TeamPrototype *> &items=prototypes;
    TeamPrototype **end=items.end();
    TeamPrototype **found=(TeamPrototype **)rva0020E873(
        (int)items.begin(),(int)end,(int *)&prototype);
    if(found!=end)
    {
        for(DLINK_ITERATOR<Team> i=(*found)->iterate();!i.done();i.advance())
        { i.cur()->mark(); i.cur()->disband(); }
        items.erase(found);
    }
}

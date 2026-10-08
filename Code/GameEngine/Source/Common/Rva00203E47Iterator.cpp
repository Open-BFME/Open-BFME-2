// cl: /MD /DNDEBUG
// Target boundary 0x00203E47-0x00203E65 is bracketed by independent returns.
// Reference lead: GeneralsMD Common/GameCommon.h DLINK_ITERATOR and
// Common/RTS/Player.cpp through open-bfme-1 revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76. The member-function-pointer
// representation supplies the return-by-value iterator structure. Target
// reads head+0x334 and stores callback VA0x009C4AF5 plus zero adjustment.
// That VA is Team::dlink_next_TeamInstanceList at RVA0x005C4AF5 (rowed in
// TeamPrototypeTeamIterators.cpp, whose walks pass the same accessor); the
// iterator and owner views keep their address-derived names.
// MSVC's eight-byte member pointer leaves the return structure's +4 gap intact.
#pragma pointers_to_members(full_generality, multiple_inheritance)
class Team;
typedef Team *(Team::*Rva00203E47Next)() const;
class Team { public: Team *dlink_next_TeamInstanceList() const; };
struct Rva00203E47IteratorView
{
    void *current;
    Rva00203E47Next next;
    // Native25B constructor at 0x00203C7A. The preceding rowed 89B body
    // at 0x00203C21 returns at 0x00203C79; rowed iterator advance begins
    // at 0x00203C93 and reads current/+8 callback/+C adjustment. Its member
    // type and owner remain address-derived; no original template name claimed.
    Rva00203E47IteratorView(void *p, Rva00203E47Next f) : current(p), next(f) {}
};
typedef char Rva00203E47SizeCheck[(sizeof(Rva00203E47IteratorView)==16)?1:-1];
class Rva00203E47OwnerView
{
    char unknown[0x334];
    void *head;
public:
    Rva00203E47IteratorView iterate() const;
};
Rva00203E47IteratorView Rva00203E47OwnerView::iterate() const
{
    return Rva00203E47IteratorView(head, &Team::dlink_next_TeamInstanceList);
}


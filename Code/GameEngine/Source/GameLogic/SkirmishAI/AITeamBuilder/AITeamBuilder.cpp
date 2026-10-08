// cl: /O1 /MD /DNDEBUG /EHs /arch:SSE
// Native 599F74..599FAA, 54B; WB1529260 AITeamBuilder::getTeamForAIPrototype
// asserts157..166 and prototype head334 establish the team-instance walk.
// Preserve the existing caller pin and address-derived receiver ABI.
// The 8-byte multiple-inheritance member pointer has a zero adjustment;
// callback Team::dlink_next_TeamInstanceList is the rowed getter5C4AF5.
#pragma pointers_to_members(full_generality, multiple_inheritance)
class Team { public: Team *dlink_next_TeamInstanceList() const; };
template<class T> class DLINK_ITERATOR {
 typedef T *(T::*Next)() const;
 T *current;
 Next next;
public:
 DLINK_ITERATOR(T *p, Next f):current(p),next(f){}
 void advance() { if (current) current=((*current).*next)(); }
 bool done() const { return current==0; }
 T *cur() const { return current; }
};
class TeamPrototype {
 char prefix[0x334]; Team *head;
public:
 DLINK_ITERATOR<Team> iterate_TeamInstanceList() const { return DLINK_ITERATOR<Team>(head,&Team::dlink_next_TeamInstanceList); }
};
class Rva0059AC4D { public: Team *rva00599F74(TeamPrototype *); };
Team *Rva0059AC4D::rva00599F74(TeamPrototype *prototype)
{
 Team *first=0;
 for(DLINK_ITERATOR<Team> it=prototype->iterate_TeamInstanceList(); !it.done(); it.advance()) {
  if (!first) first=it.cur();
 }
 return first;
}

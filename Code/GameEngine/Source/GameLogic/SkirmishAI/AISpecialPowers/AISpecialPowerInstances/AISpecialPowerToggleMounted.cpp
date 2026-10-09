// cl: /O1 /G7 /MD /DNDEBUG
// Native5D9BCC..5D9C5A RET4 and WB159B360 assertion/iteration/body agree.
// Rowed ctor5D9B93 and dtor5D9BA5 install table8763D8; slot6 is5D9BCC.
// Slots0..5 remain unnamed in this observed call view; no class size is asserted.
// Target exposes team304/player default team2EC and ridden object274. The
// ridden template bit115:20 excludes that member from the two counters;
// template520 value3 splits the rest. KindD6 selects the opposite comparison.
// The established Team iterator ABI is24B; only its current-object word is
// observed here. The remaining20B stay opaque and are passed to rowed advance.
enum KindOfType { KIND_TOGGLE_MOUNTED=0xD6 };
class Team;
class Player {public:char unknown[0x2ec];Team *defaultTeam;};
struct ToggleMountedTemplate {char pad[0x115];unsigned char exclude;char rest[0x520-0x116];int category;};
class Object {public:
 Player *getControllingPlayer() const;
 bool isKindOf(KindOfType) const;
 char pad0[4];ToggleMountedTemplate *objectTemplate;
 char pad8[0x274-8];Object *riddenObject;
 char pad278[0x304-0x278];Team *team;
};
template<class T> class DLINK_ITERATOR {public:
 void advance();bool done() const {return current==0;}T *cur() const {return current;}
 private:T *current;char unknownState[20];
};
class Team {public:DLINK_ITERATOR<Object> iterate_TeamMemberList() const;};
class AISpecialPowerToggleMounted {public:
 virtual void slot0();virtual void slot1();virtual void slot2();
 virtual void slot3();virtual void slot4();virtual void slot5();
 virtual bool shouldActivate(Object *);
};
bool AISpecialPowerToggleMounted::shouldActivate(Object *source) {
 Team *team=source->team;
 if(team!=source->getControllingPlayer()->defaultTeam) {
 int categoryThree=0,other=0;
 for(DLINK_ITERATOR<Object> it=team->iterate_TeamMemberList();!it.done();it.advance()) {
  Object *member=it.cur();
  if(member->riddenObject&&(member->riddenObject->objectTemplate->exclude&0x20)) continue;
  if(member->objectTemplate->category==3) ++categoryThree;else ++other;
 }
 if(!source->isKindOf(KIND_TOGGLE_MOUNTED)) return categoryThree>other;
 return other>categoryThree;
 }
 return false;
}

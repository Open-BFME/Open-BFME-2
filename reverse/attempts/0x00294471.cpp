// ?rva00294471@Object@@QAE_NPAXH@Z
// partial score=0.889067405355494 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native294471..2946AB RET8; owned Object callers and neutral existing pin
// establish Object receiver and pointer-word formals. Player pointer role is
// native getRelationship(Team) usage; original method and mode names unknown.
class Team;
enum Relationship {ENEMIES=0,NEUTRAL=1,ALLIES=2};
class Player {public:Relationship getRelationship(const Team*)const;char p[0x2ec];Team*team;};
class PlayerList {public:Player*getNthPlayer(int);};extern PlayerList*ThePlayerList;
enum ObjectStatusTypes {STATUS15=15,STATUS17=17};
class Object;
struct ObjectNode {ObjectNode*next,*prev;Object*value;};
struct ObjectList {ObjectNode*head;};
struct ObjectListView {void*first;const ObjectList*list;};
#define V(n) virtual void s##n();
#define V10(n) V(n##0) V(n##1) V(n##2) V(n##3) V(n##4) V(n##5) V(n##6) V(n##7) V(n##8) V(n##9)
class ContainView {public:
 V10(0) V(10) V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18)
 virtual Player*playerFor(Player*);
 V10(2) virtual ContainView*child();
 V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V10(4) V10(5)
 V(60) V(61) V(62) V(63) V(64) V(65) virtual void listA(ObjectListView*);
 V(67) V(68) virtual int countFor(int);virtual void listB(ObjectListView*);V(71) V(72) virtual int count();
};
struct ThingTemplate {char p[0x113];unsigned char b113;char b114;unsigned char b115;};
class Rva00373EC6 {public:char p[0x38];int playerIndex;int active;};
class Object {public:
 Player*getControllingPlayer()const;bool rva0028F518();bool testStatus(ObjectStatusTypes)const;int rva002933CD();Rva00373EC6*rva0028F4BC();bool rva00294471(void*,int);
 char p[4];const ThingTemplate*tmpl;char q[0x250-8];ContainView*contain;
};
bool Object::rva00294471(void*arg,int mode){
 Player*player=arg?(Player*)arg:(Player*)arg;ObjectListView view;
 if(mode==1){Player*owner=getControllingPlayer();if(owner && player->getRelationship(owner->team)==ALLIES)return false;}
 {
 if(!rva0028F518() && (!testStatus(STATUS15) || testStatus(STATUS17))){
  if(mode==1){Player*owner=getControllingPlayer();if(!owner || player->getRelationship(owner->team)!=ENEMIES)return false;}
  if(tmpl->b115&0x20){
   ContainView*base=contain;if(base){ContainView*sub=base->child();if(sub){
    sub->listA(&view);bool any=false;
    ObjectNode*endNode=view.list->head;for(ObjectNode*n=endNode->next;n!=endNode;n=n->next){
     Object*obj=n->value;if(obj){if(!obj->rva0028F518() || !obj->testStatus(STATUS15) || (unsigned char)obj->rva002933CD() || obj->testStatus(STATUS17))goto accept;any=true;}
    }
    if(any)return false;goto accept;
   }}
  }
  ContainView*current=contain;if(!current)goto accept;
  Player*owner=current->playerFor(player);int n=current->countFor(0);if(current->count()!=n)goto accept;
  current->listB(&view);ObjectNode*first=view.list->head->next;if(first==view.list->head)goto accept;
  Object*obj=first->value;if(!obj || (unsigned char)obj->rva002933CD() || obj->testStatus(STATUS17))goto accept;
  if(owner && player->getRelationship(owner->team)==ENEMIES)return false;
  goto accept;
 }
 if(!(tmpl->b113&1))return false;
 Rva00373EC6*effect=rva0028F4BC();if(effect && effect->active){Player*owner=ThePlayerList->getNthPlayer(effect->playerIndex);if(player && owner)return (unsigned char)(player->getRelationship(owner->team)==ENEMIES);}
 if(mode==1){Player*owner=getControllingPlayer();if(!owner || player->getRelationship(owner->team)!=ENEMIES)return false;}
 goto accept;
 }
accept:return true;
}

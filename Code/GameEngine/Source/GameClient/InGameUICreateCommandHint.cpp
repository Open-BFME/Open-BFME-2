// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
// ?createCommandHint@InGameUI@@UAEXPBVGameMessage@@@Z @0x002A3273 1426B (the
// code plus its 28-entry mouse-mode jump table at 0x002A3795).
// Identity (target): retail InGameUI vtables at RVA 0x007C7AB0 and 0x007FD438
// both hold this body in slot 22, between createMouseoverHint (slot 21,
// 0x0029EBE2) and createGarrisonHint (slot 23, 0x0029A7C4), the ZH order of
// InGameUI's hint virtuals.
// Structure (donor): BFME 1 InGameUICreateCommandHint.cpp (Open-BFME-1
// 0x00445080): hover/selection setup, the GUI-command mouse modes and the
// action-type cursor switch. BFME 2 adds the hero-ability path that gathers the
// hovered drawables' ObjectIDs into a local pooled list for AiOrdersManager.
// The list's base constructor is defined in the class like STLport's
// _List_base(const allocator_type &) and compiles to retail 0x0029FB3B; retail's
// caller frame (allocator temp in the dead msg slot) needs that body in view.
// Not inline-expanded under /O1.
#include <list>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Lib/ICoord2D.h"
class Drawable;class Object;class GameMessage;class GameWindow;
class RecorderClass;class Player;class CommandButton;
class Bfme939Helper {public:int get() const;};
extern RecorderClass *TheRecorder;
struct HintTemplateView {char pad108[0x108];unsigned char kind108;char pad109[6];unsigned char kind10f;};
enum CellShroudStatus {SHROUD_NONE=0};
class Object {public:char pad0[4];HintTemplateView *type;char pad8[0x6c];unsigned id;bool isLocallyControlled() const;CellShroudStatus getShroudStatusForPlayer(int) const;};
union GameMessageArgumentType {int integer;};
class GameMessage {public:char pad10[0x10];int type;const GameMessageArgumentType *getArgument(int) const;};
#include "../../Include/GameClient/Mouse.h"
extern Mouse *TheMouse;
class Player {public:char pad54[0x54];int index;char pad58[0x6f8];int value750;bool hasRadar() const;};
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
#include "../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;
class Radar {public:char pad10[0x10];bool hidden,forced;char pad12[0x1430-0x12];GameWindow *window;int isRadarWindow(GameWindow *);};
extern Radar *TheRadar;
class Rva0029A224 {public:int isRadarWindow(GameWindow *);};
#include "../../Include/Common/Rva00222A8BTarget.h"
class BfmeAptWindowManager;extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva0029B313 {public:void rva0029B313(int);};
struct DNode {DNode *next,*prev;Drawable *value;};
struct DList {DNode *head;Drawable *front() const {return head->next->value;}};
struct IdNode {IdNode *next,*prev;unsigned value;};
enum ObjectID {INVALID_OBJECT_ID=0};
// STLport list<ObjectID> over the game's pooled 12-byte nodes (pool at VA
// 0x00DA60E8). Its out-of-line members are retail bodies the ledger already
// names: the allocator-taking base constructor 0x0029FB3B, the destructor
// 0x00268902 and the four-byte element insert 0x002A1316.
class FreelistProxyHead {public:void setup(const void *alloc,void *head);};
class FreelistPool
{
public:
	void *pop();
	int m_00; // +0x00
	void *m_04; // +0x04
	void *m_head; // +0x08
};
extern FreelistPool g_freelistPool;
class PoolMember {public:void Rva00268902() throw();};
struct Rva0029FB3BAlloc {Rva0029FB3BAlloc(){} Rva0029FB3BAlloc(const Rva0029FB3BAlloc &){} ~Rva0029FB3BAlloc(){}};
struct Rva002A1316Iterator {IdNode *node;Rva002A1316Iterator(IdNode *n):node(n){} Rva002A1316Iterator(const Rva002A1316Iterator &o):node(o.node){}};
class Rva0029FB3BMember {public:
 Rva0029FB3BMember(const Rva0029FB3BAlloc &)
 {
  char nodeAlloc;
  ((FreelistProxyHead *)this)->setup(&nodeAlloc,0);
  IdNode *idNode=(IdNode *)g_freelistPool.pop();
  idNode->next=idNode;
  idNode->prev=idNode;
  node=idNode;
 }
 __declspec(dllimport) __forceinline ~Rva0029FB3BMember(){((PoolMember *)this)->Rva00268902();}
 IdNode *node;
};
class Rva002A1B6FNativeList : public Rva0029FB3BMember {public:
 Rva002A1B6FNativeList(const Rva0029FB3BAlloc &allocator=Rva0029FB3BAlloc()):Rva0029FB3BMember(allocator){}
 ~Rva002A1B6FNativeList(){}
 void push_back(void *const &value){insert(end(),value);}
 unsigned size() const {unsigned count=0;for(IdNode *i=node->next;i!=node;i=i->next)++count;return count;}
private:
 Rva002A1316Iterator end(){return node;}
 Rva002A1316Iterator insert(Rva002A1316Iterator,void *const &);
};
class CreateAHeroData;
class AiOrdersManager {public:void *rva0035538C(const Coord3D &,int,const _STL::list<CreateAHeroData *> *);};
extern AiOrdersManager *TheAiOrdersManager;
class CommandButton {public:char pad14[0x14];int command;char pad18[4];unsigned options;char pad20[0x24];void *special;char pad48[4];int radius;AsciiString cursor,invalid;char pad58[0x28];int weapon;bool isContextCommand() const;};
bool CanSelectDrawable(const Drawable *,bool);
class GameClient {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual Drawable *findDrawableByID(unsigned);

};
extern GameClient *TheGameClient;
class GameWindow {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual bool rvaVirtual18();
unsigned winGetStatus();GameWindow *winGetParent();
};
class GameWindowManager {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void slot22();
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual void slot73();
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual GameWindow *getWindowUnderCursor(int,int,bool);

};
extern GameWindowManager *TheWindowManager;
#include "../../Include/GameClient/View.h"
#include "../../Include/GameClient/Drawable.h"
extern View *TheTacticalView;
class InGameUI {public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void slot17();
 virtual void slot18();
 virtual void slot19();
 virtual void slot20();
 virtual void slot21();
 virtual void createCommandHint(const GameMessage *msg);
 virtual void slot23();
 virtual void slot24();
 virtual void slot25();
 virtual void slot26();
 virtual void slot27();
 virtual void slot28();
 virtual void slot29();
 virtual void slot30();
 virtual void slot31();
 virtual void slot32();
 virtual void slot33();
 virtual void slot34();
 virtual void slot35();
 virtual void slot36();
 virtual void slot37();
 virtual void slot38();
 virtual void slot39();
 virtual void slot40();
 virtual void slot41();
 virtual void slot42();
 virtual void slot43();
 virtual void slot44();
 virtual void slot45();
 virtual void slot46();
 virtual void slot47();
 virtual void slot48();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void slot55();
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void slot64();
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void slot68();
 virtual void slot69();
 virtual int getSelectCount();
 virtual void slot71();
 virtual void slot72();
 virtual const DList *getAllSelectedDrawables() const;
 virtual void slot74();
 virtual void slot75();
 virtual void slot76();
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void radiusCursor(int,void *,int,bool);
 virtual void clearRadius();
char pad4[0x234];CommandButton *pending;char pad23c[0x5c0];int mouseMode;char pad800[4];unsigned mousedOver;
};

#define CURSOR(n) ((Rva0029B313 *)this)->rva0029B313(n)
void InGameUI::createCommandHint(const GameMessage *msg)
{
 if (((Bfme939Helper *)TheRecorder)->get()==1) return;
 const Drawable *draw=TheGameClient->findDrawableByID(mousedOver);
 int messageType=msg->type;
 if (draw && (messageType==0xa7 || messageType==0xc0)) {
  const Object *obj=draw->getObject();
  int localPlayerIndex=ThePlayerList?ThePlayerList->m_local->index:0;
  CellShroudStatus ss=!obj?(CellShroudStatus)0:obj->getShroudStatusForPlayer(localPlayerIndex);
  if(ss==4)messageType=0xb3;
 }
 GameWindow *window=0;
 unsigned char underWindow=((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222A53();
 if(!underWindow) {
  const ICoord2D *io=&TheMouse->field4F0C;
  if(io && TheWindowManager)window=TheWindowManager->getWindowUnderCursor(io->x,io->y,false);
  while(window) {
   if(window->rvaVirtual18()){underWindow=false;break;}
   if(!(window->winGetStatus()&0x10000)){underWindow=true;break;}
   window=window->winGetParent();
  }
 }
 const Object *obj=draw?draw->getObject():0;
 bool drawSelectable=CanSelectDrawable(draw,false);
 if(!obj)drawSelectable=false;
 const Drawable *srcDraw=0;
 const Object *srcObj=0;
 if(getSelectCount()==1){srcDraw=getAllSelectedDrawables()->front();srcObj=srcDraw?srcDraw->getObject():0;}
 switch(mouseMode){
 case 0:
  if(underWindow || (srcObj&&!srcObj->isLocallyControlled())){CURSOR(2);return;}
  if(messageType==0xb3 || messageType==0xb4) {
   const DList *list=getAllSelectedDrawables();
   if(list) {
    int value=ThePlayerList->m_local->value750;
    Rva002A1B6FNativeList ids;
    DNode *end=list->head;
    for(DNode *i=end->next;i!=end;i=i->next){ObjectID id=(ObjectID)i->value->getObject()->id;ids.push_back(*(void *const *)&id);}
    if(ids.size()>0){
     Coord3D position;Coord3D *wp=&position;const ICoord2D *io=&TheMouse->field4F0C;
     TheTacticalView->screenToTerrain(io,wp,false);
     if(TheAiOrdersManager->rva0035538C(*wp,value,(const _STL::list<CreateAHeroData *> *)&ids)){CURSOR(0x37);return;}
    }
   }
  }
  switch(messageType) {
  case 0xb3:
   if(!drawSelectable && srcObj && srcObj->isLocallyControlled() && (srcObj->type->kind108&0x80))
    CURSOR(0xc);
   else if(drawSelectable && obj->isLocallyControlled() && !(obj->type->kind10f&0x10))
    CURSOR(0xd);
   else {
    Radar *radar=TheRadar;
    if((unsigned char)radar->isRadarWindow(window) && !radar->forced &&
       (radar->hidden || !ThePlayerList->m_local->hasRadar()))
     CURSOR(2);
    else CURSOR(5);
   }
   break;
  case 0xb4:
   if(drawSelectable && obj->isLocallyControlled()) CURSOR(0xd);
   else CURSOR(6);
   break;
  case 0xb5: CURSOR(0x22); break;
  case 0xa7: CURSOR(7); break;
  case 0xc0: CURSOR(0x23); break;
  case 0xa9: CURSOR(8); break;
  case 0xaa: CURSOR(9); break;
  case 0xab: CURSOR(0x11); break;
  case 0xb1: CURSOR(0x1d); break;
  case 0xb2: CURSOR(0x2e); break;
  case 0xac: CURSOR(0x12); break;
  case 0xad: CURSOR(0x13); break;
  case 0xae: CURSOR(0x14); break;
  case 0xaf: CURSOR(0xe); break;
  case 0xb0: CURSOR(0xf); break;
  case 0xb6:
  case 0xb8: CURSOR(0xf); break;
  case 0xbb: CURSOR(0x1c); break;
  case 0xb9: CURSOR(0x15); break;
  case 0xa8: CURSOR(0xc); break;
  case 0xbc:
   if(!drawSelectable) CURSOR(0x10);
   else CURSOR(0xd);
   break;
  case 0xbd: CURSOR(0x27); break;
  case 0xbe: CURSOR(5); break;
  case 0xbf: CURSOR(0xc); break;
  case 0xc1: CURSOR(0x35); break;
  case 0xc2: CURSOR(0x36); break;
  case 0x7d6: CURSOR(msg->getArgument(1)->integer); break;
  case 0x7d7: CURSOR(0x29); break;
  case 0x7d8: CURSOR(0x30); break;
  }
  break;
 case 1:
  if(underWindow){CURSOR(2);return;}
  switch(messageType){
  case 0xb3: case 0xb4: case 0x432: CURSOR(0xa); break;
  case 0xa7: case 0xc0: CURSOR(0xb); break;
  }
  break;
 case 2:
  if(underWindow){CURSOR(2);return;}
  if(pending){
   if(pending->isContextCommand() || pending->command==0x18 ||
      pending->command==0x26 || pending->command==0x20 ||
      pending->command==0x1f){
    int radius=pending->radius;
    if(radius==0){
     clearRadius();
     int index;
     switch(messageType){
     case 0xa4: index=TheMouse->getCursorIndex(pending->cursor); break;
     default: index=TheMouse->getCursorIndex(pending->invalid); break;
     }
     if(index!=-1) CURSOR(index); else CURSOR(4);
    } else {
     CURSOR(0);
     radiusCursor(radius,pending->special,pending->weapon,messageType==0xa4);
    }
   } else if(pending->options&0x227){
    int radius=pending->radius;
    if(radius==0){
     clearRadius();
     int index=TheMouse->getCursorIndex(pending->cursor);
     if(index!=-1) CURSOR(index); else CURSOR(4);
    } else {
     CURSOR(0);
     radiusCursor(radius,pending->special,pending->weapon,true);
    }
   } else clearRadius();
  }
  break;
 }
}



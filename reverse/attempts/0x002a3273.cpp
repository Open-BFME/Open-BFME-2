// ?rva002A3273@InGameUI@@QAEXPBVGameMessage@@@Z
// partial score=0.7 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
#include <list>
#include "ascii_string.h"
#include "Lib/Coord3D.h"
struct ICoord2D {int x,y;};
class Drawable;class Object;class GameMessage;class GameWindow;
class RecorderClass;class Player;class CommandButton;
class Bfme939Helper {public:int get() const;};
extern RecorderClass *TheRecorder;
struct HintTemplateView {char pad108[0x108];unsigned char kind108;char pad109[6];unsigned char kind10f;};
enum CellShroudStatus {SHROUD_NONE=0};
class Object {public:char pad0[4];HintTemplateView *type;char pad8[0x6c];unsigned id;bool isLocallyControlled() const;CellShroudStatus getShroudStatusForPlayer(int) const;};
class Drawable {public:char padFC[0xfc];Object *object;};
union GameMessageArgumentType {int integer;};
class GameMessage {public:char pad10[0x10];int type;const GameMessageArgumentType *getArgument(int) const;};
class Mouse {public:char pad4f0c[0x4f0c];ICoord2D pos;int getCursorIndex(const AsciiString &);};
extern Mouse *TheMouse;
class Player {public:char pad54[0x54];int index;char pad58[0x6f8];int value750;bool hasRadar() const;};
class PlayerList {public:char pad10[0x10];Player *local;};
extern PlayerList *ThePlayerList;
class Radar {public:char pad10[0x10];bool hidden,forced;char pad12[0x1430-0x12];GameWindow *window;int rva0029A224(GameWindow *);};
extern Radar *TheRadar;
class Rva0029A224 {public:int rva0029A224(GameWindow *);};
class Rva00222A8BTarget {public:unsigned char rva00222A53();};
class BfmeAptWindowManager;extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva0029B313 {public:void rva0029B313(int);};
struct DNode {DNode *next,*prev;Drawable *value;};
struct DList {DNode *head;Drawable *front() const {return head->next->value;}};
struct IdNode {IdNode *next,*prev;unsigned value;};
enum ObjectID {INVALID_OBJECT_ID=0};
struct Rva0029FB3BIter {IdNode *node;};
struct Rva0029FB3BAlloc {};
class PoolMember {public:void Rva00268902();};
class Rva0029FB3BMember {public:
 IdNode *node;void *init(void *);
 Rva0029FB3BMember(){Rva0029FB3BAlloc a;init(&a);}
 ~Rva0029FB3BMember(){((PoolMember *)this)->Rva00268902();}
 Rva0029FB3BIter insert(Rva0029FB3BIter,const ObjectID &);
 Rva0029FB3BIter end() const {Rva0029FB3BIter i={node};return i;}
 unsigned size() const {unsigned n=0;for(IdNode *i=node->next;i!=node;i=i->next)++n;return n;}
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
class View {public:
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
 virtual void slot77();
 virtual void slot78();
 virtual void slot79();
 virtual void slot80();
 virtual void slot81();
 virtual void slot82();
 virtual void slot83();
 virtual void slot84();
 virtual void slot85();
 virtual void slot86();
 virtual void slot87();
 virtual void slot88();
 virtual void slot89();
 virtual void screenToTerrain(const ICoord2D *,Coord3D *,bool);

};
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
char pad4[0x234];CommandButton *pending;char pad23c[0x5c0];int mouseMode;char pad800[4];unsigned mousedOver;void rva002A3273(const GameMessage *);
};

void InGameUI::rva002A3273(const GameMessage *msg)
{
 if (((Bfme939Helper *)TheRecorder)->get()==1) return;
 const Drawable *draw=TheGameClient->findDrawableByID(mousedOver);
 int type=msg->type;
 if (draw && (type==0xa7 || type==0xc0)) {
  const Object *obj=draw->object;
  int player=ThePlayerList?ThePlayerList->local->index:0;
  if(obj && obj->getShroudStatusForPlayer(player)==4)type=0xb3;
 }
 GameWindow *window=0;
 unsigned char underWindow=((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222A53();
 if(!underWindow) {
  const ICoord2D *pos=&TheMouse->pos;
  if(pos && TheWindowManager)window=TheWindowManager->getWindowUnderCursor(pos->x,pos->y,false);
  while(window) {
   if(window->rvaVirtual18()){underWindow=false;break;}
   if(!(window->winGetStatus()&0x10000)){underWindow=true;break;}
   window=window->winGetParent();
  }
 }
 const Object *obj=draw?draw->object:0;
 bool selectable=CanSelectDrawable(draw,false);
 if(!obj)selectable=false;
 const Drawable *source=0;const Object *sourceObj=0;
 if(getSelectCount()==1){source=getAllSelectedDrawables()->front();sourceObj=source?source->object:0;}
 switch(mouseMode){
 case 0:
  if(underWindow || (sourceObj&&!sourceObj->isLocallyControlled())){((Rva0029B313 *)this)->rva0029B313(2);return;}
  if(type==0xb3 || type==0xb4) {
   const DList *list=getAllSelectedDrawables();
   if(list) {
    int value=ThePlayerList->local->value750;
    Rva0029FB3BMember ids;
    for(DNode *i=list->head->next;i!=list->head;i=i->next){ObjectID id=(ObjectID)i->value->object->id;ids.insert(ids.end(),id);}
    if(ids.size()>0){
     Coord3D position;TheTacticalView->screenToTerrain(&TheMouse->pos,&position,false);
     if(TheAiOrdersManager->rva0035538C(position,value,(const _STL::list<CreateAHeroData *> *)&ids)){((Rva0029B313 *)this)->rva0029B313(0x37);return;}
    }
   }
  }
  switch(type) {
  case 0xb3:
   if(!selectable && sourceObj && sourceObj->isLocallyControlled() && (sourceObj->type->kind108&0x80))((Rva0029B313 *)this)->rva0029B313(0xc);
   else if(selectable && obj->isLocallyControlled() && !(obj->type->kind10f&0x10))((Rva0029B313 *)this)->rva0029B313(0xd);
   else if((unsigned char)TheRadar->rva0029A224(window) && !TheRadar->forced && (TheRadar->hidden || !ThePlayerList->local->hasRadar()))((Rva0029B313 *)this)->rva0029B313(2);
   else ((Rva0029B313 *)this)->rva0029B313(5);break;
  case 0xb4:
   if(selectable && obj->isLocallyControlled())((Rva0029B313 *)this)->rva0029B313(0xd);
   else ((Rva0029B313 *)this)->rva0029B313(6);break;
  case 0xa7:((Rva0029B313 *)this)->rva0029B313(0x7);break;
case 0xa9:((Rva0029B313 *)this)->rva0029B313(0x8);break;
case 0xaa:((Rva0029B313 *)this)->rva0029B313(0x9);break;
case 0xab:((Rva0029B313 *)this)->rva0029B313(0x11);break;
case 0xac:((Rva0029B313 *)this)->rva0029B313(0x12);break;
case 0xad:((Rva0029B313 *)this)->rva0029B313(0x13);break;
case 0xae:((Rva0029B313 *)this)->rva0029B313(0x14);break;
case 0xaf:((Rva0029B313 *)this)->rva0029B313(0xe);break;
case 0xb0:((Rva0029B313 *)this)->rva0029B313(0xf);break;
case 0xb1:((Rva0029B313 *)this)->rva0029B313(0x1d);break;
case 0xb2:((Rva0029B313 *)this)->rva0029B313(0x2e);break;
case 0xb5:((Rva0029B313 *)this)->rva0029B313(0x22);break;
case 0xb6:((Rva0029B313 *)this)->rva0029B313(0xf);break;
case 0xb8:((Rva0029B313 *)this)->rva0029B313(0xf);break;
case 0xb9:((Rva0029B313 *)this)->rva0029B313(0x15);break;
case 0xbb:((Rva0029B313 *)this)->rva0029B313(0x1c);break;
case 0xbd:((Rva0029B313 *)this)->rva0029B313(0x27);break;
case 0xc0:((Rva0029B313 *)this)->rva0029B313(0x23);break;
case 0xc1:((Rva0029B313 *)this)->rva0029B313(0x35);break;
case 0xc2:((Rva0029B313 *)this)->rva0029B313(0x36);break;
case 0x7d7:((Rva0029B313 *)this)->rva0029B313(0x29);break;case 0x7d8:((Rva0029B313 *)this)->rva0029B313(0x30);break;
  case 0xbc:((Rva0029B313 *)this)->rva0029B313(selectable?0xd:0x10);break;
  case 0xa8:case 0xbf:((Rva0029B313 *)this)->rva0029B313(0xc);break;
case 0xbe:((Rva0029B313 *)this)->rva0029B313(5);break;
case 0x7d6:((Rva0029B313 *)this)->rva0029B313(msg->getArgument(1)->integer);break;
  }
  break;
 case 1:
  if(underWindow){((Rva0029B313 *)this)->rva0029B313(2);return;}
  switch(type){case 0xb3:case 0xb4:case 0x432:((Rva0029B313 *)this)->rva0029B313(0xa);break;case 0xa7:case 0xc0:((Rva0029B313 *)this)->rva0029B313(0xb);break;}
  break;
 case 2:
  if(underWindow){((Rva0029B313 *)this)->rva0029B313(2);return;}
  if(pending){
   if(pending->isContextCommand() || pending->command==0x18 || pending->command==0x26 || pending->command==0x20 || pending->command==0x1f){
    if(!pending->radius){
     clearRadius();
     int index=TheMouse->getCursorIndex(type==0xa4?pending->cursor:pending->invalid);
     ((Rva0029B313 *)this)->rva0029B313(index!=-1?index:4);
    } else {((Rva0029B313 *)this)->rva0029B313(0);radiusCursor(pending->radius,pending->special,pending->weapon,type==0xa4);}
   } else if(pending->options&0x227){
    if(!pending->radius){clearRadius();int index=TheMouse->getCursorIndex(pending->cursor);((Rva0029B313 *)this)->rva0029B313(index!=-1?index:4);}
    else {((Rva0029B313 *)this)->rva0029B313(0);radiusCursor(pending->radius,pending->special,pending->weapon,true);}
   } else clearRadius();
  }
  break;
 }
}

int Radar::rva0029A224(GameWindow *value) { GameWindow *w=window; if(w==value && w) return 1; return 0; }

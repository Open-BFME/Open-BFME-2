// cl: /O1 /G7 /MD /EHsc
// ZH Network::RelayCommandsToCommandList guides frame+1 list traversal and
// message append. Native25E5F4..25E75F RET0 and WB E96910 provide quit/destroy/
// savegame cases and current target vslots43/46/63, fieldsC/10/3C.
// Existing Rva0025E970 caller supplies the shared Rva0025E4CD owner name.
class GameMessage;
class NetGameCommandMsg {public:GameMessage *constructGameMessage();};
class NetWrapperCommandMsg;
struct Rva0025E5F4Command {char opaque00[8];int frame8;char opaque0c[8];int type14;};
struct Rva0025E5F4Node {Rva0025E5F4Command *command;Rva0025E5F4Node *next;};
class NetCommandList {public:virtual void *destroy(int);Rva0025E5F4Node *first;};
class Rva004C54ECByte {public:__declspec(noinline) unsigned char get();char opaque00[0x1c];unsigned char value;};
unsigned char Rva004C54ECByte::get() {return value;}
enum PlayerLeaveCode { PLAYERLEAVECODE_UNKNOWN=0 };
class ConnectionManager {public:NetCommandList *getFrameCommandList(unsigned);PlayerLeaveCode processPlayerLeave(unsigned char);bool IsFrameAcked(unsigned);};
class Rva004CF406DwordClearer {public:void clear();};
#include "../Common/GameLogicObjectLookupView.h"
// Native40B provider supplies the status tail beyond the canonical prefix.
// This separately typed payload view keeps canonical frame access in GameLogic.
struct Rva0023D201Status {int status,quitFrame;char opaque08[0x1c-8];};
class Rva0023D201StatusView {public:
 __declspec(noinline) void rva0023D201(int slot,int state);
 char opaque00[0x40];unsigned frame;char opaque44[0x1c4-0x44];Rva0023D201Status entries[8];
};
void Rva0023D201StatusView::rva0023D201(int slot,int state) {
 if(slot<0 || slot>=8)return;
 entries[slot].status=state;entries[slot].quitFrame=frame;
}
extern GameLogic *TheGameLogic;
class CommandList {public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual void slot13();virtual void append(GameMessage*);
};
extern CommandList *TheCommandList;
class NetworkInterface {public:void rva0025E539(NetWrapperCommandMsg*);};
class Rva0025E4CD {public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
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
 virtual bool packetRouter();
 virtual void slot44();
 virtual void slot45();
 virtual int localPlayer();
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
 virtual bool leaving();
 void rva0025E5F4();
 char opaque04[8];ConnectionManager *manager;int state;char opaque14[0x3c-0x14];unsigned quitFrame;
};
void Rva0025E4CD::rva0025E5F4() {
 if(!manager || !state)return;
 NetCommandList *list=manager->getFrameCommandList(TheGameLogic->getFrame()+1);
 for(Rva0025E5F4Node *node=list->first;node;node=node->next) {
  Rva0025E5F4Command *command=node->command;
  if(!command)continue;
  switch(command->type14) {
  case 4:
   ((NetGameCommandMsg*)command)->constructGameMessage();
   TheCommandList->append(((NetGameCommandMsg*)command)->constructGameMessage());break;
  case 10:{
   unsigned char player=((Rva004C54ECByte*)command)->get();
   if(packetRouter() && (int)player==localPlayer()) {
    quitFrame=command->frame8;((Rva004CF406DwordClearer*)manager)->clear();
   } else if(manager->processPlayerLeave(player)==1)state=2;
   ((Rva0023D201StatusView*)TheGameLogic)->rva0023D201(player,1);break;
  }
  case 11:((NetworkInterface*)this)->rva0025E539((NetWrapperCommandMsg*)command);break;
  case 30:TheGameLogic->rva00240866((Rva0023E928*)command,true);break;
  }
 }
 void *allocation=list->destroy(0);operator delete(allocation);
 if(leaving() && manager->IsFrameAcked(quitFrame)) {
  manager->processPlayerLeave((unsigned char)localPlayer());quitFrame=-1;state=2;
 }
}

// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ZH ControlBarCommandProcessing.cpp semantic donor at BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85.
// BFME2 WB1129A70 names processCommandUI, with CommandButton and two boolean
// arguments. Native539A65..53B0F3 code; switch data53B0F3..53B1CF.
// Numeric command/message values and opaque fields are independently native;
// the ZH donor establishes purpose, not the added BFME2 cases or full layouts.
#include <map>
#include <list>
#include <vector>
#include "ascii_string.h"
#include "Coord3D.h"
#include "GameLogicObjectLookupView.h"

namespace _STL {
template<class V,class L,class R> __declspec(dllimport) __forceinline bool operator!=(const _Rb_tree_iterator<V,L>&a,const _Rb_tree_iterator<V,R>&b){return a._M_node!=b._M_node;}
template<class V,class L,class R> __declspec(dllimport) __forceinline bool operator!=(const _List_iterator<V,L>&a,const _List_iterator<V,R>&b){return a._M_node!=b._M_node;}
template<> __declspec(dllimport) __forceinline bool less<int>::operator()(const int&a,const int&b)const{return a<b;}
}


namespace _STL {
typedef _Rb_tree_iterator<pair<const int,int>,_Nonconst_traits<pair<const int,int> > > CBIterator;
template<> __declspec(dllimport) __forceinline CBIterator& CBIterator::operator++(){_M_node=_Rb_global_inst::_M_increment(_M_node);return *this;}
template<> __declspec(dllimport) __forceinline CBIterator& CBIterator::operator--(){_M_node=_Rb_global_inst::_M_decrement(_M_node);return *this;}
template<> __declspec(dllimport) __forceinline CBIterator::_Rb_tree_iterator(const CBIterator&x){_M_node=x._M_node;}
}


namespace _STL {
typedef pair<CBIterator,bool> CBInsertResult;
template<> __declspec(dllimport) __forceinline CBInsertResult::pair(const CBIterator&a,const bool&b):first(a),second(b){}
}


namespace _STL {
typedef _Rb_tree<int,pair<const int,void*>,_Select1st<pair<const int,void*> >,less<int>,allocator<pair<const int,void*> > > CBPointerTree;
template<> CBPointerTree::~_Rb_tree();
}


namespace _STL {
typedef _Rb_tree_node<pair<const int,int> > CBNode;
typedef _STLP_alloc_proxy<CBNode*,CBNode,allocator<CBNode> > CBNodeProxy;
template<> __declspec(dllimport) __forceinline CBNode* allocator<CBNode>::allocate(size_type n,const void*)const {return n ? reinterpret_cast<CBNode*>(allocator<char>::allocate(n*sizeof(CBNode),0)) : 0;}
template<> __declspec(dllimport) __forceinline CBNode* CBNodeProxy::allocate(size_t n){return static_cast<allocator<CBNode>&>(*this).allocate(n,0);}
template<> __declspec(dllimport) __forceinline void CBNodeProxy::deallocate(CBNode*p,size_t n){static_cast<allocator<CBNode>&>(*this).deallocate(p,n);}
}

enum ScienceType { SCIENCE_INVALID=-1 };
enum NameKeyType { NAMEKEY_INVALID=0 };
enum EvaEventID { EVA_INVALID=0 };
enum CBCommandStatus { CBC_COMMAND_NOT_USED=0, CBC_COMMAND_USED=1 };
class Matrix3D { public: float Get_Z_Rotation() const; float m[12]; };
class Object; class Player; class ThingTemplate; class Drawable; class CommandButton;
class GameWindow; class Module; class Rva0043D3A8;
class GameMessage { public:
 enum Type { INVALID=0 };
 void appendIntegerArgument(int); void appendRealArgument(float);
 void appendBooleanArgument(bool); void appendObjectIDArgument(ObjectID);
 void appendLocationArgument(const Coord3D&);
};
class DrawableList : public std::list<Drawable*> {};
class PickAndPlayInfo { public:
 PickAndPlayInfo(); bool value; Drawable *source,*target; int *weaponSlot;
 void *other; Coord3D pos; const CommandButton *commandButton;
};
bool __cdecl pickAndPlayUnitVoiceResponse(const DrawableList*,GameMessage::Type,PickAndPlayInfo*);
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator *TheNameKeyGenerator;
class Keyboard { public: bool isShift(); }; extern Keyboard *TheKeyboard;
extern GameLogic *TheGameLogic;
class Eva { public: bool reportEvaEvent(EvaEventID,const Coord3D*,const Coord3D*); }; extern Eva *TheEva;
class Overridable { public: const Overridable *friend_getFinalOverride() const; char unmodelled[0x14]; int id; };
class UpgradeTemplate { public: char pad[0x38]; int id; };
class UpgradeCenter { public:
 const UpgradeTemplate *findUpgrade(const AsciiString&) const;
 bool rva0026F11A(Player*,const UpgradeTemplate*,Object*,bool);
}; extern UpgradeCenter *TheUpgradeCenter;
class ScienceStore { public:
 bool playerHasPrereqsForScience(const Rva0043D3A8*,ScienceType) const;
 int getSciencePurchaseCost(ScienceType) const;
}; extern ScienceStore *TheScienceStore;
class Rva0035B164 { public: int rva0035B164(int); };
class Rva0028B7C1DwordField { public: int get() const; };
class Thing { public: Drawable *getDrawable() const; };
struct Rva0045A6D3Arg;
class AutoAbilityBehavior { public: int isAutoAbilityCommand(const Rva0045A6D3Arg*); };
class CommandProductionView { public: virtual void slot0(); virtual int canQueue(const UpgradeTemplate*); };
class CommandUI { public:
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
 virtual void message(AsciiString,...);
 virtual void slot16();
 virtual void slot17();
 virtual void errorMessage(AsciiString,...);
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
 virtual void setCommand(const CommandButton*);
 virtual const CommandButton *getCommand();
 virtual void slot49();
 virtual void slot50();
 virtual void slot51();
 virtual void slot52();
 virtual void slot53();
 virtual void slot54();
 virtual void placeBuildAvailable(const ThingTemplate*,Drawable*);
 virtual void slot56();
 virtual void slot57();
 virtual void slot58();
 virtual void slot59();
 virtual void slot60();
 virtual void slot61();
 virtual void slot62();
 virtual void slot63();
 virtual void clearRally(void*);
 virtual void slot65();
 virtual void slot66();
 virtual void slot67();
 virtual void clearSelection();
 virtual void slot69();
 virtual void slot70();
 virtual void slot71();
 virtual void slot72();
 virtual const DrawableList *getSelectedDrawables();
};
class CommandStream { public:
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
 virtual GameMessage *appendMessage(GameMessage::Type);
};
class CommandBuildAssistant { public:
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
 virtual int canMakeUnit(Object*,const ThingTemplate*,int);
};
class CommandSpecialState { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual int getState();
};
class CommandChangeType { public:
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
 virtual const ThingTemplate *getTemplate();
};
class CommandGateView { public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual bool isOpen();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual bool canToggle();
};
class InGameUI; extern InGameUI *TheInGameUI;
class MessageStream; extern MessageStream *TheMessageStream;
class BuildAssistant; extern BuildAssistant *TheBuildAssistant;
#define UI ((CommandUI*)TheInGameUI)
#define STREAM ((CommandStream*)TheMessageStream)
#define BUILD ((CommandBuildAssistant*)TheBuildAssistant)
#define MSG(n) STREAM->appendMessage((GameMessage::Type)(n))
#define VOICE(n,p) pickAndPlayUnitVoiceResponse(UI->getSelectedDrawables(),(GameMessage::Type)(n),(p))
class ThingTemplate { public:

 char pad000[0x108];
 unsigned char kind[28];
 char pad124[0x4B4];
 unsigned short typeKey;
 char pad5DA[0x6];
 unsigned short hero;
};
class Player { public:
bool canBuild(const ThingTemplate*) const; bool hasScience(ScienceType) const; Object *findNaturalCommandCenter();
 char pad000[0x24];
 int sciencePoints;
 char pad028[0x2C];
 int playerIndex;
 char pad058[0x6F8];
 int buildBlocked;
};
class Object { public:
Player *getControllingPlayer() const;
ObjectID getID() const { return id; }
const ThingTemplate *getTemplate() const { return thingTemplate; }
void *rva0028BC58(int); bool hasUpgrade(const UpgradeTemplate*) const;
void *rva0028C197() const;
Module *module(NameKeyType key) const { return findModule(key); }
protected: Module *findModule(NameKeyType) const;
public:
 char pad000[0x4];
 const ThingTemplate* thingTemplate;
 Matrix3D transform;
 Coord3D position;
 char pad044[0x30];
 ObjectID id;
 char pad078[0x1DC];
 CommandSpecialState* specialState;
 char pad258[0x1E3];
 bool singleUseUsed;
};
class Drawable { public:
Object *getObject() const { return object; }
 char pad000[0xFC];
 Object* object;
};
class PlayerList { public:
Player *getLocalPlayer() const { return localPlayer; }
 char pad000[0x10];
 Player* localPlayer;
};
extern PlayerList *ThePlayerList;
struct BfmeE8 { int a,b; };
class CommandButton { public:
const ThingTemplate *rva0035B570() const;
bool isReady(const Object*) const;
int getCommandType() const { return type; }
unsigned int getOptions() const { return options; }
const std::vector<AsciiString>& getExtraCommands() const { return extraCommands; }
bool getAutoAbility() const { return autoAbility; }
void setFlashCount(int n) const { flashCount=n; }
void rva0035B5C2(Object*,bool); void rva0035B6FA(ObjectID,bool);
const class Image *rva0035B19E() const;
 char pad000[0x14];
 int type;
 char pad018[0x4];
 unsigned int options;
 char pad020[0x4];
 const UpgradeTemplate* upgrade;
 char pad028[0x10];
 std::vector<AsciiString> upgradeNames;
 const Overridable* specialPower;
 char pad048[0x38];
 int weapon;
 char pad084[0x1C];
 int weaponFlags;
 std::vector<ScienceType> sciences;
 char pad0B0[0x10];
 int revivalID;
 int exitKey;
 char pad0C8[0x30];
 mutable int flashCount;
 char pad0FC[0x9];
 bool enabled;
 char pad106[0x6];
 bool autoAbility;
 char pad10D[0x7B];
 std::vector<AsciiString> extraCommands;
 char pad194[0x98];
 BfmeE8 context;
};
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_ALLOWED = 4,
	COMMAND_NOT_READY = 5,
	COMMAND_CANT_AFFORD = 6,
	COMMAND_LIMITED = 7,
	COMMAND_DONE = 8
};

class ControlBar { public:
CBCommandStatus processCommandUI(const CommandButton*,bool,bool);
CBCommandStatus rva0053B1CF(GameWindow *control, unsigned int gadgetMessage);
void switchToContext(int,void*);
const CommandButton *findCommandButton(const AsciiString&);
CommandAvailability getCommandAvailability(const CommandButton*,GameWindow*,Object*,float*,bool) const;
 char pad000[0x28];
 bool dirty;
 char pad029[0x43];
 Drawable* selectedDrawable;
 int context;
 char pad074[0x234];
 std::vector<BfmeE8> contextStack;
};
extern ControlBar *TheControlBar;
struct ControlBarInventoryEntry { GameWindow *window; int objectID; };
extern ControlBarInventoryEntry ControlBarInventoryEntries[32];
namespace _STL {
template <> void vector<BfmeE8,allocator<BfmeE8> >::push_back(const BfmeE8&);
template <> map<int,void*>::map();
}
// Owning 12-byte scalar tree view, as independently used by the native
// HordeContain rank map at474519. Native53ADBC constructs the integer map,
// 53AEDD and its EH cleanup call the existing22C612 owner destructor.
// Its original template identity is unresolved; retain the existing owner name.
class Rva00226883 { public: __declspec(dllimport) __forceinline Rva00226883() {} ~Rva00226883(); std::map<int,void*> storage; };

CBCommandStatus ControlBar::processCommandUI(const CommandButton *commandButton, bool primary, bool repeated)
{
    if (context != 7 && commandButton->getCommandType() != 0x19 && commandButton->getCommandType() != 0x20 && commandButton->getCommandType() != 0x26 && (!selectedDrawable || !selectedDrawable->getObject())) {
        if (context != 0) switchToContext(0,0);
        return CBC_COMMAND_NOT_USED;
    }
    if (!commandButton->enabled) return CBC_COMMAND_NOT_USED;
    if (repeated && commandButton->getCommandType() != 3) return CBC_COMMAND_NOT_USED;
    Object *obj=0;
    if (commandButton->getCommandType() != 0x19 && commandButton->getCommandType() != 0x20 && commandButton->getCommandType() != 0x26) {
        if (selectedDrawable) obj=selectedDrawable->getObject();
        else if (context==7) {
            const DrawableList *list=UI->getSelectedDrawables();
            for (DrawableList::const_iterator it=list->begin(); it!=list->end(); ++it) {
                Drawable *draw=(*it);
                if (draw) { Object *selected=draw->getObject(); if (selected && !(selected->getTemplate()->kind[5]&0x80)) { obj=selected; break; } }
            }
        }
    }
    bool cancellable=commandButton->getAutoAbility() || (commandButton->getOptions()&0x80000000);
    bool ready=true;
    if (commandButton->getCommandType()==0x17 || commandButton->getCommandType()==0x18) {
        if (obj) {
            if (!commandButton->isReady(obj)) ready=false;
        } else if (context==7) {
            ready=false;
            const DrawableList *list=UI->getSelectedDrawables();
            if (list && !list->empty()) {
                for (DrawableList::const_iterator it=list->begin();;++it) {
                    if (it==list->end()) { ready=true; break; }
                    Object *selected=(*it)->getObject();
                    if (!commandButton->isReady(selected)) break;
                }
            }
        }
    } else if ((!cancellable || primary) && obj) {
        ready=false;
        bool noPoints=false,noMoney=false;
        if (context==7) {
            const DrawableList *list=UI->getSelectedDrawables();
            for (DrawableList::const_iterator it=list->begin();it!=list->end();++it) {
                Drawable *draw=(*it);
                if (draw) {
                    Object *selected=draw->getObject();
                    if (selected && !(selected->getTemplate()->kind[5]&0x80)) {
                        float percent;
                        int state=getCommandAvailability(commandButton,0,selected,&percent,false);
                        if (state==1 || state==2) { ready=true; break; }
                        if (state==7) noPoints=true;
                        else if (state==6) noMoney=true;
                    }
                }
            }
        } else {
            float percent;
            int state=getCommandAvailability(commandButton,0,obj,&percent,false);
            if (state==1 || state==2) ready=true;
            else if (state==6) noMoney=true;
            else if (state==7) noPoints=true;
        }
        if (!ready) {
            if (noPoints) {
                UI->errorMessage(AsciiString("GUI:ErrorNoMoreCommandPoints"));
                TheEva->reportEvaEvent((EvaEventID)12,&obj->position,0);
            } else if (noMoney) {
                UI->errorMessage(AsciiString("GUI:ErrorNoMoreMoney"));
                TheEva->reportEvaEvent((EvaEventID)14,&obj->position,0);
            }
        }
    }
    if (ready || (cancellable && !primary)) commandButton->setFlashCount(0);
    else if (!cancellable || primary) return CBC_COMMAND_NOT_USED;
    if (obj && (commandButton->getOptions()&0x20000)) obj->singleUseUsed=true;
    if (obj && (obj->getTemplate()->kind[1]&0x40) && commandButton->getCommandType()==0x35) {
        Player *player=obj->getControllingPlayer();
        if (player && !player->buildBlocked)
            UI->placeBuildAvailable(commandButton->rva0035B570(),((Thing*)obj)->getDrawable());
    } else {
        UI->placeBuildAvailable(0,0);
        if (obj && (obj->getTemplate()->kind[0x13]&0x10)) UI->clearRally(0);
    }
    Player *player=ThePlayerList->getLocalPlayer();
    if (player) {
        const DrawableList *list=UI->getSelectedDrawables();
        if (list) {
            PickAndPlayInfo info;
            info.commandButton=commandButton;
            if (primary) pickAndPlayUnitVoiceResponse(list,(GameMessage::Type)0x7e3,&info);
            else if (commandButton->autoAbility && obj) {
                static NameKeyType autoAbilityKey=TheNameKeyGenerator->nameToKey("AutoAbilityBehavior");
                AutoAbilityBehavior *autoAbility=(AutoAbilityBehavior*)obj->module(autoAbilityKey);
                if (autoAbility) {
                    if ((unsigned char)autoAbility->isAutoAbilityCommand((const Rva0045A6D3Arg*)commandButton))
                        pickAndPlayUnitVoiceResponse(list,(GameMessage::Type)0x7e5,&info);
                    else pickAndPlayUnitVoiceResponse(list,(GameMessage::Type)0x7e4,&info);
                }
            }
        }
    }
    unsigned int options=commandButton->getOptions();
    if ((options&0x227) && (primary || !cancellable)) {
        if (UI->getCommand()!=commandButton && primary) UI->setCommand(commandButton);
        else UI->setCommand(0);
    }
    else switch (commandButton->getCommandType()) {
    case 1: {
        if (!selectedDrawable || !obj || !primary) break;
        const ThingTemplate *what=commandButton->rva0035B570();
        if (!what || !obj->getControllingPlayer() || !obj->getControllingPlayer()->canBuild(what)) break;
        if (!(obj->getTemplate()->kind[0xd]&1)) break;
        GameMessage *msg=MSG(0x419);
        msg->appendIntegerArgument(what->typeKey);
        msg->appendLocationArgument(obj->position);
        msg->appendRealArgument(obj->transform.Get_Z_Rotation());
        GameMessage *clear=MSG(0x3ec);
        clear->appendBooleanArgument(true);
        UI->clearSelection();
        break;
    }
    case 2:
        if (primary && obj) { Player *local=ThePlayerList->getLocalPlayer(); if (obj->getControllingPlayer()==local) MSG(0x41b); }
        break;
    case 0x35: {
        if (!selectedDrawable || !obj) break;
        const ThingTemplate *what=commandButton->rva0035B570();
        if (!what || !obj->getControllingPlayer() || obj->getControllingPlayer()->buildBlocked || !obj->getControllingPlayer()->canBuild(what)) break;
        int canMake=BUILD->canMakeUnit(obj,what,-1);
        if (canMake==2) { UI->message(AsciiString("GUI:NotEnoughMoneyToBuild")); break; }
        if (canMake==4) { UI->message(AsciiString("GUI:ProductionQueueFull")); break; }
        if (canMake==5) { UI->message(AsciiString("GUI:ParkingPlacesFull")); break; }
        if (canMake==6) { UI->message(AsciiString("GUI:UnitMaxedOut")); break; }
        UI->placeBuildAvailable(commandButton->rva0035B570(),selectedDrawable);
        UI->setCommand(commandButton);
        break;
    }
    case 0x22: MSG(0x43e); break;
    case 0x21: MSG(0x43d); break;
    case 0x32: {
        const ThingTemplate *what=commandButton->rva0035B570();
        if (what) { GameMessage *msg=MSG(0x43f); msg->appendIntegerArgument(what->typeKey); }
        break;
    }
    case 0x33: MSG(0x45d); break;
    case 0x3b: MSG(0x46e); break;
    case 0x3c: MSG(0x46f); break;
    case 3: case 4: case 0x2e: {
        bool revival=commandButton->getCommandType()==0x2e;
        const ThingTemplate *what=revival ? 0 : commandButton->rva0035B570();
        int revivalID=revival ? commandButton->revivalID : -1;
        if (!obj) break;
        if (!revival) { if (!what) break; } else { if (revivalID==-1) break; }
        if (!obj->rva0028BC58(0)) break;
        if (primary) {
            if (BUILD->canMakeUnit(obj,what,revivalID)==7) break;
            int upgradeID=-1;
            for (std::vector<AsciiString>::const_iterator i=commandButton->upgradeNames.begin();i!=commandButton->upgradeNames.end();++i) {
                const UpgradeTemplate *upgrade=TheUpgradeCenter->findUpgrade(*i);
                if (upgrade) upgradeID=upgrade->id;
            }
            bool multiple=TheKeyboard->isShift() && !revival && what && what->hero==0;
            if (repeated && !multiple) return CBC_COMMAND_NOT_USED;
            bool horde=commandButton->getCommandType()==4;
            GameMessage *msg=MSG(0x417);
            msg->appendBooleanArgument(revival);
            if (revival) msg->appendIntegerArgument(revivalID);
            else msg->appendIntegerArgument(what->typeKey);
            msg->appendIntegerArgument(upgradeID);
            msg->appendBooleanArgument(multiple);
            msg->appendBooleanArgument(horde);
        } else if (commandButton->getOptions()&0x80000000) {
            Player *local=ThePlayerList->getLocalPlayer();
            if (obj->getControllingPlayer()!=local) break;
            GameMessage *msg=MSG(0x418);
            msg->appendBooleanArgument(revival);
            if (revival) msg->appendIntegerArgument(revivalID);
            else msg->appendIntegerArgument(what->typeKey);
            bool multiple=TheKeyboard->isShift() && !revival && what && what->hero==0;
            msg->appendBooleanArgument(multiple);
        }
        break;
    }
    case 6: {
        const UpgradeTemplate *upgrade=commandButton->upgrade;
        if (!obj || !upgrade) break;
        if (primary) {
            Player *payer=ThePlayerList->getLocalPlayer();
            if (!TheUpgradeCenter->rva0026F11A(payer,upgrade,obj,true)) break;
            CommandProductionView *production=(CommandProductionView*)obj->rva0028BC58(0);
            if (production && production->canQueue(upgrade)==4) {
                UI->message(AsciiString("GUI:ProductionQueueFull")); break;
            }
            GameMessage *msg=MSG(0x415);
            msg->appendObjectIDArgument(obj->getID());
            msg->appendIntegerArgument(upgrade->id);
        } else if (options&0x80000000) {
            Player *local=ThePlayerList->getLocalPlayer();
            if (obj->getControllingPlayer()==local) { GameMessage *msg=MSG(0x416); msg->appendIntegerArgument(upgrade->id); }
        }
        break;
    }
    case 7: {
        const UpgradeTemplate *upgrade=commandButton->upgrade;
        if (!upgrade) break;
        if (primary) {
            bool valid=true;
            if (context==7) {
                const DrawableList *list=UI->getSelectedDrawables();
                for (DrawableList::const_iterator it=list->begin();it!=list->end();++it) {
                    Drawable *draw=(*it);
                    if (draw && draw->getObject() && !(draw->getObject()->getTemplate()->kind[5]&0x80)) {
                        Player *local=ThePlayerList->getLocalPlayer();
                        if (draw->getObject()->getControllingPlayer()!=local) return CBC_COMMAND_USED;
                        if ((obj->getTemplate()->kind[0x12]&0x40) && obj->specialState->getState()==3) return CBC_COMMAND_USED;
                    }
                }
            } else if (obj) {
                Player *local=ThePlayerList->getLocalPlayer();
                if (obj->getControllingPlayer()!=local) valid=false;
                if ((obj->getTemplate()->kind[0x12]&0x40) && obj->specialState->getState()==3) valid=false;
                if (!valid) break;
            }
            Player *payer=ThePlayerList->getLocalPlayer();
            if (!TheUpgradeCenter->rva0026F11A(payer,upgrade,obj,true)) break;
            GameMessage *msg=MSG(0x415);
            msg->appendObjectIDArgument(INVALID_OBJECT_ID);
            msg->appendIntegerArgument(upgrade->id);
        } else if (options&0x80000000) {
            Player *local=ThePlayerList->getLocalPlayer();
            if (obj->getControllingPlayer()==local) { GameMessage *msg=MSG(0x416); msg->appendIntegerArgument(upgrade->id); }
        }
        break;
    }
    case 8: {
        const UpgradeTemplate *upgrade=commandButton->upgrade;
        if (!obj || !upgrade) break;
        if (primary) {
            Player *payer=ThePlayerList->getLocalPlayer();
            if (!TheUpgradeCenter->rva0026F11A(payer,upgrade,obj,true)) break;
            CommandProductionView *production=(CommandProductionView*)obj->rva0028BC58(0);
            if (production && production->canQueue(upgrade)==4) {
                UI->message(AsciiString("GUI:ProductionQueueFull")); break;
            }
            if (obj->hasUpgrade(upgrade)) break;
            static NameKeyType castleMemberKey=TheNameKeyGenerator->nameToKey("CastleMemberBehavior");
            struct CastleMemberView { char pad[0x18]; ObjectID castleID; };
            CastleMemberView *member=(CastleMemberView*)obj->module(castleMemberKey);
            if (!member || !TheGameLogic->findObjectByID(member->castleID)) break;
            GameMessage *msg=MSG(0x415);
            msg->appendObjectIDArgument(obj->getID());
            msg->appendIntegerArgument(upgrade->id);
        } else if (options&0x80000000) {
            Player *local=ThePlayerList->getLocalPlayer();
            if (obj->getControllingPlayer()==local) { GameMessage *msg=MSG(0x416); msg->appendIntegerArgument(upgrade->id); }
        }
        break;
    }
    case 0xe: MSG(0x435); break;
    case 0xf: break;
    case 0x10: {
        int key=commandButton->exitKey;
        ObjectID id=INVALID_OBJECT_ID;
        if (!key) break;
        for (int i=0;i<32;++i) if ((int)ControlBarInventoryEntries[i].window==key) id=(ObjectID)ControlBarInventoryEntries[i].objectID;
        Object *contained=TheGameLogic->findObjectByID(id);
        if (!contained) break;
        GameMessage *msg=MSG(0x41d);
        msg->appendObjectIDArgument(contained->getID());
        msg->appendObjectIDArgument(obj->getID());
        break;
    }
    case 0x11: {
        UI->setCommand(0);
        if (!(commandButton->getOptions()&0x20)) { GameMessage::Type type=(GameMessage::Type)0x41e; VOICE(type,0); MSG(type); }
        break;
    }
    case 0x28: {
        UI->setCommand(0);
        if (!(commandButton->getOptions()&0x20)) { GameMessage::Type type=(GameMessage::Type)0x455; VOICE(type,0); MSG(type); }
        break;
    }
    case 0x2a: {
        if (!obj) break;
        GameMessage::Type type=(GameMessage::Type)0x439;
        if (TheInGameUI) { UI->setCommand(0); VOICE(type,0); }
        GameMessage *msg=MSG(type); msg->appendObjectIDArgument(obj->getID());
        break;
    }
    case 0x2b: {
        if (!obj) break;
        GameMessage::Type type=(GameMessage::Type)0x437;
        if (TheInGameUI) { UI->setCommand(0); VOICE(type,0); }
        GameMessage *msg=MSG(type); msg->appendObjectIDArgument(obj->getID());
        break;
    }
    case 0x2c: {
        if (!obj) break;
        static NameKeyType gateKey=TheNameKeyGenerator->nameToKey("GateOpenAndCloseBehavior");
        Module *module=obj->module(gateKey);
        CommandGateView *gate=module ? (CommandGateView*)((char*)module-4) : 0;
        if (!gate) {
            module=obj->module(TheNameKeyGenerator->nameToKey("GateProxyBehavior"));
            gate=module ? (CommandGateView*)((char*)module-4) : 0;
            if (!gate) break;
        }
        if (gate && gate->canToggle()) {
            GameMessage *msg=0;
            UI->setCommand(0);
            if (gate->isOpen()) {
                VOICE(0x439,0);
                msg=MSG(0x439);
            } else {
                VOICE(0x437,0);
                msg=MSG(0x437);
            }
            msg->appendObjectIDArgument(obj->getID());
        }
        break;
    }
    case 0x12: {
        UI->setCommand(0);
        if (!(commandButton->getOptions()&0x20)) { GameMessage::Type type=(GameMessage::Type)0x41f; VOICE(type,0); MSG(type); }
        break;
    }
    case 0x15: break;
    case 0x16: if (primary) MSG(0x41c); break;
    case 0x14: break;
    case 0xb: case 0xc: case 0xd: case 0x1a: break;
    case 0x1b: {
        GameMessage::Type type=(GameMessage::Type)0x43a;
        GameMessage *msg=MSG(type);
        PickAndPlayInfo info;
        int weapon=commandButton->weapon;
        info.weaponSlot=&weapon;
        VOICE(type,&info);
        msg->appendIntegerArgument(commandButton->weapon);
        break;
    }
    case 0x23: {
        if (!obj) break;
        GameMessage::Type type=(GameMessage::Type)0x43a;
        GameMessage *msg=MSG(type);
        PickAndPlayInfo info;
        int weapon=commandButton->weapon;
        info.weaponSlot=&weapon;
        VOICE(type,&info);
        int current=((Rva0028B7C1DwordField*)obj)->get();
        msg->appendIntegerArgument(((Rva0035B164*)commandButton)->rva0035B164(current));
        const_cast<CommandButton*>(commandButton)->rva0035B6FA((ObjectID)current,false);
        break;
    }
    case 0x2d: {
        GameMessage *msg=MSG(0x457);
        msg->appendObjectIDArgument(obj ? obj->getID() : INVALID_OBJECT_ID);
        if (obj) const_cast<CommandButton*>(commandButton)->rva0035B5C2(obj,true);
        break;
    }
    case 0x31: {
        GameMessage *msg=MSG(0x45c);
        int value=0;
        if (commandButton->getOptions()&0x2000) value=1;
        else if (commandButton->getOptions()&0x4000) value=2;
        else if (commandButton->getOptions()&0x8000) value=3;
        msg->appendIntegerArgument(value);
        break;
    }
    case 0x30: {
        GameMessage *msg=MSG(0x45b);
        msg->appendObjectIDArgument(obj ? obj->getID() : INVALID_OBJECT_ID);
        if (obj) const_cast<CommandButton*>(commandButton)->rva0035B6FA(obj->getID(),true);
        break;
    }
    case 0x17: {
        if (!primary) {
            if (cancellable && obj) {
                GameMessage *msg=MSG(0x459);
                msg->appendIntegerArgument(commandButton->weapon);
                msg->appendObjectIDArgument(obj->getID());
            }
        } else {
            GameMessage *msg=MSG(0x40d);
            msg->appendIntegerArgument(commandButton->weapon);
            msg->appendIntegerArgument(commandButton->weaponFlags);
        }
        break;
    }
    case 0x20: {
        Object *center=ThePlayerList->getLocalPlayer()->findNaturalCommandCenter();
        if (!center) break;
        GameMessage *msg=MSG(0x410);
        msg->appendIntegerArgument(commandButton->specialPower->friend_getFinalOverride()->id);
        msg->appendIntegerArgument(commandButton->getOptions());
        msg->appendObjectIDArgument(center->getID());
        msg->appendObjectIDArgument(INVALID_OBJECT_ID);
        break;
    }
    case 0x26: {
        GameMessage::Type type=(GameMessage::Type)0x456;
        GameMessage *msg=MSG(type);
        msg->appendIntegerArgument(commandButton->specialPower->friend_getFinalOverride()->id);
        msg->appendIntegerArgument(commandButton->getOptions());
        msg->appendObjectIDArgument(INVALID_OBJECT_ID);
        const std::vector<AsciiString>& extraCommands=commandButton->getExtraCommands();
        if (!extraCommands.empty()) {
            for (unsigned int i=0;i<extraCommands.size();++i) {
                const CommandButton *extra=TheControlBar->findCommandButton(extraCommands[i]);
                GameMessage *extraMsg=MSG(type);
                extraMsg->appendIntegerArgument(extra->specialPower->friend_getFinalOverride()->id);
                extraMsg->appendIntegerArgument(extra->options);
                extraMsg->appendObjectIDArgument(INVALID_OBJECT_ID);
            }
        }
        break;
    }
    case 0x18: {
        const_cast<CommandButton*>(commandButton)->rva0035B5C2(obj,true);
        if (!primary) {
            if (cancellable && obj) {
                GameMessage *msg=MSG(0x458);
                msg->appendIntegerArgument(commandButton->specialPower->friend_getFinalOverride()->id);
                msg->appendObjectIDArgument(obj->getID());
            }
        } else {
            GameMessage::Type type=(GameMessage::Type)0x410;
            GameMessage *msg=MSG(type);
            msg->appendIntegerArgument(commandButton->specialPower->friend_getFinalOverride()->id);
            msg->appendIntegerArgument(commandButton->getOptions());
            msg->appendObjectIDArgument(INVALID_OBJECT_ID);
            msg->appendObjectIDArgument(INVALID_OBJECT_ID);
            const std::vector<AsciiString>& extraCommands=commandButton->getExtraCommands();
        if (!extraCommands.empty()) {
                for (unsigned int i=0;i<extraCommands.size();++i) {
                    const CommandButton *extra=TheControlBar->findCommandButton(extraCommands[i]);
                    if (extra && extra->type==0x18) {
                        GameMessage *extraMsg=MSG(type);
                        extraMsg->appendIntegerArgument(extra->specialPower->friend_getFinalOverride()->id);
                        extraMsg->appendIntegerArgument(extra->options);
                        extraMsg->appendObjectIDArgument(INVALID_OBJECT_ID);
                        extraMsg->appendObjectIDArgument(INVALID_OBJECT_ID);
                    }
                }
            }
        }
        break;
    }
    case 0x19: {
        if (!player) break;
        ScienceType science=SCIENCE_INVALID;
        for (unsigned int i=0;i<commandButton->sciences.size();++i) {
            science=commandButton->sciences[i];
            if (!player->hasScience(science) && TheScienceStore->playerHasPrereqsForScience((Rva0043D3A8*)((char*)player+4),science)) {
                int points=player->sciencePoints;
                if (TheScienceStore->getSciencePurchaseCost(science)<=points) break;
            }
        }
        if (science==SCIENCE_INVALID) { switchToContext(0,0); break; }
        GameMessage *msg=MSG(0x414);
        msg->appendIntegerArgument(player->playerIndex);
        msg->appendIntegerArgument(science);
        dirty=true;
        const std::vector<AsciiString>& extraCommands=commandButton->getExtraCommands();
        if (!extraCommands.empty()) {
            GameMessage::Type type=(GameMessage::Type)0x456;
            for (unsigned int i=0;i<extraCommands.size();++i) {
                const CommandButton *extra=TheControlBar->findCommandButton(extraCommands[i]);
                GameMessage *extraMsg=MSG(type);
                extraMsg->appendIntegerArgument(extra->specialPower->friend_getFinalOverride()->id);
                extraMsg->appendIntegerArgument(extra->options);
                extraMsg->appendObjectIDArgument(INVALID_OBJECT_ID);
            }
        }
        break;
    }
    case 0x24: {
        if (context==7) {
            const DrawableList *list=UI->getSelectedDrawables();
            bool found=false;
            Rva00226883 countOwner;
            std::map<int,int>& counts=(std::map<int,int>&)countOwner.storage;
            int chosen=-1;
            for (DrawableList::const_iterator it=list->begin();it!=list->end();++it) {
                Drawable *draw=(*it);
                if (!draw || !draw->getObject()) continue;
                CommandChangeType *change=(CommandChangeType*)draw->getObject()->rva0028C197();
                if (!change) continue;
                const ThingTemplate *what=change->getTemplate();
                if (!what) continue;
                int key=what->typeKey;
                std::map<int,int>::iterator existing=counts.find(key);
                if (existing!=counts.end()) ++existing->second;
                else counts.insert(std::make_pair(key,1));
                found=true;
            }
            int highest=0;
            for (std::map<int,int>::iterator it=counts.begin();it!=counts.end();++it) {
                if (highest<it->second) { chosen=it->first; highest=it->second; }
            }
            if (found && chosen!=-1) {
                for (DrawableList::const_iterator it=list->begin();it!=list->end();++it) {
                    Drawable *draw=(*it);
                    if (draw) {
                        Object *selected=draw->getObject();
                        if (selected) {
                            void *change=selected->rva0028C197();
                            if (change) {
                                GameMessage *msg=MSG(0x460);
                                msg->appendObjectIDArgument(selected->getID());
                                msg->appendIntegerArgument(chosen);
                            }
                        }
                    }
                }
            }
        } else if (obj) { GameMessage *msg=MSG(0x453); msg->appendObjectIDArgument(obj->getID()); }
        if (obj) const_cast<CommandButton*>(commandButton)->rva0035B5C2(obj,true);
        break;
    }
    case 0x25: {
        if (!primary) {
            if (!cancellable || !obj) break;
            GameMessage *msg=MSG(0x458);
            msg->appendIntegerArgument(commandButton->specialPower->friend_getFinalOverride()->id);
            msg->appendObjectIDArgument(obj->getID());
        } else {
            GameMessage::Type type=(GameMessage::Type)0x410;
            GameMessage *msg=MSG(type);
            msg->appendIntegerArgument(commandButton->specialPower->friend_getFinalOverride()->id);
            msg->appendIntegerArgument(commandButton->getOptions());
            msg->appendObjectIDArgument(INVALID_OBJECT_ID);
            msg->appendObjectIDArgument(obj ? obj->getID() : INVALID_OBJECT_ID);
            const std::vector<AsciiString>& extraCommands=commandButton->getExtraCommands();
        if (!extraCommands.empty()) {
                for (unsigned int i=0;i<extraCommands.size();++i) {
                    const CommandButton *extra=TheControlBar->findCommandButton(extraCommands[i]);
                    if (extra && extra->type==0x18) {
                        GameMessage *extraMsg=MSG(type);
                        extraMsg->appendIntegerArgument(extra->specialPower->friend_getFinalOverride()->id);
                        extraMsg->appendIntegerArgument(extra->options);
                        extraMsg->appendObjectIDArgument(INVALID_OBJECT_ID);
                        extraMsg->appendObjectIDArgument(obj ? obj->getID() : INVALID_OBJECT_ID);
                    }
                }
            }
        }
        const_cast<CommandButton*>(commandButton)->rva0035B5C2(obj,true);
        break;
    }
    case 0x34:
        if (commandButton->rva0035B570()) {
            GameMessage *msg=MSG(0x460);
            msg->appendIntegerArgument(0);
            msg->appendIntegerArgument(commandButton->rva0035B570()->typeKey);
        }
        break;
    case 0x27: MSG(0x454); break;
    case 0x37:
        contextStack.push_back(commandButton->context);
        switchToContext(context,selectedDrawable);
        break;
    case 0x38:
        if (!contextStack.empty()) { contextStack.pop_back(); switchToContext(context,selectedDrawable); }
        break;
    default: return CBC_COMMAND_NOT_USED;
    }
    return CBC_COMMAND_USED;
}

// Retail 0x0053B1CF (141 bytes, RET 8), after processCommandUI's switch
// data: the button-click entry. A null control or one without a command
// button, a control whose vslot 8 answers false, or the rowed PlayerList
// query 0x002A7DD0 being true, ignores the click. Otherwise the button
// remembers its window (+0xC4), processCommandUI runs with primary = not
// 0x4009 and repeated = 0x400B, and a button still on the same control
// whose command type is not 0x10 gets its enabled image refreshed (rowed
// 0x0035B19E / 0x002C0433). Zero Hour's processCommandUI(GameWindow*, ...)
// front half; BFME 2's name for it is not established.
class Image;
void *GadgetButtonGetData(GameWindow *window);
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *window, const Image *image);
class Rva0053B1CFWindow { public:
virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
virtual bool slot8();
};
class Rva002A7DD0 { public: bool rva002A7DD0(); };
struct Rva0053B1CFButtonWindow { char pad000[0xC4]; GameWindow *window; };
CBCommandStatus ControlBar::rva0053B1CF(GameWindow *control, unsigned int gadgetMessage)
{
    if (!control)
        return CBC_COMMAND_NOT_USED;
    CommandButton *commandButton = (CommandButton *)GadgetButtonGetData(control);
    if (!((Rva0053B1CFWindow *)control)->slot8())
        return CBC_COMMAND_NOT_USED;
    if (!commandButton)
        return CBC_COMMAND_NOT_USED;
    if (((Rva002A7DD0 *)ThePlayerList)->rva002A7DD0())
        return CBC_COMMAND_NOT_USED;
    ((Rva0053B1CFButtonWindow *)commandButton)->window = control;
    CBCommandStatus result = processCommandUI(commandButton, gadgetMessage != 0x4009, gadgetMessage == 0x400B);
    if ((CommandButton *)GadgetButtonGetData(control) == commandButton && commandButton->getCommandType() != 0x10)
        GadgetButtonSetEnabledImage_Rva002C0433(control, commandButton->rva0035B19E());
    return result;
}

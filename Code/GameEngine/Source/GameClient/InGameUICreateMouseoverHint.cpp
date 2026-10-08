// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// InGameUI::createMouseoverHint, retail RVA 0x0029EBE2 (1901 bytes; native
// boundary VA 0x0069EBE2..0x0069F34F).
//
// Identity: WorldBuilder's debug body (WB VA 0x00DB1900) carries the same
// strings and call sequence, and Zero Hour's InGameUI::createMouseoverHint
// (GeneralsMD/Code/GameEngine/Source/GameClient/InGameUI.cpp) is the semantic
// donor: mouse-state guard, window walk, disguise handling, warehouse supply
// feedback, shroud check and the cursor update at the end. The BFME 2 body
// adds the per-object/per-drawable string overrides, the tooltip record sent
// to ControlBar::bfmeShowDN and the TheLookAtTranslator test.
//
// Target facts: every field offset, vtable slot, global, string and callee
// address below is read from the retail instructions. Callees use the names
// the ledger already gives those addresses (address-derived where no name is
// proven). Strings, Coord3D and PartitionManager come from their canonical
// headers; the other class views carry only what the body touches; TooltipRecord/TooltipBase name the 12-byte record whose vtables are
// VA 0x00BFD010 / 0x00BE5838 by its shape, not by evidence of a real name.
// Banked by earlier seats as reverse/attempts/0x0029ebe2.cpp with every
// non-call byte equal; this unit binds its calls to the rowed callees.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "../Common/PartitionRangeQueryCallView.h"

// Retail tests the display string inline (null buffer or zero length).
template<> inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length==0; }
// Retail's wide str() takes the buffer pointer, steps it past the 8-byte
// header in place and falls back to the shared null character only on null.
template<> inline const unsigned short *StringBase<unsigned short>::str() const
{
	static const unsigned short TheNullChr = 0;
	const unsigned short *result = (const unsigned short *)m_data;
	if (result)
		result = (const unsigned short *)((const char *)result + 8);
	else
		result = &TheNullChr;
	return result;
}
// The display-name compare runs with the fetched temporary live but stores no
// unwind state around the call, so this unit sees it as non-throwing.
template<> int StringBase<unsigned short>::compare(const StringBase<unsigned short> &) const throw();

typedef unsigned short wchar_t;
typedef unsigned int UnsignedInt;
enum DrawableID { INVALID_DRAWABLE_ID = 0 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum KindOfType { KINDOF_DISGUISER = 300 };
enum Relationship { NEUTRAL = 0, ALLIES = 2 };
enum CellShroudStatus { CELLSHROUD_CLEAR = 0 };
struct ICoord2D { int x, y; };
struct RGBColor { float red, green, blue; void setFromInt(int); };
class Object; class ThingTemplate; class Player; class Team; class Drawable;
class GameWindow; class ContainModuleInterface; class SpecialDisguiseUpdate; class SupplyWarehouseDockUpdate;
class TooltipRecord;
struct MouseIO { ICoord2D pos; };
class Mouse {
 public:
 enum MouseCursor { ARROW=2, SELECTING=13 };
 void rva001EEA6D(UnicodeString,int=-1,const RGBColor * =0,float=1.0f);
 const MouseIO* getMouseStatus() const { return &m_io; }
 unsigned char pad[0x4f0c]; MouseIO m_io;
};
extern Mouse* TheMouse;
class Rva001EEC4B { public: void rva001EEC4B(); };

class GameWindow { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual bool RvaInputPredicate();
 UnsignedInt winGetStatus(); GameWindow* winGetParent();

};
class WindowManager { public:
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
 virtual GameWindow* getWindowUnderCursor(int,int,int=0);


};
extern WindowManager* TheWindowManager;
class GameClient { public:
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
 virtual Drawable* findDrawableByID(DrawableID);


};
extern GameClient* TheGameClient;
union GameMessageArgumentType { DrawableID drawableID; };
class GameMessage { public:
 enum Type { MSG_MOUSEOVER_DRAWABLE_HINT=0xa2 };
 Type getType() const { return m_type; }
 const GameMessageArgumentType* getArgument(int) const;
 unsigned char pad[0x10]; Type m_type;
};
class ThingTemplate { public:
 const UnicodeString& getDisplayName() const { return displayName; }
 const AsciiString& getName() const { return name; }
 bool testByte(int index,unsigned char mask) const { return (kindFlags[index]&mask)!=0; }
 unsigned char pad0[0x30]; UnicodeString displayName;
 unsigned char pad1[0x5c-0x34]; AsciiString overrideKey;
 unsigned char pad2[4]; AsciiString name;
 unsigned char pad3[0x108-0x68]; unsigned char kindFlags[24];
};
class Drawable { public:
 Object* getObject() const { return object; }
 DrawableID getID() const;
 bool rva00274C62(AsciiString*);
 unsigned char pad[0xfc]; Object* object;
};
class Player { public:
 Relationship getRelationship(const Team*) const;
 bool isPlayerActive() const;
 bool rva002AA245() const;
 bool isLocalPlayer() const;
 const UnicodeString& getPlayerDisplayName() const { return name; }
 const Team* getDefaultTeam() const { return team; }
 int getPlayerIndex() const { return index; }
 int getPlayerColor() const { return color; }
 unsigned char pad0[0x38]; UnicodeString name;
 unsigned char pad1[0x54-0x3c]; int index;
 unsigned char pad2[0x280-0x58]; int color;
 unsigned char pad3[0x2ec-0x284]; Team* team;
};
class PlayerList { public:
 Player* getLocalPlayer() const { return local; }
 Player* getNthPlayer(int);
 unsigned char pad[0x10]; Player* local;
};
extern PlayerList* ThePlayerList;

class Rva002A7DD0 { public: bool rva002A7DD0(); };

class ContainModuleInterface { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual bool isGarrisonable() const;
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
 virtual const Player* getApparentControllingPlayer(const Player*) const;


};
class Rva00373EC6 { public: unsigned char pad[0x38]; int playerIndex; const ThingTemplate* thingTemplate; };
class Module {};
class SpecialDisguiseUpdate : public Module {};
class Rva004B031E { public: void* rva004B031E(); };
class SupplyWarehouseDockUpdate : public Module { public: unsigned char pad[0x88]; int boxes; int getBoxesStored() const { return boxes; } };
class Object { public:
 const ThingTemplate* getTemplate() const { return thingTemplate; }
 const Coord3D* getPosition() const { return &position; }
 const Team* getTeam() const { return team; }
 ContainModuleInterface* getContain() const { return contain; }
 UnsignedInt getID() const { return id; }
 bool isKindOf(KindOfType) const;
 Player* getControllingPlayer() const;
 int getIndicatorColor() const;
 bool isLocallyControlled() const;
 Module* findModule(NameKeyType) const;
 Rva00373EC6* rva0028F4BC();
 void* getDisplayName();
 bool rva0029137E(AsciiString&);
 unsigned char pad0[4]; const ThingTemplate* thingTemplate;
 unsigned char pad1[0x38-8]; Coord3D position;
 unsigned char pad2[0x74-0x44]; UnsignedInt id;
 unsigned char pad3[0x250-0x78]; ContainModuleInterface* contain;
 unsigned char pad4[0x304-0x254]; const Team* team;
};
class NameKeyGenerator { public: NameKeyType nameToKey(const char*); };
extern NameKeyGenerator* TheNameKeyGenerator;

class GameTextInterface { public:
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
 virtual UnicodeString fetchAscii(const AsciiString&,bool * =0);
 virtual UnicodeString fetchChars(const char*,bool * =0);
 virtual void slot16();
 virtual const UnicodeString* fetchRef(const char*,bool * =0);


};
extern GameTextInterface* TheGameText;
class View { public:
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
 virtual void screenToWorld(const ICoord2D*,Coord3D*,int=0);


};
extern View* TheTacticalView;
extern PartitionManager* ThePartitionManager;
enum RecorderModeType { RECORDERMODETYPE_RECORD, RECORDERMODETYPE_PLAYBACK };
class RecorderClass { public: bool isMultiplayer(); RecorderModeType getMode(); };
extern RecorderClass* TheRecorder;
class LookAtTranslator;
class BfmeOwnVVD { public: unsigned char Rva0042E8C1(); };
extern LookAtTranslator* TheLookAtTranslator;
class GlobalData { public:
 unsigned char pad0[0x9b8]; int tooltipFlag;
 unsigned char pad1[0xa5c-0x9bc]; int baseValuePerSupplyBox;
};
extern GlobalData* TheGlobalData;
class TooltipBase { public: virtual ~TooltipBase() {} };
class TooltipRecord: public TooltipBase { public:
 TooltipRecord(UnsignedInt id,UnsignedInt context):objectID(id),uiContext(context) {}
 virtual ~TooltipRecord() {}
 UnsignedInt objectID,uiContext;
};
struct BfmeMsgDN;
class ControlBar { public: void bfmeShowDN(BfmeMsgDN*); };
extern ControlBar* TheControlBar;
bool CanSelectDrawable(const Drawable*,bool);

class InGameUI { public:
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
 virtual int getSelectCount() const;
 virtual void createMouseoverHint(const GameMessage*);
protected:
 void setMouseCursor(Mouse::MouseCursor);
public:
unsigned char pad0[0x7f8-4];bool m_isScrolling,m_isSelecting;
unsigned char pad1[2]; int m_mouseMode,m_mouseModeCursor;DrawableID m_mousedOverDrawableID;
unsigned char pad2[0x984-0x808];UnsignedInt m_tooltipContext;
};
extern InGameUI* TheInGameUI;

void InGameUI::createMouseoverHint(const GameMessage* msg)
{
 if (m_isScrolling || m_isSelecting) return;
 GameWindow* window=0;
 const MouseIO* io=TheMouse->getMouseStatus();
 bool underWindow=false;
 if (io && TheWindowManager)
  window=TheWindowManager->getWindowUnderCursor(io->pos.x,io->pos.y);
 while(window) {
  if(window->RvaInputPredicate()) break;
  if(!(window->winGetStatus()&0x10000) && !(window->winGetStatus()&0x200)) {underWindow=true;break;}
  window=window->winGetParent();
 }
 if(underWindow) {setMouseCursor(Mouse::ARROW);return;}
 DrawableID oldID=m_mousedOverDrawableID;
 if(msg->getType()==GameMessage::MSG_MOUSEOVER_DRAWABLE_HINT) {
  TheMouse->rva001EEA6D(UnicodeString::TheEmptyString);
  m_mousedOverDrawableID=INVALID_DRAWABLE_ID;
  const Drawable* draw=TheGameClient->findDrawableByID(msg->getArgument(0)->drawableID);
  const Object* obj=draw?draw->getObject():0;
  if(obj) {
   if(!obj->getTemplate()->testByte(5,0x80)) m_mousedOverDrawableID=draw->getID();
   const Player* player=0;
   const ThingTemplate* thingTemplate=obj->getTemplate();
   ContainModuleInterface* contain=obj->getContain();
   if(contain) player=contain->getApparentControllingPlayer(ThePlayerList->getLocalPlayer());
   if(!player) player=obj->getControllingPlayer();
   bool disguised=false;
   if(obj->isKindOf(KINDOF_DISGUISER)) {
    static NameKeyType key_SpecialDisguiseUpdate=TheNameKeyGenerator->nameToKey("SpecialDisguiseUpdate");
    SpecialDisguiseUpdate* update=(SpecialDisguiseUpdate*)obj->findModule(key_SpecialDisguiseUpdate);
    if(update) {
     Player* clientPlayer=ThePlayerList->getLocalPlayer();
     if(player->getRelationship(clientPlayer->getDefaultTeam())!=ALLIES && clientPlayer->isPlayerActive()) {
      const ThingTemplate* replacement=(const ThingTemplate*)((Rva004B031E*)update)->rva004B031E();
      if(replacement) {thingTemplate=replacement;disguised=true;}
     }
    }
   } else {
    Rva00373EC6* component=const_cast<Object*>(obj)->rva0028F4BC();
    if(component && component->thingTemplate && !((Rva002A7DD0*)ThePlayerList)->rva002A7DD0() &&
       ThePlayerList->getLocalPlayer()->getRelationship(obj->getTeam())==NEUTRAL) {
     player=ThePlayerList->getNthPlayer(component->playerIndex);
     thingTemplate=component->thingTemplate;disguised=true;
    }
   }
   AsciiString drawKey;
   UnicodeString str;
   if(disguised) str=thingTemplate->getDisplayName();else str=*(const UnicodeString*)const_cast<Object*>(obj)->getDisplayName();
   if(const_cast<Drawable*>(draw)->rva00274C62(&drawKey)) str=TheGameText->fetchAscii(drawKey);
   AsciiString objectKey;
   if(const_cast<Object*>(obj)->rva0029137E(objectKey)) str=TheGameText->fetchAscii(objectKey);
   UnicodeString displayName=str;
   if(str.isEmpty()) {
    AsciiString txtTemp;
    txtTemp.format("ThingTemplate:%s",obj->getTemplate()->getName().str());
    str=TheGameText->fetchAscii(txtTemp);
   }
   UnicodeString warehouseFeedback;
   static NameKeyType warehouseModuleKey=TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
   SupplyWarehouseDockUpdate* warehouseModule=(SupplyWarehouseDockUpdate*)obj->findModule(warehouseModuleKey);
   if(warehouseModule) {
    int boxes=warehouseModule->getBoxesStored();
    int value=boxes*TheGlobalData->baseValuePerSupplyBox;
    warehouseFeedback.format(TheGameText->fetchRef("TOOLTIP:SupplyWarehouse"),value);
    str.concat(warehouseFeedback);
   }
   if(player) {
    UnicodeString tooltip;
    if(TheRecorder->isMultiplayer() && player->rva002AA245())
     tooltip.format(L"%s\n%s",str.str(),player->getPlayerDisplayName().str());
    else tooltip=str;
    int localPlayerIndex=ThePlayerList?ThePlayerList->getLocalPlayer()->getPlayerIndex():0;
    Coord3D cursorWorld={0,0,0};
    if(io) TheTacticalView->screenToWorld(&io->pos,&cursorWorld);
    if(ThePartitionManager->getShroudStatusForPlayer(localPlayerIndex,obj->getPosition())==CELLSHROUD_CLEAR ||
       (obj->getTemplate()->testByte(11,0x40) && ThePartitionManager->getShroudStatusForPlayer(localPlayerIndex,&cursorWorld)==CELLSHROUD_CLEAR)) {
     RGBColor rgb;
     if(disguised) rgb.setFromInt(player->getPlayerColor());
     else {
      rgb.setFromInt(draw->getObject()->getIndicatorColor());
      const Object* drawObj=draw->getObject();
      if(drawObj) {
       ContainModuleInterface* garrison=drawObj->getContain();
       if(garrison && garrison->isGarrisonable()) {
        const Player* apparent=garrison->getApparentControllingPlayer(ThePlayerList->getLocalPlayer());
        if(apparent) rgb.setFromInt(apparent->getPlayerColor());
       }
      }
     }
     if(displayName.compare(TheGameText->fetchChars("OBJECT:Prop"))) {
      bool sendOrdinaryTooltip=true;
      if(TheControlBar) {
       const Player* owner=obj->getControllingPlayer();
       if((owner && owner->isLocalPlayer() && (obj->getTemplate()->testByte(1,2) ||
          obj->getTemplate()->testByte(1,1) ||obj->getTemplate()->testByte(1,8) ||
          obj->getTemplate()->testByte(1,4) ||obj->getTemplate()->testByte(0,0x80))) ||
          obj->getTemplate()->testByte(6,4)) {
        { TooltipRecord record(obj->getID(),m_tooltipContext);
        TheControlBar->bfmeShowDN((BfmeMsgDN*)&record); }
        if(!TheGlobalData->tooltipFlag && !warehouseModule)sendOrdinaryTooltip=false;
       }
      }
      if(sendOrdinaryTooltip)TheMouse->rva001EEA6D(tooltip,-1,&rgb);
     }
    }
   }
  }
 } else m_mousedOverDrawableID=INVALID_DRAWABLE_ID;
 if(oldID!=m_mousedOverDrawableID)((Rva001EEC4B*)TheMouse)->rva001EEC4B();
 if(m_mouseMode==0 && !m_isScrolling && !m_isSelecting && !TheInGameUI->getSelectCount() &&
    (TheRecorder->getMode()!=RECORDERMODETYPE_PLAYBACK || ((BfmeOwnVVD*)TheLookAtTranslator)->Rva0042E8C1())) {
  if(m_mousedOverDrawableID!=INVALID_DRAWABLE_ID) {
   Drawable* draw=TheGameClient->findDrawableByID(m_mousedOverDrawableID);
   const Object* obj=draw?draw->getObject():0;
   bool drawSelectable=CanSelectDrawable(draw,false);
   if(!obj)drawSelectable=false;
   if(drawSelectable && obj->isLocallyControlled())setMouseCursor(Mouse::SELECTING);
   else setMouseCursor(Mouse::ARROW);
  }else setMouseCursor(Mouse::ARROW);
 } else if(m_mouseMode!=0) setMouseCursor((Mouse::MouseCursor)m_mouseModeCursor);
}

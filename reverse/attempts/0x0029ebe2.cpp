// ?createMouseoverHint@InGameUI@@UAEXPBVGameMessage@@@Z
// partial score=0.99 date=2026-10-05
// ?createMouseoverHint@InGameUI@@UAEXPBVGameMessage@@@Z
// partial score=0.98 date=2026-10-02
// cl: /O1 /arch:SSE /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS
// Unmatched reconstruction; 1899 compiled bytes versus 1901 retail bytes.
// Boundary: VA 0x0069EBE2 through 0x0069F34E; 575 retail instructions.
// Native body SHA256: 8885bffe9252ec3c5304c5a9359351616d70f40424e52f70147752c3a346cc09.
// Retail game.dat SHA256: f008b587570bad693981dc7218588c81d192a1e064b0f7f861539c51156a7640.
// Semantic donor: GeneralsMD InGameUI::createMouseoverHint, BFME1 checkout
// 10af19f44a89ab7ecc23195bb9a842ceafbc02c9, at inputs/reference/
// CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/InGameUI.cpp.
// Donor names and purpose are semantic leads. Target instructions establish
// the offsets, virtual slot numbers, call destinations, and argument shapes.
// Rva-labelled classes/helpers preserve uncertain target identities. The
// TooltipRecord/TooltipBase names describe an inferred 12-byte record ABI.
// The compare throw() declaration and inner record scope are compiler-shape
// hypotheses: they remove extra exception states and a Boolean spill.
// They do not establish the original source spelling or declaration.
//
// Remaining verification gap (wave3 l12, 2026-10-05): this body compiles to
// the 1901-byte target extent, and the player-name fallback at native VA
// 0x0069F003 now emits the target add/jump sequence in EAX. The side-by-side
// disassembly has no non-relocation instruction differences. Sixteen direct
// REL32 callees remain unresolved by the current symbol map, so their exact
// call operands are unproved. Names below are donor-semantic or structural
// leads, not target identity facts; check callee identity and placement before
// adding any pins or landing this body.
// The SEH handler and record vtable addresses are diagnostic mappings; their
// generated metadata and whole-program linkage have not been verified.
// Score 0.98 estimates reconstruction readiness, not byte equality.
//
// Recompile through tools/explain_mismatch.py with:
//   --source reverse/attempts/0x0029ebe2.cpp --rva 0x0029EBE2 --size 1901
//   selector: ?createMouseoverHint@InGameUI@@UAEXPBVGameMessage@@@Z
// Resolve calls against their observed targets, not a similarly named thunk.
//
// Observed native call destinations (RVA; mangled-name fragments):
//   0x00037050 ??0?$StringBase@G
//   0x00036E70 releaseBuffer@?$StringBase@G
//   0x00036410 releaseBuffer@?$StringBase@D
//   0x00037150 set@?$StringBase@G
//   0x00006A7A compare@?$StringBase@G
//   0x00006A2A concat@?$StringBase@G
//   0x00038150 format@AsciiString
//   0x006CB660 format@UnicodeString@@QAAXPBV
//   0x006CB5D0 format@UnicodeString@@QAAXPBG
//   0x00629188 __EH_prolog
//   0x0030F45F winGetStatus@GameWindow
//   0x003140A4 winGetParent@GameWindow
//   0x0028AFA9 getControllingPlayer@Object
//   0x0028B07A isLocallyControlled@Object
//   0x002A9D89 isLocalPlayer@Player
//   0x0006F039 isKindOf@Object
//   0x0030F4EA getArgument@GameMessage
//   0x00004EDF setFromInt@RGBColor
//   0x0037B18C isMultiplayer@RecorderClass
//   0x002A7A29 getNthPlayer@PlayerList
//   0x007397F0 getShroudStatusForPlayer@PartitionManager
//   0x001EEA6D rva001EEA6D@Mouse
//   0x0055A88B getID@Drawable
//   0x00274C62 Rva00274C62@Drawable
//   0x002AA231 Rva002AA231@Player
//   0x002AA245 Rva002AA245@Player
//   0x002A7DD0 Rva002A7DD0@PlayerList
//   0x004B031E Rva004B031E@SpecialDisguiseUpdate
//   0x0028B6D6 Rva0028B6D6@Object
//   0x0028F4BC Rva0028F4BC@Object
//   0x0028F2F8 Rva0028F2F8@Object
//   0x0029137E Rva0029137E@Object
//   0x0028B026 getIndicatorColor@Object
//   0x002AD0C6 getRelationship@Player
//   0x0030F2C7 Rva0030F2C7@RecorderClass
//   0x0042E8C1 Rva0042E8C1@LookAtTranslator
//   0x001EEC4B resetTooltipDelay@Mouse
//   0x0029A5D6 setMouseCursor@InGameUI
//   0x00405C04 Rva00405C04@TooltipController
//   0x0042FA63 CanSelectDrawable@@
//
// Observed absolute references (VA; symbol/string-name fragments):
//   0x00DFDCA0 TheMouse
//   0x00DFEF1C TheWindowManager
//   0x00DFE77C TheGameClient
//   0x00DFEEE8 ThePlayerList
//   0x00DF36A4 TheNameKeyGenerator
//   0x00DFF0BC TheGameText
//   0x00DFEA3C TheTacticalView
//   0x00DFE74C ThePartitionManager
//   0x00E02290 TheRecorder
//   0x00E03214 TheLookAtTranslator
//   0x00DFE758 TheGlobalData
//   0x00E01CFC TheTooltipController
//   0x00DFEDF0 TheInGameUI
//   0x00E0C898 TheEmptyString
//   0x00BBB5C4 TheNullChr
//   0x00DFEEC0 key_SpecialDisguiseUpdate
//   0x00DFEEBC warehouseModuleKey
//   0x00BFD010 ??_7TooltipRecord
//   0x00BE5838 ??_7TooltipBase
//   0x00DFEEC4 ?$S1
//   0x00B74D69 __ehhandler$
//   0x00000000 __except_list
//   0x00BF4EC0 SpecialDisguiseUpdate
//   0x00BF507C SupplyWarehouseDockUpdate
//   0x00BFD228 TOOLTIP?3SupplyWarehouse
//   0x00BFD240 ThingTemplate?3
//   0x00BFD210 OBJECT?3Prop
//   0x00BFD21C @_1M@
//   0x00BBAC1C @_00
//
// Additional local diagnostics remain in ignored build/byte-match-0029ebe2/.
typedef unsigned short wchar_t;
typedef unsigned int UnsignedInt;
enum DrawableID { INVALID_DRAWABLE_ID = 0 };
enum NameKeyType { NAMEKEY_INVALID = 0 };
enum KindOfType { KINDOF_DISGUISER = 300 };
enum Relationship { NEUTRAL = 0, ALLIES = 2 };
enum CellShroudStatus { CELLSHROUD_CLEAR = 0 };
struct ICoord2D { int x, y; };
struct Coord3D { float x, y, z; };
struct RGBColor { float red, green, blue; void setFromInt(int); };
class AsciiString; class UnicodeString;
template<class T> class StringBase {
 friend class AsciiString; friend class UnicodeString;
 public:
 void set(const StringBase<T>&);
 void concat(const StringBase<T>&);
 int compare(const StringBase<T>&) const throw();
 private:
 StringBase(const StringBase<T>&);
 void releaseBuffer();
};
class AsciiString {
 public:
 AsciiString() : m_buffer(0) {}
 ~AsciiString() { ((StringBase<char>*)this)->releaseBuffer(); }
 void __cdecl format(const char*, ...);
 const char* str() const { return m_buffer ? m_buffer->data : ""; }
 private:
 struct Header { int refs; unsigned short length,capacity; char data[1]; };
 Header* m_buffer;
};
class UnicodeString {
 public:
 static const UnicodeString TheEmptyString;
 UnicodeString() : m_buffer(0) {}
 UnicodeString(const UnicodeString& that) { ((StringBase<wchar_t>*)this)->StringBase<wchar_t>::StringBase(*(const StringBase<wchar_t>*)&that); }
 ~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }
 UnicodeString& operator=(const UnicodeString& that) { ((StringBase<wchar_t>*)this)->set(*(const StringBase<wchar_t>*)&that); return *this; }
 bool isEmpty() const { return !m_buffer || m_buffer->length==0; }
 const wchar_t* str() const { static const wchar_t TheNullChr=0; const wchar_t *result=(const wchar_t*)m_buffer; if (result) result=(const wchar_t*)((const char*)result+8); else result=&TheNullChr; return result; }
 void concat(const UnicodeString& that) { ((StringBase<wchar_t>*)this)->concat(*(const StringBase<wchar_t>*)&that); }
 int compare(const UnicodeString& that) const { return ((const StringBase<wchar_t>*)this)->compare(*(const StringBase<wchar_t>*)&that); }
 void __cdecl format(const wchar_t*,...);
 void __cdecl format(const UnicodeString*,...);
 private:
 struct Header { int refs; unsigned short length,capacity; wchar_t data[1]; };
 Header* m_buffer;
};
class Object; class ThingTemplate; class Player; class Team; class Drawable;
class GameWindow; class ContainModuleInterface; class SpecialDisguiseUpdate; class SupplyWarehouseDockUpdate;
class DisguiseComponent; class TooltipRecord;
struct MouseIO { ICoord2D pos; };
class Mouse {
 public:
 enum MouseCursor { ARROW=2, SELECTING=13 };
 void rva001EEA6D(UnicodeString,int=-1,const RGBColor * =0,float=1.0f);
 void resetTooltipDelay();
 const MouseIO* getMouseStatus() const { return &m_io; }
 unsigned char pad[0x4f0c]; MouseIO m_io;
};
extern Mouse* TheMouse;

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
 bool Rva00274C62(AsciiString&) const;
 unsigned char pad[0xfc]; Object* object;
};
class Player { public:
 Relationship getRelationship(const Team*) const;
 bool Rva002AA231() const;
 bool Rva002AA245() const;
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
 bool Rva002A7DD0();
 unsigned char pad[0x10]; Player* local;
};
extern PlayerList* ThePlayerList;

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
class DisguiseComponent { public: unsigned char pad[0x38]; int playerIndex; const ThingTemplate* thingTemplate; };
class Module {};
class SpecialDisguiseUpdate : public Module { public: const ThingTemplate* Rva004B031E() const; };
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
 Module* Rva0028B6D6(NameKeyType) const;
 DisguiseComponent* Rva0028F4BC() const;
 const UnicodeString& Rva0028F2F8() const;
 bool Rva0029137E(AsciiString&) const;
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
class PartitionManager { public: CellShroudStatus getShroudStatusForPlayer(int,const Coord3D*) const; };
extern PartitionManager* ThePartitionManager;
class RecorderClass { public: bool isMultiplayer(); int Rva0030F2C7(); };
extern RecorderClass* TheRecorder;
class LookAtTranslator { public: bool Rva0042E8C1(); };
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
class TooltipController { public: void Rva00405C04(const TooltipRecord*); };
extern TooltipController* TheTooltipController;
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
void setMouseCursor(Mouse::MouseCursor);
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
    SpecialDisguiseUpdate* update=(SpecialDisguiseUpdate*)obj->Rva0028B6D6(key_SpecialDisguiseUpdate);
    if(update) {
     Player* clientPlayer=ThePlayerList->getLocalPlayer();
     if(player->getRelationship(clientPlayer->getDefaultTeam())!=ALLIES && clientPlayer->Rva002AA231()) {
      const ThingTemplate* replacement=update->Rva004B031E();
      if(replacement) {thingTemplate=replacement;disguised=true;}
     }
    }
   } else {
    DisguiseComponent* component=obj->Rva0028F4BC();
    if(component && component->thingTemplate && !ThePlayerList->Rva002A7DD0() &&
       ThePlayerList->getLocalPlayer()->getRelationship(obj->getTeam())==NEUTRAL) {
     player=ThePlayerList->getNthPlayer(component->playerIndex);
     thingTemplate=component->thingTemplate;disguised=true;
    }
   }
   AsciiString drawKey;
   UnicodeString str;
   if(disguised) str=thingTemplate->getDisplayName();else str=obj->Rva0028F2F8();
   if(draw->Rva00274C62(drawKey)) str=TheGameText->fetchAscii(drawKey);
   AsciiString objectKey;
   if(obj->Rva0029137E(objectKey)) str=TheGameText->fetchAscii(objectKey);
   UnicodeString displayName=str;
   if(str.isEmpty()) {
    AsciiString txtTemp;
    txtTemp.format("ThingTemplate:%s",obj->getTemplate()->getName().str());
    str=TheGameText->fetchAscii(txtTemp);
   }
   UnicodeString warehouseFeedback;
   static NameKeyType warehouseModuleKey=TheNameKeyGenerator->nameToKey("SupplyWarehouseDockUpdate");
   SupplyWarehouseDockUpdate* warehouseModule=(SupplyWarehouseDockUpdate*)obj->Rva0028B6D6(warehouseModuleKey);
   if(warehouseModule) {
    int boxes=warehouseModule->getBoxesStored();
    int value=boxes*TheGlobalData->baseValuePerSupplyBox;
    warehouseFeedback.format(TheGameText->fetchRef("TOOLTIP:SupplyWarehouse"),value);
    str.concat(warehouseFeedback);
   }
   if(player) {
    UnicodeString tooltip;
    if(TheRecorder->isMultiplayer() && player->Rva002AA245())
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
      if(TheTooltipController) {
       const Player* owner=obj->getControllingPlayer();
       if((owner && owner->isLocalPlayer() && (obj->getTemplate()->testByte(1,2) ||
          obj->getTemplate()->testByte(1,1) ||obj->getTemplate()->testByte(1,8) ||
          obj->getTemplate()->testByte(1,4) ||obj->getTemplate()->testByte(0,0x80))) ||
          obj->getTemplate()->testByte(6,4)) {
        { TooltipRecord record(obj->getID(),m_tooltipContext);
        TheTooltipController->Rva00405C04(&record); }
        if(!TheGlobalData->tooltipFlag && !warehouseModule)sendOrdinaryTooltip=false;
       }
      }
      if(sendOrdinaryTooltip)TheMouse->rva001EEA6D(tooltip,-1,&rgb);
     }
    }
   }
  }
 } else m_mousedOverDrawableID=INVALID_DRAWABLE_ID;
 if(oldID!=m_mousedOverDrawableID)TheMouse->resetTooltipDelay();
 if(m_mouseMode==0 && !m_isScrolling && !m_isSelecting && !TheInGameUI->getSelectCount() &&
    (TheRecorder->Rva0030F2C7()!=1 || TheLookAtTranslator->Rva0042E8C1())) {
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

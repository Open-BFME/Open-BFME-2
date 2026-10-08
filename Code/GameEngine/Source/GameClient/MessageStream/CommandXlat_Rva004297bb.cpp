// cl: -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/shims/stringbaseunicode /O1 /G7 /arch:SSE /ICode/Libraries/Include -Ireference/open-bfme-1/game/GameEngine/Source/GameClient/MessageStream
// stlport
// Ported from GeneralsMD/Code/GameEngine/Source/GameClient/MessageStream/CommandXlat.cpp.
// Copyright 2025 Electronic Arts Inc.; GPL-3.0-or-later, as in the vendored source.
// BFME layout/call witnesses: build/gap_005ade0d/LAYOUTS.md and region_{a,b}.asm.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}

#include "ascii_string.h"
#include "Common/UnicodeString.h"
inline UnicodeString::~UnicodeString() { ((StringBase<wchar_t>*)this)->releaseBuffer(); }
#include "Lib/Coord3D.h"
struct ICoord2D { int x,y; };
struct IRegion2D { ICoord2D lo,hi; int width() const { return hi.x-lo.x; } int height() const { return hi.y-lo.y; } };
class Drawable; class Object; class Player; class ThingTemplate; class CommandButton;
class PickAndPlayInfo;
class Rva004D92FE { public:
 Rva004D92FE();
 bool field00; char pad01[3]; Drawable* m_drawTarget; void* m_weaponSlot;
 void* field0c; int m_specialPowerType; Coord3D m_position; void* field1c;
};
typedef _STL::list<Drawable*> SelectedDrawableList;
union GameMessageArgumentType { int integer; unsigned drawableID; ICoord2D pixel; IRegion2D pixelRegion; Coord3D location; };
enum ObjectID { OBJECTID_NONE=0 };
class GameMessage { public:
 enum Type { MSG_INVALID=0, MSG_CREATE_SELECTED_GROUP=0x3e9 };
 char pad00[0x10]; Type m_type;
 Type getType() const { return m_type; }
 const GameMessageArgumentType* getArgument(int) const;
 void appendBooleanArgument(bool); void appendObjectIDArgument(ObjectID);
 void appendLocationArgument(const struct Coord3D&);
};
enum GameMessageDisposition { KEEP_MESSAGE, DESTROY_MESSAGE };
enum CommandEvaluateType { DO_COMMAND, DO_HINT, DO_EVALUATE };
class AudioEventRTS { public: AudioEventRTS(const AsciiString&,int); ~AudioEventRTS(); void* m_vftable; char opaque04[0x6c]; };
class CommandButton { public: char pad00[0x10]; int m_command; bool isContextCommand() const; int getCommandType() const { return m_command; } };
enum KindOfType { KINDOF_PLACEHOLDER };
class Thing { public: bool isKindOf(KindOfType) const; };

class SpawnBehaviorInterface {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual Object* getClosestSlave(const Coord3D*); // vtable +0x8

};

enum CanAttackResult { ATTACKRESULT_NONE,ATTACKRESULT_INVALID_SHOT,ATTACKRESULT_VALID2,ATTACKRESULT_VALID3 };
enum AbleToAttackType { ATTACK_TYPE_ZERO,ATTACK_TYPE_ONE };
enum CommandSourceType { SOURCE_ZERO };
struct ForceAttackTemplate { char pad[0x108]; unsigned char kind108; char pad109[9]; unsigned char kind112; };
class Object {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual Drawable* getDrawable() const; // vtable +0x28

 ForceAttackTemplate* m_template; char pad08[0x30]; Coord3D m_position; char pad44[0x30]; ObjectID m_id;
 char pad78[0x19c]; Object* m_containedBy;
 ObjectID getID() const { return m_id; }
 const Coord3D* getPosition() const { return &m_position; }
 bool isKindOf(int k) const { return ((const Thing*)this)->isKindOf((KindOfType)k); }
 bool isLocallyControlled() const;
 bool isAbleToAttack() const;
 CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType,const Object*,CommandSourceType) const;
 CanAttackResult getAbleToUseWeaponAgainstTarget(AbleToAttackType,const Object*,const Coord3D*,CommandSourceType) const;
 SpawnBehaviorInterface* getSpawnBehaviorInterface() const;

};

class Drawable { public: char pad00[0xfc]; Object* m_object; Object* getObject() const { return m_object; } const Coord3D* getPosition() const; };
class PlayerTemplate { public: char pad00[0xe4]; AsciiString m_beaconTemplate; const AsciiString& getBeaconTemplate() const { return m_beaconTemplate; } };
class Player { public: char pad00[4]; PlayerTemplate* m_playerTemplate;
 const PlayerTemplate* getPlayerTemplate() const { return m_playerTemplate; }
 bool isPlayerActive() const;
 Object* rva000D4660(bool,Object**) const;
 int iterateObjects(int (*)(Object*,void*),void*) const;
 void countObjectsByThingTemplate(int,const ThingTemplate* const*,bool,int*,bool) const;
};
class PlayerList { public: char pad00[0xc]; Player* m_localPlayer; Player* getLocalPlayer() const { return m_localPlayer; } };
class ControlBar { public: const CommandButton* findCommandButton(const AsciiString&); void togglePurchaseScience(); };
class GameLogic { public: char pad00[0x91]; bool m_showBehindBuildingMarkers; char pad92[0x7a]; int m_mode;
 bool isInMultiplayerGame(); bool rva000652A0() const; bool isInReplayGame() const { return m_mode==3; }
};
// TU-local field view of retail's GlobalData; the one writable global at
// 0x012ED5C8 is declared with EA's own class below and cast at each use.
class RvaGlobalDataView { public:
 char pad00[0x38]; bool m_useCloudMap; char pad39[0xb]; bool m_useLightMap; char pad45[0x1b]; bool m_useAlternateMouse;
 char pad61[3]; bool m_useShadowVolumes; char pad65[0xaa7]; int m_netMinPlayers; char padb10[0x7c]; int m_maxParticleCount;
 char padb90[0xc9]; bool m_TiVOFastMode;
};
class Mouse { public: char pad00[0x10ec]; unsigned m_dragTolerance; char pad10f0[4]; unsigned m_clickTime;
 bool rva005A49E0(const ICoord2D*,const ICoord2D*) const;
};
class Radar { public: bool rva00107140(Coord3D*); };
class Rva004891C0 { public: char pad00[0x4d]; bool field4d; bool test() const; };
class Rva003968A0 { public: bool test(); };
enum RecorderModeType { RECORDER_NONE };
class RecorderClass { public: RecorderModeType getMode(); };
enum NameKeyType { NAMEKEY_NONE };
class NameKeyGenerator { public: NameKeyType nameToKey(const AsciiString&); };
class GameWindow { public: bool winIsHidden(); };
class ThingFactory { public: const ThingTemplate* findTemplate(const AsciiString&); };
class MultiplayerSettings { public: char pad00[0x14]; int m_maxBeaconsPerPlayer; int getMaxBeaconsPerPlayer() { return m_maxBeaconsPerPlayer; } };

class InGameUI {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void __cdecl message(UnicodeString,...); // MSVC overloaded slot +0x34
    virtual void __cdecl message(AsciiString,...); // MSVC overloaded slot +0x30
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void setGUICommand(const CommandButton*); // vtable +0xB8
    virtual const CommandButton* getGUICommand(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void selectDrawable(Drawable*); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void deselectAllDrawables(); // vtable +0xE8
    virtual void selectAllUnitsByType(int,Player*); // vtable +0xEC
    virtual int getSelectCount(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual Drawable* getFirstSelectedDrawable(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual const SelectedDrawableList* getAllSelectedDrawables() const; // vtable +0x124
    virtual void slot4A(); // vtable +0x128
    virtual void slot4B(); // vtable +0x12C
    virtual void slot4C(); // vtable +0x130
    virtual void slot4D(); // vtable +0x134
    virtual void slot4E(); // vtable +0x138
    virtual void slot4F(); // vtable +0x13C
    virtual void slot50(); // vtable +0x140
    virtual void slot51(); // vtable +0x144
    virtual void slot52(); // vtable +0x148
    virtual void slot53(); // vtable +0x14C
    virtual void slot54(); // vtable +0x150
    virtual void slot55(); // vtable +0x154
    virtual void slot56(); // vtable +0x158
    virtual void selectUnitsMatchingCurrentSelection(); // vtable +0x15C

 char pad04[0x12ac]; bool m_waypointMode; bool m_forceAttackMode; bool m_forceMoveMode; bool m_preferSelectionMode;
 bool m_cameraRotateLeft; bool m_cameraRotateRight; bool m_cameraZoomIn; bool m_cameraZoomOut;
 bool field12b8; bool field12b9; bool field12ba; bool field12bb;
 bool isInForceAttackMode() const { return m_forceAttackMode; }
 bool getInputEnabled() const;
 bool rva0043EC00() const;
 void rva0043CEC0();

};

class MessageStream {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); virtual void slot0E(); virtual void slot0F(); virtual void slot10(); virtual void slot11();
    virtual GameMessage* appendMessage(GameMessage::Type); // vtable +0x48

};

class GameClient {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual Drawable* findDrawableByID(unsigned); // vtable +0x2C
    virtual Drawable* firstDrawable(); // vtable +0x30

};

class View {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual Drawable* pickDrawable(const ICoord2D*,bool,int); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void lookAt(const Coord3D*); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void slot38(); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void slot3A(); // vtable +0xE8
    virtual void slot3B(); // vtable +0xEC
    virtual void slot3C(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual void slot41(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual const SelectedDrawableList* getAllSelectedDrawables() const; // vtable +0x124
    virtual void slot4A(); // vtable +0x128
    virtual void slot4B(); // vtable +0x12C
    virtual void slot4C(); // vtable +0x130
    virtual void slot4D(); // vtable +0x134
    virtual void slot4E(); // vtable +0x138
    virtual void slot4F(); // vtable +0x13C
    virtual void slot50(); // vtable +0x140
    virtual void slot51(); // vtable +0x144
    virtual void slot52(); // vtable +0x148
    virtual void slot53(); // vtable +0x14C
    virtual void slot54(); // vtable +0x150
    virtual void slot55(); // vtable +0x154
    virtual void slot56(); // vtable +0x158
    virtual void slot57(); // vtable +0x15C
    virtual void slot58(); // vtable +0x160
    virtual void screenToTerrain(const ICoord2D*,Coord3D*,bool); // vtable +0x164

};

class WindowLayout {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void hide(bool); // vtable +0x10
 char pad04[0x10]; bool m_hidden;
};

class Shell { public: char pad00[0x58]; bool m_active; WindowLayout* top(); };
class GameWindowManager {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual GameWindow* winGetWindowFromId(GameWindow*,int); // vtable +0xDC

};

class GameInfo {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual bool isMultiPlayer() const; // vtable +0x2C

};

class AudioManager {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual unsigned addAudioEvent(const AudioEventRTS*); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void slot38(); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void slot3A(); // vtable +0xE8
    virtual void slot3B(); // vtable +0xEC
    virtual void slot3C(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual void slot41(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual const char* getMiscAudio() const; // vtable +0x124

};

class Display {
public:
    virtual void slot00(); // vtable +0x0
    virtual void slot01(); // vtable +0x4
    virtual void slot02(); // vtable +0x8
    virtual void slot03(); // vtable +0xC
    virtual void slot04(); // vtable +0x10
    virtual void slot05(); // vtable +0x14
    virtual void slot06(); // vtable +0x18
    virtual void slot07(); // vtable +0x1C
    virtual void slot08(); // vtable +0x20
    virtual void slot09(); // vtable +0x24
    virtual void slot0A(); // vtable +0x28
    virtual void slot0B(); // vtable +0x2C
    virtual void slot0C(); // vtable +0x30
    virtual void slot0D(); // vtable +0x34
    virtual void slot0E(); // vtable +0x38
    virtual void slot0F(); // vtable +0x3C
    virtual void slot10(); // vtable +0x40
    virtual void slot11(); // vtable +0x44
    virtual void slot12(); // vtable +0x48
    virtual void slot13(); // vtable +0x4C
    virtual void slot14(); // vtable +0x50
    virtual void slot15(); // vtable +0x54
    virtual void slot16(); // vtable +0x58
    virtual void slot17(); // vtable +0x5C
    virtual void slot18(); // vtable +0x60
    virtual void slot19(); // vtable +0x64
    virtual void slot1A(); // vtable +0x68
    virtual void slot1B(); // vtable +0x6C
    virtual void slot1C(); // vtable +0x70
    virtual void slot1D(); // vtable +0x74
    virtual void slot1E(); // vtable +0x78
    virtual void slot1F(); // vtable +0x7C
    virtual void slot20(); // vtable +0x80
    virtual void slot21(); // vtable +0x84
    virtual void slot22(); // vtable +0x88
    virtual void slot23(); // vtable +0x8C
    virtual void slot24(); // vtable +0x90
    virtual void slot25(); // vtable +0x94
    virtual void slot26(); // vtable +0x98
    virtual void slot27(); // vtable +0x9C
    virtual void slot28(); // vtable +0xA0
    virtual void slot29(); // vtable +0xA4
    virtual void slot2A(); // vtable +0xA8
    virtual void slot2B(); // vtable +0xAC
    virtual void slot2C(); // vtable +0xB0
    virtual void slot2D(); // vtable +0xB4
    virtual void slot2E(); // vtable +0xB8
    virtual void slot2F(); // vtable +0xBC
    virtual void slot30(); // vtable +0xC0
    virtual void slot31(); // vtable +0xC4
    virtual void slot32(); // vtable +0xC8
    virtual void slot33(); // vtable +0xCC
    virtual void slot34(); // vtable +0xD0
    virtual void slot35(); // vtable +0xD4
    virtual void slot36(); // vtable +0xD8
    virtual void slot37(); // vtable +0xDC
    virtual void slot38(); // vtable +0xE0
    virtual void slot39(); // vtable +0xE4
    virtual void slot3A(); // vtable +0xE8
    virtual void slot3B(); // vtable +0xEC
    virtual void slot3C(); // vtable +0xF0
    virtual void slot3D(); // vtable +0xF4
    virtual void slot3E(); // vtable +0xF8
    virtual void slot3F(); // vtable +0xFC
    virtual void slot40(); // vtable +0x100
    virtual void slot41(); // vtable +0x104
    virtual void slot42(); // vtable +0x108
    virtual void slot43(); // vtable +0x10C
    virtual void slot44(); // vtable +0x110
    virtual void slot45(); // vtable +0x114
    virtual void slot46(); // vtable +0x118
    virtual void slot47(); // vtable +0x11C
    virtual void slot48(); // vtable +0x120
    virtual void takeScreenShot(); // vtable +0x124

};

extern InGameUI* TheInGameUI;
extern GameClient* TheGameClient;
extern MessageStream* TheMessageStream;
extern PlayerList* ThePlayerList;
extern View* TheTacticalView;
extern GameLogic* TheGameLogic;
class GlobalData;
extern GlobalData* TheWritableGlobalData;
static inline RvaGlobalDataView* localGlobalData() { return (RvaGlobalDataView*)TheWritableGlobalData; }
extern Mouse* TheMouse;
extern Radar* TheRadar;
extern ControlBar* TheControlBar;
extern Shell* TheShell;
extern RecorderClass* TheRecorder;
extern GameWindowManager* TheWindowManager;
extern NameKeyGenerator* TheNameKeyGenerator;
extern ThingFactory* TheThingFactory;
extern MultiplayerSettings* TheMultiplayerSettings;
extern GameInfo* TheGameInfo;
extern AudioManager* TheAudio;
extern Display* TheDisplay;
// Retail 0x012F3330 is EA's GameWindowTransitionsHandler *TheTransitionHandler;
// Rva004891C0 is this TU's view of the object, so every use casts.
class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler* TheTransitionHandler;
// 0x012F1028 is the one Glo012F1028 global.  Rva003968A0 above is this TU's
// view of that object (its test() is a pinned callee), so the use casts.
class Glo012F1028Type;

extern void* g_va012F71B4;
extern void* g_va012F4988;
void rva00511CC0(int);
void HideInGameChat();
void rva0052B2A0();
void rva00569D80();
void Rva004C1040(int);
int Rva00459060(bool);
int rva005A9B00(Object*,void*);
class DrawableList;
void pickAndPlayUnitVoiceResponse(const DrawableList*,GameMessage::Type,PickAndPlayInfo* = 0);

class CommandTranslator { public:
 virtual GameMessageDisposition translateGameMessage(const GameMessage*);
 virtual ~CommandTranslator();
private:
 int opaque04; bool m_teamExists; char pad09[3];
 ICoord2D m_mouseRightDragAnchor, m_mouseRightDragLift;
 unsigned m_mouseRightDown, m_mouseRightUp, field24, field28; bool field2c;
 CommandEvaluateType evaluateContextCommand(Drawable*,const Coord3D*,CommandEvaluateType);
 int evaluateForceAttack(Drawable*,const Coord3D*,CommandEvaluateType);
 void rva005A9C90(const GameMessage*);
};

struct HeroHolder { Object* hero; Object* previous; };

static Object* iNeedAHero(Object* previous)
{
 Player* localPlayer=ThePlayerList->getLocalPlayer();
 if(!localPlayer) return 0;
 HeroHolder holder; holder.hero=0; holder.previous=previous;
 localPlayer->iterateObjects(rva005A9B00,&holder);
 if(!holder.hero && previous) { holder.previous=0; localPlayer->iterateObjects(rva005A9B00,&holder); }
 return holder.hero;
}

// ZH canObjectForceAttack, reference34f59164f6; native4291C8..429276
// and WB00E79D50 preserve the three argument meanings. Native uses EDI/ESI
// for the first two arguments; keeping the static noinline definition with
// its actual callers lets MSVC reproduce that internal calling convention.
// Target kind bits108:04 and112:10 replace the donor queries; all object
// attack calls bind existing native providers. Coord3D uses its canonical tag.
static __declspec(noinline) int canObjectForceAttack(Object* obj,const Object* victim,const Coord3D* pos)
{
 if(!obj->isAbleToAttack()) return 0;
 if(victim) {
  int result=obj->getAbleToAttackSpecificObject(ATTACK_TYPE_ONE,victim,SOURCE_ZERO);
  if(result!=3 && result!=2 && (obj->m_template->kind112&0x10)) {
   SpawnBehaviorInterface* spawn=obj->getSpawnBehaviorInterface();
   if(spawn) { Object* slave=spawn->getClosestSlave(victim->getPosition()); if(slave) result=slave->getAbleToAttackSpecificObject(ATTACK_TYPE_ONE,victim,SOURCE_ZERO); }
  }
  return result;
 }
 if(pos) {
  if((obj->m_template->kind108&4) || (obj->m_template->kind112&0x10)) {
   SpawnBehaviorInterface* spawn=obj->getSpawnBehaviorInterface();
   if(spawn) spawn->getClosestSlave(pos);
  }
  return obj->getAbleToUseWeaponAgainstTarget(ATTACK_TYPE_ZERO,0,pos,SOURCE_ZERO);
 }
 return 0;
}
static __declspec(noinline) int canAnyForceAttack(const SelectedDrawableList* allSelected,const Object* victim,const Coord3D* pos)
{
 for(SelectedDrawableList::const_iterator it=allSelected->begin();it!=allSelected->end();++it) {
  Drawable* draw=*it; if(!draw) continue;
  Object* obj=draw->getObject(); if(!obj) continue;
  return canObjectForceAttack(obj,victim,pos);
 }
 return 0;
}

// ?CommandTranslator::evaluateForceAttack present-unmatched
int CommandTranslator::evaluateForceAttack(Drawable* draw,const Coord3D* pos,CommandEvaluateType type)
{
 int retVal=0;
 if(!draw && !pos) return retVal;
 const SelectedDrawableList* allSelected=TheInGameUI->getAllSelectedDrawables();
 if(draw) {
  Object* obj=draw->getObject();
  if(!obj) return retVal;
  int result=canAnyForceAttack(allSelected,obj,pos);
  if(result==3 || result==2) {
   retVal=0x425;
   if(type==DO_COMMAND) {
    Rva004D92FE info;
    info.m_drawTarget=draw;
    pickAndPlayUnitVoiceResponse((const DrawableList*)allSelected,(GameMessage::Type)0x425,(PickAndPlayInfo*)&info);
    GameMessage* newMsg=TheMessageStream->appendMessage((GameMessage::Type)0x425);
    newMsg->appendObjectIDArgument(obj->getID());
    newMsg->appendLocationArgument(*pos);
   } else if(type==DO_HINT) {
    retVal=0x9b;
    TheMessageStream->appendMessage((GameMessage::Type)0x9b);
   }
  } else if(result==1 && type==DO_HINT) {
   retVal=0x9a;
   TheMessageStream->appendMessage((GameMessage::Type)0x9a);
  }
 } else if(pos) {
  int result=canAnyForceAttack(allSelected,0,pos);
  if(result==3 || result==2) {
   retVal=0x426;
   if(type==DO_COMMAND) {
    Rva004D92FE info;
    info.m_position=*pos;
    pickAndPlayUnitVoiceResponse((const DrawableList*)allSelected,(GameMessage::Type)0x426,(PickAndPlayInfo*)&info);
    GameMessage* newMsg=TheMessageStream->appendMessage((GameMessage::Type)0x426);
    newMsg->appendLocationArgument(*pos);
   } else if(type==DO_HINT) {
    retVal=0x9c;
    TheMessageStream->appendMessage((GameMessage::Type)0x9c);
   }
  } else if(result==1 && type==DO_HINT) {
   retVal=0x9a;
   TheMessageStream->appendMessage((GameMessage::Type)0x9a);
  }
 }
 return retVal;
}

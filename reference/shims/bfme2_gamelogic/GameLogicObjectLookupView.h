// The canonical GameLogic view, verbatim but for the BFME 2 members this TU's rows reach (marked "BFME 2:").
// Copied from Code/GameEngine/Source/Common/GameLogicObjectLookupView.h
#pragma once

// BFME 2: the by-value members below need these complete.
#include "ascii_string.h"
#include <map>
#include <vector>

// BFME 2's native lookup at 0x00049DC5 uses the ObjectID enum and a map
// receiver at +0xB4. The provider's existing accessed prefix is shared here;
// complete GameLogic and map extents remain unreconstructed. Pointer-only
// callers do not construct these views or depend on their sizeof.
// Reference-backed consumers may already have the same ObjectID enum.
#ifndef _GAME_TYPE_H_
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};
#endif

class Xfer;
class GameMessage;
class BfmeThingEC;
class Object;
class Drawable;
class Rva00439E0C;
class AsciiString;
class CommandButton;
class WindowLayout;
class Rva0023E928;
class UnicodeString;
class TerrainResourceManager;
class LoadScreen;
class UpdateModule;
class GameInfo;
class ThingTemplate;
class Team;
struct CreateMask;
struct ObjectTOCEntry;
struct Rva0040D2FDVec;
struct Rva003F468DParticipant;
enum BuildableStatus;

struct ObjectIdNode
{
	char pad[8];
	Object *object;
};

class ObjectIdMap
{
public:
	ObjectIdNode *find(const ObjectID &id);
};

// The network code reads the command timestamp at +0x38 and Zero Hour's
// frame counter at +0x40 (ConnectionManager::update 0x004D342A, among others).
// StealthUpdate::disguiseAsObject (0x00373DF0) reads the manager at +0x178
// whose call 0x00439E0C takes the disguised object. The spell store's show
// (finishShowPurchaseScience 0x0043CB48) reads the end flag at +0x6D and
// the game mode at +0x110.
// InGameUI::addFloatingText (0x002A0D19) gates on the byte at +0x9A, Zero
// Hour's getDrawIconUI.
// The object list head is at +0xAC: getFirstObject (0x0023CAD2) returns it and
// prepareLogicForObjectLoad (0x00242C86) walks it inline.
// ScoreKeeper::addObjectLost (0x0039CF73) tests the scoring byte at +0x98
// first, as Zero Hour's isScoringEnabled does.
// GameClient::update (0x0023BEE8) reads the byte at +0x125, next to the pause
// byte isGamePaused (0x0023CD97) returns from +0x124, and skips the drawable,
// terrain and display updates while it is set.
// Object::initObject (0x002934E7) and setTriggerAreaFlagsForChangeInPosition
// (0x00291EB1) store the current frame at +0x180, as Zero Hour's
// updateObjectsChangedTriggerAreas stores m_frameObjectsChangedTriggerAreas.
// The script setters 0x003BB700 and 0x003BCA7B store their bool argument in
// the scoring byte (+0x98) and the icon-UI byte (+0x9A).
// PlaceEventTranslator::translateGameMessage (0x0043218A) swaps its
// pendingBuild/builderObj spill homes with the TU's declaration count, and
// not monotonically: before the +0x11C..+0x150 members joined, adding 1-8 or
// 13-15 declarations broke it and 9-12 or 16-19 kept it. Check it after
// adding members here; dead `extern int` lines in a scratch copy find the
// exact windows.
// BFME 2: setPlayerLeaveStatus 0x0023D1A5 and rva0023D17D 0x0023D17D store these fields; stride 0x1C.
struct PlayerLeaveStatus
{
	int m_status;
	int m_quitFrame;
	int m_defeatFrame;
	int m_victoryFrame;
	bool m_notPresent;
	unsigned char m_unknown11[3];
	int m_isHuman;
	AsciiString m_playerName;
};

// BFME 2: Save 0x0040F19D runs on the +0x184 member with the object list.
class ArmySummarySystem
{
public:
	void rva0040D280(Object*,int);
	void Save(Object *objects);
};

// BFME 2: the key and mapped types of the +0x24 map, rows 0x00242F5E and 0x00246FF6.
struct TreeKey00242F5E { int m_id; AsciiString m_name; };
struct TreeOpaqueMapped242F5E { unsigned int m_bits; };
typedef _STL::map<TreeKey00242F5E, TreeOpaqueMapped242F5E, _STL::less<TreeKey00242F5E>, _STL::allocator<_STL::pair<const TreeKey00242F5E, TreeOpaqueMapped242F5E> > > ControlBarOverrideMap;

// BFME 2: registerObject 0x00242AE9 pushes through the row vector<const ModuleData*>::push_back 0x004DFCB0.
class ModuleData;
typedef _STL::vector<const ModuleData *> UpdateModuleVector;
// BFME 2: destroyAllObjectsImmediate 0x00243B52 clears the +0x164 vector of these.
struct Rva00243B52DestroyEntry;

class GameLogic
{
	char pad[0x24];
	// BFME 2: setControlBarOverride 0x0024792F and rva00246F8E 0x00246F8E reach the map at +0x24.
	ControlBarOverrideMap m_controlBarOverrides; // +0x24
	char pad30[0x38 - 0x30];
	unsigned int m_timestamp;
	char pad3C[0x40 - 0x3C];

public:
	// Read directly by the network, script-debug and object-finish units
	// (ConnectionManager_rva004D0A0A, ScriptEngineAppendDebugMessage, ...).
	unsigned int m_frame; // +0x40, the frame getFrame returns

private:
	char pad44[0x54 - 0x44];
	// BFME 2: bfmePopulateGameReport 0x00247378 builds the report in these.
	AsciiString m_gameReport; // +0x54
	_STL::vector<AsciiString> m_gameReportDetails; // +0x58
	AsciiString m_commandLineArguments; // +0x64
	AsciiString m_gameReportTrailer; // +0x68
	bool m_gameReportReady; // +0x6C

public:
	bool m_6d; // +0x6D

private:
	char pad6E[0x98 - 0x6E];
	bool m_isScoringEnabled; // +0x98
	char pad99[0x9A - 0x99];
	bool m_drawIconUI; // +0x9A
	char pad9B[0xAC - 0x9B];
	Object *m_firstObject; // +0xAC, the head getFirstObject returns
	// BFME 2: registerObject 0x00242AE9 appends through &+0xAC and &+0xB0.
	Object *m_objListTail; // +0xB0
	ObjectIdMap m_map;
	char padB5[0xC8 - 0xB5];
	// BFME 2: registerObject 0x00242AE9 files each update module on one of these.
	UpdateModuleVector m_phaseUpdates[4]; // +0xC8
	UpdateModuleVector m_sleepingUpdates; // +0xF8
	char pad104[0x10C - 0x104];
	// BFME 2: rva0023CAD9 0x0023CAD9 post-increments this counter for Object::Object.
	int m_10c; // +0x10C

public:
	// BFME 2: DoExitMap 0x0023D0E3 reads the game mode here.
	int m_gameMode; // +0x110

	// Native AIUnitBuilder598052 and listener239457 compare this word.
	int m_114; // +0x114; precise mode meaning remains unresolved

private:
	char pad118[0x11C - 0x118];

public:
	// The script setter 0x003BD2A6 stores its flag here, calling
	// rva0023D68E first when the value changes.
	unsigned char m_field11C; // +0x11C

private:
	char pad11D[0x120 - 0x11D];
	// processProgress (0x0023D740) forwards to this screen's slot 0x10.
	LoadScreen *m_loadScreen; // +0x120
	// BFME 2: rva0023CD9E 0x0023CD9E sets the pause byte and saves input and mouse state in +0x126/+0x127.
	bool m_gamePaused; // +0x124
	bool m_flag125;
	bool m_inputEnabledMemory; // +0x126
	bool m_mouseVisibleMemory; // +0x127
	// processProgressComplete (0x0023D76E) sets a player's byte here and
	// lastHeardFrom (0x0023CF1C) stamps its timeGetTime timeout; 8 slots.
	unsigned char m_heardFlags[8]; // +0x128
	unsigned long m_progressCompleteTimeout[8]; // +0x130
	// BFME 2: rva0023CF3F 0x0023CF3F sets this flag, rva0023CEE5 0x0023CEE5 tests it.
	bool m_150; // +0x150
	char pad151[0x164 - 0x151];
	// BFME 2: rva00240EBC 0x00240EBC walks this vector at +0x164/+0x168.
	_STL::vector<Rva00243B52DestroyEntry *> m_objectsToDestroy; // +0x164
	// Native handleBuildPlacements (0x002A21E1) enumerates resource claimants
	// through this manager; WorldBuilder's corresponding field is at +0x174.
	TerrainResourceManager *m_resourceManager;
	char pad174[0x178 - 0x174];
	Rva00439E0C *m_manager178;
	char pad17C[0x180 - 0x17C];
	unsigned int m_frameObjectsChangedTriggerAreas; // +0x180
	// BFME 2: LivingWorldTacticalBattleComplete 0x0023D914 saves through +0x184 and stores the victor at +0x1B0.
	ArmySummarySystem m_armySummarySystem; // +0x184
	char pad185[0x1B0 - 0x185];
	int m_livingWorldVictorIndex; // +0x1B0
	char pad1B4[0x1B8 - 0x1B4];
	// Window cleanup 0x00376D49 owns this layout and clears the pending byte.
	// BFME1's closeWindows supplies its purpose; offsets are native BFME2.
	WindowLayout *m_background; // +0x1B8
	bool m_backgroundPending; // +0x1BC
	char pad1BD[0x1C4 - 0x1BD];
	// BFME 2: getPlayerLeaveStatus 0x0023D1E3 indexes eight 0x1C entries here.
	PlayerLeaveStatus m_playerLeaveStatus[8]; // +0x1C4

public:
	void logicMessageDispatcher(GameMessage *, void *); // Native 0x00377613
	void rva0023F8DA(); // Verified native 0x0023F8DA game-over details
	void rva0023DA49(); // Verified native 0x0023DA49 battle-complete wrapper
	void rva0023DA4E(); // Verified native 0x0023DA4E battle-complete gate
	void rva0023D68E(bool value); // 0x0023D68E, +0xAC object walk before the +0x11C store
	void selectObject(Object *, bool, unsigned int, bool); // Verified native 0x0023C924
	void ProcessCRC(unsigned int, int, unsigned int, GameMessage *, bool, BfmeThingEC *); // Verified native 0x00241529
	void rva0023D080(int); // Verified native 0x0023D080, forwards to the void ArmySummarySystem::CallArmyToEngageInBattleByID
	void CallPlayerGiveMoney(int, int, int); // Verified native 0x0023D793
	bool rva00085124();	// 0x00085124; verified mode 4-or-7 predicate
	bool isInMultiplayerGame();	// 0x00042235
	bool rva0042219();	// 0x00042219, mode gate rejecting 9, 4 and 7
	bool rva001DCD1C();	// 0x001DCD1C, mode 8 or mode 9 with +0x114 != 3
	void rva0023CD9E(bool paused, int pauseMode, bool affectMouse);	// 0x0023CD9E
	Object *findObjectByID(ObjectID id);
	void rva0023CFE4(Xfer *xfer); // 0x0023CFE4, Version1 plus native snapshot at +0x184
	void rva0023D033(); // 0x0023D033, native +0x184 cleanup forwarder
	const AsciiString *rva0023D05F(int value);	// 0x0023D05F, +0x184 army name by id
	const AsciiString *rva0023D06A(int value);	// 0x0023D06A, +0x184 army banner name by id
	int rva0023D08B(int value);	// 0x0023D08B, existing +0x184 forwarder
	void rva0023D0C2(Object *obj, int handle);	// 0x0023D0C2
	void TransitionFromLivingWorldTacticalBattle(); // 0x0023D0CD; timeline continue callback
	Object *getFirstObject();	// 0x0023CAD2
	int rva0023CAD9();	// 0x0023CAD9, next ObjectID for Object::Object 0x00298EA9
	void registerObject(Object *obj);	// 0x00242AE9, called by Object::Object 0x00298EA9
	void destroyObject(Object *obj);	// 0x00242C09
	void sendObjectDestroyed(Object *obj);	// 0x0023CD67, called by Object::~Object 0x00299CE4
	void rva0023CF8B();	// 0x0023CF8B, called by AptLoadScreen::init 0x0043A5F6
	void deselectObject(Object *obj, unsigned int playerMask, bool affectClient);	// 0x0023C9F8
	void bindObjectAndDrawable(Object *obj, Drawable *draw);	// 0x0023CD4A
	void clearGameData(bool first, bool second);	// 0x00376E92
	void rva00376D49();	// 0x00376D49, window cleanup, donor closeWindows
	void startNewGame(bool fromSave);	// 0x00248558, verified new-game/load pass
	unsigned char isGamePaused();	// 0x0023CD97
	bool rva002423E3();	// 0x002423E3
	void processDestroyList();	// 0x002413DF
	void prepareLogicForObjectLoad();	// 0x00242C86
	void processProgressComplete(int playerID);	// 0x0023D76E
	void CreateWOTRMPPlayers(); // 0x0023E99A; verified provider, campaign caller 0x0052C45E
	void setControlBarOverride(const AsciiString &commandSetName, int slot, const CommandButton *commandButton);	// 0x0024792F
	void ProcessSaveGameCommand(Rva0023E928 *msg, bool frozen);	// 0x00240866, multiplayer save request handler
	void rva0023D30F(int a, int b, UnicodeString *name);	// 0x0023D30F, thiscall spelling of the stdcall Rva0023D30FCall
	void enableScoring(bool score) { m_isScoringEnabled = score; }
	bool isScoringEnabled() const { return m_isScoringEnabled; }
	void setDrawIconUI(bool setting) { m_drawIconUI = setting; }
	void updateObjectsChangedTriggerAreas() { m_frameObjectsChangedTriggerAreas = m_frame; }
	bool getFlag125() const { return m_flag125; }
	unsigned int getTimestamp() const { return m_timestamp; }
	unsigned int getFrame() const { return m_frame; }
	bool getDrawIconUI() const { return m_drawIconUI; }
	Rva00439E0C *getManager178() const { return m_manager178; }
	TerrainResourceManager *getTerrainResourceManager() const { return m_resourceManager; }
	PlayerLeaveStatus *getPlayerLeaveStatus(int playerIndex); // 0x0023D1E3, verified eight-slot status accessor
	char rva0023C6FD();	// 0x0023C6FD
	void processCommandList();	// 0x0023CAA3
	unsigned int getCRC(int mode);	// 0x0023CB2C
	unsigned int getObjectCount();	// 0x0023CFCE
	void rva0023D007(int value);	// 0x0023D007, +0x184 forwarder
	int rva0023D0B7();	// 0x0023D0B7, +0x184 forwarder
	void DoExitMap(bool selfDestruct);	// 0x0023D0E3
	void rva0023D17D();	// 0x0023D17D
	void rva0023D201(int slotIndex, int status);	// 0x0023D201
	void processProgress(int playerId, int percentage);	// 0x0023D740
	void lastHeardFrom(int playerId);	// 0x0023CF1C
	void rva0023FABE(Object *obj);	// 0x0023FABE
	void friend_awakenUpdateModule(Object *obj, UpdateModule *updateModule, unsigned int when);	// 0x0024297F
	bool rva00245EDF(void *arg1, int *out);	// 0x00245EDF
	bool rva00246F8E(const AsciiString &setName, int slot, const CommandButton **button);	// 0x00246F8E
	bool rva0024877A();	// 0x0024877A
	void rva003BA5DD(int value);	// 0x003BA5DD
	void rva0023D028();	// 0x0023D028
	void rva0023D03E();	// 0x0023D03E
	void rva0023D054(int a, int b, Rva0040D2FDVec *out);	// 0x0023D054
	int rva0023D075(int value);	// 0x0023D075
	float rva0023D096(int value);	// 0x0023D096
	int rva0023D0A1(int value);	// 0x0023D0A1
	int rva0023D0AC(int value);	// 0x0023D0AC
	Object *friend_createObject(const ThingTemplate *thingTemplate, const CreateMask *mask, Team *team, ObjectID id);	// 0x0023CAE7
	ObjectTOCEntry *findTOCEntryByName(AsciiString name);	// 0x00240167
	void QueueForNotifyPathfindCellChanged(Object *obj);	// 0x00241C25
	void xferObjectTOC(Xfer *xfer);	// 0x00245F79
	void setBuildableStatusOverride(const ThingTemplate *thingTemplate, BuildableStatus status);	// 0x00246F71
	void bfmePopulateGameReport(GameInfo *game, int *localSlot);	// 0x00247378
	void formatPlayerStartWaypointName(AsciiString *out);	// 0x0024822B
	Rva003F468DParticipant *GetLivingWorldTacticalVictor();	// 0x0023D884
	// BFME 2: rows of this TU the canonical view does not declare.
	void setPlayerLeaveStatus(int slotIndex, const AsciiString &playerName, int isHuman);	// 0x0023D1A5
	bool rva0023CEE5();	// 0x0023CEE5
	void rva0023CF3F();	// 0x0023CF3F
	void LivingWorldTacticalBattleComplete();	// 0x0023D914
	void rva00240EBC();	// 0x00240EBC
	void addObjectToLookupTable(Object *obj);	// 0x00242AC2
	void destroyAllObjectsImmediate();	// 0x00243B52
};

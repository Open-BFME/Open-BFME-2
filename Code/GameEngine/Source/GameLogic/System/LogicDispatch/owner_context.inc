// Include context for GameLogicDispatch.cpp (GameLogic::logicMessageDispatcher, retail 0x00377613).
// cl-provenance: BFME1 cee35b7d8ca077d7255f1c39cb69e9fd9627aa85,
// game/GameEngine/Source/GameLogic/System/GameLogicDispatch.cpp (ZH-derived donor context); BFME2 views and
// call-site layouts below are read from independent BFME2 retail bytes / WB debug evidence.
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#define Matrix4x4 Matrix4

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "PreRTS.h"

#include "Common/CRCDebug.h"
#include "Common/GameAudio.h"
#include "Common/GameEngine.h"
#include "Common/GlobalData.h"
#include "Common/NameKeyGenerator.h"
#include "Common/ThingFactory.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "Common/MessageStream.h"
#include "Common/MultiplayerSettings.h"
#include "Common/Recorder.h"
#include "Common/BuildAssistant.h"
#include "Common/SpecialPower.h"
#include "Common/ThingTemplate.h"
#include "Common/Upgrade.h"
#include "Common/StatsCollector.h"
#include "Common/Radar.h"

#include "GameLogic/AIPathfind.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Locomotor.h"
#include "GameLogic/Object.h"
#include "GameLogic/ObjectCreationList.h"
#include "GameLogic/ObjectIter.h"

#include "GameLogic/AI.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/OpenContain.h"
#include "GameLogic/Module/ProductionUpdate.h"
#include "GameLogic/Module/SpecialPowerModule.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameLogic/VictoryConditions.h"
#include "GameLogic/Weapon.h"

// ZH declares pickAndPlayUnitVoiceResponse void; the retail body at 0x004DAAFD returns bool
// (its row ?pickAndPlayUnitVoiceResponse@@YA_N...), so bind the call to that one name.
#define pickAndPlayUnitVoiceResponse pickAndPlayUnitVoiceResponse_zhVoidDecl
#include "GameClient/CommandXlat.h"
#undef pickAndPlayUnitVoiceResponse
extern bool pickAndPlayUnitVoiceResponse( const DrawableList *list, GameMessage::Type msgType, PickAndPlayInfo *info = NULL );
#include "GameClient/ControlBar.h"
#include "GameClient/Drawable.h"
#include "GameClient/Eva.h"
#include "GameClient/GameText.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GuiCallbacks.h"
#include "GameClient/InGameUI.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/Mouse.h"
// Retail2AA223 is the rowed ParticleSystem::isSaveable leaf (+33A byte).
// The observer use shares that complete implementation; no second name is pinned.
enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID = 0 };
class ParticleSystem { public: bool isSaveable() const; };
#include "GameClient/Shell.h"
#include "GameClient/Module/BeaconClientUpdate.h"
#include "GameClient/LookAtXlat.h"

#include "GameNetwork/NetworkInterface.h"

#ifdef _INTERNAL

#endif

#define MAX_PATH_SUBJECTS 64
static Bool theBuildPlan = false;
static Object *thePlanSubject[MAX_PATH_SUBJECTS];
static int thePlanSubjectCount = 0;
Object *__fastcall getSingleObjectFromSelection(const AIGroup *);

// Native entry 377639..377661 forwards the Living World range before player
// selection. This provider remains unrowed; no provisional pin is supplied.
class LivingWorldLogic { public: void logicMessageDispatcher(GameMessage *, void *); void rva002BD544(int); };
extern LivingWorldLogic *TheLivingWorldLogic;
Bool Rva0037711ADoSetRallyPoint(Object *, const Coord3D *, Bool, Object *);
void Rva003774ABSetGlobalRallyPoint(Object *, const Coord3D *);

// BFME2 additions: native call signatures; private bank context only.
class LinearCampaignManager;
extern LinearCampaignManager *TheLinearCampaignManager;
class Rva001EB0B1Holder { public: void rva001EB0B1(); };
class Rva001EB72F { public: void rva001EB72F(); };
class Rva0023D607Holder { public: void rva001ECF03(int,int); };
class Rva0036E346;
class AiOrdersManager { public: void rva003559B5(int,Rva0036E346 *,int); void clearOrders(int,int); void rva00355949(int,Rva0036E346 *,const Coord3D &,bool,bool); void rva00355358(int,void *); void rva003558D6(int,Rva0036E346 *,int,const Coord3D &,float,bool); };
extern AiOrdersManager *TheAiOrdersManager;
class Rva003559B5Host { public: void rva00355A09(int,Rva0036E346 *,int); void rva00355A5D(int,Rva0036E346 *,int); void rva00355AB1(int,Rva0036E346 *); };
class Rva002AA257DwordSlot { public: void set(int); };
class BfmeHostABG { public: void bfmeVisitABG(void *,void *); };
// This provisional descriptive name still needs reconciliation with the existing
// frame-rate datum at VA00DBA4E4; no pin or second data definition is supplied.
extern int BfmeLogicFramesPerSecond;
class LogicDispatchRepairInterface {
public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void startSelfRepair(int); virtual void s14(); virtual void s18();
 virtual bool canPlayerRepair(Player *); virtual bool canSelfRepair();
 virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30();
 virtual void s34(); virtual void s38(); virtual void s3c(); virtual void s40();
 virtual void s44(); virtual void s48(); virtual bool canNeighborhoodRepair();
 virtual void s50(); virtual void startNeighborhoodRepair(int);
 virtual bool canPlayerNeighborhoodRepair(Player *); virtual void s5c();
 virtual void s60(); virtual bool canCancelNeighborhood(); virtual void cancelNeighborhood();
};
class LogicDispatchGateInterface {
public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual bool isOpen(); virtual void open();
 virtual void close(); virtual void s24(); virtual bool canChange();
};
// Data access observed in retail. These views are not canonical class contracts.
struct LogicDispatchPlayerView { char pad[0x750]; int orderMode; };
struct LogicDispatchGlobalDataView { char pad[0x11ca]; bool orderQueueEnabled; };
class CastleBehavior { public: static NameKeyType rva0003955DA(); void initiatePack(); void initiateUnpack(bool,const ThingTemplate *); };
class Rva0039567CCmpBoolField { public: bool get() const; };
class Rva00397F45 { public: bool isPlayerAllowedToPackOrUnpack(Player *,int); };
class Rva00395F57 { public: bool canUnpack(bool); };
class Rva0039718B { public: bool rva0039718B(Player *); };
class Rva00395686 { public: bool rva00395686(Player *,ThingTemplate *); };
struct Rva002CF1FBNode;
class Rva002CF1FB { public: Rva002CF1FBNode *findByTemplateID(unsigned short); };
struct LogicDispatchControlBarView { char pad[0x28]; bool dirty; };
class LogicDispatchHordeInterface { public:
 virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
 virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
 virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
 virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
 virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
 virtual void s50(); virtual void s54(); virtual void s58(); virtual bool canToggleFormation();
 virtual void toggleFormation(); virtual bool canSetFormation(Rva002CF1FBNode *);
 virtual void setFormation(Rva002CF1FBNode *);
};
class Rva0031D5F8 { public: void *rva0031D5F8(const AsciiString *); };
class AutoAbilityBehavior { public: void rva0045A6FE(void *); };
struct Rva0045A63FObject; class Rva0045A63FModule;
Rva0045A63FModule *Rva0045A63F(const Rva0045A63FObject *,const AsciiString &);
struct LogicDispatchButtonView { char p00[0x14]; int command; char p18[0x44-0x18]; const SpecialPowerTemplate *power; char p48[0x80-0x48]; int weapon; };
struct LogicDispatchPowerView { char p00[0x10]; AsciiString name; char p14[8]; int type; };

struct Rva00372571Params { const Coord3D *pos; bool flag; int a,b,c,d,e; bool f; Rva00372571Params(const Coord3D *p,bool b0):pos(p),flag(b0),a(0),b(0),c(0),d(-1),e(0),f(false) {} };
class Rva0036CB94 { public: Rva0036CB94(int,int,int,int,bool); char bytes[32]; };
class Rva0028B7AELeaGetter { public: void *get() const; };
class FiringTracker { friend class GameLogic; private: void coolDown(bool); };
struct LogicDispatchTemplateView { char p0[0x115]; unsigned char kind115; char p116[2]; unsigned char kind118; };
class LogicDispatchAIView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11c();
virtual void s120();
virtual void s124();
virtual void s128();
virtual void s12c();
virtual void s130();
virtual void s134();
virtual void s138();
virtual void s13c();
virtual void s140();
virtual void s144();
virtual void s148();
virtual void s14c();
virtual void s150();
virtual void s154();
virtual void s158();
virtual void s15c();
virtual void s160();
virtual void s164();
virtual void s168();
virtual void s16c();
virtual void s170();
virtual void s174();
virtual void s178();
virtual void s17c();
virtual void s180();
virtual void s184();
virtual void s188();
virtual void s18c();
virtual void s190();
virtual void s194();
virtual void s198();
virtual void s19c();
virtual void s1a0();
virtual void s1a4();
virtual void s1a8();
virtual void s1ac();
virtual void s1b0();
virtual void s1b4();
virtual void s1b8();
virtual bool s1bc();
};
class LogicDispatchContainView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual int s7c();
virtual void s80();
virtual void s84(bool);
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual bool se8(Object *);
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual unsigned int s114(int);
};
class LogicDispatchInGameUIView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void message(UnicodeString,...);
virtual void s44();
virtual void s48();
virtual void eventMessage(UnicodeString,...);
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void selectDrawable(Drawable *);
virtual void s10c();
virtual void deselectAll();
virtual void selectAll(bool,Player *);
};
struct LogicDispatchObjectView { char pad0[4]; const ThingTemplate *tmpl; char pad8[0x240-8]; FiringTracker *firing; char pad244[12]; LogicDispatchContainView *contain; char pad254[4]; AIUpdateInterface *ai; };
#include "GameNetwork/GameInfo.h"
struct BfmeSubobject0022CE19 {
    virtual ~BfmeSubobject0022CE19();
    unsigned char opaque[0xDE4];
    BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};
struct TreeHintOpaque0043671B {
    UnicodeString text; BfmeSubobject0022CE19 subobject; unsigned wordDEC,wordDF0;
    TreeHintOpaque0043671B(const TreeHintOpaque0043671B &r) : text(r.text),subobject(r.subobject),wordDEC(r.wordDEC),wordDF0(r.wordDF0) {}
    ~TreeHintOpaque0043671B();
};
class GameState { public: int rva002DE3C1(TreeHintOpaque0043671B); };
extern GameState *TheGameState;
class Rva0023E7D9 { public: void rva0023F88C(bool); };
class Rva00210C66CmpBoolField { public: bool get() const; };
void Rva00437E9C(int);
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva00222A8BTarget { public: void rva00222F55(bool); };
struct LogicDispatchGameInfoView { char p00[0x8c]; bool flag; char p8d[0xc8-0x8d]; TreeHintOpaque0043671B *save; };
struct LogicDispatchGameSlotView { char pad[0x4c]; int value; };
struct LogicDispatchGameLogicView { char pad[0x40]; unsigned int frame; bool start; char p45[0x110-0x45]; int mode; int gameType; };
struct OpaqueRefElement4;
#include "Code/GameEngine/Include/Common/BfmeAudioEventPrefix136.h"
class Rva002D9531 { public: void rva002D9531(int); };
class Rva0033F15DDwordSlot { public: void set(int); };
struct LogicDispatchPlayerIndexView { char pad[0x54]; int playerIndex; };
class LogicDispatchBuildAssistantView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void constructFoundation(Object *,ThingTemplate *,const Coord3D *,float,Player *);
virtual void constructWall(Object *,const Coord3D *,const Coord3D *,Player *,int,int);
};
class LogicDispatchAudioView { public:
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual int addEvent(const BfmeAudioEventPrefix136 *);
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11c();
virtual void s120();
virtual void s124();
virtual void s128();
virtual void s12c();
virtual void s130();
virtual void s134();
virtual const void *getMisc();
};


class Rva000E01A3 { public: bool rva000E01A3(); };

class BfmeSelectionState { public: bool isSelectionLocked() const; };
struct LogicDispatchPlayerTemplateView { char pad[0x17c]; AsciiString beacon; };
struct LogicDispatchDrawableModules { char pad[0x150]; Module **modules; };
class ActionManager;
extern ActionManager *TheActionManager;
class LogicDispatchActionManagerView { public:
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
 virtual void sell(Object *);
};

class Rva00377064 { public: void rva00377064(int,int,int); };
class Rva002B254F { public: int rva002B254F(); };
class Rva002BED10 { public: void rva002BED10(); };
class Rva0023D2D8DwordClearer { public: void clear(); };
class Rva0023D26F { public: void rva0023D26F(bool); };
class CopyProtect { public: static bool isVerified(); };
struct LogicDispatchUi174 { char pad[0x174]; bool flag; };
struct LogicDispatchCampaign10 { char pad[0x10]; int campaign; };
struct LogicDispatchShell5C { char pad[0x5c]; bool flag; };
class LogicDispatchNetworkRelease { public: virtual void *release(int); };
class LivingWorld;
// Target usage establishes the LivingWorld receiver; existing provisional
// address-global ownership remains a dependency, not a new pin or alias.
extern LivingWorld *TheLivingWorld;

class Rva0036E1F7 { public: void groupOverrideSpecialPowerDestination(int,int,int); };

class LogicDispatchProductionInterface { public:
 virtual void s00(); virtual void s04(); virtual int nextId(); virtual void s0c(); virtual void s10();
 virtual void cancelTemplate(const void *,bool);
 virtual void s18(); virtual void s1c();
 virtual bool queue(const ThingTemplate *,int,int,int,bool,const AsciiString &,bool);
 virtual void s24(); virtual void s28(); virtual void s2c(); virtual void cancelId(int);
};

class LogicDispatchDozerView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual int getIndex();
};
class LogicDispatchDozerAIView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11c();
virtual void s120();
virtual void s124();
virtual void s128();
virtual void s12c();
virtual void s130();
virtual void s134();
virtual void s138();
virtual void s13c();
virtual void s140();
virtual void s144();
virtual void s148();
virtual void s14c();
virtual void s150();
virtual void s154();
virtual void s158();
virtual void s15c();
virtual void s160();
virtual void s164();
virtual void s168();
virtual void s16c();
virtual void s170();
virtual LogicDispatchDozerView *getDozer();
};

struct LogicDispatchTemplateKinds { char pad[0x108]; unsigned int kinds[5]; };
class Rva0039B7AD;
class Rva003B0D7C { public: void rva003B0D7C(int,Rva0039B7AD *,bool); };
class Rva0028F59A { public: int bits[19]; Rva0028F59A(int,int); };
class Rva001E431E { public: void rva001E431E(const int *); };
class Rva001E42F2 { public: void rva001E42F2(const int *); };
struct LogicDispatchCancelObject { char a[0x324]; float cost; char b[0x438-0x328]; unsigned char flag; };
class LogicDispatchRefundInterface { public:
virtual void s00();virtual void s04();virtual void s08();virtual void s0c();virtual void s10();virtual void s14();
virtual bool hasRefund(); virtual void s1c();virtual void s20();virtual void s24();virtual void s28();
virtual bool noRefund();virtual void s30(); virtual float refund();
};
class Rva0037BBED { public: void rva0037D0A7(unsigned int,int,bool,unsigned int); };
struct LogicDispatchCRCPlayer { char a[0x38]; UnicodeString name; char b[0x5c-0x3c]; int type; };

class BfmeOwnVVD { public: unsigned char Rva0042E8C1(); };
class LinearOffsetTextureMapperClass { public: void Set_Current_UV_Offset(const Vector2 &); };
struct LogicDispatchViewLocation {
 bool valid; Coord3D pos; float angle,pitch,zoom,height;
 LogicDispatchViewLocation() : valid(false) {pos.zero();height=0;zoom=0;pitch=0;angle=0;}
 void init(float x,float y,float z,float a,float p,float zoomValue,float h) {pos.x=x;pos.y=y;pos.z=z;angle=a;pitch=p;zoom=zoomValue;height=h;valid=true;}
};
class LogicDispatchView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual bool cameraFinished();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual void scc();
virtual void sd0();
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
virtual void sf0();
virtual void sf4();
virtual void sf8();
virtual void sfc();
virtual void s100();
virtual void s104();
virtual void s108();
virtual void s10c();
virtual void s110();
virtual void s114();
virtual void s118();
virtual void s11c();
virtual void s120();
virtual void s124();
virtual void s128();
virtual void s12c();
virtual void s130();
virtual void s134();
virtual void s138();
virtual void s13c();
virtual void s140();
virtual void s144();
virtual void s148();
virtual void s14c();
virtual void s150();
virtual void s154();
virtual void s158();
virtual void s15c();
virtual void s160();
virtual void s164();
virtual void s168();
virtual void s16c();
virtual void s170();
virtual void setLocation(const LogicDispatchViewLocation *);
};

bool Rva0027DC65Check(float *);
struct CreateMask { unsigned bits[4]; CreateMask() {memset(bits,0,sizeof(bits));} };
class Rva002D9508 { public: void rva002D9508(const void *); };
class Rva00271496 { public: void rva00271496(); };

class LogicDispatchGameTextView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual UnicodeString fetch(const char *,bool *);
virtual void s40();
virtual const UnicodeString *getText(const char *,bool);
};

class Rva002AB5C7Player { public: void rva002AB44A(); };
void ShowStuckAsObserverInStrategicRTSGameMessage();

class LogicDispatchEngineView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void fpsLimit(int);
};

class LogicDispatchMessageStreamView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual GameMessage *append(GameMessage::Type);
};

class LogicDispatchVictoryView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual bool defeated(Player *);
};

class LogicDispatchMouseView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void position(int,int);
virtual void s48();
virtual void cursor(int);
};

class LogicDispatchNetworkView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
virtual void s4c();
virtual void s50();
virtual void s54();
virtual void s58();
virtual void s5c();
virtual void s60();
virtual void s64();
virtual void s68();
virtual void s6c();
virtual void s70();
virtual void s74();
virtual void s78();
virtual void s7c();
virtual void s80();
virtual void s84();
virtual void s88();
virtual void s8c();
virtual void s90();
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
virtual void sa8();
virtual void sac();
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual UnicodeString name(int);
virtual void sc0();
virtual void sc4();
virtual void sc8();
virtual bool connected(int);
};

class LogicDispatchModuleKeyView { public:
virtual void s0();
virtual void s4();
virtual void s8();
virtual void sc();
virtual NameKeyType key() const;
};

struct LogicDispatchSavedSlot { char prefix[0x4c]; int value; char tail[0x1ac-0x50]; };
struct LogicDispatchSavedSlots { char prefix[0x4c]; LogicDispatchSavedSlot slots[8]; };

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// Canonical StringBase wide-empty body: native 00035740, used inline in
// the dispatcher caption path (native 0037A580 tests buffer then length).
// The inline import view leaves the out-of-line copy to string_base_inline.cpp.
template<> __declspec(dllimport) inline bool StringBase<unsigned short>::isEmpty() const throw()
{
    return m_data == 0 || m_data->length == 0;
}

// cl: /Ireference/shims/bfmelist /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// stlport
#include <vector>
#include <list>
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class PlayerList;
extern PlayerList *ThePlayerList;
class Rva002A7DDEArg;
class Rva002A7DDE { public: bool rva002A7DDE(Rva002A7DDEArg *); };
class Rva00005C357FPtrChaseField { public: int get() const; };
class Rva00005C39A3PtrChaseField { public: int get() const; };
class Rva0057C22FByteChaseField { public: unsigned char get() const; };
class Rva005C39AA { public: void rva005C39AA(); };
class Rva005C3EE0 { public: void show(); };
class Rva005C3F02;
class Rva005677B9 { public: struct Payload { int v[2]; }; };
void Rva00567B6DAdd(Rva005C3F02 *,const Rva005677B9::Payload *);
class CommandButton {
public:
 int getStance(int);
 char pad[0x234];
 _STL::vector<int> stances;
};
// Prefix-only factory view: unused vslots specify layout, not signatures.
// Provider declarations above preserve their existing ABI, not class extents.
class StanceMenuFactory {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
 virtual Rva005C3F02 *getMenu();
};
class StancesBehavior;
// Neutral observer-base identity: retail restores table VA 0x00C6CE84.
// Two slots, and no destructor slot: RET4 at RVA 0x0047A69C and RET12 at
// 0x000D1407. The derived table at VA 0x00C6CF6C has the named unregister
// callback 0x00568143 and the changed-stance callback 0x00567B10. WorldBuilder
// supplies the behavior reference and signed old/new stance arguments; their
// original enum spelling remains unresolved, so this view uses integer ABI.
class Rva0086CE84Observer {
public:
 virtual void onDestroyingStancesBehavior(StancesBehavior&) {}
 virtual void onStancesBehaviorStanceChanged(StancesBehavior&, int, int) {}
 __forceinline ~Rva0086CE84Observer() {}
};
class CreateAHeroData;
class Rva002B7250 { public: void rva002B7250(CreateAHeroData*); };
struct StanceBehaviorPrefix { char pad[0x20]; Rva002B7250 observers; };
struct TargetRef00217D4C;
struct Rva002BED91 { TargetRef00217D4C *p; void clear(); };
struct Rva003591F4Arg {
 Rva003591F4Arg(const Rva003591F4Arg &other):m_id(other.m_id),m_flag(other.m_flag){}
 int m_id; bool m_flag;
};
// The existing release provider touches only the 12-byte prefix (ref +8).
// Retail's hotkey vector advances 16 bytes and tests its active flag at +12.
// Keep that extra flag in a distinct record instead of widening the prefix.
struct Rva004F691E { Rva003591F4Arg action; Rva002BED91 ref; ~Rva004F691E(); };
struct StanceHotKeyRecord : Rva004F691E { bool active; };
struct Rva005681CE : _STL::vector<StanceHotKeyRecord> { ~Rva005681CE(); };
class Rva005C3E79 { public: void rva005C3E79(); };
class Rva00E01E28Owner { public: void rva003591F4(Rva003591F4Arg); };
class HotKeyManager;
extern HotKeyManager *TheHotKeyManager;
class HotKeyManager { public: unsigned int removeMessageAction(int); };
int GetAssociatedMessageType(int);
class InGameToggleStanceCommandButton {
public:
 class Impl : public Rva0086CE84Observer {
 public:
  void OnLeftClicked();
  ~Impl();
  virtual void onDestroyingStancesBehavior(StancesBehavior&);
  virtual void onStancesBehaviorStanceChanged(StancesBehavior&, int, int);
 private:
  _STL::list<int>::iterator listPosition;
  Rva00005C357FPtrChaseField *owner08;
  StanceMenuFactory *factory0C;
  void *window10;
  CommandButton *button14;
  StanceBehaviorPrefix *behavior18;
  Rva005681CE hotKeys;
 };
};
// ?OnLeftClicked@Impl@InGameToggleStanceCommandButton@@QAEXXZ
// retail 0x00568021 (181 bytes), named by WorldBuilder 0x01431040.
// WorldBuilder supplies the menu check, object/relationship guard, three-item
// limit, and owner/stance payload construction. Retail supplies the accessed
// prefixes: owner +8, menu factory +0xC, command +0x14, stance vector +0x234.
// All direct calls use their existing verified signatures; GameLogic uses
// the canonical lookup view. The two-dword payload is the existing neutral
// Rva005677B9::Payload; its original class identity is not asserted here.
void InGameToggleStanceCommandButton::Impl::OnLeftClicked()
{
 Rva005C3F02 *menu=factory0C->getMenu();
 if(!menu) return;
 Object *object=TheGameLogic->findObjectByID(static_cast<ObjectID>(owner08->get()));
 if(object && (!ThePlayerList || !reinterpret_cast<Rva002A7DDE *>(ThePlayerList)->rva002A7DDE(reinterpret_cast<Rva002A7DDEArg *>(object)))) return;
 if(!reinterpret_cast<Rva0057C22FByteChaseField *>(menu)->get()) {
  int count=(int)button14->stances.size();
  for(int i=0;i<count && reinterpret_cast<Rva00005C39A3PtrChaseField *>(menu)->get()<3;++i) {
   Rva005677B9::Payload params;
   params.v[0]=reinterpret_cast<int>(this);
   params.v[1]=button14->getStance(i);
   Rva00567B6DAdd(menu,&params);
  }
  reinterpret_cast<Rva005C3EE0 *>(menu)->show();
 } else {
  reinterpret_cast<Rva005C39AA *>(menu)->rva005C39AA();
 }
}


//
// Vtable-slot bodies with no ledger owner and no Ghidra entry, batch AJ:
// each is a single tail jump to a rowed or pinned function on the same
// object (a derived slot that only runs its base's or a sibling's method).
// The forwarders are address-derived classes over the target's class,
// declared with the target's own signature; nothing else is modeled.

class Object;
class Xfer;
enum StateReturnType
{
	STATE_CONTINUE = 0
};
enum StateExitType
{
	EXIT_NORMAL = 0
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

class Rva006C1F60
{
public:
	bool rva00033D50();
};

class Rva001EDDBBForwarder
{
public:
	void rva001EDDBB();
};

class Win32GameEngine
{
public:
	virtual void * rva0005E959();
};

#include "../GameClient/Rva000869CF.h"

class VideoPlayer
{
public:
	virtual void Rva00689180();
};

class Rva0030ADE8Forwarder
{
public:
	void rva0030ADE8();
};

class Rva005CB260
{
public:
	void rva005CB260();
};

class W3DModelDraw
{
protected:
	virtual void loadPostProcess();
};

class Rva00131CEAForwarder
{
public:
	void rva00131CEA(int a);
};

class Rva002D35C7Forwarder
{
public:
	void rva002D35C7();
};

class Rva002D6AE2Forwarder
{
public:
	void rva002D6AE2();
};

class W3DProjectedShadow
{
public:
	void rva00108951();
};

class GameInfo
{
public:
	int getNumPlayers() const;
	int getNumOpenOrOccupiedSlots() const;
};

class AIUpdateInterface
{
public:
	virtual void onObjectCreated();
	virtual bool chooseLocomotorSet(int a);
	virtual bool getTreatAsAircraftForLocoDistToGoal() const;
protected:
	void wakeUpNow();
	virtual void loadPostProcess();
	virtual void privateIdle(CommandSourceType a);
};

class Rva0030BBE5
{
public:
	void rva0030BBE5(int a);
};

class CommandList
{
public:
	void destroyAllMessages();
};

class SidesList
{
public:
	void clear();
};

class StateMachine
{
public:
	virtual void setGoalObject(const Object *a);
};

class AIExitState
{
public:
	virtual StateReturnType onEnter();
	virtual StateReturnType update();
};

class BfmeThing932E
{
public:
	void bfmeTail932E();
};

class AIPickUpCrateState
{
public:
	virtual StateReturnType update();
};

class Rva00262CB6DwordClearer
{
public:
	void clear();
};

class GiantBirdNormalFlightState
{
public:
	virtual void onExit(StateExitType a);
};

class StealthUpdate
{
public:
	void rva003748BD();
};

class Rva0038404A
{
public:
	void rva00384E8E();
};

class TeamFactory
{
public:
	void clear();
};

class CreateModule
{
protected:
	virtual void xfer(Xfer *a);
};

class Rva000B56F0Object
{
public:
	void * selectStorage();
};

class Rva003145B1
{
public:
	int Rva003145B1Dispatch(int a, int b, int c);
};

class HordeContain
{
public:
	virtual void slot42(const Object *a);
};

class TransportContain
{
public:
	virtual void onCapture(int a, int b);
};

class Rva00497805
{
protected:
	virtual void loadPostProcess();
};

class Rva002645FF
{
public:
	bool rva002645FF();
};

class SpecialAbilityUpdate
{
public:
	virtual bool rva0044FC52();
	virtual void startUnpacking();
	virtual UpdateSleepTime update();
private:
	void onExit(bool a, bool b);
	friend class Rva00494E4D;
};

class GateOpenAndCloseBehavior
{
protected:
	virtual void xfer(Xfer *a);
};

class Rva00493009
{
protected:
	virtual void xfer(Xfer *a);
};

class Rva00507823
{
public:
	virtual void rva00507877();
};

class _bfme_AptGameWindow
{
public:
	int rva0051274F(int a, unsigned int b, unsigned int c);
};

class MovieWindowPlayback
{
public:
	void clear();
};

class XferSave
{
public:
	virtual void endBlock();
};

class AIEnterState
{
public:
	virtual void onExit(StateExitType a);
};

namespace StrategicHUD {
class SelectionDetailsUIImpl
{
public:
	void rva0057BA90();
};
}

class Rva005E717ENamed
{
public:
	const char * name() const;
};

class Rva005CC5DFNamed
{
public:
	const char * name() const;
};

class Rva005E39E0Named
{
public:
	const char * name() const;
};

class AIBuildable
{
public:
	void addNeed(int a);
};

#include "../../Include/Common/Overridable.h"

class Rva00420B2AZeroSetter
{
public:
	void disable();
};

class Rva005FD8C1
{
public:
	void rva005FD8C1();
};

class AptCIH
{
public:
	void rva006dbd80();
};

class BfmeAptValue006DCD20
{
public:
	void * rva006E04A0() const;
};

class AptValueWithHash
{
public:
	virtual void RegisterReferences() const;
};

namespace Debug_Statistics
{
int Get_Draw_Calls();
}
int Rva000A8F58Get();
int Rva000A8F5EGet();

// 0x00034D00: tail jump to Rva006C1F60::rva00033D50.
class Rva00034D00 : public Rva006C1F60
{
public:
	bool rva00034D00();
};


// 0x00041A06: tail jump to Rva001EDDBBForwarder::rva001EDDBB.
class Rva00041A06 : public Rva001EDDBBForwarder
{
public:
	void rva00041A06();
};
void Rva00041A06::rva00041A06()
{
	Rva001EDDBBForwarder::rva001EDDBB();
}

// 0x00099109: tail jump to Rva00041A06::rva00041A06 (W3DMouse vftable slot
// 9, the Zero Hour reset position; the existing W3DMouse::reset row sits in
// slot 1, so this keeps an address-derived name).
class Rva00099109 : public Rva00041A06
{
public:
	void rva00099109();
};

// 0x00041E65: tail jump to Win32GameEngine::rva0005E959.
class Rva00041E65 : public Win32GameEngine
{
public:
	void * rva00041E65();
};
void * Rva00041E65::rva00041E65()
{
	return Win32GameEngine::rva0005E959();
}

// 0x00043F94: tail jump to Debug_Statistics::Get_Draw_Calls.
class Rva00043F94
{
public:
	int rva00043F94();
};
int Rva00043F94::rva00043F94()
{
	return Debug_Statistics::Get_Draw_Calls();
}

// 0x00062972: tail jump to Rva000A8F58Get.
class Rva00062972
{
public:
	int rva00062972();
};
int Rva00062972::rva00062972()
{
	return Rva000A8F58Get();
}

// 0x00062977: tail jump to Rva000A8F5EGet.
class Rva00062977
{
public:
	int rva00062977();
};
int Rva00062977::rva00062977()
{
	return Rva000A8F5EGet();
}

// 0x00088D05: tail jump to Rva000869CF::rva000869CF.
class Rva00088D05 : public Rva000869CF
{
public:
	float * rva00088D05();
};
float * Rva00088D05::rva00088D05()
{
	return Rva000869CF::rva000869CF();
}

// 0x000907B7: tail jump to VideoPlayer::Rva00689180.
class Rva000907B7 : public VideoPlayer
{
public:
	void rva000907B7();
};
void Rva000907B7::rva000907B7()
{
	VideoPlayer::Rva00689180();
}

// 0x00098560: tail jump to Rva0030ADE8Forwarder::rva0030ADE8.
class Rva00098560 : public Rva0030ADE8Forwarder
{
public:
	void rva00098560();
};
void Rva00098560::rva00098560()
{
	Rva0030ADE8Forwarder::rva0030ADE8();
}

// 0x000B23D8: tail jump to Rva005CB260::rva005CB260.
class Rva000B23D8 : public Rva005CB260
{
public:
	void rva000B23D8();
};
void Rva000B23D8::rva000B23D8()
{
	Rva005CB260::rva005CB260();
}

// 0x000B23DD: tail jump to the slot +0x18 vcall thunk ??_9@$BBI@AE (0x005CB274):
// a call through a constant pointer to the seventh virtual, which cl routes
// through the vcall thunk instead of loading the vtable inline.
class Rva000B23DDTarget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
};
class Rva000B23DD : public Rva000B23DDTarget
{
public:
	void rva000B23DD();
};
void Rva000B23DD::rva000B23DD()
{
	void (Rva000B23DDTarget::*method)() = &Rva000B23DDTarget::v6;
	(this->*method)();
}

// 0x000CA132: tail jump to Rva000B3A2D::rva000B3A2D.
class Rva000CA132 : public W3DModelDraw
{
public:
	void rva000CA132();
};

// 0x000EF961: tail jump to Rva00131CEAForwarder::rva00131CEA.
class Rva000EF961 : public Rva00131CEAForwarder
{
public:
	void rva000EF961(int a);
};
void Rva000EF961::rva000EF961(int a)
{
	Rva00131CEAForwarder::rva00131CEA(a);
}

// 0x001040E7: tail jump to Rva002D35C7Forwarder::rva002D35C7.
class Rva001040E7 : public Rva002D35C7Forwarder
{
public:
	void rva001040E7();
};
void Rva001040E7::rva001040E7()
{
	Rva002D35C7Forwarder::rva002D35C7();
}

// 0x001040EC: tail jump to Rva002D6AE2Forwarder::rva002D6AE2.
class Rva001040EC : public Rva002D6AE2Forwarder
{
public:
	void rva001040EC();
};
void Rva001040EC::rva001040EC()
{
	Rva002D6AE2Forwarder::rva002D6AE2();
}

// 0x00109643: tail jump to W3DProjectedShadow::rva00108951.
class Rva00109643 : public W3DProjectedShadow
{
public:
	void rva00109643();
};
void Rva00109643::rva00109643()
{
	W3DProjectedShadow::rva00108951();
}

// 0x0022C4CF: tail jump to GameInfo::getNumPlayers.
class Rva0022C4CF : public GameInfo
{
public:
	int rva0022C4CF() const;
};
int Rva0022C4CF::rva0022C4CF() const
{
	return GameInfo::getNumPlayers();
}

// 0x0022C4D4: tail jump to GameInfo::getNumOpenOrOccupiedSlots.
class Rva0022C4D4 : public GameInfo
{
public:
	int rva0022C4D4() const;
};
int Rva0022C4D4::rva0022C4D4() const
{
	return GameInfo::getNumOpenOrOccupiedSlots();
}

// 0x002628B1: tail jump to AIUpdateInterface::wakeUpNow.
class Rva002628B1 : public AIUpdateInterface
{
public:
	void rva002628B1();
};
void Rva002628B1::rva002628B1()
{
	AIUpdateInterface::wakeUpNow();
}

// 0x0030BCBA: tail jump to Rva0030BBE5::rva0030BBE5.
class Rva0030BCBA : public Rva0030BBE5
{
public:
	void rva0030BCBA(int a);
};
void Rva0030BCBA::rva0030BCBA(int a)
{
	Rva0030BBE5::rva0030BBE5(a);
}

// 0x00311092: tail jump to CommandList::destroyAllMessages.
class Rva00311092 : public CommandList
{
public:
	void rva00311092();
};
void Rva00311092::rva00311092()
{
	CommandList::destroyAllMessages();
}

// 0x0032E53D: tail jump to SidesList::clear.
class Rva0032E53D : public SidesList
{
public:
	void rva0032E53D();
};

// 0x0033FCDC: tail jump to StateMachine::setGoalObject.
class Rva0033FCDC : public StateMachine
{
public:
	void rva0033FCDC(Object *a);
};
void Rva0033FCDC::rva0033FCDC(Object *object)
{
	StateMachine::setGoalObject(object);
}

// 0x00341D1C: tail jump to AIExitState::onEnter.
class Rva00341D1C : public AIExitState
{
public:
	StateReturnType rva00341D1C();
};
StateReturnType Rva00341D1C::rva00341D1C()
{
	return AIExitState::onEnter();
}

// 0x00341D21: tail jump to AIExitState::update.
class Rva00341D21 : public AIExitState
{
public:
	StateReturnType rva00341D21();
};
StateReturnType Rva00341D21::rva00341D21()
{
	return AIExitState::update();
}

// 0x00349D8D: tail jump to BfmeThing932E::bfmeTail932E.
class Rva00349D8D : public BfmeThing932E
{
public:
	void rva00349D8D();
};
void Rva00349D8D::rva00349D8D()
{
	BfmeThing932E::bfmeTail932E();
}

// 0x00368095: tail jump to AIPickUpCrateState::update.
class Rva00368095 : public AIPickUpCrateState
{
public:
	StateReturnType rva00368095();
};
StateReturnType Rva00368095::rva00368095()
{
	return AIPickUpCrateState::update();
}

// 0x003681ED: tail jump to AIUpdateInterface::onObjectCreated.
class Rva003681ED : public AIUpdateInterface
{
public:
	void rva003681ED();
};
void Rva003681ED::rva003681ED()
{
	AIUpdateInterface::onObjectCreated();
}

// 0x003682E2: tail jump to AIUpdateInterface::chooseLocomotorSet.
class Rva003682E2 : public AIUpdateInterface
{
public:
	bool rva003682E2(int a);
};
bool Rva003682E2::rva003682E2(int a)
{
	return AIUpdateInterface::chooseLocomotorSet(a);
}

// 0x003682E7: tail jump to Rva00262CB6DwordClearer::clear.
class Rva003682E7 : public Rva00262CB6DwordClearer
{
public:
	void rva003682E7();
};
void Rva003682E7::rva003682E7()
{
	Rva00262CB6DwordClearer::clear();
}

// 0x003682EC: tail jump to AIUpdateInterface::getTreatAsAircraftForLocoDistToGoal.
class Rva003682EC : public AIUpdateInterface
{
public:
	bool rva003682EC() const;
};
bool Rva003682EC::rva003682EC() const
{
	return AIUpdateInterface::getTreatAsAircraftForLocoDistToGoal();
}

// 0x003697F4: tail jump to GiantBirdNormalFlightState::onExit.
class Rva003697F4 : public GiantBirdNormalFlightState
{
public:
	void rva003697F4(StateExitType a);
};
void Rva003697F4::rva003697F4(StateExitType a)
{
	GiantBirdNormalFlightState::onExit(a);
}

// 0x00374FD0: tail jump to StealthUpdate::rva003748BD.
class Rva00374FD0 : public StealthUpdate
{
public:
	void rva00374FD0();
};
void Rva00374FD0::rva00374FD0()
{
	StealthUpdate::rva003748BD();
}

// 0x00385BDC: tail jump to Rva0038404A::rva00384E8E.
class Rva00385BDC : public Rva0038404A
{
public:
	void rva00385BDC();
};
void Rva00385BDC::rva00385BDC()
{
	Rva0038404A::rva00384E8E();
}

// 0x003A44DA: tail jump to CreateModule::xfer.
class Rva003A44DA : public CreateModule
{
public:
	void rva003A44DA(Xfer *a);
};
void Rva003A44DA::rva003A44DA(Xfer *a)
{
	CreateModule::xfer(a);
}

// 0x004333FE: tail jump to Rva000B56F0Object::selectStorage.
class Rva004333FE : public Rva000B56F0Object
{
public:
	void * rva004333FE();
};
void * Rva004333FE::rva004333FE()
{
	return Rva000B56F0Object::selectStorage();
}

// 0x004444A9: tail jump to Rva003145B1::Rva003145B1Dispatch.
class Rva004444A9 : public Rva003145B1
{
public:
	int rva004444A9(int a, int b, int c);
};
int Rva004444A9::rva004444A9(int a, int b, int c)
{
	return Rva003145B1::Rva003145B1Dispatch(a, b, c);
}

// 0x004766BE: tail jump to HordeContain::slot42.
class Rva004766BE : public HordeContain
{
public:
	void rva004766BE(const Object *a);
};
void Rva004766BE::rva004766BE(const Object *object)
{
	HordeContain::slot42(object);
}

// 0x0047E33F: tail jump to TransportContain::onCapture.
class Rva0047E33F : public TransportContain
{
public:
	virtual void rva0047E33F(int a, int b);
};
void Rva0047E33F::rva0047E33F(int a, int b)
{
	TransportContain::onCapture(a, b);
}

// 0x00483CEF: tail jump to Rva00497805::loadPostProcess.
class Rva00483CEF : public Rva00497805
{
public:
	void rva00483CEF();
};

// 0x0048F46D: tail jump to Rva002645FF::rva002645FF.
class Rva0048F46D : public Rva002645FF
{
public:
	bool rva0048F46D();
};
bool Rva0048F46D::rva0048F46D()
{
	return Rva002645FF::rva002645FF();
}

// 0x00494E21: tail jump to SpecialAbilityUpdate::rva0044FC52.
class Rva00494E21 : public SpecialAbilityUpdate
{
public:
	bool rva00494E21();
};


// 0x00494E48: tail jump to SpecialAbilityUpdate::startUnpacking.
class Rva00494E48 : public SpecialAbilityUpdate
{
public:
	void rva00494E48();
};

// 0x00494E4D: tail jump to SpecialAbilityUpdate::onExit.
class Rva00494E4D : public SpecialAbilityUpdate
{
public:
	void rva00494E4D(bool a, bool b);
};


// 0x00494E52: tail jump to SpecialAbilityUpdate::update.
class Rva00494E52 : public SpecialAbilityUpdate
{
public:
	UpdateSleepTime rva00494E52();
};

// 0x00498CAC: tail jump to GateOpenAndCloseBehavior::xfer.
class Rva00498CAC : public GateOpenAndCloseBehavior
{
public:
	void rva00498CAC(Xfer *a);
};
void Rva00498CAC::rva00498CAC(Xfer *a)
{
	GateOpenAndCloseBehavior::xfer(a);
}

// 0x004A976F: tail jump to AIUpdateInterface::privateIdle; slot 81 of the
// WorkerAIUpdate vtable 0x00C540AC its rowed ctor 0x004AA3AB installs.
class WorkerAIUpdate : public AIUpdateInterface
{
protected:
	virtual void loadPostProcess();
public:
	void rva004A976F(CommandSourceType a);
};

// 0x0049A7EE: slot 1, tail jump to AIUpdateInterface::loadPostProcess.
void WorkerAIUpdate::loadPostProcess()
{
	AIUpdateInterface::loadPostProcess();
}
void WorkerAIUpdate::rva004A976F(CommandSourceType a)
{
	AIUpdateInterface::privateIdle(a);
}

// 0x004C38D0: tail jump to Rva00493009::xfer.
class Rva004C38D0 : public Rva00493009
{
public:
	void rva004C38D0(Xfer *a);
};
void Rva004C38D0::rva004C38D0(Xfer *a)
{
	Rva00493009::xfer(a);
}

// 0x0050B928: tail jump to Rva00507823::rva00507877.
class Rva0050B928 : public Rva00507823
{
public:
	void rva0050B928();
};
void Rva0050B928::rva0050B928()
{
	Rva00507823::rva00507877();
}

// 0x00521111: tail jump to _bfme_AptGameWindow::rva0051274F.
class Rva00521111 : public _bfme_AptGameWindow
{
public:
	int rva00521111(int a, unsigned int b, unsigned int c);
};
int Rva00521111::rva00521111(int a, unsigned int b, unsigned int c)
{
	return _bfme_AptGameWindow::rva0051274F(a, b, c);
}

// 0x00524AE2: tail jump to MovieWindowPlayback::clear.
class Rva00524AE2 : public MovieWindowPlayback
{
public:
	void rva00524AE2();
};

// 0x0052B48D: tail jump to XferSave::endBlock.
class Rva0052B48D : public XferSave
{
public:
	void rva0052B48D();
};
void Rva0052B48D::rva0052B48D()
{
	XferSave::endBlock();
}

// 0x00545CAA: tail jump to AIEnterState::onExit.
class Rva00545CAA : public AIEnterState
{
public:
	void rva00545CAA(StateExitType a);
};
void Rva00545CAA::rva00545CAA(StateExitType a)
{
	AIEnterState::onExit(a);
}

// 0x0057BC20: tail jump to SelectionDetailsUIImpl::rva0057BA90 (the Open body).
class Rva0057BC20 : public StrategicHUD::SelectionDetailsUIImpl
{
public:
	void rva0057BC20();
};
void Rva0057BC20::rva0057BC20()
{
	StrategicHUD::SelectionDetailsUIImpl::rva0057BA90();
}

// 0x005CE344: tail jump to Rva005E717ENamed::name.
class Rva005CE344 : public Rva005E717ENamed
{
public:
	const char * rva005CE344() const;
};
const char * Rva005CE344::rva005CE344() const
{
	return Rva005E717ENamed::name();
}

// 0x005CEB76: tail jump to Rva005CC5DFNamed::name.
class Rva005CEB76 : public Rva005CC5DFNamed
{
public:
	const char * rva005CEB76() const;
};
const char * Rva005CEB76::rva005CEB76() const
{
	return Rva005CC5DFNamed::name();
}

// 0x005FABBC: tail jump to Rva005E39E0Named::name.
class Rva005FABBC : public Rva005E39E0Named
{
public:
	const char * rva005FABBC() const;
};
const char * Rva005FABBC::rva005FABBC() const
{
	return Rva005E39E0Named::name();
}

// 0x005DAC33: tail jump to AIBuildable::addNeed.
class AIBuildableUnit : public AIBuildable
{
public:
	void addNeed(int a);
};
void AIBuildableUnit::addNeed(int a)
{
	AIBuildable::addNeed(a);
}

// 0x005E358F: tail jump to Overridable::markAsOverride.
class Rva005E358F : public Overridable
{
public:
	void rva005E358F();
};
void Rva005E358F::rva005E358F()
{
	Overridable::markAsOverride();
}

// 0x005E3594: tail jump to Rva00420B2AZeroSetter::disable.
class Rva005E3594 : public Rva00420B2AZeroSetter
{
public:
	void rva005E3594();
};
void Rva005E3594::rva005E3594()
{
	Rva00420B2AZeroSetter::disable();
}

// 0x005F4B52: tail jump to Rva005FD8C1::rva005FD8C1.
class Rva005F4B52 : public Rva005FD8C1
{
public:
	void rva005F4B52();
};
void Rva005F4B52::rva005F4B52()
{
	Rva005FD8C1::rva005FD8C1();
}

// 0x006CBD00: tail jump to AptCIH::rva006dbd80.
class Rva006CBD00 : public AptCIH
{
public:
	void rva006CBD00();
};
void Rva006CBD00::rva006CBD00()
{
	AptCIH::rva006dbd80();
}

// 0x006E0500: tail jump to BfmeAptValue006DCD20::rva006E04A0.
class Rva006E0500 : public BfmeAptValue006DCD20
{
public:
	void * rva006E0500() const;
};
void * Rva006E0500::rva006E0500() const
{
	return BfmeAptValue006DCD20::rva006E04A0();
}

// 0x0070DFD0: tail jump to Rva006D6360::rva006DCC00.
class AptObject : public AptValueWithHash
{
public:
	virtual void RegisterReferences() const;
};
void AptObject::RegisterReferences() const
{
	AptValueWithHash::RegisterReferences();
}

// Constant and field slots.
typedef int Int;
// 0x00444680 (22 tables): answers 1 for any two arguments.
class Rva00444680
{
public:
	Int rva00444680(Int a, Int b);
};
Int Rva00444680::rva00444680(Int, Int)
{
	return 1;
}
// 0x005B8012 (three tables): answers 1 for any four arguments.
class Rva005B8012
{
public:
	Int rva005B8012(Int a, Int b, Int c, Int d);
};
Int Rva005B8012::rva005B8012(Int, Int, Int, Int)
{
	return 1;
}
// 0x004BF8DF (eleven tables): 0 while +0xC6 is set, else +0x48.
class Rva004BF8DF
{
public:
	Int rva004BF8DF() const;
private:
	char m_pad00[0x48];
	Int m_48;
	char m_pad4C[0x7A];
	bool m_C6;
};
Int Rva004BF8DF::rva004BF8DF() const
{
	Int value = 0;
	if (!m_C6)
		value = m_48;
	return value;
}
// 0x005277CF: whether +0x0C is 3.
class Rva005277CF
{
public:
	bool rva005277CF() const;
private:
	char m_pad00[0x0C];
	Int m_0C;
};
bool Rva005277CF::rva005277CF() const
{
	return m_0C == 3;
}
// 0x00528F03 and 0x005C3998: the leading word of the +0x14 (resp. +0x10)
// object.
class Rva00528F03
{
public:
	Int rva00528F03() const;
private:
	char m_pad00[0x14];
	Int *m_14;
};
Int Rva00528F03::rva00528F03() const
{
	return *m_14;
}
class Rva005C3998
{
public:
	Int rva005C3998() const;
private:
	char m_pad00[0x10];
	Int *m_10;
};
Int Rva005C3998::rva005C3998() const
{
	return *m_10;
}
// 0x005F3EF3, 0x005F3EFE and 0x005F3F09: virtual slot 5, 7 resp. 6 of the
// +0x04 object (the argument is unused).
class Rva005F3EF3Target
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual Int v05();
	virtual Int v06();
	virtual Int v07();
};
class Rva005F3EF3
{
public:
	Int rva005F3EF3(Int unused);
	Int rva005F3EFE(Int unused);
	Int rva005F3F09(Int unused);
private:
	Int m_00;
	Rva005F3EF3Target *m_04;
};
Int Rva005F3EF3::rva005F3EF3(Int)
{
	return m_04->v05();
}
Int Rva005F3EF3::rva005F3EFE(Int)
{
	return m_04->v07();
}
Int Rva005F3EF3::rva005F3F09(Int)
{
	return m_04->v06();
}

// Tail-jump slots over unrowed callees, pinned in reverse/symbols.csv under
// address-derived names (argument counts from each callee's ret).

class Rva002D7DD5
{
public:
	void rva002D7DD5();
};
class Rva0004E3A1 : public Rva002D7DD5
{
public:
	void rva0004E3A1();
};


class LargeGroupAudioKeyMap;
class Rva002862C9
{
public:
	LargeGroupAudioKeyMap *rva002862C9();
};
class Rva00286351 : public Rva002862C9
{
public:
	void rva00286351();
};

// Target boundary at 0x00286356 is 29 bytes: it calls the adjacent pinned
// accessor at 0x002862C9, copies the returned object through the rowed
// Rva003ED658 copy constructor at 0x003ED658, and returns that object. The
// address-derived class and accessor result view preserve the target behavior;
// no named identity or broader layout is inferred.
class Rva003ED658
{
public:
	Rva003ED658(Rva003ED658 const &src);
	~Rva003ED658();
private:
	char m_storage[12];
};

class Rva00286356 : public Rva002862C9
{
public:
	Rva003ED658 rva00286356();
};

class Rva00286CC4
{
public:
	void rva00286CC4();
};


class Rva003412DB
{
public:
	void rva003412DB();
};
class Rva00341339 : public Rva003412DB
{
public:
	void rva00341339();
};


class Rva00349013
{
public:
	void rva00349013();
};
class Rva00349217 : public Rva00349013
{
public:
	void rva00349217();
};


// Native slot3497C2 forwards the StateReturnType result of the recovered
// 433B internal update. Bind the call to its real provider instead of the
// older unprovided void-return pin; this wrapper keeps its neutral spelling.
class Rva00349611
{
public:
 StateReturnType rva00349611();
};
class Rva003497C2 : public Rva00349611
{
public:
	void rva003497C2();
};
void Rva003497C2::rva003497C2()
{
	rva00349611();
}

class Rva0034D98B
{
public:
	void rva0034D98B();
};
class Rva0034DC00 : public Rva0034D98B
{
public:
	void rva0034DC00();
};


class Rva0035066B
{
public:
	void rva0035066B();
};
class Rva003508C0 : public Rva0035066B
{
public:
	void rva003508C0();
};


// Native 00404B03..00404B6C: two owned pointers at +12C/+130,
// an embedded 168-byte float-pair table at +78, and trailing state fields.
// The rowed +404B6C forwarder proves the receiver ABI: VictorySystem::reset
// and VictorySystem::newMap both call it on their own this. Method and field
// names are unknown.
class CellGrid { public: void rva0056C065(); };
class Rva0056C3E5
{
public:
    ~Rva0056C3E5();
    /* the rowed CellGrid::rva0056C065 */ __declspec(dllimport) __forceinline void rva0056C065() { ((CellGrid *)this)->rva0056C065(); }
};
class Rva00404781
{
public:
    void rva0040475C();
private:
    float a[20];
    float b[20];
    unsigned int flags0;
    unsigned int flags1;
};
class VictorySystem
{
public:
    virtual void reset();	// SubsystemInterface slot 9
    void rva00404B03();
private:
    // +0x00 is the SubsystemInterface vtable pointer.
    unsigned char prefix04[0x14 - 0x04];
    int field14;
    unsigned char prefix18[0x78 - 0x18];
    Rva00404781 table78;
    unsigned char prefix120[0x12C - 0x120];
    Rva0056C3E5 *owned[2];
    bool flag134;
    unsigned char prefix135[3];
    int field138;
    int field13C;
};
void VictorySystem::rva00404B03()
{
    for (int i = 0; i < 2; ++i)
    {
        if (owned[i])
        {
            owned[i]->rva0056C065();
            delete owned[i];
            owned[i] = 0;
        }
    }
    field13C = 0;
    field14 = 0;
    field138 = 2;
    table78.rva0040475C();
    flag134 = false;
}
// VictorySystem::reset: SubsystemInterface slot 9 of VictorySystem's table
// 0x008388D4 (installed by the rowed VictorySystem ctor 0x004054E1); it
// tail-jumps to the clear body 0x00404B03 above.
void VictorySystem::reset()
{
	rva00404B03();
}

class Rva0047BBA7
{
public:
	void rva0047BBA7();
};
class Rva0047E32B : public Rva0047BBA7
{
public:
	void rva0047E32B();
};


class Rva00467F3B
{
public:
	void rva00467F3B();
};
class Rva0047E330 : public Rva00467F3B
{
public:
	void rva0047E330();
};


class Rva004BF40F
{
public:
	void rva004BF40F();
};
class Rva004C202F : public Rva004BF40F
{
public:
	void rva004C202F();
};
void Rva004C202F::rva004C202F()
{
	rva004BF40F();
}

class Rva005C674A
{
public:
	void rva005C674A();
};
class Rva0053EC3A
{
public:
	void rva0053EC3A();
private:
	char m_pad00[0x0C];
	Rva005C674A m_0C;
};


class Rva005680D6
{
public:
	void rva005680D6();
private:
	char m_pad00[0x0C];
	InGameToggleStanceCommandButton::Impl *m_0C;
};
void Rva005680D6::rva005680D6()
{
	m_0C->OnLeftClicked();
}

class Rva005D2F7E
{
public:
	void rva005D2F7E();
};
class Rva0057862E
{
public:
	void rva0057862E();
private:
	char m_pad00[0x48];
	Rva005D2F7E *m_48;
};


class Rva005D2F84
{
public:
	void rva005D2F84();
};
class Rva00578636
{
public:
	void rva00578636();
private:
	char m_pad00[0x48];
	Rva005D2F84 *m_48;
};


class Rva005D2F8A
{
public:
	void rva005D2F8A();
};
class Rva0057863E
{
public:
	void rva0057863E();
private:
	char m_pad00[0x48];
	Rva005D2F8A *m_48;
};


class AptStats
{
public:
	void rva005DD22B();
};
class Rva005B7FFA
{
public:
	void rva005B7FFA();
private:
	char m_pad00[0x60];
	AptStats m_60;
};
void Rva005B7FFA::rva005B7FFA()
{
	m_60.rva005DD22B();
}



class Rva00517EA2
{
public:
	void rva00517EA2();
};
class Rva005B800A
{
public:
	void rva005B800A();
private:
	char m_pad00[0x58];
	Rva00517EA2 *m_58;
};
void Rva005B800A::rva005B800A()
{
	m_58->rva00517EA2();
}

class Rva005BA440
{
public:
	void rva005BA440();
};
class Rva005BA621 : public Rva005BA440
{
public:
	void rva005BA621();
};

class Rva005F963A
{
public:
	void rva005F963A(Int a);
};
class Rva005F97AC
{
public:
	void rva005F97AC(Int a);
private:
	char m_pad00[0x3C];
	Rva005F963A *m_3C;
};


class Rva005F9687
{
public:
	void rva005F9687(Int a);
};
class Rva005F97B4
{
public:
	void rva005F97B4(Int a);
private:
	char m_pad00[0x38];
	Rva005F9687 *m_38;
};


// Retail 0x005680F9 (74 bytes) returns the instance-list storage at VA
// 0x00E062D8; its one-time guard is VA 0x00E062DC. The named Impl constructor
// inserts its instance and the named destructor erases its saved iterator.
// The original list element spelling is unresolved: this is the existing
// verified list<int> ABI view, using its rowed base constructor and holder
// destructor. Explicit specialization declarations reuse those providers.
// The function-local static generates _$E2 at retail 0x007B945A (10 bytes),
// registered by this getter, and destroys this same object through 0x00200667.
// It replaces the former independent g_Va00E062D8/manual-callback storage.
namespace _STL {
 template<> _List_base<int, allocator<int> >::_List_base(const allocator<int>&);
 template<> _List_base<int, allocator<int> >::~_List_base();
}
class Rva00200667 : public _STL::list<int> {
public:
 __forceinline Rva00200667() : _STL::list<int>(_STL::allocator<int>()) {}
 ~Rva00200667();
};
Rva00200667 *Rva005680F9GetInstances()
{
 static Rva00200667 instances;
 return &instances;
}

// ??1Impl@InGameToggleStanceCommandButton@@QAE@XZ
// Retail 0x0056820D, 278 bytes. WorldBuilder 0x014307B0 names this destructor
// and asserts its saved instance-list iterator (source line 478). It removes
// its observer, hides an open menu, unregisters hotkeys/messages, erases the
// saved list node and destroys the hotkey vector. Native accesses establish
// the +4 iterator, +0x18 behavior and +0x1C vector prefixes. Both native
// observer tables lack a destructor slot, so destruction is nonvirtual.
// The compiler's complete unwind graph matches retail, including both
// member/base cleanup handlers; no hand-written table addresses are used.
InGameToggleStanceCommandButton::Impl::~Impl()
{
 if(behavior18) behavior18->observers.rva002B7250(reinterpret_cast<CreateAHeroData*>(this));
 Rva005C3F02 *menu=factory0C->getMenu();
 if(menu && reinterpret_cast<Rva0057C22FByteChaseField*>(menu)->get())
  reinterpret_cast<Rva005C3E79*>(menu)->rva005C3E79();
 if(TheHotKeyManager) {
  int count=(int)button14->stances.size();
  for(int i=0;i<count;++i) {
   StanceHotKeyRecord &key=hotKeys[i];
   if(key.active) ((Rva00E01E28Owner *)TheHotKeyManager)->rva003591F4(key.action);
   int message=GetAssociatedMessageType(button14->getStance(i));
   if(message) TheHotKeyManager->removeMessageAction(message);
   key.ref.clear();
  }
 }
 Rva005680F9GetInstances()->erase(listPosition);
}

// Retail 0x00568143, 23 bytes; WB 0x014311F0 names this callback and asserts
// &behavior == m_stancesBehavior at source line 624. The release body removes
// this observer from behavior +0x20 and clears the saved behavior pointer.
void InGameToggleStanceCommandButton::Impl::onDestroyingStancesBehavior(StancesBehavior &)
{
 behavior18->observers.rva002B7250(reinterpret_cast<CreateAHeroData*>(this));
 behavior18=0;
}

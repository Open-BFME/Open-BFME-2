// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
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
class Rva005C3EE0 { public: void rva005C3EE0(); };
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
class InGameToggleStanceCommandButton {
public:
 class Impl {
 public:
  void OnLeftClicked();
 private:
  char pad00[8];
  Rva00005C357FPtrChaseField *owner08;
  StanceMenuFactory *factory0C;
  void *window10;
  CommandButton *button14;
 };
};
// ?OnLeftClicked@Impl@InGameToggleStanceCommandButton@@QAEXXZ,
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
  reinterpret_cast<Rva005C3EE0 *>(menu)->rva005C3EE0();
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

class Rva000869CF
{
public:
	float * rva000869CF();
};

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

class Rva000B3A2D
{
public:
	void rva000B3A2D();
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
	void rva004D750F(Object *a);
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
	virtual void rva004672B7(int a, int b);
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
	virtual void rva004508B7();
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

class Rva00524A4C
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

class Rva0057BA90
{
public:
	void rva0057BA90();
};

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

class Rva0055B146
{
public:
	void rva0055B146(int a);
};

class Overridable
{
public:
	void markAsOverride();
};

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

class Rva006D6360
{
public:
	void rva006DCC00();
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
bool Rva00034D00::rva00034D00()
{
	return Rva006C1F60::rva00033D50();
}

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

// 0x000CA132: tail jump to Rva000B3A2D::rva000B3A2D.
class Rva000CA132 : public Rva000B3A2D
{
public:
	void rva000CA132();
};
void Rva000CA132::rva000CA132()
{
	Rva000B3A2D::rva000B3A2D();
}

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
void Rva0032E53D::rva0032E53D()
{
	SidesList::clear();
}

// 0x0033FCDC: tail jump to StateMachine::rva004D750F.
class Rva0033FCDC : public StateMachine
{
public:
	void rva0033FCDC(Object *a);
};
void Rva0033FCDC::rva0033FCDC(Object *a)
{
	StateMachine::rva004D750F(a);
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

// 0x003A3899: tail jump to TeamFactory::clear.
class Rva003A3899 : public TeamFactory
{
public:
	void rva003A3899();
};
void Rva003A3899::rva003A3899()
{
	TeamFactory::clear();
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
void Rva004766BE::rva004766BE(const Object *a)
{
	HordeContain::slot42(a);
}

// 0x0047E33F: tail jump to TransportContain::rva004672B7.
class Rva0047E33F : public TransportContain
{
public:
	void rva0047E33F(int a, int b);
};
void Rva0047E33F::rva0047E33F(int a, int b)
{
	TransportContain::rva004672B7(a, b);
}

// 0x00483CEF: tail jump to Rva00497805::loadPostProcess.
class Rva00483CEF : public Rva00497805
{
public:
	void rva00483CEF();
};
void Rva00483CEF::rva00483CEF()
{
	Rva00497805::loadPostProcess();
}

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
bool Rva00494E21::rva00494E21()
{
	return SpecialAbilityUpdate::rva0044FC52();
}

// 0x00494E48: tail jump to SpecialAbilityUpdate::rva004508B7.
class Rva00494E48 : public SpecialAbilityUpdate
{
public:
	void rva00494E48();
};
void Rva00494E48::rva00494E48()
{
	SpecialAbilityUpdate::rva004508B7();
}

// 0x00494E4D: tail jump to SpecialAbilityUpdate::onExit.
class Rva00494E4D : public SpecialAbilityUpdate
{
public:
	void rva00494E4D(bool a, bool b);
};
void Rva00494E4D::rva00494E4D(bool a, bool b)
{
	SpecialAbilityUpdate::onExit(a, b);
}

// 0x00494E52: tail jump to SpecialAbilityUpdate::update.
class Rva00494E52 : public SpecialAbilityUpdate
{
public:
	UpdateSleepTime rva00494E52();
};
UpdateSleepTime Rva00494E52::rva00494E52()
{
	return SpecialAbilityUpdate::update();
}

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

// 0x0049A7EE: tail jump to AIUpdateInterface::loadPostProcess.
class Rva0049A7EE : public AIUpdateInterface
{
public:
	void rva0049A7EE();
};
void Rva0049A7EE::rva0049A7EE()
{
	AIUpdateInterface::loadPostProcess();
}

// 0x004A976F: tail jump to AIUpdateInterface::privateIdle.
class Rva004A976F : public AIUpdateInterface
{
public:
	void rva004A976F(CommandSourceType a);
};
void Rva004A976F::rva004A976F(CommandSourceType a)
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

// 0x00524AE2: tail jump to Rva00524A4C::clear.
class Rva00524AE2 : public Rva00524A4C
{
public:
	void rva00524AE2();
};
void Rva00524AE2::rva00524AE2()
{
	Rva00524A4C::clear();
}

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

// 0x0057BC20: tail jump to Rva0057BA90::rva0057BA90.
class Rva0057BC20 : public Rva0057BA90
{
public:
	void rva0057BC20();
};
void Rva0057BC20::rva0057BC20()
{
	Rva0057BA90::rva0057BA90();
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

// 0x005DAC33: tail jump to Rva0055B146::rva0055B146.
class AIBuildableUnit : public Rva0055B146
{
public:
	void addNeed(int a);
};
void AIBuildableUnit::addNeed(int a)
{
	Rva0055B146::rva0055B146(a);
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
class Rva0070DFD0 : public Rva006D6360
{
public:
	void rva0070DFD0();
};
void Rva0070DFD0::rva0070DFD0()
{
	Rva006D6360::rva006DCC00();
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
void Rva0004E3A1::rva0004E3A1()
{
	rva002D7DD5();
}

class Rva002862C9
{
public:
	void rva002862C9();
};
class Rva00286351 : public Rva002862C9
{
public:
	void rva00286351();
};
void Rva00286351::rva00286351()
{
	rva002862C9();
}

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

union Rva002862C9ResultCall
{
	void (Rva002862C9::*voidCall)();
	Rva003ED658 const *(Rva002862C9::*resultCall)();
};

Rva003ED658 Rva00286356::rva00286356()
{
	Rva002862C9ResultCall call;
	call.voidCall = &Rva002862C9::rva002862C9;
	return *(this->*call.resultCall)();
}

class Rva00286CC4
{
public:
	void rva00286CC4();
};
class Rva00287010 : public Rva00286CC4
{
public:
	void rva00287010();
};
void Rva00287010::rva00287010()
{
	rva00286CC4();
}

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
void Rva00341339::rva00341339()
{
	rva003412DB();
}

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
void Rva00349217::rva00349217()
{
	rva00349013();
}

class Rva00349611
{
public:
	void rva00349611();
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
void Rva0034DC00::rva0034DC00()
{
	rva0034D98B();
}

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
void Rva003508C0::rva003508C0()
{
	rva0035066B();
}

// Native 00404B03..00404B6C: two owned pointers at +12C/+130,
// an embedded 168-byte float-pair table at +78, and trailing state fields.
// The rowed +404B6C forwarder proves the receiver ABI. Original names unknown.
class Rva0056C3E5
{
public:
    ~Rva0056C3E5();
    void rva0056C065();
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
class Rva00404B03
{
public:
    void rva00404B03();
private:
    unsigned char prefix00[0x14];
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
void Rva00404B03::rva00404B03()
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
class Rva00404B6C : public Rva00404B03
{
public:
	void rva00404B6C();
};
void Rva00404B6C::rva00404B6C()
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
void Rva0047E32B::rva0047E32B()
{
	rva0047BBA7();
}

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
void Rva0047E330::rva0047E330()
{
	rva00467F3B();
}

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
void Rva0053EC3A::rva0053EC3A()
{
	m_0C.rva005C674A();
}

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
void Rva0057862E::rva0057862E()
{
	m_48->rva005D2F7E();
}

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
void Rva00578636::rva00578636()
{
	m_48->rva005D2F84();
}

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
void Rva0057863E::rva0057863E()
{
	m_48->rva005D2F8A();
}

class Rva005DD22B
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
	Rva005DD22B m_60;
};
void Rva005B7FFA::rva005B7FFA()
{
	m_60.rva005DD22B();
}

class Rva005DD06D
{
public:
	void rva005DD06D();
};
class Rva005B8002
{
public:
	void rva005B8002();
private:
	char m_pad00[0x60];
	Rva005DD06D m_60;
};
void Rva005B8002::rva005B8002()
{
	m_60.rva005DD06D();
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
void Rva005BA621::rva005BA621()
{
	rva005BA440();
}

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
void Rva005F97AC::rva005F97AC(Int a)
{
	m_3C->rva005F963A(a);
}

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
void Rva005F97B4::rva005F97B4(Int a)
{
	m_38->rva005F9687(a);
}

// ?rva0030BCB2@Rva0030BCB2@@QAEMXZ @0x0030BCB2 8B
// Adjustor tail-jmp to Rva0053863ESub::rva00538661 with this-0x28.
// Evidence: same -0x28 adjustment as Rva0030BEE6Owner::fwd in RvaAdjustCallEchoFamily.cpp to same target; callee rowed; caller 0x0030C4B9.
class Rva0053863ESub
{
public:
	float rva00538661();
};
class Rva0030BCB2
{
public:
	float rva0030BCB2();
};
float Rva0030BCB2::rva0030BCB2()
{
	return ((Rva0053863ESub *)((char *)this - 0x28))->rva00538661();
}


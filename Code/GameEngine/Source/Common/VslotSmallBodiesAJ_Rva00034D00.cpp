// cl: /Ireference/shims/bfmelist /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// stlport
// Split from VslotSmallBodiesAJ.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
#include <vector>
#include <list>
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class PlayerList;
extern PlayerList *ThePlayerList;
class Rva002A7DDEArg;
class Rva005C3F02;
class Rva005677B9 { public: struct Payload { int v[2]; }; };
void Rva00567B6DAdd(Rva005C3F02 *,const Rva005677B9::Payload *);
// Prefix-only factory view: unused vslots specify layout, not signatures.
// Provider declarations above preserve their existing ABI, not class extents.
class StancesBehavior;
// Neutral observer-base identity: retail restores table VA 0x00C6CE84.
// Two slots, and no destructor slot: RET4 at RVA 0x0047A69C and RET12 at
// 0x000D1407. The derived table at VA 0x00C6CF6C has the named unregister
// callback 0x00568143 and the changed-stance callback 0x00567B10. WorldBuilder
// supplies the behavior reference and signed old/new stance arguments; their
// original enum spelling remains unresolved, so this view uses integer ABI.
class CreateAHeroData;
struct TargetRef00217D4C;
// The existing release provider touches only the 12-byte prefix (ref +8).
// Retail's hotkey vector advances 16 bytes and tests its active flag at +12.
// Keep that extra flag in a distinct record instead of widening the prefix.
class HotKeyManager;
extern HotKeyManager *TheHotKeyManager;
#include "../../Include/GameClient/HotKeyManager.h"
int GetAssociatedMessageType(int);
//
// Vtable-slot bodies with no ledger owner and no Ghidra entry, batch AJ:
// each is a single tail jump to a rowed or pinned function on the same
// object (a derived slot that only runs its base's or a sibling's method).
// The forwarders are address-derived classes over the target's class,
// declared with the target's own signature; nothing else is modeled.

class Object;
class Xfer;
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};
enum CommandSourceType
{
	CMD_FROM_PLAYER = 0
};

#include "../../Include/Common/GeneralAllocator.h"
namespace EA
{
namespace Allocator
{
}
}

class Rva001EDDBBForwarder
{
public:
	void rva001EDDBB();
};

class Win32GameEngine
{
public:
	virtual void * createAudioManager();
};

#include "../GameClient/Rva000869CF.h"

#include "../../Include/GameClient/VideoPlayerClass.h"

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

#include "../../Include/Common/Rva00131CEAForwarder.h"

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

#include "../../Include/GameNetwork/GameInfo.h"

#include "../../Include/GameLogic/Module/AIUpdate.h"

class Rva0030BBE5
{
public:
	void rva0030BBE5(int a);
};

#include "../../Include/Common/CommandList.h"

#include "../../Include/Common/SidesList.h"

#include "../../Include/Common/StateMachineClass.h"

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

#include "../../Include/GameLogic/Module/StealthUpdate.h"

#include "../../Include/Common/Rva0038404A.h"

#include "../../Include/GameLogic/Module/CreateModuleClass.h"

class Rva000B56F0Object
{
public:
	void * selectStorage();
};

#include "../../Include/GameLogic/Rva003145B1.h"

class HordeContain
{
public:
	virtual void slot42(const Object *a);
};

class TransportContain
{
public:
	virtual void onCapture(int a, int b);
protected:
	virtual void killRidersWhoAreNotFreeToExit();	// rowed 0x00467F3B
};

class Rva00497805
{
protected:
	virtual void loadPostProcess();
};

#include "../../Include/Common/Rva002645FF.h"

#include "../../Include/GameLogic/Module/SpecialAbilityUpdate.h"

class GateOpenAndCloseBehavior
{
protected:
	virtual void xfer(Xfer *a);
};

#include "../../Include/GameLogic/Rva00493009.h"

#include "../../Include/GameLogic/Module/Rva00507823.h"

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

#include "../../Include/Common/Rva005E717ENamed.h"

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

#include "../../Include/Common/Rva00420B2AZeroSetter.h"

class Rva005FD8C1
{
public:
	void rva005FD8C1();
};

#include "../../../Libraries/Source/Apt/AptCIHClass.h"

#include "../../../Libraries/Source/Apt/BfmeAptValue006DCD20.h"

namespace Debug_Statistics
{
int Get_Draw_Calls();
}
int Rva000A8F58Get();
int Rva000A8F5EGet();

// Native 0x00034D00: the nonvirtual GeneralAllocator destructor.
// Derived destruction and its unwind action call this thunk, which runs
// the independently rowed teardown at 0x00033D50.
EA::Allocator::GeneralAllocator::~GeneralAllocator()
{
    rva00033D50();
}

// 0x00041A06: tail jump to Rva001EDDBBForwarder::rva001EDDBB.
class Rva00041A06 : public Rva001EDDBBForwarder
{
public:
	void rva00041A06();
};


// 0x00099109: tail jump to Rva00041A06::rva00041A06 (W3DMouse vftable slot
// 9, the Zero Hour reset position; the existing W3DMouse::reset row sits in
// slot 1, so this keeps an address-derived name).
// 0x00041E65: tail jump to Win32GameEngine::rva0005E959.
// 0x00043F94: tail jump to Debug_Statistics::Get_Draw_Calls.
// 0x00062972: tail jump to Rva000A8F58Get.
// 0x00062977: tail jump to Rva000A8F5EGet.
// 0x00088D05: tail jump to Rva000869CF::rva000869CF.
// 0x000907B7: tail jump to VideoPlayer::Rva00689180.
// 0x00098560: tail jump to Rva0030ADE8Forwarder::rva0030ADE8.
// 0x000B23D8: tail jump to Rva005CB260::rva005CB260.
// 0x000CA132: tail jump to Rva000B3A2D::rva000B3A2D.
// 0x000EF961: tail jump to Rva00131CEAForwarder::rva00131CEA.
// 0x001040E7: tail jump to Rva002D35C7Forwarder::rva002D35C7.
// 0x001040EC: tail jump to Rva002D6AE2Forwarder::rva002D6AE2.
// 0x00109643: tail jump to W3DProjectedShadow::rva00108951.
// 0x0022C4CF: tail jump to GameInfo::getNumPlayers.
// 0x0022C4D4: tail jump to GameInfo::getNumOpenOrOccupiedSlots.
// 0x002628B1: tail jump to AIUpdateInterface::wakeUpNow.
// 0x0030BCBA: tail jump to Rva0030BBE5::rva0030BBE5.
// 0x00311092: tail jump to CommandList::destroyAllMessages.
// 0x0032E53D: tail jump to SidesList::clear.
// 0x0033FCDC: tail jump to StateMachine::setGoalObject.
// 0x00341D1C: tail jump to AIExitState::onEnter.
// 0x00341D21: tail jump to AIExitState::update.
// 0x00349D8D: tail jump to BfmeThing932E::bfmeTail932E.
// 0x00368095: tail jump to AIPickUpCrateState::update.
// 0x003681ED: tail jump to AIUpdateInterface::onObjectCreated.
// 0x003682E2: tail jump to AIUpdateInterface::chooseLocomotorSet.
// 0x003682E7: tail jump to Rva00262CB6DwordClearer::clear.
// 0x003682EC: tail jump to AIUpdateInterface::getTreatAsAircraftForLocoDistToGoal.
// 0x003697F4: tail jump to GiantBirdNormalFlightState::onExit.
// 0x00374FD0: tail jump to StealthUpdate::rva003748BD.
// 0x00385BDC: tail jump to Rva0038404A::rva00384E8E.
// 0x003A44DA: tail jump to CreateModule::xfer.
// 0x004333FE: tail jump to Rva000B56F0Object::selectStorage.
// 0x004444A9: tail jump to Rva003145B1::Rva003145B1Dispatch.
// 0x004766BE: tail jump to HordeContain::slot42.
// 0x0047E33F: tail jump to TransportContain::onCapture.
// 0x00483CEF: tail jump to Rva00497805::loadPostProcess.
// 0x0048F46D: tail jump to Rva002645FF::rva002645FF.
// 0x00494E21: tail jump to SpecialAbilityUpdate::continuePreparation.
class Rva00494E21 : public SpecialAbilityUpdate
{
public:
	bool rva00494E21();
};
bool Rva00494E21::rva00494E21()
{
	return SpecialAbilityUpdate::continuePreparation();
}

// 0x00494E48: tail jump to SpecialAbilityUpdate::startUnpacking.
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
// 0x00498CAC: tail jump to GateOpenAndCloseBehavior::xfer.
// 0x004A976F: tail jump to AIUpdateInterface::privateIdle.
// 0x004C38D0: tail jump to Rva00493009::xfer.
// 0x0050B928: tail jump to Rva00507823::rva00507877.
// 0x00521111: tail jump to _bfme_AptGameWindow::rva0051274F.
// 0x00524AE2: tail jump to MovieWindowPlayback::clear.
// 0x0052B48D: tail jump to XferSave::endBlock.
// 0x00545CAA: tail jump to AIEnterState::onExit.
// 0x0057BC20: tail jump to SelectionDetailsUIImpl::rva0057BA90 (the Open body).
// 0x005CE344: tail jump to Rva005E717ENamed::name.
// 0x005CEB76: tail jump to Rva005CC5DFNamed::name.
// 0x005FABBC: tail jump to Rva005E39E0Named::name.
// 0x005DAC33: tail jump to AIBuildable::addNeed.
// 0x005E358F: tail jump to Overridable::markAsOverride.
// 0x005E3594: tail jump to Rva00420B2AZeroSetter::disable.
// 0x005F4B52: tail jump to Rva005FD8C1::rva005FD8C1.
// 0x006CBD00: tail jump to AptCIH::rva006dbd80.
// 0x006E0500: tail jump to BfmeAptValue006DCD20::rva006E04A0.
// 0x0070DFD0: tail jump to Rva006D6360::rva006DCC00.
// Constant and field slots.
typedef int Int;
// 0x00444680 (22 tables): answers 1 for any two arguments.
// 0x005B8012 (three tables): answers 1 for any four arguments.
// 0x004BF8DF (eleven tables): 0 while +0xC6 is set, else +0x48.
// 0x005277CF: whether +0x0C is 3.
// 0x00528F03 and 0x005C3998: the leading word of the +0x14 (resp. +0x10)
// object.
// 0x005F3EF3, 0x005F3EFE and 0x005F3F09: virtual slot 5, 7 resp. 6 of the
// +0x04 object (the argument is unused).
// Tail-jump slots over unrowed callees, pinned in reverse/symbols.csv under
// address-derived names (argument counts from each callee's ret).

// 0x002D7DD5 is the rowed Radar::update.
class Radar
{
public:
	virtual void update();
};
class Rva0004E3A1 : public Radar
{
public:
	void rva0004E3A1();
};
void Rva0004E3A1::rva0004E3A1()
{
	Radar::update();
}

class LargeGroupAudioKeyMap;
// Target boundary at 0x00286356 is 29 bytes: it calls the adjacent pinned
// accessor at 0x002862C9, copies the returned object through the rowed
// Rva003ED658 copy constructor at 0x003ED658, and returns that object. The
// address-derived class and accessor result view preserve the target behavior;
// no named identity or broader layout is inferred.
#include "../../Include/GameLogic/Rva003ED658.h"

#include "../../Include/GameLogic/FireLogicSystem.h"
void FireLogicSystem::reset()
{
	rva00286CC4();
}

class Rva003412DB
{
public:
	StateReturnType rva003412DB();
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

// 0x00349013 is the rowed AIAttackMeleeHordeApproachTargetState::update.
class AIAttackMeleeHordeApproachTargetState
{
public:
	virtual StateReturnType update();
};
class Rva00349217 : public AIAttackMeleeHordeApproachTargetState
{
public:
	void rva00349217();
};
void Rva00349217::rva00349217()
{
	AIAttackMeleeHordeApproachTargetState::update();
}

// Native slot3497C2 forwards the StateReturnType result of the recovered
// 433B internal update. Bind the call to its real provider instead of the
// older unprovided void-return pin; this wrapper keeps its neutral spelling.
class AIAttackMeleeSquishState
{
	StateReturnType rva0034D98B();	// rowed 0x0034D98B
	friend class Rva0034DC00;
};
class Rva0034DC00 : public AIAttackMeleeSquishState
{
public:
	void rva0034DC00();
};
void Rva0034DC00::rva0034DC00()
{
	rva0034D98B();
}

class AIAttackFireDuringApproachState
{
	StateReturnType updateInternal();	// rowed 0x0035066B
	friend class Rva003508C0;
};
class Rva003508C0 : public AIAttackFireDuringApproachState
{
public:
	void rva003508C0();
};
void Rva003508C0::rva003508C0()
{
	updateInternal();
}

// Native 00404B03..00404B6C: two owned pointers at +12C/+130,
// an embedded 168-byte float-pair table at +78, and trailing state fields.
// The rowed +404B6C forwarder proves the receiver ABI: VictorySystem::reset
// and VictorySystem::newMap both call it on their own this. Method and field
// names are unknown.
class CellGrid { public: void rva0056C065(); };
#include "../../Include/Common/Rva0056C3E5.h"
#include "../../Include/Common/Rva00404781.h"
#include "../../Include/Common/VictorySystem.h"


// 0x0047BBA7 is the rowed SiegeEngineContain::createPayload.
class SiegeEngineContain
{
public:
	virtual void createPayload();
};
class Rva0047E32B : public SiegeEngineContain
{
public:
	void rva0047E32B();
};
void Rva0047E32B::rva0047E32B()
{
	SiegeEngineContain::createPayload();
}

class Rva0047E330 : public TransportContain
{
public:
	void rva0047E330();
};
void Rva0047E330::rva0047E330()
{
	TransportContain::killRidersWhoAreNotFreeToExit();
}

class Rva005C6D4D
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
	Rva005C6D4D m_0C;
};
void Rva0053EC3A::rva0053EC3A()
{
	m_0C.rva005C674A();
}

class Rva005D2F7E
{
public:
	char *rva005D2F7E();
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
	char *rva005D2F84();
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
	char *rva005D2F8A();
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

class AptStats
{
public:
	void rva005DD22B();
	virtual void InitGadgets();	// rowed 0x005DD06D
};
class Rva005B8002
{
public:
	void rva005B8002();
private:
	char m_pad00[0x60];
	AptStats m_60;
};
void Rva005B8002::rva005B8002()
{
	m_60.AptStats::InitGadgets();
}

#include "../../Include/GameClient/BattlePromptMovieClip.h"
class StrategicHUD::BattlePromptMovieClip::Impl
{
public:
	void rva005F963A(Int a);	// rowed 0x005F963A
	void rva005F9687(Int a);	// rowed 0x005F9687
};
class Rva005F97AC
{
public:
	void rva005F97AC(Int a);
private:
	char m_pad00[0x3C];
	StrategicHUD::BattlePromptMovieClip::Impl *m_3C;
};
void Rva005F97AC::rva005F97AC(Int a)
{
	m_3C->rva005F963A(a);
}

class Rva005F97B4
{
public:
	void rva005F97B4(Int a);
private:
	char m_pad00[0x38];
	StrategicHUD::BattlePromptMovieClip::Impl *m_38;
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
Rva00200667 *Rva005680F9GetInstances();




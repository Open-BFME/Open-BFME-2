// cl: /DNDEBUG /MD
//
// Retail RE: ?ownerIdle@SupplyTruckStateMachine@@SA_NPAVState@@PAX@Z @0x004A6D38 (37B).
//
// BFME2 SupplyTruck state-machine condition, fresh sibling of refuted
// ?ownerDocking@SupplyTruckStateMachine@@SA_NPAVState@@PAX@Z @0x004A6CF2 (35B).
// This seat pivots per lane: do NOT retry the same 35B EAX-vs-ECX/EDX +
// unresolved-0x262FC3 shape. New body has independent provider support.
//
// Target facts from retail bytes (read this round from
// /home/levy/projects/bfme-data/BFME2/game.dat via PE section parse,
// independent of donor):
// - Boundary 0x004A6D38..0x004A6D5D 37B; prev sibling 0x004A6D15/35 ends at
//   0x004A6D38 (0x4A6D15+0x23); next sibling 0x004A6D5D starts at end with
//   the same 16B prologue 8B442404/8B4018/8B4014/8B8858020000/85C9.
// - Bytes: 8B442404 8B4018 8B4014 8B8858020000 85C9 7503 32C0 C3
//   8B01 FF90B8010000 84C0 0F95C0 C3.
//   Chain State+0x18 / Machine+0x14 / Object+0x258 (same three offsets the
//   ownerDocking r18 pass proved exact); null-guard returns false; tail is an
//   INDIRECT virtual call [eax+0x1B8] then test al,al + setne al (bool).
// - The disp32 B8010000 is slot 110 (+0x1B8): AIUpdateInterface::isIdle.
//   Proven by two independent rows: AIRoamingDefenseTactic.cpp slot-110
//   comment and Rva0044E655Check "AI slot 0x1b8 isIdle". No REL32, so no
//   0x00262FC3 identity question and no pin (pins are candidates, not proof).
// - The retail 0x004A6CF2/0x004A6D15/0x004A6D38/0x004A6D5D cluster
//   shares one 16B prologue. Its correspondence to donor condition tables
//   is a structural lead, not independently proven target table identity.
// - Donor busyConditions[0] references ownerIdle; regroupingConditions[0]
//   references ownerPlayerCommanded. These are donor facts only.
// Donor-carried only: reference/open-bfme-1 rev 6583b3c1
// game/GameEngine/Source/GameLogic/Object/Update/AIUpdate/SupplyTruckAIUpdate.cpp
// ownerIdle (same name/shape/role: getMachineOwner + getAIUpdateInterface +
// null-guard + ai->isIdle). BFME2 offsets +0x18/+0x14/+0x258 read off retail,
// not donor (+0x1c/+0x10/+0x204). No ZH same-name donor needed.
// No shared-header edits; TU-scoped views only.

class Object;
class StateMachine;
class AIUpdateInterface;

class State
{
public:
	char m_pad[0x18];
	StateMachine *m_machine; // +0x18
};

class StateMachine
{
public:
	char m_pad[0x14];
	Object *m_owner; // +0x14
};

class Object
{
public:
	char m_pad[0x258];
	AIUpdateInterface *m_ai; // +0x258
};

class AIUpdateInterface
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual bool isIdle(); // slot 110 (+0x1B8)
};

class SupplyTruckStateMachine
{
public:
	static bool ownerIdle(State *thisState, void *userData);
};

// ?ownerIdle@SupplyTruckStateMachine@@SA_NPAVState@@PAX@Z
bool SupplyTruckStateMachine::ownerIdle(State *thisState, void *userData)
{
	StateMachine *machine = thisState->m_machine;
	Object *owner = machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	if (!ai)
		return false;
	if (ai->isIdle())
		return true;
	return false;
}

// cl: /DNDEBUG /MD
// BFME1 6583b3c1 SupplyTruckAIUpdate.cpp supplies the callback name and
// core semantics; target-specific control flow and ABI come from retail.
// Native registration: VA0x00C5330C -> callbackVA0x008A6D5D and transition2.
// Native State+0x18 -> machine+0x14 -> Object AI+0x258; isIdle slot110.
// Exact retail interval 0x004A6D5D / 68B.
// SupplyTruck interface slot4 is opaque: donor slot3 does not prove its name.
class Object;
class StateMachine;
class AIUpdateInterface;
class SupplyTruckAIInterface;

struct State
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

class SupplyTruckAIInterface
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual bool v004(); // slot 4 (+0x10); target offset only; semantic name unproved
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
	virtual SupplyTruckAIInterface *getSupplyTruckAIInterface(); // slot 95 (+0x17C)
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
	static bool ownerAvailableForSupplying(State *thisState, void *userData);
};

// ?ownerAvailableForSupplying@SupplyTruckStateMachine@@SA_NPAUState@@PAX@Z
bool SupplyTruckStateMachine::ownerAvailableForSupplying(State *thisState, void *userData)
{
	StateMachine *machine = thisState->m_machine;
	Object *owner = machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	if (!ai)
		return false;
	SupplyTruckAIInterface *update = ai->getSupplyTruckAIInterface();
	if (!update)
		return false;
	if (update->v004() && ai->isIdle())
		return true;
	return false;
}

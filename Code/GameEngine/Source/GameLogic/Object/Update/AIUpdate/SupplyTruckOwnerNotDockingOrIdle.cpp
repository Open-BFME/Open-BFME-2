// cl: /DNDEBUG /MD
// BFME1 6583b3c1 SupplyTruckAIUpdate.cpp supplies the callback name and
// core semantics; target-specific control flow and ABI come from retail.
// Native registration: VA0x00C53318 VA0x00C53378 VA0x00C533C0 -> callbackVA0x008A6DA1 and transition1.
// Native State+0x18 -> machine+0x14 -> Object AI+0x258; isIdle slot110.
// Exact retail interval 0x004A6DA1 / 67B.
// Additional target state exclusion0x2F remains unnamed.
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
	int getCurrentStateID() const;
};

enum { AI_DOCK = 14 };

class SupplyTruckStateMachine
{
public:
	static bool ownerNotDockingOrIdle(State *thisState, void *userData);
};

// ?ownerNotDockingOrIdle@SupplyTruckStateMachine@@SA_NPAVState@@PAX@Z
bool SupplyTruckStateMachine::ownerNotDockingOrIdle(State *thisState, void *userData)
{
	StateMachine *machine = thisState->m_machine;
	Object *owner = machine->m_owner;
	AIUpdateInterface *ai = owner->m_ai;
	// Single && chain as an if-CONDITION (same far-jump layout as the landed
	// 68B TU: retail 74 2A / 75 1C / 74 10 / 74 04 all -> shared xor-false
	// tail at 0x004A6DE0, B001 true path). `return chain` materializes the
	// last compare as xor+inc value (+1B); `if (chain) return true` keeps
	// it a branch over B001. Early-return spelling lays the ai-null false
	// inline and loops later falses back to it (refuted this round, op2).
	// Retail second exclusion: cmp eax,0x2F. No proven BFME2 AI-state name
	// for 47 (renumbered vs ZH); kept raw so no identity is invented.
	if (ai && !ai->isIdle() && ai->getCurrentStateID() != AI_DOCK
		&& ai->getCurrentStateID() != 0x2F)
		return true;
	return false;
}

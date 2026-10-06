// cl: /MD
//
// Opaque single-inheritance destructors tail-calling AITacticOffensive::~
// AITacticOffensive at 0x005DC73C (pinned opaque base dtor; identity unproven).
// Each class below stores its own vtable and tail-calls the base destructor;
// the base itself is only declared here (defined nowhere -- it resolves via
// the pin), because a same-TU definition would capture the call locally
// instead of at the ledger address. Owner identities are unproven (opaque
// Rva names). One ledger row per destructor, landed one commit at a time.

class AITacticOffensive
{
public:
	virtual ~AITacticOffensive();
};

class AIBasePenetrationTroopsTactic : public AITacticOffensive
{
public:
	virtual ~AIBasePenetrationTroopsTactic();
};

AIBasePenetrationTroopsTactic::~AIBasePenetrationTroopsTactic()
{
}

class AISimpleAttackTactic : public AITacticOffensive
{
public:
	virtual ~AISimpleAttackTactic();
};

AISimpleAttackTactic::~AISimpleAttackTactic()
{
}

class AITacticSiege : public AITacticOffensive
{
public:
	virtual ~AITacticSiege();
};

AITacticSiege::~AITacticSiege()
{
}

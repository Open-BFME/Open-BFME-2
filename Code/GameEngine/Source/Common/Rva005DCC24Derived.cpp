// cl: /MD
//
// Opaque single-inheritance destructors tail-calling Rva005DCC24::~
// Rva005DCC24 at 0x005DCC24 (row in Rva004D759CDerived.cpp). Each class below
// stores its own vtable and tail-calls the base destructor; the base itself
// is only declared here (defined once in Rva004D759CDerived.cpp), because a
// same-TU definition would capture the call locally instead of at the ledger
// address. Owner identities are unproven (opaque Rva names). One ledger row
// per destructor, landed one commit at a time.

class Rva005DCC24
{
public:
	virtual ~Rva005DCC24();
};

class AIRoamingDefenseTactic : public Rva005DCC24
{
public:
	virtual ~AIRoamingDefenseTactic();
};

AIRoamingDefenseTactic::~AIRoamingDefenseTactic()
{
}

class AIStartWoTRBattleTactic : public Rva005DCC24
{
public:
	virtual ~AIStartWoTRBattleTactic();
};

AIStartWoTRBattleTactic::~AIStartWoTRBattleTactic()
{
}

class AIReturnTheRingTactic : public Rva005DCC24
{
public:
	virtual ~AIReturnTheRingTactic();
};

AIReturnTheRingTactic::~AIReturnTheRingTactic()
{
}

class AIRingHeroTactic : public Rva005DCC24
{
public:
	virtual ~AIRingHeroTactic();
};

AIRingHeroTactic::~AIRingHeroTactic()
{
}

class AIFarmKillSquad : public Rva005DCC24
{
public:
	virtual ~AIFarmKillSquad();
};

AIFarmKillSquad::~AIFarmKillSquad()
{
}

// cl: /O1 /MD
//
// Opaque single-inheritance destructors tail-calling Rva005CB23C::~
// Rva005CB23C at 0x005CB23C (pinned opaque leaf base dtor: vtable store
// plus ret; identity unproven). Each class below stores its own vtable and
// tail-calls the base destructor; the base itself is only declared here
// (defined nowhere -- it resolves via the pin), because a same-TU definition
// would capture the call locally instead of at the ledger address. Owner
// identities are unproven (opaque Rva names). One ledger row per destructor,
// landed one commit at a time.

class Rva005CB23C
{
public:
	virtual ~Rva005CB23C();
};

class Rva00572C6E : public Rva005CB23C
{
public:
	virtual ~Rva00572C6E();
};

Rva00572C6E::~Rva00572C6E()
{
}

class Rva00572DE8 : public Rva005CB23C
{
public:
	virtual ~Rva00572DE8();
};

Rva00572DE8::~Rva00572DE8()
{
}

class Rva00572ED8 : public Rva005CB23C
{
public:
	virtual ~Rva00572ED8();
};

Rva00572ED8::~Rva00572ED8()
{
}

class AITarget;
class Player;

struct AITargetHeuristicExpansionBase : public Rva005CB23C
{
public:
	virtual ~AITargetHeuristicExpansionBase();
	virtual void findBestTarget(AITarget *choice, Player *player, int unused);
};

AITargetHeuristicExpansionBase::~AITargetHeuristicExpansionBase()
{
}

class Rva005734EB : public Rva005CB23C
{
public:
	virtual ~Rva005734EB();
};

Rva005734EB::~Rva005734EB()
{
}

class AITargetHeuristicBaseDefense : public Rva005CB23C
{
public:
	virtual ~AITargetHeuristicBaseDefense();
};

AITargetHeuristicBaseDefense::~AITargetHeuristicBaseDefense()
{
}

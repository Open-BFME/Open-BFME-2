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

class Rva00573117 : public Rva005CB23C
{
public:
	virtual ~Rva00573117();
};

inline Rva00573117::~Rva00573117()
{
}

class Rva005734EB : public Rva005CB23C
{
public:
	virtual ~Rva005734EB();
};

inline Rva005734EB::~Rva005734EB()
{
}

class AITargetHeuristicBaseDefense : public Rva005CB23C
{
public:
	virtual ~AITargetHeuristicBaseDefense();
};

inline AITargetHeuristicBaseDefense::~AITargetHeuristicBaseDefense()
{
}

// The three destructors above are header inlines other units emit as
// select-any copies, so strong definitions here were duplicates in the linked
// build. This anchor only makes this unit emit its copies for the ledger rows;
// it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva005CB23CDerived@@YAXPAVRva00573117@@PAVRva005734EB@@PAVAITargetHeuristicBaseDefense@@@Z present-unmatched
void bfmeEmitRva005CB23CDerived(Rva00573117 *a, Rva005734EB *b, AITargetHeuristicBaseDefense *c)
{
    a->Rva00573117::~Rva00573117();
    b->Rva005734EB::~Rva005734EB();
    c->AITargetHeuristicBaseDefense::~AITargetHeuristicBaseDefense();
}
#pragma inline_depth()

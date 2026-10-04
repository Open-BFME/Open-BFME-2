// cl: /O1 /DNDEBUG /MD
//
// ??_GTeam@@MAEPAXI@Z, retail 0x003A38CD (28 bytes): slot 0
// of vtable 0x00C1AEFC, whose slot-2 name getter returns "Team" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x003A354F and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00C1AEFC, which
// identifies it as Team::~Team (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's Common/Team.h (pooled).
// Zero Hour pools the class (MEMORY_POOL_GLUE: protected virtual
// destructor and an inline class operator delete); BFME 2's form frees
// through the global operator delete, so the class is modelled with none.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;

// The this-adjusting deleting-destructor thunk (sub ecx, 0x4) in the
// secondary vtable proves a second base with a virtual destructor at +0x4;
// these two bases model only that.
class TeamBase0
{
public:
	virtual ~TeamBase0();
};

class TeamBase4
{
public:
	virtual ~TeamBase4();
};

class Team : public TeamBase0, public TeamBase4
{
public:
	Team(EmitVtableTag *);
protected:
	virtual ~Team();
};

// ?<Team::Team> absent-from-retail
Team::Team(EmitVtableTag *)
{
}

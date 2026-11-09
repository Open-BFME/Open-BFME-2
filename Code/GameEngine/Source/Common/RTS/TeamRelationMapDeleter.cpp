// cl: /O1 /DNDEBUG /MD
//
// ??_GTeamRelationMap@@MAEPAXI@Z, retail 0x003A2A8A (28 bytes): slot 0
// of vtable 0x00C1ADFC, whose slot-2 name getter returns "TeamRelationMap" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x003A2563 and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00C1ADFC, which
// identifies it as TeamRelationMap::~TeamRelationMap (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's Common/Team.h (pooled).
// Zero Hour pools the class (MEMORY_POOL_GLUE: protected virtual
// destructor and an inline class operator delete); BFME 2's form frees
// through the global operator delete, so the class is modelled with none.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;
class Xfer;

class TeamRelationMap
{
public:
	TeamRelationMap(EmitVtableTag *);
protected:
	virtual ~TeamRelationMap();
public:
protected:
	// Retail's table 0x00C1ADFC: slot 1 an empty body (0x000B3FD0, folded), slot 2 the name
	// getter 0x003A25AB, slot 3 the rowed xfer, as in TeamRelationMapDtor_Rva003A2563.cpp's copy.
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *xfer);
};

// ?<TeamRelationMap::TeamRelationMap> absent-from-retail
TeamRelationMap::TeamRelationMap(EmitVtableTag *)
{
}

void TeamRelationMap::loadPostProcess()
{
}

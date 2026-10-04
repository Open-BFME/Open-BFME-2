// cl: /O1 /MD
//
// Opaque multiple-inheritance destructor tail-calling the matched
// Locomotor::~Locomotor at 0x003067D2 (defined in
// GameLogic/Object/Locomotor.cpp; only declared here so the tail-call
// resolves to the ledger address instead of a same-TU definition). The
// class below derives from Locomotor alone, whose two bases give the vptrs
// at +0x00/+0x04 (0xBC5A5C/0xBC5A24, DIR32 auto-patches); the derived
// destructor stores both vptrs and tail-calls the base destructor.
// The base declares a protected virtual dtor to mangle MAE like the row.
// Owner identity is unproven (opaque Rva name). One ledger row per
// destructor, landed one commit at a time.

// Locomotor's two vptrs (+0x00 and +0x04, Zero Hour's MemoryPoolObject and
// Snapshot bases) both lead tables with a deleting destructor: the
// this-adjusting thunk at 0x00064801 (sub ecx, 4; jmp to this class's
// scalar deleting destructor 0x00064809) and Locomotor's own at 0x003067CA
// are target evidence that the +0x04 base has a virtual destructor in BFME 2.
// The bases are declared only; this TU emits nothing of theirs.
class LocomotorPrimaryBase
{
protected:
	virtual ~LocomotorPrimaryBase();
};

class LocomotorSnapshotBase
{
protected:
	virtual ~LocomotorSnapshotBase();
};

class Locomotor : public LocomotorPrimaryBase, public LocomotorSnapshotBase
{
protected:
	virtual ~Locomotor();
};

class Rva000647D4 : public Locomotor
{
public:
	virtual ~Rva000647D4();
};

Rva000647D4::~Rva000647D4()
{
}

// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /MD /EHsc
//
// ??1CarryoverUnit@@UAE@XZ, retail 0x0037dee4, 72 bytes. Banked partial (score 1.0) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// BANK ONLY: destructor bytes exact; complete vtable providers/owner names
// require reconciliation before this can be moved to Code. Target slots:
// scalar dtor1EB815; shared noopB3FD0; name37DC84; xfer37DE79.
// Getter currently owned by Rva0037DC84Named::name. Existing ctor37DF2C /
// copy1EB79E and destructor pins Rva0037DEE4/Rva0037DF2C/Element remain
// address-named views of this same CarryoverUnit record; retain consumers
// until a verified class reconciliation gives them one shared owner.
// Vtable BDF158 names CarryoverUnit and slot3 is existing xfer37DE79.
// Native37DEE4..37DF2C72B and WB F5D6C0 prove name4 and member94
// cleanup, followed by Snapshot vptrBBB554. The member dtor1EB05E is
// independently rowed from UnitRevivalEntry with strings atC/10.
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "Common/Snapshot.h"
class Rva001EB05E{public:~Rva001EB05E();private:char bytes[0x20];};
class Xfer;
class CarryoverUnit:public Snapshot{public:virtual ~CarryoverUnit();virtual void loadPostProcess();virtual const char*GetSnapshotName()const;virtual void xfer(Xfer*);private:AsciiString name;char fields08[0x94-8];Rva001EB05E member;};
CarryoverUnit::~CarryoverUnit(){}

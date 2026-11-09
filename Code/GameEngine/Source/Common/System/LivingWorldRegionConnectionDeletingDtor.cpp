// cl: /Ireference/shims/moduledata /MD
// Each destructor rowed in another unit is only declared here: the inline
// constructor references the vtable, which brings the compiler's deleting
// destructor into this unit without a second definition of the destructor;
// its int tag keeps it from spelling a real default constructor.

// ??_GLivingWorldRegionConnection@@UAEPAXI@Z, the scalar deleting
// destructor in vtable 0x00C36E48 slot 0 (retail 0x003F2A70, 28 bytes).
// The class is declared locally only so its deleting destructor is
// emitted; the complete-destructor call resolves through that
// destructor's own row at 0x003F2517, and the operator delete through
// the rowed 0x0002FD60. The Snapshot base and the remaining virtuals repeat
// LivingWorldRegionConnectionCtor.cpp's view (vtable 0x00C36E48), so this
// unit's vtable copy is the one every other unit emits.
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "Common/Snapshot.h"

class LivingWorldRegionConnection : public Snapshot
{
public:
	explicit LivingWorldRegionConnection(int);
	virtual ~LivingWorldRegionConnection();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &xfer);
private:
	int m_famgen;
};

// The class is abstract in this view, so a defined tag constructor (no
// retail counterpart) emits the vtable instead of a new-expression.
// ?<LivingWorldRegionConnection::LivingWorldRegionConnection> absent-from-retail
LivingWorldRegionConnection::LivingWorldRegionConnection(int)
{
}

void famgenDelete(LivingWorldRegionConnection *livingWorldRegionConnection)
{
	delete livingWorldRegionConnection;
}

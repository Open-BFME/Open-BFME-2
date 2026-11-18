// ??0DefaultPhysicsModuleInfo@FXParticleSystem@@QAE@ABV01@@Z
// cl: /O1 /DNDEBUG /MD /EHsc
// Retail RVA 0x003A7736, 64 bytes. The export table names this address
// FXParticleSystem::DefaultPhysicsModuleInfo's copy constructor; it installs
// that class's exported vtable 0x00C1BCB0 (slots LoadPostProcess 0x000B3FD0,
// GetSnapshotName 0x003A612D, DoXfer 0x0055EECB) on a Snapshot base whose
// destructor is the exported fold 0x0049B47C. Body: vptr + four ints +
// wholesale 3-dword block + two bytes.
// The barrier places retail's push esi/edi after the +0x10 load (without it
// this shape pushes esi before the +0x0C store); named ints vs an
// array-held block give identical output.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "../../Include/Common/ScalarTypes.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

struct PhysicsBlock
{
	Int m_v0;
	Int m_v1;
	Int m_v2;
};

class DefaultPhysicsModuleInfo : public Snapshot
{
public:
	DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &other);
	virtual ~DefaultPhysicsModuleInfo();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(Xfer &);

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	PhysicsBlock m_block14;
	char m_field20;
	char m_field21;
};

DefaultPhysicsModuleInfo::DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	_ReadWriteBarrier();
	m_block14 = other.m_block14;
	m_field20 = other.m_field20;
	m_field21 = other.m_field21;
}

}

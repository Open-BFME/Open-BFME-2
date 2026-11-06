// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ob2

// LifeEventModuleInfo default constructor @0x564001 (91B). Retail: own
// vtable, an AsciiString at +4 (its inline ctor stores the null buffer and
// its rowed dtor 0x0048BA39 is what the state-1 unwind funclet calls on
// this+4), a GameClientRandomVariable at +8 zeroed inline then ranged (0, 0)
// through the rowed setRange 0x002341E7, and a zeroed int at +0x14.

#include "ascii_string.h"

#include "../../../../Include/GameClient/GameClientRandomVariable.h"
#include "../../../../Include/GameClient/GameClientRandomVariableInlines.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

class LifeEventModuleInfo : public Snapshot
{
public:
	LifeEventModuleInfo();
	virtual ~LifeEventModuleInfo();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &xfer);

private:
	AsciiString m_name;
	GameClientRandomVariable m_var;
	int m_14;
};

// ??0LifeEventModuleInfo@FXParticleSystem@@QAE@XZ @0x564001
LifeEventModuleInfo::LifeEventModuleInfo() : m_14(0)
{
	m_var.setRange(0.0f, 0.0f);
}

}

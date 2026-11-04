// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ob2

// TerrainCollisionModuleInfo default constructor @0x56459E (96B). Retail: own
// vtable, an AsciiString at +4 (its inline ctor stores the null buffer and
// its rowed dtor 0x0048BA39 is what the state-1 unwind funclet calls on
// this+4), a GameClientRandomVariable at +8 zeroed inline then ranged (0, 0)
// through the rowed setRange 0x002341E7, a zeroed int at +0x18, and the flag
// at +0x14 cleared after the call (retail keeps the zero in ebx across it).

#include "ascii_string.h"

#include "../../../../Include/GameClient/GameClientRandomVariable.h"
#include "../../../../Include/GameClient/GameClientRandomVariableInlines.h"

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_NONCONST_NAME_SLOT
#define BFME_SNAPSHOT_REFERENCE_XFER
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

namespace FXParticleSystem
{

class TerrainCollisionModuleInfo : public Snapshot
{
public:
	TerrainCollisionModuleInfo();
	virtual ~TerrainCollisionModuleInfo();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer(::Xfer &);

private:
	AsciiString m_name;
	GameClientRandomVariable m_var;
	bool m_flag14;
	int m_18;
};

// ??0TerrainCollisionModuleInfo@FXParticleSystem@@QAE@XZ @0x56459E
TerrainCollisionModuleInfo::TerrainCollisionModuleInfo() : m_18(0)
{
	m_var.setRange(0.0f, 0.0f);
	m_flag14 = false;
}

}

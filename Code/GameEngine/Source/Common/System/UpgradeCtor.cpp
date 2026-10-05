// cl: /Ireference/shims/moduledata /O1 /DNDEBUG /MD
//
// ??0Upgrade@@QAE@PBVUpgradeTemplate@@@Z @0x0026EDDC (29B): Zero Hour
// Upgrade::Upgrade(const UpgradeTemplate *). Target evidence: the only caller,
// the Player addUpgrade body 0x002AE329, news 0x14 bytes, constructs with the
// upgrade template and then links the result through +0x0C/+0x10 on the
// player's upgrade list (+0x9C) and sets +0x08 to the status (1 in
// production, 2 complete). The ctor stores the template at +0x04, zeroes
// status, next and prev, and installs vtable 0x00BFAA9C whose slots are the
// deleting destructor 0x0026EF34, the shared empty body 0x000B3FD0, the
// name getter 0x0026EDF9 returning "Upgrade" and the status xfer 0x0026EE11
// (UpgradeStatusType through Xfer); the destructor 0x0026EDFF falls back to
// the Snapshot vtable 0x00BBB554. One vtable pointer, so BFME 2's Upgrade is a
// plain Snapshot (no separate MemoryPoolObject base, plain operator new). An
// earlier AABTreeLinkClass name for this address was retracted (see
// reverse/re_attempts.log).

#include "Common/Snapshot.h"

class UpgradeTemplate;

enum UpgradeStatusType
{
	UPGRADE_STATUS_INVALID = 0,
	UPGRADE_STATUS_IN_PRODUCTION,
	UPGRADE_STATUS_COMPLETE
};

class Upgrade : public Snapshot
{
public:
	Upgrade(const UpgradeTemplate *upgradeTemplate);
	virtual ~Upgrade();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

private:
	const UpgradeTemplate *m_template;		// +0x04
	UpgradeStatusType m_status;				// +0x08
	Upgrade *m_next;						// +0x0C
	Upgrade *m_prev;						// +0x10
};

Upgrade::Upgrade(const UpgradeTemplate *upgradeTemplate)
{
	m_template = upgradeTemplate;
	m_status = UPGRADE_STATUS_INVALID;
	m_next = 0;
	m_prev = 0;
}

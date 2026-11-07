// Shared partial receiver for the matched pool-key, constructor and
// apply/remove bodies. The implementation donor proves the +0x10 secondary
// UpgradeMux receiver and ModuleData/Object operands; the constructor's four
// vptr stores prove the subobjects at +0x00, +0x0C, +0x10 and +0x18, named as
// the data ledger names StatusBitsUpgrade's vtables.
#ifndef BFME2_STATUS_BITS_UPGRADE_VIEW_H
#define BFME2_STATUS_BITS_UPGRADE_VIEW_H

enum NameKeyType { NK_UNKNOWN = 0 };

class Rva00346BC0
{
	public:
	unsigned int m_words[4];
};

class Object
{
public:
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
};

class Thing;
class ModuleData;
// The class is StatusBitsUpgrade.h's, over the canonical UpgradeModule.h.
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../Include/GameLogic/Module/StatusBitsUpgrade.h"

class StatusBitsUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	Rva00346BC0 m_statusToSet;
	Rva00346BC0 m_statusToClear;
};


#endif

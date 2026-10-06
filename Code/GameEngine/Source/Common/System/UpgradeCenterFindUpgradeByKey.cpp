// cl: /DNDEBUG /MD /EHsc
//
// ?findUpgradeByKey@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4NameKeyType@@@Z,
// retail 0x0026EEB8, 22 bytes. Dedicated TU (Upgrade.cpp itself is
// unstageable: ~20 unmarked defs trip find_declared_unmatched, same wall as
// marker-less meshmdlio.cpp/meshmatdesc.cpp; drain it via new TUs).
//
// Zero Hour reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source/Common/System/Upgrade.cpp,
// UpgradeCenter::findUpgradeByKey): const key-compare walk over the template
// list. BFME2 layout measured from retail: list head at UpgradeCenter+0x0C
// (ZH +0x08), name key at UpgradeTemplate+0x0C (same as ZH), next link at
// +0x64 (ZH +0x108). Leaf: no calls, no pins.

typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class UpgradeTemplate
{
public:
	NameKeyType getUpgradeNameKey() const { return m_nameKey; }
	int getMaskIndex() const { return m_maskIndex; }
	const UpgradeTemplate *friend_getNext() const { return m_next; }
	UpgradeTemplate *friend_getNext() { return m_next; }
	const UpgradeTemplate *friend_getPrev() const { return m_prev; }
	UpgradeTemplate *friend_getPrev() { return m_prev; }
	void friend_setNext(UpgradeTemplate *n) { m_next = n; }
	void friend_setPrev(UpgradeTemplate *p) { m_prev = p; }

private:
	unsigned char m_unreconstructed_000[0x0C];
	NameKeyType m_nameKey; // +0x0C
	unsigned char m_pad010[0x38 - 0x10];
	int m_maskIndex; // +0x38 mask bit index retail-measured
	unsigned char m_pad03C[0x64 - 0x3C];
	UpgradeTemplate *m_next; // +0x64
	UpgradeTemplate *m_prev; // +0x68
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgradeByKey(NameKeyType key) const;
	const UpgradeTemplate *rva0026EEA0(int key) const;

protected:
	void unlinkUpgrade(UpgradeTemplate *upgrade);

private:
	unsigned char m_unreconstructed_000[0x0C];
	UpgradeTemplate *m_upgradeList; // +0x0C
};

// ?findUpgradeByKey@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4NameKeyType@@@Z
const UpgradeTemplate *UpgradeCenter::findUpgradeByKey(NameKeyType key) const
{
	const UpgradeTemplate *upgrade;

	// search list
	for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext())
		if (upgrade->getUpgradeNameKey() == key)
			return upgrade;

	// item not found
	return 0;
}

//
// rva0026EEA0 at UpgradeCenter (mangled ?rva0026EEA0@UpgradeCenter@@QBEPBVUpgradeTemplate@@H@Z rowed),
// retail 0x0026EEA0, 24 bytes. Adjacent to findUpgradeByKey (ends at 0x0026EEB8).
// Same list walk but comparing mask bit index at +0x38 (UpgradeMuxData TU
// measures it as plain int). Callers pass TheUpgradeCenter (0x009FEB60) with a
// 0..0x400 index and use template+8 (m_name) or +0x28 fields on hit.
//
const UpgradeTemplate *UpgradeCenter::rva0026EEA0(int key) const
{
	const UpgradeTemplate *upgrade;

	// search list
	for (upgrade = m_upgradeList; upgrade; upgrade = upgrade->friend_getNext())
		if (key == upgrade->getMaskIndex())
			return upgrade;

	// item not found
	return 0;
}

// unlinkUpgrade at retail 0x0026EEF2 44 bytes: ZH Upgrade.cpp unlink verbatim
// with BFME2 links at +0x64 next and +0x68 prev and head at +0x0C.
void UpgradeCenter::unlinkUpgrade(UpgradeTemplate *upgrade)
{
	if (upgrade == 0)
		return;

	if (upgrade->friend_getNext())
		upgrade->friend_getNext()->friend_setPrev(upgrade->friend_getPrev());
	if (upgrade->friend_getPrev())
		upgrade->friend_getPrev()->friend_setNext(upgrade->friend_getNext());
	else
		m_upgradeList = upgrade->friend_getNext();
}

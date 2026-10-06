// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// UpgradeCenter::newUpgrade, retail 0x0026F952 (179 bytes):
// ?newUpgrade@UpgradeCenter@@QAEPAVUpgradeTemplate@@ABVAsciiString@@_N@Z
// Identity (target): WorldBuilder's debug Upgrade.cpp
// UpgradeCenter::newUpgrade builds the "DefaultUpgrade" name and calls, in
// retail's order, operator new(0x9C), the UpgradeTemplate constructor
// (0x0026F5B3), UpgradeCenter::findUpgrade, the copy assignment
// (0x0026F767), StringBase::set, nameToKey and the link step 0x0026EED0.
// Donor (Zero Hour UpgradeCenter::newUpgrade): copy the default upgrade
// when present, set the name and its key, link the new upgrade. BFME 2
// delta (target): when the second argument is set the upgrade takes the
// next mask bit index (+0x38 from the centre's +0x10 counter).
// Layout (target): name +0x08, name key +0x0C.
#include "ascii_string.h"

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class UpgradeTemplate
{
public:
	UpgradeTemplate();
	UpgradeTemplate &operator=(const UpgradeTemplate &that);
	void setUpgradeName(const AsciiString &name) { m_name = name; }
	void setUpgradeNameKey(NameKeyType key) { m_nameKey = key; }
	void friend_setMaskBitIndex(int index) { m_maskBitIndex = index; }

private:
	unsigned char m_pad00[0x08];
	AsciiString m_name; // +0x08
	NameKeyType m_nameKey; // +0x0C
	unsigned char m_pad10[0x38 - 0x10];
	int m_maskBitIndex; // +0x38
	unsigned char m_pad3C[0x9C - 0x3C];
};

class UpgradeCenter
{
public:
	UpgradeTemplate *newUpgrade(const AsciiString &name, bool assignMaskBit);
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
	void linkUpgrade(UpgradeTemplate *upgrade);

private:
	unsigned char m_pad00[0x10];
	int m_nextTemplateMaskBit; // +0x10
};

UpgradeTemplate *UpgradeCenter::newUpgrade(const AsciiString &name, bool assignMaskBit)
{
	UpgradeTemplate *newUpgrade = new UpgradeTemplate;

	// copy data from the default upgrade
	const UpgradeTemplate *defaultUpgrade = findUpgrade("DefaultUpgrade");
	if (defaultUpgrade)
		*newUpgrade = *defaultUpgrade;

	// assign name and starting data
	newUpgrade->setUpgradeName(name);
	newUpgrade->setUpgradeNameKey(TheNameKeyGenerator->nameToKey(name));
	if (assignMaskBit)
	{
		newUpgrade->friend_setMaskBitIndex(m_nextTemplateMaskBit);
		m_nextTemplateMaskBit++;
	}

	// link upgrade
	linkUpgrade(newUpgrade);
	return newUpgrade;
}

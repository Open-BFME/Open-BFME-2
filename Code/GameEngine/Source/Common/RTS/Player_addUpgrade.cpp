// cl: /DNDEBUG /MD /EHsc
//
// ?addUpgrade@Player@@QAEPAVUpgrade@@PBVUpgradeTemplate@@W4UpgradeStatusType@@H@Z
// @0x002AE329
// (203B): Zero Hour Player::addUpgrade with BFME 2's pass-through int. Target
// evidence: the rowed upgrade-list find 0x002AA031 (head Player +0x9C, keyed
// by the template); on a miss a 0x14-byte operator new plus the matched
// Upgrade ctor 0x0026EDDC (EH frame for the new), prev cleared and the node
// pushed on the list head through +0x0C next / +0x10 prev; the status (+0x08)
// is stored, status 1 (UPGRADE_STATUS_IN_PRODUCTION) sets the template's
// +0x38 bit in the in-progress mask +0xBC, status 2 (UPGRADE_STATUS_COMPLETE)
// moves it to the completed mask +0x13C and calls the onUpgradeCompleted
// body 0x002AD93A with the template and the int; the node is returned
// (mov eax, ebx). The existing pin spells this address with a void return,
// which the retail eax result refutes. Callers include 0x0033557F
// (status 2, 0) and 0x001EC745 / 0x0021979C / 0x002AEDF8.

#include "PlayerUpgradeStatus.h"

typedef int Int;

class UpgradeTemplate
{
public:
	unsigned int getUpgradeBit() const { return m_bit; }

private:
	char m_pad[0x38];
	unsigned int m_bit;							// +0x38
};

class Upgrade
{
public:
	Upgrade(const UpgradeTemplate *upgradeTemplate);
	Upgrade *friend_getNext() const { return m_next; }
	__declspec(dllimport) __forceinline void friend_setNext(Upgrade *next) { m_next = next; }
	__declspec(dllimport) __forceinline void friend_setPrev(Upgrade *prev) { m_prev = prev; }
	__declspec(dllimport) __forceinline void setStatus(UpgradeStatusType status) { m_status = status; }

private:
	void *m_vtbl;
	const UpgradeTemplate *m_template;			// +0x04
	UpgradeStatusType m_status;					// +0x08
	Upgrade *m_next;							// +0x0C
	Upgrade *m_prev;							// +0x10
};

// The rowed list find's node type is the Upgrade above.


struct UpgradeMaskType
{
public:
	void clear(unsigned int bit) { m_bits[bit >> 5] &= ~(1 << (bit & 0x1F)); }
	void set(unsigned int bit) { m_bits[bit >> 5] |= 1 << (bit & 0x1F); }
private:
	unsigned int m_bits[0x20]; // +0x00
};

class Player
{
public:
	Upgrade *addUpgrade(const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status, Int x);
	void onUpgradeCompleted(const UpgradeTemplate *upgradeTemplate, Int x);
	Upgrade *findUpgrade(const UpgradeTemplate *upgradeTemplate);	// rowed 0x002AA031 (Rva002AA031Find.cpp)

private:
	char m_pad[0x9C];
	Upgrade *m_upgradeList;						// +0x9C
	char m_padA0[0xBC - 0xA0];
	UpgradeMaskType m_upgradesInProgress;		// +0xBC
	UpgradeMaskType m_upgradesCompleted;		// +0x13C
};

Upgrade *Player::addUpgrade(const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status, Int x)
{
	Upgrade *upgrade = findUpgrade(upgradeTemplate);
	if (upgrade == 0)
	{
		upgrade = new Upgrade(upgradeTemplate);
		upgrade->friend_setPrev(0);
		upgrade->friend_setNext(m_upgradeList);
		if (m_upgradeList)
			m_upgradeList->friend_setPrev(upgrade);
		m_upgradeList = upgrade;
	}

	upgrade->setStatus(status);

	unsigned int newBit = upgradeTemplate->getUpgradeBit();
	if (status == UPGRADE_STATUS_IN_PRODUCTION)
	{
		m_upgradesInProgress.set(newBit);
	}
	else if (status == UPGRADE_STATUS_COMPLETE)
	{
		m_upgradesInProgress.clear(newBit);
		m_upgradesCompleted.set(newBit);
		onUpgradeCompleted(upgradeTemplate, x);
	}

	return upgrade;
}

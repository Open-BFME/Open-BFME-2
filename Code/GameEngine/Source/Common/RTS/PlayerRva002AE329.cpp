// cl: /DNDEBUG /MD /EHsc
//
// ?rva002AE329@Player@@QAEPAVUpgrade@@PBVUpgradeTemplate@@W4UpgradeStatusType@@H@Z
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
	void friend_setNext(Upgrade *next) { m_next = next; }
	void friend_setPrev(Upgrade *prev) { m_prev = prev; }
	void setStatus(UpgradeStatusType status) { m_status = status; }

private:
	void *m_vtbl;
	const UpgradeTemplate *m_template;			// +0x04
	UpgradeStatusType m_status;					// +0x08
	Upgrade *m_next;							// +0x0C
	Upgrade *m_prev;							// +0x10
};

// The rowed list find's node type is the Upgrade above.
struct Rva002AA031Node;

class Rva002AA031Holder
{
public:
	Rva002AA031Node *find(Int key);
};

class UpgradeMaskType
{
public:
	void set(unsigned int bit) { m_bits[bit >> 5] |= 1 << (bit & 0x1F); }
	void clear(unsigned int bit) { m_bits[bit >> 5] &= ~(1 << (bit & 0x1F)); }

private:
	unsigned int m_bits[0x20];
};

class Player
{
public:
	Upgrade *rva002AE329(const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status, Int x);
	void rva002AD93A(const UpgradeTemplate *upgradeTemplate, Int x);
	Upgrade *findUpgrade(const UpgradeTemplate *upgradeTemplate)
	{
		return (Upgrade *)((Rva002AA031Holder *)this)->find((Int)upgradeTemplate);
	}

private:
	char m_pad[0x9C];
	Upgrade *m_upgradeList;						// +0x9C
	char m_padA0[0xBC - 0xA0];
	UpgradeMaskType m_upgradesInProgress;		// +0xBC
	UpgradeMaskType m_upgradesCompleted;		// +0x13C
};

Upgrade *Player::rva002AE329(const UpgradeTemplate *upgradeTemplate, UpgradeStatusType status, Int x)
{
	Upgrade *u = findUpgrade(upgradeTemplate);
	if (u == 0)
	{
		u = new Upgrade(upgradeTemplate);
		u->friend_setPrev(0);
		u->friend_setNext(m_upgradeList);
		if (m_upgradeList)
			m_upgradeList->friend_setPrev(u);
		m_upgradeList = u;
	}

	u->setStatus(status);

	unsigned int newBit = upgradeTemplate->getUpgradeBit();
	if (status == UPGRADE_STATUS_IN_PRODUCTION)
	{
		m_upgradesInProgress.set(newBit);
	}
	else if (status == UPGRADE_STATUS_COMPLETE)
	{
		m_upgradesInProgress.clear(newBit);
		m_upgradesCompleted.set(newBit);
		rva002AD93A(upgradeTemplate, x);
	}

	return u;
}

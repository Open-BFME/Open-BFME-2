// cl: /O1 /DNDEBUG /MD
//
// ?rva002ADAC3@Player@@QAEXPBVUpgradeTemplate@@H@Z @0x002ADAC3 (140B): Zero
// Hour Player::removeUpgrade with BFME 2's pass-through int and a type gate.
// Target evidence: an upgrade template whose +0x04 type is 1 goes straight to
// 0x002AD9FD (the onUpgradeRemoved counterpart: it walks the player's team
// prototypes like the onUpgradeCompleted body 0x002AD93A) with both
// arguments; otherwise the rowed upgrade-list find 0x002AA031 (list head
// Player +0x9C, keyed by the template) yields the node, which is unlinked
// through its +0x0C next / +0x10 prev links exactly as ZH does, the
// template's +0x38 bit index is cleared from the in-progress (+0xBC) and
// completed (+0x13C) masks, and a node whose +0x08 status is 2
// (UPGRADE_STATUS_COMPLETE) calls 0x002AD9FD. Unlike ZH the node is not
// freed here and no ControlBar refresh follows. Callers 0x0021B590,
// 0x00335587, 0x00486C3F.

typedef int Int;

class UpgradeTemplate
{
public:
	Int getUpgradeType() const { return m_type; }
	Int getUpgradeBit() const { return m_bit; }

private:
	char m_pad[0x04];
	Int m_type;									// +0x04
	char m_pad08[0x38 - 0x08];
	Int m_bit;									// +0x38
};

// The rowed list find's node type is the Upgrade below.
struct Rva002AA031Node;

class Upgrade
{
public:
	Upgrade *friend_getNext() const { return m_next; }
	Upgrade *friend_getPrev() const { return m_prev; }
	void friend_setNext(Upgrade *next) { m_next = next; }
	void friend_setPrev(Upgrade *prev) { m_prev = prev; }
	Int getStatus() const { return m_status; }

private:
	void *m_vtbl;
	const UpgradeTemplate *m_template;			// +0x04
	Int m_status;								// +0x08
	Upgrade *m_next;							// +0x0C
	Upgrade *m_prev;							// +0x10
};

class Rva002AA031Holder
{
public:
	Rva002AA031Node *find(Int key);
};

class UpgradeMaskType
{
public:
	void clear(unsigned int bit) { m_bits[bit >> 5] &= ~(1 << (bit & 0x1F)); }

private:
	unsigned int m_bits[0x20];
};

enum
{
	UPGRADE_STATUS_COMPLETE = 2
};

class Player
{
public:
	void rva002ADAC3(const UpgradeTemplate *upgradeTemplate, Int x);
	void rva002AD9FD(const UpgradeTemplate *upgradeTemplate, Int x);
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

void Player::rva002ADAC3(const UpgradeTemplate *upgradeTemplate, Int x)
{
	if (upgradeTemplate->getUpgradeType() == 1)
	{
		rva002AD9FD(upgradeTemplate, x);
		return;
	}

	Upgrade *upgrade = findUpgrade(upgradeTemplate);
	if (upgrade)
	{
		if (upgrade->friend_getNext())
			upgrade->friend_getNext()->friend_setPrev(upgrade->friend_getPrev());
		if (upgrade->friend_getPrev())
			upgrade->friend_getPrev()->friend_setNext(upgrade->friend_getNext());
		else
			m_upgradeList = upgrade->friend_getNext();

		m_upgradesInProgress.clear(upgradeTemplate->getUpgradeBit());
		m_upgradesCompleted.clear(upgradeTemplate->getUpgradeBit());

		if (upgrade->getStatus() == UPGRADE_STATUS_COMPLETE)
			rva002AD9FD(upgradeTemplate, x);
	}
}

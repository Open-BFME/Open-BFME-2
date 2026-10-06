// cl: /DNDEBUG /MD
//
// ?forceRefreshUpgrade@UpgradeMux@@UAEXXZ, retail 0x004CE270, 12 bytes.
// ?attemptUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z, retail 0x004CE27C, 33 bytes.
// UpgradeMux slots 5 and 1 of vftable 0x00C5FF10 (installed by the rowed
// ??0UpgradeMux at 0x004CE2A3); both are shared by the 17 behavior
// vftables that embed an UpgradeMux. Donor ZH UpgradeModule.cpp:
//   forceRefreshUpgrade: if executed, re-run upgradeImplementation (slot 10,
//     the slot the rowed giveSelfUpgrade calls third);
//   attemptUpgrade: if wouldUpgrade (slot 2, rowed 0x004CE2B0) then
//     giveSelfUpgrade (rowed 0x0045230C) and return true.
// Retail's attemptUpgrade pops one dword (ret 4) and forwards it unchanged,
// so BFME2 passes the mask by reference, not by value as ZH does.

template <int NUMBITS> class BitFlags
{
private:
	unsigned int m_bits[NUMBITS / 32];
};

typedef BitFlags<128> UpgradeMaskType;

class UpgradeMux
{
public:
	void giveSelfUpgrade();

	virtual void slot00();
	virtual bool attemptUpgrade(const UpgradeMaskType &keyMask);
	virtual bool wouldUpgrade(const UpgradeMaskType &keyMask) const;
	virtual void slot03();
	virtual void slot04();
	virtual void forceRefreshUpgrade();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void upgradeImplementation();

private:
	bool m_upgradeExecuted; // +4
};

// ?forceRefreshUpgrade@UpgradeMux@@UAEXXZ @0x004CE270
void UpgradeMux::forceRefreshUpgrade()
{
	if (m_upgradeExecuted)
	{
		upgradeImplementation();
	}
}

// ?attemptUpgrade@UpgradeMux@@UAE_NABV?$BitFlags@$0IA@@@@Z @0x004CE27C
bool UpgradeMux::attemptUpgrade(const UpgradeMaskType &keyMask)
{
	if (wouldUpgrade(keyMask))
	{
		giveSelfUpgrade();
		return true;
	}
	return false;
}

// cl: /O1 /DNDEBUG /MD
//
// BFME2's options screen Apt callback "AptOptions::RefreshNat", 0x005182AB,
// bound by that name as a member pointer by the screen's registration; that
// binding is its only reference. Zero Hour's firewall refresh (OptionsMenu's
// ButtonFirewallRefresh) behind the screen's +0x283 flag.

// Zero Hour's FirewallHelperClass and TheFirewallHelper (0x00E063B0); the
// helper is deleted through its vslot 0 and a separate operator delete
// (AnimateWindowManager.cpp's spelling).
class FirewallHelperClass
{
public:
	virtual void *deleteInstance(int flags);

	void flagNeedToRefresh(bool flag);
	bool behaviorDetectionUpdate();
	// Rowed as the free ?Rva00595E46Save@@YAXXZ; called here as Zero Hour's
	// member, pinned by address.
	void writeFirewallBehavior();
};

extern FirewallHelperClass *TheFirewallHelper;

// Rva00595143Firewall.cpp's createFirewallHelper.
FirewallHelperClass *Rva00595143Get();

// Rva00595D95Firewall.cpp's detectFirewall.
class Rva00595D95
{
public:
	bool rva00595D95();
};

class AptOptions
{
public:
	void RefreshNat(const char *unused);

private:
	unsigned char m_pad000[0x283];
	bool m_online; // +0x283
};

// Retail 0x005182AB, 174 bytes: "AptOptions::RefreshNat".
void AptOptions::RefreshNat(const char *unused)
{
	if (!m_online)
		return;
	if (TheFirewallHelper == 0)
		TheFirewallHelper = Rva00595143Get();
	TheFirewallHelper->flagNeedToRefresh(true);
	if (((Rva00595D95 *)TheFirewallHelper)->rva00595D95() == true)
	{
		::operator delete(TheFirewallHelper ? TheFirewallHelper->deleteInstance(0) : 0);
		TheFirewallHelper = 0;
	}
	if (TheFirewallHelper != 0)
	{
		while (TheFirewallHelper->behaviorDetectionUpdate() == false)
			;
		TheFirewallHelper->writeFirewallBehavior();
		TheFirewallHelper->flagNeedToRefresh(false);
		::operator delete(TheFirewallHelper ? TheFirewallHelper->deleteInstance(0) : 0);
		TheFirewallHelper = 0;
	}
}

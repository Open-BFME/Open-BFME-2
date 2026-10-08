// cl: /O1 /DNDEBUG /MD /EHsc
//
// ThingTemplate::getCurrentLivingWorldAutoResolveWeapon, retail 0x0033A9E2
// (61 bytes, ret 4).
// Identity (target): WorldBuilder's debug ThingTemplate.cpp names it
// (wb-lead 2/callgraph): walk the auto-resolve weapon entries, return the
// first entry's weapon whose condition check passes, else the default weapon.
// Retail facts: entries are 0x104 bytes from +0x3F8 to +0x3FC with the weapon
// pointer at entry +0; each is tested by the rowed const check 0x0033A8D9
// with the caller's argument; the fallback is the rowed default getter
// 0x004196F8 on the global at VA 0x00E030C0. Argument and return types are
// not established and stay opaque pointers; the entry and getter classes
// keep their address-derived names.

// Address-named auto-resolve weapon entry (0x104 bytes).
class Rva0033A8D9
{
public:
	bool rva0033A8D9(const void *context) const;
	void *getWeapon() const { return m_weapon; }

private:
	void *m_weapon; // +0x00
	unsigned char m_pad004[0x104 - 0x04];
};

class Rva0041811D
{
public:
	void *rva004196F8();
};

extern class Rva0041811D *g_Va00E030C0;

class ThingTemplate
{
public:
	void *getCurrentLivingWorldAutoResolveWeapon(const void *context) const;

private:
	unsigned char m_pad000[0x3F8];
	Rva0033A8D9 *m_autoResolveWeaponsBegin; // +0x3F8
	Rva0033A8D9 *m_autoResolveWeaponsEnd; // +0x3FC
};

void *ThingTemplate::getCurrentLivingWorldAutoResolveWeapon(const void *context) const
{
	const Rva0033A8D9 *end = m_autoResolveWeaponsEnd;
	for (const Rva0033A8D9 *it = m_autoResolveWeaponsBegin; it != end; ++it)
	{
		if (it->rva0033A8D9(context))
			return it->getWeapon();
	}
	return g_Va00E030C0->rva004196F8();
}

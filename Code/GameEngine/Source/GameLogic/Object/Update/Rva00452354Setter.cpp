// cl: /MD
//
// ?rva00452354@UpgradeMux@@QAEX_N@Z, retail 0x00452354, 10 bytes.
// Gap between 0x0045232D (Rva dtor) and 0x0045235E (AutoHeal pool key).
// Shared slot 9 (offset 0x24) of UpgradeMux member vtables (AutoHeal
// 0x83FC88 plus Replenish 0x849F20 plus AttributeModifier 0x850CD8 plus
// RadiateFear 0x850F68 and others) via rowed ctor evidence. Sets bool at
// +4 (m_upgradeExecuted). Donor ZH UpgradeModule.h backs the UpgradeMux
// name and bool shape. Honest address name: virtualness unproven.

class UpgradeMux
{
public:
	void rva00452354(bool e);

private:
	void *m_vtable;
	bool m_executed;
};

void UpgradeMux::rva00452354(bool e)
{
	m_executed = e;
}

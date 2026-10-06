// cl: /DNDEBUG /MD /EHsc
// ?setCopiedFromDefault@ThingTemplate@@QAEXXZ @0x0033B539 71B
// Evidence: callers in ThingFactory 0x002D1B10 0x002D1BC4 0x002D1D48 (newTemplate->setCopiedFromDefault);
// 2 bools at +0x5E9/+0x5EA plus 4 ModuleInfos at +0x2E4/+0x2F0/+0x2FC/+0x308 via rowed ModuleInfo::setCopiedFromDefault 0x0033B18A.
class ModuleInfo
{
public:
	void setCopiedFromDefault(bool copied);
private:
	void *m_begin;
	void *m_end;
	void *m_storage;
};

class ThingTemplate
{
public:
	void setCopiedFromDefault();
private:
	char m_pad0[0x2E4];
	ModuleInfo m_behaviorModuleInfo; // +0x2E4
	ModuleInfo m_drawModuleInfo; // +0x2F0
	ModuleInfo m_clientUpdateModuleInfo; // +0x2FC
	ModuleInfo m_extraModuleInfo; // +0x308 measured retail fourth slot name unproven
	char m_pad314[0x5E9 - 0x314];
	bool m_armorCopiedFromDefault; // +0x5E9
	bool m_weaponsCopiedFromDefault; // +0x5EA
};

void ThingTemplate::setCopiedFromDefault()
{
	m_armorCopiedFromDefault = true;
	m_weaponsCopiedFromDefault = true;
	m_behaviorModuleInfo.setCopiedFromDefault(true);
	m_drawModuleInfo.setCopiedFromDefault(true);
	m_clientUpdateModuleInfo.setCopiedFromDefault(true);
	m_extraModuleInfo.setCopiedFromDefault(true);
}

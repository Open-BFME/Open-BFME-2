// cl: /O1 /DNDEBUG /MD
//
// ArmorUpgrade::upgradeImplementation, retail 0x004B34B5 (192 bytes): slot 10
// of the +0x10 UpgradeMux vtable 0x00C57058 that the matched
// ??1ArmorUpgrade@@MAE@XZ (0x004B33FD) installs.
// Donor: BFME1 game/GameEngine/Source/GameLogic/Object/Upgrade/
// ArmorUpgradeUpgradeImplementation.cpp (open-bfme-1 068db38bb4): same module
// data fields (kill/ignore flags and the armor set flag, BFME1 +0x70/+0x71/
// +0x74, BFME2 +0x118/+0x119/+0x11C), the body module armor-set-flag call and
// the model condition looked up from the armor-set table.
// BFME2 deltas (target evidence): the UpgradeModule condition apply 0x004CE4A0
// runs right after the checks (BFME1 called its base helper last); the body
// module is Object+0x254 with set/clear at vslots 12/13 (the ZH order: a kill
// upgrade clears the flag and its condition, otherwise both are set); the
// condition table is the int array at VA 0x00DCC7C8 indexed by the armor set
// flag; the condition words start at Object+0x10C with notifier 0x0028AE6D.
// ArmorUpgrade::upgradeRemovalImplementation, retail 0x004B3575 (184 bytes),
// slot 8 of the same vtable: the reversal with the same checks (no body module
// still reaches the end), the flag and condition operations swapped, then the
// UpgradeModule condition removal 0x004CE4A8 (tail jump). The slot name is the
// BFME1 one (GarrisonUpgradeRemovalImplementation.cpp: upgradeRemovalImplementation
// directly before setUpgradeExecuted, which is BFME2 slot 9, the rowed bool
// setter UpgradeMux::rva00452354).
enum ArmorSetType
{
	ARMORSET_NONE = 0
};
template <int N> class ArmorUpgradeBodySlots : public ArmorUpgradeBodySlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class ArmorUpgradeBodySlots<0>
{
};
// BodyModuleInterface (Object +0x254): slots 12/13 are the armor set flag
// setter and clearer (the Zero Hour order).
class BodyModuleInterface : public ArmorUpgradeBodySlots<12>
{
public:
	virtual void setArmorSetFlag(ArmorSetType ast) = 0;
	virtual void clearArmorSetFlag(ArmorSetType ast) = 0;
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	BodyModuleInterface *getBodyModule() const { return m_body; }
	__forceinline void setModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(unsigned int mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
	unsigned char m_pad158[0x254 - 0x158];
	BodyModuleInterface *m_body; // +0x254
};
extern const unsigned int g_00DCC7C8[];
class ArmorUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	bool m_killArmorUpgrade; // +0x118
	bool m_ignoreArmorUpgrade; // +0x119
	ArmorSetType m_armorSetFlag; // +0x11C
};
class ModuleData;
class Rva00406F9C;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
template <int N> class ArmorUpgradeMuxSlots : public ArmorUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class ArmorUpgradeMuxSlots<0>
{
};
// UpgradeMux interface at +0x10: slots 0..7 placeholders, slot 8 is
// upgradeRemovalImplementation, slot 10 is upgradeImplementation.
class UpgradeMuxIface : public ArmorUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void slot09() = 0;
	virtual void upgradeImplementation() = 0;
};
class UpgradeModule : public BehaviorModule, public UpgradeModuleInterface, public UpgradeMuxIface
{
public:
	void rva004CE4A0();
	void rva004CE4A8();
};
class ArmorUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};
void ArmorUpgrade::upgradeImplementation()
{
	Object *object = m_object;
	if (!object)
		return;
	const ArmorUpgradeModuleData *data = (const ArmorUpgradeModuleData *)m_moduleData;
	if (!data || data->m_ignoreArmorUpgrade)
		return;
	rva004CE4A0();
	BodyModuleInterface *body = object->getBodyModule();
	if (!body)
		return;
	if (data->m_killArmorUpgrade)
	{
		body->clearArmorSetFlag(data->m_armorSetFlag);
		object->clearModelConditionState(g_00DCC7C8[data->m_armorSetFlag]);
	}
	else
	{
		body->setArmorSetFlag(data->m_armorSetFlag);
		object->setModelConditionState(g_00DCC7C8[data->m_armorSetFlag]);
	}
}
void ArmorUpgrade::upgradeRemovalImplementation()
{
	Object *object = m_object;
	if (!object)
		return;
	const ArmorUpgradeModuleData *data = (const ArmorUpgradeModuleData *)m_moduleData;
	if (!data || data->m_ignoreArmorUpgrade)
		return;
	BodyModuleInterface *body = object->getBodyModule();
	if (body)
	{
		if (!data->m_killArmorUpgrade)
		{
			body->clearArmorSetFlag(data->m_armorSetFlag);
			object->clearModelConditionState(g_00DCC7C8[data->m_armorSetFlag]);
		}
		else
		{
			body->setArmorSetFlag(data->m_armorSetFlag);
			object->setModelConditionState(g_00DCC7C8[data->m_armorSetFlag]);
		}
	}
	rva004CE4A8();
}

// cl: /O1 /DNDEBUG /MD
//
// StatusBitsUpgrade::upgradeImplementation and upgradeRemovalImplementation,
// retail 0x004B49AD and 0x004B49E2 (53 bytes each). The BFME1 donor confirms
// the two inverse StatusToSet/StatusToClear operations. BFME2 target evidence
// supplies the ModuleData offsets (+0x118 and +0x128, from the matched
// StatusBitsUpgrade parse table at 0x004B493E and module-data constructor),
// the Object mask setter at 0x0028CDEB, and the apply/remove wrappers at
// 0x004CE4A0/0x004CE4A8. The module's +0x10 UpgradeMux view gives these
// implementations their negative offsets to ModuleData and Object.

class Rva00346BC0
{
	public:
	unsigned int m_words[4];
};

class Object
{
public:
	void rva0028CDEB(const Rva00346BC0 &mask, bool set);
};

class ModuleData;
class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	Object *getObject() const { return m_object; }
};

class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};

template <int N> class StatusBitsUpgradeMuxSlots : public StatusBitsUpgradeMuxSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};

template <> class StatusBitsUpgradeMuxSlots<0>
{
};

class UpgradeMuxIface : public StatusBitsUpgradeMuxSlots<8>
{
protected:
	virtual void upgradeRemovalImplementation() = 0;
	virtual void setUpgradeExecuted(bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};

class UpgradeModule : public ObjectModuleBase,
	public UpgradeModuleInterface,
	public UpgradeMuxIface
{
public:
	void rva004CE4A0();
	void rva004CE4A8();
};

class StatusBitsUpgradeModuleData
{
public:
	unsigned char m_pad[0x118];
	Rva00346BC0 m_statusToSet;
	Rva00346BC0 m_statusToClear;
};

class StatusBitsUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeRemovalImplementation();
	virtual void upgradeImplementation();
};

void StatusBitsUpgrade::upgradeImplementation()
{
	Object *object = getObject();
	const StatusBitsUpgradeModuleData *data =
		(const StatusBitsUpgradeModuleData *)m_moduleData;
	object->rva0028CDEB(data->m_statusToSet, true);
	data = (const StatusBitsUpgradeModuleData *)m_moduleData;
	object->rva0028CDEB(data->m_statusToClear, false);
	rva004CE4A0();
}

void StatusBitsUpgrade::upgradeRemovalImplementation()
{
	Object *object = getObject();
	const StatusBitsUpgradeModuleData *data =
		(const StatusBitsUpgradeModuleData *)m_moduleData;
	object->rva0028CDEB(data->m_statusToSet, false);
	data = (const StatusBitsUpgradeModuleData *)m_moduleData;
	object->rva0028CDEB(data->m_statusToClear, true);
	rva004CE4A8();
}

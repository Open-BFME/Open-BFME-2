// Shared declaration for the existing xfer and reaction consumers.
// The rowed constructor supplies the UpdateModule base and secondary interface.
#pragma once

class Thing;
class ModuleData;
class Object;
class Xfer;

class ClickReactionBehaviorIface
{
public:
	virtual void slot0();
	virtual void rva004596F9();
};

class PB_DeepBase
{
public:
	virtual ~PB_DeepBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class PB_Iface1
{
public:
	virtual void slot();
};

class PB_Iface2
{
public:
	virtual void slot();
};

class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
	UpdateModule(Thing *, const ModuleData *);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);
private:
	unsigned int m_f14;
	int m_f18;
	int m_f1c;
};

enum NameKeyType
{
	NK_UNKNOWN = 0
};

class ClickReactionBehavior : public UpdateModule, public ClickReactionBehaviorIface
{
public:
	ClickReactionBehavior(Thing *, const ModuleData *);
	virtual void slot0();
	virtual void rva004596F9();
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_clicks; // +0x24
	int m_cooldown; // +0x28
public:
	virtual NameKeyType getModuleNameKey() const;
};

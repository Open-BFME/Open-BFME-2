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

#include "../../../../Include/GameLogic/Module/UpdateModule.h"

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

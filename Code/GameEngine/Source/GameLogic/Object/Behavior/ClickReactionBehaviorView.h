// Shared declaration for the existing xfer and reaction consumers.
// The rowed constructor supplies the UpdateModule base and secondary interface.
#pragma once

class Thing;
class ModuleData;
class Object;
class Xfer;

// Keep the constructor view's existing slot binding. The reaction operation is
// an abstract interface contract, implemented by the rowed leaf override; a
// second leaf slot0 would instead invent another primary-table entry. This
// remains a partial interface view, not a recovered complete vftable.
class ClickReactionBehaviorIface
{
public:
	virtual void slot();
	virtual void rva004596F9() = 0;
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
	virtual void rva004596F9();
protected:
	virtual void xfer(Xfer *xfer);
private:
	int m_clicks; // +0x24
	int m_cooldown; // +0x28
public:
	virtual NameKeyType getModuleNameKey() const;
public:
	// BehaviorModuleInterface table 0x00C411A0 (+0x0C) slot 33: retail 0x004543A9, the +0x0C
	// receiver converted to the +0x20 interface (the null-preserving cast retail folds).
	virtual void *slot33();
};

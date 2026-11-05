// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: TransportAIUpdate module ctor.
// Out-of-line base MI, then five most-derived vtbls at
// +0/+0xC/+0x10/+0x20/+0x24.

class Thing;
class ModuleData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
#include "../../../../../Include/GameLogic/Module/BehaviorModule.h"


class TransportAIUpdateIface2
{
public:
	virtual void transportAIUpdateIface2Anchor();

private:
	unsigned char m_pad[0xC];
};

class TransportAIUpdateIface3
{
public:
	virtual void transportAIUpdateIface3Anchor();
};

class TransportAIUpdateIface4
{
public:
	virtual void transportAIUpdateIface4Anchor();
};

class AIUpdateInterface : public BehaviorModule, public TransportAIUpdateIface2, public TransportAIUpdateIface3, public TransportAIUpdateIface4
{
public:
	AIUpdateInterface(Thing *thing, const ModuleData *moduleData);
protected:
	virtual ~AIUpdateInterface();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TransportAIUpdate.h
class TransportAIUpdate : public AIUpdateInterface
{
public:
	TransportAIUpdate(Thing *thing, const ModuleData *moduleData);
public:
	virtual ~TransportAIUpdate();
protected:
	// retail slot 3: the rowed ?xfer@TransportAIUpdate@@MAEXPAVXfer@@@Z
	virtual void xfer(Xfer *xfer);
public:
	// retail slot 4: the rowed ?getModuleNameKey@TransportAIUpdate@@UBE?AW4NameKeyType@@XZ
	virtual NameKeyType getModuleNameKey() const;
};

// ??0TransportAIUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
TransportAIUpdate::TransportAIUpdate(Thing *thing, const ModuleData *moduleData)
	: AIUpdateInterface(thing, moduleData)
{
}


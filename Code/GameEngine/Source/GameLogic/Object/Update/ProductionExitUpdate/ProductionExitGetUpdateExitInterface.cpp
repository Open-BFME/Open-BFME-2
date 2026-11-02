// cl: /O1 /DNDEBUG /MD
//
// getUpdateExitInterface overrides of QueueProductionExitUpdate and
// SpawnPointProductionExitUpdate: slot 20 (+0x50) of the interface vtable
// both constructors install at +0x0C (folded VA 0x00C4B1F0, ctors 0x4A010E
// and 0x4A3C1B) holds 0x004543A9, which takes the +0x0C subobject and
// returns the ExitInterface subobject at +0x20 (null-preserving). Zero
// Hour defines the override inline as `return this;`. Both fold onto the
// one 13-byte body. The views give only the subobject offsets.

#include "../../../../../Include/GameLogic/Module/ExitInterface.h"

class BehaviorModuleInterface
{
public:
	virtual ExitInterface *getUpdateExitInterface();
};

class ProductionExitModuleHead
{
public:
	virtual void moduleHeadAnchor();
protected:
	void *m_04;
	void *m_08;
};

class ProductionExitUpdateModuleTail
{
public:
	virtual void updateTailAnchor();
protected:
	int m_14[3];
};

class QueueProductionExitUpdate : public ProductionExitModuleHead, public BehaviorModuleInterface,
	public ProductionExitUpdateModuleTail, public ExitInterface
{
public:
	virtual ExitInterface *getUpdateExitInterface();
};

class SpawnPointProductionExitUpdate : public ProductionExitModuleHead, public BehaviorModuleInterface,
	public ProductionExitUpdateModuleTail, public ExitInterface
{
public:
	virtual ExitInterface *getUpdateExitInterface();
};

ExitInterface *QueueProductionExitUpdate::getUpdateExitInterface()
{
	return this;
}

ExitInterface *SpawnPointProductionExitUpdate::getUpdateExitInterface()
{
	return this;
}

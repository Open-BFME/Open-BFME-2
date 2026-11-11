// cl: /O1 /MD
#include "../../Include/GameLogic/PartitionData.h"
class PartitionManager
{
public:
	void rva00625330(void *p);
};
class Rva009A36F0Param;
class Rva00758240
{
public:
	void rva00758240(Rva009A36F0Param *p);
};
struct Rva00287C21Other
{
	unsigned char m_pad[0x49C];
	int m_49C;
};
#include "../../Include/GameLogic/FireLogicSystem.h"
class Object;
// Row spellings: 0x00333F37 is LuaDrawableState::rva00333F37(Object *),
// 0x002A8F56 is Rva002A8F24::UnRegister(Object *).
#include "../../Include/GameLogic/LuaDrawableState.h"
#include "../../Include/GameLogic/Rva002A8F24.h"
// Bind to the existing data-ledger owner; keep the retail access view local.
class PartitionManager;
extern PartitionManager *ThePartitionManager;
// Bind to the existing data-ledger owner; keep the retail access view local.
class CollisionManager;
extern CollisionManager *TheCollisionManager;
// Bind to the existing data-ledger owner; keep the retail access view local.
class Rva002872BA;
extern Rva002872BA *TheTriggerManager;
// Bind to the existing data-ledger owner; keep the retail access view local.
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;
// Bind to the existing data-ledger owner; keep the retail access view local.
class Rva002A8F24;
extern Rva002A8F24 *TheSkirmishAIManager;
// 0x0028BAC0 is an Object member: Object::~Object and the Object script-status
// setter call it on this, every other retail caller passes an Object pointer
// (TunnelTracker post-process, doTransferTeamToPlayer members and hordes), and
// it unregisters this from the partition, trigger, Lua and AI-player managers.
// Formerly rowed as Rva0028BAC0Host::rva0028BAC0; the method name stays
// address-derived.
class Object
{
public:
	void rva0028BAC0();
private:
	unsigned char m_pad[0x6C];
	unsigned char m_6C;
	unsigned char m_pad70[0x70 - 0x6D];
	unsigned char m_70;
	unsigned char m_pad454[0x454 - 0x71];
	unsigned char m_454;
	unsigned char m_pad49C[0x49C - 0x455];
	int m_49C;
	unsigned char m_pad4C4[0x4C4 - 0x4A0];
	PartitionData *m_4C4;
	int m_4C8;
	int m_4CC;
};
// ?rva0028BAC0@Object@@QAEXXZ
void Object::rva0028BAC0()
{
	if (m_4C4 != 0)
		m_4C4->makeDirty();
	if (m_4C8 != 0)
		((PartitionManager *)ThePartitionManager)->rva00625330(&m_6C);
	if (m_4CC != 0)
		((Rva00758240 *)TheCollisionManager)->rva00758240((Rva009A36F0Param*)&m_70);
	if (m_49C >= 0)
	{
		if (((FireLogicSystem *)TheTriggerManager) != 0)
			((FireLogicSystem *)TheTriggerManager)->UnregisterObject((Rva00287C21Other *)this);
	}
	if (((LuaDrawableState *)TheLuaScriptEngine) != 0)
		((LuaDrawableState *)TheLuaScriptEngine)->rva00333F37(this);
	if (((Rva002A8F24 *)TheSkirmishAIManager) != 0)
		((Rva002A8F24 *)TheSkirmishAIManager)->UnRegister(this);
	m_454 = 0;
}

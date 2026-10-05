// cl: /O1 /DNDEBUG /MD
//
// ?update@CritterEmitterUpdate@@UAE?AW4UpdateSleepTime@@XZ, retail
// 0x004C8DE2, 96 bytes. Identity: slot 0 of the vtable 0x00C5E8DC that the
// matched CritterEmitterUpdate ctor 0x004C8D86 and dtor 0x004C8D1B install at
// +0x10 (the UpdateModuleInterface base), i.e. update(); compiled with that
// subobject this, hence m_object at [this-8] and m_moduleData at [this-0xC].
// The body was first rowed as ?rva004C8DE2@HordeDispatchSpecialPower@@MAEHXZ
// (slot 20 of 0x00C5E88C) from an over-long candidate vtable that ran on into
// CritterEmitterUpdate's; see reverse/deleted_rows.csv.
// The two bools at +0x24/+0x25 are the ones the matched xfer 0x004C8E42 saves
// and the ctor clears; +0x24 is also onCollide's once-only flag. Returns the
// module data's +0x20 sleep value on the set path, else UPDATE_SLEEP_NONE.
// Callees 0x00758230/0x00758240 are reached through the global at 0x00DFE754
// (rowed via Rva00758210Thunks.cpp). Recipe: ternary +0x70 via neg-sbb-and
// under /O1 with xor-inc for return 1.

struct Rva009A29A0Window;
class Rva00758230
{
public:
	void rva00758230(Rva009A29A0Window *window);
};

class Rva009A36F0Param;
class Rva00758240
{
public:
	void rva00758240(Rva009A36F0Param *param);
};

// g_Va00DFE754: VA 0x00dfe754 (.data/bss); retail zero-filled.
void *g_Va00DFE754;

#define TheThunk230 ((Rva00758230 *)g_Va00DFE754)
#define TheThunk240 ((Rva00758240 *)g_Va00DFE754)

class Object;
class ModuleData;

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class CritterEmitterUpdateIface20
{
public:
	virtual void iface20Anchor();
};
class CritterEmitterUpdate : public UpdateModule, public CritterEmitterUpdateIface20
{
public:
	virtual UpdateSleepTime update();
private:
	bool m_24;
	bool m_25;
};

UpdateSleepTime CritterEmitterUpdate::update()
{
	if (m_24)
	{
		Rva00758240 *mgr = TheThunk240;
		if (mgr)
		{
			char *obj = (char *)m_object;
			char *arg = obj ? obj + 0x70 : 0;
			mgr->rva00758240((Rva009A36F0Param *)arg);
		}
		const char *d = (const char *)m_moduleData;
		m_24 = false;
		m_25 = false;
		return *(const UpdateSleepTime *)(d + 0x20);
	}
	if (m_25)
		return UPDATE_SLEEP_NONE;
	Rva00758230 *mgr = TheThunk230;
	if (!mgr)
		return UPDATE_SLEEP_NONE;
	char *obj = (char *)m_object;
	char *arg = obj ? obj + 0x70 : 0;
	mgr->rva00758230((Rva009A29A0Window *)arg);
	return UPDATE_SLEEP_NONE;
}

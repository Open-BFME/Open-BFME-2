// cl: /O1 /DNDEBUG /MD
//
// PickupStuffUpdate::update, retail 0x0049212B (78 bytes): slot 0 of the
// class's +0x10 update-module interface table 0x00C4DD9C, so `this` is that
// subobject (module data at -0x0C, Object at -0x08). Sleeps forever for an
// Object without an AI, or, when the module data's +0x08 flag is set, for one
// whose controlling Player has no record in the g_00DFEEF8 registry
// (0x002A8AB1). Otherwise, with the flag at +0x20 set it runs 0x00491EE6
// (rowed under the address class Rva00491DD3 from this caller; pinned for
// PickupStuffUpdate), else 0x004920B5 (pinned by address), and stays awake.
enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};
class Player;
class AIUpdateInterface;
class Object
{
public:
	Player *getControllingPlayer() const;
	AIUpdateInterface *getAI() const { return m_ai; }
private:
	unsigned char m_pad000[0x258];
	AIUpdateInterface *m_ai;	// +0x258
};
struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *owner);
};
extern Rva002A8F24 *g_00DFEEF8;
struct PickupStuffUpdateModuleData
{
	unsigned char m_pad00[0x08];
	bool m_08;			// +0x08
};
class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};
class UpdateModule : public ModuleBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned char m_pad14[0x20 - 0x14];
};
class PickupStuffUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void rva00491EE6();
	void rva004920B5();
private:
	bool m_20;			// +0x20
};
UpdateSleepTime PickupStuffUpdate::update()
{
	Object *obj = m_object;
	if (obj->getAI())
	{
		const PickupStuffUpdateModuleData *data = (const PickupStuffUpdateModuleData *)m_moduleData;
		if (!data->m_08 || g_00DFEEF8->rva002A8AB1(obj->getControllingPlayer()))
		{
			if (m_20)
				rva00491EE6();
			else
				rva004920B5();
			return UPDATE_SLEEP_NONE;
		}
	}
	return UPDATE_SLEEP_FOREVER;
}

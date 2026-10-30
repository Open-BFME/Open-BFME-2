// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: EntEnragedUpdate constructor with the retail module layout.

class Thing;
class Object;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
private:
	unsigned char m_gap00[8];
public:
	unsigned int m_initialValue;
};

enum UpdateSleepTime { UPDATE_SLEEP_FOREVER = 0x3fffffff };

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class BodyModuleInterface;

// Slot 0 of the shared BehaviorModuleInterface vftable 0x007EFF90 this ctor
// stores at +0xC is the folded xor eax,eax/ret at 0x000D43D0: ZH's
// BehaviorModule::getBody returning NULL. The inline body folds onto it.
class BehaviorModuleInterface
{
public:
	virtual BodyModuleInterface *getBody() { return 0; }
};
class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public BehaviorModuleInterface,
	public UpdateModuleInterface
{
public:
	// Defined once, out of line, in UpdateModuleCtor.cpp (retail 0x00253390): derived
	// ctors call it, and a copy here would offer the link a second, non-retail body.
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();

private:
	unsigned int m_field14;
	int m_field18;
	int m_field1C;
};

class EntEnragedUpdate : public UpdateModule
{
public:
	EntEnragedUpdate(Thing *, const ModuleData *);
	virtual ~EntEnragedUpdate();
	// Rowed in EntEnragedUpdateUpdate.cpp: slot 0 of retail's UpdateModuleInterface table 0x00C5693C.
	virtual UpdateSleepTime update();

private:
	int m_value;
	unsigned int m_sleepTime;
	unsigned int m_field28;
	bool m_field2C;
	bool m_field2D;
	bool m_field2E;
	bool m_field2F;
	bool m_field30;
};

// ??0EntEnragedUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
EntEnragedUpdate::EntEnragedUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const ModuleData *data = m_moduleData;
	m_value = 0;
	m_value += GetGameLogicRandomValue(0, data->m_initialValue,
		(char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\EntEnraged.cpp", 0x4c);
	m_field2C = false;
	m_field2E = false;
	m_field2F = false;
	m_field2D = false;
	m_field28 = 0;
	m_field30 = false;
	m_sleepTime = 0x3fffffff;
}

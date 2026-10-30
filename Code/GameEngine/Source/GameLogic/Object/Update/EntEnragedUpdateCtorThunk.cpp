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

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

enum NameKeyType { NK_UNKNOWN = 0 };

class Thing;
class Object;
class ModuleData;
class BodyModuleInterface;
class Xfer;

class PB_DeepBase
{
public:
	PB_DeepBase(Thing *, const ModuleData *);
	virtual ~PB_DeepBase();
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

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
class UpdateModule : public PB_DeepBase, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	// Defined once, out of line, in UpdateModuleCtor.cpp (retail 0x00253390): derived
	// ctors call it, and a copy here would offer the link a second, non-retail body.
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	void xfer(Xfer *xfer);

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
	virtual NameKeyType getModuleNameKey() const;
	virtual void rva004B23C5(Xfer *xfer); // slot 3 of 0x00C56948
	// Rowed in EntEnragedUpdateUpdate.cpp: slot 0 of retail's UpdateModuleInterface table 0x00C5693C.
	virtual UpdateSleepTime update();
	bool rva004B25C9();
	bool rva004B266D();

private:
	unsigned int m_20;
	unsigned int m_24;
	unsigned int m_28;
	bool m_2C;
	bool m_2D;
	bool m_2E;
	bool m_2F;
	bool m_30;
};

// ??0EntEnragedUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
EntEnragedUpdate::EntEnragedUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
{
	const ModuleData *data = m_moduleData;
	m_20 = 0;
	m_20 += GetGameLogicRandomValue(0, data->m_initialValue,
		(char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\EntEnraged.cpp", 0x4c);
	m_2C = false;
	m_2E = false;
	m_2F = false;
	m_2D = false;
	m_28 = 0;
	m_30 = false;
	m_24 = 0x3fffffff;
}

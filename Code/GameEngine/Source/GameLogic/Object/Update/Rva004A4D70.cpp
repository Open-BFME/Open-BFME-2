// cl: /DNDEBUG /MD /GX
// ?rva004A4D70@Rva004A4D70@@QAEXXZ, retail 0x004A4D70, 40 bytes.
// Evidence: same +0x24/+0x28/+0x2c int zeros and +0x30/+0x34/+0x38 float zeros plus setWakeFrame(m_object 1) as StructureCollapseUpdate ctor at 0x004A42E4; setWakeFrame row 0x0044DF71; neighbours 0x004A4D54 and 0x004A4DBE.
// UpdateModule layout with m_object at +8.

class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class Thing;
class ModuleData;

class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime t);

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class Rva004A4D70 : public UpdateModule
{
public:
	void rva004A4D70();

private:
	const void *m_secondary20;
	unsigned int m_24;
	unsigned int m_28;
	unsigned int m_2C;
	float m_30;
	float m_34;
	float m_38;
};

void Rva004A4D70::rva004A4D70()
{
	int zero = 0;
	float fzero = 0.0f;
	m_24 = zero;
	m_2C = zero;
	m_30 = fzero;
	m_28 = zero;
	m_34 = fzero;
	m_38 = fzero;
	setWakeFrame(m_object, UPDATE_SLEEP_NONE);
}

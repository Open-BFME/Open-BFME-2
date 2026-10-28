// cl: /DNDEBUG /MD /GX
// ?rva004A4D70@RubbleRiseUpdate@@QAEXXZ, retail 0x004A4D70, 40 bytes.
// Evidence: same +0x24/+0x28/+0x2c int zeros and +0x30/+0x34/+0x38 float zeros plus setWakeFrame(m_object 1) as StructureCollapseUpdate ctor at 0x004A42E4; setWakeFrame row 0x0044DF71; neighbours 0x004A4D54 and 0x004A4DBE.
// UpdateModule layout with m_object at +8.

class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

enum RubbleRiseStateType
{
	RISESTATE_WAITING = 0,
	RISESTATE_RISING,
	RISESTATE_DONE
};

class Thing;
class ModuleData;

class UpdateModule
{
protected:
	void setWakeFrame(Object *obj, UpdateSleepTime t);
	Object *getObject() const { return m_object; }

	const void *m_vtable;
	const ModuleData *m_moduleData;
	Object *m_object;
	const void *m_secondary0C;
	const void *m_secondary10;
	unsigned int m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_reserved1C;
};

class RubbleRiseUpdate : public UpdateModule
{
public:
	void rva004A4D70();

private:
	const void *m_secondary20;
	unsigned int m_unused24; // +0x24
	unsigned int m_nextBurstFrame; // +0x28
	RubbleRiseStateType m_riseState; // +0x2C
	float m_riseVelocity; // +0x30
	float m_currentHeight; // +0x34
	float m_rubbleHeight; // +0x38
};

void RubbleRiseUpdate::rva004A4D70()
{
	int zero = 0;
	float fzero = 0.0f;
	m_unused24 = zero;
	m_riseState = (RubbleRiseStateType)zero;
	m_riseVelocity = fzero;
	m_nextBurstFrame = zero;
	m_currentHeight = fzero;
	m_rubbleHeight = fzero;
	setWakeFrame(getObject(), UPDATE_SLEEP_NONE);
}

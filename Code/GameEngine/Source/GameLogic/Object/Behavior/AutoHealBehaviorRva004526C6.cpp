// cl: /O1 /MD /DNDEBUG /arch:SSE
// ?rva004526C6@AutoHealBehavior@@QAEXPAVObject@@_N@Z @0x004526C6 207B via AutoHeal pulse with nonStackable gate plus attribute bonus plus FX flag
// Evidence: prev onDamage 0x0045266B same TU layout +0x04/+0x08/+0x2C/+0x30; callees rowed rva0028C149 0x13 bonus attemptHealing rva0028FEA7 doFXObj; TheGameLogic frame +0x40; ModuleData 0x11C/0x120/0x128/0x150/0x154 from ModuleDataCtor 0x160.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

class Object;
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class Body
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual UnsignedInt v17();
};

class Object
{
public:
	Bool rva0028C149(Int attribute, Real *value, Int arg);
	void attemptHealing(Real amount, const Object *source);
	Bool rva0028FEA7(Real amount, const Object *source, UnsignedInt extra);

	unsigned char m_pad00[0x254];
	Body *m_body;
};

class GameLogic
{
public:
	char m_pad00[0x40];
	UnsignedInt m_frame;
};
extern GameLogic *TheGameLogic;

struct AutoHealBehaviorModuleData
{
	unsigned char m_pad00[0x11C];
	Int m_healingAmount;
	UnsignedInt m_healingDelay;
	UnsignedInt m_startHealingDelay;
	Int m_radius;
	unsigned char m_pad12C[0x150 - 0x12C];
	const FXList *m_unitHealPulseFX;
	Bool m_nonStackable;
};

class AutoHealBehavior
{
public:
	void rva004526C6(Object *obj, Bool flag);

private:
	void *m_vtable;
	const AutoHealBehaviorModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_pad0C[0x2C - 0x0C];
	UnsignedInt m_soonestHealFrame;
	Bool m_stopped;
};

void AutoHealBehavior::rva004526C6(Object *obj, Bool flag)
{
	if (m_stopped)
		return;
	const AutoHealBehaviorModuleData *data = m_moduleData;
	if (data->m_nonStackable)
	{
		Body *body = obj->m_body;
		if (body)
		{
			UnsignedInt frame = TheGameLogic->m_frame;
			if (body->v17() + data->m_healingDelay > frame)
				return;
		}
	}
	Real bonus;
	Int zero = 0;
	m_object->rva0028C149(0x13, &bonus, zero);
	Int truncated = (Int)((Real)data->m_healingAmount + bonus);
	if (data->m_radius == zero)
		obj->attemptHealing((Real)truncated, m_object);
	else
		obj->rva0028FEA7((Real)truncated, m_object, data->m_healingDelay);
	if (flag)
		FXList::doFXObj(data->m_unitHealPulseFX, obj, (const Object *)zero);
	m_soonestHealFrame = TheGameLogic->m_frame + data->m_healingDelay;
}

// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?upgradeImplementation@Rva004B63BD@@MAEXXZ, retail 0x004B6532 (115B): the
// UpgradeMux-side slot before getUpgradeActivationMasks in the vtable of the
// upgrade module whose destructor is rowed as Rva004B63BD
// (FireWeaponWhenDeadBehaviorDerived.cpp), so `this` is the module +0x10
// (module data at -0x0C, object at -0x08). When the upgrade fires it sets the
// module data's model-condition flags at +0x164 (0x001E42F2), clears those at
// +0x118 (0x001E431E), and, given a special condition type (+0x1B0, not -1)
// with a positive duration in seconds (+0x1B4), sets it for that many logic
// frames (frame rate g_Va00DBA4E4). Own unit: the destructor unit keeps every
// class down to its destructor so its emitted vtables stay alike; this view
// defines no constructor or destructor and emits none.
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

class ModelConditionFlags
{
public:
	Bool rva000B3EB3() const;	// any bit set
private:
	UnsignedInt m_bits[19];
};

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};

struct Rva004B63BDModuleData
{
	unsigned char m_pad000[0x118];
	ModelConditionFlags m_conditionsToClear;	// +0x118
	ModelConditionFlags m_conditionsToSet;		// +0x164
	ModelConditionFlagType m_specialCondition;	// +0x1B0
	Real m_specialConditionSeconds;			// +0x1B4
};

class Object
{
public:
	void setSpecialModelConditionState(ModelConditionFlagType type, UnsignedInt frames);
};
class Rva001E42F2 { public: void rva001E42F2(const int *flags); };
class Rva001E431E { public: void rva001E431E(const int *flags); };

extern int g_Va00DBA4E4;	// logic frames per second

class Rva004B63BDPrimary
{
public:
	virtual void slot0();
protected:
	const Rva004B63BDModuleData *m_moduleData;	// +0x04
	Object *m_object;				// +0x08
};
class Rva004B63BDInterfaceC
{
public:
	virtual void slot0();
};
class Rva004B63BDUpgradeMux
{
protected:
	virtual void upgradeImplementation() = 0;
};

class Rva004B63BD : public Rva004B63BDPrimary, public Rva004B63BDInterfaceC, public Rva004B63BDUpgradeMux
{
protected:
	virtual void upgradeImplementation();
};

void Rva004B63BD::upgradeImplementation()
{
	const Rva004B63BDModuleData *data = m_moduleData;
	Object *obj = m_object;
	if (data->m_conditionsToSet.rva000B3EB3())
		((Rva001E42F2 *)obj)->rva001E42F2((const int *)&data->m_conditionsToSet);
	if (data->m_conditionsToClear.rva000B3EB3())
		((Rva001E431E *)obj)->rva001E431E((const int *)&data->m_conditionsToClear);
	if (data->m_specialCondition != MODELCONDITION_INVALID && data->m_specialConditionSeconds > 0.0f)
		obj->setSpecialModelConditionState(data->m_specialCondition,
			(UnsignedInt)(g_Va00DBA4E4 * data->m_specialConditionSeconds));
}

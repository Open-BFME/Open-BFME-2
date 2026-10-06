// cl: /DNDEBUG /MD
//
// Retail 0x0044EE80 (74 bytes): SpecialAbilityUpdate::rva0044EE80, a
// non-virtual helper called with the module as this by the SpecialAbilityUpdate
// slot-22 base 0x004508B7 and by 0x00451FA2 (SpecialAbilityUpdate block). Name
// by address. Sets the model condition named by the module data +0x18 on the
// Object (directly, notifier as a tail jump) or times it through the matched
// Object::setSpecialModelConditionState 0x0028AEB2 when the +0x1C frames are
// non-zero. Object condition words at +0x10C, masked-word accessors.

enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
class ModelConditionFlags
{
public:
	unsigned int test(unsigned int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(unsigned int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
	void clear(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1U << (bit & 0x1f));
	}
private:
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	void setSpecialModelConditionState(ModelConditionFlagType mc, unsigned int frames);
	__forceinline void setModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) == 0)
		{
			m_modelConditionFlags.set(mc);
			rva0028AE6D();
		}
	}
	__forceinline void clearModelConditionState(ModelConditionFlagType mc)
	{
		if (m_modelConditionFlags.test(mc) != 0)
		{
			m_modelConditionFlags.clear(mc);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	ModelConditionFlags m_modelConditionFlags; // +0x10C
};
struct Rva004CE41ECondition
{
	ModelConditionFlagType m_type; // +0x00
	unsigned int m_frames; // +0x04
};
class SpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad[0x18];
	ModelConditionFlagType m_18; // +0x18
	unsigned int m_1C; // +0x1C
};
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class SpecialAbilityUpdate : public BehaviorModule
{
public:
	void rva0044EE80();
};
void SpecialAbilityUpdate::rva0044EE80()
{
	Object *object = m_object;
	const SpecialAbilityUpdateModuleData *data = (const SpecialAbilityUpdateModuleData *)m_moduleData;
	ModelConditionFlagType mc = data->m_18;
	if (mc == MODELCONDITION_INVALID)
		return;
	if (data->m_1C == 0)
		object->setModelConditionState(mc);
	else
		object->setSpecialModelConditionState(mc, data->m_1C);
}

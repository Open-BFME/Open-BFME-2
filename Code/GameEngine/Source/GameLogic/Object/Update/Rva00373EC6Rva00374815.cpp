// cl: /DNDEBUG /MD
//
// Rva00373EC6::rva00374815, retail 0x00374815 (168 bytes).
// Class: every caller (0x00370680, 0x00499C6C, 0x004A2D93) gets this from the
// matched Object::rva0028F4BC, whose result type is the placeholder class
// Rva00373EC6 (the module whose 0x00373EC6 predicate tests the masks at +0x48 and
// +0xC8). The masks, the adjacent StealthUpdate rows 0x003748BD/0x00374AE8 and
// the StealthUpdate pool key 0x00373CCA suggest StealthUpdate; that is an
// inference, so the placeholder name is kept.
// Body (target evidence): early out when module data +0x98 and +0xA0 are both
// zero. On the first activation (+0x31 clear, current frame past +0x28) it sets
// +0x20 to now plus data +0x90, clears +0x24, sets model condition 7*32+29 on
// the Object (word +0x128, notifier 0x0028AE6D on change), queues special model
// condition 0x104 for data +0x98 frames, disables the object (type 3) until
// +0x20, sets weapon set flag 0x1C and marks +0x31. Otherwise it queues special
// model condition 0x105 for data +0x9C frames and sets +0x24 to now plus +0x94.
enum ModelConditionFlagType
{
	MODELCONDITION_INVALID = -1
};
enum DisabledType
{
	DISABLED_DEFAULT = 0
};
enum WeaponSetType
{
	WEAPONSET_NONE = 0
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
	void setDisabledUntil(DisabledType type, unsigned int frame);
	void setWeaponSetFlag(WeaponSetType wst);
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
class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	unsigned int m_frame; // +0x40
};
extern GameLogic *TheGameLogic;
class Rva00373EC6ModuleData
{
public:
	unsigned char m_pad[0x90];
	unsigned int m_90; // +0x90
	unsigned int m_94; // +0x94
	unsigned int m_98; // +0x98
	unsigned int m_9C; // +0x9C
	unsigned int m_A0; // +0xA0
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
class Rva00373EC6 : public BehaviorModule
{
public:
	void rva00374815();
private:
	unsigned char m_pad0C[0x20 - 0x0C];
	unsigned int m_20; // +0x20
	unsigned int m_24; // +0x24
	unsigned int m_28; // +0x28
	unsigned char m_pad2C[0x31 - 0x2C];
	bool m_31; // +0x31
};
void Rva00373EC6::rva00374815()
{
	unsigned int now = TheGameLogic->getFrame();
	Object *object = m_object;
	const Rva00373EC6ModuleData *data = (const Rva00373EC6ModuleData *)m_moduleData;
	if (data->m_98 == 0 && data->m_A0 == 0)
		return;
	if (!m_31)
	{
		if (now < m_28)
			return;
		m_20 = data->m_90 + now;
		m_24 = 0;
		object->setModelConditionState((ModelConditionFlagType)(7 * 32 + 29));
		object->setSpecialModelConditionState((ModelConditionFlagType)0x104, data->m_98);
		m_object->setDisabledUntil((DisabledType)3, m_20);
		object->setWeaponSetFlag((WeaponSetType)0x1C);
		m_31 = true;
	}
	else
	{
		object->setSpecialModelConditionState((ModelConditionFlagType)0x105, data->m_9C);
		m_24 = data->m_94 + now;
	}
}

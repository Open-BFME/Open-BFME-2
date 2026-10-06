// cl: /DNDEBUG /MD
//
// UpgradeModule model-condition helpers, retail UpgradeModule.cpp block (after
// the matched UpgradeMux ctor 0x004CE2A3, upgradeMuxXfer 0x004CE397 and
// UpgradeModule::xfer 0x004CE3F9). The module has the ModuleData at +4, the
// Object at +8 and its UpgradeMux subobject at +0x10. Names by address.
// Retail 0x004CE41E (130 bytes): apply (true) or remove (false) the model
// condition named by the module data +0x108 {condition, frames} pair: timed
// through Object::setSpecialModelConditionState 0x0028AEB2 when frames > 0,
// else set directly; removal clears it (variable index, masked-word accessors,
// Object condition words at +0x10C). Retail reads both fields from the pair's
// address, hence the pair struct read through a reference.
// Retail 0x004CE4A0 / 0x004CE4A8 (8 bytes each): the apply / remove wrappers
// (8 and 7 direct callers).
// Retail 0x004CE4B0 (36 bytes): slot 3 of the UpgradeMux vtable at +0x10
// (inherited by FireWeaponWhenDeadBehavior and DynamicPortalBehaviour): when the
// matched placeholder base test 0x004CE342 accepts the mask, remove the
// condition and return true. The UpgradeMux subobject keeps that row's
// placeholder class name so the call is a plain this conversion.

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
class UpgradeModuleData
{
public:
	unsigned char m_pad[0x108];
	Rva004CE41ECondition m_108; // +0x108
};
class ModuleData;
class AsciiString;
namespace _STL
{
template <typename T> class allocator
{
};
template <typename T, typename A = allocator<T> > class vector
{
	unsigned char m_data[12];
public:
	void push_back(const T &value);
};
}
class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *rva0026EEA0(int key) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Rva00406F9C
{
public:
	bool rva00406F9C(const void *other);
	void rva004CE4D4(_STL::vector<AsciiString> *out);
	unsigned int m_data[32];
};

class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};
// The +0x10 UpgradeMux subobject; the matched placeholder row 0x004CE342 is
// its non-virtual base test, so the subobject keeps that row's class name.
class Rva004CE342
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual bool rva004CE4B0(Rva00406F9C *mask) = 0;
	bool rva004CE342(Rva00406F9C *mask);
};
class UpgradeModule : public BehaviorModule, public UpgradeModuleInterface, public Rva004CE342
{
public:
	void rva004CE41E(bool apply);
	void rva004CE4A0();
	void rva004CE4A8();
	virtual bool rva004CE4B0(Rva00406F9C *mask);
};
void UpgradeModule::rva004CE41E(bool apply)
{
	Object *object = m_object;
	const UpgradeModuleData *data = (const UpgradeModuleData *)m_moduleData;
	if (!object || !data)
		return;
	const Rva004CE41ECondition &cond = data->m_108;
	if (cond.m_type == MODELCONDITION_INVALID)
		return;
	if (apply)
	{
		if (cond.m_frames > 0)
			object->setSpecialModelConditionState(cond.m_type, cond.m_frames);
		else
			object->setModelConditionState(cond.m_type);
	}
	else
	{
		object->clearModelConditionState(cond.m_type);
	}
}
void UpgradeModule::rva004CE4A0()
{
	rva004CE41E(true);
}
void UpgradeModule::rva004CE4A8()
{
	rva004CE41E(false);
}
bool UpgradeModule::rva004CE4B0(Rva00406F9C *mask)
{
	if (rva004CE342(mask))
	{
		rva004CE41E(false);
		return true;
	}
	return false;
}

// Target evidence: this walks the 0x80-byte mask at this and tests all 0x400
// indices. Set bits pass through UpgradeCenter::rva0026EEA0 (0x0026EEA0),
// whose row returns the template selected by its mask index. The resulting
// template's AsciiString at +8 is appended through rowed STLport push_back
// 0x0002DBE6. Keep the containing method name address-derived.
void Rva00406F9C::rva004CE4D4(_STL::vector<AsciiString> *out)
{
	for (int i = 0; i < 0x400; ++i)
	{
		if ((m_data[(unsigned int)i >> 5] & (1U << (i & 0x1f))) != 0)
		{
			const UpgradeTemplate *upgrade = TheUpgradeCenter->rva0026EEA0(i);
			if (upgrade != 0)
				out->push_back(*(const AsciiString *)((const unsigned char *)upgrade + 8));
		}
	}
}

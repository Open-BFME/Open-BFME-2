// cl: /DNDEBUG /MD
//
// Retail 0x004ACE11 (133 bytes): RousingSpeechUpdate::rva004ACE11.
// Identity: slot 15 of the primary vtable 0x00C54FE8 that the matched
// RousingSpeechUpdate dtor installs; the class derives from
// SpecialAbilityUpdate, whose own slot 15 (0x00450D9A, pinned as
// SpecialAbilityUpdate::rva00450D9A) this override calls first, exactly like
// the matched GloriousChargeUpdate slot-15 override 0x004AD554. Name by
// address: the slot name is not established.
// Body: base call, set condition bit 6*32+15 on the Object, play the module
// data FXList at +0xD4 on it through the static FXList::doFXObj 0x000B2235,
// reset the +0x94 float and set the +0x98 float to the data +0xE0 value capped
// at +0xC8 when the +0xDC flag is set, else to +0xC8.
//
// Model-condition bits: the Object word array starts at +0x10C (see
// GloriousChargeUpdateRva004AD554.cpp); masked-word accessors in a free
// __forceinline helper call the pinned notifier 0x0028AE6D on a change.

class Drawable;
class Rva0010CConditionBits
{
public:
	unsigned int test(int bit) const
	{
		return m_words[bit >> 5] & (1U << (bit & 0x1f));
	}
	void set(int bit)
	{
		m_words[bit >> 5] |= 1U << (bit & 0x1f);
	}
private:
	unsigned int m_words[20];
};
class Object
{
public:
	void rva0028AE6D();
	unsigned char m_pad000[0x10C];
	Rva0010CConditionBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};
class Thing;
class ModuleData;
class BehaviorModule
{
public:
	virtual ~BehaviorModule();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};
class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};
class UpdateModuleInterface
{
public:
	virtual int update() = 0;
};
class UpdateModule : public BehaviorModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	unsigned int m_14;
	int m_18;
	int m_1C;
};
class SpecialAbilityUpdate : public UpdateModule
{
public:
	virtual void rva00450D9A();
};
class RousingSpeechUpdateModuleData
{
public:
	unsigned char m_pad[0xC8];
	float m_C8; // +0xC8
	unsigned char m_padCC[0xD4 - 0xCC];
	const FXList *m_D4; // +0xD4
	unsigned char m_padD8[0xDC - 0xD8];
	bool m_DC; // +0xDC
	float m_E0; // +0xE0
};
class RousingSpeechUpdate : public SpecialAbilityUpdate
{
public:
	virtual void rva004ACE11();
private:
	unsigned char m_pad20[0x94 - 0x20];
	float m_94; // +0x94
	float m_98; // +0x98
};
void RousingSpeechUpdate::rva004ACE11()
{
	SpecialAbilityUpdate::rva00450D9A();
	setModelConditionBit(m_object, 6 * 32 + 15);
	const RousingSpeechUpdateModuleData *data = (const RousingSpeechUpdateModuleData *)m_moduleData;
	if (data->m_D4)
		FXList::doFXObj(data->m_D4, m_object, 0);
	m_94 = 0.0f;
	if (data->m_DC)
	{
		m_98 = data->m_E0;
		if (m_98 > data->m_C8)
			m_98 = data->m_C8;
	}
	else
	{
		m_98 = data->m_C8;
	}
}

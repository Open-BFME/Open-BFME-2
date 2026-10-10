// cl: /DNDEBUG /MD
//
// Retail 0x0049283E (242 bytes): WeaponFireSpecialAbilityUpdate::startUnpacking,
// slot 22 of the primary vtable 0x00C4E090 that the matched
// WeaponFireSpecialAbilityUpdate dtor installs; it overrides the
// SpecialAbilityUpdate slot 22 (0x004508B7, pinned) and calls it first, like
// the matched Rva00492179/Rva00492402 overrides. Name by address.
// Body: unless the data flag +0xD0 is set while the +0x24 counter is non-zero,
// set the model condition picked by the data +0xCC value (1..3: 7*32+20..22,
// 4..6: 18*32+12..14; switch with literal cases, cl merges the masked-word
// tails per word); then, when the data flag +0xD9 is set and the +0x88 holder
// has a source with an FXList at +0xB8, play it through the matched static
// FXList::doFXPos at the Drawable position with its transform and the source
// +0x68 speed. The Drawable position getter 0x002763E6 is pinned as
// Drawable::getPosition, hence the cast of the Object's Drawable.
// Condition word array at Object+0x10C with masked-word accessors.

struct Coord3D;
class Matrix3D;
class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
public:
	const Coord3D *getPosition() const;
};
// 0x002763E6 is pinned under this name; it is called on the Object's Drawable.
class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
};
class Rva0010CBits
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
	unsigned int m_words[19];
};
class Object
{
public:
	void rva0028AE6D();
	Drawable *getDrawable() const;
	unsigned char m_pad000[0x10C];
	Rva0010CBits m_conditionBits; // +0x10C
};
static __forceinline void setModelConditionBit(Object *object, int bit)
{
	if (object->m_conditionBits.test(bit) == 0)
	{
		object->m_conditionBits.set(bit);
		object->rva0028AE6D();
	}
}
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
class SpecialPowerUpdateInterface
{
public:
	virtual void specialPowerUpdateAnchor();
};
class SpecialAbilityUpdate : public UpdateModule, public SpecialPowerUpdateInterface
{
public:
	virtual void startUnpacking();	// row 0x004508B7
protected:
	int m_24; // +0x24
	unsigned char m_pad28[0x88 - 0x28];
};
struct Rva0049283EFXSource
{
	unsigned char m_pad[0x68];
	float m_68; // +0x68
	unsigned char m_pad6C[0xB8 - 0x6C];
	const FXList *m_B8; // +0xB8
};
struct Rva0049283EHolder
{
	int m_00;
	const Rva0049283EFXSource *m_04; // +0x04
};
class WeaponFireSpecialAbilityUpdateModuleData
{
public:
	unsigned char m_pad[0xCC];
	int m_CC; // +0xCC
	bool m_D0; // +0xD0
	unsigned char m_padD1[0xD9 - 0xD1];
	bool m_D9; // +0xD9
};
class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual void startUnpacking();
private:
	const Rva0049283EHolder *m_88; // +0x88
};
void WeaponFireSpecialAbilityUpdate::startUnpacking()
{
	SpecialAbilityUpdate::startUnpacking();
	const WeaponFireSpecialAbilityUpdateModuleData *data = (const WeaponFireSpecialAbilityUpdateModuleData *)m_moduleData;
	Object *object = m_object;
	if (!data->m_D0 || m_24 == 0)
	{
		switch (data->m_CC)
		{
		case 1:
			setModelConditionBit(object, 7 * 32 + 20);
			break;
		case 2:
			setModelConditionBit(object, 7 * 32 + 21);
			break;
		case 3:
			setModelConditionBit(object, 7 * 32 + 22);
			break;
		case 4:
			setModelConditionBit(object, 18 * 32 + 12);
			break;
		case 5:
			setModelConditionBit(object, 18 * 32 + 13);
			break;
		case 6:
			setModelConditionBit(object, 18 * 32 + 14);
			break;
		}
	}
	if (data->m_D9 && m_88 && m_88->m_04)
	{
		const FXList *fx = m_88->m_04->m_B8;
		if (fx)
		{
			float speed = m_88->m_04->m_68;
			FXList::doFXPos(fx,
				((const Drawable *)object->getDrawable())->getPosition(),
				object->getDrawable()->getTransformMatrix(),
				speed,
				((const Drawable *)object->getDrawable())->getPosition());
		}
	}
}

// cl: /O1 /DNDEBUG /MD
//
// ?onExit@WeaponFireSpecialAbilityUpdate@@MAEX_N0@Z, retail 0x00492930, 161
// bytes: slot 13 of WeaponFireSpecialAbilityUpdate's primary vtable 0x00C4E090
// (ctors 0x0049257C, 0x00492736), over the SpecialAbilityUpdate slot-13 base
// onExit 0x004502CE (pinned; name donor-carried from BFME 1). After the base,
// the module data's +0xCC selector (1..6) names one model-condition bit to
// drop from the Object, 7*32+20..22 or 18*32+12..14; a bit that was set is
// cleared and the Object notified (0x0028AE6D).
class Object;

class Rva00492930Bits
{
public:
	unsigned int test(int bit) const { return m_words[bit >> 5] & (1U << (bit & 0x1f)); }
	void clear(int bit) { m_words[bit >> 5] &= ~(1U << (bit & 0x1f)); }
private:
	unsigned int m_words[19];
};

class Object
{
public:
	void rva0028AE6D();
	__forceinline void clearModelCondition(int bit)
	{
		if (m_conditionBits.test(bit))
		{
			m_conditionBits.clear(bit);
			rva0028AE6D();
		}
	}
private:
	unsigned char m_pad000[0x10C];
	Rva00492930Bits m_conditionBits; // +0x10C
};

struct WeaponFireSpecialAbilityUpdateModuleData
{
	unsigned char m_pad00[0xCC];
	int m_CC; // +0xCC
};

class WeaponFireSpecialAbilityUpdate;

class SpecialAbilityUpdate
{
public:
	virtual ~SpecialAbilityUpdate();
protected:
	const WeaponFireSpecialAbilityUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
private:
	void onExit(bool a, bool b);
	friend class WeaponFireSpecialAbilityUpdate;
};

class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
protected:
	virtual void onExit(bool a, bool b);
};

void WeaponFireSpecialAbilityUpdate::onExit(bool a, bool b)
{
	SpecialAbilityUpdate::onExit(a, b);
	Object *obj = m_object;
	switch (m_moduleData->m_CC)
	{
	case 1:
		obj->clearModelCondition(7 * 32 + 20);
		break;
	case 2:
		obj->clearModelCondition(7 * 32 + 21);
		break;
	case 3:
		obj->clearModelCondition(7 * 32 + 22);
		break;
	case 4:
		obj->clearModelCondition(18 * 32 + 12);
		break;
	case 5:
		obj->clearModelCondition(18 * 32 + 13);
		break;
	case 6:
		obj->clearModelCondition(18 * 32 + 14);
		break;
	}
}

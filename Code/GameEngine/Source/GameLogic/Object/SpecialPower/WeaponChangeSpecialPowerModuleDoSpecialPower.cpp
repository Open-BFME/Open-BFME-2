// cl: /MD /DNDEBUG /GX- /Oy- /O1 /arch:SSE /G7
//
// WeaponChangeSpecialPowerModule::doSpecialPower, retail 0x004C40BA, 413 bytes:
// slot 10 of the +0x10 special-power interface vftable 0x00C5D150, so `this`
// is that subobject (module data at -0x0C, Object at -0x08), as for
// ScavengerSpecialPower 0x004C4401. Toggles each weapon-set flag named by the
// module data's mask at +0x7C on the Object (clear when set, else set and
// clear the moving/attacking/firing model conditions), then applies the data's
// attribute modifier, disabled-until frames and special model condition, and
// runs the SpecialPowerModule base 0x0049490F.
// Target copy constructor 0x002CF108 (16 fixed bytes; see Object872.h).
class BfmeObject872Header
{
	char bytes[16];
public:
	__declspec(nothrow) BfmeObject872Header(const BfmeObject872Header &);
};
// Out-of-line StringBase<char>::isEmpty is the matched row 0x00001E2F.
template <class T>
class StringBase
{
public:
	bool isEmpty() const;
private:
	void *m_data;
};
// class-gate: allow AsciiString retail calls the out-of-line StringBase<char>::isEmpty at 0x00001E2F here, which the shared shim header inlines; the call is proved by the byte match
class AsciiString : public StringBase<char>
{
};

void *__cdecl ji_006291ae(void *dest, int val, unsigned int count);
#pragma comment(linker, "/alternatename:?ji_006291ae@@YAPAXPAXHI@Z=?ji_006291ae@@YAXXZ")

template <unsigned N>
class BitFlags
{
public:
	BitFlags() { clear(); }
	bool setBitByName(const char *token);
	void clear() { ji_006291ae(m_words, 0, sizeof(m_words)); }
private:
	unsigned m_words[19];
};

class Rva0028D891Owner
{
public:
	bool testBit(int bit) const;
};

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }
private:
	unsigned char m_pad[0x40];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

enum WeaponSetType { WEAPONSET_FIRST = 0 };
enum DisabledType { DISABLED_FIRST = 0 };
enum ModelConditionFlagType { MODELCONDITION_FIRST = 0 };

class Object
{
public:
	void setWeaponSetFlag(WeaponSetType type);
	void clearWeaponSetFlag(WeaponSetType type);
	void rva001E42F2(const int *mask);
	bool addAttributeModifierToPool(const AsciiString &name, int n);
	void setDisabledUntil(DisabledType type, unsigned int frame);
	void setSpecialModelConditionState(ModelConditionFlagType set, unsigned int frames);
};

struct WeaponChangeData
{
	unsigned char m_pad00[0x7C];
	BfmeObject872Header m_weaponSets;	// +0x7C, 16 bytes
	int m_attackerModifier;			// +0x8C
	int m_disabledFrames;			// +0x90
	AsciiString m_name94;			// +0x94
	AsciiString m_name98;			// +0x98
	const unsigned int *weaponSetWords() const { return (const unsigned int *)&m_weaponSets; }
};

class ModuleData;
class ModuleBase
{
public:
	virtual ~ModuleBase();
protected:
	const ModuleData *m_moduleData;	// +0x04
	Object *m_object;		// +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void b00() = 0;
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void s09() = 0;
	virtual void doSpecialPower(unsigned int options) = 0;
};

class SpecialPowerModule : public ModuleBase, public BehaviorModuleInterface,
	public SpecialPowerModuleInterface
{
public:
	virtual void doSpecialPower(unsigned int options);	// 0x0049490F
};

class WeaponChangeSpecialPowerModule : public SpecialPowerModule
{
public:
	virtual void doSpecialPower(unsigned int options);
	const WeaponChangeData *getData() const { return (const WeaponChangeData *)m_moduleData; }
};

void WeaponChangeSpecialPowerModule::doSpecialPower(unsigned int options)
{
	Object *object = m_object;
	if (object)
	{
		const WeaponChangeData *data = getData();
		static BitFlags<304> conditions;
		conditions.clear();
		conditions.setBitByName("MOVING");
		conditions.setBitByName("ATTACKING");
		conditions.setBitByName("FIRING_OR_PREATTACK_A");
		conditions.setBitByName("FIRING_OR_PREATTACK_B");
		if (!data)
			return;
		BfmeObject872Header sets(data->m_weaponSets);
		const unsigned int *words = (const unsigned int *)&sets;
		bool added = false;
		for (int i = 0; i < 0x68; ++i)
		{
			if (words[(unsigned int)i >> 5] & (1 << (i & 0x1f)))
			{
				if (((const Rva0028D891Owner *)object)->testBit(i))
					object->clearWeaponSetFlag((WeaponSetType)i);
				else
				{
					object->setWeaponSetFlag((WeaponSetType)i);
					object->rva001E42F2((const int *)&conditions);
					added = true;
					object->rva001E42F2((const int *)&conditions);
				}
			}
		}
		if (added)
		{
			if (!data->m_name94.isEmpty() && data->m_attackerModifier)
				object->addAttributeModifierToPool(data->m_name94, data->m_attackerModifier);
			if (data->m_attackerModifier > 0)
				object->setDisabledUntil((DisabledType)4, TheGameLogic->getFrame() + data->m_attackerModifier);
			object->setSpecialModelConditionState((ModelConditionFlagType)0x149, data->m_attackerModifier);
		}
		else
		{
			if (!data->m_name98.isEmpty() && data->m_disabledFrames)
				object->addAttributeModifierToPool(data->m_name98, data->m_disabledFrames);
			if (data->m_disabledFrames > 0)
				object->setDisabledUntil((DisabledType)4, TheGameLogic->getFrame() + data->m_disabledFrames);
		}
	}
	SpecialPowerModule::doSpecialPower(options);
}

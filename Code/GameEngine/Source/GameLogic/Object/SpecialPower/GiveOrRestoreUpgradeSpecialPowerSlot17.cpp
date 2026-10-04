// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// ?rva0045108D@GiveOrRestoreUpgradeSpecialPower@@UAEXXZ 0x004CD1B9 275B evidence: slot 17 of vtable 0x0085FA40; base SpecialAbilityUpdate rva0045108D pin 0x0045108D; ModuleData +0xCC UpgradeToGive +0xD0 toggle from rowed ctor 0x004CD0B1; Curse slot-17 precedent
#include "ascii_string.h"

class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern "C" UpgradeCenter *TheUpgradeCenter;
#pragma comment(linker, "/alternatename:_TheUpgradeCenter=?TheUpgradeCenter@@3PAVUpgradeCenter@@A")

namespace _STL
{
template<unsigned N> struct _Base_bitset;
template<> struct _Base_bitset<4>
{
	bool _M_is_any() const;
	unsigned long _M_w[4];
};
}

class Rva0028C570;
class Rva0028D86F
{
public:
	void rva0028D86F(const _STL::_Base_bitset<4> &other);
};

class Object
{
public:
	void rva00293077(const void *arg);
	void rva00290AC1(const Rva0028C570 &flags);
};

class SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
protected:
	const void *m_moduleData;
	Object *m_object;
};

class GiveOrRestoreUpgradeSpecialPowerModuleData
{
public:
	void *m_vtable;
	char m_pad[0xCC - 4];
	AsciiString m_CC;
	_STL::_Base_bitset<4> m_D0;
};

class GiveOrRestoreUpgradeSpecialPower : public SpecialAbilityUpdate
{
public:
	virtual void rva0045108D();
private:
	const GiveOrRestoreUpgradeSpecialPowerModuleData *getData() const
	{
		return (const GiveOrRestoreUpgradeSpecialPowerModuleData *)m_moduleData;
	}
	char m_pad0C[0x88 - 0x0C];
	unsigned char m_88;
	char m_pad89[3];
	AsciiString m_8C;
};

void GiveOrRestoreUpgradeSpecialPower::rva0045108D()
{
	SpecialAbilityUpdate::rva0045108D();
	Object *obj = m_object;
	const GiveOrRestoreUpgradeSpecialPowerModuleData *data = getData();
	if (!obj)
		return;
	if (m_88 != 0)
	{
		if (((const StringBase<char> *)&m_8C)->isEmpty() == false
			&& ((const StringBase<char> *)&m_8C)->isNone() == false)
		{
			const UpgradeTemplate *up = TheUpgradeCenter->findUpgrade(m_8C);
			if (up)
				obj->rva00293077(up);
		}
		m_88 = 0;
		const _STL::_Base_bitset<4> *bits = &data->m_D0;
		if (bits->_M_is_any())
			obj->rva00290AC1(*(const Rva0028C570 *)(const void *)bits);
	}
	else
	{
		AsciiString tmp(data->m_CC);
		if (((const StringBase<char> *)&m_8C)->isEmpty() == false
			&& ((const StringBase<char> *)&m_8C)->isNone() == false)
		{
			const UpgradeTemplate *up = TheUpgradeCenter->findUpgrade(tmp);
			if (up)
				obj->rva00293077(up);
		}
		const _STL::_Base_bitset<4> *bits = &data->m_D0;
		m_88 = 1;
		if (bits->_M_is_any())
			((Rva0028D86F *)obj)->rva0028D86F(*bits);
	}
}

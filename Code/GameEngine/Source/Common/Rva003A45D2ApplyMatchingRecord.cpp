// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii
// stlport
// ?rva003A45D2@Rva003A45D2@@QAEXPAX@Z  Native 0x003A45D2..0x003A46DC (266 bytes)
// Module callback (thiscall ret 4) that takes an Object: snapshots its
// 128-byte upgrade mask at +0x284 (BfmeFixedStorage128 copy ctor 0x0004548B)
// then walks the module data vector of 0xA0-byte records at data +8 for the
// first record whose name matches the object template name (+0x64;
// StringBase::compare 0x000069D6). A record with model-condition flags
// (+0x54; 0x000B3EB3) that the object conditions (+0x10C; 0x00263546) do not
// satisfy aborts; otherwise the owner object gets the record values
// (0x001E431E) and the record FXList (doFXObj 0x000B2235) and its drawable
// (the folded getter 0x005508E2) is refreshed (0x00274176 false); when the
// snapshot has any bit set it is ORed back into the owner mask
// (_Base_bitset<32>::_M_do_or 0x0028C557) and updateUpgradeModules 0x00292EEA
// runs. WB twin 0x00FA6BD0 has the same callees in the same order. The only
// direct caller is 0x001F22A8. A real STLport vector gives the idiv size and
// strength-reduced index; retail inlines the any-bit scan (zero kept in ESI).
#include <bitset>
#include <vector>
#include "ascii_string.h"

struct BfmeFixedStorage128
{
	unsigned int words[32];
	BfmeFixedStorage128(const BfmeFixedStorage128 &rhs);
	bool any() const
	{
		for (unsigned int i = 0; i < 32; ++i)
			if (words[i] != 0)
				return true;
		return false;
	}
};

class FXList
{
public:
	static void doFXObj(const FXList *fx, const class Object *primary, const class Object *secondary);
};

class ModelConditionFlags
{
public:
	bool rva000B3EB3() const;
};

class Rva00263546
{
public:
	bool rva00263546(const Rva00263546 *other) const;
};

class Rva001E431E
{
public:
	void rva001E431E(const int *value);
};

class Drawable
{
public:
	void rva00274176(bool flag);
};

class BuildListInfo
{
public:
	int getDesiredGatherers();
};

struct ThingTemplate
{
	char m_pad00[0x64];
	AsciiString m_name;
};

class Object
{
public:
	Drawable *getDrawable() { return (Drawable *)((BuildListInfo *)this)->getDesiredGatherers(); }
	void updateUpgradeModules();
	const ThingTemplate *getTemplate() const { return m_template; }
	char m_pad00[4];
	const ThingTemplate *m_template;
	char m_pad08[0x10C - 0x08];
	Rva00263546 m_conditions;
	char m_pad10D[0x284 - 0x10D];
	BfmeFixedStorage128 m_upgrades;
};

struct Rva003A45D2Rec
{
	AsciiString m_name;
	const FXList *m_fx;
	int m_value[19];
	ModelConditionFlags m_flags;
	char m_pad55[0xA0 - 0x55];
};

struct Rva003A45D2Data
{
	char m_pad00[8];
	_STL::vector<Rva003A45D2Rec> m_recs;
};

class Rva003A45D2
{
public:
	void rva003A45D2(void *arg);
	void *m_vtbl;
	const Rva003A45D2Data *m_data;
	Object *m_object;
};

void Rva003A45D2::rva003A45D2(void *arg)
{
	Object *obj = (Object *)arg;
	const Rva003A45D2Data *data = m_data;
	BfmeFixedStorage128 saved(obj->m_upgrades);
	for (unsigned int i = 0; i < data->m_recs.size(); ++i)
	{
		const Rva003A45D2Rec *rec = &data->m_recs[i];
		if (rec->m_name.compare(obj->getTemplate()->m_name) == 0)
		{
			if (rec->m_flags.rva000B3EB3() && !obj->m_conditions.rva00263546((const Rva00263546 *)&rec->m_flags))
				return;
			((Rva001E431E *)m_object)->rva001E431E(rec->m_value);
			if (rec->m_fx)
				FXList::doFXObj(rec->m_fx, m_object, 0);
			Drawable *draw = m_object->getDrawable();
			if (draw)
				draw->rva00274176(false);
			if (saved.any())
			{
				((_STL::_Base_bitset<32> *)&m_object->m_upgrades)->_M_do_or(*(_STL::_Base_bitset<32> *)&saved);
				m_object->updateUpgradeModules();
			}
			return;
		}
	}
}

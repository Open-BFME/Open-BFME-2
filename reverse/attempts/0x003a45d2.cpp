// 0x003A45D2
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
//
// ?rva003A45D2@Rva003A45D2@@QAEXPAX@Z retail 0x003A45D2..0x003A46DC (266B)
#include <bitset>
#include <vector>
#include "ascii_string.h"

struct BfmeFixedStorage128
{
	unsigned int words[32];
	BfmeFixedStorage128(const BfmeFixedStorage128 &rhs);
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

class Drawable
{
public:
	void rva00274176(bool flag);
};

struct ThingTemplate
{
	char m_pad00[0x64];
	AsciiString m_name;
};

class Object
{
public:
	void rva001E431E(const int *value);
	Drawable *getDrawable() const;
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
			m_object->rva001E431E(rec->m_value);
			if (rec->m_fx)
				FXList::doFXObj(rec->m_fx, m_object, 0);
			Drawable *draw = m_object->getDrawable();
			if (draw)
				draw->rva00274176(false);
			_STL::_Base_bitset<32> &bits = *(_STL::_Base_bitset<32> *)&saved;
			if (bits._M_is_any())
			{
				((_STL::_Base_bitset<32> *)&m_object->m_upgrades)->_M_do_or(bits);
				m_object->updateUpgradeModules();
			}
			return;
		}
	}
}

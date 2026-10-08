// ?OnDeactivation@EmotionNugget@@QAEXXZ
// partial score=0.9 date=2026-10-09
// Retail/WB pass 2026-10-09: reconstructed from the complete target body
// and WorldBuilder's EmotionNugget.cpp sibling. Member offsets, vtable slots,
// frame comparisons, and call targets are retail evidence. Method identity is
// the WB assertion/callgraph lead; the entry's original getter names remain
// unresolved. The BFME 1 emotion unit at 0bef414b5 was compiled and placed no
// new target bodies. This is a near match, not recovered coverage.
// Real StringBase::isEmpty template definition from string_base.cpp makes
// its nonthrowing implementation visible. Direct condition temporaries then
// reproduce retail's cleanup-state pattern. The old bank's cached FX pointer,
// unguarded null-AI tail, and signed expiry comparison were target divergences.
// A word at Object+0x124 owns the cleared 0x100 model-condition mask.
// ?rva004DD2C0@Emotion@@QAEXXZ
// partial score=0.93 date=2026-10-04
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva004DD2C0@Emotion@@QAEXXZ @ 0x004DD2C0 (457B).
// Emotion update: folds entry delays into local frames through TheGameLogic,
// plays entry FX, nudges AI, applies weapon-set/condition changes and applies
// the entry attribute modifier by name. Evidence: callers at 0x004B0E12,
// 0x004B0EB2, 0x004B15F2, 0x004B1689 pass [EmotionTrackerUpdate+0x7c] as this;
// callees rowed map<int,int>::operator[] 0x0028932C, map<ushort,int> 0x004DD277,
// Object::rva0029439D, GameLogic::findObjectByID 0x00049DC5,
// FXList::doFXObj 0x000B2235, AIUpdateInterface::rva002632E1,
// Object::clearAndSetModelConditionFlagsForHorde/0x0028CFB2/0x0028AE6D, AsciiField::get 0x004DC8E7,
// StringBase::isEmpty 0x00001E2F/releaseBuffer 0x00036410,
// Object::addAttributeModifierToPool (pin); TheGameLogic 0x009FE78C.

#include <map>
#include "ascii_string.h"
template <typename T>
inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}


struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};

enum ObjectID
{
	INVALID_ID = 0
};

class Object;
class FXList;
class AIUpdateInterface;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
public:
	char m_pad00[0x40];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

class FXList
{
public:
	void doFXObj(const Object *primary, const Object *secondary) const;
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class AIUpdateInterface
{
public:
	void rva002632E1();
public:
	char m_pad00[0x3C5];
	unsigned char m_byte3C5;
};

class Rva0029439DIface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual Object *v19();
};

class Object
{
public:
	void *rva0029439D();
	void clearAndSetModelConditionFlagsForHorde(const int *a, const int *b);
	void rva0028CFB2(const int *a, const int *b);
	void rva0028AE6D();
	bool addAttributeModifierToPool(const AsciiString &name, int value);
public:
	char m_pad00[0x124];
	unsigned int m_conditionWord124;
	char m_pad128[0x258 - 0x128];
	AIUpdateInterface *m_ai258;
};

class Rva004DC8E7AsciiField
{
public:
	AsciiString get() const;
public:
	char m_pad00[0x10];
	int m_10;
	int m_14;
	int m_18;
	char m_pad1C[0x38 - 0x1C];
	const FXList *m_fx38;
	AsciiString m_str3C;
	int m_40;
	unsigned char m_flag44;
	char m_pad45[3];
	int m_48;
	int m_4C;
	char m_pad50[0xA0 - 0x50];
	int m_a0;
	char m_padA4[0x138 - 0xA4];
	int m_138;
	char m_pad13C[0x184 - 0x13C];
	unsigned char m_184;
};

class EmotionNugget
{
public:
	void OnDeactivation();
private:
	Object *m_object;
	Rva004DC8E7AsciiField *m_entry;
	int m_id08;
	unsigned short m_key0C;
	char m_pad0E[2];
	unsigned int m_frame10;
	_STL::map<int, int> m_map14;
	_STL::map<unsigned short, int, Gen_lt_00940b40> m_map20;
	int m_2C;
	unsigned int m_start30;
};

// ?rva004DD2C0@Emotion@@QAEXXZ present-unmatched
void EmotionNugget::OnDeactivation()
{
	if (m_entry->m_10)
		m_frame10 = TheGameLogic->m_frame + m_entry->m_10;
	if (m_entry->m_14 && m_id08)
	{
		int duration = m_entry->m_14;
		unsigned frame = TheGameLogic->m_frame;
		m_map14[m_id08] = frame + duration;
	}
	if (m_entry->m_18 && m_key0C)
	{
		int duration = m_entry->m_18;
		unsigned frame = TheGameLogic->m_frame;
		m_map20[m_key0C] = frame + duration;
	}
	if (m_entry->m_fx38)
	{
		Object *obj = m_object;
		void *iface = obj->rva0029439D();
		if (iface)
			obj = ((Rva0029439DIface *)iface)->v19();
		int id = m_id08;
		Object *found = TheGameLogic->findObjectByID((ObjectID)id);
		if (found || !id)
		{
			if (!obj)
				obj = m_object;
			FXList::doFXObj(m_entry->m_fx38, obj, found);
		}
	}
	AIUpdateInterface *ai = m_object->m_ai258;
	if (ai)
	{
		int kind = m_entry->m_4C;
		if (!kind || (kind > 1 && kind <= 5))
		{
			ai->rva002632E1();
			if (m_entry->m_184)
				ai->m_byte3C5 = 0;
		}
	{
		void *iface = m_object->rva0029439D();
		if (iface)
			m_object->clearAndSetModelConditionFlagsForHorde(&m_entry->m_a0, &m_entry->m_138);
		else
			m_object->rva0028CFB2(&m_entry->m_a0, &m_entry->m_138);
		Object *object = m_object;
		if (object->m_conditionWord124 & 0x100)
		{
			object->m_conditionWord124 &= ~0x100;
			object->rva0028AE6D();
		}
	}
	if (!((const StringBase<char> &)(m_entry->get())).isEmpty() && TheGameLogic->m_frame >= m_start30 + m_entry->m_40 && m_entry->m_flag44)
	{
		m_object->addAttributeModifierToPool(m_entry->get(), m_entry->m_48);
	}
	}
}

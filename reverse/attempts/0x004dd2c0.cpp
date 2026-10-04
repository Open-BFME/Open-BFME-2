// ?rva004DD2C0@Emotion@@QAEXXZ
// partial score=0.92 date=2026-10-04
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
// Object::rva00293C77/0x0028CFB2/0x0028AE6D, AsciiField::get 0x004DC8E7,
// StringBase::isEmpty 0x00001E2F/releaseBuffer 0x00036410,
// Object::rva0028EA91 (pin); TheGameLogic 0x009FE78C.

#include <map>
#include "ascii_string.h"

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
	int m_frame;
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
	void rva00293C77(const int *a, const int *b);
	void rva0028CFB2(const int *a, const int *b);
	void rva0028AE6D();
	bool rva0028EA91(const AsciiString &name, int value);
public:
	char m_pad00[0x125];
	volatile unsigned char m_byte125;
	char m_pad126[0x258 - 0x126];
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

class Emotion
{
public:
	void rva004DD2C0();
private:
	Object *m_object;
	Rva004DC8E7AsciiField *m_entry;
	int m_id08;
	unsigned short m_key0C;
	char m_pad0E[2];
	int m_frame10;
	_STL::map<int, int> m_map14;
	_STL::map<unsigned short, int, Gen_lt_00940b40> m_map20;
	int m_2C;
	int m_start30;
};

// ?rva004DD2C0@Emotion@@QAEXXZ present-unmatched
void Emotion::rva004DD2C0()
{
	if (m_entry->m_10)
		m_frame10 = m_entry->m_10 + TheGameLogic->m_frame;
	if (m_entry->m_14 && m_id08)
		m_map14[m_id08] = m_entry->m_14 + TheGameLogic->m_frame;
	if (m_entry->m_18 && m_key0C)
		m_map20[m_key0C] = m_entry->m_18 + TheGameLogic->m_frame;
	if (m_entry->m_fx38)
	{
		Object *obj = m_object;
		void *iface = obj->rva0029439D();
		Object *who = obj;
		if (iface)
			who = ((Rva0029439DIface *)iface)->v19();
		int id = m_id08;
		Object *found = TheGameLogic->findObjectByID((ObjectID)id);
		if (found || !id)
		{
			if (!who)
				who = m_object;
			FXList::doFXObj(m_entry->m_fx38, who, found);
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
	}
	{
		Object *obj = m_object;
		void *iface = obj->rva0029439D();
		if (iface)
			obj->rva00293C77(&m_entry->m_a0, &m_entry->m_138);
		else
			obj->rva0028CFB2(&m_entry->m_a0, &m_entry->m_138);
		if (obj->m_byte125 & 1)
		{
			obj->m_byte125 &= ~1;
			obj->rva0028AE6D();
		}
	}
	AsciiString name = m_entry->get();
	bool doApply = true;
	if (((StringBase<char> *)&name)->isEmpty() || TheGameLogic->m_frame < m_start30 + m_entry->m_40 || !m_entry->m_flag44)
		doApply = false;
	if (doApply)
	{
		AsciiString name2 = m_entry->get();
		m_object->rva0028EA91(name2, m_entry->m_48);
	}
}

// cl: /O1 /Ireference/shims/bfme2_ascii /MD /EHsc
#include "unicode_string.h"

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned flags);
	int references;
};

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva002BED91
{
	TargetRef00217D4C *m_ptr;
	Rva002BED91() : m_ptr(0) {}
	__forceinline ~Rva002BED91()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	void set(TargetRef00217D4C *p);
};

class Rva005398CD
{
	char m_opaque[12];

public:
	Rva005398CD(const UnicodeString &first, const UnicodeString &second);
};

class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &hint);
};

class Rva005CB260
{
public:
	void rva005CB260(int observer);
};

class Rva005CC208
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual bool slot2();
	virtual bool rva005CC208();
};

class Rva0086E330Base
{
public:
	virtual ~Rva0086E330Base() {}
};

class InGameHelpBox;
class InGameHotSpot;

class InGameHotSpotSimpleHelp : public Rva0086E330Base
{
public:
	InGameHotSpotSimpleHelp(InGameHelpBox *helpBox, InGameHotSpot *hotSpot,
		const UnicodeString &first, const UnicodeString &second);
	virtual ~InGameHotSpotSimpleHelp();
	virtual void OnHotSpotRollOver(InGameHotSpot *&hotSpot);

private:
	InGameHelpBox *m_helpBox;
	InGameHotSpot *m_hotSpot;
	UnicodeString m_string0;
	UnicodeString m_string1;
	Rva002BED91 m_hint;
};

InGameHotSpotSimpleHelp::InGameHotSpotSimpleHelp(InGameHelpBox *helpBox,
	InGameHotSpot *hotSpot, const UnicodeString &first, const UnicodeString &second)
	: m_helpBox(helpBox), m_hotSpot(hotSpot), m_string0(first), m_string1(second), m_hint()
{
	((Rva005CB260 *)m_hotSpot)->rva005CB260((int)this);
	if (((Rva005CC208 *)m_hotSpot)->Rva005CC208::rva005CC208())
	{
		TargetRef00217D4C *hint =
			(TargetRef00217D4C *)new Rva005398CD(m_string0, m_string1);
		m_hint.set(hint);
		((Rva001FF3A9 *)m_helpBox)->rva001FF3A9((const TreeHintRef00217D4C &)m_hint);
	}
}

void InGameHotSpotSimpleHelp::OnHotSpotRollOver(InGameHotSpot *&hotSpot)
{
	(void)hotSpot;
	TargetRef00217D4C *hint =
		(TargetRef00217D4C *)new Rva005398CD(m_string0, m_string1);
	m_hint.set(hint);
	((Rva001FF3A9 *)m_helpBox)->rva001FF3A9((const TreeHintRef00217D4C &)m_hint);
}

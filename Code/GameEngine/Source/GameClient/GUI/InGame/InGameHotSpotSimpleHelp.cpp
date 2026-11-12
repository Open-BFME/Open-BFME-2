// cl: /O1 /Ireference/shims/bfme2_ascii /MD /EHsc
#include "unicode_string.h"

#include "../../../../../Libraries/Source/Apt/AptRefTarget.h"


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

class InGameSimpleHelp
{
	char m_opaque[12];

public:
	InGameSimpleHelp(const UnicodeString &first, const UnicodeString &second);
};

class Rva001FF3A9
{
public:
	void rva001FF3A9(const TreeHintRef00217D4C &hint);
};

#include "../../../../Include/Common/Rva005CB260.h"

class Rva005CC208
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual bool slot2();
	virtual bool rva005CC208();
};

// Retail's base vftable 0x00C6E330 (and this class's 0x00C77960 up to slot 3)
// holds the shared empty one-argument body 0x0047A69C, not a destructor: the
// destructors are not virtual. Other units' views of Rva0086E330Base give it
// a virtual destructor (their vftable COMDAT holds it), so this unit spells
// the same base under its own name to keep its vftable copy distinct.
class Rva0086E330BaseSlots
{
public:
	virtual void slot0(void *);
	~Rva0086E330BaseSlots() {}
};

class InGameHelpBox;
class InGameHotSpot;

class InGameHotSpotSimpleHelp : public Rva0086E330BaseSlots
{
public:
	InGameHotSpotSimpleHelp(InGameHelpBox *helpBox, InGameHotSpot *hotSpot,
		const UnicodeString &first, const UnicodeString &second);
	~InGameHotSpotSimpleHelp();
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
			(TargetRef00217D4C *)new InGameSimpleHelp(m_string0, m_string1);
		m_hint.set(hint);
		((Rva001FF3A9 *)m_helpBox)->rva001FF3A9((const TreeHintRef00217D4C &)m_hint);
	}
}

void InGameHotSpotSimpleHelp::OnHotSpotRollOver(InGameHotSpot *&hotSpot)
{
	(void)hotSpot;
	TargetRef00217D4C *hint =
		(TargetRef00217D4C *)new InGameSimpleHelp(m_string0, m_string1);
	m_hint.set(hint);
	((Rva001FF3A9 *)m_helpBox)->rva001FF3A9((const TreeHintRef00217D4C &)m_hint);
}

// ?slot0@Rva0086E330BaseSlots@@UAEXPAX@Z, retail 0x0047A69C (3B, ret 4): slot 0
// of the base vftable 0x00C6E330 (ICF-rowed as EmissionVelocityInfo::DoXfer).
void Rva0086E330BaseSlots::slot0(void *)
{
}

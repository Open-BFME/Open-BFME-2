// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc
// Table-reached bodies from .text gaps no ledger row covers (seat-3 batch H;
// see GapBodiesS3A.cpp). Retail bytes establish every shape; owning classes
// are not recovered unless a callee names them, so each keeps an
// address-derived name and a view of only the members it touches. Unrowed
// callees are pinned under address-derived names.
#include "unicode_string.h"

class Object;

// --- 0x005FEDCD (60B): after the +0x08 part's (folded, empty) hook, show the
// strategic tooltip for the +0x24 index (none for 7) through TheMouse.
struct RGBColor;

class Mouse
{
public:
	void rva001EEA6D(UnicodeString tooltip, int delay, const RGBColor *color, float width);	// 0x001EEA6D
};

extern Mouse *TheMouse;

namespace StrategicInGameUI
{
	UnicodeString GetTooltipText(int index);				// 0x005F027D
}

// 0x000B3FD0 is the one-byte empty body the toolchain folds many empties into.
class Rva000B3FD0
{
public:
	void rva000B3FD0();
};

class Rva005FEDCD
{
public:
	virtual void rva005FEDCD();
private:
	int m_04;
	Rva000B3FD0 m_part08;									// +0x08
	char m_pad09[0x24 - 0x09];
	int m_tooltipIndex;										// +0x24
};

void Rva005FEDCD::rva005FEDCD()
{
	m_part08.rva000B3FD0();
	int index = m_tooltipIndex;
	if (index != 7)
		TheMouse->rva001EEA6D(StrategicInGameUI::GetTooltipText(index), -1, 0, 1.0f);
}

// --- 0x005D898A (74B): for an armed object (rowed getCurrentWeapon) whose AI
// (+0x258) has a victim, defer to own slot 7 or slot 8 as the 0x005D896F
// test on the object decides; false otherwise.
class Weapon;
enum WeaponSlotType { PRIMARY_WEAPON = 0 };

class AIUpdateInterface
{
public:
	Object *getCurrentVictim() const;						// 0x00268D71
};

class Object
{
public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const;	// 0x0028AEBD
	char m_pad000[0x258];
	AIUpdateInterface *m_ai;								// +0x258
};

class Rva005D898A
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6();
	virtual bool s7(Object *obj);
	virtual bool s8(Object *obj);
	virtual bool rva005D898A(Object *obj);
	bool rva005D896F(Object *obj);							// 0x005D896F
};

bool Rva005D898A::rva005D898A(Object *obj)
{
	if (obj->getCurrentWeapon(0) && obj->m_ai && obj->m_ai->getCurrentVictim())
		return rva005D896F(obj) ? s7(obj) : s8(obj);
	return false;
}

// --- 0x002E41EC (64B): after the 0x002E40DB step succeeds, raise
// PolygonTrigger's id counter past the largest id (+0x44) on the
// 0x00DBD0F4 trigger list (linked through +0x3C).
struct Rva002E373CTrigger
{
	char m_pad00[0x3C];
	Rva002E373CTrigger *m_next;								// +0x3C
	int m_40;
	int m_id;												// +0x44
};

struct Rva002E373CHolder
{
	Rva002E373CTrigger *m_first;							// +0x00
};

extern Rva002E373CHolder *g_Va00DBD0F4;

class Rva002E41EC;

class PolygonTrigger
{
	friend class Rva002E41EC;
	static int s_currentID;									// 0x00DBD0F0
};

class DataChunkInput;
struct DataChunkInfo;

class PolygonTriggerDataChunkParserBase
{
public:
	bool parse(DataChunkInput &file, const DataChunkInfo *info);	// 0x002E40DB
};

class Rva002E41EC
{
public:
	virtual bool rva002E41EC(void *file, void *b);
};

// The parse step is the rowed PolygonTriggerDataChunkParserBase::parse; this
// class's relation to it is not recovered, so it is reached through this.
bool Rva002E41EC::rva002E41EC(void *file, void *b)
{
	if (!reinterpret_cast<PolygonTriggerDataChunkParserBase *>(this)->parse(
			*static_cast<DataChunkInput *>(file), static_cast<const DataChunkInfo *>(b)))
		return false;
	int maxID = 0;
	for (Rva002E373CTrigger *trigger = g_Va00DBD0F4->m_first; trigger; trigger = trigger->m_next)
	{
		if (trigger->m_id > maxID)
			maxID = trigger->m_id;
	}
	if (maxID + 1 > PolygonTrigger::s_currentID)
		PolygonTrigger::s_currentID = maxID + 1;
	return true;
}

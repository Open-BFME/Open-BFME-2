// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common /ICode/Libraries/Include/Lib
// stlport
//
// ?rva00439428@Rva00439E0C@@QAE_NPAVObject@@PBUCoord3D@@PAURva004393D6Entry@@HHPAW4ObjectID@@@Z,
// retail 0x00439428 (427 bytes).  The per-entry check of the detection walk
// 0x0043966A (the only caller, on the TheGameLogic +0x178 invisibility
// manager), given the object, its position, one record entry, the record's
// +0x0C and +0x04 words and an out ObjectID.
//
// Target evidence: false for an object with +0x438 bit 0, the 0x002933CD
// flag or kind 0x220, before the record's +0x04 frame, or whose 0x0028F4BC
// part has a nonzero +0x3C.  Otherwise it starts true and is cleared by: entry
// bit 2 with a positive 0x0028AC7D value; 0x004387B1 for the entry's flags;
// a nonempty entry mask (+0x04, 128 bits) the object's +0x94 holder meets;
// entry bit 0x200 with object status 0x18; entry bit 0x100 when the object's
// state (0x0028F4EF) is not 2 and its +0x254 part answers slot 16 at least
// the record's +0x0C word with a slot-15 record whose +0x20 is nonzero and
// +0x10 is not 7.  The nearby check 0x004388E3 (Rva004389AENearbyCheck.cpp,
// which reads the same entry as Rva004388E3Template) then forces the result
// back on for a cleared entry carrying +0x9C bit 0, or clears it under entry
// bit 0 when nothing is near.  A surviving entry of mode 0 (+0x18) still
// fails for an object with +0x437 bit 3, and one of mode 1 when 0x0043912F
// finds a detector (its ID goes to the out argument).  Names are neutral.
#include "GameLogicObjectLookupView.h"
#include "Coord3D.h"
#include <bitset>

extern GameLogic *TheGameLogic;

enum KindOfType
{
	KINDOF_INVALID = -1
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_NONE = 0
};

class Rva00373EC6
{
public:
	char m_pad00[0x3C];
	int m_3c;	// +0x3C
};

struct Rva00439428Record
{
	char m_pad00[0x10];
	int m_10;	// +0x10
	char m_pad14[0x20 - 0x14];
	float m_20;	// +0x20
};

class Rva00439428Part
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual Rva00439428Record *f15();	// +0x3C
	virtual unsigned int f16();	// +0x40
};

class Object
{
public:
	int rva002933CD();
	bool isKindOf(KindOfType kind) const;
	Rva00373EC6 *rva0028F4BC();
	float rva0028AC7D() const;
	bool testStatus(ObjectStatusTypes bit) const;
	int rva0028F4EF();
private:
	char m_pad000[0x254];
public:
	Rva00439428Part *m_254;	// +0x254
private:
	char m_pad258[0x437 - 0x258];
public:
	unsigned char m_437;	// +0x437
	unsigned char m_438;	// +0x438
};

class Rva0028B7AELeaGetter
{
public:
	void *get() const;
};

class Rva00331682Holder
{
public:
	bool test(const void *key) const;
};

struct Rva004393D6Entry
{
	unsigned int m_flags;	// +0x00
	_STL::bitset<128> m_mask;	// +0x04
	float m_14;	// +0x14
	int m_mode;	// +0x18
	char m_pad1c[0x9C - 0x1C];
	unsigned char m_9c;	// +0x9C
};

struct Rva004388E3Template;

class Rva004389AE
{
public:
	bool rva004388E3(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl);
	bool rva0043912F(Object *obj, const Coord3D *pos, Rva004388E3Template *tmpl, ObjectID *out);
};

class Rva00439E0C
{
public:
	bool rva00439428(Object *obj, const Coord3D *pos, Rva004393D6Entry *entry, int level, int frame, ObjectID *id);
	bool rva004387B1(Object *obj, unsigned int flags);
};

bool Rva00439E0C::rva00439428(Object *obj, const Coord3D *pos, Rva004393D6Entry *entry, int level, int frame, ObjectID *id)
{
	if (!(obj->m_438 & 1) && !(unsigned char)obj->rva002933CD() && !obj->isKindOf((KindOfType)0x220)
		&& TheGameLogic->getFrame() >= (unsigned int)frame)
	{
		Rva00373EC6 *part = obj->rva0028F4BC();
		if (!part || part->m_3c == 0)
		{
			bool visible = true;
			if ((entry->m_flags & 2) && obj->rva0028AC7D() > 0.0f)
				visible = false;
			if (rva004387B1(obj, entry->m_flags))
				visible = false;
			if (entry->m_mask.any())
			{
				Rva00331682Holder *holder = (Rva00331682Holder *)((Rva0028B7AELeaGetter *)obj)->get();
				if (holder->test(&entry->m_mask))
					visible = false;
			}
			unsigned int flags = entry->m_flags;
			if ((flags & 0x200) && obj->testStatus((ObjectStatusTypes)0x18))
				visible = false;
			if ((flags & 0x100) && obj->rva0028F4EF() != 2)
			{
				Rva00439428Part *other = obj->m_254;
				if (other && other->f16() >= (unsigned int)level)
				{
					Rva00439428Record *record = other->f15();
					if (record && record->m_20 != 0.0f && record->m_10 != 7)
						visible = false;
				}
			}

			bool force = !visible && (entry->m_9c & 1);
			if (force || (entry->m_flags & 1))
			{
				if (((Rva004389AE *)this)->rva004388E3(obj, pos, (Rva004388E3Template *)entry))
				{
					if (force)
						visible = true;
				}
				else if (entry->m_flags & 1)
					visible = false;
			}
			if (visible)
			{
				int mode = entry->m_mode;
				if (mode != 0 || !(obj->m_437 & 8))
				{
					if (mode != 1 || !((Rva004389AE *)this)->rva0043912F(obj, pos, (Rva004388E3Template *)entry, id))
						return true;
				}
			}
		}
	}
	return false;
}

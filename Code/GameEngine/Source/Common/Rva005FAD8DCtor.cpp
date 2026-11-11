// cl: /O1 /MD /EHsc /DNDEBUG
// ??0Rva005FAD8D@@QAE@PAX0@Z, retail 0x005FAFE8..0x005FB14E (358 bytes, EH,
// ret 8): the constructor of the class whose destructor 0x005FAD8D is rowed
// in Rva005FAD8DDtor.cpp (base table 0x00C75284, own table 0x00C79ED4).
// Target evidence: the owner word at +4 (the destructor reaches the battle
// through its +0x14), three words copied from the second argument's
// +0x0C/+0x10/+0x14, the +0x14 flag cleared, the rowed Rva005F2381 member at
// +0x18 (its dtor 0x005F23B2), a three-entry table of 8-byte records at +0x34
// built by the vector constructor iterator over the element ctor 0x005FA892
// (two -1 words, rowed here), the record count at +0x4C and -1 at +0x50.
// The body resets the owner's +8 list (rowed 0x005FFED5(0)) and walks the
// battle's units like the twin constructors in Rva005FB204Ctor.cpp: each unit
// gets a counted prompt (rowed factory 0x005FAC2B over a {unit, this}
// payload); a unit with a template name is recorded with the list's handle
// (0x005FFEE5), the rest go to 0x005FFEDD. Two rounds then set entries 0 and 1
// through 0x00600052/0x0060005A by whether the table holds j+2 records, and
// the object joins the battle's +8 listener list (rowed 0x005A0B4C), which the
// destructor leaves again. Names are address-derived; identities are not
// established.
#include "BattlePromptCallbackPayloadView.h"

template <class T> class StringBase
{
public:
	bool isEmpty() const;
};

class Rva005FAAA1
{
public:
	struct Payload { int v[2]; };
};
RvaCloneResult<Rva005FAAA1> Rva005FAC2BCreate(const Rva005FAAA1::Payload *src);

class Rva002BC1DAUnit
{
public:
	unsigned char m_pad00[0x18];
	StringBase<char> m_templateName;	// +0x18
};

#include "../../Include/GameLogic/LivingWorldBattle.h"

#include "../../Include/GameLogic/Rva003F4DCA.h"

struct Rva002BA8F1Listener;

#include "../../Include/Common/Rva005A0B4CList.h"

class Rva005FFED5 { public: void rva005FFED5(int value); };
class Rva005FFEDD { public: void rva005FFEDD(const TreeHintRef00217D4C &prompt); };
class Rva005FFEE5 { public: int rva005FFEE5(const TreeHintRef00217D4C &prompt); };
class Rva00600052VisibilityForward { public: void forward(int index, bool visible); };
class Rva0060005A { public: void SetSwapButtonState(int index, bool enabled); };

// The owner (the Rva006003FC layout of Rva005FB204Ctor.cpp): the +8 list and
// the battle side/army it shows.
class Rva005FAFE8Owner
{
public:
	void *m_vtbl;
	int m_04;
	unsigned char m_list08[0xC];		// +0x08
	LivingWorldBattle *m_battle;		// +0x14
	int m_side;				// +0x18
	int m_army;				// +0x1C
};

class Rva005FAD8DV10;
class Rva005FAD8DV0C;

struct Rva005FAFE8Source
{
	unsigned char m_pad00[0xC];
	int m_0C;
	Rva005FAD8DV0C *m_10;
	Rva005FAD8DV10 *m_14;
};

class Rva00875284Base
{
public:
	virtual void f0();
	virtual void f1();
	~Rva00875284Base() {}
};

class Rva005F2381
{
public:
	Rva005F2381();
	~Rva005F2381();
private:
	unsigned char m_bytes[0x1C];
};

// The +0x34 records: an index and the list handle, both -1 when unused.
class Rva005FA892
{
public:
	Rva005FA892();
	int m_index;
	int m_value;
};

Rva005FA892::Rva005FA892() : m_index(-1), m_value(-1)
{
}

class Rva005FAD8D : public Rva00875284Base
{
public:
	Rva005FAD8D(void *owner, void *source);
	~Rva005FAD8D();
	virtual void f0();
	virtual void f1();
private:
	Rva005FAFE8Owner *m_04;
	int m_08;
	Rva005FAD8DV0C *m_0C;
	Rva005FAD8DV10 *m_10;
	int m_flag14;
	Rva005F2381 m_18;
	Rva005FA892 m_records[3];		// +0x34
	int m_recordCount;			// +0x4C
	int m_50;				// +0x50
};

Rva005FAD8D::Rva005FAD8D(void *owner, void *source)
	: m_04((Rva005FAFE8Owner *)owner),
	  m_08(((Rva005FAFE8Source *)source)->m_0C),
	  m_0C(((Rva005FAFE8Source *)source)->m_10),
	  m_10(((Rva005FAFE8Source *)source)->m_14),
	  m_flag14(0)
{
	m_recordCount = 0;
	m_50 = -1;
	void *list = m_04->m_list08;
	((Rva005FFED5 *)list)->rva005FFED5(0);
	LivingWorldBattle *battle = m_04->m_battle;
	int side = m_04->m_side;
	int army = m_04->m_army;
	int count = ((Rva003F4DCA *)battle)->rva003F4DCA(side, army);
	int i = 0;
	if (i < count)
	{
		Rva005FAAA1::Payload payload;
		payload.v[1] = (int)this;
		do
		{
			Rva002BC1DAUnit *unit = (Rva002BC1DAUnit *)battle->rva003F48FE(side, army, i);
			payload.v[0] = (int)unit;
			RvaCloneResult<Rva005FAAA1> prompt = Rva005FAC2BCreate(&payload);
			if (!unit->m_templateName.isEmpty())
			{
				Rva005FA892 &record = m_records[m_recordCount++];
				record.m_index = i;
				record.m_value = ((Rva005FFEE5 *)list)->rva005FFEE5(prompt);
			}
			else
			{
				((Rva005FFEDD *)list)->rva005FFEDD(prompt);
			}
		} while (++i < count);
	}
	for (int j = 0; j < 2; ++j)
	{
		((Rva00600052VisibilityForward *)list)->forward(j, m_recordCount >= j + 2);
		((Rva0060005A *)list)->SetSwapButtonState(j, m_recordCount >= j + 2);
	}
	((Rva005A0B4CList *)((char *)battle + 8))->append((Rva002BA8F1Listener *)this);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f0@Rva005FAD8D@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?f0@Rva00875284Base@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?f1@Rva005FAD8D@@UAEXXZ=?swapEntries@@YIXPAVRva005FA98C@@HHHHHH@Z")
// Base C75284 slot 1 is the empty RET20 at 25EF04, not the derived
// C79ED4 slot 1 swap callback. Both complete tables contain two entries.
#pragma comment(linker, "/alternatename:?f1@Rva00875284Base@@UAEXXZ=?Set_Animation@RenderObjClass@@UAEXPAVHAnimClass@@M0MM@Z")

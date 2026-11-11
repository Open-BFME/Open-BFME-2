// cl: /O1 /MD /EHsc /DNDEBUG
//
// ??0Rva005FB204@@QAE@IIPAX@Z @0x005FB30A 207B (EH, ret 0xC).
// Constructor of the class whose destructor 0x005FB204 and deleting
// destructor 0x005FB20F are rowed in RvaDerivedDtorTails.cpp (vtable
// 0x00C79EF0); built by the rowed factory 0x005E97D5 into a 0x20-byte object.
// Target evidence: base Rva006003FC(a, b, c) (constructor 0x00600432,
// pinned), the vptr, then the +8 list is reset through rowed 0x005FFED5(1).
// The battle at +0x14 reports a unit count for the side/army pair at
// +0x18/+0x1C (0x003F4DCA) and each unit (0x003F48FE); every unit is wrapped
// in a counted prompt (rowed factory 0x005FB29A over a one-word payload) and
// handed to the list: units with an empty template name (+0x18, the view
// LivingWorldLogic.cpp uses) through 0x005FFEDD, the rest through 0x005FFEE5.
// The unit pointer survives the factory call in a register, so the factory
// reads a separate payload word, not the unit variable itself.
// Names are address-derived; identities are not established.
#include "BattlePromptCallbackPayloadView.h"

template <class T> class StringBase
{
public:
	bool isEmpty() const;
};

class Rva005FB22B;
RvaCloneResult<Rva005FB22B> Rva005FB29ACreate(const void *arg);

// The one-word counted handle the rowed factory 0x005FB46F returns; released
// inline through 0x0007DEEF like RvaCloneResult.
struct RvaF1Handle
{
	void *m_p;
	~RvaF1Handle()
	{
		if (m_p) ReleaseTreeHintRef00217D4C((TargetRef00217D4C *)m_p);
	}
	operator const TreeHintRef00217D4C &() const
	{
		return *(const TreeHintRef00217D4C *)this;
	}
};
RvaF1Handle Rva005FB46FCreate(const void *input);

class Rva002BC1DAUnit
{
public:
	unsigned char m_pad00[0x18];
	StringBase<char> m_templateName;	// +0x18
};

#include "../../Include/GameLogic/LivingWorldBattle.h"

#include "../../Include/GameLogic/Rva003F4DCA.h"

class Rva005FFED5 { public: void rva005FFED5(int value); };
class Rva005FFEDD { public: void rva005FFEDD(const TreeHintRef00217D4C &prompt); };
class Rva005FFEE5 { public: int rva005FFEE5(const TreeHintRef00217D4C &prompt); };

class Rva006003FC
{
public:
	Rva006003FC(void *a, void *b, void *c);
	virtual ~Rva006003FC();
protected:
	int m_04;
	unsigned char m_list08[0xC];		// +0x08
	LivingWorldBattle *m_battle;		// +0x14
	int m_side;				// +0x18
	int m_army;				// +0x1C
};

class Rva005FB204 : public Rva006003FC
{
public:
	Rva005FB204(unsigned int a, unsigned int b, void *c);
	virtual ~Rva005FB204();
};

Rva005FB204::Rva005FB204(unsigned int a, unsigned int b, void *c)
	: Rva006003FC((void *)a, (void *)b, c)
{
	((Rva005FFED5 *)m_list08)->rva005FFED5(1);
	LivingWorldBattle *battle = m_battle;
	int side = m_side;
	int army = m_army;
	int count = ((Rva003F4DCA *)battle)->rva003F4DCA(side, army);
	for (int i = 0; i < count; ++i)
	{
		Rva002BC1DAUnit *unit = (Rva002BC1DAUnit *)battle->rva003F48FE(side, army, i);
		Rva002BC1DAUnit *payload = unit;
		RvaCloneResult<Rva005FB22B> prompt = Rva005FB29ACreate(&payload);
		if (!unit->m_templateName.isEmpty())
			((Rva005FFEE5 *)m_list08)->rva005FFEE5(prompt);
		else
			((Rva005FFEDD *)m_list08)->rva005FFEDD(prompt);
	}
}

// ??0Rva005FB3D9@@QAE@IIPAX@Z @0x005FB4DF 207B (EH, ret 0xC): the twin built
// by the rowed factory 0x005E9849, whose destructor 0x005FB3D9 and deleting
// destructor 0x005FB3E4 are rowed in RvaDerivedDtorTails.cpp (vtable
// 0x00C79F10). Same walk with list mode 2 and the prompt factory 0x005FB46F.
class Rva005FB3D9 : public Rva006003FC
{
public:
	Rva005FB3D9(unsigned int a, unsigned int b, void *c);
	virtual ~Rva005FB3D9();
};

Rva005FB3D9::Rva005FB3D9(unsigned int a, unsigned int b, void *c)
	: Rva006003FC((void *)a, (void *)b, c)
{
	((Rva005FFED5 *)m_list08)->rva005FFED5(2);
	LivingWorldBattle *battle = m_battle;
	int side = m_side;
	int army = m_army;
	int count = ((Rva003F4DCA *)battle)->rva003F4DCA(side, army);
	for (int i = 0; i < count; ++i)
	{
		Rva002BC1DAUnit *unit = (Rva002BC1DAUnit *)battle->rva003F48FE(side, army, i);
		Rva002BC1DAUnit *payload = unit;
		RvaF1Handle prompt = Rva005FB46FCreate(&payload);
		if (!unit->m_templateName.isEmpty())
			((Rva005FFEE5 *)m_list08)->rva005FFEE5(prompt);
		else
			((Rva005FFEDD *)m_list08)->rva005FFEDD(prompt);
	}
}

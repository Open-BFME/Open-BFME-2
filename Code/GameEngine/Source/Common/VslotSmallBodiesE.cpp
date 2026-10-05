// cl: /O1 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch E. As in VslotSmallBodiesA-D, each class and method
// is address-derived and models only what its body touches; the comment above
// each gives the .rdata slot address(es) that reference it. Meanings are not
// recovered.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_pad00[0x40];
	UnsignedInt m_frame; // +0x40
};
extern GameLogic *TheGameLogic;

// slots at VA 0x00C433A0, 0x00C4401C, 0x00C45D1C, 0x00C46054, 0x00C46F68,
// 0x00C47314, 0x00C47868 and 0x00C48900: the embedded +0xA0 block while the
// +0xAC byte is set, else NULL.
struct Rva00462579Block
{
	char m_pad00[0x0C];
};
class Rva00462579
{
public:
	Rva00462579Block *rva00462579();
private:
	char m_pad00[0xA0];
	Rva00462579Block m_A0;
	Bool m_AC;
};
Rva00462579Block *Rva00462579::rva00462579()
{
	if (m_AC)
		return &m_A0;
	return 0;
}

// slot at VA 0x00C496E8: counts the +0x98 field down and, when it reaches
// zero, hands +0x1C to the embedded +0x18 object's first virtual; answers 1.
class Rva00482BB9Member
{
public:
	virtual void vslot00(void *arg);
};
class Rva00482BB9
{
public:
	Int rva00482BB9();
private:
	char m_pad00[0x18];
	Rva00482BB9Member m_18;
	char m_1C[0x98 - 0x1C];
	Int m_98;
};
Int Rva00482BB9::rva00482BB9()
{
	Int *count = &m_98;
	if (*count > 0 && --*count == 0)
		m_18.vslot00(m_1C);
	return 1;
}

// slot at VA 0x00C49AFC: both +0x24 and +0x28 become TheGameLogic's frame
// plus the +0x04 object's +0x08 delay.
struct Rva00483BA3Data
{
	char m_pad00[0x08];
	UnsignedInt m_08;
};
class Rva00483BA3
{
public:
	void rva00483BA3();
private:
	char m_pad00[0x04];
	const Rva00483BA3Data *m_04;
	char m_pad08[0x24 - 0x08];
	UnsignedInt m_24;
	UnsignedInt m_28;
};
void Rva00483BA3::rva00483BA3()
{
	UnsignedInt now = TheGameLogic->getFrame();
	m_24 = m_04->m_08 + now;
	m_28 = m_24;
}

// slot at VA 0x00C4B4C4 (a state's onExit, its status unused): the owner's
// AI interface (+0x258 of the machine owner) passes its vslot 93 result's
// vslot 24 a turn when both exist.
class Rva004885B8Target
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
	virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
	virtual void vslot06(); virtual void vslot07(); virtual void vslot08();
	virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(); virtual void vslot13(); virtual void vslot14();
	virtual void vslot15(); virtual void vslot16(); virtual void vslot17();
	virtual void vslot18(); virtual void vslot19(); virtual void vslot20();
	virtual void vslot21(); virtual void vslot22(); virtual void vslot23();
	virtual void vslot24();
};
template <int N> class Rva004885B8Slots : public Rva004885B8Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <> class Rva004885B8Slots<0>
{
};
class Rva004885B8AI : public Rva004885B8Slots<93>
{
public:
	virtual Rva004885B8Target *vslot93();
	virtual void vslot94();
	virtual void vslot95();
	virtual void vslot96();
	virtual void vslot97();
	virtual void vslot98();
	virtual void vslot99();
	virtual Rva004885B8Target *vslot100();
};
struct Rva004885B8Owner
{
	char m_pad00[0x258];
	Rva004885B8AI *m_ai;
};
struct Rva004885B8Machine
{
	char m_pad00[0x14];
	Rva004885B8Owner *m_owner;
};
class Rva004885B8
{
public:
	void rva004885B8(Int status);
	Int rva004A6C30();
private:
	char m_pad00[0x18];
	Rva004885B8Machine *m_machine;
};
void Rva004885B8::rva004885B8(Int status)
{
	Rva004885B8AI *ai = m_machine->m_owner->m_ai;
	if (ai)
	{
		Rva004885B8Target *target = ai->vslot93();
		if (target)
			target->vslot24();
	}
}

// slot at VA 0x00C53270 (a state's onEnter): with an owner and its AI
// interface, runs vslot 0 of the AI's vslot 100 result when there is one;
// answers 0 (continue). Same owner/AI path as 0x004885B8.
Int Rva004885B8::rva004A6C30()
{
	Rva004885B8Owner *owner = m_machine->m_owner;
	if (owner)
	{
		Rva004885B8AI *ai = owner->m_ai;
		if (ai)
		{
			Rva004885B8Target *target = ai->vslot100();
			if (target)
				target->vslot00();
		}
	}
	return 0;
}

// slot at VA 0x00C4B578 (a state's onEnter): stamps TheGameLogic's frame at
// +0x20, clears the +0x28 byte and answers 0 (continue).
class Rva0048872D
{
public:
	Int rva0048872D();
private:
	char m_pad00[0x20];
	UnsignedInt m_20;
	char m_pad24[0x28 - 0x24];
	Bool m_28;
};
Int Rva0048872D::rva0048872D()
{
	m_20 = TheGameLogic->getFrame();
	m_28 = false;
	return 0;
}

// slot at VA 0x00C4B4B0 slot 4 (offset 0x10) of Rva00488545 (vtable 0x0084B4B0,
// class of ??0Rva00488545@@QAE@PAVStateMachine@@H@Z from AIStateHashCtorsMisc):
// runs AI vslot93, answers -2 when null, else stamps TheGameLogic frame at
// +0x24 and runs target vslot18(0) when +0x20 is 0 or 1, answers 0.
// Evidence: +0x18/+0x14/+0x258 AI path and vslot93/frame+0x40 same as 0x004885B8,
// m_20 at +0x20 and m_24 at +0x24 match Rva00488545 layout, ret void with -2/0.
class Rva00488573Target : public Rva004885B8Slots<18>
{
public:
	virtual void vslot18(Int arg);
};
class Rva00488545
{
public:
	Int rva00488573();
private:
	char m_pad00[0x18];
	Rva004885B8Machine *m_machine;
	char m_pad1C[0x20 - 0x1C];
	Int m_20;
	UnsignedInt m_24;
};

Int Rva00488545::rva00488573()
{
	Rva004885B8AI *ai = m_machine->m_owner->m_ai;
	Rva00488573Target *target = (Rva00488573Target *)ai->vslot93();
	if (!target)
		return -2;
	m_24 = TheGameLogic->getFrame();
	Int status = m_20;
	if (status == 0 || status == 1)
		target->vslot18(0);
	return 0;
}

// slot at VA 0x00C4B568 slot 5 (offset 0x14) of Rva004886C7 (vtable 0x0084B568,
// class of ??0Rva004886C7@@QAE@PAVStateMachine@@@Z from AIStateHashCtorsMisc):
// when +0x28 is set runs InGameUI vslot106 with owner and +0x24 then stamps
// +0x24 to -1 and clears +0x28. Evidence: ret 4 with unused arg, TheInGameUI
// at VA 0x009FEDF0, or -1 and bool clear, same machine/owner path as above.
class InGameUI : public Rva004885B8Slots<106>
{
public:
	virtual void vslot106(Rva004885B8Owner *owner, Int val);
};
extern InGameUI *TheInGameUI;
class Rva004886C7
{
public:
	void rva0048873F(Int arg);
private:
	char m_pad00[0x18];
	Rva004885B8Machine *m_machine;
	char m_pad1C[0x24 - 0x1C];
	Int m_24;
	Bool m_28;
};

void Rva004886C7::rva0048873F(Int arg)
{
	if (!m_28)
		return;
	TheInGameUI->vslot106(m_machine->m_owner, m_24);
	m_24 |= -1;
	m_28 = false;
}

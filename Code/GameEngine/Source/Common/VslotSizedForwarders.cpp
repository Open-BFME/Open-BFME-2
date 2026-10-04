// cl: /O1 /DNDEBUG /MD
//
// Vtable-slot forwarders with no ledger owner and no Ghidra size, generated
// by tools/slot_forwarders.py (family vjmp). Each body was sized from its
// bytes (a branch-free hop ending in jmp, followed by a known boundary).
// Every class and method here is address-derived: the bytes prove the hop
// and the slot or callee, nothing more. A tail-jumped virtual slot passes
// the caller's arguments through untouched, so its argument count is not
// provable and the slot is declared without arguments (inference).
// A direct callee's argument count comes from its own ret N; an unnamed
// callee is pinned by address in reverse/symbols.csv.

typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int UnsignedInt;

class SizedForwarderSlots
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual void slot70();
	virtual void slot71();
	virtual void slot72();
	virtual void slot73();
	virtual void slot74();
	virtual void slot75();
	virtual void slot76();
	virtual void slot77();
	virtual void slot78();
	virtual void slot79();
	virtual void slot80();
	virtual void slot81();
	virtual void slot82();
	virtual void slot83();
	virtual void slot84();
	virtual void slot85();
	virtual void slot86();
	virtual void slot87();
	virtual void slot88();
	virtual void slot89();
	virtual void slot90();
	virtual void slot91();
	virtual void slot92();
	virtual void slot93();
	virtual void slot94();
	virtual void slot95();
	virtual void slot96();
	virtual void slot97();
	virtual void slot98();
	virtual void slot99();
	virtual void slot100();
	virtual void slot101();
	virtual void slot102();
	virtual void slot103();
	virtual void slot104();
	virtual void slot105();
	virtual void slot106();
	virtual void slot107();
	virtual void slot108();
	virtual void slot109();
	virtual void slot110();
	virtual void slot111();
	virtual void slot112();
	virtual void slot113();
	virtual void slot114();
	virtual void slot115();
	virtual void slot116();
	virtual void slot117();
	virtual void slot118();
	virtual void slot119();
	virtual void slot120();
	virtual void slot121();
	virtual void slot122();
	virtual void slot123();
	virtual void slot124();
	virtual void slot125();
	virtual void slot126();
	virtual void slot127();
	virtual void slot128();
	virtual void slot129();
	virtual void slot130();
	virtual void slot131();
	virtual void slot132();
};

class Rva000512BCForwarder : public SizedForwarderSlots
{
public:
	void rva000512BC();
};

// vtable 0x00BC55B0#96: this->slot94()
void Rva000512BCForwarder::rva000512BC()
{
	slot94();
}

class Rva00078AC6Forwarder
{
public:
	void rva00078AC6();
private:
	char m_lead[0x4];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00BCBC40#60 (??_7Rva000CA119@@6BRva000C79C9@@@): (+0x4)->slot30()
void Rva00078AC6Forwarder::rva00078AC6()
{
	m_inner->slot30();
}

class Rva0008605ALead
{
public:
	virtual void lead0();
private:
	char m_lead[0xB0];
};

class Rva0008605AForwarder : public Rva0008605ALead, public SizedForwarderSlots
{
public:
	void rva0008605A();
};

// vtable 0x00BC7568#94: base at +0xB4 ->slot12()
void Rva0008605AForwarder::rva0008605A()
{
	slot12();
}

class Rva0008615BLead
{
public:
	virtual void lead0();
private:
	char m_lead[0x24C4];
};

class Rva0008615BForwarder : public Rva0008615BLead, public SizedForwarderSlots
{
public:
	void rva0008615B();
};

// vtable 0x00BC7568#58: base at +0x24C8 ->slot1()
void Rva0008615BForwarder::rva0008615B()
{
	slot1();
}

class Rva0008BD2BLead
{
public:
	virtual void lead0();
private:
	char m_lead[0x24C4];
};

class Rva0008BD2BForwarder : public Rva0008BD2BLead, public SizedForwarderSlots
{
public:
	void rva0008BD2B();
};

// vtable 0x00BC7568#138: base at +0x24C8 ->slot20()
void Rva0008BD2BForwarder::rva0008BD2B()
{
	slot20();
}

class Rva00091D32Forwarder
{
public:
	void rva00091D32();
private:
	char m_lead[0x14];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00BC80A0#5: (+0x14)->slot132()
void Rva00091D32Forwarder::rva00091D32()
{
	m_inner->slot132();
}

class Rva000ABD68Forwarder
{
public:
	void rva000ABD68();
private:
	char m_lead[0x4];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00BC957C#0 (??_7Rva000ABD56@@6B@): (+0x4)->slot3()
void Rva000ABD68Forwarder::rva000ABD68()
{
	m_inner->slot3();
}

class Rva001EDDBBForwarder
{
public:
	void rva001EDDBB();
private:
	char m_lead[0x4FA8];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00BE0358#9 (??_7Rva001EE3DE@@6B@): (+0x4FA8)->slot5()
void Rva001EDDBBForwarder::rva001EDDBB()
{
	m_inner->slot5();
}

class Rva0024002ELead
{
public:
	virtual void lead0();
private:
	char m_lead[0xC];
};

class Rva0024002EForwarder : public Rva0024002ELead, public SizedForwarderSlots
{
public:
	void rva0024002E();
};

// vtable 0x00BEDCB4#0: base at +0x10 ->slot0()
void Rva0024002EForwarder::rva0024002E()
{
	slot0();
}

class Rva00240035Lead
{
public:
	virtual void lead0();
private:
	char m_lead[0xC];
};

class Rva00240035Forwarder : public Rva00240035Lead, public SizedForwarderSlots
{
public:
	void rva00240035();
};

// vtable 0x00BEDCB4#1: base at +0x10 ->slot1()
void Rva00240035Forwarder::rva00240035()
{
	slot1();
}

class Rva0024003DLead
{
public:
	virtual void lead0();
private:
	char m_lead[0xC];
};

class Rva0024003DForwarder : public Rva0024003DLead, public SizedForwarderSlots
{
public:
	void rva0024003D();
};

// vtable 0x00BEDCB4#2: base at +0x10 ->slot2()
void Rva0024003DForwarder::rva0024003D()
{
	slot2();
}

class Rva0025C25AForwarder : public SizedForwarderSlots
{
public:
	void rva0025C25A();
};

// vtable 0x00BF5DA0#12 (??_7BfmeStrVM0@@6B@): this->slot38()
void Rva0025C25AForwarder::rva0025C25A()
{
	slot38();
}

class Rva0029AC98Forwarder : public SizedForwarderSlots
{
public:
	void rva0029AC98();
};

// vtable 0x00BC7A88#83: this->slot67()
void Rva0029AC98Forwarder::rva0029AC98()
{
	slot67();
}

class Rva0030ADE8Forwarder : public SizedForwarderSlots
{
public:
	void rva0030ADE8();
};

// vtable 0x00BC8318#1 (??_7Rva00985E4@@6B@): this->slot14()
void Rva0030ADE8Forwarder::rva0030ADE8()
{
	slot14();
}

class Rva00328CC5Forwarder
{
public:
	void rva00328CC5();
private:
	char m_lead[0x18];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00C0D8D8#2: (+0x18)->slot0()
void Rva00328CC5Forwarder::rva00328CC5()
{
	m_inner->slot0();
}

class Rva00328CCCForwarder
{
public:
	void rva00328CCC();
private:
	char m_lead[0xC];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00C0D8E4#2: (+0xC)->slot1()
void Rva00328CCCForwarder::rva00328CCC()
{
	m_inner->slot1();
}

class Rva0039AC9CForwarder
{
public:
	void rva0039AC9C();
private:
	char m_lead[0x2C];
	SizedForwarderSlots *m_inner;
};

// vtable 0x00C1AD20#1 (??_7Rva0039AD56@@6B@): (+0x2C)->slot1()
void Rva0039AC9CForwarder::rva0039AC9C()
{
	m_inner->slot1();
}

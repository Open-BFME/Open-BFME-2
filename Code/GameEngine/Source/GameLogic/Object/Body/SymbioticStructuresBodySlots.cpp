// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// SymbioticStructuresBody overrides in the vtables its matched ctor 0x004C0AF1
// installs over ActiveBody: primary 0x00C5B830, +0x0C 0x00C5B770 and the body
// interface at +0x10 (0x00C5B6C0). The +0x10 slots are compiled with that
// subobject this. Names are by address.
//
// The float queries hand the same question to the host body module kept at
// +0x100 (its body interface at +0x10) when the rowed Rva004C0D4F check holds
// (after the pinned refresh 0x004C0C52 for slot 5 and primary slot 24), else
// answer 0. Primary slot 24 asks the host's body-interface slot 4.

class Object;
class ModuleData;

template <int N> class Rva004C0D13Slots : public Rva004C0D13Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva004C0D13Slots<1>
{
public:
	virtual void gap(char (*)[1]) = 0;
};

class BfmeOwnFCB
{
public:
	void bfmeAfterFCB();
};

class Rva004C0D4F
{
public:
	bool rva004C0D4F();
};

class BfmeSubFCB
{
public:
	void bfmeCallFCB(void *a1, int a2);
};

class BodyModuleInterface : public Rva004C0D13Slots<4>
{
public:
	virtual float rva004C0D9CSlot4() = 0;
	virtual float rva004C0D13() = 0;
	virtual float rva004C105A() = 0;
	virtual float rva004C108B() = 0;
	virtual void gap8() = 0; virtual void gap9() = 0; virtual void gap10() = 0; virtual void gap11() = 0;
	virtual void gap12() = 0; virtual void gap13() = 0; virtual void gap14() = 0; virtual void gap15() = 0;
	virtual void gap16() = 0; virtual void gap17() = 0; virtual void gap18() = 0; virtual void gap19() = 0;
	virtual void gap20() = 0; virtual void gap21() = 0; virtual void gap22() = 0; virtual void gap23() = 0;
	virtual void gap24() = 0; virtual void gap25() = 0; virtual void gap26() = 0;
	virtual float rva004C0DF3() = 0;
	virtual void gap28() = 0; virtual void gap29() = 0; virtual void gap30() = 0; virtual void gap31() = 0;
	virtual void gap32() = 0; virtual void gap33() = 0; virtual void gap34() = 0; virtual void gap35() = 0;
	virtual void gap36() = 0; virtual void gap37() = 0; virtual void gap38() = 0;
	virtual void rva004C121B(void *a1) = 0;
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

struct Rva004C0B60Arg
{
	int m_words[32];
};

class BehaviorModule : public Rva004C0D13Slots<23>
{
public:
	virtual void rva004C0B60(Rva004C0B60Arg arg) = 0;
	virtual float rva004C0D9C() = 0;
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

// The host's body module: the same module shape with its body interface at
// +0x10.
class HostBodyModule : public BehaviorModule, public BehaviorModuleInterface, public BodyModuleInterface
{
};

class ActiveBody : public BehaviorModule, public BehaviorModuleInterface, public BodyModuleInterface
{
protected:
	unsigned char m_pad014[0x100 - 0x14];
};

class SymbioticStructuresBody : public ActiveBody
{
public:
	virtual void rva004C0B60(Rva004C0B60Arg arg);
	virtual float rva004C0D9C();
	virtual float rva004C0D13();
	virtual float rva004C105A();
	virtual float rva004C108B();
	virtual float rva004C0DF3();
	virtual void rva004C121B(void *a1);
private:
	BfmeOwnFCB *refresher() { return (BfmeOwnFCB *)(BehaviorModule *)this; }
	Rva004C0D4F *checker() { return (Rva004C0D4F *)(BehaviorModule *)this; }
	HostBodyModule *m_host; // +0x100
};

// ?rva004C0B60@SymbioticStructuresBody@@UAEXURva004C0B60Arg@@@Z, retail 0x004C0B60,
// 3 bytes: primary slot 23, a no-op taking a 0x80-byte argument by value.
void SymbioticStructuresBody::rva004C0B60(Rva004C0B60Arg)
{
}

// ?rva004C0D9C@SymbioticStructuresBody@@UAEMXZ, retail 0x004C0D9C, 53 bytes:
// primary slot 24.
float SymbioticStructuresBody::rva004C0D9C()
{
	refresher()->bfmeAfterFCB();
	return checker()->rva004C0D4F() ? m_host->rva004C0D9CSlot4() : 0.0f;
}

// ?rva004C0D13@SymbioticStructuresBody@@UAEMXZ, retail 0x004C0D13, 60 bytes: body
// interface slot 5.
float SymbioticStructuresBody::rva004C0D13()
{
	refresher()->bfmeAfterFCB();
	return checker()->rva004C0D4F() ? m_host->rva004C0D13() : 0.0f;
}

// ?rva004C105A@SymbioticStructuresBody@@UAEMXZ, retail 0x004C105A, 49 bytes: body
// interface slot 6.
float SymbioticStructuresBody::rva004C105A()
{
	return checker()->rva004C0D4F() ? m_host->rva004C105A() : 0.0f;
}

// ?rva004C108B@SymbioticStructuresBody@@UAEMXZ, retail 0x004C108B, 49 bytes: body
// interface slot 7.
float SymbioticStructuresBody::rva004C108B()
{
	return checker()->rva004C0D4F() ? m_host->rva004C108B() : 0.0f;
}

// ?rva004C0DF3@SymbioticStructuresBody@@UAEMXZ, retail 0x004C0DF3, 49 bytes: body
// interface slot 27.
float SymbioticStructuresBody::rva004C0DF3()
{
	return checker()->rva004C0D4F() ? m_host->rva004C0DF3() : 0.0f;
}

// ?rva004C121B@SymbioticStructuresBody@@UAEXPAX@Z, retail 0x004C121B, 33 bytes:
// body interface slot 39; with an owning Object, the pinned
// BfmeSubFCB::bfmeCallFCB(argument, 0) on it, then the pinned refresh.
void SymbioticStructuresBody::rva004C121B(void *a1)
{
	Object *obj = m_object;
	if (obj)
	{
		((BfmeSubFCB *)obj)->bfmeCallFCB(a1, 0);
		refresher()->bfmeAfterFCB();
	}
}

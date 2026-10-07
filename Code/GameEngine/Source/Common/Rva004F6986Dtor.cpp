// cl: /EHsc
// ??1Rva004F6986@@QAE@XZ, retail 0x004F6986, 61 bytes.
// Dtor of 8-byte holder with two inline member dtors each releasing TargetRef via rowed fastcall 0x0007DEEF with EH.
// Evidence: destroy-loop caller 0x004F8373 stride 8 plus 0x004F6E2B 0x004F9C50 plus jmp 0x004F73E5 and Unwind 0x00793281; prev copy ctor 0x004F6966 next dtor 0x004F69C3 both /O1.

struct TargetRef00217D4C
{
	virtual void *destroy(unsigned int flags);
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva004F6986Member
{
	Rva004F6986Member(const Rva004F6986Member &that) : m_ptr(that.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	~Rva004F6986Member()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

struct Rva004F6986
{
	~Rva004F6986();
	Rva004F6986Member m_00;
	Rva004F6986Member m_04;
};

Rva004F6986::~Rva004F6986()
{
}

// Two more 8-byte holders of two TargetRef handles whose destructors match
// ??1Rva004F6986's bytes but for the EH handler record. Owners keep their
// addresses.

// ??1Rva0044BA4E@@QAE@XZ, retail 0x0044BA4E, 61 bytes.
// ??0Rva0044BA4E, retail 0x0044BCAB, 85 bytes: builds the holder from two
// handles taken by value -- each member copy adds a reference, then the
// callee-destroyed arguments release theirs (EH state 0 covers the second).
// Callers 0x0044C042 0x0044C19F 0x0051615A 0x005176B9 0x00517E11 0x005B6B24.
struct Rva0044BA4E
{
	Rva0044BA4E(Rva004F6986Member first, Rva004F6986Member second);
	~Rva0044BA4E();
	Rva004F6986Member m_00;
	Rva004F6986Member m_04;
};

Rva0044BA4E::Rva0044BA4E(Rva004F6986Member first, Rva004F6986Member second) : m_00(first), m_04(second)
{
}

Rva0044BA4E::~Rva0044BA4E()
{
}

// ??1Rva005F8447@@QAE@XZ, retail 0x005F8447, 61 bytes.
struct Rva005F8447
{
	~Rva005F8447();
	Rva004F6986Member m_00;
	Rva004F6986Member m_04;
};

Rva005F8447::~Rva005F8447()
{
}

// ?rva005F842F@Rva005F842F@@QAEPAU1@ABURva004F6986Member@@@Z @0x005F842F 24B
// Init 8-byte holder: first handle null plus second handle copied from single
// member with AddRef. Evidence: retail zeroes [+0] plus copies [arg+0] to [+4]
// with inc [ptr+4] guard; caller 0x005F888C builds temp at [ebp-0x14] from
// [ebp+8] then push_back plus dtor 0x005F8447; prev 0x005F8427 next 0x005F8447.
struct Rva005F842F
{
	Rva005F842F *rva005F842F(const Rva004F6986Member &src);
	Rva004F6986Member m_00;
	Rva004F6986Member m_04;
};

Rva005F842F *Rva005F842F::rva005F842F(const Rva004F6986Member &src)
{
	m_00.m_ptr = 0;
	m_04.m_ptr = src.m_ptr;
	if (m_04.m_ptr)
		++m_04.m_ptr->references;
	return this;
}

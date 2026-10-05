// Eight helper-then-member steps (17B each): push esi, mov esi, ecx,
// call <helper>, mov ecx, [esi+off], pop esi, jmp <run>. Each runs a
// no-argument helper on this, then tail-jumps the run method of the owned
// pointer at its offset:
// 0x005D1516 (+0x08, fold-nop helper, -> 0x005D13C2),
// 0x005E1906 (+0x0C, rowed Overridable::markAsOverride, -> 0x005E18D0),
// 0x005E1917 (+0x0C, rowed Rva00420B2AZeroSetter::disable, -> 0x005E18DC),
// 0x005E1BC4 (+0x0C, fold-nop helper, -> 0x005E1B9A),
// 0x005E25DE (+0x0C, fold-nop helper, -> 0x005E254C),
// 0x005E590F (+0x08, fold-nop helper, -> 0x005E589E),
// 0x005E6BA3 (+0x20, fold-nop helper, -> 0x005E6A9D),
// 0x005E6BB4 (+0x20, fold-nop helper, -> 0x005E6AD8).
// The fold-nop helper shares one opaque alias pin at 0x000B3FD0 (the known
// folded empty body); run/member/owner identities unproven (opaque run
// pins); names are address-derived. One ledger row per step.

class Overridable
{
public:
	void markAsOverride();
};

class Rva00420B2AZeroSetter
{
public:
	void disable();
};

class Rva000B3FD0Nop
{
public:
	void noop();
};

class Rva005D13C2Run
{
public:
	void run();
};

class Rva005E18D0Run
{
public:
	void run();
};

class Rva005E18DCRun
{
public:
	void run();
};

class Rva005E1B9ARun
{
public:
	void run();
};

class Rva005E254CRun
{
public:
	void run();
};

class Rva005E589ERun
{
public:
	void run();
};

class Rva005E6A9DRun
{
public:
	void run();
};

class Rva005E6AD8Run
{
public:
	void run();
};

class Rva005D1516
{
public:
	void step();

private:
	char m_pad[8];
	Rva005D13C2Run *m_next;
};

class Rva005E1906
{
public:
	void step();

private:
	char m_pad[0x0C];
	Rva005E18D0Run *m_next;
};

class Rva005E1917
{
public:
	void step();

private:
	char m_pad[0x0C];
	Rva005E18DCRun *m_next;
};

class Rva005E1BC4
{
public:
	void step();

private:
	char m_pad[0x0C];
	Rva005E1B9ARun *m_next;
};

class Rva005E25DE
{
public:
	void step();

private:
	char m_pad[0x0C];
	Rva005E254CRun *m_next;
};

class Rva005E590F
{
public:
	void step();

private:
	char m_pad[8];
	Rva005E589ERun *m_next;
};

class Rva005E6BA3
{
public:
	void step();

private:
	char m_pad[0x20];
	Rva005E6A9DRun *m_next;
};

class Rva005E6BB4
{
public:
	void step();

private:
	char m_pad[0x20];
	Rva005E6AD8Run *m_next;
};

void Rva005D1516::step()
{
	((Rva000B3FD0Nop *)this)->noop();
	m_next->run();
}

void Rva005E1906::step()
{
	((Overridable *)this)->markAsOverride();
	m_next->run();
}

void Rva005E1917::step()
{
	((Rva00420B2AZeroSetter *)this)->disable();
	m_next->run();
}

void Rva005E1BC4::step()
{
	((Rva000B3FD0Nop *)this)->noop();
	m_next->run();
}

void Rva005E25DE::step()
{
	((Rva000B3FD0Nop *)this)->noop();
	m_next->run();
}

void Rva005E590F::step()
{
	((Rva000B3FD0Nop *)this)->noop();
	m_next->run();
}

void Rva005E6BA3::step()
{
	((Rva000B3FD0Nop *)this)->noop();
	m_next->run();
}

void Rva005E6BB4::step()
{
	((Rva000B3FD0Nop *)this)->noop();
	m_next->run();
}

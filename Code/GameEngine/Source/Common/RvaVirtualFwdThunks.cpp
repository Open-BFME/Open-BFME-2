// Seven retail virtual-forward thunks (7-8B each). Retail shape per member:
// mov ecx, [ecx+adj], mov eax, [ecx], jmp [eax+slot]. Each forwards through
// a pointer owned at a fixed displacement from this to one virtual slot:
// 0x005E6817: adj +4, slot 0x00 (1st); 0x005E681E: adj +4, slot 0x18 (7th);
// 0x005E6826: adj +4, slot 0x14 (6th); 0x005E682E: adj +4, slot 0x10 (5th);
// 0x005E6836: adj +4, slot 0x08 (3rd);
// 0x005E683E: adj +4, slot 0x04 (2nd, two stack args from callers 0x005CE130 0x005CE804);
// 0x005E3AA2: adj -8 (pointer kept 8 below this), slot 0x0C (4th).
// Slot/owner identities unproven; names are address-derived.
// One ledger row per thunk.

class Rva005E6817Outer
{
public:
	virtual void slot0();
};

class Rva005E681EOuter
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
};

class Rva005E6826Outer
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
};

class Rva005E682EOuter
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
};

class Rva005E6836Outer
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
};

class Rva005E683EOuter
{
public:
	virtual void slot0();
	virtual void slot1(int a, int b);
};

class Rva005E3AA2Outer
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
};

class Rva005E6817Mid
{
public:
	void fwd();

private:
	unsigned m_00;
	Rva005E6817Outer *m_outer;
};

class Rva005E681EMid
{
public:
	void fwd();

private:
	unsigned m_00;
	Rva005E681EOuter *m_outer;
};

class Rva005E6826Mid
{
public:
	void fwd();

private:
	unsigned m_00;
	Rva005E6826Outer *m_outer;
};

class Rva005E682EMid
{
public:
	void fwd();

private:
	unsigned m_00;
	Rva005E682EOuter *m_outer;
};

class Rva005E6836Mid
{
public:
	void fwd();

private:
	unsigned m_00;
	Rva005E6836Outer *m_outer;
};

class Rva005E683EMid
{
public:
	void fwd(int a, int b);

private:
	unsigned m_00;
	Rva005E683EOuter *m_outer;
};

class Rva005E3AA2Mid
{
public:
	void fwd();
};

void Rva005E6817Mid::fwd()
{
	m_outer->slot0();
}

void Rva005E681EMid::fwd()
{
	m_outer->slot6();
}

void Rva005E6826Mid::fwd()
{
	m_outer->slot5();
}

void Rva005E682EMid::fwd()
{
	m_outer->slot4();
}

void Rva005E6836Mid::fwd()
{
	m_outer->slot2();
}

void Rva005E683EMid::fwd(int a, int b)
{
	m_outer->slot1(a, b);
}

void Rva005E3AA2Mid::fwd()
{
	Rva005E3AA2Outer *outer = *(Rva005E3AA2Outer *const *)((char *)this - 8);
	outer->slot3();
}

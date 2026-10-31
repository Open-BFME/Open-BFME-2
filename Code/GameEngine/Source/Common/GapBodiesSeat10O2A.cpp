// Small unrowed .text bodies from the 0x00654850..0x00681AAF (/O2) region.
// Retail bytes establish every shape; no caller is recovered and the owning
// classes are unknown, so each keeps an address-derived name and a view of
// only the fields it touches. Callees are the rowed bodies the jmp targets.

// ?rva0066D4F0@Rva0066D4F0@@QAEXH@Z @0x0066D4F0 10B: store the argument at +0x4C.
class Rva0066D4F0
{
public:
	void rva0066D4F0(int value);
private:
	char m_pad[0x4c];
	int m_4c;
};
void Rva0066D4F0::rva0066D4F0(int value)
{
	m_4c = value;
}

// Destructors whose only non-trivial member is a BfmeMsg (rowed virtual
// ??1BfmeMsg@@UAE@XZ 0x00655780, called directly for a member).
class BfmeMsg
{
public:
	virtual ~BfmeMsg();
};

// ??1Rva00665970@@QAE@XZ @0x00665970 8B: BfmeMsg member at +0x14.
class Rva00665970
{
public:
	~Rva00665970();
private:
	char m_pad[0x14];
	BfmeMsg m_14;
};
Rva00665970::~Rva00665970()
{
}

// ??1Rva0066CAC0@@QAE@XZ @0x0066CAC0 8B: BfmeMsg member at +0x10.
class Rva0066CAC0
{
public:
	~Rva0066CAC0();
private:
	char m_pad[0x10];
	BfmeMsg m_10;
};
Rva0066CAC0::~Rva0066CAC0()
{
}

// ?rva00674BA0@Rva00674BA0@@QBEPAXXZ @0x00674BA0 11B: rowed lea-field getter
// 0x0066D7D0 on the object at +0x0C of the object held at +0x08.
class Rva0066D7D0LeaField
{
public:
	void *get() const;
};
struct Rva00674BA0Inner
{
	char m_pad[0x0c];
	Rva0066D7D0LeaField *m_0c;
};
class Rva00674BA0
{
public:
	void *rva00674BA0() const;
private:
	char m_pad[0x08];
	Rva00674BA0Inner *m_08;
};
void *Rva00674BA0::rva00674BA0() const
{
	return m_08->m_0c->get();
}

// ?rva0066CA80@Rva0066CA80@@QAEXXZ @0x0066CA80 5B (called from 0x006661DA):
// clear the chain member at +0 through the rowed Rva00800550Chain::clear
// 0x0066C970.
class Rva00800550Chain
{
public:
	void clear();
};
class Rva0066CA80
{
public:
	void rva0066CA80();
private:
	Rva00800550Chain m_chain;
};
void Rva0066CA80::rva0066CA80()
{
	m_chain.clear();
}

// ??0Rva00665B70@@QAE@XZ @0x00665B70 13B: default constructor zeroing three words.
class Rva00665B70
{
public:
	Rva00665B70();
private:
	int m_00;
	int m_04;
	int m_08;
};

// ?rva00674A20@Rva00674A20@@QAEHXZ @0x00674A20 8B: post-increment of the +0
// counter, returning the old value.
class Rva00674A20
{
public:
	int rva00674A20();
private:
	int m_00;
};
int Rva00674A20::rva00674A20()
{
	return m_00++;
}

// Tail jumps to a rowed member of the object at +0.
// ??1Rva00661860@@QAE@XZ @0x00661860 5B: BfmeMsg member dtor 0x00655780.
class Rva00661860
{
public:
	~Rva00661860();
private:
	BfmeMsg m_msg;
};
Rva00661860::~Rva00661860()
{
}
class Rva00801570 { public: void clear(); };
class Rva00801600 { public: void clear(); };
class Rva00802A10 { public: void clear(); };
// ?rva0066DF00@Rva0066DF00@@QAEXXZ @0x0066DF00 5B: rowed Rva00801570::clear 0x0066D890.
class Rva0066DF00
{
public:
	void rva0066DF00();
private:
	Rva00801570 m_00;
};
void Rva0066DF00::rva0066DF00()
{
	m_00.clear();
}
// ?rva0066E260@Rva0066E260@@QAEXXZ @0x0066E260 5B: rowed Rva00801600::clear 0x0066D900.
class Rva0066E260
{
public:
	void rva0066E260();
private:
	Rva00801600 m_00;
};
void Rva0066E260::rva0066E260()
{
	m_00.clear();
}
// ?rva0066EDA0@Rva0066EDA0@@QAEXXZ @0x0066EDA0 5B: rowed Rva00802A10::clear 0x0066EB40.
class Rva0066EDA0
{
public:
	void rva0066EDA0();
private:
	Rva00802A10 m_00;
};
void Rva0066EDA0::rva0066EDA0()
{
	m_00.clear();
}

// cl: /O1 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry, batch
// AG: each calls a rowed function whose ledger name types its return (or
// convention) differently from what this call site needs, so the callee
// is bound through an alias pin in reverse/symbols.csv under an
// address-derived name (the rowed bodies answer 0/1 in eax, i.e. bool, and
// 0x0023C7F5 ignores ECX, so the thiscall spelling reaches the same
// bytes). As in VslotSmallBodiesA-AF, classes and methods are
// address-derived and model only what each body touches.

typedef int Int;
typedef float Real;

// 0x00131CF2 and 0x00151415 (texture tables): true when the +0x14 object's
// +0x08 (resp. +0x04) is set, else the rowed 0x00130FCE on this object.
struct Rva00131CF2Info
{
	Int m_00;
	Int m_04;
	Int m_08;
};
class Rva00130FCE
{
public:
	bool rva00130FCE();
};
class Rva00131CF2 : public Rva00130FCE
{
public:
	bool rva00131CF2();
	bool rva00151415();
private:
	char m_pad00[0x14];
	Rva00131CF2Info *m_14;
};
bool Rva00131CF2::rva00131CF2()
{
	Rva00131CF2Info *info = m_14;
	if (info && info->m_08)
		return true;
	return rva00130FCE();
}
bool Rva00131CF2::rva00151415()
{
	Rva00131CF2Info *info = m_14;
	if (info && info->m_04)
		return true;
	return rva00130FCE();
}

// 0x0057B97C: 1 when the +0x34 object exists and the rowed 0x005D4E6F
// holds for it, else 0.
class Rva005D4E6F
{
public:
	bool rva005D4E6F();
};
class Rva0057B97C
{
public:
	Int rva0057B97C();
private:
	char m_pad00[0x34];
	Rva005D4E6F *m_34;
};
Int Rva0057B97C::rva0057B97C()
{
	if (m_34 && m_34->rva005D4E6F())
		return 1;
	return 0;
}

// 0x003FF312: false while +0x10 is clear, else the rowed GameSlot
// 0x003FF145 of the +0x18 slot for the +0x38 address.
struct BfmeNetAddress;
class Rva003FF145
{
public:
	bool rva003FF145(const BfmeNetAddress *address) const;
};
class Rva003FF312
{
public:
	bool rva003FF312();
private:
	char m_pad00[0x10];
	bool m_10;
	char m_pad11[0x07];
	Rva003FF145 *m_18;
	char m_pad1C[0x1C];
	Int m_38;
};
bool Rva003FF312::rva003FF312()
{
	if (!m_10)
		return false;
	return m_18->rva003FF145((const BfmeNetAddress *)&m_38);
}

// 0x0023DAF7: the rowed 0x0023C7F5 with both arguments on the +0x08
// member.
class Rva0023C7F5
{
public:
	Int rva0023C7F5(Real a, Int b);
};
class Rva0023DAF7
{
public:
	void rva0023DAF7(Real a, Int b);
private:
	Int m_00;
	Int m_04;
	Rva0023C7F5 m_08;
};
void Rva0023DAF7::rva0023DAF7(Real a, Int b)
{
	m_08.rva0023C7F5(a, b);
}

// 0x005FEEC7 and 0x005FEEE6 (adjacent slots of table VA 0x00C7A454): each
// first runs the shared empty base slot 0x0047A69C (pinned there as
// Gen_003bcb40::m) with its index, then stores entry [index] of the +0x08
// object's +0x18 table into its +0x24, resp. resets +0x24 to 7 when it
// holds that entry.
class Gen_003bcb40
{
public:
	void m(Int index);
};
struct Rva005FEEC7Info
{
	char m_pad00[0x18];
	Int *m_18;
	char m_pad1C[0x08];
	Int m_24;
};
class Rva005FEEC7 : public Gen_003bcb40
{
public:
	void rva005FEEC7(Int index);
	void rva005FEEE6(Int index);
private:
	Int m_00;
	Int m_04;
	Rva005FEEC7Info *m_08;
};
void Rva005FEEC7::rva005FEEC7(Int index)
{
	m(index);
	m_08->m_24 = m_08->m_18[index];
}
void Rva005FEEC7::rva005FEEE6(Int index)
{
	m(index);
	if (m_08->m_24 == m_08->m_18[index])
		m_08->m_24 = 7;
}

// 0x005C4352 and 0x005C4553 (tables VA 0x00C745E0/0x00C746D8): field-parse
// builders: the shared empty base slot 0x0047A69C (alias-pinned here as a
// buildFieldParse), then the pinned MultiIniFieldParse::add of the table at
// VA 0x00C74540 (resp. 0x00C74630) with offset 0.
struct FieldParse;
class MultiIniFieldParse
{
public:
	void add(const FieldParse *table, unsigned int offset);
};
extern const FieldParse g_rva005C4352FieldParse[];
extern const FieldParse g_rva005C4553FieldParse[];
class Rva005C4352Base
{
public:
	void buildFieldParse(MultiIniFieldParse &p);
};
class Rva005C4352 : public Rva005C4352Base
{
public:
	void rva005C4352(MultiIniFieldParse &p);
	void rva005C4553(MultiIniFieldParse &p);
};
void Rva005C4352::rva005C4352(MultiIniFieldParse &p)
{
	buildFieldParse(p);
	p.add(g_rva005C4352FieldParse, 0);
}
void Rva005C4352::rva005C4553(MultiIniFieldParse &p)
{
	buildFieldParse(p);
	p.add(g_rva005C4553FieldParse, 0);
}

// 0x00576FFE (table VA 0x00C6E8F0): the dword the rowed getter 0x0042D697
// reads through the object the rowed getter 0x00328A83 (alias-pinned with
// its pointer result) reaches from the +0x08 object's +0x04 member.
class Rva0042D697PtrChaseField
{
public:
	Int get() const;
};
class Rva00328A83
{
public:
	Rva0042D697PtrChaseField *rva00328A83() const;
};
struct Rva00576FFEInfo
{
	Int m_00;
	Rva00328A83 *m_04;
};
class Rva00576FFE
{
public:
	Int rva00576FFE();
private:
	Int m_00;
	Int m_04;
	Rva00576FFEInfo *m_08;
};
Int Rva00576FFE::rva00576FFE()
{
	return m_08->m_04->rva00328A83()->get();
}

// 0x00251C24, 0x004624E3, 0x00466E0A and 0x004BC51B: interface overrides
// (interface at +0x0C, +0x20, +0x34 resp. +0x10) that only dispatch to
// virtual slot 12, 18, 28 resp. 13 of the complete object.
template <int N>
class Rva00251C24Slots : public Rva00251C24Slots<N - 1>
{
public:
	virtual void gap(char (*)[N]);
};
template <>
class Rva00251C24Slots<0>
{
};
template <int SLOT, int SIZE>
class Rva00251C24Primary : public Rva00251C24Slots<SLOT>
{
public:
	virtual void target();
private:
	char m_pad04[SIZE - 4];
};
class Rva00251C24Iface
{
public:
	virtual void forward() = 0;
};
class Rva00251C24 : public Rva00251C24Primary<12, 0x0C>, public Rva00251C24Iface
{
public:
	void forward();
};
void Rva00251C24::forward()
{
	target();
}
class Rva004624E3 : public Rva00251C24Primary<18, 0x20>, public Rva00251C24Iface
{
public:
	void forward();
};
void Rva004624E3::forward()
{
	target();
}
class Rva00466E0A : public Rva00251C24Primary<28, 0x34>, public Rva00251C24Iface
{
public:
	void forward();
};
void Rva00466E0A::forward()
{
	target();
}
class Rva004BC51B : public Rva00251C24Primary<13, 0x10>, public Rva00251C24Iface
{
public:
	void forward();
};
void Rva004BC51B::forward()
{
	target();
}

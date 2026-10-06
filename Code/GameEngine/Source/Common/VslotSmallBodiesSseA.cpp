// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes) whose float code is SSE (movss/comiss), so they need
// /arch:SSE. As in VslotSmallBodiesA-U, each class and method is
// address-derived and models only what its body touches. Meanings are not
// recovered.

typedef int Int;
typedef float Real;

// 0x0055B0B9 (tables of Rva0055B0CC and Rva00573B23): the larger of the
// Reals at +0x18 and +0x04.
class Rva0055B0B9
{
public:
	Real rva0055B0B9() const;
private:
	Int m_00;
	Real m_04;
	char m_pad08[0x10];
	Real m_18;
};
Real Rva0055B0B9::rva0055B0B9() const
{
	if (m_18 > m_04)
		return m_18;
	return m_04;
}

// 0x00597372 (beside xfer 0x005974CC): zeroes the three Reals out.
struct Rva00597372Triple
{
	Real x;
	Real y;
	Real z;
};
class Rva00597372
{
public:
	void rva00597372(Rva00597372Triple *out);
};
void Rva00597372::rva00597372(Rva00597372Triple *out)
{
	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
}

// 0x005C793A: 1.0 and the most negative Int out.
struct Rva005C793APair
{
	Real m_00;
	Int m_04;
};
class Rva005C793A
{
public:
	void rva005C793A(Rva005C793APair *out);
};
void Rva005C793A::rva005C793A(Rva005C793APair *out)
{
	out->m_00 = 1.0f;
	out->m_04 = (Int)0x80000000;
}

// 0x005EA1E7: adds the argument's +0x0C Real into entry [+0x30] of the Real
// array the +0x04 object points at; answers true.
struct Rva005EA1E7Arg
{
	char m_pad00[0x0C];
	Real m_0C;
	char m_pad10[0x20];
	Int m_30;
};
struct Rva005EA1E7Table
{
	Real *m_values;
};
class Rva005EA1E7
{
public:
	bool rva005EA1E7(const Rva005EA1E7Arg *arg);
private:
	Int m_00;
	Rva005EA1E7Table *m_04;
};
bool Rva005EA1E7::rva005EA1E7(const Rva005EA1E7Arg *arg)
{
	m_04->m_values[arg->m_30] += arg->m_0C;
	return true;
}

// 0x00452E00 (interface at +0x20, beside GameClientRandomVariable's
// getMinimumValue): copies the module data's +0x30 Real out and reports
// whether it differs from the 54321.0 sentinel.
struct Rva00452E00Data
{
	char m_pad00[0x30];
	Real m_30;
};
class Rva00452E00Primary
{
public:
	virtual void primarySlot();
protected:
	const Rva00452E00Data *m_moduleData; // +0x04
	char m_pad08[0x18];
};
class Rva00452E00Iface
{
public:
	virtual Int rva00452E00(Real *out) = 0;
};
class Rva00452E00 : public Rva00452E00Primary, public Rva00452E00Iface
{
public:
	Int rva00452E00(Real *out);
};
Int Rva00452E00::rva00452E00(Real *out)
{
	Real value = m_moduleData->m_30;
	*out = value;
	return value != 54321.0f;
}

// 0x005D9D81: whether the two arguments' +0x38/+0x3C positions are more than
// 100 apart (squared distance against 10000).
struct Rva005D9D81Pos
{
	char m_pad00[0x38];
	Real x;
	Real y;
};
struct Rva005D9D81Delta
{
	Real x;
	Real y;
};
class Rva005D9D81
{
public:
	bool rva005D9D81(const Rva005D9D81Pos *a, const Rva005D9D81Pos *b);
};
bool Rva005D9D81::rva005D9D81(const Rva005D9D81Pos *a, const Rva005D9D81Pos *b)
{
	Rva005D9D81Delta d;
	d.x = b->x;
	d.y = b->y;
	d.x -= a->x;
	d.y -= a->y;
	if (d.x * d.x + d.y * d.y > 10000.0f)
		return true;
	return false;
}

// 0x004624C1: zeroes the Real and the three Reals out; answers false.
class Rva004624C1
{
public:
	bool rva004624C1(Rva00597372Triple *pos, Real *value);
};
bool Rva004624C1::rva004624C1(Rva00597372Triple *pos, Real *value)
{
	*value = 0.0f;
	pos->z = 0.0f;
	pos->y = 0.0f;
	pos->x = 0.0f;
	return false;
}

// 0x00509DF8: for a non-NULL second argument, own virtual slot 15 when slot
// 1 accepts both arguments, then slot 6 with its +0x38 while +0x12C is
// positive.
struct Rva00509DF8Arg
{
	char m_pad00[0x38];
	Int m_38;
};
class Rva00509DF8
{
public:
	virtual void v00();
	virtual bool v01(Int a, Rva00509DF8Arg *b);
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06(Int a, Int *b);
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15(Int a, Rva00509DF8Arg *b);
	void rva00509DF8(Int a, Rva00509DF8Arg *b);
private:
	char m_pad04[0x128];
	Real m_12C;
};
void Rva00509DF8::rva00509DF8(Int a, Rva00509DF8Arg *b)
{
	if (b)
	{
		if (v01(a, b))
			v15(a, b);
		if (m_12C > 0.0f)
			v06(a, &b->m_38);
	}
}

// 0x0055F4CE: steps three value/rate/damping triples (at +0x10, +0x1C and
// +0x2C): the value advances by the rate, the rate decays by the damping.
// The operand order of the middle sum differs in retail and is kept.
struct Rva0055F4CEDrift
{
	Real value;
	Real rate;
	Real damping;
};
class Rva0055F4CE
{
public:
	void rva0055F4CE();
private:
	char m_pad00[0x10];
	Rva0055F4CEDrift m_10;
	Rva0055F4CEDrift m_1C;
	Int m_28;
	Rva0055F4CEDrift m_2C;
};
void Rva0055F4CE::rva0055F4CE()
{
	m_10.value = m_10.value + m_10.rate;
	m_10.rate = m_10.damping * m_10.rate;
	m_1C.value = m_1C.rate + m_1C.value;
	m_1C.rate = m_1C.damping * m_1C.rate;
	m_2C.value = m_2C.value + m_2C.rate;
	m_2C.rate = m_2C.damping * m_2C.rate;
}

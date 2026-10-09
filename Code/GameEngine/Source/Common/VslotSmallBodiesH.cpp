// cl: /O1 /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch H. As in VslotSmallBodiesA-G, each class and method
// is address-derived unless the ledger already names it, and models only what
// its body touches; the comment above each gives the .rdata slot address(es)
// that reference it. Meanings are not recovered.

typedef int Int;
typedef bool Bool;
typedef float Real;

Real normalizeAngle(Real angle);

// slot at VA 0x00C75800: true when entry i (0x1C-byte entries after a
// 0x1C-byte header) has its +0x0C or +0x10 field set.
struct Rva005D24E5Entry
{
	char m_pad00[0x0C];
	Int m_0C;
	Int m_10;
	char m_pad14[0x1C - 0x14];
};
class Rva005D24E5
{
public:
	Int rva005D24E5(Int index);
private:
	char m_header[0x1C];
	Rva005D24E5Entry m_entries[1];
};
Int Rva005D24E5::rva005D24E5(Int index)
{
	Rva005D24E5Entry *entry = &m_entries[index];
	if (entry->m_10 != 0 || entry->m_0C != 0)
		return 1;
	return 0;
}

// slots at VA 0x00C7645C and 0x00C76480: sets bit 2 of the +0x2B byte, bits
// 0x40000800 of +0x34 and bit 2 of the +0x21 byte.
class Rva005D9E02
{
public:
	void rva005D9E02();
private:
	char m_pad00[0x21];
	unsigned char m_21;
	char m_pad22[0x2B - 0x22];
	unsigned char m_2B;
	char m_pad2C[0x34 - 0x2C];
	unsigned int m_34;
};
void Rva005D9E02::rva005D9E02()
{
	m_2B |= 4;
	m_34 |= 0x40000800;
	m_21 |= 4;
}

// slot at VA 0x00C77A40: hands +0x08 to vslot 4 of the object the +0x04
// pointer refers to; the argument is unused.
class Rva005E18A7Target
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
	virtual void vslot03();
	virtual void vslot04(Int value);
};
class Rva005E18A7
{
public:
	void rva005E18A7(Int unused);
private:
	char m_pad00[0x04];
	Rva005E18A7Target **m_04;
	Int m_08;
};
void Rva005E18A7::rva005E18A7(Int unused)
{
	(*m_04)->vslot04(m_08);
}

// slots at VA 0x00C6FC98, 0x00C6FDA8 and 0x00C77B24: sets the +0x14 byte;
// the argument is unused.
class Rva005E2171
{
public:
	void rva005E2171(Int unused);
private:
	char m_pad00[0x14];
	Bool m_14;
};
void Rva005E2171::rva005E2171(Int unused)
{
	m_14 = true;
}

class Rva005E2180Target
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
	virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
	virtual void vslot06(); virtual void vslot07();
};

class Rva005E2180
{
public:
	void rva005E2180();
private:
	char m_pad00[0x08];
	Rva005E2180Target *m_08;
	char m_pad0C[0x20 - 0x0C];
	Int m_20;
};

void Rva005E2180::rva005E2180()
{
	if (m_20 >= 0)
		m_08->vslot07();
}


// slots at VA 0x00C6E30C and 0x00C70B7C: the normalized sum of the +0x4C and
// +0x3C angles (rowed normalizeAngle).
class Rva00573E1A
{
public:
	Real rva00573E1A();
private:
	char m_pad00[0x3C];
	Real m_3C;
	char m_pad40[0x4C - 0x40];
	Real m_4C;
};
Real Rva00573E1A::rva00573E1A()
{
	return normalizeAngle(m_4C + m_3C);
}

// slot at VA 0x00C6F12C: with the +0x14 state 0 runs the rowed 0x0057A92D (StrategicHUD::ChecklistUIImpl::Open)
// on this object (a tail jump); with state 3 sets the +0x26 byte.
namespace StrategicHUD { class ChecklistUIImpl { public: void Open(); }; }
class Rva0057A92D
{
public:
	void rva0057AB00();
private:
	char m_pad00[0x14];
	Int m_14;
	char m_pad18[0x26 - 0x18];
	Bool m_26;
};
void Rva0057A92D::rva0057AB00()
{
	if (m_14 == 0)
	{
		((StrategicHUD::ChecklistUIImpl *)this)->Open();
		return;
	}
	if (m_14 == 3)
		m_26 = true;
}

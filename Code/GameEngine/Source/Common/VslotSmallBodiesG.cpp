// cl: /DNDEBUG /MD
//
// Small vtable-slot bodies with no ledger owner and no Ghidra entry (sized
// from their bytes), batch G. As in VslotSmallBodiesA-F, each class and method
// is address-derived and models only what its body touches; the comment above
// each gives the .rdata slot address(es) that reference it. Meanings are not
// recovered.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

// slot at VA 0x00C6E3D8: true when the argument equals +0x10.
class Rva00574365
{
public:
	Bool rva00574365(Int value);
private:
	char m_pad00[0x10];
	Int m_10;
};
Bool Rva00574365::rva00574365(Int value)
{
	return value == m_10;
}

// slot at VA 0x00C6E400: true when the argument's +0x74 byte is clear.
struct Rva00574374Arg
{
	char m_pad00[0x74];
	Bool m_74;
};
class Rva00574374
{
public:
	Bool rva00574374(const Rva00574374Arg *arg);
};
Bool Rva00574374::rva00574374(const Rva00574374Arg *arg)
{
	return arg->m_74 == false;
}

// slot at VA 0x00C6E424: hands the argument's +0x88 pointer, when set, to
// this object's vslot 12.
struct Rva00574383Arg
{
	char m_pad00[0x88];
	void *m_88;
};
class Rva00574383
{
public:
	virtual void vslot00(); virtual void vslot01(); virtual void vslot02();
	virtual void vslot03(); virtual void vslot04(); virtual void vslot05();
	virtual void vslot06(); virtual void vslot07(); virtual void vslot08();
	virtual void vslot09(); virtual void vslot10(); virtual void vslot11();
	virtual void vslot12(void *value);
	void rva00574383(const Rva00574383Arg *arg);
};
void Rva00574383::rva00574383(const Rva00574383Arg *arg)
{
	void *value = arg->m_88;
	if (value)
		vslot12(value);
}

// slot at VA 0x00C6F128: the +0x08 field of the +0x34 entry unless it equals
// +0x30, else 0.
struct Rva0057AAF1Entry
{
	char m_pad00[0x08];
	Int m_08;
};
class Rva0057AAF1
{
public:
	Int rva0057AAF1();
private:
	char m_pad00[0x30];
	Rva0057AAF1Entry *m_30;
	Rva0057AAF1Entry *m_34;
};
Int Rva0057AAF1::rva0057AAF1()
{
	if (m_34 != m_30)
		return m_34->m_08;
	return 0;
}

// slot at VA 0x00C6F270: stores the byte argument at +0x2C when it differs.
class Rva0057B93E
{
public:
	void rva0057B93E(char value);
private:
	char m_pad00[0x2C];
	char m_2C;
};
void Rva0057B93E::rva0057B93E(char value)
{
	if (value != m_2C)
		m_2C = value;
}

// slot at VA 0x00C7391C: clears the +0x34 byte and +0x38, and copies the
// value the +0x0C pointer refers to into +0x10.
class Rva005B7426
{
public:
	void rva005B7426();
private:
	char m_pad00[0x0C];
	Int *m_0C;
	Int m_10;
	char m_pad14[0x34 - 0x14];
	Bool m_34;
	char m_pad35[0x38 - 0x35];
	Int m_38;
};
void Rva005B7426::rva005B7426()
{
	m_34 = false;
	m_10 = *m_0C;
	m_38 = 0;
}

// slot at VA 0x00C73954: the global block at VA 0x00E05FCC while +0x2C is 2,
// else the one at VA 0x00E06000.
// The two blocks are the GameSpy rank-weight tables, defined with the ledger's
// canonical class spelling (and the layout Rva00559A11.cpp proves) in the unit
// whose arg-ctor bodies fill them, Common/Rva007ABEF3ArgCtorInits.cpp; an
// incomplete view is enough because only the address is taken.
class Rva00559D0CRankWeights;
extern Rva00559D0CRankWeights g_00E05FCC;
extern Rva00559D0CRankWeights g_00E06000;
class Rva005B8018
{
public:
	char *rva005B8018();
private:
	char m_pad00[0x2C];
	Int m_2C;
};
char *Rva005B8018::rva005B8018()
{
	switch (m_2C)
	{
	case 2:
		return (char *)&g_00E05FCC;
	default:
		return (char *)&g_00E06000;
	}
}

// slot at VA 0x00C743E0: the +0x2C object's +0x04 field, or the global
// block at VA 0x00E06060 without the object.
extern char g_rva005C1A8DDefault[];
struct Rva005C1A8DInner
{
	char m_pad00[0x04];
	char *m_04;
};
class AptSkirmishStats
{
public:
	char *GetRankPointValue();
private:
	char m_pad00[0x2C];
	Rva005C1A8DInner *m_2C;
};
char *AptSkirmishStats::GetRankPointValue()
{
	if (m_2C == 0)
		return g_rva005C1A8DDefault;
	return m_2C->m_04;
}

// slots at VA 0x00C6E408, 0x00C6E640, 0x00C6E8C8, 0x00C74DD8 and
// 0x00C77DB0: tests one bit of the word array at +0x04.
class Rva005CBA3D
{
public:
	Int rva005CBA3D(UnsignedInt bit);
private:
	char m_pad00[0x04];
	UnsignedInt m_words[1];
};
Int Rva005CBA3D::rva005CBA3D(UnsignedInt bit)
{
	return (m_words[bit >> 5] & (1 << (bit & 0x1f))) != 0;
}

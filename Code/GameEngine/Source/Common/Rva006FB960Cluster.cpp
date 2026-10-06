// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Four Apt-neighbourhood bodies around 0x006FB960..0x006FC130, in the
// BfmePicker1284.cpp page of Code/GameEngine/Source/Common.
//
// 0x006FB960 / 0x006FB9C0 (29B): constructors of two BfmeAptValue006DCD20
//   subclasses.  Each calls the rowed base ctor 0x006DCCC0 with its folded type
//   constant (4 and 8), stores the int argument at +8 and installs its own
//   vtable (0x00CED808 / 0x00CED844, masked DIR32).
// 0x006FBBE0 (43B): linked-list lookup; walks +0x1C next pointers and calls the
//   rowed BfmeTab1034::bfmeFind1034F 0x0070B380 on the embedded table at +8.
//   The sibling 0x006FBE80, which wraps this over a global plus a +0x28 list,
//   is banked as a 60/66 partial (see reverse/re_attempts.log).
// 0x006FC130 (95B): subclass ctor built on Rva006D6360Base (base type 0x1E,
//   AptNativeHash at +8 sized 8) plus a non-polymorphic bits base at +0x1C,
//   then its own vtable.  The EH frame comes from the AptNativeHash member's
//   destructor being in scope while the base ctor runs.
//
// Class identities beyond the rowed base/tab callees are unproven; the classes
// are address-named after their body RVAs.

class BfmeAptValue006DCD20
{
public:
	BfmeAptValue006DCD20(int type);
	virtual void vtableSlot0();
	virtual ~BfmeAptValue006DCD20();
	unsigned int m_flags;
};

class Rva006FB960 : public BfmeAptValue006DCD20
{
public:
	Rva006FB960(int value);
	virtual void vtableSlot0();

private:
	int m_value;	// +0x08
};

Rva006FB960::Rva006FB960(int value) : BfmeAptValue006DCD20(4)
{
	m_value = value;
}

class Rva006FB9C0 : public BfmeAptValue006DCD20
{
public:
	Rva006FB9C0(int value);
	virtual void vtableSlot0();

private:
	int m_value;	// +0x08
};

Rva006FB9C0::Rva006FB9C0(int value) : BfmeAptValue006DCD20(8)
{
	m_value = value;
}

class BfmeN1034;

class BfmeTab1034
{
public:
	BfmeN1034 *bfmeFind1034F(int key);

private:
	char m_pad[0x14];	// embedded table occupies +0x08..+0x1B
};

struct Rva006FBBE0
{
	BfmeN1034 *find(int key);

	char m_pad00[8];
	BfmeTab1034 m_table;		// +0x08
	Rva006FBBE0 *m_next;		// +0x1C
};

BfmeN1034 *Rva006FBBE0::find(int key)
{
	Rva006FBBE0 *node = this;
	while (node != 0) {
		BfmeN1034 *found = node->m_table.bfmeFind1034F(key);
		if (found != 0)
			return found;
		node = node->m_next;
	}
	return 0;
}

class AptNativeHash
{
	int mnTotalSize;
	void *mpData;
	void *mp__proto__;
	void *mpPrototype;
	unsigned int nEventHandlers;

public:
	AptNativeHash(int size);
	~AptNativeHash();
};

class Rva006D6360Base : public BfmeAptValue006DCD20
{
public:
	AptNativeHash m_hash;	// 0x14 bytes, so the bits base lands at +0x1C

	Rva006D6360Base(int type, int size) : BfmeAptValue006DCD20(type), m_hash(size) {}
	virtual ~Rva006D6360Base();
};

class Rva006DBits
{
protected:
	unsigned int m_bits;

public:
	Rva006DBits()
	{
		*(unsigned char *)&m_bits = 0;
		m_bits &= 0xFFFFFCFF;
	}
};

class Rva006FC130 : public Rva006D6360Base, public Rva006DBits
{
public:
	Rva006FC130();
	virtual ~Rva006FC130();
};

Rva006FC130::Rva006FC130() : Rva006D6360Base(0x1e, 8), Rva006DBits()
{
}

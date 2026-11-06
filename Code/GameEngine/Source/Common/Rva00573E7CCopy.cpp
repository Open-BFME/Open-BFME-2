// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ??0Rva00573F03@@QAE@ABV0@@Z @0x00573EB8 75B (existing pin): order-object
// copy constructor. It copies the base through the rowed Rva00573B23 copy
// 0x00573AC8, installs vtable 0x00C6E2C8 (same as the rowed ctor 0x00573E7C)
// and copies the +0x40..+0x5C fields (layout from Rva00573E7CCtor.cpp; the
// Coord at +0x40 is spelled as three floats since a struct copy emits movsd).

class Rva00573B23
{
public:
	Rva00573B23(const Rva00573B23 &other);
	virtual ~Rva00573B23();
private:
	char m_pad04[0x40 - 0x04];
};

class Rva00573F03 : public Rva00573B23
{
public:
	Rva00573F03(const Rva00573F03 &other);
	// Retail 0x00573F03, defined in Rva00573B23Dtor.cpp; an inline body here would
	// emit a second, non-retail copy.
	virtual ~Rva00573F03();
private:
	float m_40;
	float m_44;
	float m_48;
	float m_4c;
	int m_50;
	bool m_54;
	unsigned int m_58;
	unsigned int m_5c;
};

Rva00573F03::Rva00573F03(const Rva00573F03 &other) :
	Rva00573B23(other),
	m_40(other.m_40),
	m_44(other.m_44),
	m_48(other.m_48),
	m_4c(other.m_4c),
	m_50(other.m_50),
	m_54(other.m_54),
	m_58(other.m_58),
	m_5c(other.m_5c)
{
}

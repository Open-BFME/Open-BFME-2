// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /arch:SSE
//
// ??0Rva00573E7C@@QAE@ABV0@@Z @0x00573EB8 75B (existing pin): order-object
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

class Rva00573E7C : public Rva00573B23
{
public:
	Rva00573E7C(const Rva00573E7C &other);
	virtual ~Rva00573E7C();
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

Rva00573E7C::Rva00573E7C(const Rva00573E7C &other) :
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

// cl: /O1 /Ob0
// ??4Rva00381F04@@QAEAAV0@ABV0@@Z @0x00381F04 265B
// Copy assignment over StringBaseG at +4 ints bytes loop8 ints AsciiString
// ints loop10 int byte Rva00235A37 at +90 ints loop16 via rowed assigns.
// Evidence: chain lane calls just-landed 0x00235A37; unblocks 0x00382E73.
template <typename T>
class StringBase
{
public:
	void set(const StringBase<T> &other);
};

class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);
private:
	void *m_data;
};

class Rva00235A37
{
public:
	Rva00235A37 &operator=(const Rva00235A37 &other);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1C;
	AsciiString m_20;
	AsciiString m_24;
	AsciiString m_28;
	unsigned char m_2C;
	char m_pad2D[3];
};

class Rva00381F04
{
public:
	Rva00381F04 &operator=(const Rva00381F04 &other);
	virtual ~Rva00381F04();
private:
	StringBase<unsigned short> m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_11;
	unsigned char m_12;
	char m_pad13;
	int m_14;
	int m_18[8];
	int m_38;
	int m_3C;
	AsciiString m_40;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
	int m_54;
	int m_58;
	int m_5C;
	int m_60[10];
	int m_88;
	unsigned char m_8C;
	char m_pad8D[3];
	Rva00235A37 m_90;
	int m_C0;
	int m_C4;
	int m_C8;
	char m_CC[16];
};

// ??1Rva00381F04@@UAE@XZ present-unmatched
Rva00381F04::~Rva00381F04()
{
}

Rva00381F04 &Rva00381F04::operator=(const Rva00381F04 &other)
{
	m_04.set(other.m_04);
	m_08 = other.m_08;
	m_0C = other.m_0C;
	m_10 = other.m_10;
	m_11 = other.m_11;
	m_12 = other.m_12;
	m_14 = other.m_14;
	for (int i = 0; i < 8; ++i)
		m_18[i] = other.m_18[i];
	m_38 = other.m_38;
	m_3C = other.m_3C;
	// rowed narrow copy-set 0x000366F0 (?set@?$StringBase@D@@QAEXABV1@@Z),
	// not the pin-only ??4AsciiString alias at the same address.
	((StringBase<char> &)m_40).set((const StringBase<char> &)other.m_40);
	m_44 = other.m_44;
	m_48 = other.m_48;
	m_4C = other.m_4C;
	m_50 = other.m_50;
	m_54 = other.m_54;
	m_58 = other.m_58;
	m_5C = other.m_5C;
	for (int i = 0; i < 10; ++i)
		m_60[i] = other.m_60[i];
	m_88 = other.m_88;
	m_8C = other.m_8C;
	m_90 = other.m_90;
	m_C0 = other.m_C0;
	m_C4 = other.m_C4;
	m_C8 = other.m_C8;
	for (int i = 0; i < 16; ++i)
		m_CC[i] = other.m_CC[i];
	return *this;
}

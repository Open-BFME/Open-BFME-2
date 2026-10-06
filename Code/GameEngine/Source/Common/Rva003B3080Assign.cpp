// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Rva003B3080's assignment operator at 0x00564B41: vptr-skip assign of three
// strings plus a trailing byte, ported from the BFME1 Rva003B3080Assign.cpp
// donor. Two retail adaptations: size-tuning (/O1 keeps eax for every argument
// slot where /O2 reuses ecx), and the members are StringBase<char> assigned
// via set() — retail calls StringBase<char>::set at 0x00366F0 directly, the
// same worker BFME2's AsciiString::operator= wrapper (0x001733) reaches, which
// mirrors BFME1's operator=-calls-set shape.

template <typename CharType>
class StringBase
{
public:
	void set(const StringBase<CharType> &other);

private:
	void *m_data;
};

class Rva003B3080
{
	virtual void handle(void);
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	char m_10;

public:
	Rva003B3080 &operator=(const Rva003B3080 &other);
};

Rva003B3080 &Rva003B3080::operator=(const Rva003B3080 &other)
{
	m_04.set(other.m_04);
	m_08.set(other.m_08);
	m_0C.set(other.m_0C);
	m_10 = other.m_10;
	return *this;
}

// cl: /DNDEBUG /MD
// Flag refreshers on the map-node payload whose pinned callers sit at
// 0x00213AA1..0x00213C4C. Each sets the +0x32 byte, then tail-calls the
// 0x003FAC83 dispatcher. The bit0/bit2 siblings 0x003FACB4 and 0x003FAD2B
// stay out: MSVC merges their two bit tests into one (see re_attempts).
// Names are address-derived (see the symbols.csv pins).

class Rva003FAC83
{
public:
	void rva003FAC83();
	void rva003FAD9A();
	void rva003FADA3();

private:
	char m_pad00[0x18];
	unsigned int m_state;
	char m_pad1c[0x14];
	bool m_30;
	bool m_31;
	bool m_32;
};

// 0x003FAD9A 9B
void Rva003FAC83::rva003FAD9A()
{
	m_32 = true;
	rva003FAC83();
}

// 0x003FADA3 18B
void Rva003FAC83::rva003FADA3()
{
	m_32 = !((m_state >> 3) & 1);
	rva003FAC83();
}

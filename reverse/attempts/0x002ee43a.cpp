// ?rva002EE43A@Rva002EE43A@@QAEPAV1@HPAXHHPBURva002EE43AWords@@@Z
// partial score=0.75 date=2026-10-07
// cl: /O1 /arch:SSE /Oy- /MD
// Native Ghidra extent 0x002EE43A..0x002EE49B (97 bytes), ending in RET 20.
// The receiver and original method name are unknown. Retail stores four
// argument words, copies three words through argument five, clears three
// floats, calls the verified parity splitter on +4, clears +0x18, and
// returns its receiver. These offsets and the ABI come from target bytes;
// the address-derived names do not assert an original class identity.

void __cdecl Rva002EBCA7Split(void *, int *, unsigned char *);

struct Rva002EE43AWords
{
	unsigned first, second, third;
};

class Rva002EE43A
{
public:
	Rva002EE43A *rva002EE43A(int, void *, int, int, const Rva002EE43AWords *);
private:
	int m_00;
	void *m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	char m_pad11[3];
	int m_14;
	bool m_18;
	char m_pad19[3];
	Rva002EE43AWords m_1C;
	float m_28, m_2C, m_30;
};

Rva002EE43A *Rva002EE43A::rva002EE43A(int a, void *b, int c, int d,
	const Rva002EE43AWords *words)
{
	m_00 = a;
	m_04 = b;
	m_08 = c;
	m_14 = d;
	m_1C.first = words->first;
	m_1C.second = words->second;
	m_1C.third = words->third;
	m_28 = 0.0f;
	m_2C = 0.0f;
	m_30 = 0.0f;
	Rva002EBCA7Split(m_04, &m_0C, &m_10);
	m_18 = false;
	return this;
}

// cl: /MD /GX-
//
// ?rva002707FA@Rva002707FA@@QAEXE@Z, retail 0x002707FA, 29 bytes. Chain lane:
// calls 0x003626CE (rowed Rva003626CE::rva003626CE in Rva00409930SlotArray.cpp)
// which this landing just made ready. Prev is DrawableFade.cpp
// (/O1 /DNDEBUG /MD /arch:SSE), next is Rva00270BA8.cpp (/O1 /MD /GX-) whose
// flags are copied here. Sets byte at +0x441 from arg low byte, then forwards
// to Rva003626CE at +0x450 when nonzero. Callers include unclaimed 0x000B5A72,
// 0x000B5C41, 0x002391AA and tiny 0x0029B1AC/0x0029B1C2.

class Rva003626CE
{
public:
	void rva003626CE(unsigned char value);
};

class Rva002707FA
{
public:
	void rva002707FA(unsigned char value);
private:
	unsigned char m_pad00[0x441];
	unsigned char m_441;
	unsigned char m_pad442[0x450 - 0x441 - 1];
	Rva003626CE *m_450;
};

void Rva002707FA::rva002707FA(unsigned char value)
{
	m_441 = value;
	if (m_450)
		m_450->rva003626CE(value);
}

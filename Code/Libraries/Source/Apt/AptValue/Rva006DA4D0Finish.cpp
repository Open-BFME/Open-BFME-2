// ?Rva006DA4D0::Rva006DA4D0 present-unmatched
// Native 6DA4D0/138 installs the AptArray-family table CEA778.
// This is distinct from AptValue constructors 6DCCC0/6DCD20 (CEAED0).
// Original class name is unknown; array offsets20/24/28 and calls are target facts.
// The rowed array-operation providers retain their older receiver spelling.
// This call-only declaration does not assert their private class layout.
// cl: /O2 /MD
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);
class BfmeAptValue006DCD20 { public: void rva006D9500(int); void rva006D8AD0(int, BfmeAptValue006DCD20 *); };
class Rva006D6360 { public: Rva006D6360(int type, int size); virtual ~Rva006D6360(); char m_pad[0x18]; };
class Rva006D6470Owner : public Rva006D6360
{
public:
	Rva006D6470Owner(int type, int size) : Rva006D6360(type, size)
	{
		*(unsigned char *)&m_bits = 0;
		m_bits &= 0xFFFFFCFF;
	}
	virtual ~Rva006D6470Owner();
	unsigned int m_bits;
};
class Rva006DA4D0 : public Rva006D6470Owner
{
public:
	virtual void slot0();
	virtual void slot1();
	Rva006DA4D0(int count, BfmeAptValue006DCD20 **pValues);
	BfmeAptValue006DCD20 **m_data;
	int mnCapacity;
	int mnLength;
};
Rva006DA4D0::Rva006DA4D0(int count, BfmeAptValue006DCD20 **pValues)
	: Rva006D6470Owner(0x16, count)
{
	mnCapacity = 0;
	m_data = 0;
	mnLength = count;
	reinterpret_cast<BfmeAptValue006DCD20 *>(this)->rva006D9500(count);
	for (int i = 0; i < mnLength; ++i)
		reinterpret_cast<BfmeAptValue006DCD20 *>(this)->rva006D8AD0(i, pValues[i]);
}

// cl: /DNDEBUG /MD
//
// ?rva0027070C@Rva0027070C@@QAEPAURva0027070CData@@XZ, retail 0x0027070C, 74 bytes.
// Unlock lane: returns &m_90 (12B at +0x90) or 0. Guards on global g_00DFE1E4
// (data 0x009FE1E4, no name yet): null check, virtual at +0x3C returning bool,
// then virtual at +0x48 filling a 12B stack tmp and returning a 12B src which
// is copied to m_90. Prev is our Rva002706A8.cpp, next is DrawableFade.cpp,
// both /O1 /DNDEBUG /MD /arch:SSE whose flags are copied here.

struct Rva0027070CData
{
	int a;
	int b;
	int c;
};

class Rva0027070CGlobal
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual bool slot3C();
	virtual void slot40(); virtual void slot44();
	virtual Rva0027070CData *slot48(Rva0027070CData *out);
};

// g_00DFE1E4: matched references place it at VA 0xdfe1e4 (retail .data initial value 0).
Rva0027070CGlobal * g_00DFE1E4 = 0;

class Rva0027070C
{
public:
	Rva0027070CData *rva0027070C();
private:
	unsigned char m_pad00[0x90];
	Rva0027070CData m_90;
};

Rva0027070CData *Rva0027070C::rva0027070C()
{
	if (g_00DFE1E4 != 0 && g_00DFE1E4->slot3C())
	{
		Rva0027070CData tmp;
		Rva0027070CData *src = g_00DFE1E4->slot48(&tmp);
		Rva0027070CData *dst = &m_90;
		dst->a = src->a;
		dst->b = src->b;
		dst->c = src->c;
		return dst;
	}
	return 0;
}

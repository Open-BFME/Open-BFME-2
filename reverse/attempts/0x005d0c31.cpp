// ??0Rva005D0C31@@QAE@PAX@Z
// partial score=0.93 date=2026-10-04
// cl: /O1 /MD /EHsc
// ??0Rva005D0C31@@QAE@PAX@Z, retail 0x005D0C31, 86 bytes.
// Evidence: base 0x005CF8A1 with arg passthrough, vtables 0x00875574 and listener at +0x10 then append via g_009FEF10+0x6c.
class Rva005CF8A1
{
public:
	Rva005CF8A1(void *p);
	virtual ~Rva005CF8A1();
private:
	char m_pad04[0x10 - 4];
};

struct Rva002BA8F1Listener
{
	char m_pad[4];
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
};

class Rva002BA8F1Logic
{
public:
	char m_pad00[0x6c];
	Rva005A0B4CList m_6c;
};

extern Rva002BA8F1Logic *g_009FEF10;

class ListenerBase
{
public:
	virtual ~ListenerBase();
};

class Listener10 : public ListenerBase
{
public:
	virtual ~Listener10();
};

class Rva005D0C31 : public Rva005CF8A1
{
public:
	Rva005D0C31(void *p);
	virtual ~Rva005D0C31();
private:
	Listener10 m_10;
};

Rva005D0C31::Rva005D0C31(void *p)
	: Rva005CF8A1(p)
{
	g_009FEF10->m_6c.append((Rva002BA8F1Listener *)&m_10);
}

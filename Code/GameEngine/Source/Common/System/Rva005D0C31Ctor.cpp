// cl: /O1 /MD /EHsc
// ??0Rva005D0C31@@QAE@PAX@Z, retail 0x005D0C31, 86 bytes.
// Evidence: base 0x005CF8A1 with arg passthrough, second base at +0x10 with own vtable 0x0087528C then derived vtables 0x00875574/0x00875570, append via g_009FEF10+0x6c. MI pattern per Rva00575125Ctor second base at +0x10.
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

class Rva005D0C31Second
{
public:
	virtual ~Rva005D0C31Second();
};

class Rva005D0C31 : public Rva005CF8A1, public Rva005D0C31Second
{
public:
	Rva005D0C31(void *p);
	virtual ~Rva005D0C31();
};

Rva005D0C31::Rva005D0C31(void *p)
	: Rva005CF8A1(p)
	, Rva005D0C31Second()
{
	g_009FEF10->m_6c.append((Rva002BA8F1Listener *)((char *)this + 0x10));
}

// cl: /MD /EHsc
// ??0Rva005D078B@@QAE@PAX@Z, retail 0x005D0C31, 86 bytes.
// Evidence: base 0x005CF8A1 with arg passthrough, second base at +0x10 with own vtable 0x0087528C then derived vtables 0x00875574/0x00875570, append via g_009FEF10+0x6c. MI pattern per Rva00575125Ctor second base at +0x10.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
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

#include "../../../Include/Common/Rva005A0B4CList.h"

class Rva002BA8F1Logic
{
public:
	char m_pad00[0x6c];
	Rva005A0B4CList m_6c;
};

class Rva005D0C31Second
{
public:
	virtual ~Rva005D0C31Second() {}
};

class Rva005D078B : public Rva005CF8A1, public Rva005D0C31Second
{
public:
	Rva005D078B(void *p);
	virtual ~Rva005D078B();
};

Rva005D078B::Rva005D078B(void *p)
	: Rva005CF8A1(p)
	, Rva005D0C31Second()
{
	(*(Rva002BA8F1Logic **)&TheLivingWorldLogic)->m_6c.append((Rva002BA8F1Listener *)((char *)this + 0x10));
}

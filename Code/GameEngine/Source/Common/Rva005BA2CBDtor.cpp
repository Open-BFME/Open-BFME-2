// cl: /DNDEBUG /MD
// ??1Rva005BA2CB@@UAE@XZ @0x005BA2CB 40B dtor stores three vtables plus clears global plus tail-jmps to pinned base 0x005A0009 via caller ??_G 0x005BA303. Evidence: pin plus vtable slots plus rowed global g_Va00E06548 plus pinned base.
extern int g_Va00E06548;

class Rva005A0009
{
public:
	virtual ~Rva005A0009();
private:
	char m_pad04[0x60 - 4];
};

class Rva005BA2CBBase60
{
public:
	virtual void s60();
private:
	char m_pad04[0x6C - 0x60 - 4];
};

class Rva005BA2CBBase6C
{
public:
	virtual void s6C();
};

class Rva005BA2CB : public Rva005A0009, public Rva005BA2CBBase60, public Rva005BA2CBBase6C
{
public:
	virtual ~Rva005BA2CB();
};

Rva005BA2CB::~Rva005BA2CB()
{
	if (g_Va00E06548 == (int)this)
		g_Va00E06548 = 0;
}

extern int g_Va00E06544;

class Rva005BA23ABase60
{
public:
	virtual void s60();
private:
	char m_pad04[0x6C - 0x60 - 4];
};

class Rva005BA23ABase6C
{
public:
	virtual void s6C();
};

class Rva005BA23A : public Rva005A0009, public Rva005BA23ABase60, public Rva005BA23ABase6C
{
public:
	virtual ~Rva005BA23A();
};

Rva005BA23A::~Rva005BA23A()
{
	if (g_Va00E06544 == (int)this)
		g_Va00E06544 = 0;
}

// cl: /DNDEBUG /MD /EHsc
// ??1Rva00131D07@@UAE@XZ @0x00131D07 77B
// Dtor stores vtable 0x007D2630, delete[]s +0x50 array via rowed ??_V,
// frees +0x3C StringClass via rowed Free_String, then rowed base 0x00131BE5
// dtor. Evidence: packet disasm with rowed callees, caller deleting dtor,
// prev/next vslot bodies, base Rva00131BE5Dtor layout.
class BfmeThingUB
{
public:
	virtual ~BfmeThingUB();
	char m_pad[0x10 - 4];
};

class Rva00131BE5M14
{
public:
	virtual void v00();
};

class StringClass
{
public:
	char *m_Buffer;
private:
	void Free_String();
	friend class Rva00131BE5;
	friend class Rva00131D07;
};

void __cdecl operator delete[](void *p);

class Rva00131BE5 : public BfmeThingUB
{
public:
	virtual ~Rva00131BE5();
	int m_10;
	Rva00131BE5M14 *m_14;
	StringClass m_str;
};

class Rva00131D07 : public Rva00131BE5
{
public:
	virtual ~Rva00131D07();
private:
	char m_pad1C[0x3C - 0x1C];
	StringClass m_3C;
	char m_pad40[0x50 - 0x40];
	char *m_50;
};

Rva00131D07::~Rva00131D07()
{
	if (m_50 != 0) {
		::operator delete[](m_50);
		m_50 = 0;
	}
	m_3C.Free_String();
}

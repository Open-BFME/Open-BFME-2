// cl: /MD /EHsc
// ??0Rva005AFE86@@QAE@PAX@Z, retail 0x005AFE86, 85 bytes.
// Chain ctor: stores vtable 0x00C728B8, arg at +4, zeroes +8..+20,
// then appends this to global list via Get 0x00381452 (returns 0x00E02310)
// and append 0x005A0B4C. Base 0x005AFE86 calls derived 0x005D57D3.
// EH_prolog with state 0 via empty unwindable base. Evidence: callers
// 0x005AF9F4 0x005D509C 0x005D57DA, callees rowed, vtable store.

int Rva00381452Get(void);

extern const void *const g_00C728B8[];

struct Rva002BA8F1Listener
{
	char opaque[4];
};

class Rva005A0B4CList
{
public:
	void append(Rva002BA8F1Listener *p);
private:
	char m_pad[12];
};

class EmptyBase005AFE86
{
public:
	EmptyBase005AFE86() {}
	~EmptyBase005AFE86();
};

class Rva005AFE86 : public EmptyBase005AFE86
{
public:
	Rva005AFE86(void *p);
private:
	const void *m_vtable;
	void *m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
};

Rva005AFE86::Rva005AFE86(void *p)
	: EmptyBase005AFE86()
	, m_vtable(g_00C728B8)
	, m_04(p)
{
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0;
	m_1C = 0;
	m_20 = 0;
	((Rva005A0B4CList *)(unsigned int)Rva00381452Get())->append((Rva002BA8F1Listener *)(void *)this);
}

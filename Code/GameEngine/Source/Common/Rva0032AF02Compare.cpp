// cl: /O1 /EHsc /MD
// ?Rva0032AF02Compare@@YAHHHH@Z @0x0032AF02 84B unlock caller 0x0032B624 globals 0x007FDC60 0x0080D938
// Evidence: builds two stack Reader adaptors with vtables g_00BFDC60/g_00C0D938 around first two args then cdecl Compare with third arg. Same shape as Rva002ABC22Compare (84B).
class Rva002AADB6Reader
{
public:
	virtual int GetLength();
	virtual void Read(void *buf, int offset, int size);
};

extern const void *const g_00BFDC60[];
extern const void *const g_00C0D938[];

int Rva002AADB6Compare(Rva002AADB6Reader *a, Rva002AADB6Reader *b, int unused);

class ReaderA0032AF02 : public Rva002AADB6Reader
{
public:
	ReaderA0032AF02(const void *p)
	{
		*(const void *const **)this = g_00BFDC60;
		m_arg = p;
	}
	virtual ~ReaderA0032AF02() {}
	const void *m_arg;
};

class ReaderB0032AF02 : public Rva002AADB6Reader
{
public:
	ReaderB0032AF02(const void *p)
	{
		*(const void *const **)this = g_00C0D938;
		m_arg = p;
	}
	virtual ~ReaderB0032AF02() {}
	const void *m_arg;
};

int __cdecl Rva0032AF02Compare(int a, int b, int c)
{
	*(volatile int *)&a = a;
	ReaderB0032AF02 rb((const void *)b);
	ReaderA0032AF02 ra(&a);
	return Rva002AADB6Compare((Rva002AADB6Reader *)&ra, (Rva002AADB6Reader *)&rb, c);
}

// cl: /O1 /EHsc /MD
// ?Rva002ABC22Compare@@YAHHHH@Z @0x002ABC22 84B unlock caller 0x002AC285 globals 0x007FDC60 0x007FDC6C
// Evidence: builds two stack Reader adaptors with vtables g_00BFDC60/g_00BFDC6C around first two args then cdecl Compare with third arg.
class Rva002AADB6Reader
{
public:
	virtual int GetLength();
	virtual void Read(void *buf, int offset, int size);
};

extern const void *const g_00BFDC60[];
extern const void *const g_00BFDC6C[];

int Rva002AADB6Compare(Rva002AADB6Reader *a, Rva002AADB6Reader *b, int unused);

class ReaderA002ABC22 : public Rva002AADB6Reader
{
public:
	ReaderA002ABC22(const void *p)
	{
		*(const void *const **)this = g_00BFDC60;
		m_arg = p;
	}
	virtual ~ReaderA002ABC22() {}
	const void *m_arg;
};

class ReaderB002ABC22 : public Rva002AADB6Reader
{
public:
	ReaderB002ABC22(const void *p)
	{
		*(const void *const **)this = g_00BFDC6C;
		m_arg = p;
	}
	virtual ~ReaderB002ABC22() {}
	const void *m_arg;
};

int __cdecl Rva002ABC22Compare(int a, int b, int c)
{
	*(volatile int *)&a = a;
	ReaderB002ABC22 rb((const void *)b);
	ReaderA002ABC22 ra(&a);
	return Rva002AADB6Compare((Rva002AADB6Reader *)&ra, (Rva002AADB6Reader *)&rb, c);
}

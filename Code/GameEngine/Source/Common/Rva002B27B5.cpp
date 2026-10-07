// cl: /O1 /MD /Oy-
// ?rva002B27B5@Rva002B27B5@@QAE_NPAVRva00318C32@@H@Z @0x002B27B5 87B.
extern class Rva003B8BAA *g_00E02D6C;

class Rva00318C32
{
public:
	int rva00318C32();
};

class Rva0020EC99Helper
{
public:
	int rva0020EC99(Rva00318C32 *a1, int t2, int t1, int z1, int z2);
};

class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva003B8BAA
{
public:
	void *rva003B8BAA();
};

class TailVirt27B5
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual bool tail(Rva00318C32 *a, int b);
};

class Rva002B27B5
{
public:
	bool rva002B27B5(Rva00318C32 *a, int b);

private:
	unsigned char m_pad00[0xB0];
	Rva0020EC99Helper *m_b0;
};

bool Rva002B27B5::rva002B27B5(Rva00318C32 *a, int b)
{
	int r = m_b0->rva0020EC99(a, a->rva00318C32(), b, 0, 0);
	if (r < 0 || r > 1)
		return false;
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
	{
		void *p = g_00E02D6C->rva003B8BAA();
		return ((TailVirt27B5 *)p)->tail(a, b);
	}
	return true;
}

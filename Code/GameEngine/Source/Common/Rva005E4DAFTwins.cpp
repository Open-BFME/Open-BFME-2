// cl: /MD
class Rva005E4BB7
{
public:
	void *rva005E4BB7(void *out);
};
struct Rva005F3F41Outer
{
	void set(unsigned char v);
};
class Rva005F22D2
{
public:
	void rva005F2295(int v);
};
class Rva005F2406
{
public:
	void rva005F2406(int v);
};
class Rva005E4DAF
{
public:
	void rva005E4DAF(int v);
	void rva005E4DE5(int v);
private:
	char m_00[0x14];
	void *m_14;
	char m_pad18[0x1C - 0x18];
	Rva005E4BB7 m_1C;
	char m_pad1D[0x2C - 0x1D];
	bool m_2C;
};
void Rva005E4DAF::rva005E4DAF(int v)
{
	if (m_2C) {
		void *ret = m_1C.rva005E4BB7(&v);
		void *p = *(void **)ret;
		void *q = *(void **)p;
		int r = *(int *)((char *)q + 4);
		((Rva005F3F41Outer *)(r + (int)p))->set(0);
	}
	((Rva005F22D2 *)m_14)->rva005F2295(v);
}
void Rva005E4DAF::rva005E4DE5(int v)
{
	if (m_2C) {
		void *ret = m_1C.rva005E4BB7(&v);
		void *p = *(void **)ret;
		void *q = *(void **)p;
		int r = *(int *)((char *)q + 4);
		((Rva005F3F41Outer *)(r + (int)p))->set(1);
	}
	((Rva005F2406 *)m_14)->rva005F2406(v);
}

// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ??0Rva005CF7BF@@QAE@PAXHHHHHHHH@Z, retail 0x005CF751..0x005CF7BF (110
// bytes, EH, RET 36): the constructor matching the rowed Rva005CF7BF
// destructor (vtable 0x00C75254). The base is built from the first argument
// (rowed 0x005E67FE; EH state 0) and the +0x08 holder takes a new 0x20-byte
// implementation (0x005CF27A, not yet rowed; pinned) built from this and the
// other eight arguments -- the sixth and seventh swapped -- with state 1
// guarding the allocation. WorldBuilder's twin (0x015C3E50) is unnamed.

class Rva005E67FE
{
public:
	Rva005E67FE(void *a);
	virtual ~Rva005E67FE();
private:
	int m_04;
};

class Rva005CF7BF;

class Rva005CF27A
{
public:
	Rva005CF27A(Rva005CF7BF *owner, int a2, int a3, int a4, int a5, int a7, int a6, int a8, int a9);
private:
	unsigned char m_pad00[0x20];
};

class Rva005CF363
{
public:
	Rva005CF363(Rva005CF27A *impl) : m_impl(impl) {}
	~Rva005CF363();
private:
	Rva005CF27A *m_impl;
};

class Rva005CF7BF : public Rva005E67FE
{
public:
	Rva005CF7BF(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9);
	virtual ~Rva005CF7BF();
private:
	Rva005CF363 m_impl08;					// +0x08
};

Rva005CF7BF::Rva005CF7BF(void *a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
	: Rva005E67FE(a1),
	  m_impl08(new Rva005CF27A(this, a2, a3, a4, a5, a7, a6, a8, a9))
{
}

// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020E9F2@Rva0020E9F2Outer@@QAEXXZ @0x0020E9F2 48B
// ?rva0020EA22@Rva0020EA22Outer@@QAEXH@Z @0x0020EA22 54B
// Homogeneous vector-clear loops via inner at *(this+8), bounds idiom gives
// retail add esi,0x2C prolog.

class Rva003F300A
{
public:
	void rva003F300A();
};

class Rva003F3708
{
public:
	void rva003F3708(int v);
};

struct Rva0020E9F2Inner
{
	char m_pad[0x2C];
	Rva003F300A **m_begin;
	Rva003F300A **m_end;
};

struct Rva0020EA22Inner
{
	char m_pad[0x2C];
	Rva003F3708 **m_begin;
	Rva003F3708 **m_end;
};

class Rva0020E9F2Outer
{
public:
	void rva0020E9F2();
private:
	char m_pad[8];
	Rva0020E9F2Inner *m_inner;
};

class Rva0020EA22Outer
{
public:
	void rva0020EA22(int v);
private:
	char m_pad[8];
	Rva0020EA22Inner *m_inner;
};

void Rva0020E9F2Outer::rva0020E9F2()
{
	Rva0020E9F2Inner *inner = m_inner;
	Rva003F300A ***bounds = (Rva003F300A ***)&inner->m_begin;
	for (unsigned i = 0; i < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++i)
		bounds[0][i]->rva003F300A();
}

void Rva0020EA22Outer::rva0020EA22(int v)
{
	Rva0020EA22Inner *inner = m_inner;
	Rva003F3708 ***bounds = (Rva003F3708 ***)&inner->m_begin;
	for (unsigned i = 0; i < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++i)
		bounds[0][i]->rva003F3708(v);
}

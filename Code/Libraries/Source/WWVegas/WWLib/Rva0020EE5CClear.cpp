// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020EE5C@Rva0020EE5C@@QAEXXZ @0x0020EE5C 51B
// Clears each entry of the pointer vector at inner+0x2c/+0x30 (inner = *(this+8))
// by calling rowed ?rva003F20B0@Rva003F20B0@@QAEXXZ. Same 51B shape as
// Rva0020EE29::rva0020EE29 over [eax+edi*4] with reload-each-iteration count.
// Evidence: callees rowed 0x003F20B0; caller at 0x002B2945; neighbours
// 0x0020EE29/0x0020EE8F; Ghidra start proven by direct call.

class Rva003F20B0
{
public:
	void rva003F20B0();
};

struct Rva0020EE5CInner
{
	char m_pad[0x2c];
	Rva003F20B0 **m_begin;
	Rva003F20B0 **m_end;
};

class Rva0020EE5C
{
public:
	void rva0020EE5C();

private:
	char m_pad[8];
	Rva0020EE5CInner *m_inner;
};

void Rva0020EE5C::rva0020EE5C()
{
	Rva0020EE5CInner *inner = m_inner;
	if (!inner)
		return;
	for (unsigned i = 0; i < (unsigned)(((char *)inner->m_end - (char *)inner->m_begin) >> 2); ++i)
		inner->m_begin[i]->rva003F20B0();
}

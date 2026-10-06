// cl: /O1 /Ob1 /EHsc /MD /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// ?rva0020EB4E@Rva0020EB4EOuter@@QAEXPAX@Z @0x0020EB4E 82B
// Gated search over inner vector at *(this+8)+0x2C/+0x30 via bounds (add esi,0x2C): runs rowed 0x003F7954 on the outer arg, then for each element with +0x13C == arg+4+0x14 runs pinned 0x003F2150(arg). Void arg keeps PAX mangling; casts are explicit.
class Rva003F7954
{
public:
	void rva003F7954();
};
class Rva003F2150
{
public:
	void rva003F2150(int v);
};
struct Rva0020EB4EInner
{
	char m_pad[0x2C];
	void **m_begin;
	void **m_end;
};
struct Rva0020EB4EElem
{
	char m_pad[0x13C];
	int m_13C;
};
struct Arg04
{
	char m_pad[0x14];
	int m_14;
};
struct OuterArg
{
	char m_pad[4];
	Arg04 *m_04;
};
class Rva0020EB4EOuter
{
public:
	void rva0020EB4E(void *argRaw);
private:
	char m_pad[8];
	Rva0020EB4EInner *m_inner;
};
void Rva0020EB4EOuter::rva0020EB4E(void *argRaw)
{
	OuterArg *arg = (OuterArg *)argRaw;
	((Rva003F7954 *)arg)->rva003F7954();
	Rva0020EB4EInner *inner = m_inner;
	void ***bounds = (void ***)&inner->m_begin;
	for (unsigned i = 0; i < (unsigned)(((char *)bounds[1] - (char *)bounds[0]) >> 2); ++i)
	{
		Rva0020EB4EElem *e = (Rva0020EB4EElem *)bounds[0][i];
		if (e->m_13C != arg->m_04->m_14)
			continue;
		((Rva003F2150 *)e)->rva003F2150((int)arg);
	}
}
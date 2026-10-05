// ?Rva0040F10F@@YGXPAVRva0037EB1D@@@Z
// partial score=0.91 date=2026-10-05
// cl: /O1 /DNDEBUG /MD /EHsc
// ?Rva0040F10F@@YGXPAVRva0037EB1D@@@Z @0x0040F10F 142B
// Finds owner via bfmeFind1038, creates Rva0040C351, inits and adds via 0x0040ECCF.
// Evidence: find 0x0040D008 pin, new 0xC8 rowed ??2@YAPAXI@Z, ctor 0x0040C351,
// rva0037EB1D 0x0037EB1D rowed, our 0x0040ECCF rowed, Release 0x0007DEEF;
// caller at 0x0037EBBA; ret 4 stdcall one arg.
struct BfmeY1038;
BfmeY1038 *__stdcall bfmeFind1038(int key);

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct Rva0040F454Target
{
	char m_pad00[8];
	float m_value;
	char m_pad0C[0xAC - 0xC];
	TargetRef00217D4C m_ac;
};

class Rva004F6093Holder
{
public:
	~Rva004F6093Holder()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(&m_ptr->m_ac);
	}

public:
	Rva0040F454Target *m_ptr;
};

class Rva0040ECCF
{
public:
	int rva0040ECCF(const Rva004F6093Holder &holder);
};

class Rva0037DF2C
{
public:
	Rva0037DF2C();
private:
	char m_pad[0xAC];
};

struct MemberAC
{
	MemberAC() {}
	void *m_vtable;
	int m_04;
};

class Rva0040C351 : public Rva0037DF2C
{
public:
	Rva0040C351();
public:
	MemberAC m_ac;
	char m_padB4[0xC8 - 0xB4];
};

class Rva0037EB1D
{
public:
	void rva0037EB1D(void *p);
public:
	char m_pad[0xA8];
	int m_a8;
};

void *__cdecl operator new(unsigned int size);

typedef unsigned int size_t;

inline void *operator new(size_t, void *place)
{
	return place;
}

// ?Rva0040F10F@@YGXPAVRva0037EB1D@@@Z present-unmatched
void __stdcall Rva0040F10F(Rva0037EB1D *obj)
{
	BfmeY1038 *owner = bfmeFind1038(obj->m_a8);
	Rva0040C351 *p = 0;
	if (owner == (BfmeY1038 *)p)
		return;
	p = new Rva0040C351;
	Rva004F6093Holder h;
	h.m_ptr = (Rva0040F454Target *)p;
	if (p)
		++p->m_ac.m_04;
	obj->rva0037EB1D(p);
	++*(int *)((char *)p + 0x94);
	((Rva0040ECCF *)owner)->rva0040ECCF(h);
}

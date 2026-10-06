// ??0Rva0056AEC6@@QAE@PAXH@Z
// partial score=0.6 date=2026-10-06
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ??0Rva0056AEC6@@QAE@PAXH@Z @0x0056AEC6 105B.
// Constructor: run the pinned 0x0056AD80 initializer, install the
// 0x00C6D0FC vftable at +0 and the 0x00C6D0C0 vftable at +8, set +0x14 to
// the int argument and clear +0x18, then probe the living-world holder at
// g_00DFEF10[0xB0] with a temporary carrying the 0x00C6D0BC vtable plus the
// same argument. Sibling shape of the rowed 0x0056ADF1/0x0056AF94 ctors.
// Honest address-derived name.
class Rva0056AD80
{
public:
	virtual ~Rva0056AD80();
	void rva0056AD80(void *arg);
};

extern "C" const void *const vtbl_00C6D0FC[];
extern "C" const void *const vtbl_00C6D0C0[];
extern "C" const void *const vtbl_00C6D0BC[];

class Rva0020E7BD
{
public:
	void rva0020E7BD(void *arg);
};

struct Rva0056AEC6Glob
{
	char m_pad[0xB0];
	Rva0020E7BD *m_B0;
};

extern Rva0056AEC6Glob *g_00DFEF10;

struct Rva0056AEC6Tmp
{
	void *m_vtbl;
	int m_arg;
};

class Rva0056AEC6
{
public:
	virtual ~Rva0056AEC6();
	Rva0056AEC6(void *arg1, int arg2);
};

Rva0056AEC6::Rva0056AEC6(void *arg1, int arg2)
{
	((Rva0056AD80 *)this)->rva0056AD80(arg1);
	*(unsigned int *)this = ((unsigned int)vtbl_00C6D0FC);
	*(unsigned int *)((char *)this + 8) = ((unsigned int)vtbl_00C6D0C0);
	*(int *)((char *)this + 0x14) = arg2;
	*(unsigned char *)((char *)this + 0x18) = 0;
	Rva0056AEC6Tmp tmp;
	tmp.m_vtbl = (void *)vtbl_00C6D0BC;
	tmp.m_arg = arg2;
	g_00DFEF10->m_B0->rva0020E7BD(&tmp);
}

// ?IsLocalPlayerAllowedToEndPhase@LivingWorldLogic@@QAE_NXZ
// partial score=0.779342723 date=2026-10-09
// cl: /O1 /MD
// ?rva002B5EB5@Rva002B5EB5@@QAE_NXZ @0x002B5EB5 213B: __thiscall bool with
// no stack args. Gate chain: rowed 0x2B254F int probe (byte-tested); on hit
// the rowed 0x3B8BAA lookup off g_00E02D6C plus the pinned 0x3F85C6 bool
// check must pass. Then the +0x154 bound pair must be equal, then the rowed
// 0x2B3621 probe must pass. Then an if-else chain on +0xF4: 0 returns whether
// the +0xCC pair is equal; 1 and 5 return the negation of the rowed 0x2B4B3D
// probe; 2 runs the rowed 0x20E72A scan over +0x98 (false on hit) else the
// negation of the pinned 0x2B5CBB worker; 3 and 6 return true; 4 returns
// whether the +0x10C pair is equal or the rowed 0x2B32CE probe passes;
// anything else returns false. Evidence: retail dec-chain on m_f4 with
// sub-eax-0 first (if-else, no jump table), lea-formed bound-pair accesses,
// neg/sbb/inc booleanize tails, shared pops epilogue. Boundary: Ghidra
// FUN_006b5eb5 213B; prev ret, next prologue. Names address-derived except
// rowed callees and pins.
extern class Rva003B8BAA *g_00E02D6C;

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

class Rva003F81FDProxy
{
public:
	unsigned char rva003F85C6();
};

class Rva002B4C09
{
public:
	bool rva002B3621();
};

class Rva002B32CE
{
public:
	bool rva002B32CE();
};

class Rva002B4B3D
{
public:
	bool rva002B4B3D();
};

class Rva0020E72A
{
public:
	bool rva0020E72A(void *p);
};

struct Rva002B4C35Player;
class LivingWorldLogic
{
public:
	bool IsLocalPlayerAllowedToEndPhase();
	bool rva002B5CBB(const Rva002B4C35Player *p);
private:
	char m_pad0[0x98];
	void *m_98; // +0x98 scan subject passed to 0x20E72A and 0x2B5CBB
	char m_pad9C[0xB0 - 0x9C];
	Rva0020E72A *m_pB0; // +0xB0 scan owner for the 0x20E72A call
	char m_padB4[0xCC - 0xB4];
	int m_beginCC; // +0xCC bound pair for case 0
	int m_endD0; // +0xD0
	char m_padD4[0xF4 - 0xD4];
	int m_f4; // +0xF4 dispatch
	char m_padF8[0x10C - 0xF8];
	int m_begin10C; // +0x10C bound pair for case 4
	int m_end110; // +0x110
	char m_pad114[0x154 - 0x114];
	int m_begin154; // +0x154 bound pair for the entry gate
	int m_end158; // +0x158
};

bool LivingWorldLogic::IsLocalPlayerAllowedToEndPhase()
{
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() == 0)
		goto check154;
	{
		Rva003F81FDProxy *inner = (Rva003F81FDProxy *)g_00E02D6C->rva003B8BAA();
		if (!inner->rva003F85C6())
			goto fail;
	}
check154:
	int *p154 = (int *)((char *)this + 0x154);
	if (p154[0] != p154[1])
		goto fail;
	if (((Rva002B4C09 *)this)->rva002B3621())
		goto fail;
	int m = m_f4;
	switch (m)
	{
	case 0:
		{
		int *pCC = (int *)((char *)this + 0xCC);
		return pCC[0] == pCC[1];
		}
	case 1:
	case 5:
		return !(((Rva002B4B3D *)this)->rva002B4B3D());
	case 2:
		{
		void **pp = (void **)((char *)this + 0x98);
		if (((Rva0020E72A *)m_pB0)->rva0020E72A(*pp))
			goto fail;
		bool b = !rva002B5CBB((const Rva002B4C35Player*)*pp);
		return b;
		}
	case 3:
	case 6:
		return true;
	case 4:
		{
		int *p10C = (int *)((char *)this + 0x10C);
		int result=0;
		if (p10C[0] == p10C[1] || ((Rva002B32CE *)this)->rva002B32CE())
			result=1;
		return result;
		}
	default:
		goto fail;
	}
 goto fail;
fail:
 return false;
}
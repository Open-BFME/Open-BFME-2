// cl: /MD
// Caller units retained after duplicate reserve-then-set bodies were consolidated.
// Original Wave-3 evidence, five 36-byte reserve-then-set twins:
//   push esi; eax=[this+0x10]+1; C1(eax); C2(b, a); return a; ret 8
// (C1 is a one-arg thiscall on the same this with ecx passing through; C2 a
// two-arg thiscall on the same this; the body returns its first argument.
// Only the two callee addresses differ per member, except 0x003EF34A and
// 0x0052B7F8 which share C1 0x00212858.) The shared C1 reads an int-vector
// count at this+4 and grows via 0x0005571B when the request exceeds it, so
// C1 is a reserve-like grower and C2 the indexed set; owner class identities
// are unproven, so each body gets an address-named owner with its two
// callees pinned. 0x00212858 carries one pin per owner spelling (alias pins,
// same bytes).
//
//   body        C1 (reserve)  C2 (set)
//   0x00057B27  0x00056BFE    0x00054BC3
//   0x00057D38  0x0053F1EC    0x000556AB
//   0x000E0536  0x000E0322    0x000E0298
//   0x003EF34A  0x00212858    0x003EF264
//   0x0052B7F8  0x00212858    0x0052B737
class Rva00057B27Owner { public: int fwd(int, int); };
class Rva000E0536Owner { public: int fwd(int, int); };

class Rva00057B27
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva00056BFE(unsigned int n);
	void rva00054BC3(unsigned int a, unsigned int b);
	int rva00057B27(unsigned int a, unsigned int b);
	void rva00058913(void *dst, unsigned int b);
};


class Rva00057D38
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva0053F1EC(unsigned int n);
	void rva000556AB(unsigned int a, unsigned int b);
	int rva00057D38(unsigned int a, unsigned int b);
};


class Rva000E0536
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva000E0322(unsigned int n);
	void rva000E0298(unsigned int a, unsigned int b);
	int rva000E0536(unsigned int a, unsigned int b);
	void rva000E055A(void *dst, unsigned int b);
};


class Rva003EF34A
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva00212858(unsigned int n);
	void rva003EF264(unsigned int a, unsigned int b);
	int rva003EF34A(unsigned int a, unsigned int b);
};


class Rva0052B7F8
{
	char m_pad[0x10];
	int m_count10;
public:
	int rva00212858(unsigned int n);
	void rva0052B737(unsigned int a, unsigned int b);
	int rva0052B7F8(unsigned int a, unsigned int b);
};


// 0x00058913 42B: fills a 9-byte (int int byte) temp via rowed reserve-then-set
// 0x00057B27 on the same this (ecx passes through) then copies it to *dst.
// Evidence: pushes outer arg then temp address then rowed call then three
// moves to [dst] [dst+4] [dst+8] with ret 8; callers 0x00059D90 plus 0x0006265C;
// unblocks 0x00059CE6; precedent rva000E055A 0x000E055A same recipe same size.
void Rva00057B27::rva00058913(void *dst, unsigned int b)
{
	struct Temp
	{
		int a;
		int c2;
		unsigned char c3;
	} tmp;
	((Rva00057B27Owner *)this)->fwd((int)&tmp, (int)b);
	((int *)dst)[0] = tmp.a;
	((int *)dst)[1] = tmp.c2;
	((unsigned char *)dst)[8] = tmp.c3;
}

// 0x000E055A 42B: fills a 9-byte (int int byte) temp via rowed reserve-then-set
// 0x000E0536 on the same this (ecx passes through) then copies it to *dst.
// Evidence: pushes outer arg then temp address then rowed call then three
// moves to [dst] [dst+4] [dst+8] with ret 8; unblocks 0x000E0584.
void Rva000E0536::rva000E055A(void *dst, unsigned int b)
{
	struct Temp
	{
		int a;
		int c2;
		unsigned char c3;
	} tmp;
	((Rva000E0536Owner *)this)->fwd((int)&tmp, (int)b);
	((int *)dst)[0] = tmp.a;
	((int *)dst)[1] = tmp.c2;
	((unsigned char *)dst)[8] = tmp.c3;
}

// 0x00058913 (42B): snapshot-after-set. Calls the 0x00057B27 twin above on
// the SAME incoming this (no mov ecx: the callee's owner view is reused
// here, owner identity unproven) with a stack 9-byte out-slot and the index,
// then copies the slot (dword, dword, byte) to the caller's out pointer.
struct Rva00058913Out
{
	int m_0;
	int m_4;
	char m_8;
};

class Rva00058913
{
public:
	void rva00058913(Rva00058913Out *o, unsigned int b);
};

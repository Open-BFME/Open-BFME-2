// ?rva002B3484@Rva002B3484@@QAE_NPAUArg24@@@Z
// partial score=0.92 date=2026-10-06
// ?rva002B3484@Rva002B3484@@QAE_NPAUArg24@@@Z
// partial score=0.92 date=2026-10-04
// cl: /O1 /MD
// ?rva002B3484@Rva002B3484@@QAE_NPAUArg24@@@Z @0x002B3484 97B.
// Chain on 0x002B254F with one arg plus second-stage 0x002B2B66 compare.
// Evidence: retail cmp [esi+98] je false/cmp [esi+F4] je cont/xor al jmp end/
// call 0x2B254F/test al je second/mov ecx[g_00E02D6C]/call 0x3B8BAA/
// mov edx[eax]/push arg/mov ecx eax/call [edx+1C]/test al je false/
// mov edx[arg+24]/test edx je false/mov ecx esi/call 0x2B2B66/
// cmp [edx+13C] eax jne false/mov al 1/xor al al/ret 4.
// Callees rowed. Caller at 0x002B7733 0x005754B9 0x00576120.
extern class Rva003B8BAA *g_00E02D6C;

class Rva002B254F
{
public:
	int rva002B254F();
};

class Rva002B2B66
{
public:
	int rva002B2B66();
};

class Rva003B8BAA
{
public:
	void *rva003B8BAA();
};

struct Inner24
{
	char m_pad[0x13C];
	int m_val13C;
};

struct Arg24
{
	char m_pad[0x24];
	Inner24 *m_ptr24;
};

class LookupVirt1C
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual bool check(Arg24 *a);
};

class Rva002B3484
{
	char m_pad0[0x98];
	int m_field98;
	char m_pad1[0xF4 - 0x9C];
	int m_fieldF4;
public:
	bool rva002B3484(Arg24 *a);
};

// ?rva002B3484@Rva002B3484@@QAE_NPAUArg24@@@Z present-unmatched
bool Rva002B3484::rva002B3484(Arg24 *a)
{
	if (m_field98 == 0)
		return false;
	if (m_fieldF4 != 0)
		return false;
	if ((unsigned char)((Rva002B254F *)this)->rva002B254F() != 0)
	{
		void *p = g_00E02D6C->rva003B8BAA();
		if (!((LookupVirt1C *)p)->check(a))
			return false;
	}
	Inner24 *q1 = a->m_ptr24;
	if (q1 == 0)
		return false;
	int v = ((Rva002B2B66 *)this)->rva002B2B66();
	Inner24 *q2 = a->m_ptr24;
	if (q2->m_val13C == v)
		return true;
	return false;
}

// Open-BFME5 conversions (trimmed; only bfmeGoRF is placed, the rest is
// declared-only).

struct BfmeObjRB
{
	int m_bfmeOn;
};

extern BfmeObjRB *g_bfmeGlobRB;
void bfmeOneRB(int f, BfmeObjRB *p);
void bfmeTwoRB(int k, int f);

void bfmeGoRB(void);




class BfmeOtherRE
{
public:
	char bfmeCmpRE(int a, int b);
};

class BfmeThingRE
{
public:
	char bfmeGoRE(BfmeOtherRE *o);
	int m_bfmeA;
	int m_bfmeB;
};

void *bfmeOneRF(void *t, void *a);
void *bfmeTwoRF(void *r, void *b);

class BfmeThingRF
{
public:
	void *bfmeGoRF(void *a, void *b);
	char m_bfmePad[0x10];
	void *m_bfmeT;
};

// ?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z
void *BfmeThingRF::bfmeGoRF(void *a, void *b)
{
	void *r = bfmeOneRF(m_bfmeT, a);
	if (!r)
		return b;
	return bfmeTwoRF(r, b);
}

// ?bfmeGoRE@BfmeThingRE@@QAEDPAVBfmeOtherRE@@@Z
char BfmeThingRE::bfmeGoRE(BfmeOtherRE *o)
{
	if (!o->bfmeCmpRE(m_bfmeA, m_bfmeB))
		return 0;
	++m_bfmeB;
	return 1;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?getPtr@Rva00803620Getter@@QAEPAXPAX0@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeGetVJI@BfmeMsgVJI@@QAEHPBDH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?getInt@BfmeSrc803BF0@@QAEHPBDH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?getInt@BfmeSrc803A00@@QAEHPBDH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeFindVNC@BfmeKeyVNC@@QAEPAXPBDH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?getInt@BfmeSrc803B60@@QAEHPBDH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?getInt@BfmeSrc803C90@@QAEHPBDH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeGetVHC@BfmeMsgVHC@@QAEPAXPAX0@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeGetSA@BfmeThingSA@@QAEHPBDH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeGetSB@BfmeThingSB@@QAEPAXPAX0@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeGetESI@BfmeDictESI@@QAEPAXPBDPAX@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeOneEBK@BfmeObjEBK@@QAEXPAXH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeGetVHE@BfmeMsgVHE@@QAEHPAXH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeFind1052@BfmeI1052@@QAEHPADH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeGetTCA@BfmeGetterTCA@@QAEPAXPAX0@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeMakeDFC@BfmeOtherDFC@@QAEPAXPAXH@Z=?bfmeGoRF@BfmeThingRF@@QAEPAXPAX0@Z")

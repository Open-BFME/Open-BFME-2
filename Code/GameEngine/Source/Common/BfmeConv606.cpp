class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *one, void *two);
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

int Rva007EC5C0(char *a, int b, const char *c, int d);

void BfmeThingCIB::bfmeGoCIB(void *one, void *two)
{
	if (Rva007EC5C0((char *)m_bfmeA, (int)m_bfmeB, (const char *)one, (int)two) < 0)
		m_bfmeErr = -100;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeWriteAlt@BfmeSetupRecord@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeSet3VJA@BfmeMsgVJA@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSet3VJI@BfmeMsgVJI@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSet3VJC@BfmeMsgVJC@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?addInt@BfmeMsg803BF0@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?addInt@BfmeMsg803A00@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSet3VJF@BfmeMsgVJF@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSet3VJH@BfmeMsgVJH@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?addInt@BfmeMsg803B60@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?addInt@BfmeMsg803C90@@QAEXPBDH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSetVHE@BfmeMsgVHE@@QAEXPAXH@Z=?bfmeGoCIB@BfmeThingCIB@@QAEXPAX0@Z")

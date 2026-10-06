// cl: /MD
//
// ?rva006E0D40@Rva006E0D40@@QAEXXZ, retail 0x006E0D40, 22 bytes.
// Reference-count release: decrement the 16-bit field at +0x5C and, when it
// reaches zero, call the __cdecl teardown at 0x006CE1C0 with 0. Evidence: the
// caller at 0x006FAC33 (on the pointer at +0x24 of an Apt value) and the
// caller at 0x00709E2D both load the pointer into ecx and call this after a
// vtable-slot-1 release; the 0xffff dword test is the bitfield zero test.
// The owning class name is not recovered, so it stays address-derived.

void rva006CE1C0(int arg);

class Rva006E0D40
{
public:
	void rva006E0D40();

private:
	char m_pad[0x5C];
	unsigned int m_5C : 16;
};

void Rva006E0D40::rva006E0D40()
{
	if (--m_5C == 0)
		rva006CE1C0(0);
}

// ?rva006E1540@BfmeAptValue006DCD20@@QAEXXZ, retail 0x006E1540, 126 bytes.
// AptCIH display-object worker. When the "isSpriteInstBase()" predicate
// (0x006CFCD0) holds it re-tests it (the assertion's own evaluation), then
// tail-calls the +0x24 sub-object of the +0x4C display object at 0x006F76B0.
// Otherwise, for a text instance (predicate 0x006E02B0), it takes the +0x4C
// object via 0x006E0F40, releases the +0x20 pointer through the free callback
// at VA 0x00E17774 (size 2) unless it is null or the 0x00DDC2E0 sentinel, sets
// +0x6C = 6, then clears +0x20. Evidence: matched sibling Rva006EE1B0Cluster
// uses the same AptCIH.h:125 assert; 15 callers of 0x006E02B0 all test `al`;
// the retail string at 0x008E9A78 is "isSpriteInstBase()".

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void (__cdecl *g_00E17774)(void *p, int v);
extern char g_00DDC2E0;
#pragma intrinsic(__debugbreak)

class Rva006F76B0
{
public:
	void rva006F76B0();
};

class BfmeAptValue006DCD20
{
public:
	bool rva006cfcd0();
	bool rva006E02B0() const;
	void *rva006E0F40() const;
	void rva006E1540();

private:
	char m_pad00[0x4C];
	void *m_p;	// +0x4C
};

struct Rva006E0F40Target
{
	char m_pad00[0x20];
	void *m_20;		// +0x20
	Rva006F76B0 m_24;	// +0x24
	char m_pad28[0x6C - 0x28];
	int m_6C;		// +0x6C
};

void BfmeAptValue006DCD20::rva006E1540()
{
	if (rva006cfcd0()) {
		if (!rva006cfcd0()) {
			g_bfmeAptAssertAtE17734("isSpriteInstBase()",
				"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
			if (g_bfmeAptBreakOnAssertAtDDC01C)
				__debugbreak();
		}
		((Rva006E0F40Target *)m_p)->m_24.rva006F76B0();
		return;
	}
	if (rva006E02B0()) {
		Rva006E0F40Target *target = (Rva006E0F40Target *)rva006E0F40();
		void *p20 = target->m_20;
		if (p20 != 0 && p20 != (void *)&g_00DDC2E0) {
			target->m_6C = 6;
			g_00E17774(p20, 2);
		}
		target->m_20 = 0;
	}
}

// cl: /Oy-
// Four retail morph-init bodies (45B each). Retail shape per member: ebp
// frame, 5 args, push esi/edi, cache 5th arg in edi, forward all five to a
// shared init, store the 5th arg at +0x20, then a trailing vtable install at
// +0x00, return this, ret 0x14. The trailing store is spelled as placement
// new; the morph identity is unproven and the names are address-derived.
// Members differ only in the installed vtable (0x1C apart):
// 0x005CD257 -> 0x00C74F84, 0x005CD2A3 -> 0x00C74FA0,
// 0x005CD2EF -> 0x00C74FBC, 0x005CD34B -> 0x00C74FD8.
// Shared-init identity unproven (opaque member pin on the owner).
// /O1 keeps pushes on the stack slots (with pop-ecx-class cleanups) and
// /Oy- keeps the ebp frame; /O2 drops the frame and preloads registers.
// One ledger row per member.

#include <new>

class Rva005CDSub84
{
public:
	virtual ~Rva005CDSub84();
};

class Rva005CDSubA0
{
public:
	virtual ~Rva005CDSubA0();
};

class Rva005CDSubBC
{
public:
	virtual ~Rva005CDSubBC();
};

class Rva005CDSubD8
{
public:
	virtual ~Rva005CDSubD8();
};

class Rva005CDMorph
{
public:
	void sharedInit(int a, int b, int c, int d, int e);
	Rva005CDMorph *setup84(int a, int b, int c, int d, int e);
	Rva005CDMorph *setupA0(int a, int b, int c, int d, int e);
	Rva005CDMorph *setupBC(int a, int b, int c, int d, int e);
	Rva005CDMorph *setupD8(int a, int b, int c, int d, int e);

private:
	unsigned char m_pad[0x20];
	int m_last;
};

Rva005CDMorph *Rva005CDMorph::setup84(int a, int b, int c, int d, int e)
{
	sharedInit(a, b, c, d, e);
	m_last = e;
	new (this) Rva005CDSub84;
	return this;
}

Rva005CDMorph *Rva005CDMorph::setupA0(int a, int b, int c, int d, int e)
{
	sharedInit(a, b, c, d, e);
	m_last = e;
	new (this) Rva005CDSubA0;
	return this;
}

Rva005CDMorph *Rva005CDMorph::setupBC(int a, int b, int c, int d, int e)
{
	sharedInit(a, b, c, d, e);
	m_last = e;
	new (this) Rva005CDSubBC;
	return this;
}

Rva005CDMorph *Rva005CDMorph::setupD8(int a, int b, int c, int d, int e)
{
	sharedInit(a, b, c, d, e);
	m_last = e;
	new (this) Rva005CDSubD8;
	return this;
}

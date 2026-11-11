// cl: /Oy- /EHsc
// Four retail morph-init bodies (45B each). Retail shape per member: ebp
// frame, 5 args, push esi/edi, cache 5th arg in edi, forward all five to a
// shared init, store the 5th arg at +0x20, then a trailing vtable install at
// +0x00, return this, ret 0x14. The trailing store is spelled as placement
// new; the morph identity is unproven and the names are address-derived.
// Members differ only in the installed vtable (0x1C apart):
// 0x005CD257 -> 0x00C74F84, 0x005CD2A3 -> 0x00C74FA0,
// 0x005CD2EF -> 0x00C74FBC, 0x005CD34B -> 0x00C74FD8.
// The shared init 0x005CD1D3 is the members' common base constructor (it
// returns this and installs vtable 0x00C74F68 after constructing the
// Rva005CCDDD base); each member calls it in place, so no new-expression
// unwind state appears in them.
// /O1 keeps pushes on the stack slots (with pop-ecx-class cleanups) and
// /Oy- keeps the ebp frame; /O2 drops the frame and preloads registers.
// One ledger row per member.

#include <new>

class UnicodeString;

class Rva005CCDDD
{
public:
	Rva005CCDDD();						// 0x005CCD94
	virtual ~Rva005CCDDD();				// 0x005CCDDD
private:
	void *m_04;
	void *m_payload;					// +0x08
};

class Rva005CCB73 { public: void rva005CCB73(void *arg); };				// 0x005CCB73
#include "../../Include/Common/Rva005CCB7B.h"
class Rva005CCE13 { public: void rva005CCE13(const UnicodeString &text); };	// 0x005CCE13

// ??0Rva005CDMorphBase@@QAE@HHHHH@Z, retail 0x005CD1D3, 111 bytes (RET 0x14):
// the five arguments land at +0x0C..+0x1C; then 0x005CCB73(1),
// 0x005CCB7B(false) and 0x005CCE13 with the UnicodeString at +0x0C of the
// fifth argument's object.
class Rva005CDMorphBase : public Rva005CCDDD
{
public:
	Rva005CDMorphBase(int a, int b, int c, int d, int textSource);
	virtual ~Rva005CDMorphBase() {}
private:
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	unsigned char *m_1c;
};

Rva005CDMorphBase::Rva005CDMorphBase(int a, int b, int c, int d, int textSource)
	: m_0c(a), m_10(b), m_14(c), m_18(d), m_1c((unsigned char *)textSource)
{
	((Rva005CCB73 *)this)->rva005CCB73((void *)1);
	((Rva005CCB7B *)this)->rva005CCB7B(false);
	((Rva005CCE13 *)this)->rva005CCE13(*(const UnicodeString *)(m_1c + 0xc));
}

class Rva005CDSub84
{
public:
	virtual ~Rva005CDSub84() {}
};

class Rva005CDSubA0
{
public:
	virtual ~Rva005CDSubA0() {}
};

class Rva005CDSubBC
{
public:
	virtual ~Rva005CDSubBC() {}
};

class Rva005CDSubD8
{
public:
	virtual ~Rva005CDSubD8() {}
};

class Rva005CDMorph
{
public:
	Rva005CDMorph *setup84(int a, int b, int c, int d, int textSource);
	Rva005CDMorph *setupA0(int a, int b, int c, int d, int textSource);
	Rva005CDMorph *setupBC(int a, int b, int c, int d, int textSource);
	Rva005CDMorph *setupD8(int a, int b, int c, int d, int textSource);

private:
	unsigned char m_pad[0x20];
	int m_last;
};

Rva005CDMorph *Rva005CDMorph::setup84(int a, int b, int c, int d, int textSource)
{
	((Rva005CDMorphBase *)this)->Rva005CDMorphBase::Rva005CDMorphBase(a, b, c, d, textSource);
	m_last = textSource;
	new (this) Rva005CDSub84;
	return this;
}

Rva005CDMorph *Rva005CDMorph::setupA0(int a, int b, int c, int d, int textSource)
{
	((Rva005CDMorphBase *)this)->Rva005CDMorphBase::Rva005CDMorphBase(a, b, c, d, textSource);
	m_last = textSource;
	new (this) Rva005CDSubA0;
	return this;
}

Rva005CDMorph *Rva005CDMorph::setupBC(int a, int b, int c, int d, int textSource)
{
	((Rva005CDMorphBase *)this)->Rva005CDMorphBase::Rva005CDMorphBase(a, b, c, d, textSource);
	m_last = textSource;
	new (this) Rva005CDSubBC;
	return this;
}

Rva005CDMorph *Rva005CDMorph::setupD8(int a, int b, int c, int d, int textSource)
{
	((Rva005CDMorphBase *)this)->Rva005CDMorphBase::Rva005CDMorphBase(a, b, c, d, textSource);
	m_last = textSource;
	new (this) Rva005CDSubD8;
	return this;
}

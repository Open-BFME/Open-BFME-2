// cl: /DNDEBUG /MD
// ?allocBlock@Rva006D2A60@@QAEPAXH@Z @ 0x006D29E0 (127B). Retail's class is the
// AptValueGCAllocator (assert literals name AptValueGCAllocator.cpp/.h); the
// address-derived class name matches the already-published pin at this RVA.
//
// Allocates through the pool's own base allocator (0x006DB160, rowed as
// Rva006DB160::allocBlock), marks the new value's mbIsAllocated bit false and
// then true, asserting the bit after each step. The mode byte at VA
// 0x00E177E0 selects which word of the value the setter at 0x006D28D0
// toggles; the asserts read +4, so the bitfield sits at +4.
//
// The base call keeps ecx == this (Rva006DB160 is the offset-0 base), which is
// why retail emits no `mov ecx` before it. The setter 0x006D28D0 is declared
// here and pinned address-derived.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

unsigned char g_00E177E0;
// g_00E177E0: the mode byte read at VA 0xe177e0 (zero-filled .bss).

class Rva006DB160
{
public:
	void *allocBlock(int blockSize);

	union ValueBitfield
	{
		struct
		{
			unsigned int mbIsAllocated : 1;
			unsigned int mRest : 31;
		};
		int mRaw;
	};
	ValueBitfield mBitfield0;
	ValueBitfield mValueBitfield;
};

class Rva006D2A60 : public Rva006DB160
{
public:
	void *allocBlock(int nBytes);
	void rva006D28D0(int mode, bool value);
	bool isAllocated(int nSizeOffset);
	int rva006D2930(int nSizeOffset);
};

inline bool Rva006D2A60::isAllocated(int nSizeOffset)
{
	if (nSizeOffset == 4)
	{
		return mValueBitfield.mbIsAllocated;
	}
	if (nSizeOffset == 0)
	{
		return mBitfield0.mbIsAllocated;
	}
	g_bfmeAptAssertAtE17734("false", "..\\..\\include\\apt\\AptValueGCAllocator.h", 0xE2);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
	{
		__asm int 3
	}
	return false;
}

int Rva006D2A60::rva006D2930(int nSizeOffset)
{
	if (isAllocated(nSizeOffset))
	{
		g_bfmeAptAssertAtE17734("!IsAllocated(nSizeOffset)", "..\\..\\include\\apt\\AptValueGCAllocator.h", 0x121);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
		{
			__asm int 3
		}
	}
	if (nSizeOffset == 4)
	{
		return mValueBitfield.mRaw & ~1;
	}
	if (nSizeOffset == 0)
	{
		return mBitfield0.mRaw & ~1;
	}
	g_bfmeAptAssertAtE17734("false", "..\\..\\include\\apt\\AptValueGCAllocator.h", 0x137);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
	{
		__asm int 3
	}
	return 0;
}

void Rva006D2A60::rva006D28D0(int mode, bool value)
{
	if (mode == 4)
	{
		mValueBitfield.mbIsAllocated = value;
		return;
	}
	if (mode == 0)
	{
		mBitfield0.mbIsAllocated = value;
		return;
	}
	g_bfmeAptAssertAtE17734("false", "..\\..\\include\\apt\\AptValueGCAllocator.h", 0x107);
	if (g_bfmeAptBreakOnAssertAtDDC01C)
	{
		__asm int 3
	}
}

void *Rva006D2A60::allocBlock(int nBytes)
{
	Rva006D2A60 *p = (Rva006D2A60 *)Rva006DB160::allocBlock(nBytes);
	p->rva006D28D0(g_00E177E0, false);
	if (!(p->mValueBitfield.mbIsAllocated == false)) {
		g_bfmeAptAssertAtE17734("pValue->mValueBitfield.mbIsAllocated == false",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueGCAllocator.cpp", 0x6F);
		if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
	}
	p->rva006D28D0(g_00E177E0, true);
	if (!(p->mValueBitfield.mbIsAllocated == true)) {
		g_bfmeAptAssertAtE17734("pValue->mValueBitfield.mbIsAllocated == true",
			"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValueGCAllocator.cpp", 0x73);
		if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
	}
	return p;
}


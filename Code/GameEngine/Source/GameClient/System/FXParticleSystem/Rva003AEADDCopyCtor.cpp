// cl: /O1 /GX- /arch:SSE2

// Rva003AEADD (45B) outer copy via rowed base Rva003AEB0A (91B).
// Same 45B base-plus-4-vtables shape as Rva003AEA15; base is already rowed
// so no pin is needed. All vtable dwords are DIR32.

class Rva003AEB0A
{
public:
	Rva003AEB0A(const Rva003AEB0A &other);
};

extern "C" char Rva003AEADD_v0;
extern "C" char Rva003AEADD_v14;
extern "C" char Rva003AEADD_v18;
extern "C" char Rva003AEADD_v1c;

class Rva003AEADD
{
public:
	__declspec(noinline) Rva003AEADD(const Rva003AEADD &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13 owned by base copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
	char m_pad20[128]; // +0x20..0x9F owned by base copy
};

// ??0Rva003AEADD@@QAE@ABV0@@Z
Rva003AEADD::Rva003AEADD(const Rva003AEADD &that)
{
	const void *src = &that;
	((Rva003AEB0A *)this)->Rva003AEB0A::Rva003AEB0A(*(const Rva003AEB0A *)src);
	*(void **)this = &Rva003AEADD_v0;
	*(void **)((char *)this + 0x14) = &Rva003AEADD_v14;
	*(void **)((char *)this + 0x18) = &Rva003AEADD_v18;
	*(void **)((char *)this + 0x1C) = &Rva003AEADD_v1c;
}

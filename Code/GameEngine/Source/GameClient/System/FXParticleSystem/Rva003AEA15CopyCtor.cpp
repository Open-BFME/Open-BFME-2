// cl: /O1 /GX- /arch:SSE2

// Rva003AEA15 (45B) outer copy via pinned middle Rva003AEA42 (97B).
// Conservative Rva owner; true ConcreteModuleTemplate pin at same address
// is hierarchy-blocked (4 vptr slots vs 3 declared bases) and stays pinned
// for the already-rowed clone at 0x3AE9DB. All vtable dwords are DIR32.

class Rva003AEA42
{
public:
	Rva003AEA42(const Rva003AEA42 &other);
};

extern "C" char Rva003AEA15_v0;
extern "C" char Rva003AEA15_v14;
extern "C" char Rva003AEA15_v18;
extern "C" char Rva003AEA15_v1c;

class Rva003AEA15
{
public:
	__declspec(noinline) Rva003AEA15(const Rva003AEA15 &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04..0x13 owned by middle copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C
	char m_pad20[128]; // +0x20..0x9F owned by middle copy
};

// ??0Rva003AEA15@@QAE@ABV0@@Z
Rva003AEA15::Rva003AEA15(const Rva003AEA15 &that)
{
	const void *src = &that;
	((Rva003AEA42 *)this)->Rva003AEA42::Rva003AEA42(*(const Rva003AEA42 *)src);
	*(void **)this = &Rva003AEA15_v0;
	*(void **)((char *)this + 0x14) = &Rva003AEA15_v14;
	*(void **)((char *)this + 0x18) = &Rva003AEA15_v18;
	*(void **)((char *)this + 0x1C) = &Rva003AEA15_v1c;
}

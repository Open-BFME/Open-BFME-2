// ??0Rva003AEA42@@QAE@ABV0@@Z
// partial score=0.97 date=2026-09-25
// cl: /DNDEBUG /MD /GX- /O1 /Ob2

// Default module template copy constructors (retail 0x003AEA42 cluster).
// Each per-module template copy calls the shared base at 0x003AEEB3,
// copies its info payload through a null-preserving sub pointer at +0x1C
// (the Cylindrical-assignment idiom from FXParticleSystemModules.cpp),
// and installs its own vftables. All vftable dwords are DIR32 sites the
// gate takes from the target; the base call resolves through the ledger.

class Rva003AEEB3
{
public:
	Rva003AEEB3(const Rva003AEEB3 &other);
};

extern "C" char Rva003AEA42_v0a;
extern "C" char Rva003AEA42_v14a;
extern "C" char Rva003AEA42_v18a;
extern "C" char Rva003AEA42_v1ca;
extern "C" char Rva003AEA42_v0b;
extern "C" char Rva003AEA42_v14b;
extern "C" char Rva003AEA42_v18b;
extern "C" char Rva003AEA42_v1cb;

struct Rva003AEA42InfoPayload
{
	unsigned long d[32];
};

class Rva003AEA42
{
public:
	__declspec(noinline) Rva003AEA42(const Rva003AEA42 &other);

private:
	void *m_v0; // +0x00
	char m_pad04[16]; // +0x04: smart member + int, owned by the base copy
	void *m_v14; // +0x14
	void *m_v18; // +0x18
	void *m_v1c; // +0x1C: info vptr
	char m_payload[128]; // +0x20: info payload
};

// ??0Rva003AEA42@@QAE@ABV0@@Z
Rva003AEA42::Rva003AEA42(const Rva003AEA42 &that)
{
	const void *src = &that;
	((Rva003AEEB3 *)this)->Rva003AEEB3::Rva003AEEB3(*(const Rva003AEEB3 *)&that);
	const void *sub_src = src ? (const char *)src + 0x1C : 0;
	*(void **)this = &Rva003AEA42_v0a;
	*(void **)((char *)this + 0x14) = &Rva003AEA42_v14a;
	*(void **)((char *)this + 0x18) = &Rva003AEA42_v18a;
	*(void **)((char *)this + 0x1C) = &Rva003AEA42_v1ca;
	*(Rva003AEA42InfoPayload *)((char *)this + 0x20) =
		*(const Rva003AEA42InfoPayload *)((const char *)sub_src + 4);
	*(void **)this = &Rva003AEA42_v0b;
	*(void **)((char *)this + 0x14) = &Rva003AEA42_v14b;
	*(void **)((char *)this + 0x18) = &Rva003AEA42_v18b;
	*(void **)((char *)this + 0x1C) = &Rva003AEA42_v1cb;
}

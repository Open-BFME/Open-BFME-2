// ?rva006C3180@GeneralAllocatorDebug@@QAEXPAUGeneralAllocatorDebugBlock@@@Z
// partial score=0.88 date=2026-10-05
// cl: /O2 /DNDEBUG /MD
//
// 0x006C3180, 150B: GeneralAllocatorDebug::VerifyGuardFill. The body is
// frameless (no SEH handler, no EH state), so the near file's /O2 /DNDEBUG /MD
// flags suffice and no /EHsc is added; the scoped lock lives inside the callees.
//
// Evidence, all from target bytes:
//  * +0x4E4 is the lock. 0x006C25F0 and 0x006C26F0 both load it and AddRef
//    (0x00030DD0) / Release (0x00030DF0) it, the same pattern as the recovered
//    0x006C1EB0 in Rva006C1F60.cpp and the guard in Rva006C3840Cluster.cpp.
//  * +0x514 is the flag word. 0x006C1EB0 clears bit 0x800 there; retail here
//    reads it with `test ah, 8`, i.e. (m_flags & 0x800) != 0 on a 16-bit read.
//  * +0x50B is a one-byte fill value handed to the CRT fill (0x00030E20).
//  * [info + 4] bit 2 gates the check; 0x006C30C0 reads the same field with
//    `test al, 2`.
//  * `ret 4` proves one stack argument. 0x006C26F0 loads `byte [esp + 8]` as
//    an int flag and dereferences its second argument, and 0x006C2FB0Report is
//    handed the message then this, so both take the descriptor.
//  * The builder's fifth argument is an out-parameter: `lea eax, [esp + 0x14]`
//    lands on this frame's dead incoming-argument slot, and the result is read
//    back with `mov ecx, [esp + 0x10]` from the same slot, then clamped to
//    0x40. The caller keeps the descriptor in ebp, so the slot is free.
//
// Identity: the failure string at VA 0x00CE7C0C (RVA 0x008E7C0C) is
// "GeneralAllocatorDebug::VerifyGuardFill failure.", which is a direct
// target-side proof of the class and method name.
//
// 0x006C30C0 and 0x006C26F0 are unrowed retail bodies reached only from here.
// Both are pinned address-derived in reverse/symbols.csv; their names are
// candidates, not proven identities.

// CRT internal aligned-fill memset: cdecl, returns unsigned char (dst or 0).
unsigned char rva00030E20Fill(void *dst, int value, unsigned int count);

struct GeneralAllocatorDebugBlock
{
	void *m_block;               // +0x00
	unsigned int m_flags;        // +0x04, bit 2 gates the guard check
	void *m_payload;             // +0x08
	unsigned int m_pad0;         // +0x0C
	unsigned char m_guard[8];    // +0x10, start of the guard run
};

class GeneralAllocatorDebug;

// Guard-run builder: thiscall, seven stack args (runBlock, kind 0xB, 0, 0,
// outLen, 0, 0), returns the run base or 0. Unrowed retail body.
class Rva006C25F0Helper
{
public:
	void *rva006C25F0(void *runBlock, unsigned int kind, unsigned int a, unsigned int b,
		unsigned int &outLen, unsigned int c, unsigned int d);
};

// Verify-guard report helper: thiscall, two stack args (const char *message,
// void *block), popped by the callee. Unrowed retail body.
class Rva006C2FB0Helper
{
public:
	void *rva006C2FB0Report(const char *message, void *block);
};

// Pinned here, address-derived: thiscall, one stack arg.
class Rva006C30C0Helper
{
public:
	void rva006C30C0(GeneralAllocatorDebugBlock *block);
};

// Pinned here, address-derived: thiscall, two stack args (int flag, block).
class Rva006C26F0Helper
{
public:
	void rva006C26F0(int flag, GeneralAllocatorDebugBlock *block);
};

// Pinned already: thiscall, one stack arg, void.
class Rva00033E90Helper
{
public:
	void freeBlock(void *block);
};

class GeneralAllocatorDebug
{
public:
	void rva006C3180(GeneralAllocatorDebugBlock *info);

private:
	unsigned char m_pad0[0x4e4];
	void *m_lock;                               // +0x4E4
	unsigned char m_pad1[0x50b - 0x4e4 - 4];
	unsigned char m_fill;                       // +0x50B
	unsigned char m_pad2[0x514 - 0x50b - 1];
	int m_flags;                                // +0x514, bit 0x800
};

void GeneralAllocatorDebug::rva006C3180(GeneralAllocatorDebugBlock *info)
{
	if ((info->m_flags & 4) == 0 && (m_flags & 0x800) != 0) {
		unsigned int runLen;
		void *run = ((Rva006C25F0Helper *)this)->rva006C25F0(
			info->m_payload, 0xb, 0, 0, runLen, 0, 0);
		if (run != 0) {
			unsigned int len = runLen;
			if (len >= 0x40)
				len = 0x40;
			char *base = (char *)run + len;
			char *dst = (char *)run;
			char *end = (char *)info->m_payload + 8;
			if (dst < end)
				dst = end;
			if (rva00030E20Fill(dst, m_fill, (unsigned int)(base - dst)) == 0)
				((Rva006C2FB0Helper *)this)->rva006C2FB0Report(
					"GeneralAllocatorDebug::VerifyGuardFill failure.", info);
		}
	}
	((Rva006C30C0Helper *)this)->rva006C30C0(info);
	((Rva006C26F0Helper *)this)->rva006C26F0(0, info);
	((Rva00033E90Helper *)this)->freeBlock((char *)info + 8);
}

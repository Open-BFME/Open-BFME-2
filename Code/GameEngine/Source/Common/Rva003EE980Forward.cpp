// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
// stlport
//
// ?rva003EE980@Rva003EE980@@QAEXH@Z @0x003EE980 87B. Unlock lane: three-call
// forward with string g_Rva00E02E84 and triple-float struct from
// 0.95f; arg+0x44; caller at 0x004FF21E. Prev/next are the
// Rva003EE966/A1A family (// cl: /O1 /MD) plus /arch:SSE for movss.
#include <map>

typedef int Int;

#include "../../Include/Common/BfmeStringData.h"

#include "ascii_string.h"


bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class Rva004E35D5
{
public:
	void rva004E35D5(const AsciiString &key, Int a, bool b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35AF
{
public:
	void rva004E35AF(const AsciiString &key, Int a);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

class Rva004E35FF
{
public:
	void rva004E35FF(const AsciiString &key, Int a, Int b);
private:
	_STL::map<AsciiString, AsciiString> m_map;
};

// Matched DIR32 witness places this one-pointer AsciiString at VA 0x00E02E84
// in the zero-filled .data tail; the shared BFME2 header establishes its
// four-byte layout and the retail initial bytes are zero. Its retail dynamic
// initializer (0x007AF9BB) constructs it from "UnifiedEffect" through the
// out-of-line AsciiString(const char *) at 0x0000654A, as in
// Rva003EE900Forward.cpp.
#pragma inline_depth( 0 )
AsciiString g_Rva00E02E84("UnifiedEffect");
// P32 TEST-BRANCH-ONLY diagnostic: retail builds every effect-name string before 0x007AF9D6 fills the
// LivingWorldRegionEffects FieldParse entries; this image runs that fill earlier (bridged), so fill again here.
void initializeRegionEffectFields();
// ?<s_p32RegionEffectFieldsDiag> absent-from-retail
static int s_p32RegionEffectFieldsDiag = (initializeRegionEffectFields(), 0);
#pragma inline_depth()

class Rva003EE980
{
public:
	void rva003EE980(Int region);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE980::rva003EE980(Int region)
{
	char *p = (char *)region + 0x44;
	float f = 0.95f;
	float color[3];
	color[0] = f;
	color[1] = f;
	color[2] = f;
	m_owner.rva004E35D5(g_Rva00E02E84, (Int)p, 1);
	((Rva004E35FF *)&m_owner)->rva004E35FF(g_Rva00E02E84, (Int)p, (Int)&color[0]);
	((Rva004E35AF *)&m_owner)->rva004E35AF(g_Rva00E02E84, 1);
}

// ?disableUnifiedEffect@Rva003EE9D7@@QAEXH@Z @0x003EE9D7 26B. Clearing twin of the
// forward above, and skeleton twin of Rva003EE900 (Rva003EE900Forward.cpp):
// one rowed 0x004E35D5 call on the owner map at this+8 with string
// g_Rva00E02E84 and (arg+0x44, 0).
class Rva003EE9D7
{
public:
	void disableUnifiedEffect(Int region);
private:
	char m_pad[8];
	Rva004E35D5 m_owner;
};
void Rva003EE9D7::disableUnifiedEffect(Int region)
{
	m_owner.rva004E35D5(g_Rva00E02E84, (Int)((char *)region + 0x44), 0);
}

// P67 TEST-BRANCH-ONLY diagnostic (never lands): why does the dynamic vertex buffer's Lock leave a null pointer at the
// first 2D draw? Hooks the rows at run time, so no row's bytes change. Output: I:\p67_lock.log (the job dir), and on the
// failing lock a 0xE0670067 exception whose arguments carry the HRESULT and the buffer's inputs, for the receipt.
extern "C" __declspec(dllimport) int __stdcall VirtualProtect(void *, unsigned long, unsigned long, unsigned long *);
extern "C" __declspec(dllimport) void *__stdcall VirtualAlloc(void *, unsigned long, unsigned long, unsigned long);
extern "C" __declspec(dllimport) void __stdcall RaiseException(unsigned long, unsigned long, unsigned long, const unsigned long *);
extern "C" __declspec(dllimport) void *__stdcall CreateFileA(const char *, unsigned long, unsigned long, void *,
	unsigned long, unsigned long, void *);
extern "C" __declspec(dllimport) int __stdcall WriteFile(void *, const void *, unsigned long, unsigned long *, void *);
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(const char *);

extern "C"
{
	void __identifier("?Log_DX8_ErrorCode@@YAXI@Z")();
	void __identifier("??0WriteLock@DynamicVBAccessClass@@QAE@PAV1@@Z")();
	void __identifier("?Reset_Device@DX8Wrapper@@SA_N_N@Z")();
	void __identifier("?Set_Render_Device@DX8Wrapper@@KA_NHHHHH_N00@Z")();
	void __identifier("?Create_Device@DX8Wrapper@@KA_NXZ")();
	void __identifier("?_Deinit@DynamicVBAccessClass@@SAXXZ")();
	void __identifier("?_Reset@DynamicVBAccessClass@@SAX_N@Z")();
	void __identifier("?Create@BfmeDynamicNativeVB@@QAEXI@Z")();
	void __identifier("?Allocate_DX8_Dynamic_Buffer@DynamicVBAccessClass@@QAEXXZ")();
	extern unsigned int __identifier("?CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A");
	extern unsigned int __identifier("?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A");
}

namespace {

void *p67File = 0;

void p67Text(char *&out, const char *text)
{
	while (*text)
		*out++ = *text++;
}

void p67Hex(char *&out, unsigned int value)
{
	static const char digits[] = "0123456789abcdef";
	*out++ = ' ';
	for (int shift = 28; shift >= 0; shift -= 4)
		*out++ = digits[(value >> shift) & 15];
}

void p67Line(const char *tag, const unsigned int *values, int count)
{
	char line[512];
	char *out = line;
	p67Text(out, tag);
	for (int i = 0; i < count && i < 20; ++i)
		p67Hex(out, values[i]);
	*out++ = '\r';
	*out++ = '\n';
	*out = 0;
	unsigned long written = 0;
	if (p67File)
		WriteFile(p67File, line, (unsigned long)(out - line), &written, 0);
	OutputDebugStringA(line);
}

unsigned int p67Word(unsigned int address)
{
	__try
	{
		return *(const unsigned int *)address;
	}
	__except (1)
	{
		return 0xDEADBEEF;
	}
}

void __cdecl p67Entry(unsigned int tag, unsigned int edi, unsigned int esi, unsigned int ebp, unsigned int esp,
	unsigned int ebx, unsigned int edx, unsigned int ecx, unsigned int eax, unsigned int ret, unsigned int a1,
	unsigned int a2, unsigned int a3)
{
	static int allocations = 0;
	if (tag == 9 && ++allocations > 12)
		return;
	static const char *const names[] = { "?", "log-error", "?", "reset-device", "set-render-device", "create-device",
		"vb-deinit", "vb-reset", "vb-create", "vb-allocate" };
	const unsigned int values[] = { ret, ecx, a1, a2, a3 };
	p67Line(names[tag], values, 5);
}

typedef unsigned int (__fastcall *P67WriteLockFn)(unsigned int, unsigned int, unsigned int);
P67WriteLockFn p67Original = 0;

typedef long (__stdcall *P67LockFn)(unsigned int, unsigned int, unsigned int, void **, unsigned int);
typedef long (__stdcall *P67UnlockFn)(unsigned int);
typedef long (__stdcall *P67DescFn)(unsigned int, unsigned int *);
typedef long (__stdcall *P67DeviceFn)(unsigned int);

unsigned int __fastcall p67WriteLock(unsigned int self, unsigned int edx, unsigned int access)
{
	static int reports = 0;
	unsigned int result = p67Original(self, edx, access);
	unsigned int vertices = p67Word(self + 4);
	if (vertices && reports >= 4)
		return result;
	++reports;
	unsigned int type = p67Word(access + 4), index = p67Word(access + 8);
	unsigned int count = p67Word(access + 0x10) & 0xFFFF, start = p67Word(access + 0x10) >> 16;
	unsigned int buffer = p67Word(access + 0x14), stride = p67Word(p67Word(buffer + 0x14) + 0xC);
	unsigned int vertexCount = p67Word(buffer + 0xC) & 0xFFFF, d3d = p67Word(buffer + 0x1C);
	unsigned int caps = __identifier("?CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A");
	unsigned int device = __identifier("?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A");
	unsigned int desc[6] = { 0, 0, 0, 0, 0, 0 };
	long descResult = -1, cooperative = -1;
	__try
	{
		if (d3d)
			descResult = ((P67DescFn)p67Word(p67Word(d3d) + 0x34))(d3d, desc);
		if (device)
			cooperative = ((P67DeviceFn)p67Word(p67Word(device) + 0xC))(device);
	}
	__except (1)
	{
		descResult = -2;
	}
	const unsigned int inputs[] = { vertices, type, index, count, start, buffer, stride, vertexCount, d3d, device,
		(unsigned int)cooperative, p67Word(caps + 0x138) };
	p67Line("write-lock vertices type index count start buffer stride vertexCount d3d device cooperative caps138:", inputs, 12);
	const unsigned int described[] = { (unsigned int)descResult, desc[0], desc[1], desc[2], desc[3], desc[4], desc[5] };
	p67Line("vb-desc hr format type usage pool size fvf:", described, 7);
	if (vertices)
		return result;
	unsigned int offset = start * stride, size = count * stride, flags = (start ? 0x1000 : 0x2000) | 0x800;
	void *pointer = 0;
	long lockResult = -1;
	__try
	{
		if (d3d)
		{
			lockResult = ((P67LockFn)p67Word(p67Word(d3d) + 0x2C))(d3d, offset, size, &pointer, flags);
			if (lockResult == 0)
				((P67UnlockFn)p67Word(p67Word(d3d) + 0x30))(d3d);
		}
	}
	__except (1)
	{
		lockResult = -2;
	}
	const unsigned int again[] = { (unsigned int)lockResult, (unsigned int)pointer, offset, size, flags };
	p67Line("re-lock hr pointer offset size flags:", again, 5);
	static const unsigned int tries[][3] = { { 0, 0, 0 }, { 0, 0, 0x2000 }, { 0, 0xB0, 0 }, { 0, 0xB0, 0x800 } };
	for (int t = 0; t < 4; ++t)
	{
		void *tried = 0;
		long tryResult = -1;
		__try
		{
			tryResult = ((P67LockFn)p67Word(p67Word(d3d) + 0x2C))(d3d, tries[t][0], tries[t][1], &tried, tries[t][2]);
			if (tryResult == 0)
				((P67UnlockFn)p67Word(p67Word(d3d) + 0x30))(d3d);
		}
		__except (1)
		{
			tryResult = -2;
		}
		const unsigned int result2[] = { (unsigned int)tryResult, (unsigned int)tried, tries[t][0], tries[t][1], tries[t][2] };
		p67Line("try-lock hr pointer offset size flags:", result2, 5);
	}
	const unsigned int code[] = { p67Word(p67Word(d3d)), p67Word(p67Word(d3d) + 0x2C), p67Word(p67Word(d3d) + 0x30), p67Word(d3d + 4), p67Word(d3d + 8) };
	p67Line("vb-object vtable0 lock unlock word4 word8:", code, 5);
	const unsigned long arguments[] = { (unsigned long)lockResult, (unsigned long)pointer, offset, size, flags, desc[2], desc[3],
		desc[4], stride, type, index, (unsigned long)cooperative, p67Word(caps + 0x138) };
	RaiseException(0xE0670067, 0, 13, arguments);
	return result;
}

void p67Jump(unsigned char *from, const void *to)
{
	unsigned long old = 0;
	VirtualProtect(from, 5, 0x40, &old);
	from[0] = 0xE9;
	*(int *)(from + 1) = (int)((const unsigned char *)to - (from + 5));
	VirtualProtect(from, 5, old, &old);
}

unsigned char *p67Copy(unsigned char *out, const unsigned char *code, int length)
{
	for (int i = 0; i < length; ++i)
		*out++ = code[i];
	*out = 0xE9;
	*(int *)(out + 1) = (int)((code + length) - (out + 5));
	return out + 5;
}

unsigned char *p67Hook(unsigned char *out, unsigned int tag, void (*function)(), int length)
{
	unsigned char *code = (unsigned char *)function;
	unsigned char *stub = out;
	*out++ = 0x60;
	*out++ = 0x68;
	*(unsigned int *)out = tag;
	out += 4;
	*out = 0xE8;
	*(int *)(out + 1) = (int)((unsigned char *)&p67Entry - (out + 5));
	out += 5;
	*out++ = 0x83;
	*out++ = 0xC4;
	*out++ = 0x04;
	*out++ = 0x61;
	out = p67Copy(out, code, length);
	p67Jump(code, stub);
	return out;
}

int p67Install()
{
	p67File = CreateFileA("I:\\p67_lock.log", 0x40000000, 1, 0, 2, 0x80000000, 0);
	unsigned char *out = (unsigned char *)VirtualAlloc(0, 4096, 0x3000, 0x40);
	out = p67Hook(out, 1, &__identifier("?Log_DX8_ErrorCode@@YAXI@Z"), 6);
	out = p67Hook(out, 3, &__identifier("?Reset_Device@DX8Wrapper@@SA_N_N@Z"), 6);
	out = p67Hook(out, 4, &__identifier("?Set_Render_Device@DX8Wrapper@@KA_NHHHHH_N00@Z"), 6);
	out = p67Hook(out, 5, &__identifier("?Create_Device@DX8Wrapper@@KA_NXZ"), 5);
	out = p67Hook(out, 6, &__identifier("?_Deinit@DynamicVBAccessClass@@SAXXZ"), 5);
	out = p67Hook(out, 7, &__identifier("?_Reset@DynamicVBAccessClass@@SAX_N@Z"), 5);
	out = p67Hook(out, 8, &__identifier("?Create@BfmeDynamicNativeVB@@QAEXI@Z"), 7);
	out = p67Hook(out, 9, &__identifier("?Allocate_DX8_Dynamic_Buffer@DynamicVBAccessClass@@QAEXXZ"), 7);
	unsigned char *lock = (unsigned char *)&__identifier("??0WriteLock@DynamicVBAccessClass@@QAE@PAV1@@Z");
	p67Original = (P67WriteLockFn)out;
	out = p67Copy(out, lock, 7);
	p67Jump(lock, (const void *)&p67WriteLock);
	const unsigned int installed[] = { (unsigned int)lock };
	p67Line("installed", installed, 1);
	return 1;
}

int p67Installed = p67Install();

}

// P78 TEST-BRANCH-ONLY diagnostic (never lands): how often does a block from the game's allocator reach msvcr71's free,
// and how often does a block the table never saw reach the game's free? Wraps the allocator's three slots to keep a table
// of live game blocks, and stubs the __imp__free slot. No row's bytes change. Output: I:\p78_free.log (the job dir).
// A block allocated before this initializer ran is unknown to the table: the CRT count can miss one, and the game-free
// count can falsely report one. A caller binding free another way is not seen.
// extern "C" adds an underscore, so _imp__free is the __imp__free slot. These must be the real symbols: the diagnostic link
// stubs an unresolved name instead of failing, and the first form of this counter wrote to such a stub in .text.
extern "C"
{
	extern void *_imp__free;
	extern void *(__cdecl *_imp__malloc)(unsigned int);
	extern void *(__cdecl *__gameMemAllocatePtr)(unsigned int, int, const void *);
	extern void (__cdecl *__gameMemFreePtr)(void *, int);
}
extern void *__gameMemReallocatePtr;
namespace MemoryPool { void InitFunctionPointers(); }
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);

namespace {

typedef void *(__cdecl *P78AllocFn)(unsigned int, int, const void *);
typedef void (__cdecl *P78FreeFn)(void *, int);
typedef void *(__cdecl *P78ReallocFn)(void *, unsigned int, int, unsigned int);

enum { P78_SLOTS = 1 << 21, P78_CALLERS = 96 };
const unsigned int P78_GONE = 1;

void *p78File = 0;
char p78Section[64];
unsigned int *p78Table = 0;
P78AllocFn p78RealAlloc = 0;
P78FreeFn p78RealFree = 0;
P78ReallocFn p78RealRealloc = 0;
unsigned int p78Allocs = 0, p78Frees = 0, p78Unknown = 0, p78CrtFrees = 0, p78Crossings = 0, p78Full = 0, p78Events = 0;
unsigned int p78Seen[2][P78_CALLERS];
unsigned int p78Hits[2][P78_CALLERS];

void p78Line(const char *tag, const unsigned int *values, int count)
{
	static const char digits[] = "0123456789abcdef";
	char line[320];
	char *out = line;
	while (*tag && out < line + 64)
		*out++ = *tag++;
	for (int i = 0; i < count && i < 16; ++i)
	{
		*out++ = ' ';
		for (int shift = 28; shift >= 0; shift -= 4)
			*out++ = digits[(values[i] >> shift) & 15];
	}
	*out++ = '\r';
	*out++ = '\n';
	unsigned long written = 0;
	if (p78File)
		WriteFile(p78File, line, (unsigned long)(out - line), &written, 0);
}

void p78Totals()
{
	const unsigned int totals[] = { p78Allocs, p78Frees, p78Unknown, p78CrtFrees, p78Crossings, p78Full };
	p78Line("totals allocs gamefrees unknown crtfrees crossings full:", totals, 6);
}

unsigned int p78Hash(unsigned int key)
{
	return (key >> 3) * 2654435761u >> 11;
}

void p78Remember(unsigned int key)
{
	unsigned int at = p78Hash(key);
	for (int probes = 0; probes < 4096; ++probes)
	{
		unsigned int value = p78Table[at];
		if (value <= P78_GONE || value == key)
		{
			p78Table[at] = key;
			return;
		}
		at = (at + 1) & (P78_SLOTS - 1);
	}
	++p78Full;
}

bool p78Holds(unsigned int key, bool forget)
{
	unsigned int at = p78Hash(key);
	for (int probes = 0; probes < 4096; ++probes)
	{
		unsigned int value = p78Table[at];
		if (value == 0)
			return false;
		if (value == key)
		{
			if (forget)
				p78Table[at] = P78_GONE;
			return true;
		}
		at = (at + 1) & (P78_SLOTS - 1);
	}
	return false;
}

// One line per new caller, then counts: free is hot.
void p78Report(int kind, unsigned int caller, unsigned int next, unsigned int block)
{
	for (int i = 0; i < P78_CALLERS; ++i)
	{
		if (p78Seen[kind][i] == caller)
		{
			++p78Hits[kind][i];
			return;
		}
		if (p78Seen[kind][i] == 0)
		{
			p78Seen[kind][i] = caller;
			p78Hits[kind][i] = 1;
			const unsigned int values[] = { caller, next, block };
			p78Line(kind ? "unknown-block-to-game-free caller next block:" : "game-block-to-crt-free caller next block:", values, 3);
			return;
		}
	}
}

void p78Tick()
{
	if ((++p78Events & 0xFFF) == 0)
		p78Totals();
}

void *__cdecl p78Alloc(unsigned int size, int type, const void *hint)
{
	void *block = p78RealAlloc(size, type, hint);
	EnterCriticalSection(p78Section);
	++p78Allocs;
	if (block)
		p78Remember((unsigned int)block);
	p78Tick();
	LeaveCriticalSection(p78Section);
	return block;
}

void __cdecl p78Free(void *block, int type)
{
	if (block)
	{
		EnterCriticalSection(p78Section);
		++p78Frees;
		if (!p78Holds((unsigned int)block, true))
		{
			++p78Unknown;
			const unsigned int *frame = (const unsigned int *)&block;
			p78Report(1, frame[-1], frame[2], (unsigned int)block);
		}
		p78Tick();
		LeaveCriticalSection(p78Section);
	}
	p78RealFree(block, type);
}

void *__cdecl p78Realloc(void *block, unsigned int size, int type, unsigned int tag)
{
	void *moved = p78RealRealloc(block, size, type, tag);
	EnterCriticalSection(p78Section);
	if (block)
		p78Holds((unsigned int)block, true);
	if (moved)
		p78Remember((unsigned int)moved);
	LeaveCriticalSection(p78Section);
	return moved;
}

void __cdecl p78CrtFree(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int,
	unsigned int, unsigned int, unsigned int ret, unsigned int block)
{
	if (!block)
		return;
	EnterCriticalSection(p78Section);
	++p78CrtFrees;
	if (p78Holds(block, false))
	{
		++p78Crossings;
		p78Report(0, ret, 0, block);
		p78Holds(block, true);
	}
	p78Tick();
	LeaveCriticalSection(p78Section);
}

int p78Install()
{
	p78File = CreateFileA("I:\\p78_free.log", 0x40000000, 1, 0, 2, 0x80000000, 0);
	InitializeCriticalSection(p78Section);
	p78Table = (unsigned int *)VirtualAlloc(0, P78_SLOTS * 4, 0x3000, 0x04);
	const unsigned int before[] = { (unsigned int)__gameMemAllocatePtr, (unsigned int)p78Table };
	p78Line("slot-before-install table:", before, 2);
	// Fill the slots now, and make a later call a no-op so it can't overwrite the wrappers.
	MemoryPool::InitFunctionPointers();
	unsigned char *init = (unsigned char *)&MemoryPool::InitFunctionPointers;
	unsigned long old = 0;
	VirtualProtect(init, 1, 0x40, &old);
	*init = 0xC3;
	VirtualProtect(init, 1, old, &old);
	p78RealAlloc = __gameMemAllocatePtr;
	p78RealFree = __gameMemFreePtr;
	p78RealRealloc = (P78ReallocFn)__gameMemReallocatePtr;
	__gameMemAllocatePtr = &p78Alloc;
	__gameMemFreePtr = &p78Free;
	__gameMemReallocatePtr = (void *)&p78Realloc;
	unsigned char *out = (unsigned char *)VirtualAlloc(0, 4096, 0x3000, 0x40);
	unsigned char *stub = out;
	*out++ = 0x60;
	*out++ = 0x68;
	*(unsigned int *)out = 1;
	out += 4;
	*out = 0xE8;
	*(int *)(out + 1) = (int)((unsigned char *)&p78CrtFree - (out + 5));
	out += 5;
	*out++ = 0x83;
	*out++ = 0xC4;
	*out++ = 0x04;
	*out++ = 0x61;
	*out++ = 0x68;
	*(void **)out = _imp__free;
	out += 4;
	*out++ = 0xC3;
	VirtualProtect(&_imp__free, 4, 0x40, &old);
	_imp__free = stub;
	VirtualProtect(&_imp__free, 4, old, &old);
	const unsigned int installed[] = { (unsigned int)p78RealAlloc, (unsigned int)p78RealFree, (unsigned int)p78RealRealloc };
	p78Line("installed alloc free realloc:", installed, 3);
	// Positive control: a CRT block planted in the table, freed through the patched slot. It must log one crossing with this
	// function as the caller, and it is harmless because the block really is msvcr71's. Without this line a zero means nothing.
	void *planted = _imp__malloc(16);
	const unsigned int control[] = { (unsigned int)planted, (unsigned int)stub };
	p78Line("control-planting block stub:", control, 2);
	EnterCriticalSection(p78Section);
	p78Remember((unsigned int)planted);
	LeaveCriticalSection(p78Section);
	((void (__cdecl *)(void *))_imp__free)(planted);
	const unsigned int after[] = { p78CrtFrees, p78Crossings };
	p78Line("control-result crtfrees crossings (want 1 1):", after, 2);
	// The other slot's wrapper, end to end: this block must be known to the table, so the unknown count must stay 0.
	void *known = __gameMemAllocatePtr(16, 3, 0);
	__gameMemFreePtr(known, 3);
	const unsigned int after2[] = { p78Allocs, p78Frees, p78Unknown };
	p78Line("control-result allocs gamefrees unknown (want 1 1 0):", after2, 3);
	return 1;
}

int p78Installed = p78Install();

}

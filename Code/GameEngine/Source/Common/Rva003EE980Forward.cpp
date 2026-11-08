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
extern "C" __declspec(dllimport) unsigned long __stdcall GetCurrentThreadId(void);
extern "C" __declspec(dllimport) int __stdcall IsWindow(void *);
extern "C" unsigned int __cdecl _control87(unsigned int, unsigned int);

extern "C"
{
	extern void *__identifier("__imp__ExitProcess@4");
	extern void *__identifier("__imp__TerminateProcess@8");
	extern void *__identifier("__imp__abort");
	extern void *__identifier("__imp__exit");
	extern void *__identifier("__imp___exit");
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
	extern unsigned int __identifier("?g_00DFE9E0@@3UDisplayCriticalSection@@A")[2];
	extern double __identifier("?g_bfmeVM0Scale@@3NA");
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
		"vb-deinit", "vb-reset", "vb-create", "vb-allocate", "ExitProcess", "TerminateProcess", "abort", "exit", "_exit" };
	const unsigned int values[] = { ret, ecx, a1, a2, a3, (unsigned int)GetCurrentThreadId() };
	p67Line(names[tag], values, 6);
	if (tag >= 10)
	{
		const unsigned int *stack = (const unsigned int *)esp;
		for (int row = 0; row < 8; ++row)
		{
			unsigned int words[8];
			for (int i = 0; i < 8; ++i)
				words[i] = p67Word((unsigned int)(stack + row * 8 + i));
			p67Line("  stack", words, 8);
		}
	}
}

typedef unsigned int (__fastcall *P67WriteLockFn)(unsigned int, unsigned int, unsigned int);
P67WriteLockFn p67Original = 0;

typedef long (__stdcall *P67LockFn)(unsigned int, unsigned int, unsigned int, void **, unsigned int);
typedef long (__stdcall *P67UnlockFn)(unsigned int);
typedef long (__stdcall *P67DescFn)(unsigned int, unsigned int *);
typedef long (__stdcall *P67DeviceFn)(unsigned int);
typedef long (__stdcall *P67DeviceOutFn)(unsigned int, unsigned int *);

P67LockFn p67RealLock = 0;

long __stdcall p67Lock(unsigned int self, unsigned int offset, unsigned int size, void **data, unsigned int flags)
{
	static int calls = 0;
	const unsigned int before[] = { self, offset, size, flags, (unsigned int)GetCurrentThreadId(), _control87(0, 0) };
	if (calls < 12)
		p67Line("real-lock in self offset size flags thread fpu:", before, 6);
	long result = p67RealLock(self, offset, size, data, flags);
	const unsigned int after[] = { (unsigned int)result, data ? (unsigned int)*data : 0 };
	if (calls < 12 || !(data && *data))
		p67Line("real-lock out hr pointer:", after, 2);
	++calls;
	return result;
}

unsigned int __fastcall p67WriteLock(unsigned int self, unsigned int edx, unsigned int access)
{
	static int reports = 0;
	if (!p67RealLock)
	{
		unsigned int early = p67Word(access + 0x14);
		unsigned int object = early ? p67Word(early + 0x1C) : 0;
		if (object)
		{
			unsigned int *slot = (unsigned int *)(p67Word(object) + 0x2C);
			unsigned long old = 0;
			p67RealLock = (P67LockFn)*slot;
			VirtualProtect(slot, 4, 0x40, &old);
			*slot = (unsigned int)&p67Lock;
			VirtualProtect(slot, 4, old, &old);
			const unsigned int wrapped[] = { (unsigned int)slot, (unsigned int)p67RealLock };
			p67Line("wrapped Lock slot real:", wrapped, 2);
		}
	}
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
	unsigned int created[4] = { 0, 0, 0, 0 }, mode[4] = { 0, 0, 0, 0 };
	long createdResult = -1, modeResult = -1;
	__try
	{
		if (device)
		{
			createdResult = ((P67DeviceOutFn)p67Word(p67Word(device) + 0x24))(device, created);
			modeResult = ((P67DeviceOutFn)p67Word(p67Word(device) + 0x20))(device, mode);
		}
	}
	__except (1)
	{
		createdResult = -2;
	}
	const unsigned int deviceState[] = { (unsigned int)createdResult, created[0], created[1], created[2], created[3],
		(unsigned int)IsWindow((void *)created[2]), (unsigned int)modeResult, mode[0], mode[1], mode[3],
		(unsigned int)GetCurrentThreadId(), _control87(0, 0), p67Word((unsigned int)&__identifier("__imp__ExitProcess@4")) };
	p67Line("device hr adapter type window behavior isWindow modeHr width height format thread fpu exit:", deviceState, 13);
	const double scale = __identifier("?g_bfmeVM0Scale@@3NA");
	const unsigned int timer[] = { __identifier("?g_00DFE9E0@@3UDisplayCriticalSection@@A")[0], __identifier("?g_00DFE9E0@@3UDisplayCriticalSection@@A")[1], ((const unsigned int *)&scale)[0], ((const unsigned int *)&scale)[1] };
	p67Line("timer frequency-lo frequency-hi scale-lo scale-hi:", timer, 4);
	if (vertices)
		return result;
	const unsigned int abouts[] = { d3d, p67Word(d3d), p67Word(p67Word(d3d) + 0x2C), p67Word(d3d + 4), p67Word(d3d + 8) };
	p67Line("about to re-lock object vtable lock word4 word8:", abouts, 5);
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
	void **slots[] = { &__identifier("__imp__ExitProcess@4"), &__identifier("__imp__TerminateProcess@8"), &__identifier("__imp__abort"),
		&__identifier("__imp__exit"), &__identifier("__imp___exit") };
	for (int i = 0; i < 5; ++i)
	{
		unsigned char *stub = out;
		*out++ = 0x60;
		*out++ = 0x68;
		*(unsigned int *)out = 10 + i;
		out += 4;
		*out = 0xE8;
		*(int *)(out + 1) = (int)((unsigned char *)&p67Entry - (out + 5));
		out += 5;
		*out++ = 0x83;
		*out++ = 0xC4;
		*out++ = 0x04;
		*out++ = 0x61;
		*out++ = 0x68;
		*(void **)out = *slots[i];
		out += 4;
		*out++ = 0xC3;
		unsigned long old = 0;
		VirtualProtect(slots[i], 4, 0x40, &old);
		*slots[i] = stub;
		VirtualProtect(slots[i], 4, old, &old);
	}
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

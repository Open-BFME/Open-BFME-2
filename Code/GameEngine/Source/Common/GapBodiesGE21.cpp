// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// CRT replacement shims from .text gaps no Ghidra function covers, between
// the matched wwmath wrappers (0x0002FBC0) and mem_ops.cpp's operator
// new/delete (0x0002FD60..0x0002FDE0). Each begins after its neighbour's
// padding and ends in its own ret or tail jump. They route the C heap through
// the game's pluggable memory-manager slots, the counterparts of BFME 1's
// Rva00881D70CrtShims.cpp (donor shapes only: BFME 2's allocate slot takes a
// third tag word, read from these bodies). The inlined strlen/strcpy loops and
// the rep stos memset are the /O2 intrinsic forms. Names stay address-derived
// except the two operator new overloads, whose ABI is the one Zero Hour's
// GameMemory.h declares for the file/line forms.
#include <mbstring.h>
#include <string.h>
#include <stdlib.h>

typedef void *(__cdecl *GameAllocateFunction)(unsigned int, int, const void *);
extern "C" GameAllocateFunction __gameMemAllocatePtr;	// VA 0x00DE0404

namespace _STL
{
	template <class T> class allocator;
	template <> class allocator<char>
	{
	public:
		static char *allocate(unsigned int n, const void *hint);	// 0x000307F0
	};
}

// Tag the duplicating shims pass to the byte allocator: the multi-character
// constant 'str' (dword 0x00737472 in the pushes).
#define GAP_RTS_TAG ((const void *)'str')

// --- 0x0002FBD0 (54B): calloc: count*size bytes, class 0, zero-filled.
void *rva0002FBD0(unsigned int count, unsigned int size)
{
	unsigned int bytes = count * size;
	void *block = __gameMemAllocatePtr(bytes, 0, 0);
	if (block)
		memset(block, 0, bytes);
	return block;
}

// --- 0x0002FC60 (19B): malloc: class 0.
void *rva0002FC60(unsigned int size)
{
	return __gameMemAllocatePtr(size, 0, 0);
}

// --- 0x0002FC80 (24B): _msize: the block's size through the null-guarded
// block-size forwarder 0x00030860, with the heap word the block-heap slot
// (VA 0x00DE03F0, ?_GetBlockHeap@MemoryPool@@YAIPAX@Z) reports.
extern void *__gameMemGetBlockHeapPtr;
unsigned int rva00030860(void *block, unsigned int heap);


// --- 0x0002FCA0 (24B): realloc through the resize slot VA 0x00DE0400 with
// two zero words.
extern void *__gameMemReallocatePtr;


// --- 0x0002FCC0 (68B): strdup through the rowed allocator<char>::allocate.
char *rva0002FCC0(const char *source)
{
	if (source)
	{
		char *copy = _STL::allocator<char>::allocate(strlen(source) + 1, GAP_RTS_TAG);
		if (copy)
			return strcpy(copy, source);
	}
	return 0;
}

// --- 0x0002FD10 (58B): wcsdup through the same allocator, msvcr71 wcslen
// and wcscpy imports.
wchar_t *rva0002FD10(const wchar_t *source)
{
	if (source)
	{
		wchar_t *copy = (wchar_t *)_STL::allocator<char>::allocate(wcslen(source) * 2 + 2, GAP_RTS_TAG);
		if (copy)
			return wcscpy(copy, source);
	}
	return 0;
}

// --- 0x0002FD50 (6B): _mbsdup forwarder (tail jump through the import).

unsigned char *rva0002FD50(const unsigned char *source)
{
	return _mbsdup(source);
}

// --- 0x0002FDC0 / 0x0002FE00 (22B each): the file/line operator new forms,
// class 1 scalar and class 2 array, tail-jumping into the allocate slot over
// their own argument words.
void *__cdecl operator new(unsigned int size, const char *, int)
{
	return __gameMemAllocatePtr(size, 1, 0);
}

void *__cdecl operator new[](unsigned int size, const char *, int)
{
	return __gameMemAllocatePtr(size, 2, 0);
}

// --- 0x0002FFA0 (25B): run the resolver 0x00030730 (its WorldBuilder
// identity MemoryPool::InitFunctionPointers), register the slot at
// VA 0x00DE040C with atexit, then tail-call the slot at VA 0x00DE0410.
namespace MemoryPool { void InitFunctionPointers(); }
extern void *__gameMemExitPtr;
extern void *__gameMemInitPtr;


// --- 0x0002F980 (22B): the registry block's once-gate on its own, ahead of
// the getters at 0x0002F9C0 that inline the same test; tail-jumps to the
// rowed LoadRegistryValues 0x0002F840.
extern bool g_registryValuesLoaded;
void LoadRegistryValues();

void rva0002F980()
{
	if (!g_registryValuesLoaded)
	{
		g_registryValuesLoaded = true;
		LoadRegistryValues();
	}
}

// Unreferenced leaves from the /O2 regions (twins.tsv leads): the full
// dword store and the load-then-test byte read are /O2 forms.
// 0x000657B3 (9B): constructor zeroing the word at +0.
class Rva000657B3
{
public:
	Rva000657B3();
private:
	int m_00;
};

Rva000657B3::Rva000657B3() : m_00(0)
{
}

// 0x0001D1D0 (11B): whether the byte at +0x0E is set.
class Rva0001D1D0
{
public:
	bool rva0001D1D0() const;
private:
	char m_pad[0x0E];
	unsigned char m_0E;
};

bool Rva0001D1D0::rva0001D1D0() const
{
	return m_0E != 0;
}

// 0x00030E10 (8B): the word at +0x18 of a record passed by pointer (the
// shape of STLport's _FILE_I_begin over a stdio FILE).
struct Rva00030E10Record
{
	char m_pad[0x18];
	int m_18;
};

int rva00030E10(const Rva00030E10Record *record)
{
	return record->m_18;
}

// Unreferenced virtual-slot forwarders: each calls one slot of its own
// object with no arguments, a tail jump through the vtable (mov eax,[ecx];
// jmp [eax+4*slot]). Owners are address-derived views of the slots used.
// 0x00013280: slot 6.
class Rva00013280Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	void rva00013280();
};

void Rva00013280Slots::rva00013280()
{
	slot06();
}

// 0x00013290: slot 10.
class Rva00013290Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	void rva00013290();
};

void Rva00013290Slots::rva00013290()
{
	slot10();
}

// 0x00013380, 0x00013390, 0x000133A0: slots 4, 5 and 7, three CC-padded
// forwarders in the STLport fstream run. Lead only: slots 4/5/7 of the
// codecvt vftables (0x007BBB08, 0x007BBB2C) are do_encoding,
// do_always_noconv and do_max_length, so these read as codecvt's encoding(),
// always_noconv() and max_length(); the char and wchar_t instantiations are
// byte-identical and nothing references these copies, so the owner stays an
// address-derived view.
class Rva00013380Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	void rva00013380();
	void rva00013390();
	void rva000133A0();
};

void Rva00013380Slots::rva00013380()
{
	slot04();
}

void Rva00013380Slots::rva00013390()
{
	slot05();
}

void Rva00013380Slots::rva000133A0()
{
	slot07();
}

// 0x000184E0: slot 8.
class Rva000184E0Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	void rva000184E0();
};

void Rva000184E0Slots::rva000184E0()
{
	slot08();
}

// 0x000184F0: slot 12.
class Rva000184F0Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	void rva000184F0();
};

void Rva000184F0Slots::rva000184F0()
{
	slot12();
}

// 0x0001C8B0: slot 11.
class Rva0001C8B0Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	void rva0001C8B0();
};

void Rva0001C8B0Slots::rva0001C8B0()
{
	slot11();
}

// 0x0001D170: slot 3.
class Rva0001D170Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	void rva0001D170();
};

void Rva0001D170Slots::rva0001D170()
{
	slot03();
}

// 0x00035790: slot 0.
class Rva00035790Slots
{
public:
	virtual void slot00();
	void rva00035790();
};

void Rva00035790Slots::rva00035790()
{
	slot00();
}

// 0x000357F0: slot 2.
class Rva000357F0Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	void rva000357F0();
};

void Rva000357F0Slots::rva000357F0()
{
	slot02();
}

// 0x00021280 (5B), unreferenced: return the fifth argument.
int rva00021280(int, int, int, int, int fifth)
{
	return fifth;
}

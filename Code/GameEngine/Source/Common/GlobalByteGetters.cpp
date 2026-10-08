// cl: /GX-
// Global byte getters, each `mov al,[mem]; ret` (6B), ported from Open-BFME-1
// (same shape as its GlobalDwordGetters file, byte-width). Each reads one
// .data byte global into AL; identity unrecoverable, so globals and functions
// are address-derived (g_Va<VA> / Rva<RVA>GetByte). One shared TU, one row
// per body.

// ?Rva0004CAB1GetByte@@YAEXZ @ 0x0004CAB1 (6B) over 0x00DB5F7D.

extern unsigned char g_Va00DB5F7D;
// g_Va00DB5F7D: matched references place it at VA 0xdb5f7d (retail .data initial value 1).
unsigned char g_Va00DB5F7D = 1;

unsigned char Rva0004CAB1GetByte(void)
{
	return g_Va00DB5F7D;
}

// ?Rva0004CAB7GetByte@@YAEXZ @ 0x0004CAB7 (6B) over 0x00DEC3D9.

extern unsigned char g_Va00DEC3D9;
// ?g_Va00DEC3D9@@3EA: the global at this VA is ?AreStaticSortListsEnabled@WW3D@@0_NA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00DEC3D9@@3EA=?AreStaticSortListsEnabled@WW3D@@0_NA")

unsigned char Rva0004CAB7GetByte(void)
{
	return g_Va00DEC3D9;
}

// ?Rva00131062GetByte@@YAEXZ @ 0x00131062 (6B) over 0x00DB5F98.

extern unsigned char g_Va00DB5F98;
// ?g_Va00DB5F98@@3EA: the global at this VA is ?IsTexturingEnabled@WW3D@@0_NA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00DB5F98@@3EA=?IsTexturingEnabled@WW3D@@0_NA")

unsigned char Rva00131062GetByte(void)
{
	return g_Va00DB5F98;
}

// ?Rva00131068GetByte@@YAEXZ @ 0x00131068 (6B) over 0x00DEDA04.

extern unsigned char g_Va00DEDA04;
// ?g_Va00DEDA04@@3EA: the global at this VA is ?IsInitted@DX8Wrapper@@1_NA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00DEDA04@@3EA=?IsInitted@DX8Wrapper@@1_NA")

unsigned char Rva00131068GetByte(void)
{
	return g_Va00DEDA04;
}

// ?Rva0006E19BGetByte@@YAEXZ @ 0x0006E19B (6B) over 0x00DB5FCD.

extern unsigned char g_Va00DB5FCD;
// ?g_Va00DB5FCD@@3EA: the global at this VA is ?_EnableTriangleDraw@DX8Wrapper@@1_NA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00DB5FCD@@3EA=?_EnableTriangleDraw@DX8Wrapper@@1_NA")

unsigned char Rva0006E19BGetByte(void)
{
	return g_Va00DB5FCD;
}

// ?Rva0006E1A1GetByte@@YAEXZ @ 0x0006E1A1 (6B) over 0x00DEDA05.

extern unsigned char g_Va00DEDA05;
// ?g_Va00DEDA05@@3EA: the global at this VA is ?bfmeCameraProjectionOverride@@3_NA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00DEDA05@@3EA=?bfmeCameraProjectionOverride@@3_NA")

unsigned char Rva0006E1A1GetByte(void)
{
	return g_Va00DEDA05;
}

// ?Rva00110094GetByte@@YAEXZ @ 0x00110094 (6B) over 0x00DEC3D7.

extern unsigned char g_Va00DEC3D7;
// g_Va00DEC3D7: matched references place it at VA 0xdec3d7 (zero-filled .bss).
unsigned char g_Va00DEC3D7;

unsigned char Rva00110094GetByte(void)
{
	return g_Va00DEC3D7;
}

// ?Rva000308D0GetByte@@YAEXZ @ 0x000308D0 (6B) over 0x00DE0818.
// TU-scoped minimal HeapTable view (+0x404 only). Same tag so ?g_heaps@MemoryPool@@3UHeapTable@1@A
// resolves to the single memory_pool.cpp BSS definition. Size 0x410, member at +0x404.
// No second definition, no /alternatename, no initializer, no header edit.
namespace MemoryPool
{
struct HeapTable
{
	unsigned char _pad404[0x404];
	bool m_clearAllocations;
	unsigned char _tail[0x410 - 0x405];
};

extern HeapTable g_heaps;
} // namespace MemoryPool

unsigned char Rva000308D0GetByte(void)
{
	return MemoryPool::g_heaps.m_clearAllocations;
}

// ?Rva00116F70GetByte@@YAEXZ @ 0x00116F70 (6B) over 0x00DEDA06.

extern unsigned char g_Va00DEDA06;

unsigned char Rva00116F70GetByte(void)
{
	return g_Va00DEDA06;
}

// ?Rva00171650GetByte@@YAEXZ @ 0x00171650 (6B) over 0x00DEC410.

extern unsigned char g_Va00DEC410;
// g_Va00DEC410: matched references place it at VA 0xdec410 (zero-filled .bss).
unsigned char g_Va00DEC410;

unsigned char Rva00171650GetByte(void)
{
	return g_Va00DEC410;
}

// ?Rva00171670GetByte@@YAEXZ @ 0x00171670 (6B) over 0x00DEC3DA.

extern unsigned char g_Va00DEC3DA;
// ?g_Va00DEC3DA@@3EA: the global at this VA is ?MungeSortOnLoad@WW3D@@0_NA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00DEC3DA@@3EA=?MungeSortOnLoad@WW3D@@0_NA")

unsigned char Rva00171670GetByte(void)
{
	return g_Va00DEC3DA;
}
// ?g_Va00DEDA06@@3EA: the global at VA 0xdeda06 is ?IsWindowed@DX8Wrapper@@1_NA.
#pragma comment(linker, "/alternatename:?g_Va00DEDA06@@3EA=?IsWindowed@DX8Wrapper@@1_NA")

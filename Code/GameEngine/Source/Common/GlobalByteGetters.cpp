// cl: /GX- C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// Global byte getters, each `mov al,[mem]; ret` (6B), ported from Open-BFME-1
// (same shape as its GlobalDwordGetters file, byte-width). Each reads one
// .data byte global into AL; identity unrecoverable, so functions are
// address-derived (g_Va<VA> / Rva<RVA>GetByte). One shared TU, one row
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

// Reuse ww3d.cpp's and dx8wrapper.cpp's private/protected static bytes through
// TU-scoped friend views: the friends keep each member's real decoration
// (?X@WW3D@@0_NA, ?X@DX8Wrapper@@1_NA) without a second datum or an alias.
#include "../../../Libraries/Source/WWVegas/WW3D2/WW3DClass.h"

class DX8Wrapper
{
	friend unsigned char Rva00131068GetByte(void);
	friend unsigned char Rva0006E19BGetByte(void);
	friend unsigned char Rva00116F70GetByte(void);
protected:
	static bool IsInitted;
	static bool _EnableTriangleDraw;
	static bool IsWindowed;
};

extern bool bfmeCameraProjectionOverride;

unsigned char Rva0004CAB7GetByte(void)
{
	return WW3D::AreStaticSortListsEnabled;
}

// ?Rva00131062GetByte@@YAEXZ @ 0x00131062 (6B) over 0x00DB5F98.

unsigned char Rva00131062GetByte(void)
{
	return WW3D::IsTexturingEnabled;
}

// ?Rva00131068GetByte@@YAEXZ @ 0x00131068 (6B) over 0x00DEDA04.

unsigned char Rva00131068GetByte(void)
{
	return DX8Wrapper::IsInitted;
}

// ?Rva0006E19BGetByte@@YAEXZ @ 0x0006E19B (6B) over 0x00DB5FCD.

unsigned char Rva0006E19BGetByte(void)
{
	return DX8Wrapper::_EnableTriangleDraw;
}

// ?Rva0006E1A1GetByte@@YAEXZ @ 0x0006E1A1 (6B) over 0x00DEDA05.

unsigned char Rva0006E1A1GetByte(void)
{
	return bfmeCameraProjectionOverride;
}

// ?Rva00110094GetByte@@YAEXZ @ 0x00110094 (6B) over 0x00DEC3D7.

unsigned char Rva00110094GetByte(void)
{
	return WW3D::IsScreenUVBiased;
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

unsigned char Rva00116F70GetByte(void)
{
	return DX8Wrapper::IsWindowed;
}

// ?Rva00171650GetByte@@YAEXZ @ 0x00171650 (6B) over 0x00DEC410.

extern unsigned char LODMeshCacheSetting;
// LODMeshCacheSetting: matched references place it at VA 0xdec410 (zero-filled .bss).
unsigned char LODMeshCacheSetting;

unsigned char Rva00171650GetByte(void)
{
	return LODMeshCacheSetting;
}

// ?Rva00171670GetByte@@YAEXZ @ 0x00171670 (6B) over 0x00DEC3DA.

unsigned char Rva00171670GetByte(void)
{
	return WW3D::MungeSortOnLoad;
}

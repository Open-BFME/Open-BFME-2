// Cold-slice global-int returners without vtable carriage (twin-free TU).
//
// Same discipline as ConstGlobalGetters.cpp (opaque address-derived names for
// unclaimed leaves with no callers, no branch sources and no .rdata vtable
// slot) but kept in a separate TU to avoid contending with that file's active
// worker. Each is the 6-byte shape (mov eax,[global] / ret), follows int3
// (prev CC) with CC padding after, so the boundary is proven.
// No // cl: line (defaults match the frameless 6-byte shape).
//
// The G00xxxxxx externs are address-derived placeholders (DIR32 sites the
// verifier fills from retail) and carry no type information beyond int.

// ?Rva00139450Get@@YAHXZ @ 0x00139450 (6B): returns global at 0x9F2A40.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G009F2A40;
// G009F2A40: matched references place it at VA 0xdf2a40 (zero-filled .bss).
int G009F2A40;
int Rva00139450Get(void)
{
	return G009F2A40;
}

// ?Rva00139460Get@@YAHXZ @ 0x00139460 (6B): returns global at 0x9F2A84.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G009F2A84;
// G009F2A84: matched references place it at VA 0xdf2a84 (zero-filled .bss).
int G009F2A84;
int Rva00139460Get(void)
{
	return G009F2A84;
}

// ?Rva00139470Get@@YAHXZ @ 0x00139470 (6B): returns global at 0x9F2A00.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G009F2A00;
// G009F2A00: matched references place it at VA 0xdf2a00 (zero-filled .bss).
int G009F2A00;
int Rva00139470Get(void)
{
	return G009F2A00;
}

// ?Rva0011CDB0Get@@YAHXZ @ 0x0011CDB0 (6B): returns global at 0x9ED5EC.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G009ED5EC;
// G009ED5EC: matched references place it at VA 0xded5ec (zero-filled .bss).
int G009ED5EC;
int Rva0011CDB0Get(void)
{
	return G009ED5EC;
}

// ?Rva00120130Get@@YAHXZ @ 0x00120130 (6B): returns global at 0x9EE5D0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G009EE5D0;
// G009EE5D0: matched references place it at VA 0xdee5d0 (zero-filled .bss).
int G009EE5D0;
int Rva00120130Get(void)
{
	return G009EE5D0;
}

// ?Rva00129450Get@@YAHXZ @ 0x00129450 (6B): returns global at 0x9B5F94.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G009B5F94;
int Rva00129450Get(void)
{
	return G009B5F94;
}

// ?Rva0011D250Get@@YAHXZ @ 0x0011D250 (6B): returns global at 0xDEDAB0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DEDAB0;
// G00DEDAB0: matched references place it at VA 0xdedab0 (zero-filled .bss).
int G00DEDAB0;
int Rva0011D250Get(void)
{
	return G00DEDAB0;
}

// ?Rva0011D260Get@@YAHXZ @ 0x0011D260 (6B): returns global at 0xDEDAB4.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DEDAB4;
// G00DEDAB4: matched references place it at VA 0xdedab4 (zero-filled .bss).
int G00DEDAB4;
int Rva0011D260Get(void)
{
	return G00DEDAB4;
}

// ?Rva0011D270Get@@YAHXZ @ 0x0011D270 (6B): returns global at 0xDEDAB8.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DEDAB8;
// G00DEDAB8: matched references place it at VA 0xdedab8 (zero-filled .bss).
int G00DEDAB8;
int Rva0011D270Get(void)
{
	return G00DEDAB8;
}

// ?Rva0011D280Get@@YAHXZ @ 0x0011D280 (6B): returns global at 0xDEDABC.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DEDABC;
// G00DEDABC: matched references place it at VA 0xdedabc (zero-filled .bss).
int G00DEDABC;
int Rva0011D280Get(void)
{
	return G00DEDABC;
}

// ?Rva0011D290Get@@YAHXZ @ 0x0011D290 (6B): returns global at 0xDEDAC0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DEDAC0;
// G00DEDAC0: matched references place it at VA 0xdedac0 (zero-filled .bss).
int G00DEDAC0;
int Rva0011D290Get(void)
{
	return G00DEDAC0;
}

// ?Rva0011D2A0Get@@YAHXZ @ 0x0011D2A0 (6B): returns global at 0xDEDA84.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DEDA84;
// ?G00DEDA84@@3HA: the global at this VA is ?FrameCount@DX8Wrapper@@1KA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00DEDA84@@3HA=?FrameCount@DX8Wrapper@@1KA")
int Rva0011D2A0Get(void)
{
	return G00DEDA84;
}

// ?Rva001432A0Get@@YAHXZ @ 0x001432A0 (6B): returns global at 0xDEC3E0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DEC3E0;
// ?G00DEC3E0@@3HA: the global at this VA is ?FrameCount@WW3D@@0HA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00DEC3E0@@3HA=?FrameCount@WW3D@@0HA")
int Rva001432A0Get(void)
{
	return G00DEC3E0;
}

// ?Rva00143300Get@@YAHXZ @ 0x00143300 (6B): returns global at 0xDEDA78.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DEDA78;
// G00DEDA78: matched references place it at VA 0xdeda78 (zero-filled .bss).
int G00DEDA78;
int Rva00143300Get(void)
{
	return G00DEDA78;
}

// ?Rva00187F30Get@@YAHXZ @ 0x00187F30 (6B): returns global at 0xDB5F88.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DB5F88;
// G00DB5F88: matched references place it at VA 0xdb5f88 (retail .data initial value 1).
int G00DB5F88 = 1;
int Rva00187F30Get(void)
{
	return G00DB5F88;
}

// ?Rva001B6390Get@@YAHXZ @ 0x001B6390 (6B): returns global at 0xDFDA54.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00DFDA54;
// G00DFDA54: VA 0xdfda54 (zero-filled .bss).
int G00DFDA54;
int Rva001B6390Get(void)
{
	return G00DFDA54;
}

// ?Rva00610F10Get@@YAHXZ @ 0x00610F10 (6B): returns global at 0xE08C48.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08C48;
// ?G00E08C48@@3HA: the global at this VA is ?FeatureBits@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08C48@@3HA=?FeatureBits@CPUDetectClass@@0IA")
int Rva00610F10Get(void)
{
	return G00E08C48;
}

// ?Rva00610F20Get@@YAHXZ @ 0x00610F20 (6B): returns global at 0xE08CF0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08CF0;
// ?G00E08CF0@@3HA: the global at this VA is ?ExtendedFeatureBits@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08CF0@@3HA=?ExtendedFeatureBits@CPUDetectClass@@0IA")
int Rva00610F20Get(void)
{
	return G00E08CF0;
}

// ?Rva00610F30Get@@YAHXZ @ 0x00610F30 (6B): returns global at 0xE08C44.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08C44;
// ?G00E08C44@@3HA: the global at this VA is ?L2CacheSize@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08C44@@3HA=?L2CacheSize@CPUDetectClass@@0IA")
int Rva00610F30Get(void)
{
	return G00E08C44;
}

// ?Rva00610F40Get@@YAHXZ @ 0x00610F40 (6B): returns global at 0xE08CA0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08CA0;
// ?G00E08CA0@@3HA: the global at this VA is ?L2CacheLineSize@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08CA0@@3HA=?L2CacheLineSize@CPUDetectClass@@0IA")
int Rva00610F40Get(void)
{
	return G00E08CA0;
}

// ?Rva00610F50Get@@YAHXZ @ 0x00610F50 (6B): returns global at 0xE08CA4.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08CA4;
// ?G00E08CA4@@3HA: the global at this VA is ?L2CacheSetAssociative@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08CA4@@3HA=?L2CacheSetAssociative@CPUDetectClass@@0IA")
int Rva00610F50Get(void)
{
	return G00E08CA4;
}

// ?Rva00610F60Get@@YAHXZ @ 0x00610F60 (6B): returns global at 0xE08C28.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08C28;
// ?G00E08C28@@3HA: the global at this VA is ?L1DataCacheSize@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08C28@@3HA=?L1DataCacheSize@CPUDetectClass@@0IA")
int Rva00610F60Get(void)
{
	return G00E08C28;
}

// ?Rva00610F70Get@@YAHXZ @ 0x00610F70 (6B): returns global at 0xE08CC0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08CC0;
// ?G00E08CC0@@3HA: the global at this VA is ?L1DataCacheLineSize@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08CC0@@3HA=?L1DataCacheLineSize@CPUDetectClass@@0IA")
int Rva00610F70Get(void)
{
	return G00E08CC0;
}

// ?Rva00610F80Get@@YAHXZ @ 0x00610F80 (6B): returns global at 0xE08D08.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08D08;
// ?G00E08D08@@3HA: the global at this VA is ?L1DataCacheSetAssociative@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08D08@@3HA=?L1DataCacheSetAssociative@CPUDetectClass@@0IA")
int Rva00610F80Get(void)
{
	return G00E08D08;
}

// ?Rva00610F90Get@@YAHXZ @ 0x00610F90 (6B): returns global at 0xE08CD8.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08CD8;
// ?G00E08CD8@@3HA: the global at this VA is ?L1InstructionCacheSize@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08CD8@@3HA=?L1InstructionCacheSize@CPUDetectClass@@0IA")
int Rva00610F90Get(void)
{
	return G00E08CD8;
}

// ?Rva00610FA0Get@@YAHXZ @ 0x00610FA0 (6B): returns global at 0xE08CC4.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08CC4;
// ?G00E08CC4@@3HA: the global at this VA is ?L1InstructionCacheLineSize@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08CC4@@3HA=?L1InstructionCacheLineSize@CPUDetectClass@@0IA")
int Rva00610FA0Get(void)
{
	return G00E08CC4;
}

// ?Rva00610FB0Get@@YAHXZ @ 0x00610FB0 (6B): returns global at 0xE08C40.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08C40;
// ?G00E08C40@@3HA: the global at this VA is ?L1InstructionCacheSetAssociative@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08C40@@3HA=?L1InstructionCacheSetAssociative@CPUDetectClass@@0IA")
int Rva00610FB0Get(void)
{
	return G00E08C40;
}

// ?Rva00610FC0Get@@YAHXZ @ 0x00610FC0 (6B): returns global at 0xE08CFC.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08CFC;
// ?G00E08CFC@@3HA: the global at this VA is ?L1InstructionTraceCacheSize@CPUDetectClass@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08CFC@@3HA=?L1InstructionTraceCacheSize@CPUDetectClass@@0IA")
int Rva00610FC0Get(void)
{
	return G00E08CFC;
}

// ?Rva00611020Get@@YAHXZ @ 0x00611020 (6B): returns global at 0xE08D24.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E08D24;
// ?G00E08D24@@3HA: the global at this VA is ?ProcessorType@CPUDetectClass@@0HA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G00E08D24@@3HA=?ProcessorType@CPUDetectClass@@0HA")
int Rva00611020Get(void)
{
	return G00E08D24;
}

// ?Rva0069BD50Get@@YAHXZ @ 0x0069BD50 (6B): returns global at 0xE0BE00.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
extern int G00E0BE00;
// G00E0BE00: VA 0xe0be00 (zero-filled .bss).
int G00E0BE00;
int Rva0069BD50Get(void)
{
	return G00E0BE00;
}

// ?Rva006C5E70Get@@YAHXZ @ 0x006C5E70 (6B): returns ProfileId::first (0xE0C620,
// defined in profile/profile_highlevel.cpp); inside that unit's address range.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
#include "../../../Libraries/Source/profile/internal_highlevel.h"

int Rva006C5E70Get(void)
{
	return (int)ProfileId::GetFirst();
}

// ?G009B5F94@@3HA: the global at this VA is ?NPatchesLevel@WW3D@@0IA; this name is an alias for it.
#pragma comment(linker, "/alternatename:?G009B5F94@@3HA=?NPatchesLevel@WW3D@@0IA")
#pragma comment(linker, "/alternatename:?NPatchesLevel@@3IA=?NPatchesLevel@WW3D@@0IA")
// ?G009B5F94@@3HA: the global at VA 0xdb5f94 is ?NPatchesLevel@WW3D@@0IA.
#pragma comment(linker, "/alternatename:?G009B5F94@@3HA=?NPatchesLevel@WW3D@@0IA")

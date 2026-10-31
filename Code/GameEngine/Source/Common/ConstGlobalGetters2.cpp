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

// Retail globals the getters below read, declared as minimal views of the
// real classes (the data ledger's names and owners: WW3D in ww3d.cpp,
// DX8Wrapper in dx8wrapper.cpp, CPUDetectClass in cpudetect.cpp); each
// static is read through an inline accessor.

class DX8Wrapper {
public:
	static __forceinline unsigned long Read_FrameCount() { return FrameCount; }
protected:
	static unsigned long FrameCount;
};

class WW3D {
public:
	static __forceinline int Read_FrameCount() { return FrameCount; }
	static __forceinline unsigned int Read_NPatchesLevel() { return NPatchesLevel; }
private:
	static int FrameCount;
	static unsigned int NPatchesLevel;
};

class CPUDetectClass {
public:
	static __forceinline unsigned int Read_ExtendedFeatureBits() { return ExtendedFeatureBits; }
	static __forceinline unsigned int Read_FeatureBits() { return FeatureBits; }
	static __forceinline unsigned int Read_L1DataCacheLineSize() { return L1DataCacheLineSize; }
	static __forceinline unsigned int Read_L1DataCacheSetAssociative() { return L1DataCacheSetAssociative; }
	static __forceinline unsigned int Read_L1DataCacheSize() { return L1DataCacheSize; }
	static __forceinline unsigned int Read_L1InstructionCacheLineSize() { return L1InstructionCacheLineSize; }
	static __forceinline unsigned int Read_L1InstructionCacheSetAssociative() { return L1InstructionCacheSetAssociative; }
	static __forceinline unsigned int Read_L1InstructionCacheSize() { return L1InstructionCacheSize; }
	static __forceinline unsigned int Read_L1InstructionTraceCacheSize() { return L1InstructionTraceCacheSize; }
	static __forceinline unsigned int Read_L2CacheLineSize() { return L2CacheLineSize; }
	static __forceinline unsigned int Read_L2CacheSetAssociative() { return L2CacheSetAssociative; }
	static __forceinline unsigned int Read_L2CacheSize() { return L2CacheSize; }
	static __forceinline int Read_ProcessorType() { return ProcessorType; }
private:
	static unsigned int ExtendedFeatureBits;
	static unsigned int FeatureBits;
	static unsigned int L1DataCacheLineSize;
	static unsigned int L1DataCacheSetAssociative;
	static unsigned int L1DataCacheSize;
	static unsigned int L1InstructionCacheLineSize;
	static unsigned int L1InstructionCacheSetAssociative;
	static unsigned int L1InstructionCacheSize;
	static unsigned int L1InstructionTraceCacheSize;
	static unsigned int L2CacheLineSize;
	static unsigned int L2CacheSetAssociative;
	static unsigned int L2CacheSize;
	static int ProcessorType;
};

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

// ?getNPatchesLevel@@YAHXZ @ 0x00129450 (6B): returns global at 0x9B5F94.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getNPatchesLevel(void)
{
	return (int)WW3D::Read_NPatchesLevel();
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

// ?getDX8FrameCount@@YAHXZ @ 0x0011D2A0 (6B): returns global at 0xDEDA84.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getDX8FrameCount(void)
{
	return (int)DX8Wrapper::Read_FrameCount();
}

// ?Rva001432A0Get@@YAHXZ @ 0x001432A0 (6B): returns global at 0xDEC3E0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int Rva001432A0Get(void)
{
	return (int)WW3D::Read_FrameCount();
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

// ?Rva001432F0Set@@YAXH@Z @ 0x001432F0 (10B): the matching setter that sits
// just before the getter (mov eax,[esp+4] / mov [0xDEDA78],eax / ret);
// prev and next are CC padding, no direct callers. Opaque address-derived name.
void Rva001432F0Set(int value)
{
	G00DEDA78 = value;
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

extern int G00DFDA54;
// G00DFDA54: VA 0xdfda54 (zero-filled .bss).
int G00DFDA54;

// ?getFeatureBits@@YAHXZ @ 0x00610F10 (6B): returns global at 0xE08C48.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getFeatureBits(void)
{
	return (int)CPUDetectClass::Read_FeatureBits();
}

// ?getExtendedFeatureBits@@YAHXZ @ 0x00610F20 (6B): returns global at 0xE08CF0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getExtendedFeatureBits(void)
{
	return (int)CPUDetectClass::Read_ExtendedFeatureBits();
}

// ?getL2CacheSize@@YAHXZ @ 0x00610F30 (6B): returns global at 0xE08C44.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL2CacheSize(void)
{
	return (int)CPUDetectClass::Read_L2CacheSize();
}

// ?getL2CacheLineSize@@YAHXZ @ 0x00610F40 (6B): returns global at 0xE08CA0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL2CacheLineSize(void)
{
	return (int)CPUDetectClass::Read_L2CacheLineSize();
}

// ?getL2CacheSetAssociative@@YAHXZ @ 0x00610F50 (6B): returns global at 0xE08CA4.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL2CacheSetAssociative(void)
{
	return (int)CPUDetectClass::Read_L2CacheSetAssociative();
}

// ?getL1DataCacheSize@@YAHXZ @ 0x00610F60 (6B): returns global at 0xE08C28.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL1DataCacheSize(void)
{
	return (int)CPUDetectClass::Read_L1DataCacheSize();
}

// ?getL1DataCacheLineSize@@YAHXZ @ 0x00610F70 (6B): returns global at 0xE08CC0.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL1DataCacheLineSize(void)
{
	return (int)CPUDetectClass::Read_L1DataCacheLineSize();
}

// ?getL1DataCacheSetAssociative@@YAHXZ @ 0x00610F80 (6B): returns global at 0xE08D08.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL1DataCacheSetAssociative(void)
{
	return (int)CPUDetectClass::Read_L1DataCacheSetAssociative();
}

// ?getL1InstructionCacheSize@@YAHXZ @ 0x00610F90 (6B): returns global at 0xE08CD8.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL1InstructionCacheSize(void)
{
	return (int)CPUDetectClass::Read_L1InstructionCacheSize();
}

// ?getL1InstructionCacheLineSize@@YAHXZ @ 0x00610FA0 (6B): returns global at 0xE08CC4.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL1InstructionCacheLineSize(void)
{
	return (int)CPUDetectClass::Read_L1InstructionCacheLineSize();
}

// ?getL1InstructionCacheSetAssociative@@YAHXZ @ 0x00610FB0 (6B): returns global at 0xE08C40.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL1InstructionCacheSetAssociative(void)
{
	return (int)CPUDetectClass::Read_L1InstructionCacheSetAssociative();
}

// ?getL1InstructionTraceCacheSize@@YAHXZ @ 0x00610FC0 (6B): returns global at 0xE08CFC.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getL1InstructionTraceCacheSize(void)
{
	return (int)CPUDetectClass::Read_L1InstructionTraceCacheSize();
}

// ?getProcessorType@@YAHXZ @ 0x00611020 (6B): returns global at 0xE08D24.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
int getProcessorType(void)
{
	return (int)CPUDetectClass::Read_ProcessorType();
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

// ?getFirstProfileId@@YAHXZ @ 0x006C5E70 (6B): returns ProfileId::first (0xE0C620,
// defined in profile/profile_highlevel.cpp); inside that unit's address range.
// Follows int3 (prev CC), followed by CC padding, no .rdata vtable slot,
// no direct callers, no branch sources. Opaque address-derived name.
#include "../../../Libraries/Source/profile/internal_highlevel.h"

int getFirstProfileId(void)
{
	return (int)ProfileId::GetFirst();
}

// cl: /GX-
// Global float getters (twin-free TU).
//
// Seven-byte free functions with one shape:
//
//     fld dword [global] / ret
//
// One engine float global is read and returned in ST0. MSVC 7.1 emits the
// absolute load `D9 05 <VA>`, plus `ret`, for seven bytes total. This is the
// float sibling of the ColdGlobalDwordGetters family; the opcode itself is
// why the two families are kept in separate translation units. Identity is
// not recovered beyond the global: every name is derived from its address
// (Rva<RVA>Get over g_Va<VA>). The /GX- line matches the sibling TUs
// (verified frameless seven-byte shape).

// ?Rva004647D1Get@@YAMXZ @ 0x004647d1 (7B) over 0x00BBB8D8 (1.0f).
// Follows a ret (prev C3); carried by 33 .rdata vtable slots, no direct
// callers, no branch sources. Opaque address-derived name.
float Rva004647D1Get(void)
{
	return 1.0f;
}

extern float g_Va00BD2F58;
// ?g_Va00BD2F58@@3MA: the global at this VA is ?AT_MIN_LOD@RenderObjClass@@2MB; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00BD2F58@@3MA=?AT_MIN_LOD@RenderObjClass@@2MB")

// ?Rva00167F59Get@@YAMXZ @ 0x00167f59 (7B) over 0x00BD2F58 (FLT_MAX).
// Follows a ret (prev C3); carried by 19 .rdata vtable slots, adjacent to
// Rva00167F60Get below, no branch sources. Opaque address-derived name.
float Rva00167F59Get(void)
{
	return g_Va00BD2F58;
}

extern float g_Va00BD2F5C;
// ?g_Va00BD2F5C@@3MA: the global at this VA is ?AT_MAX_LOD@RenderObjClass@@2MB; this name is an alias for it.
#pragma comment(linker, "/alternatename:?g_Va00BD2F5C@@3MA=?AT_MAX_LOD@RenderObjClass@@2MB")

// ?Rva00167F60Get@@YAMXZ @ 0x00167f60 (7B) over 0x00BD2F5C (-1.0f).
// Adjacent after Rva00167F59Get (pair proves both boundaries); carried by
// 19 .rdata vtable slots, no branch sources. Opaque address-derived name.
float Rva00167F60Get(void)
{
	return g_Va00BD2F5C;
}

extern float g_Va00BC93F0;
// g_Va00BC93F0: matched references place it at VA 0xbc93f0 (retail .rdata value 1024.0f).
float g_Va00BC93F0 = 1024.0f;

// ?Rva000A92A2Get@@YAMXZ @ 0x000a92a2 (7B) over 0x00BC93F0 (1024.0f).
// Follows a ret (prev C3); address stored to global 0x00E177C8,
// adjacent to Rva000A92A9Get below, no branch sources.
float Rva000A92A2Get(void)
{
	return g_Va00BC93F0;
}

extern float g_Va00BC93F4;
// g_Va00BC93F4: matched references place it at VA 0xbc93f4 (retail .rdata value 768.0f).
float g_Va00BC93F4 = 768.0f;

// ?Rva000A92A9Get@@YAMXZ @ 0x000a92a9 (7B) over 0x00BC93F4 (768.0f).
// Adjacent after Rva000A92A2Get (pair proves both boundaries); address
// stored to global 0x00E177CC, no branch sources.
float Rva000A92A9Get(void)
{
	return g_Va00BC93F4;
}


// ?Rva00050EA0Get@@YAMXZ @ 0x00050ea0 (7B) over 0x00BBB8E0 (FLT_MAX).
// Adjacent before Rva00050EA7Get below (pair proves both boundaries);
// follows a ret (prev C3), no direct callers, no branch sources.
// Opaque address-derived name.
float Rva00050EA0Get(void)
{
	return 3.4028235e+38f;
}

extern float g_Va00BBDA30;

// ?Rva00050EA7Get@@YAMXZ @ 0x00050ea7 (7B) over 0x00BBDA30 (inf).
// Adjacent after Rva00050EA0Get (pair proves both boundaries), no branch sources.
// Opaque address-derived name.
float Rva00050EA7Get(void)
{
	return g_Va00BBDA30;
}

extern float g_Va00BBDA2C;

// ?Rva00041457Get@@YAMXZ @ 0x00041457 (7B) over 0x00BBDA2C (NaN).
// Follows a ret (prev C3); next is a frameless fn start; no direct callers,
// no branch sources. Opaque address-derived name.
float Rva00041457Get(void)
{
	return g_Va00BBDA2C;
}

extern float bfmeProjectionBias;

// ?Rva000D1A9AGet@@YAMXZ @ 0x000d1a9a (7B) over 0x00DEDA74 (0.0f).
// Follows a ret (prev C3); next is a frameless fn start; no direct callers,
// no branch sources. Opaque address-derived name.
float Rva000D1A9AGet(void)
{
	return bfmeProjectionBias;
}

// ?Rva00154310Get@@YAMXZ @ 0x00154310 (7B) over 0x00BBB8D8 (1.0f).
// CC-padded both sides (isolated); same global as landed Rva004647D1Get
// above (distinct address, not a fold); no direct callers, no branch sources.
// Opaque address-derived name.
float Rva00154310Get(void)
{
	return 1.0f;
}

extern float g_Va00DEDA2C;
// g_Va00DEDA2C: matched references place it at VA 0xdeda2c (zero-filled .bss).
float g_Va00DEDA2C;

// ?Rva0018BD82Get@@YAMXZ @ 0x0018bd82 (7B) over 0x00DEDA2C (0.0f).
// Follows another float getter (adjacent); no direct callers, no branch sources.
// Opaque address-derived name.
float Rva0018BD82Get(void)
{
	return g_Va00DEDA2C;
}


// ?Rva002BFBF0Get@@YAMXZ @ 0x002bfbf0 (7B) over 0x00BBAEAC (0.0f).
// Follows a ret (prev C3); carried by 28 .rdata vtable slots, no direct callers,
// no branch sources. Opaque address-derived name.
float Rva002BFBF0Get(void)
{
	return 0.0f;
}


// ?Rva006CBC10Get@@YAMXZ @ 0x006cbc10 (7B) over 0x00BC28F4 (2.0f).
// CC-padded both sides (isolated); no direct callers, no branch sources.
// Opaque address-derived name.
float Rva006CBC10Get(void)
{
	return 2.0f;
}

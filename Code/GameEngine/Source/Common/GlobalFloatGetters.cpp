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
extern float g_Va00BBB8D8;

// ?Rva004647D1Get@@YAMXZ @ 0x004647d1 (7B) over 0x00BBB8D8 (1.0f).
// Follows a ret (prev C3); carried by 33 .rdata vtable slots, no direct
// callers, no branch sources. Opaque address-derived name.
float Rva004647D1Get(void)
{
	return g_Va00BBB8D8;
}

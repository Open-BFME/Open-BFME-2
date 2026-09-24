// cl: /GX-
// Cold-slice global dword setters (twin-free TU).
//
// Ten-byte free functions with one shape:
//
//     mov eax,[esp+4] / mov [global],eax / ret
//
// Each writes one .data dword global from its single int argument. Identity
// unrecoverable, so globals and functions are address-derived
// (g_Va<VA> / Rva<RVA>Set). The /GX- line matches the sibling getter TUs
// (verified frameless ten-byte shape).
extern int g_Va00DB5FE0;

// ?Rva00116E40Set@@YAXH@Z @ 0x00116e40 (10B) over 0x00DB5FE0.
// Int3-padded both sides (prev CC next CC), live E8 caller. Opaque
// address-derived name.
void Rva00116E40Set(int value)
{
	g_Va00DB5FE0 = value;
}
extern int g_Va00DFDA54;

// ?Rva001B6380Set@@YAXH@Z @ 0x001b6380 (10B) over 0x00DFDA54.
// Int3-padded both sides (prev CC next CC), live E8 caller. Opaque
// address-derived name.
void Rva001B6380Set(int value)
{
	g_Va00DFDA54 = value;
}
extern int g_Va00E0BE00;

// ?Rva0069BD40Set@@YAXH@Z @ 0x0069bd40 (10B) over 0x00E0BE00.
// Int3-padded both sides (prev CC next CC), live E8 callers. Opaque
// address-derived name.
void Rva0069BD40Set(int value)
{
	g_Va00E0BE00 = value;
}
extern int g_Va00DDC01C;

// ?Rva006CD1F0Set@@YAXH@Z @ 0x006cd1f0 (10B) over 0x00DDC01C.
// Int3-padded both sides (prev CC next CC), live E8 caller. Opaque
// address-derived name.
void Rva006CD1F0Set(int value)
{
	g_Va00DDC01C = value;
}
extern int g_Va00E17724;

// ?Rva006CD210Set@@YAXH@Z @ 0x006cd210 (10B) over 0x00E17724.
// Int3-padded both sides (prev CC next CC), live E8 caller at 0x006d198a.
// Opaque address-derived name. Setter pairs with the rowed getter over the
// same global (A1 2477E100 at 0x006cd220).
void Rva006CD210Set(int value)
{
	g_Va00E17724 = value;
}
extern int g_Va00E177EC;

// ?Rva006D37E0Set@@YAXH@Z @ 0x006d37e0 (10B) over 0x00E177EC.
// Int3-padded both sides (prev CC next CC), live E8 caller at 0x006cf85c.
// Opaque address-derived name. Setter pairs with the clearer over the same
// global (C7 05 EC77E100 00000000 at 0x006d37f0).
void Rva006D37E0Set(int value)
{
	g_Va00E177EC = value;
}

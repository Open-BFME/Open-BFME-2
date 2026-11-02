// cl: /GX- C:/Program Files/Git/ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
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
// 0x009B5FE0 is the data ledger's DX8Wrapper::TextureBitDepth (protected,
// dx8wrapper.cpp). A minimal view of the real class writes it through the
// WW3D2 inline setter.
#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

// ?Rva00116E40Set@@YAXH@Z @ 0x00116e40 (10B) over 0x00DB5FE0.
// Int3-padded both sides (prev CC next CC), live E8 caller. Opaque
// address-derived name.
void Rva00116E40Set(int value)
{
	DX8Wrapper::Set_Texture_Bitdepth(value);
}
extern int G00DFDA54;

extern int G00E0BE00;

// ?Rva0069BD40Set@@YAXH@Z @ 0x0069bd40 (10B) over 0x00E0BE00.
// Int3-padded both sides (prev CC next CC), live E8 callers. Opaque
// address-derived name.
void Rva0069BD40Set(int value)
{
	G00E0BE00 = value;
}
extern int g_bfmeAptBreakOnAssertAtDDC01C; // Apt.cpp break-on-assert flag

// ?Rva006CD1F0Set@@YAXH@Z @ 0x006cd1f0 (10B) over 0x00DDC01C.
// Int3-padded both sides (prev CC next CC), live E8 caller. Opaque
// address-derived name.
void Rva006CD1F0Set(int value)
{
	g_bfmeAptBreakOnAssertAtDDC01C = value;
}
extern int g_Va00E17724;
// g_Va00E17724: matched references place it at VA 0xe17724 (zero-filled .bss).
int g_Va00E17724;

// ?Rva006CD210Set@@YAXH@Z @ 0x006cd210 (10B) over 0x00E17724.
// Int3-padded both sides (prev CC next CC), live E8 caller at 0x006d198a.
// Opaque address-derived name. Setter pairs with the rowed getter over the
// same global (A1 2477E100 at 0x006cd220).
void Rva006CD210Set(int value)
{
	g_Va00E17724 = value;
}
extern int g_Va00E177EC;
// g_Va00E177EC: matched references place it at VA 0xe177ec (zero-filled .bss).
int g_Va00E177EC;

// ?Rva006D37E0Set@@YAXH@Z @ 0x006d37e0 (10B) over 0x00E177EC.
// Int3-padded both sides (prev CC next CC), live E8 caller at 0x006cf85c.
// Opaque address-derived name. Setter pairs with the clearer over the same
// global (C7 05 EC77E100 00000000 at 0x006d37f0).
void Rva006D37E0Set(int value)
{
	g_Va00E177EC = value;
}

// ?Rva006D37F0Clear@@YAXXZ @ 0x006d37f0 (11B) over 0x00E177EC.
// Pairs with setter 0x006d37e0 over same global; caller at 0x006cfca2.
// Prev setter 0x006d37e0 next hashLower 0x006d3800. Opaque address-derived.
void Rva006D37F0Clear()
{
	g_Va00E177EC = 0;
}

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

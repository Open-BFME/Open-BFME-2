// Global dword-array indexed getters: twelve-byte __cdecl free functions with
// one shape:
//
//     mov eax,[esp+4] / mov eax,[eax*4+<GLOBAL>] / ret
//
// An integer index is loaded, then the dword at that index in a fixed .data
// dword array is returned. Spelled as an extern array-index read, which MSVC
// 7.1 emits frameless with scaled-index addressing in the default flags.
// Identity unrecoverable, so globals and functions are address-derived
// (g_Va<VA> / Rva<RVA>Get) following the GlobalGetterSingles convention.
// Opaque names witness only the address and the global.
// No // cl: line (defaults match the frameless twelve-byte shape).

extern int g_Va00DB5F30[];

// ?Rva00115DE8Get@@YAHH@Z @ 0x00115DE8 (12B) over 0x00DB5F30.
// Follows a leave/ret (prev C9 C3), Ghidra-12, direct E8 caller at
// 0x000F5701 (unclaimed). Opaque address-derived name.
int Rva00115DE8Get(int index)
{
	return g_Va00DB5F30[index];
}

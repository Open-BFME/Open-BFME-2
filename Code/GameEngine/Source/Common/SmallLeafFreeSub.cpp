// Small free-function arithmetic leaf: seven-byte __cdecl body with one shape:
//
//     mov eax,[esp+4] / sub eax,[eax] / ret
//
// A pointer-sized argument is loaded, then the dword it points at is
// subtracted from the pointer value itself and returned. Spelled as a
// pointer-minus-pointed-value free function, which MSVC 7.1 emits
// frameless in the default flags. Identity is not recovered: the name is
// derived from its address.
// No // cl: line (defaults match the frameless seven-byte shape).

// ?Rva00030AE0Sub@@YAHPAH@Z @ 0x00030AE0 (7B): returns (int)ptr - *ptr.
// CC-island (prev C3 CC, 8xCC after), Ghidra-7, direct E8 caller at
// 0x00033DBC (call then add-esp/mov). Opaque address-derived name.
int Rva00030AE0Sub(int *ptr)
{
	return (int)ptr - *ptr;
}

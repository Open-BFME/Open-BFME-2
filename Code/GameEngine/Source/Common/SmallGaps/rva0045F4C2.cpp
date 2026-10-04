// cl: /O1
//
// ?Rva0045F4C2NotEqual@@YAHPBX0@Z @0x0045F4C2 (21B).
// Logical NOT of rowed ?Rva0037DC8AEqual@@YA_NPBX0@Z (memcmp 0x80 == 0).
// Retail pushes both args then E8 to Equal, neg al, pops, sbb eax eax, inc eax, ret.
// Callers at 0x004603B0 and 0x004847EB.
bool __cdecl Rva0037DC8AEqual(const void *a, const void *b);
int __cdecl Rva0045F4C2NotEqual(const void *a, const void *b)
{
	return !Rva0037DC8AEqual(a, b);
}

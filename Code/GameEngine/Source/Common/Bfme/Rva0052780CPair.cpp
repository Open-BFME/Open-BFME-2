// ?Rva0052780C@@YA?AURva0052780CPair@@DH@Z, retail 0x0052780C, 27 bytes. Address-derived name.
// Target evidence: cdecl, the first stack word is the hidden return slot (returned in eax).
// A byte argument is staged through a dword stack local (upper bytes uninitialised) and the
// whole dword is copied to the result's first word; the int argument fills the second.
// A user-declared copy constructor makes the 8-byte result non-trivially returnable (hidden
// pointer); copying it as one 64-bit unit is a codegen inference, the real member layout is
// unproven.
struct Rva0052780CPair
{
	char flag;
	int value;
	Rva0052780CPair() {}
	Rva0052780CPair(const Rva0052780CPair &o) { *(long long *)this = *(const long long *)&o; }
};

Rva0052780CPair Rva0052780C(char flag, int value)
{
	Rva0052780CPair p;
	p.flag = flag;
	p.value = value;
	return p;
}

// cl: /MD
// ?rva004340A4@Rva004340A4@@QAEFFH@Z @0x004340A4 8B: honest thiscall short returning first short arg; callers 0x003F0BEF and 0x00434831 pass 2 DWORDs plus ecx and use signed result via movsx; ret 8 proves 2 stack args; second arg and this unused.
struct Rva004340A4 {
    short rva004340A4(short x, int y);
};
short Rva004340A4::rva004340A4(short x, int y) { return x; }

// cl: /MD /DNDEBUG
// BFME1 donor: game/GameEngine/Source/Common/Rva009A8410ReadCounter.cpp
// at 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor RVA 0x009A8410.
// Target Ghidra entry 0x001B8E70, 29B, followed by INT3 then 0x001B8E90.
// CPUID/RDTSC with general-register preservation writes the low timestamp
// DWORD through one cdecl output-pointer argument. Original name is unknown.
// Direct callers 0x001B5C69/0x001B5D3E/0x001B5D94/0x001B5DB9/0x001B60EE/
// 0x001B6224 pass output storage; the last then subtracts two stored timestamps.
// MSVC7.1 requires hardware assembly here; the compiler generates the frame,
// named local store, output-pointer store and return. No emitted bytes or
// hand-written prologue, return or stack offset.
void Rva001B8E70(unsigned int *result)
{
    unsigned int stamp;
    __asm {
        pushad
        cpuid
        rdtsc
        mov stamp, eax
        popad
    }
    *result = stamp;
}

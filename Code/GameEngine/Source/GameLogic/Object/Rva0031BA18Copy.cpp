// cl: /DNDEBUG /MD /EHs-c-
// ?Rva0031BA18Copy@@YAPAURva002C99FB@@PAU1@00@Z @0x0031BA18 47B
// __copy for 8-byte Rva002C99FB via rowed operator= 0x002C99FB (sar 3 count,
// EBP frame, loop with add [ebp+8]/[ebp+0x10]). Caller 0x0031BDA4.
// Evidence: (last-first)/8 count; landing unblocks 0x0031BDA4.
struct OpaqueRefElement4
{
    OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

struct Rva002C99FB
{
    int m_first;
    OpaqueRefElement4 m_second;
    Rva002C99FB &operator=(const Rva002C99FB &other);
};

Rva002C99FB *Rva0031BA18Copy(Rva002C99FB *first, Rva002C99FB *last, Rva002C99FB *dest)
{
    int n = ((char *)last - (char *)first) >> 3;
    if (n <= 0)
        return dest;
    for (; n != 0; --n) {
        *dest = *first;
        ++first;
        ++dest;
    }
    return dest;
}

// cl: /MD
// ?Rva00566663Copy@@YAPAURva004FAFF2@@PAU1@00@Z, retail 0x00566663, 50 bytes.
// Array copy of Rva004FAFF2 via rowed assign with 0x58 stride.
// Evidence: count via (end-begin)/0x58 idiv; loop assign plus 0x58 bumps; caller 0x00566933; unblocks 0x00566920.
struct Rva004FAFF2 {
    char m_pad00[0x58];
    Rva004FAFF2 &rva004FAFF2(const Rva004FAFF2 &other);
};
Rva004FAFF2 *Rva00566663Copy(Rva004FAFF2 *src, Rva004FAFF2 *end, Rva004FAFF2 *dest)
{
    int count = end - src;
    if (count <= 0)
        return dest;
    int n = count;
    do {
        dest->rva004FAFF2(*src);
        src = src + 1;
        dest = dest + 1;
        --n;
    } while (n != 0);
    return dest;
}

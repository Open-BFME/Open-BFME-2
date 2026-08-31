// ?d_00005841@@YAXXZ
// partial score=0.95 date=2026-08-31
// ?d_00005841@@YAXXZ
// partial score=0.95 date=2026-08-31
// cl: /O1
// Retail 0x00005841: the case-insensitive twin of 0x00005816. Same five-argument
// cdecl shape, same tail, but the comparison goes through the import at
// 0x00BBA690 (_memicmp) instead of the memcmp thunk. Both callers now land as
// clean C++ in Code/Libraries/Source/WWVegas/WWLib/string_base.cpp; this body is
// blocked on exactly the same cmovge/branch difference that blocks 0x00005816.
struct CharCompare
{
    char m_unused;
};

int compareRangeNoCase(const char *a, int alen, const char *b, int blen, CharCompare tag)
{
    int len = alen;
    if (len >= blen)
        len = blen;
    const int result = _memicmp(a, b, len);
    if (result != 0)
        return result;
    return alen - blen;
}

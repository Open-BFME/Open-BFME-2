// ?Rva004E98F7Find@@YAPAPBXPAPBX0PBX@Z
// partial score=0.97 date=2026-10-05
// ?Rva004E98F7Find@@YAPAPBXPAPBX0PBX@Z
// partial score=0.97 date=2026-10-04
// cl: /Os /MD
// ?Rva004E98F7Find@@YAPAPBXPAPBX0PBX@Z, retail 0x004E98F7, 186 bytes.
// Four-element unrolled pointer search via rowed Rva004EAB9FCmp 0x004EAB9F; caller 0x004E99D6 forwards first/last/val.
// ?Rva004E98F7Find@@YAPAPBXPAPBX0PBX@Z present-unmatched
bool __cdecl Rva004EAB9FCmp(const void *a, const void *b);
const void **__cdecl Rva004E98F7Find(const void **first, const void **last, const void *val)
{
    const void **p = first;
    int n = ((const char *)last - (const char *)p) >> 4;
    while (n > 0) {
        if (Rva004EAB9FCmp(*p, val))
            return p;
        ++p;
        if (Rva004EAB9FCmp(*p, val))
            return p;
        ++p;
        if (Rva004EAB9FCmp(*p, val))
            return p;
        ++p;
        if (Rva004EAB9FCmp(*p, val))
            return p;
        ++p;
        --n;
    }
    int r = ((const char *)last - (const char *)p) >> 2;
    switch (r) {
    case 3:
        if (Rva004EAB9FCmp(*p, val))
            return p;
        ++p;
    case 2:
        if (Rva004EAB9FCmp(*p, val))
            return p;
        ++p;
    case 1:
        if (Rva004EAB9FCmp(*p, val))
            return p;
        ++p;
    }
    return last;
}

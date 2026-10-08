// ?rva004B65E4@Rva004B65E4@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.95 date=2026-10-08
// cl: /O1 /Oy- /DNDEBUG /MD /GX- /Oi-
// Retail 0x004B65E4..0x004B6691: ModelConditionUpgrade's
// RemoveConditionFlagsInRange parser (field table at VA 0x00C58730).
// The native calls establish a 19-dword (591-bit) model-condition set.
// The established copy/intersection providers retain their opaque set name;
// no original spelling for this parser is asserted.
class INI;
class WeaponTemplateSetHead
{
public:
    unsigned int bits[19];
    WeaponTemplateSetHead(const WeaponTemplateSetHead &);
    void rva000B3ED3(const WeaponTemplateSetHead &);
};
template<int N> class BitFlags
{
public:
    int count() const;
};
class Rva000B937E
{
public:
    void rva000B937E(INI *, void *);
};
struct INIException
{
    INIException(int, const char *, ...);
    char *mFailureMessage;
    int mErrorCode;
};
extern "C" void __stdcall _CxxThrowException(void *, const _s__ThrowInfo *);
extern "C" const struct _s__ThrowInfo __identifier("_TI1?AVINIException@@");

class Rva004B65E4
{
public:
    static void rva004B65E4(INI *, void *, void *, const void *);
};
void Rva004B65E4::rva004B65E4(INI *ini, void *, void *store, const void *)
{
    WeaponTemplateSetHead *dest = (WeaponTemplateSetHead *)store;
    WeaponTemplateSetHead added(*dest);
    int bit = 0;
    ((Rva000B937E *)dest)->rva000B937E(ini, 0);
    for (unsigned int w = 0; w < 19; ++w)
        added.bits[w] ^= ~0u;
    added.rva000B3ED3(*dest);
    if (((const BitFlags<591> *)&added)->count() != 2)
    {
        INIException e(1, "you must specifly only two bit flags for a range.");
        _CxxThrowException(&e, &__identifier("_TI1?AVINIException@@"));
    }
    bool first = false;
    bool last = false;
    for (; bit < 591; ++bit)
    {
        unsigned int word = (unsigned int)bit >> 5;
        unsigned int mask = 1u << (bit & 31);
        if (!first)
        {
            if (!(added.bits[word] & mask))
                continue;
            first = true;
        }
        else if (added.bits[word] & mask)
            last = true;
        dest->bits[word] |= mask;
        if (last)
            break;
    }
}

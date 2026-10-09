// cl: /MD /D_STLP_USE_STATIC_LIB
// stlport


struct Rva0084DBText
{
    char unused[0x14];
    const char *text;
};

// Native 0x20E60..0x20E71 is INT3-bracketed: the cdecl argument supplies a
// pointer whose field at +0x14 is returned when nonnull; the other path returns
// StringBase<char>::str TheNullChr at VA 0xBBAC1C. The old 0x20E6B row was
// an interior suffix with no independent call or address xrefs, now retracted.
// BF1 f989 StringAndCodePage emits twins; retain an address-owned function name
// and the existing consumed-prefix view without asserting the original class.
const char *Rva00020E60GetText(const Rva0084DBText *owner)
{
    const char *text = owner->text;
    return text ? text : "";
}

const char *Rva0084DC40GetText(const Rva0084DBText *owner)
{
    const char *text = owner->text;
    return text ? text : "";
}

struct Rva0084D860CodePage
{
    unsigned int unknown;
    unsigned int codePage;
};

struct Rva0084D860CpInfo
{
    unsigned int MaxCharSize;
    unsigned char remainder[16];
};
// The target IAT identifies kernel32!GetCPInfo; the BFME1 C++ declaration
// lacked C linkage and compiled an unresolved C++-mangled import reference.
extern "C" __declspec(dllimport) int __stdcall GetCPInfo(unsigned int, Rva0084D860CpInfo *);

// Rva0084D860IsSingleByte: defined in Rva0084D860IsSingleByte.cpp (its row's unit).
bool Rva0084D860IsSingleByte(const Rva0084D860CodePage *owner);

// Target 0x00020AF0: address-derived name because the BFME1 donor is an ICF twin.
unsigned int Rva00020AF0(const Rva0084D860CodePage *owner)
{
    Rva0084D860CpInfo info;
    if (GetCPInfo(owner->codePage, &info))
        return info.MaxCharSize;
    return 0;
}

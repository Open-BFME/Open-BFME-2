// ?rva006ee3b0@@YAPAVAptValue@@PAV1@@Z
// partial score=0.95 date=2026-10-06
// cl: /O2 /DNDEBUG /MD /EHsc
// Target 0x006EE3B0 (393B) and 0x006EE540 (373B), with entry/return boundaries
// confirmed in game.dat. reverse/string_xrefs.tsv names their callback slots
// gAptFuncs.pfnGetBytesTotal and gAptFuncs.pfnGetBytesLoaded; the matching
// ActionScript property names are also in R4PerfectHashWordSets.cpp. The
// target calls through those slots with a String path and converts the
// returned byte count to an Apt float. Slot identity is table evidence; the
// address-derived global names below do not claim an original source name.
// The +0x34 resource pointer and +8 EAStringC field follow the target loads.

extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class AptCIH;
class AptValue
{
public:
    AptCIH *c_cih(bool bUndefinedOK);
    bool isCIH(bool bUndefinedOK) const;
    int getVtblIndex() const;
    bool isUndefined() const;
};

class AptCIH
{
public:
    unsigned char prefix[0x4c];
    void *member4C;
};

class EAStringC
{
public:
    EAStringC();
    ~EAStringC();
    EAStringC &Rva006D4F00Append(const EAStringC &other);
    const char *rva00620090() const;
};

class Rva006CD650
{
public:
    void *rva006CD650();
};

static __forceinline EAStringC &rva006EECharacterUrl(void *character)
{
    void *resource = *(void **)((char *)character + 0x34);
    return *(EAStringC *)((char *)resource + 8);
}

extern int (__cdecl *g_rva00A177BC)(const char *, int);
extern int (__cdecl *g_rva00A177C0)(const char *, int);
AptValue *__cdecl Rva008A4EA0MakeFloat(float value);

static __forceinline bool rva006EEIsDefinedMovieClip(AptCIH *cih)
{
    if (!cih) {
        g_bfmeAptAssertAtE17734(
            "this",
            "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h",
            0xD3);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    const AptValue *value = (const AptValue *)cih;
    return value->getVtblIndex() == 0x12 && !value->isUndefined();
}

// ?rva006ee3b0@@YAPAVAptValue@@PAV1@@Z @0x006EE3B0, 393B.
AptValue *__cdecl rva006ee3b0(AptValue *value)
{
    EAStringC url;

    AptCIH *initial = value->c_cih(false);
    if (!initial->member4C)
        return Rva008A4EA0MakeFloat(0.0f);
    if (value->isCIH(false)) {
        AptCIH *cih = value->c_cih(false);
        if (rva006EEIsDefinedMovieClip(cih)) {
            cih = value->c_cih(false);
            url.Rva006D4F00Append(rva006EECharacterUrl(
                ((Rva006CD650 *)cih)->rva006CD650()));
        }
    }

    if (!g_rva00A177BC) {
        g_bfmeAptAssertAtE17734("gAptFuncs.pfnGetBytesTotal",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",
            0x636);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    float byteCount = 0.0f;
    AptCIH *cih = value->c_cih(false);
    if (rva006EEIsDefinedMovieClip(cih))
        byteCount = (float)g_rva00A177BC(url.rva00620090(), 0);
    return Rva008A4EA0MakeFloat(byteCount);
}

// ?rva006ee540@@YAPAVAptValue@@PAV1@@Z @0x006EE540, 373B.
AptValue *__cdecl rva006ee540(AptValue *value)
{
    EAStringC url;

    if (value->isCIH(false)) {
        AptCIH *cih = value->c_cih(false);
        if (rva006EEIsDefinedMovieClip(cih)) {
            cih = value->c_cih(false);
            url.Rva006D4F00Append(rva006EECharacterUrl(
                ((Rva006CD650 *)cih)->rva006CD650()));
        }
    }

    if (!g_rva00A177C0) {
        g_bfmeAptAssertAtE17734("gAptFuncs.pfnGetBytesLoaded",
            "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptCharacter.cpp",
            0x64B);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    float byteCount = 0.0f;
    AptCIH *cih = value->c_cih(false);
    if (rva006EEIsDefinedMovieClip(cih))
        byteCount = (float)g_rva00A177C0(url.rva00620090(), 0);
    return Rva008A4EA0MakeFloat(byteCount);
}

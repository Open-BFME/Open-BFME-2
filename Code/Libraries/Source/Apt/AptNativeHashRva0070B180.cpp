// cl: /MD
// ?rva0070B180@AptNativeHash@@QAEXPAVBfmeAptValue006DCD20@@PAVEAStringC@@H@Z @0x0070B180 159B
// Evidence: AptNativeHash layout (nEventHandlers+0x10) from AptNativeHashBFME2.cpp/Mark.cpp;
// callees isCIH 0x006DC580, EAStringC len 0x006D3750, c_str 0x00620090, gperf Rva008D48F0 0x007112A0;
// table aSpriteGperfToActionFlag at 0x008EEBA8 with assert nTableIndex range and line 0x40C in AptNativeHash.cpp;
// callers at 0x006FEE55/0x006FEFB6 inside 0x006FED00.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class BfmeAptValue006DCD20 {
public:
    int isCIH(bool bUndefOK) const;
};

class EAStringC {
public:
    unsigned int rva006D3750() const;
    const char *rva00620090() const;
};

struct R4Word {
    const char *name;
    int value;
};
const R4Word *__cdecl Rva008D48F0(const char *str, unsigned int len);

// Matched DIR32 witness (w=1) places the retail flag table at VA 0x00CEEBA8
// (.rdata). The checked index range below bounds it to 19 ints (0x4c bytes),
// ending at VA 0x00CEEBF4 before a zero padding DWORD and path text at
// VA 0x00CEEBF8. Values are the retail initial bytes.
#pragma data_seg(".rdata")
extern int aSpriteGperfToActionFlag[19] = {
	0x00000100, 0x00010000, 0x00008000, 2, 0x40, 0x80, -1,
	1, 0x10, 8, 0x20, 0x400, 0x800, 0x1000, 0x4000, 0x2000,
	-1, 4, 0x00080000,
};
#pragma data_seg()

class AptNativeHash {
    int mnTotalSize;
    void *mpData;
    void *mp__proto__;
    void *mpPrototype;
    unsigned int nEventHandlers;
public:
    void rva0070B180(BfmeAptValue006DCD20 *pValue, EAStringC *pStr, int bRemove);
};

void AptNativeHash::rva0070B180(BfmeAptValue006DCD20 *pValue, EAStringC *pStr, int bRemove)
{
    if (static_cast<unsigned char>(pValue->isCIH(false)))
        return;
    unsigned int len;
    const R4Word *found;
    len = pStr->rva006D3750();
    found = Rva008D48F0(pStr->rva00620090(), len);
    if (!found)
        return;
    int v = found->value;
    if (v < 0xC8)
        return;
    int nTableIndex = v - 0xC8;
    if (nTableIndex < 0 || nTableIndex >= 0x13) {
        g_bfmeAptAssertAtE17734("nTableIndex >= 0 && nTableIndex < APT_ARRAYSIZE(aSpriteGperfToActionFlag)", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x40C);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
    int flag = aSpriteGperfToActionFlag[nTableIndex];
    if (flag == -1)
        return;
    if (bRemove)
        nEventHandlers &= ~flag;
    else
        nEventHandlers |= flag;
}

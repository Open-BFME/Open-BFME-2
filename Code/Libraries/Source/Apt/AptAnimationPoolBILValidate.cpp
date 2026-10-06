// cl: /MD
// ?Rva006FA020Validate@@YA_NXZ @0x006FA020 224B. Global BIL button validation.
// Evidence: unlock lane; AptAnimationPoolData layout count+0x10 list+0x14 stride28
// shared with AptAnimationPoolDataBIL.cpp; assert lines 0x5D9/0x5E1 via
// AptInput.cpp and 0xB5 via AptCIH.h shared with neighbours; rowed
// isUndefined 0x6DC010 and get 0x6DBB30; caller 0x006E6540.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006E34D0;
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
class AptCIH {
public:
    virtual void AddRef();
    virtual void Release();
};
class BfmeAptValue006DCD20 {
public:
    bool isUndefined() const;
};
class Rva006DBB30SarDwordField {
public:
    int get() const;
};
struct AptMatrix {
    float a, b, c, d, tx, ty;
};
struct ButtonHitTestRecord {
    AptCIH *pCIH;
    AptMatrix matrix;
};
struct AptAnimationPoolData {
    unsigned char _pad[16];
    int mBILCount;
    ButtonHitTestRecord *aButtonInstanceList;
};
bool __cdecl Rva006FA020Validate()
{
    AptAnimationPoolData *pool = (AptAnimationPoolData *)g_bfmeAptPtrAtE176D0;
    int count = pool->mBILCount;
    --count;
    if (count < 0)
        return true;
    for (int i = count; i >= 0; --i) {
        AptAnimationPoolData *p2 = (AptAnimationPoolData *)g_bfmeAptPtrAtE176D0;
        if (p2->aButtonInstanceList[i].pCIH == 0) {
            g_bfmeAptAssertAtE17734("gpPool->aButtonInstanceList[i].pCIH != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp", 0x5D9);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        AptAnimationPoolData *p3 = (AptAnimationPoolData *)g_bfmeAptPtrAtE176D0;
        if (((const BfmeAptValue006DCD20 *)p3->aButtonInstanceList[i].pCIH)->isUndefined())
            continue;
        AptAnimationPoolData *p4 = (AptAnimationPoolData *)g_bfmeAptPtrAtE176D0;
        AptCIH *pCIH = p4->aButtonInstanceList[i].pCIH;
        if (!pCIH) {
            g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xB5);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
        if (((const Rva006DBB30SarDwordField *)pCIH)->get() != 0xE || ((const BfmeAptValue006DCD20 *)pCIH)->isUndefined()) {
            g_bfmeAptAssertAtE17734("gpPool->aButtonInstanceList[i].pCIH->isButtonInst()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptInput.cpp", 0x5E1);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
        }
    }
    return true;
}

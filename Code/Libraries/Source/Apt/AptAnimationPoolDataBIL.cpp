// cl: /MD
// APT0.19.03 Xbox final donor PDB GUID 729627e9-b922-4d59-9b50-e116a2834635 age24.
// Donor PDB types 0x15C9E/0x155E5/0x3604 provide pool/member/type names.
// Retail independently establishes count+0x10, list+0x14, entry stride28,
// pointer+0, six-float matrix+4, and virtual AddRef/Release slots0/4.
// Complete bodies at RVA6E35A0(49) and6E35E0(81) equal the donor bytes.
// Retail caller6E15C0 cites AptCIH.h/.cpp; its button-type14 branch calls
// 6E35E0 at6E1873 with this from global E176D0 and a 24-byte matrix.
// Caller6CC880 clears the same pool via6E35A0 at6CC8B9.
// The class name is donor-supported; no full 172-byte donor pool layout is
// transferred. AptCIH declares only the virtual interface used by these bodies.
extern "C" void *__cdecl memmove(void *, const void *, unsigned int);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptCIH {
public:
    virtual void AddRef();
    virtual void Release();
};
class Rva006DBB30SarDwordField
{
public:
    int get() const;
};
struct AptMatrix { float a,b,c,d,tx,ty; };
struct ButtonHitTestRecord { AptCIH *pCIH; AptMatrix matrix; };
struct AptAnimationPoolData {
    unsigned char unaccessed[16];
    int mBILCount;
    ButtonHitTestRecord *aButtonInstanceList;
    void clearBIL();
    void appendButtonToBIL(AptCIH *button, AptMatrix *matrix);
    void rva006E3640(AptCIH *button);
};
void AptAnimationPoolData::clearBIL()
{
    for (int i=0;i<mBILCount;++i) aButtonInstanceList[i].pCIH->Release();
    mBILCount=0;
}
void AptAnimationPoolData::appendButtonToBIL(AptCIH *button, AptMatrix *matrix)
{
    aButtonInstanceList[mBILCount].pCIH=button;
    button->AddRef();
    aButtonInstanceList[mBILCount].matrix=*matrix;
    ++mBILCount;
}

// ?rva006E3640@AptAnimationPoolData@@QAEXPAVAptCIH@@@Z @0x006E3640 180B.
// Removes a button from the BIL: scans entries for the pointer, asserts the
// button non-null (AptCIH.h:181) and its type field 0xE via the SarDword view
// (AptAnimation.cpp:1236), Releases it, memmoves the tail down one 28-byte
// entry and decrements the count. Evidence: unlock lane, callers
// 0x006E2690/0x006E2B40; layout/stride shared with clearBIL/append above;
// strings pinned by reverse/string_xrefs.tsv.
void AptAnimationPoolData::rva006E3640(AptCIH *button)
{
    for (int i = 0; i <= mBILCount - 1; ++i) {
        if (button == aButtonInstanceList[i].pCIH) {
            if (!button) {
                g_bfmeAptAssertAtE17734("this", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xB5);
                if (g_bfmeAptBreakOnAssertAtDDC01C)
                    __debugbreak();
            }
            if (((const Rva006DBB30SarDwordField *)button)->get() != 0xE) {
                g_bfmeAptAssertAtE17734("pBI->isButtonInst(UNDEF_OK)", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptAnimation.cpp", 0x4D4);
                if (g_bfmeAptBreakOnAssertAtDDC01C)
                    __debugbreak();
            }
            button->Release();
            memmove(&aButtonInstanceList[i], &aButtonInstanceList[i] + 1, (mBILCount - i) * sizeof(ButtonHitTestRecord));
            mBILCount--;
        }
    }
}

typedef char AptMatrixSize[(sizeof(AptMatrix)==24)?1:-1];
typedef char ButtonHitTestRecordSize[(sizeof(ButtonHitTestRecord)==28)?1:-1];

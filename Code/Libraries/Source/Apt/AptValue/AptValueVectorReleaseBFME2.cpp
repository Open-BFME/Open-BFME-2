// cl: /MD
// APT0.19.03 Xbox release donor supplies method names and the 16-byte vector.
// Target assertions name AptValueVector.inl/.cpp and mCurrentNum. Target
// independently establishes count+4 and pointer+8; unused capacity/high-water
// names are donor facts. No shared vector declaration is changed.
// Boundaries6E6C90+56 and6E6D90+134 include their final returns. Target calls
// the matched getRefCount at6DBB20 and ClearReleaseAtEnd at6DBDC0. The latter
// has the already-ledgered 5-byte body836104FBC3; a clean bitfield assignment
// compiled exactly to that body before adding the donor-name callee pin.
// ForceDelete is target virtual slot8, also identified by the donor vtable.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DB270
{
public:
    void freeBlock(void *block, int blockSize);
};
extern Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8
class Rva006DB160
{
public:
    void *allocBlock(int blockSize);
};
// Same pool instance allocation side; per-TU extern patches from retail.
extern class Rva006DB270 *g_pChainBlockAllocator; // 0x00E176E8
class AptValue {
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    unsigned int getRefCount() const;
    int IsReleaseAtEnd() const;
    void ClearReleaseAtEnd();
};
class AptValueVector {
    int mCapacity;
    int mCurrentNum;
    AptValue **mpValues;
    int mHighWaterNum;
public:
    AptValue *PopValue();
    void ReleaseValues();
    void rva006E6C00(AptValue *pValue);
    void rva006E6D50();
    AptValueVector *rva006E6CF0(int capacity);
};
AptValue *AptValueVector::PopValue()
{
    if (!(mCurrentNum>0)) {
        g_bfmeAptAssertAtE17734("mCurrentNum > 0", ".\\AptValue/AptValueVector.inl",95);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    return mpValues[--mCurrentNum];
}
void AptValueVector::ReleaseValues()
{
    while (mCurrentNum) {
        AptValue *value=PopValue();
        if (value->getRefCount()>0) value->ClearReleaseAtEnd();
        else value->ForceDelete();
    }
    if (!(mCurrentNum==0)) {
        g_bfmeAptAssertAtE17734("mCurrentNum == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValue\\AptValueVector.cpp",120);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
}
// ?rva006E6C00@AptValueVector@@QAEXPAVAptValue@@@Z, retail 0x006E6C00 (137B).
// AptValueVector push with ReleaseAtEnd handling: asserts IsReleaseAtEnd,
// drops on full via ClearReleaseAtEnd, else stores and bumps high-water.
// Evidence: AptValueVector.inl lines 0x35/0x43 with pValue asserts; layout
// count+4 pointer+8 capacity+0 highwater+0xC from PopValue/ReleaseValues;
// callees IsReleaseAtEnd at 0x006DBDD0 and ClearReleaseAtEnd at 0x006DBDC0;
// 16 callers unblock on landing.
void AptValueVector::rva006E6C00(AptValue *pValue)
{
    if (!static_cast<unsigned char>(pValue->IsReleaseAtEnd())) {
        g_bfmeAptAssertAtE17734("pValue->IsReleaseAtEnd()", ".\\AptValue/AptValueVector.inl", 0x35);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    if (mCurrentNum >= mCapacity) {
        pValue->ClearReleaseAtEnd();
        return;
    }
    if (!pValue) {
        g_bfmeAptAssertAtE17734("pValue != NULL", ".\\AptValue/AptValueVector.inl", 0x43);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    mpValues[mCurrentNum] = pValue;
    ++mCurrentNum;
    if (mCurrentNum > mHighWaterNum)
        mHighWaterNum = mCurrentNum;
}
// ?rva006E6D50@AptValueVector@@QAEXXZ, retail 0x006E6D50 (64B).
// AptValueVector free: asserts empty via GetNumValues then frees array
// through pool freeBlock. Evidence: AptValueVector.cpp:79 cond
// GetNumValues()==0; layout capacity+0 count+4 pointer+8 from siblings;
// callee freeBlock at 0x006DB270 via pool at 0x00E176E8; 3 callers.
void AptValueVector::rva006E6D50()
{
    if (!(mCurrentNum == 0)) {
        g_bfmeAptAssertAtE17734("GetNumValues() == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValue\\AptValueVector.cpp", 0x4F);
        if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
    }
    g_pChainBlockAllocator->freeBlock(mpValues, mCapacity * 4);
}
// ?rva006E6CF0@AptValueVector@@QAEPAV1@H@Z, retail 0x006E6CF0 (82B).
// AptValueVector init: sets capacity then allocs array via pool allocBlock.
// Evidence: AptValueVector.cpp:62 cond mpValues!=NULL; layout capacity+0
// count+4 pointer+8 highwater+0xC from siblings; callee allocBlock at
// 0x006DB160 via pool at 0x00E176E8; 2 callers.
AptValueVector *AptValueVector::rva006E6CF0(int capacity)
{
    mCapacity = capacity;
    mCurrentNum = 0;
    mHighWaterNum = 0;
    mpValues = (AptValue **)(*(Rva006DB160 **)&g_pChainBlockAllocator)->allocBlock(capacity * 4);
    if (!mpValues) {
        g_bfmeAptAssertAtE17734("mpValues != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptValue\\AptValueVector.cpp", 0x3E);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __asm int 3
    }
    return this;
}

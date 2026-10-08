// cl: /MD
// Reconstructed from BFME2 and APT 0.19.03 Xbox final donor evidence.
// Donor: ears_godfather_f PDB GUID 729627e9-b922-4d59-9b50-e116a2834635 age24;
// SHA256 8f9525adc557812dfe2866ce0d621904bfce9f9ba83341f85ec330f0b8fc4fb5.
// All five complete bodies are raw-exact in the donor and retail. Donor PDB/MAP
// supplies class/member spellings; target instructions independently establish
// offsets 0/4/8/12/16, 8-byte entries, and AddRef/Release virtual slots 0/4.
// Target constructor 0x70A740 initializes those fields and cites AptNativeHash.cpp;
// its constant-string indices 0/120 and hashes 0x6BBD/0x699 are reused by caller
// 0x70B410 to select Set__Proto__ / SetPrototype. The resize path 0x70ABC0
// constructs the same 20-byte hash and calls DestroyGCPointers at 0x70AC5B.
// Target 0x70A610 also cites AptNativeHash.h and uses the same entry layout.
// AptValue below declares only the accessed virtual interface, not its full ABI.
// Entry is a local view: the key is opaque here, not a recovered donor key type.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern "C" void *__cdecl memset(void *, int, unsigned int);
#pragma intrinsic(memset)
void __debugbreak();
#pragma intrinsic(__debugbreak)
class EAStringC {
public:
    void rva006D3C20();
    unsigned short rva006D2F40() const;
    bool rva006D3560(const EAStringC *) const;
    bool rva006D36F0(const EAStringC *) const;
    void rva006D3CA0(const EAStringC *);
    EAStringC &operator=(const EAStringC &);
    unsigned int rva006D3750() const;
    unsigned short rva006D3D10() const;
    bool IsEmpty() const;
};
class AsciiString {
    void *m_data;
public:
    bool hasData() const;
};
EAStringC *Rva0070B4F0GetString(int eSC);
class Rva006DB160 {
public:
    void *allocBlock(int blockSize);
};
extern class Rva006DB270 *g_pChainBlockAllocator;
class AptValue {
public:
    virtual void AddRef();
    virtual void Release();
};
struct AptHashItem;
class AptNativeHash {
    struct Entry { AsciiString key; AptValue *value; };
    int mnTotalSize;
    Entry *mpData;
    AptValue *mp__proto__;
    AptValue *mpPrototype;
    unsigned int nEventHandlers;
public:
    AptNativeHash(int size);
    ~AptNativeHash();
    void ClearData(); void ClearDataNoDelete();
    void Set(const EAStringC *const,AptValue *const);
    void Unset(const EAStringC *const);
    void Set__Proto__(AptValue *const value);
    void SetPrototype(AptValue *const value);
    void Unset__Proto__();
    void UnsetPrototype();
    void DestroyGCPointers();
    void rva0070A680(int index, AptValue *pValue);
    void rva0070A610(int index, AptValue *pValue);
    AsciiString *rva0070AA40();
    void rva0070AB30();
    Entry *rva0070AAA0(Entry *pItem);
private:
    AptHashItem *HashFindKey(const EAStringC *const) const;
    void Expand();
    void HashSet(const EAStringC *const,AptValue *const);
};
void AptNativeHash::Set__Proto__(AptValue *const value)
{
    if (value) value->AddRef();
    if (mp__proto__) mp__proto__->Release();
    mp__proto__ = value;
}
AptNativeHash::AptNativeHash(int size)
{
    mnTotalSize = size;
    mpData = 0;
    mp__proto__ = 0;
    mpPrototype = 0;
    nEventHandlers = 0;
    if (Rva0070B4F0GetString(0)->rva006D3750() != 9) {
        g_bfmeAptAssertAtE17734("StringPool::GetString(SC___proto__)->GetLength() == LENGTH_PROTOTYPE", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x33);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    if (Rva0070B4F0GetString(0x78)->rva006D3750() != 9) {
        g_bfmeAptAssertAtE17734("StringPool::GetString(SC_prototype)->GetLength() == LENGTH_PROTO", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x34);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    if (Rva0070B4F0GetString(0)->rva006D3D10() != 0x6BBD) {
        g_bfmeAptAssertAtE17734("StringPool::GetString(SC___proto__)->UpdateHashValue() == HASH_VALUE_PROTO", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x36);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    if (Rva0070B4F0GetString(0x78)->rva006D3D10() != 0x699) {
        g_bfmeAptAssertAtE17734("StringPool::GetString(SC_prototype)->UpdateHashValue() == HASH_VALUE_PROTOTYPE", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x37);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
}
void AptNativeHash::SetPrototype(AptValue *const value)
{
    if (value) value->AddRef();
    if (mpPrototype) mpPrototype->Release();
    mpPrototype = value;
}
void AptNativeHash::Unset__Proto__()
{
    if (mp__proto__) {
        mp__proto__->Release();
        mp__proto__ = 0;
    }
}
void AptNativeHash::UnsetPrototype()
{
    if (mpPrototype) {
        mpPrototype->Release();
        mpPrototype = 0;
    }
}
void AptNativeHash::DestroyGCPointers()
{
    if (mpPrototype) {
        mpPrototype->Release();
        mpPrototype = 0;
    }
    if (mp__proto__) {
        mp__proto__->Release();
        mp__proto__ = 0;
    }
    if (mpData) {
        for (int i = 0; i < mnTotalSize; ++i) {
            if (mpData[i].value) {
                mpData[i].value->Release();
                mpData[i].value = 0;
            }
        }
        nEventHandlers = 0;
    }
}
void AptNativeHash::rva0070A680(int index, AptValue *pValue)
{
    if (!pValue) {
        g_bfmeAptAssertAtE17734("pValue != NULL", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptNativeHash.h", 0xBD);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    pValue->AddRef();
    mpData[index].value = pValue;
}
void AptNativeHash::rva0070A610(int index, AptValue *pValue)
{
    if (!pValue) {
        g_bfmeAptAssertAtE17734("pValue != NULL", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptNativeHash.h", 0xA8);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    AptValue *oldValue = mpData[index].value;
    pValue->AddRef();
    if (oldValue)
        oldValue->Release();
    mpData[index].value = pValue;
}
AsciiString *AptNativeHash::rva0070AA40()
{
    if (!mpData)
        return 0;
    for (int i = 0; i < mnTotalSize; ++i) {
        if (!mpData[i].key.hasData())
            continue;
        if (!((const EAStringC *)&mpData[i].key)->IsEmpty())
            return &mpData[i].key;
    }
    return 0;
}
void Rva0070A6D0Release(void *pHashItem)
{
    if (!pHashItem) {
        g_bfmeAptAssertAtE17734("pHashItem != NULL", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptNativeHash.h", 0xCD);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    AptValue **ppValue = (AptValue **)((char *)pHashItem + 4);
    if (!*ppValue) {
        g_bfmeAptAssertAtE17734("pHashItem->mValue != NULL", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptNativeHash.h", 0xCE);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    (*ppValue)->Release();
    *ppValue = 0;
}
void AptNativeHash::rva0070AB30()
{
    if (mpData) {
        g_bfmeAptAssertAtE17734("IsEmpty()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x1F7);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    mpData = (Entry *)(*(Rva006DB160 **)&g_pChainBlockAllocator)->allocBlock(mnTotalSize * 8);
    if (!mpData) {
        g_bfmeAptAssertAtE17734("mpData != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x1F9);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    memset(mpData, 0, mnTotalSize * 8);
}
AptNativeHash::Entry *AptNativeHash::rva0070AAA0(Entry *pItem)
{
    if (!mpData)
        return 0;
    if (pItem < &mpData[0] || pItem >= &mpData[mnTotalSize]) {
        g_bfmeAptAssertAtE17734("(pItem >= &mpData[0]) && (pItem < &mpData[mnTotalSize])", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x1DB);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    pItem = pItem + 1;
    for (; pItem < &mpData[mnTotalSize]; ++pItem) {
        if (!pItem->key.hasData())
            continue;
        if (!((const EAStringC *)&pItem->key)->IsEmpty())
            return pItem;
    }
    return 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?handle@Gen0089C880@@QAEXXZ=?DestroyGCPointers@AptNativeHash@@QAEXXZ")

void    AptNativeHash::Set(const EAStringC * const pKey, AptValue * const pValue)
{
    if (pValue == 0)
    {
        Unset(pKey);
        return;
    }

    if  (pKey->IsEmpty())
    {
        return;
    }

    unsigned int    h = pKey->rva006D3D10();

    if ((0x699 == h) && (pKey->rva006D3560(Rva0070B4F0GetString(0x78))))
    {
        SetPrototype(pValue);
        return;
    }
    else if ((0x6BBD == h) && (pKey->rva006D3560(Rva0070B4F0GetString(0))))
    {
        Set__Proto__(pValue);
        return;
    }

    if (!mpData)
    {
        rva0070AB30();
    }

    HashSet(pKey, pValue);
}
void    AptNativeHash::Expand()
{


    AptNativeHash       TempHash(mnTotalSize * 2);
    TempHash.rva0070AB30();             //  We will add items, don't forget to allocate ;)
    EAStringC *   pKey;
    int             i;

    for(i = 0 ; i < mnTotalSize ; ++i)
    {
        
        pKey = (EAStringC *)&mpData[i].key;
        if (((AsciiString *)pKey)->hasData() == false)
        {
            continue;
        }
        if (pKey->IsEmpty())
        {
            continue;
        }

        AptValue *      pValue = mpData[i].value;
        TempHash.HashSet(pKey, pValue);
    }

    Entry *   pOldItems = mpData;
    mpData          = TempHash.mpData;
    TempHash.mpData = pOldItems;
    int         iTemp;                     // ONA 2004/4/9: It's possible that we grow several times instead only one
    iTemp               = TempHash.mnTotalSize; //  So we take the TempHash size to be sure that we have the right size
    TempHash.mnTotalSize = mnTotalSize;
    mnTotalSize = iTemp;



    TempHash.DestroyGCPointers();
}
void    AptNativeHash::HashSet(const EAStringC * const pKey, AptValue * const pValue)
{

    if (!(pKey)) { g_bfmeAptAssertAtE17734("pKey", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x2a6); if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 } }



    int         nBoundMin, nBoundMax;
    int         nFirstFit = -1;
    unsigned int    h = pKey->rva006D2F40() & (mnTotalSize-1);

    if (mpData[h].key.hasData() == false)
    {
        ((EAStringC *)&mpData[h].key)->rva006D3CA0(pKey); //  Validate the string with the new copy
        rva0070A680(h, pValue);
        return;
    }

    if (((EAStringC *)&mpData[h].key)->IsEmpty())
    {
        nFirstFit = h;
    }
    else
    {
        if (((EAStringC *)&mpData[h].key)->rva006D36F0(pKey))
        {
            rva0070A610(h, pValue);
            return;
        }
    }


    nBoundMin = h - 8;
    if (nBoundMin < 0)
    {
        nBoundMin = 0;
        nBoundMax = 2 * 8;
        if (nBoundMax >= mnTotalSize)
        {
            nBoundMax = mnTotalSize - 1;
        }
    }
    else
    {
        nBoundMax = h + 8;
        if (nBoundMax > mnTotalSize - 1)
        {
            nBoundMax = mnTotalSize - 1;
            nBoundMin = nBoundMax - (2 * 8);
            if (nBoundMin < 0)
            {
                nBoundMin = 0;
            }
        }
    }

    if (!(nBoundMax < mnTotalSize)) { g_bfmeAptAssertAtE17734("nBoundMax < mnTotalSize", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x2e5); if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 } }
    if (!(nBoundMin < nBoundMax)) { g_bfmeAptAssertAtE17734("nBoundMin < nBoundMax", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x2e6); if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 } }

    int i, nCurrentH;

    nCurrentH = h;
    i = nBoundMax - h;
    while(i--)
    {
        ++nCurrentH;
        if (mpData[nCurrentH].key.hasData() == false)
        {
            ((EAStringC *)&mpData[nCurrentH].key)->rva006D3CA0(pKey); //  Validate the string with the new copy
            rva0070A680(nCurrentH, pValue);
            return;
        }
        if (((EAStringC *)&mpData[nCurrentH].key)->IsEmpty())
        {
            if (nFirstFit != -1)
            {
                nFirstFit = nCurrentH;
            }
        }
        else
        {
            if (((EAStringC *)&mpData[nCurrentH].key)->rva006D36F0(pKey))
            {
                rva0070A610(nCurrentH, pValue);
                return;
            }
        }
    }

    nCurrentH = h;
    i = h - nBoundMin;
    while(i--)
    {
        --nCurrentH;
        if (mpData[nCurrentH].key.hasData() == false)
        {
            ((EAStringC *)&mpData[nCurrentH].key)->rva006D3CA0(pKey); //  Validate the string with the new copy
            rva0070A680(nCurrentH, pValue);
            return;
        }
        if (((EAStringC *)&mpData[nCurrentH].key)->IsEmpty())
        {
            if (nFirstFit != -1)
            {
                nFirstFit = nCurrentH;
            }
        }
        else
        {
            if (((EAStringC *)&mpData[nCurrentH].key)->rva006D36F0(pKey))
            {
                rva0070A610(nCurrentH, pValue);
                return;
            }
        }
    }



    if (nFirstFit == -1)
    {
        Expand();
        HashSet(pKey, pValue);
        return;
    }

    *(EAStringC *)&mpData[nFirstFit].key = *pKey;
    rva0070A680(nFirstFit, pValue);
}

// Later source7c62a2782ef9f3f1 supplies hash algorithms; PC retains the pre-bug884
// first-fit test !=-1. All probe bounds, assertion lines and full extents checked.
#pragma comment(linker, "/alternatename:??1AptNativeHash@@QAE@XZ=??1Rva0070A840@@QAE@XZ")
#pragma comment(linker, "/alternatename:?Unset@AptNativeHash@@QAEXQBVEAStringC@@@Z=?bfmeErase1279@BfmeLookup1279@@QAEXAAUBfmeKey1279@@@Z")

// Bind the existing addIfAbsent consumer to this now-recovered Set provider.
#pragma comment(linker, "/alternatename:?add@Rva8D0D80Table@@QAEXPAVRva8D0D80String@@PAVRva8D0D80Value@@@Z=?Set@AptNativeHash@@QAEXQBVEAStringC@@QAVAptValue@@@Z")

class Rva006DB270 { public: void freeBlock(void *,int); };
extern Rva006DB270 *g_pChainBlockAllocator;
// Donor7c62a278 source and original MAP names; PC ClearData148B/NoDelete137B.
// Direct field accesses preserve native address scheduling across virtual Release.
void AptNativeHash::ClearData()
{
    if(mpPrototype) { mpPrototype->Release();mpPrototype=0; }
    if(mp__proto__) { mp__proto__->Release();mp__proto__=0; }
    if(mpData) {
        for(int i=0;i<mnTotalSize;++i) {
            if(mpData[i].key.hasData()) {
                if(mpData[i].value) { mpData[i].value->Release();mpData[i].value=0; }
                ((EAStringC *)&mpData[i].key)->rva006D3C20();
            }
        }
        g_pChainBlockAllocator->freeBlock(mpData,mnTotalSize*8);mpData=0;
    }
    nEventHandlers=0;
}
void AptNativeHash::ClearDataNoDelete()
{
    if(mpPrototype) { mpPrototype->Release();mpPrototype=0; }
    if(mp__proto__) { mp__proto__->Release();mp__proto__=0; }
    if(mpData) {
        for(int i=0;i<mnTotalSize;++i) {
            if(mpData[i].key.hasData()) {
                if(mpData[i].value) { mpData[i].value->Release();mpData[i].value=0; }
                ((EAStringC *)&mpData[i].key)->rva006D3C20();
            }
        }
    }
    nEventHandlers=0;
}

// Original MAP signature and donor7c62a278 while(i--) loops; native extent
// through70B178 includes final return7B omitted by prior Ghidra/bank482B size.
AptHashItem *AptNativeHash::HashFindKey(const EAStringC *const pKey) const
{
    if (!pKey) {
        g_bfmeAptAssertAtE17734("pKey != NULL", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x351);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    int nIndex = pKey->rva006D2F40() & (mnTotalSize - 1);
    if (!mpData[nIndex].key.hasData())
        return 0;
    if (!((const EAStringC *)&mpData[nIndex].key)->IsEmpty()) {
        if (((const EAStringC *)&mpData[nIndex].key)->rva006D36F0(pKey))
            return (AptHashItem *)&mpData[nIndex];
    }
    int nBoundMin = nIndex - 8;
    int nBoundMax;
    if (nBoundMin < 0) {
        nBoundMin = 0;
        nBoundMax = 0x10;
        if (mnTotalSize <= 0x10)
            nBoundMax = mnTotalSize - 1;
    } else {
        nBoundMax = nIndex + 8;
        if (nBoundMax > mnTotalSize - 1) {
            nBoundMax = mnTotalSize - 1;
            nBoundMin = nBoundMax - 0x10;
            if (nBoundMin < 0)
                nBoundMin = 0;
        }
    }
    if (!(nBoundMax < mnTotalSize)) {
        g_bfmeAptAssertAtE17734("nBoundMax < mnTotalSize", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x388);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }
    if (!(nBoundMin < nBoundMax)) {
        g_bfmeAptAssertAtE17734("nBoundMin < nBoundMax", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptNativeHash.cpp", 0x389);
        if (g_bfmeAptBreakOnAssertAtDDC01C) {
            __asm int 3
        }
    }

    int current=nIndex,i=nBoundMax-nIndex;
    while(i--) {
        ++current;
        if(!mpData[current].key.hasData()) return 0;
        if(!((const EAStringC *)&mpData[current].key)->IsEmpty()) {
            if(((const EAStringC *)&mpData[current].key)->rva006D36F0(pKey)) return (AptHashItem *)&mpData[current];
        }
    }
    current=nIndex;i=nIndex-nBoundMin;
    while(i--) {
        --current;
        if(!mpData[current].key.hasData()) return 0;
        if(!((const EAStringC *)&mpData[current].key)->IsEmpty()) {
            if(((const EAStringC *)&mpData[current].key)->rva006D36F0(pKey)) return (AptHashItem *)&mpData[current];
        }
    }
    return 0;
}

#pragma comment(linker, "/alternatename:?rva0070AF90@Rva0070B380@@QAEPAXABVEAStringC@@@Z=?HashFindKey@AptNativeHash@@ABEPAUAptHashItem@@QBVEAStringC@@@Z")

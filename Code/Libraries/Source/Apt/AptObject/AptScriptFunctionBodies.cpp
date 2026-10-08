// cl: /O2 /MD /EHsc /GR-
#include "AptScriptFunction.h"
// The original PDB gives SIX arguments: constantPool occupies two stack words.
// The older seven-pointer attempt misidentified these words and member stores.
// Redwood6 APT0.19.03 private ctor record and PC full71-byte comparison agree;
// later APT3.02.02 AptScriptFunction.cpp SHA256
// e20eb4d1c0efde20bbea01f5c7d0ad49b9c6d178e2378f0eec9ed4ae18a6010b independently
// confirms this initializer sequence. Target, not the later enum, supplies45.
AptScriptFunctionByteCodeBlock::AptScriptFunctionByteCodeBlock(
    const unsigned char *pBytecodeBase, int blockSize, AptConstantPool constantPool,
    const char *pName, AptCIH *pCurCIH, AptScriptFunctionBase *pCreatorFunction)
    : AptScriptFunctionBase(AptVFT_ScriptFunctionByteCodeBlock, pCreatorFunction, pCurCIH, false),
      mpByteCodeBase(pBytecodeBase), mnByteCodeSize(blockSize), mpName(pName),
      mConstantPool(constantPool)
{
}
// PC vtable8EE9A0 slot20 points to709D30. Its21 bytes equal the original donor
// body; the single ret4 argument is the hidden structure-return pointer.
AptConstantPool AptScriptFunction2::GetConstantPool()
{
    return mpFunction->constantPool;
}

// Original donor virtual slots23 and PC full67/130B bodies establish both
// cleanup methods. The later source retains this frame restoration and register
// release loop. PC reads frame reserve+2C and saved frame/register pointers+0/+4.
// The inline base emits its own COMDAT and is inlined in Function2 as in retail.
extern AptValue *gpUndefinedValue;
inline void AptScriptFunctionBase::CleanupAfterExecution(_AptScriptFunctionState *pState)
{
    if(spFrameStack) {
        mnFrameStackReserve = (unsigned short)spFrameStack->GetNativeHashVirtual()->mnTotalSize;
        spFrameStack->Release();
    }
    spFrameStack = pState->mpFrameStack;
}
void AptScriptFunction2::CleanupAfterExecution(_AptScriptFunctionState *pState)
{
    AptScriptFunctionBase::CleanupAfterExecution(pState);
    for(int i=0; i<snRegBlockCurrentFrameCount; ++i) {
        AptValue *pValue=spRegBlockCurrentFrameBase[i];
        spRegBlockCurrentFrameBase[i]=gpUndefinedValue;
        pValue->Release();
    }
    snRegBlockCurrentFrameCount=spRegBlockCurrentFrameBase-pState->mpRegBlockPreviousFrameBase;
    spRegBlockCurrentFrameBase=pState->mpRegBlockPreviousFrameBase;
}

// Native E1835C starts at zero. Existing address-derived frame-root users
// bind this one definition through their linker aliases.
AptFrameStack *AptScriptFunctionBase::spFrameStack;

class EAStringC
{
public:
    EAStringC(const char *);
    ~EAStringC();
private:
    void *data;
};
EAStringC *Rva0070B4F0GetString(int);
void Rva00709F70Set(int, AptValue *);
extern AptValue *gpGlobalGlobalObject;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
// Original PDB and PC vtable8EE9A0 slot21 establish the two-argument API.
// Later APT source supplies the preload algorithm; its override-this/super
// arguments were added after this version and are absent in the PC body.
// Native+0A flag tests and constant-string IDs A4/A0 establish the target data.
__forceinline AptValue **advanceRegisters(AptValue **p,int n) { return p+n; }
void AptScriptFunction2::SetupBeforeExecution(_AptScriptFunctionState *pState, AptValue *pContext)
{
    pState->mpFrameStack=spFrameStack;
    spFrameStack=0;
    pState->mpRegBlockPreviousFrameBase=spRegBlockCurrentFrameBase;
    spRegBlockCurrentFrameBase=advanceRegisters(spRegBlockCurrentFrameBase,snRegBlockCurrentFrameCount);
    snRegBlockCurrentFrameCount=0;
    AptValue *pTemp=0;
    int nStartReg=1;
    if(mpFunction->getDF2Flag(1)) {
        pTemp=((AptValue *)mpCIH)->findChild(Rva0070B4F0GetString(0xA4),0);
        Rva00709F70Set(nStartReg++,pTemp);
    }
    if(mpFunction->getDF2Flag(4)) {
        g_bfmeAptAssertAtE17734("false && \"Arguments Array is unsupported in Apt at this time.\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp", 0x303);
        if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
        Rva00709F70Set(nStartReg++,gpUndefinedValue);
    }
    if(mpFunction->getDF2Flag(0x10)) {
        pTemp=pContext->findChild(Rva0070B4F0GetString(0xA0),0);
        if(pTemp==0 || !pTemp->getIsDefined()) pTemp=((AptValue *)mpCIH)->findChild(Rva0070B4F0GetString(0xA0),0);
        Rva00709F70Set(nStartReg++,pTemp);
    }
    if(mpFunction->getDF2Flag(0x40)) {
        EAStringC pTmpStr="_root";
        pTemp=((AptValue *)mpCIH)->findChild(&pTmpStr,0);
        Rva00709F70Set(nStartReg++,pTemp);
    }
    if(mpFunction->getDF2Flag(0x80)) {
        EAStringC pTmpStr="_parent";
        pTemp=((AptValue *)mpCIH)->findChild(&pTmpStr,0);
        if(pTemp==0) pTemp=gpUndefinedValue;
        Rva00709F70Set(nStartReg++,pTemp);
    }
    if(mpFunction->getDF2Flag(0x100)) Rva00709F70Set(nStartReg++,gpGlobalGlobalObject);
}

// Existing providers own the predicate and the zero-initialized global storage.
#pragma comment(linker, "/alternatename:?getIsDefined@AptValue@@QBE_NXZ=?get@Rva006DBB60ShrNAndField@@QBE_NXZ")
#pragma comment(linker, "/alternatename:?gpGlobalGlobalObject@@3PAVAptValue@@A=?g_00E18650@@3VEAStringC@@A")

#define CHECK_AT(c,s,f,l) if(!(c)) { g_bfmeAptAssertAtE17734(s,f,l); if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }
class AptCIH : public AptValue
{
public:
    AptCIH *GetRootAnimation();
    void IncZombieCount() {
        CHECK_AT(nZombieCounter < 65536, "nZombieCounter < 65536", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x53);
        nZombieCounter=nZombieCounter+1;
    }
private:
    // Native CIH adds four bytes before this field versus the original donor.
    // PC ctor709870 accesses the 16-bit zombie count at+5C, not donor+58.
    char remaining[0x5c-8];
    unsigned int nZombieCounter : 16;
};
class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *, int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
class AptPrototype : public AptValueWithHash
{
public:
    AptPrototype();
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *, unsigned int);
private:
    AptValue *mp__constructor__;
};
AptCIH *_AptGetAnimationAtLevel(int);
// Native E180F0 is zero-filled and has no existing provider.
AptPrototype *gpObjectPrototype;
// ?AptObject::AptObject present-unmatched
inline AptObject::AptObject(AptVirtualFunctionTable_Indices t, int n) : AptValueWithHash(t,n), mnImplementedObjects(0), mbHasClass(0), mbIsInMainInst(0) {}
inline void AptNativeHash::SetPrototype(AptValue *p) { if(p) p->AddRef(); if(mpPrototype) mpPrototype->Release(); mpPrototype=p; }
inline void AptNativeHash::Set__Proto__(AptValue *p) { if(p) p->AddRef(); if(mp__proto__) mp__proto__->Release(); mp__proto__=p; }
// Original private PDB signature and three native derived constructors establish
// this identity. Later source confirms scope/prototype ownership; native lacks
// the later init-action test and function-prototype assignment. FuncInfo964088
// has base destruction and the 32-byte allocation cleanup; both providers alias
// below. This also resolves the banked attempt's opaque-base codegen differences.
AptScriptFunctionBase::AptScriptFunctionBase(AptVirtualFunctionTable_Indices eType, AptScriptFunctionBase *pCreatorFunction, AptCIH *pCurCIH, bool bNeedsPrototype)
 : AptObject(eType), mpCIH(pCurCIH), mpParentAnim(0), mpCreatorScope(0), mnFrameStackReserve(0)
{
    CHECK_AT(spRegBlockBase, "spRegBlockBase", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp", 0xF4);
    if(pCreatorFunction) {
        pCreatorFunction->CreatingNestedFunction();
        mpCreatorScope=spFrameStack;
        if(mpCreatorScope) mpCreatorScope->AddRef();
    }
    if(pCurCIH->isCIH()) mpParentAnim=mpCIH->GetRootAnimation();
    else mpParentAnim=_AptGetAnimationAtLevel(0);
    mpCIH->AddRef();
    mpParentAnim->AddRef();
    mpParentAnim->IncZombieCount();
    if(bNeedsPrototype) {
        AptPrototype *pConstructorPrototype=new AptPrototype();
        mNativeHash.SetPrototype(pConstructorPrototype);
        pConstructorPrototype->GetNativeHashVirtual()->Set__Proto__(gpObjectPrototype);
    }
}

#undef CHECK_AT
#pragma comment(linker, "/alternatename:??0AptPrototype@@QAE@XZ=??0Rva006DE1A0@@QAE@XZ")
#pragma comment(linker, "/alternatename:?isCIH@AptValue@@QBE_N_N@Z=?isCIH@BfmeAptValue006DCD20@@QBEH_N@Z")
#pragma comment(linker, "/alternatename:?GetRootAnimation@AptCIH@@QAEPAV1@XZ=?rva006E0CB0@AptCIH@@QBEPBV1@XZ")
#pragma comment(linker, "/alternatename:??1AptObject@@MAE@XZ=??1Rva006D6470Owner@@UAE@XZ")
#pragma comment(linker, "/alternatename:??3AptPrototype@@SAXPAXI@Z=?Rva006F12F0Free@@YAXPAXH@Z")

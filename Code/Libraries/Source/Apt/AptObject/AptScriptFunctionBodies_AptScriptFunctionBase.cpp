// cl: /O2 /MD /EHsc /GR-
// Split from AptScriptFunctionBodies.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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



class EAStringC
{
public:
    EAStringC(const char *);
    ~EAStringC();
private:
    void *data;
};
EAStringC *Rva0070B4F0GetString(int);
extern AptValue *gpGlobalGlobalObject;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
// Original PDB and PC vtable8EE9A0 slot21 establish the two-argument API.
// Later APT source supplies the preload algorithm; its override-this/super
// arguments were added after this version and are absent in the PC body.
// Native+0A flag tests and constant-string IDs A4/A0 establish the target data.


// Existing providers own the predicate and the zero-initialized global storage.
#pragma comment(linker, "/alternatename:?gpGlobalGlobalObject@@3PAVAptValue@@A=?g_00E18650@@3VEAStringC@@A")

#define APT_SCRIPT_FUNCTION_CHECK_AT(c,s,f,l) if(!(c)) { g_bfmeAptAssertAtE17734(s,f,l); if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }
class AptCIH : public AptValue
{
public:
    AptCIH *GetRootAnimation();
    void IncZombieCount() {
        APT_SCRIPT_FUNCTION_CHECK_AT(nZombieCounter < 65536, "nZombieCounter < 65536", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x53);
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
// AptScriptFunctionBodies.cpp owns the zero-initialized prototype pointer.
extern AptPrototype *gpObjectPrototype;
// ?AptObject::AptObject present-unmatched
inline AptObject::AptObject(AptVirtualFunctionTable_Indices type, int n) : AptValueWithHash(type,n), mnImplementedObjects(0), mbHasClass(0), mbIsInMainInst(0) {}
inline void AptNativeHash::SetPrototype(AptValue *aptValue) { if(aptValue) aptValue->AddRef(); if(mpPrototype) mpPrototype->Release(); mpPrototype=aptValue; }
inline void AptNativeHash::Set__Proto__(AptValue *aptValue) { if(aptValue) aptValue->AddRef(); if(mp__proto__) mp__proto__->Release(); mp__proto__=aptValue; }
// Original private PDB signature and three native derived constructors establish
// this identity. Later source confirms scope/prototype ownership; native lacks
// the later init-action test and function-prototype assignment. FuncInfo964088
// has base destruction and the 32-byte allocation cleanup; both providers alias
// below. This also resolves the banked attempt's opaque-base codegen differences.
AptScriptFunctionBase::AptScriptFunctionBase(AptVirtualFunctionTable_Indices eType, AptScriptFunctionBase *pCreatorFunction, AptCIH *pCurCIH, bool bNeedsPrototype)
 : AptObject(eType), mpCIH(pCurCIH), mpParentAnim(0), mpCreatorScope(0), mnFrameStackReserve(0)
{
    APT_SCRIPT_FUNCTION_CHECK_AT(spRegBlockBase, "spRegBlockBase", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp", 0xF4);
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

// Native709A10..709B78 is the three-argument clone overload: ret12 and
// the original function reads at+28/+14/+10 establish its distinct ABI.
// WB179ABF0 supplies the class/constructor name and clone semantics; native
// CIH+5C and both hash-pointer reference-count transfers establish layout.
// It inherits the original creator scope without CreatingNestedFunction(),
// and copies both prototype pointers instead of allocating a prototype.
AptScriptFunctionBase::AptScriptFunctionBase(AptVirtualFunctionTable_Indices eType, AptScriptFunctionBase *pOrigFunc, AptCIH *pCurCIH)
 : AptObject(eType),mpCIH(pCurCIH),mpParentAnim(0),mnFrameStackReserve(0)
{
    APT_SCRIPT_FUNCTION_CHECK_AT(spRegBlockBase, "spRegBlockBase", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp", 0x131);
    APT_SCRIPT_FUNCTION_CHECK_AT(pOrigFunc, "pOrigFunc", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp", 0x132);
    mpCreatorScope=pOrigFunc->mpCreatorScope;
    if(pCurCIH->isCIH())mpParentAnim=mpCIH->GetRootAnimation();
    else mpParentAnim=_AptGetAnimationAtLevel(0);
    if(mpCreatorScope)mpCreatorScope->AddRef();
    mpCIH->AddRef();
    mpParentAnim->AddRef();
    mpParentAnim->IncZombieCount();
    mNativeHash.SetPrototype(pOrigFunc->mNativeHash.mpPrototype);
    mNativeHash.Set__Proto__(pOrigFunc->mNativeHash.mp__proto__);
}

#pragma comment(linker, "/alternatename:??0AptPrototype@@QAE@XZ=??0Rva006DE1A0@@QAE@XZ")
#pragma comment(linker, "/alternatename:?isCIH@AptValue@@QBE_N_N@Z=?isCIH@BfmeAptValue006DCD20@@QBE_N_N@Z")
#pragma comment(linker, "/alternatename:?GetRootAnimation@AptCIH@@QAEPAV1@XZ=?rva006E0CB0@AptCIH@@QBEPBV1@XZ")
#pragma comment(linker, "/alternatename:??1AptObject@@MAE@XZ=??1Rva006D6470Owner@@UAE@XZ")

// AptScriptFunctionBase virtuals, by retail vftable slot (0x00CEE938, 0x00CEE9A0, 0x00CEEAE8):
// slot 10 PreDestroy is the empty body, 11 DestroyGCPointers 0x00709E00, 13 RegisterReferences
// 0x00709D80, 21 SetupBeforeExecution 0x00709E50, 24 CreatingNestedFunction 0x00709A00. The
// destructor 0x00709B80 stores the base table 0x00CEE8C8 and tails into AptObject's; every
// derived deleting destructor (0x0070A530, 0x0070A590) calls it directly.
#pragma comment(linker, "/alternatename:??1AptScriptFunctionBase@@MAE@XZ=??1Rva00709B80@@UAE@XZ")
#pragma comment(linker, "/alternatename:?PreDestroy@AptScriptFunctionBase@@UAEXXZ=?debugIgnoreLeaks@?$StringBase@D@@QAEXXZ")
#pragma comment(linker, "/alternatename:?DestroyGCPointers@AptScriptFunctionBase@@UAEXXZ=?DestroyGCPointers@Rva00709B80@@UAEXXZ")
#pragma comment(linker, "/alternatename:?RegisterReferences@AptScriptFunctionBase@@UBEXXZ=?rva00709D80@Rva00709B80@@QAEXXZ")
#pragma comment(linker, "/alternatename:?SetupBeforeExecution@AptScriptFunctionBase@@UAEXPAU_AptScriptFunctionState@@PAVAptValue@@@Z=?rva00709E50@Rva00709E50@@QAEXPAPAXH@Z")
#pragma comment(linker, "/alternatename:?CreatingNestedFunction@AptScriptFunctionBase@@MAEXXZ=?rva00709A00@Rva8D0D80Result@@QAEXXZ")
// AptScriptFunctionByteCodeBlock's own slots in 0x00CEEAE8: 15 Duplicate 0x0070A360, 16 GetName
// 0x0066EA50, 17 GetNumArguments 0x0065CE90 (returns 0), 18 GetByteCodeBase 0x0066D5B0, 19
// GetByteCodeSize 0x00149580, 20 GetConstantPool 0x0070A310, 22 SetArgument 0x0070A330.
#pragma comment(linker, "/alternatename:??1AptScriptFunctionByteCodeBlock@@MAE@XZ=??1Rva00709B80@@UAE@XZ")
#pragma comment(linker, "/alternatename:?Duplicate@AptScriptFunctionByteCodeBlock@@UAEPAVAptScriptFunctionBase@@PAVAptCIH@@@Z=?rva0070A360@Rva0070A330@@QAEHH@Z")
#pragma comment(linker, "/alternatename:?GetName@AptScriptFunctionByteCodeBlock@@UBEPBDXZ=?get@Rva0066EA50DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetNumArguments@AptScriptFunctionByteCodeBlock@@UAEIXZ=?GetNativeHashVirtual@AptValue@@UAEPAUAptNativeHash@@XZ")
#pragma comment(linker, "/alternatename:?GetByteCodeBase@AptScriptFunctionByteCodeBlock@@UAEPBEXZ=?get@Rva0066D5B0DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetByteCodeSize@AptScriptFunctionByteCodeBlock@@UAEIXZ=?get@Rva00149580DwordField@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetConstantPool@AptScriptFunctionByteCodeBlock@@UAE?AUAptConstantPool@@XZ=?rva0070A310@Rva0070A310@@QAEXPAURva0070A310Pair@@@Z")
#pragma comment(linker, "/alternatename:?SetArgument@AptScriptFunctionByteCodeBlock@@UAEXPAVAptValue@@H@Z=?rva0070A330@Rva0070A330@@QAEXHH@Z")

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

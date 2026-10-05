#include "AptScriptFunction.h"
// cl: /O2 /MD
// APT0.19.03 May2006 Xbox release donor supplies class and method spellings.
// Target assertions name AptObject/AptScriptFunction.cpp and independently name
// spRegBlockBase (VA E1834C), spRegBlockCurrentFrameBase (E18350),
// snRegBlockCurrentFrameCount (E18354) and gpUndefinedValue (E18078).
// Signed loop bound E18358 is named snRegisterBlockSize by donor PDB only.
// Target Shutdown calls the already matched scalar operator delete at 2FD60.
// Initialize709610+91 uses the same globals and matched operator new2FDA0.
// AptInitParmsT::iRegArraySize name comes from final donor TPI2DEF; target
// independently loads a signed dword at+30. Only that parameter prefix is modeled.
// Target full spans709670+190 /709730+117 agree with donor records and returns.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue;
struct AptInitParmsT { unsigned char unaccessed[48]; int iRegArraySize; };
void *__cdecl operator new(unsigned int);
extern AptValue *gpUndefinedValue;
void __cdecl operator delete(void *);

// These four class statics occupy consecutive zero-filled .data slots.
// VA 0x00E1834C (.data, zero-filled tail).
AptValue **AptScriptFunctionBase::spRegBlockBase;
// VA 0x00E18350 (.data, zero-filled tail).
AptValue **AptScriptFunctionBase::spRegBlockCurrentFrameBase;
// VA 0x00E18354 (.data, zero-filled tail).
int AptScriptFunctionBase::snRegBlockCurrentFrameCount;
// VA 0x00E18358 (.data, zero-filled tail).
int AptScriptFunctionBase::snRegisterBlockSize;
#define CHECK_AT(cond,text,line) if (!(cond)) { g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp",line); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }
void AptScriptFunctionBase::ShutdownStaticData()
{
    CHECK_AT(spRegBlockCurrentFrameBase == spRegBlockBase,"spRegBlockCurrentFrameBase == spRegBlockBase",117);
    CHECK_AT(snRegBlockCurrentFrameCount == 0,"snRegBlockCurrentFrameCount == 0",118);
    for(int i=0;i<snRegisterBlockSize;++i) {
        CHECK_AT(spRegBlockBase[i] == gpUndefinedValue,"spRegBlockBase[i] == gpUndefinedValue",123);
    }
    operator delete(spRegBlockBase);
    spRegBlockBase=0;
    spRegBlockCurrentFrameBase=0;
}
void *AptScriptFunctionBase::PushStaticData()
{
    CHECK_AT(spRegBlockBase,"spRegBlockBase",159);
    CHECK_AT(spRegBlockCurrentFrameBase,"spRegBlockCurrentFrameBase",160);
    void *saved=spRegBlockCurrentFrameBase;
    spRegBlockCurrentFrameBase+=snRegBlockCurrentFrameCount;
    snRegBlockCurrentFrameCount=0;
    return saved;
}

void AptScriptFunctionBase::InitializeStaticData(const AptInitParmsT &parms)
{
    snRegisterBlockSize=parms.iRegArraySize;
    spRegBlockBase=(AptValue **)operator new(snRegisterBlockSize*sizeof(AptValue *));
    spRegBlockCurrentFrameBase=spRegBlockBase;
    for(int i=0;i<snRegisterBlockSize;++i) spRegBlockBase[i]=gpUndefinedValue;
    snRegBlockCurrentFrameCount=0;
}

void __cdecl Rva00709F70Set(int nIndex, AptValue *pNewValue)
{
    CHECK_AT(pNewValue,"pNewValue",0x2C2);
    CHECK_AT(nIndex < 256,"nIndex < MAX_REGISTERS_IN_FUNCTION",0x2C3);
    CHECK_AT(nIndex < (AptScriptFunctionBase::snRegisterBlockSize - (AptScriptFunctionBase::spRegBlockCurrentFrameBase - AptScriptFunctionBase::spRegBlockBase)),"nIndex < ( snRegisterBlockSize - (spRegBlockCurrentFrameBase-spRegBlockBase))",0x2C4);
    int next = nIndex + 1;
    if (next > AptScriptFunctionBase::snRegBlockCurrentFrameCount)
        AptScriptFunctionBase::snRegBlockCurrentFrameCount = next;
    AptValue **base = AptScriptFunctionBase::spRegBlockCurrentFrameBase;
    AptValue *old = base[nIndex];
    base[nIndex] = pNewValue;
    pNewValue->AddRef();
    old->Release();
}

#undef CHECK_AT
#define CHECK_AT(cond,text,line) if (!(cond)) { g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp",line); if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 } }
// Native GetRegisterValue helper; complete175B includes both return paths.
// Donor supplies semantic name; PC assertions prove index bounds and state.
AptValue *__cdecl Rva00709EC0Get(int nIndex)
{
    CHECK_AT(nIndex < 256,"nIndex < MAX_REGISTERS_IN_FUNCTION",0x29E);
    CHECK_AT(nIndex < (AptScriptFunctionBase::snRegisterBlockSize - (AptScriptFunctionBase::spRegBlockCurrentFrameBase - AptScriptFunctionBase::spRegBlockBase)),"nIndex < ( snRegisterBlockSize - (spRegBlockCurrentFrameBase-spRegBlockBase))",0x29F);
    CHECK_AT(AptScriptFunctionBase::spRegBlockCurrentFrameBase[nIndex],"spRegBlockCurrentFrameBase[nIndex]",0x2A0);
    return AptScriptFunctionBase::spRegBlockCurrentFrameBase[nIndex];
}

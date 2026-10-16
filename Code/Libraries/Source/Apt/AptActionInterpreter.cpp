// cl: /O2 /MD /EHsc
#include "AptObject/AptScriptFunction.h"
// ?rva006ff980@@YAXPAVAptValue@@AAVEAStringC@@H@Z
// retail 0x006FF980..0x006FFC2A (682 bytes), cdecl, recursive.
// Callers: the rowed path workers 0x006FFC30 and 0x006FFCE0, which pass
// (value, sBuf, 0) and (value, sBuf, 1). WB twin 0x0175DEB0
// (AptActionInterpreter.cpp assert lines 0x677/0x67C) supplies the flow.
// Target evidence: the retail assert text names the four CIH predicates
// (isButtonInst inlined with the AptCIH.h:0xB5 this-assert, as in the matched
// getVariable 0x006FFD80); the separator is "." for a dotted path and "/"
// otherwise; a parentless clip prints "_level%d" from the signed 17-bit field
// at +0x58; a named clip appends separator+name (+0x08); an unnamed one gets
// "instance%ld", stores it as its name and registers itself under it in the
// parent character's native hash (+0x4C, then +0x10). Field names are
// structural inferences; the function name is address-derived.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
extern "C" int __cdecl sprintf(char *, const char *, ...);

#define APT_ASSERT(cond, text, file, line)                                     \
    if (!(cond)) {                                                             \
        g_bfmeAptAssertAtE17734(text, file, line);                             \
        if (g_bfmeAptBreakOnAssertAtDDC01C)                                    \
            __debugbreak();                                                    \
    }
#define APT_CIH_H "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h"
#define APT_INTERP_CPP "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp"

class EAStringC
{
    void *mpData;
public:
    EAStringC();
    EAStringC(const char *value);
    ~EAStringC();
    EAStringC &operator=(const EAStringC &);
    bool IsEmpty() const;
    EAStringC &Rva006D4F00Append(const EAStringC &);
    EAStringC &Rva006D50A0Append(const char *);
    void __cdecl rva006D62C0(const char *, ...);
};
EAStringC rva006D5160(const char *, const EAStringC &);

class AptValue;
struct Rva006FF980Character
{
    char pad0[0x10];
    AptNativeHash *mpNativeHash; // +0x10
};
class Rva006DBB30SarDwordField
{
public:
    int get() const; // 0x006DBB30
};
class BfmeAptValue006DCD20
{
public:
    int rva006E02B0() const; // rowed provider at 0x006E02B0; callers test AL
    int isNativeFunction() const;
    int isScriptFunction() const;
    bool isUndefined() const;
    int rva006E03A0() const;
    BfmeAptValue006DCD20 *rva006DCF20();
    BfmeAptValue006DCD20 *rva006DCEE0();
};
class AptCIH : public AptValue
{
public:
    bool IsSpriteInstBase() const; // 0x006CFCD0
    bool IsLevelInst() const;      // 0x006E03A0
    bool IsCharacterInst() const;  // 0x006E0200
    __forceinline bool isButtonInst() const
    {
        APT_ASSERT(this, "this", APT_CIH_H, 0xB5)
        return ((const Rva006DBB30SarDwordField *)this)->get() == 14 && !isUndefined();
    }
    // Keep the AL-test adapter inline without a competing external definition.
    __declspec(dllimport) __forceinline bool isTextInst() const
    {
        return (unsigned char)((const BfmeAptValue006DCD20 *)this)->rva006E02B0();
    }
    __forceinline AptCIH *c_characterInst()
    {
        APT_ASSERT(IsCharacterInst(), "isCharacterInst()", APT_CIH_H, 0xA5)
        return this;
    }
    // The canonical AptValue base supplies the eight-byte vptr/flags prefix.
    EAStringC mName;                  // +0x08
    char padC[0x3C];
    AptCIH *mpParent;                 // +0x48
    Rva006FF980Character *mpCharacter; // +0x4C
    char pad50[0x8];
    int mnLevel : 17;                 // +0x58
    unsigned int state;              // +0x5C; retail tests bits 18..19
    const AptCIH *rva006E0CB0() const;
};

void rva006ff980(AptValue *pValue, EAStringC &sBuf, int bDotted)
{
    AptCIH *pContext = (AptCIH *)pValue;
    APT_ASSERT(pContext->IsSpriteInstBase() || pContext->isButtonInst() || pContext->IsLevelInst()
                   || pContext->isTextInst(),
               "pContext->isSpriteInstBase() || pContext->isButtonInst() || pContext->isLevelInst() || pContext->isTextInst()",
               APT_INTERP_CPP, 0x677)
    const char *sep = !bDotted ? "/" : ".";
    AptCIH *pParent = pContext->mpParent;
    if (!pParent) {
        APT_ASSERT(pContext->IsSpriteInstBase() || pContext->isButtonInst() || pContext->IsLevelInst()
                       || pContext->isTextInst(),
                   "pContext->isSpriteInstBase() || pContext->isButtonInst() || pContext->isLevelInst() || pContext->isTextInst()",
                   APT_INTERP_CPP, 0x67C)
        if ((bDotted == 0 && pContext->mnLevel != 0) || bDotted == 1) {
            char buf[16];
            sprintf(buf, "_level%d", pContext->mnLevel);
            EAStringC level(buf);
            sBuf = level;
        }
        return;
    }
    rva006ff980(pParent, sBuf, bDotted);
    if (!pContext->mName.IsEmpty()) {
        sBuf.Rva006D4F00Append(rva006D5160(sep, pContext->mName));
    } else {
        int id = pContext->mnLevel;
        EAStringC name;
        sBuf.Rva006D50A0Append(sep);
        name.rva006D62C0("instance%ld", id);
        sBuf.Rva006D4F00Append(name);
        pContext->mName = name;
        Rva006FF980Character *pCharacter = pParent->c_characterInst()->mpCharacter;
        AptNativeHash *pHash = pCharacter->mpNativeHash;
        pHash->Set(&name, pContext);
    }
}

// The callback field at +0x20 and its context/count ABI are corroborated by
// the retail native-function constructor and this function's indirect call.
struct BfmeAptNativeFunctionView
{
    char opaque[0x20];
    AptValue *(__cdecl *function)(AptValue *, int);
};
class Rva006CD650
{
public:
    void *rva006CD650();
};
extern AptValue *gpUndefinedValue;
inline void *operator new(unsigned int, void *storage) { return storage; }

class AptBasePtrStack
{
public:
    int count, capacity;
    AptValue **items;
    BfmeAptValue006DCD20 *At(int);
    void rva006E3AA0(int);
    void PopAndPush(int, BfmeAptValue006DCD20 *);
    void rva006FDF30(BfmeAptValue006DCD20 *);
    // This is the inlined call-site form. The established out-of-line
    // PushNoInc provider has a different body; do not emit a competing copy.
    __declspec(dllimport) __forceinline void PushNoInc(AptValue *value)
    {
        APT_ASSERT(count < capacity, "m_nElements < m_nCapacity",
                   "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x90)
        items[count++] = value;
    }
};
template<class T> struct AptValuePtrStack
{
    int count, capacity;
    AptValue **items;
    void push(AptValue *);
    void pop()
    {
        APT_ASSERT(count > 0, "size() > 0",
                   "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x7D)
        items[count - 1]->Release();
        --count;
    }
};
struct AptActionInterpreter
{
    AptBasePtrStack stack;
    char pad0C[0x24 - 12];
    AptValuePtrStack<AptValue> thisStack; // +0x24
    AptScriptFunctionBase *mpCurrentFunction; // +0x30
    char debug[12];
    AptConstantPool constantPool; // +0x40
    char pad48[0x60 - 0x48];
    int unwind; // +0x60

    const unsigned char *runStream(const unsigned char *, AptCIH *, int,
                                   struct AptCharacterInst *);
    void callFunction(AptValue *, AptValue *, int);
};

// Retail's 20-byte local frame holds the pre-call stack count and this
// 16-byte workspace. Its pool result and execution state occupy the same
// eight bytes at non-overlapping times, below the saved constant pool.
// Explicit trivial-object lifetimes preserve that storage reuse with MSVC
// 7.1; independent locals reverse the two areas in otherwise identical code.
// This workspace is a reconstruction aid, not a claimed original type.
struct AptInterpreterCallFrame
{
    union {
        AptConstantPool pool;
        _AptScriptFunctionState state;
    } scratch;
    AptConstantPool savedPool;
};
typedef char AptInterpreterCallFrameSize[sizeof(AptInterpreterCallFrame) == 16 ? 1 : -1];

// ?callFunction@AptActionInterpreter@@QAEXPAVAptValue@@0H@Z
// Native RVA 0x00706660..0x00706946: all 742 bytes including RET 12.
// Original Redwood6 PDB/MAP establishes the three-argument method ABI;
// WB 0x0175EA50 corroborates dispatch, argument setup and cleanup order.
// Continues the banked reconstruction in reverse/re_attempts.log. Uses the
// canonical ScriptFunction layout and the existing providers' signatures;
// AL truncation matches the retail predicate tests without new symbol pins.
void AptActionInterpreter::callFunction(AptValue *context, AptValue *function, int nParams)
{
    int nStackElementsPre = stack.count - nParams;
    if (function && (unsigned char)((BfmeAptValue006DCD20 *)function)->isNativeFunction()) {
        AptInterpreterCallFrame nativeFrame;
        nativeFrame.savedPool = constantPool;
        stack.PopAndPush(nParams, (BfmeAptValue006DCD20 *)
            ((BfmeAptNativeFunctionView *)((BfmeAptValue006DCD20 *)function)->rva006DCF20())->function(context, nParams));
        constantPool = nativeFrame.savedPool;
    } else if (function && (unsigned char)((BfmeAptValue006DCD20 *)function)->isScriptFunction()) {
        AptInterpreterCallFrame frame;
        frame.savedPool = constantPool;
        AptScriptFunctionBase *pPrevFunction = mpCurrentFunction;
        mpCurrentFunction = (AptScriptFunctionBase *)((BfmeAptValue006DCD20 *)function)->rva006DCEE0();
        constantPool = *new (&frame.scratch.pool) AptConstantPool(mpCurrentFunction->GetConstantPool());
        if (((BfmeAptValue006DCD20 *)mpCurrentFunction->mpCIH)->isUndefined()
            || ((unsigned char)((BfmeAptValue006DCD20 *)mpCurrentFunction->mpCIH)->rva006E03A0()
                && (mpCurrentFunction->mpCIH->state & 0xC0000) == 0)
            || ((unsigned char)((BfmeAptValue006DCD20 *)mpCurrentFunction->mpCIH)->rva006E03A0()
                && (mpCurrentFunction->mpCIH->state & 0xC0000) == 0x80000)) {
            stack.rva006E3AA0(nParams);
            stack.rva006FDF30((BfmeAptValue006DCD20 *)gpUndefinedValue);
            mpCurrentFunction->mpCIH = (AptCIH *)gpUndefinedValue;
        } else {
            thisStack.push(context);
            mpCurrentFunction->AddRef();
            // The temporary pool has been copied; begin the execution-state
            // lifetime in its storage. Both union members are trivial.
            new (&frame.scratch.state) _AptScriptFunctionState;
            mpCurrentFunction->SetupBeforeExecution(&frame.scratch.state, context);
            int nFormalArgs = mpCurrentFunction->GetNumArguments();
            int nArgs = nFormalArgs < nParams ? nFormalArgs : nParams;
            int i;
            for (i = 0; i < nArgs; ++i) {
                AptValue *param = (AptValue *)stack.At(i);
                mpCurrentFunction->SetArgument(param, i);
            }
            for (; i < nFormalArgs; ++i)
                mpCurrentFunction->SetArgument(gpUndefinedValue, i);
            stack.rva006E3AA0(nParams);
            const AptCIH *root = mpCurrentFunction->mpParentAnim->rva006E0CB0();
            AptCharacterInst *character = root ? (AptCharacterInst *)((Rva006CD650 *)root)->rva006CD650() : 0;
            runStream(mpCurrentFunction->GetByteCodeBase(), mpCurrentFunction->mpCIH,
                      mpCurrentFunction->GetByteCodeSize(), character);
            mpCurrentFunction->CleanupAfterExecution(&frame.scratch.state);
            mpCurrentFunction->Release();
            thisStack.pop();
        }
        mpCurrentFunction = pPrevFunction;
        constantPool = frame.savedPool;
    } else {
        stack.rva006E3AA0(nParams);
        stack.PushNoInc(gpUndefinedValue);
    }
    int nStackElementsPost = stack.count;
    if (unwind) {
        if (nStackElementsPost > nStackElementsPre)
            stack.rva006E3AA0(nStackElementsPost - nStackElementsPre);
    } else {
        APT_ASSERT(nStackElementsPost == nStackElementsPre || nStackElementsPost == nStackElementsPre + 1,
                   "nStackElementsPost == nStackElementsPre || nStackElementsPost == (nStackElementsPre+1)",
                   APT_INTERP_CPP, 0x837)
    }
}

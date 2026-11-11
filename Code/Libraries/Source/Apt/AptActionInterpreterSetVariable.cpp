// ?setVariable@AptActionInterpreter@@QAE_NPAVAptValue@@0PBVEAStringC@@0HHH@Z
// cl: /O2 /MD /EHsc
// Target evidence: Ghidra gives 0x006FED00 a 739-byte extent. The 0x006CCA50
// caller loads g_aptDateInterpreter in ECX and supplies the seven stack args;
// retail calls 0x006FEC00, 0x006FBE60, AptNativeHash::Set at 0x0070B410,
// and AptNativeHash::rva0070B180 at 0x0070B180. Other branches use the rowed
// AptValue predicates and virtual slots. The final CIH assertion string and
// AptActionInterpreter.cpp:0x4cc location come directly from retail operands.
// Donor evidence: the pinned original AptActionInterpreter::setVariable
// signature/defaults are from the Redwood6 PDB and _AptActions.h. The context,
// current-frame and native-hash relationships below follow the retail calls;
// offsets +0x24 and +0x30 are target accesses supported by the donor layout.
class AptCIH;
class AptValue;
class AptScriptFunctionBase;
class AptFrameStack;
class Rva8D0D80String;
class Rva8D0D80Value;

#include "EAStringC.h"
// setVariable calls EAStringC's default constructor (0x006D2F90, folded with
// clear), declared in EAStringC.h; its rowed definition is AptValueUrlEncode.cpp's.

#include "AptNativeHash.h"

#include "AptValue.h"

#include "BfmeAptValue006DCD20.h"

extern AptValue *g_00E180B0;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

// class-gate: allow AptScriptFunctionBase target-proven field view: retail
// SetVariable reads parent animation at +0x24; static frame pointer is the
// established AptScriptFunctionBase::spFrameStack at VA 0x00E1835C.
struct AptActionInterpreter;
class AptScriptFunctionBase {
    unsigned char m_beforeParentAnimation[0x24];
protected:
    static AptFrameStack *spFrameStack;	// protected: rowed ?spFrameStack@AptScriptFunctionBase@@1PAVAptFrameStack@@A
    friend class AptActionInterpreter;
public:
    AptValue *mpParentAnim;
    AptValue *mpCreatorScope;
    void rva006FBED0();
};

class Rva006FBE60 {
public:
    bool rva006FBE60(Rva8D0D80String *, Rva8D0D80Value *);
};

struct AptActionInterpreter {
private:
    unsigned char m_beforeCurrentFunction[0x30];
    AptScriptFunctionBase *mpCurrentFunction;
private:
    static bool getContext(AptValue *, AptValue *, const EAStringC *, AptValue **, EAStringC &);
public:
    bool setVariable(AptValue *, AptValue *, const EAStringC *, AptValue *, int = 1, int = 1, int = 0);
};

#pragma comment(linker, "/alternatename:?getContext@AptActionInterpreter@@CA_NPAVAptValue@@0PBVEAStringC@@PAPAV2@AAV3@@Z=?rva006FEC00@@YAEHHPAVEAStringC@@PAH0@Z")

bool AptActionInterpreter::setVariable(AptValue *context, AptValue *with,
                                       const EAStringC *sourceName, AptValue *value,
                                       int localFrameMode, int searchCurrentFrame,
                                       int directContext)
{
    EAStringC name;
    AptValue *resolvedContext;
    if (directContext == 0) {
        getContext(context, with, sourceName, &context, name);
        resolvedContext = context;
    } else {
        resolvedContext = context;
        name = *sourceName;
    }

    if (!resolvedContext)
        return false;
    if (resolvedContext->isCIH(false)
        && (unsigned char)((BfmeAptValue006DCD20 *)resolvedContext->c_cih(false))->rva006E0260())
        return false;
    if (!resolvedContext->isUndefined()
        && resolvedContext->objectMemberSet(resolvedContext, &name, value))
        return true;

    if (localFrameMode) {
        if (searchCurrentFrame && mpCurrentFunction
            && ((Rva006FBE60 *)mpCurrentFunction)->rva006FBE60(
                (Rva8D0D80String *)&name, (Rva8D0D80Value *)value))
            return true;

        AptNativeHash *hash = resolvedContext->GetNativeHashVirtual();
        if (hash) {
            hash->Set(&name, value);
            hash->rva0070B180((BfmeAptValue006DCD20 *)resolvedContext, &name,
                              !value || value->isUndefined());
            if (resolvedContext == g_00E180B0 && value->isScriptFunction()) {
                AptNativeHash *functionHash = value->GetNativeHashVirtual();
                AptNativeHash *prototypeHash = functionHash->mpPrototype->GetNativeHashVirtual();
                if (prototypeHash->mp__proto__)
                    prototypeHash->mp__proto__->Release();
                prototypeHash->mp__proto__ = 0;
            }
            return true;
        }

        if (!resolvedContext->isCIH(false) && mpCurrentFunction && !directContext) {
            AptNativeHash *parentHash = mpCurrentFunction->mpParentAnim->GetNativeHashVirtual();
            if (parentHash)
                parentHash->Set(&name, value);
            return true;
        }

        if (resolvedContext->isCIH(false)) {
            if (!(unsigned char)((BfmeAptValue006DCD20 *)resolvedContext->c_cih(false))->rva006DCC60(false))
                return true;
            g_bfmeAptAssertAtE17734(
                "false && \"SHOULD NOT GET HERE ANYMORE\"",
                "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",
                0x4cc);
            if (g_bfmeAptBreakOnAssertAtDDC01C)
                __debugbreak();
            BfmeAptValue006DCD20 *displayOwner =
                *(BfmeAptValue006DCD20 **)((unsigned char *)resolvedContext->c_cih(false) + 0x48);
            void *displayHash = displayOwner->rva006E04A0();
            if (displayHash)
                ((AptNativeHash *)displayHash)->Set(&name, value);
        }
    } else if (mpCurrentFunction) {
        if (!AptScriptFunctionBase::spFrameStack)
            mpCurrentFunction->rva006FBED0();
        ((AptNativeHash *)((unsigned char *)AptScriptFunctionBase::spFrameStack + 8))->Set(&name, value);
    } else {
        AptNativeHash *hash = resolvedContext->GetNativeHashVirtual();
        if (hash) {
            hash->Set(&name, value);
            hash->rva0070B180((BfmeAptValue006DCD20 *)resolvedContext, &name,
                              !value || value->isUndefined());
        }
    }
    return true;
}

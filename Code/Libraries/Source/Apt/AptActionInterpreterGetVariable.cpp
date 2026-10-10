// cl: /O2 /G6 /arch:SSE /MD /EHsc
// ?getVariable@AptActionInterpreter@@QAEPAVAptValue@@PAV2@0PBVEAStringC@@HHH@Z
// retail 0x006FFD80..0x0070008D (781 bytes) thiscall ret 0x18; recursive.
// Callers: interpreter handlers 0x00705330/0x007056D0 and the matched
// handler unit (pCurrentContext pCurWith name and the 1/1/0 defaults).
// WB twin 0x0175E4F0 (AptActionInterpreter.cpp assert line 1816 = 0x718)
// supplies the flow; the retail assert text names the four CIH predicates
// (isButtonInst inlined with the AptCIH.h:0xB5 this-assert; IsSpriteInstBase
// 0x006CFCD0 IsLevelInst 0x006E03A0 and isTextInst 0x006E02B0 called).
// Flow: a name starting with $ becomes a new AptString; otherwise resolve the
// context through getContext 0x006FEC00 (or take the context and copy the
// name), then try the context child (findChild 0x006DF9A0) the current
// function locals (0x006FBE80 on interpreter +0x30) the context member lookup
// (vtable slot 7) and child again; with a with-object recurse once without
// it; finally the current function parent-anim native hash (+0x24 slot 3 then
// AptNativeHash::Lookup) and the undefined-variable callback at 0x00E177C4.
// The getContext result goes through a separate out temporary: retail keeps
// it in the dead pCurrentContext home slot and copies it to a register.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

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
    ~EAStringC();
    EAStringC &operator=(const EAStringC &);
    bool IsEmpty() const;
    const char *rva00620090() const; // 0x00620090
};

class AptCIH;
class AptNativeHash;
class AptValue
{
    unsigned int mnValueData;
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual int getHasClass() const;
    virtual void setHasClass(int);
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
    bool isCIH(bool = false) const;
    AptCIH *c_cih(bool = false);
    bool isUndefined() const;
    AptValue *findChild(const EAStringC *, AptValue *);
};
class Rva006DBB30SarDwordField
{
public:
    int get() const; // 0x006DBB30
};
class AptCIH : public AptValue
{
public:
    bool IsSpriteInstBase() const; // 0x006CFCD0
    bool IsLevelInst() const;      // 0x006E03A0
    __forceinline bool isButtonInst() const
    {
        APT_ASSERT(this, "this", APT_CIH_H, 0xB5)
        return ((const Rva006DBB30SarDwordField *)this)->get() == 14 && !isUndefined();
    }
};
class BfmeAptValue006DCD20
{
public:
    bool rva006E02B0() const; // 0x006E02B0 isTextInst
};
struct AptNativeHash
{
    AptValue *Lookup(const EAStringC *const) const;
};
class AptString : public AptValue
{
public:
    static AptString *Create();
    EAStringC str; // +0x08
};
class BfmeN1034;
class Rva006FBE80
{
public:
    BfmeN1034 *find2(int name); // 0x006FBE80
    char pad0[0x24];
    AptCIH *mpParentAnim; // +0x24
};
extern AptValue *gpUndefinedValue;
extern void (__cdecl *g_00E177C4)(const char *);

struct AptActionInterpreter
{
    char pad0[0x30];
    Rva006FBE80 *mpCurrentFunction; // +0x30
    AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int = 1, int = 1, int = 0);
private:
    static bool getContext(AptValue *, AptValue *, const EAStringC *, AptValue **, EAStringC &);
};

AptValue *AptActionInterpreter::getVariable(AptValue *pCurrentContext, AptValue *pCurWith, const EAStringC *pName,
                                            int bWith, int bLocals, int bNoContext)
{
    EAStringC name;
    APT_ASSERT(!pCurrentContext || !pCurrentContext->isCIH() || pCurrentContext->c_cih()->isButtonInst()
                   || pCurrentContext->c_cih()->IsSpriteInstBase() || pCurrentContext->c_cih()->IsLevelInst()
                   || ((BfmeAptValue006DCD20 *)pCurrentContext->c_cih())->rva006E02B0(),
               "!pCurrentContext || !pCurrentContext->isCIH() || pCurrentContext->c_cih()->isButtonInst() || pCurrentContext->c_cih()->isSpriteInstBase() || pCurrentContext->c_cih()->isLevelInst() || pCurrentContext->c_cih()->isTextInst()",
               APT_INTERP_CPP, 0x718)
    if (*pName->rva00620090() == '$') {
        AptString *pString = AptString::Create();
        pString->str = *pName;
        return pString;
    }
    bool bFound = false;
    AptValue *pContext;
    if (!bNoContext) {
        AptValue *pFound;
        bFound = getContext(pCurrentContext, pCurWith, pName, &pFound, name);
        pContext = pFound;
    } else {
        pContext = pCurrentContext;
        name = *pName;
    }
    if (name.IsEmpty()) {
        if (pContext)
            return pContext;
        return gpUndefinedValue;
    }
    AptValue *pResult;
    if (bFound == true && pContext) {
        pResult = pContext->findChild(&name, pCurWith);
        if (pResult)
            return pResult;
    }
    if (bLocals && mpCurrentFunction) {
        pResult = (AptValue *)mpCurrentFunction->find2((int)&name);
        if (pResult)
            return pResult;
    }
    if (!pContext || pContext->isUndefined()) {
        if (pCurWith)
            return getVariable(pCurrentContext, 0, pName, bWith, 1, 0);
        return gpUndefinedValue;
    }
    pResult = pContext->objectMemberLookup(pContext, &name);
    if (pResult)
        return pResult;
    pResult = pContext->findChild(&name, pCurWith);
    if (pResult)
        return pResult;
    if (pCurWith)
        return getVariable(pCurrentContext, 0, pName, bWith, 1, 0);
    if (!pContext->isCIH() && mpCurrentFunction && !bNoContext) {
        AptNativeHash *pHash = mpCurrentFunction->mpParentAnim->GetNativeHashVirtual();
        if (pHash) {
            pResult = pHash->Lookup(&name);
            if (pResult)
                return pResult;
        }
    }
    if (g_00E177C4)
        g_00E177C4(pName->rva00620090());
    return gpUndefinedValue;
}

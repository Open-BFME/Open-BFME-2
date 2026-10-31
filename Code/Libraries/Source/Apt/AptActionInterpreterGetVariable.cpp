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
public:
	class StringDataC { public: unsigned short m_uRefCount; unsigned short m_uSize; unsigned short m_uMaxSize; unsigned short m_uHash; };
	EAStringC();
	EAStringC(const char *value);
	~EAStringC();
	EAStringC &operator=(const EAStringC &);
	bool IsEmpty() const;
	bool rva006D3510(const char *) const;
	const char *rva00620090() const; // 0x00620090
	EAStringC(const EAStringC &);
	EAStringC &Rva006D4F00Append(const EAStringC &);
	EAStringC &Rva006D50A0Append(const char *);
	void __cdecl rva006D62C0(const char *, ...);
	EAStringC &clear();
	unsigned int rva006D3750() const;
	void rva006D3470();
	EAStringC &TrimRight(const char *);
	EAStringC(unsigned int,unsigned int);
	EAStringC rva006D5ED0(int) const;
	EAStringC rva006d5f30(int,int) const;
	int Find(char,int=0);
	EAStringC &Append(const char *const,unsigned int);
	bool IsEqualTo(const EAStringC *) const;
	bool rva006D3560(const EAStringC *) const;
	int rva006d6070(const char *,int=0);
	int GetAt(int) const;
	int rva006D54B0(int,int);
private:
	StringDataC *mpData; // +0x00
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
	int rva006E02B0() const; // rowed provider at 0x006E02B0; callers test AL
	int isNativeFunction() const;
	bool rva006DCA60() const;
	int isObject() const;
	int isInteger() const;
	int isFloat() const;
	int isString() const;
	int toInteger() const;
	float rva006DD460();
	BfmeAptValue006DCD20 *rva006DCF60(bool);
	BfmeAptValue006DCD20 *checkedString();
	int isScriptFunction() const;
	bool isUndefined() const;
	int rva006E03A0() const;
	BfmeAptValue006DCD20 *rva006DCF20();
	BfmeAptValue006DCD20 *rva006DCEE0();
	void rva006DD6C0(EAStringC *out);
	// These call-site views follow the retail test-al instruction at 0x6FED89
	// and 0x6FEF02; the matched predicate declarations keep their own names.
	int rva006E0260() const;
	int rva006DCC60(bool) const;
	void *rva006E04A0() const;
	virtual void AddRef();
	virtual void Release();
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
void (__cdecl *g_aptUndefinedVariableCallback)(const char *);

struct AptActionInterpreter
{
    char pad0[0x30];
    class AptScriptFunctionBase *mpCurrentFunction; // +0x30
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
                   || (unsigned char)((BfmeAptValue006DCD20 *)pCurrentContext->c_cih())->rva006E02B0(),
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
        pResult = (AptValue *)((Rva006FBE80 *)mpCurrentFunction)->find2((int)&name);
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
        AptNativeHash *pHash = ((Rva006FBE80 *)mpCurrentFunction)->mpParentAnim->GetNativeHashVirtual();
        if (pHash) {
            pResult = pHash->Lookup(&name);
            if (pResult)
                return pResult;
        }
    }
    if (g_aptUndefinedVariableCallback)
        g_aptUndefinedVariableCallback(pName->rva00620090());
    return gpUndefinedValue;
}

class AptCIH;
// cl: /O2 /MD /EHsc
// Split from AptActionInterpreterConstantHandlers.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// Active PC interpreter handlers, identified by explicit opcode fields in the
// 185-entry table at RVA9DC980. Every slot/pointer and complete native extent
// was re-read; frozen research coverage was refreshed against the live ledger.
// Original Redwood6 PDB supplies private static two-argument signatures.
// Later APT3.02.02 AptActionInterpreter.cpp is the semantic/body reference:
// SHA256 0cbfd5f746c895045f46f8ee139e803dda0f88e1dd006a9ca383bc889b9b2237.
// Build-specific Godfather original PDBs independently name constantPool+40
// and LocalContextT(28B); PC instructions confirm instruction+0, return+14,
// dictionary item pointer+44. Only the accessed interpreter prefix is modeled.
// AptValue prefix is vptr+flags (8B); the PC stack Release calls use slot1.
// Native Delete uses ContainsNativeHashVirtual at slot4. Original Redwood6
// PDB order is recorded in AptObject/AptScriptFunction.h; use that prefix.
// Native arithmetic uses SWF version ==7, not the later source's >=7.
// Native Pop(2) releases items[count-i] before one count decrement; the later
// container-based implementation pops individually. Preserve PC sequencing.
// PushThis/PushGlobal push pooled NAME strings, not the context objects.
// Slots75(NULL) and76(Undefined) share705320; row it only once as Undefined.
#include <string.h>
#include <math.h>

// Preserve fmodf's float argument rounding before the MSVC _CIfmod intrinsic.
// Native Modulo spills its second conversion to a float slot before the call.
#pragma intrinsic(fmod)
// Native equality threshold is double0.001 at VA BC6E68, not the later float macro.
#pragma intrinsic(strcmp)
#pragma intrinsic(fabs)
static __forceinline float bfme_fmodf(float x,float y) { return (float)fmod(x,y); }
class EAStringC;
class AptString;
class AptInteger;
class AptScriptFunctionBase;
class AptPrototype;
class AptLookup;
class AptRegister;
class AptArray;
class AptNativeHash;
class AptCIH;
enum AptVirtualFunctionTable_Indices { AptVFT_ScriptFunctionByteCodeBlock = 45 };
class AptValue {
    unsigned int m_valueFlags;
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ForceDelete();
    virtual AptNativeHash *GetNativeHashVirtual();
    virtual bool ContainsNativeHashVirtual() const;
    virtual int getHasClass() const;
    virtual void setHasClass(int);
    AptValue *findChild(const EAStringC *,AptValue *);
    AptCIH *c_cih(bool=false);
    AptArray *c_array() const;
    bool getIsDefined() const; bool isBoolean() const; bool isNone() const; bool isScriptFunction() const; bool isNativeFunction() const;
    bool isArray() const;
    AptVirtualFunctionTable_Indices getVtblIndex() const;
    bool isPrototype() const;
    AptPrototype *c_prototype() const;
    bool isLookup() const;
    bool isRegister() const;
    AptLookup *c_lookup() const;
    AptRegister *c_register() const;
    bool isExtern() const;
    AptCIH *c_cih(bool=false) const;
    unsigned int getRefCount() const;
    bool isCIH(bool=false) const;
    bool isObject() const;
    AptString *c_string() const;
    AptInteger *c_integer() const;
    bool isUndefined() const;
    bool isInteger() const;
    bool isFloat() const;
    void SetString(const char *);
    float toFloat() const;
    bool toBool() const;
    int toInteger() const;
    void toString(EAStringC &) const;
};
struct AptCharacterInst;
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
class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *,int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
// Native InitArray allocates44B; ctor6D91B0 builds type0x16, hash+8,
// AptArray vtableCEA778 and slots+20/+24/+28. Unaccessed state stays opaque.
class AptArray : public AptValue { char m_arrayState[32]; public: int mnCount; AptValue *GetAt(int) const; AptArray(); static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); } static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); } AptValue *get(int); void set(int,AptValue *); };
// PC callbacks occupy two independently zero-initialized slots in gAptFuncs.
// Member handlers establish the getter/setter ABI; later source names their role.
extern AptValue *(__cdecl *g_bfmeAptGetExternAtE17768)(const char *);
extern void (__cdecl *g_bfmeAptSetExternAtE17764)(const char *,const char *);
class AptString : public AptValue { public: static AptString *Create(); EAStringC str; __forceinline EAStringC *GetInternalString() { return &str; } };
class AptInteger : public AptValue { public: static AptValue *Create(int); int GetInt() const; };
int Rva006CD220Get();
bool rva006fc370(AptValue *);
class AptBoolean
{
public:
	static AptValue *Create(bool value);
};
AptValue *Rva008A4EA0MakeFloat(float);
EAStringC *Rva0070B4F0GetString(int);
extern void *g_eaStringAtE177D4Storage;
extern AptValue *gpUndefinedValue;
extern AptValue *gpGlobalGlobalObject;
class AptValueVector
{
public:
	void ReleaseValues();
};
extern AptValueVector *g_releaseVectorAtE17710;
void Rva006CC110Log(int, const char *, ...);
extern "C" void (__cdecl *g_bfmeAptLogAtE1773C)(const char *,const char *);
struct AptConstantPool { int nItems; AptValue **apItems; };

// Native At/PopNoDec inline bodies preserve the original stack semantics.
// Later _AptBasePtrStack.h (4e14146a35139d6d) is the source lead; retail
// independently supplies the field offsets, assertion text and line numbers.
// MSVC7.1 schedules __debugbreak after argument setup in StackSwap's tail;
// the native assertion requires the original inline int3 compiler barrier.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;

class BfmeAptValue006DCD20 { public: int isString() const; };
class AptBasePtrStack
{
public:
    void rva006E3AA0(int);
    void PopAndPush(int,AptValue *);
    void Push(AptValue *);
    void PushNoInc(AptValue *);
    void rva006FE050(int);
    void rva006FE920();
    __forceinline AptValue *At(int nPos) const
    {
        if (!(count-nPos>0)) {
            g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x10A);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return items[count-nPos-1];
    }
    __forceinline void PopNoDec()
    {
        if (count<=0) {
            g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0xBF);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        } else --count;
    }
    __forceinline void Pop(int n)
    {
        if (count<n) {
            g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping more elements than the stack contains. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0xAA);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        } else {
            for (int i=1;i<=n;++i) items[count-i]->Release();
            count-=n;
        }
    }
    __forceinline void Pop()
    {
        if (count<=0) {
            g_bfmeAptAssertAtE17734("false && \"[APT] Error, Popping from Stack with 0 elements. Please contact the Apt Team for Support.\"", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x98);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        } else {
            items[count-1]->Release();
            --count;
        }
    }
    __forceinline int GetSize() const { return count; }
    AptValue *rva006FE580(int);
    BfmeAptValue006DCD20 *rva007062F0();
    int count,capacity;
    AptValue **items;
};

class AptObject;
class Rva006DB160
{
public:
	void *allocBlock(int);
};
class Rva006DB270
{
public:
	void freeBlock(void *,int);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006FBDB0 : public EAStringC {
public:
    Rva006FBDB0(EAStringC,int,int);
    ~Rva006FBDB0() { context=0; }
    static void *operator new(unsigned int n) { return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n); }
    static void operator delete(void *v,unsigned int n) { g_pChainBlockAllocator->freeBlock(v,n); }
    int context,action;
};
struct AptCallDebugStack {
    int count,capacity; Rva006FBDB0 **items;
    __forceinline void Push(Rva006FBDB0 *v) {
        if(count>=capacity) {
            g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptDebugStack.h",0x6a);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        items[count++]=v;
    }
    __forceinline void Pop() { --count; delete items[count]; items[count]=0; }
};

void __debugbreak();
#pragma intrinsic(__debugbreak)
// WB175A800 names AptValuePtrStack<AptValue>::push (native6E0D60). The
// interpreter's with/this stacks at+0C/+24 are this specialization. Retail
// inlines some member uses and calls others, so both shapes are spelled out;
// the line-0x89 "m_nElements - nPos > 0" assertion is at()'s, which top()
// inlines (out-of-line6DE160 top, 6DCC10 at).
template<class T> struct AptValuePtrStack {
    int count,capacity; T **items;
    void push(T *);
    T *top();
    T *at(int);
    __forceinline void pushInline(T *value) {
        if(!(count<capacity)) {
            g_bfmeAptAssertAtE17734("m_nElements < m_nSize", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x76);
            if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
        }
        items[count]=value; ++count; value->AddRef();
    }
    inline T *topInline() {
        if(count<=0) {
            g_bfmeAptAssertAtE17734("m_nElements - nPos > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x89);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return items[count-1];
    }
    inline void pop() {
        if(count<=0) {
            g_bfmeAptAssertAtE17734("size() > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x7D);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        items[count-1]->Release(); --count;
    }
};

// Original MAP names AptActionSetup; native cleanup reads function name at+8.
struct AptActionSetup { AptValue *context,*value; const char *name; int action; };
void rva007097B0(void *);
void *AptPushStaticData();
struct AptActionInterpreter
{
    struct LocalContextT {
        const unsigned char *pInstruction;
        AptCIH *pCurrentContext;
        AptValue *pCurWith;
        const unsigned char *pRemoveWithAt;
        AptValue *pSuper;
        bool bEncounteredReturn;
        AptCharacterInst *pParentCharacter;
    };
private:
    const char *urlDecode(const char *,EAStringC &,EAStringC &);
public:
    void loadVariables(AptValue *,AptValue *,const EAStringC *);
    static void getName(AptCIH *,EAStringC &);
private:
    struct FunctionTable { int mCheckAlignment; void (__cdecl *mFunctionPointer)(AptActionInterpreter *const,LocalContextT *const); };
    static FunctionTable sGlobalTable[185];
public:
    AptBasePtrStack stack;
    AptValuePtrStack<AptValue> withStack;
    unsigned char m_pad18[0x24-0x18];
    AptValuePtrStack<AptValue> thisStack;
    AptScriptFunctionBase *mpCurrentFunction;
    AptCallDebugStack debugCallStack;
    AptConstantPool constantPool;
    unsigned char m_pad48[0x60-0x48];
    AptValue *mpThrownValue; // PC Throw reads/writes+60; donor supplies semantic role.
    // Original Godfather debug/release field100; native Pop reads +0x64.
    int mnStackFrameBase;
    void *PrepareForExecution(AptActionSetup *);
    void CleanupAfterExecution(void *,AptActionSetup *);
    void callFunction(AptValue *,AptValue *,int);
    bool setVariable(AptValue *, AptValue *, const EAStringC *, AptValue *, int=1, int=1, int=0);
    AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int=1, int=1, int=0);
    const unsigned char *runStream(const unsigned char *,AptCIH *,int,AptCharacterInst *);
    int doFSCommand(const char *,const char *);
    void stackPushIndirect(AptValue *const);
    static bool isObjectOfType(AptValue *,AptValue *);
private:
    void rva007092F0(AptCIH *,AptValue *,AptValue *,AptValue *,int,AptValue *);
    static AptValue *getObject(AptValue *,AptValue *,const EAStringC *);
    static bool getContext(AptValue *,AptValue *,const EAStringC *,AptValue **,EAStringC &);
    AptObject *_createObject(AptValue *,AptValue *,const EAStringC *,int,bool);
    static void _FunctionAptActionStartDragMovie(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionRemoveSprite(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGotoFrame2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCloneSprite(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionSetTarget(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionSetTarget2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCallFrame(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGotoLabel(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGotoFrame(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStopDragMovie(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPlay(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStop(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionNextFrame(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPrevFrame(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushFloat(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushByte(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushWord(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushDWord(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionReturn(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDefineDictionary(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushStringDictByte(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushStringDictWord(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushThis(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushGlobal(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPush0(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPush1(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushTrue(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushFalse(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushUndefined(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushThisVariable(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushGlobalVariable(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushZeroSetVar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushString(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStringDictByteGetVar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStringDictByteGetMember(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushDuplicate(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStackSwap(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStoreRegister(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionAdd(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionSubtract(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionMultiply(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDivide(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionModulo(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionIncrement(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDecrement(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionEquals(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionLessThan(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionAnd(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionOr(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionNot(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionBranchAlways(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionBranchIfTrue(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionBranchIfFalse(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPop(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionNewObject(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionNewMethod(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCallFunction(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCallMethod(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionWith(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCallFuncAndPop(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCallFuncSetVar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCallMethodPop(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCallMethodSetVar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDictCallFuncPop(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDictCallFuncSetVar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDictCallMethodPop(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDictCallMethodSetVar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionToInteger(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStringLength(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGetVariable(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionInitArray(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGetProperty(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionSetProperty(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionInitObject(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStringAdd(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGetTimer(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionTrace(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStrictEquals(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionEquals2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionAdd2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionTargetPath(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCastOp(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionInstanceOf(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionTypeOf(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGreater(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionLessThan2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionSubString(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionAsciiToChar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDelete(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDelete2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStringEquals(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionToNumber(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionToString(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionSetVariable(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGetMember(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionSetMember(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushStringGetVar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushStringGetMember(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushStringSetVar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPushStringSetMember(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionEnd(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionToggleQuality(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionStringLessThan(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionMBLength(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionCharToAscii(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionMBSubString(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionMBCharToAscii(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionMBAsciiToChar(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionBitURShift(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionPush(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionThrow(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionExtends(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGetUrl2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionGetUrl(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionTry(AptActionInterpreter *const,LocalContextT *const);
public:
    static void _FunctionAptActionBitAnd(AptActionInterpreter *const);
private:
public:
    static void _FunctionAptActionBitOr(AptActionInterpreter *const);
private:
public:
    static void _FunctionAptActionBitXor(AptActionInterpreter *const);
private:
public:
    static void _FunctionAptActionBitLShift(AptActionInterpreter *const);
private:
public:
    static void _FunctionAptActionBitRShift(AptActionInterpreter *const);
private:
public:
    static void _FunctionAptActionRandom(AptActionInterpreter *const);
private:
    static void _FunctionAptActionDefineFunction(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDefineFunction2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDefineLocal(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDefineLocal2(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionImplementsOp(AptActionInterpreter *const,LocalContextT *const);
};

typedef char LocalContextSize[sizeof(AptActionInterpreter::LocalContextT)==28 ? 1 : -1];
typedef char ConstantPoolSize[sizeof(AptConstantPool)==8 ? 1 : -1];
// Use the existing byte-verified stack provider's repository spelling.
#pragma comment(linker, "/alternatename:?Push@AptBasePtrStack@@QAEXPAVAptValue@@@Z=?Push@AptBasePtrStack@@QAEXPAVBfmeAptValue006DCD20@@@Z")


// Source headers declare c_string() const; native callers select this exact
// checked-string provider. The global shares the existing four-byte storage.
#pragma comment(linker, "/alternatename:?c_string@AptValue@@QBEPAVAptString@@XZ=?checkedString@BfmeAptValue006DCD20@@QAEPAV1@XZ")










// Each alias binds the independently checked retail provider. GetInt folds
// with the existing four-byte +8 dword getter; no container identity is inferred.





#pragma comment(linker, "/alternatename:?toInteger@AptValue@@QBEHXZ=?toInteger@BfmeAptValue006DCD20@@QBEHXZ")










// GetNumValues shares retail's four-byte +4 getter; the target count field
// is independently established by AptValueVector::ReleaseValues and PopValue.





















#pragma comment(linker, "/alternatename:?isCIH@AptValue@@QBE_N_N@Z=?isCIH@BfmeAptValue006DCD20@@QBE_N_N@Z")




// PC opcode0x34 at table RVA9DC980 loads the same tick cell reset at
// RVA6CD019 and advanced at6CD8B3. Later source calls it gnCurTick; reuse
// the existing address-qualified provider rather than duplicate its storage.
extern int g_rva00891FA0Value;

// With opcode0x94 points to native708B20; original PDB signature and later
// handler source agree. Native assertions retain original spelling and lines.
class BfmeAptValue006DCD20;
void rva007065e0(int,int,BfmeAptValue006DCD20 *,BfmeAptValue006DCD20 **);
__forceinline AptValue *convertWith(AptCIH *aptCIH,AptValue *aptValue) { AptValue *out; rva007065e0((int)aptCIH,0,(BfmeAptValue006DCD20 *)aptValue,(BfmeAptValue006DCD20 **)&out); return out; }



// Play/Stop: opcode6/7 dispatch and original PDB establish handler identity.
// Later source supplies semantics; PC proves CIH+4C and sprite playing bit25+1C.
// Keep direct accessor-expression bitfield assignment: a temporary changes MSVC codegen.
class AptMovie { public: int labelToFrame(const EAStringC *) const; void runFrameActions(AptCIH *,int); };
struct AptCharacter { unsigned char prefix[8]; AptMovie movie; };
class AptDisplayList { public: void removeClonedObject(AptCIH *); };
struct AptSpriteInstBase { unsigned char prefix[0xC]; AptCharacter *character; unsigned char middle[8]; int mnFrame; int mnObjectClipActions:24; unsigned int mbJustLoaded:1; unsigned int mbIsPlaying:1; unsigned int mnIsCustomControl:2; void *clipActions; AptDisplayList displayList; };
class AptCIH : public AptValue {
public:
    unsigned char prefix[0x1C-8];
    float matrixTX,matrixTY;
    unsigned char matrixToParent[0x48-0x24];
    AptCIH *mpDisplayListParent;
    void *mpCharacterInst;
    bool IsLevelInst() const;
    bool IsSpriteInst(bool=false) const;
    bool IsAnimationInst(bool=false) const;
    AptSpriteInstBase *GetSpriteInstBase() const;
    bool IsSpriteInstBase() const;
    bool IsCharacterInst() const;
    __forceinline AptSpriteInstBase *GetCharacterInst() const {
        if (!IsCharacterInst()) {
            g_bfmeAptAssertAtE17734("isCharacterInst()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0xA5);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return (AptSpriteInstBase *)mpCharacterInst;
    }
    void jumpToFrame(int);
    __forceinline AptSpriteInstBase *SpriteBaseInline() const {
        if (!IsSpriteInstBase()) {
            g_bfmeAptAssertAtE17734("isSpriteInstBase()", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7D);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return (AptSpriteInstBase *)mpCharacterInst;
    }
    __forceinline void SetIsPlaying(bool play) {
        GetSpriteInstBase()->mbIsPlaying=play ? 1 : 0;
    }
};
#pragma comment(linker, "/alternatename:?c_cih@AptValue@@QAEPAVAptCIH@@_N@Z=?rva006DCF60@BfmeAptValue006DCD20@@QAEPAV1@_N@Z")


struct AptContextRootState { unsigned char prefix[0x54]; AptValue *head; };
struct AptContextRootDisplay { AptContextRootState *state; };
void __debugbreak();
#pragma intrinsic(__debugbreak)
struct AptIntervalTimer { unsigned int field0; AptValue *callback; float interval,countdown; AptValue *context; AptValuePtrStack<AptValue>params; void cleanParams(); };
class Rva006E34D0 { public: unsigned char prefix[0x30]; AptContextRootDisplay *display; AptIntervalTimer *intervalTimers; int nActiveTimers; unsigned char middle[8]; AptValue *mpDragMC; float a,b,c,d,tx,ty; unsigned char toMouse[0x74-0x60]; int mouseX,mouseY; unsigned char beforeMax[0xa8-0x7c]; int maxIntervalTimers; };
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;



class BfmeAptValue006DCD20;
void rva007065e0(int,int,BfmeAptValue006DCD20 *,BfmeAptValue006DCD20 **);
// Native indexed22-entry StringCode table, exactly the88 bytes at DDC928.
// Later gaszPropertyNames supplies semantic order; retain address-qualified storage.
extern int g_aptPropertyCodesAtDDC928[22];

// The original AptValue header supplies bool predicates and const checked casts.
// Lookup/Register headers c6dc857ff8e1760a/95fdc6cae0bddecc name these integer
// payloads. PC independently reads +8 after checked casts; only prefixes used.
class AptLookup : public AptValue { public: int nLookup; };
class AptRegister : public AptValue { public: int nVal; };
AptValue *Rva00709EC0Get(int);





class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table { public: void add(Rva8D0D80String *,Rva8D0D80Value *); };
void AptActionInterpreter::_FunctionAptActionInitObject(AptActionInterpreter *const aptActionInterpreter, LocalContextT *const localContextT)
{
    int n=static_cast<const AptBasePtrStack &>(aptActionInterpreter->stack).At(0)->toInteger();
    aptActionInterpreter->stack.Pop();
    AptValue *object=(AptValue *)aptActionInterpreter->_createObject((AptValue *)localContextT->pCurrentContext,localContextT->pCurWith,Rva0070B4F0GetString(0x64),0,true);
    if(object) {
        for(int i=0,reg=0;i<n;++i,reg+=2) {
            AptValue *value=static_cast<const AptBasePtrStack &>(aptActionInterpreter->stack).At(reg);
            AptValue *name=static_cast<const AptBasePtrStack &>(aptActionInterpreter->stack).At(reg+1);
            EAStringC text;name->toString(text);
            ((Rva8D0D80Table *)((char *)object+8))->add((Rva8D0D80String *)&text,(Rva8D0D80Value *)value);
        }
        aptActionInterpreter->stack.rva006E3AA0(2*n);
        aptActionInterpreter->stack.Push(object);object->Release();
    } else {aptActionInterpreter->stack.rva006FE050(2*n);aptActionInterpreter->stack.Push(gpUndefinedValue);}
}

// Native static helper uses pB in EBX and pA on the stack. MSVC chooses
// that internal ABI from real C++; branch-local destination binding retains
// the native predicate/member-address ordering (objects seat scheduling fix).
static AptString *_concatAsStrings(AptValue *aptValue,AptValue *b)
{
    AptString *result=AptString::Create();
    EAStringC *str;
    if((unsigned char)((BfmeAptValue006DCD20 *)b)->isString()) {str=result->GetInternalString(); *str=*b->c_string()->GetInternalString();}
    else {str=result->GetInternalString(); b->toString(*str); }
    if((unsigned char)((BfmeAptValue006DCD20 *)aptValue)->isString()) str->Rva006D4F00Append(*aptValue->c_string()->GetInternalString());
    else {EAStringC text;aptValue->toString(text);str->Rva006D4F00Append(text);}
    return result;
}



void AptActionInterpreter::_FunctionAptActionNewObject(AptActionInterpreter *const aptActionInterpreter,LocalContextT *const localContextT)
{
    AptValue *name=static_cast<const AptBasePtrStack &>(aptActionInterpreter->stack).At(0);
    AptValue *params=static_cast<const AptBasePtrStack &>(aptActionInterpreter->stack).At(1);
    EAStringC objectName;
    name->toString(objectName);
    int nParams=params->toInteger();
    aptActionInterpreter->stack.Pop(2);
    AptValue *object=(AptValue *)aptActionInterpreter->_createObject((AptValue *)localContextT->pCurrentContext,localContextT->pCurWith,&objectName,nParams,true);
    if(object) { aptActionInterpreter->stack.Push(object); object->Release(); }
    else aptActionInterpreter->stack.Push(gpUndefinedValue);
}

void AptActionInterpreter::_FunctionAptActionNewMethod(AptActionInterpreter *const aptActionInterpreter,LocalContextT *const localContextT)
{
    AptValue *name=static_cast<const AptBasePtrStack &>(aptActionInterpreter->stack).At(0);
    AptValue *context=static_cast<const AptBasePtrStack &>(aptActionInterpreter->stack).At(1);
    AptValue *params=static_cast<const AptBasePtrStack &>(aptActionInterpreter->stack).At(2);
    EAStringC objectName;
    name->toString(objectName);
    int nParams=params->toInteger();
    aptActionInterpreter->stack.Pop();
    aptActionInterpreter->stack.PopNoDec();
    aptActionInterpreter->stack.Pop();
    AptValue *object=(AptValue *)aptActionInterpreter->_createObject(context,localContextT->pCurWith,&objectName,nParams,true);
    context->Release();
    if(object) { aptActionInterpreter->stack.Push(object); object->Release(); }
    else aptActionInterpreter->stack.Push(gpUndefinedValue);
}

class AptNativeHash { public: void Set(const EAStringC *const,AptValue *const); int mnTotalSize; void *mpData; AptValue *mp__proto__; AptValue *mpPrototype; unsigned int nEventHandlers; __forceinline AptValue *Get__Proto__() const { return mp__proto__; } __forceinline AptValue *GetPrototype() const { return mpPrototype; } __forceinline void SetPrototype(AptValue *p) { if(p) p->AddRef(); if(mpPrototype) mpPrototype->Release(); mpPrototype=p; } __forceinline void Set__Proto__(AptValue *p) { if(p) p->AddRef(); if(mp__proto__) mp__proto__->Release(); mp__proto__=p; } };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
// Accessed AptPrototype prefix: AptValue8 + native hash20 + constructor pointer.
class AptPrototype : public AptValue {
    AptNativeHash mNativeHash;
    AptValue *mp__constructor__;
public:
    AptPrototype();
    static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); }
    static void operator delete(void *,unsigned int);
    __forceinline AptValue *GetSuperConstructor() const { return mp__constructor__; }
    __forceinline void SetSuperConstructor(AptValue *aptValue) { AptValue *old=mp__constructor__; mp__constructor__=aptValue; aptValue->AddRef(); if(old) old->Release(); }
};



// PC prefix slotDDC920 points to FSCommand:; callback E17758 is zero-initialized.
// Original Apt.h callback declaration and native caller establish void cdecl ABI.
#pragma intrinsic(strlen)
extern const char *g_bfmeAptFSCommandAtDDC920;
extern void (__cdecl *g_bfmeAptCommandAtE17758)(const char *,const char *);


// Rehomed from Rva007065E0Cluster.cpp. Preserve its address-named ABI and
// verified121B body. Visibility lets MSVC prove the output cell does not escape;
// TargetPath then reuses the dead incoming argument slot as retail does.
class BfmeAptValue006DCD20;
BfmeAptValue006DCD20 *rva007064f0(int,int,EAStringC *);
__declspec(noinline) void rva007065e0(int a,int b,BfmeAptValue006DCD20 *value,BfmeAptValue006DCD20 **out);

void rva006ffce0(AptValue *,EAStringC &);



#pragma intrinsic(strcpy)
__declspec(noinline) unsigned char rva006FD100(int current,int with,EAStringC *var,int *out,char *name);

__declspec(noinline) unsigned char rva006FEC00(int value, int allowEmpty, EAStringC *src,
	int *resultSlot, EAStringC *outString);
class AptObject : public AptValue { public: bool DoesImplementObject(AptValue *) const; };




// Native 6FDA40..6FDC29; buffer capacity260 inferred from frame allocation,
// exact declared source bound within alignment padding is not independently known.
// Load6D1F80 has native-supported original MAP ABI but remains a link backlog.
#pragma intrinsic(strcpy)
static __forceinline bool bfmeIsFSCommand(const char *s) { return strncmp(s,g_bfmeAptFSCommandAtDDC920,strlen(g_bfmeAptFSCommandAtDDC920))==0; }
class AptLinker { public: void Load(const EAStringC &,EAStringC); };
extern AptLinker *g_bfmeAptLinkerAtE176F8;




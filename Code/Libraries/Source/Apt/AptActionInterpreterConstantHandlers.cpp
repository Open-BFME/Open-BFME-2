class AptCIH;
// cl: /O2 /MD /EHsc
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
// Preserve fmodf's float argument rounding before the MSVC _CIfmod intrinsic.
// Native Modulo spills its second conversion to a float slot before the call.
extern "C" double __cdecl fmod(double,double);
#pragma intrinsic(fmod)
// Native equality threshold is double0.001 at VA BC6E68, not the later float macro.
extern "C" int __cdecl strcmp(const char *,const char *);
#pragma intrinsic(strcmp)
extern "C" double __cdecl fabs(double);
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
    bool isString() const;
    void SetString(const char *);
    float toFloat() const;
    bool toBool() const;
    int toInteger() const;
    void toString(EAStringC &) const;
};
struct AptCharacterInst;
class EAStringC { void *mpData; public: EAStringC &TrimRight(const char *); EAStringC &Rva006D4F00Append(const EAStringC &); EAStringC &Rva006D50A0Append(const char *); EAStringC(unsigned int,unsigned int); EAStringC rva006D5ED0(int) const; EAStringC rva006d5f30(int,int) const; void rva006D3470(); int Find(char,int=0); EAStringC &Append(const char *const,unsigned int); bool IsEmpty() const; bool IsEqualTo(const EAStringC *) const; bool rva006D3560(const EAStringC *) const; const char *rva00620090() const; int rva006d6070(const char *,int=0); EAStringC(); unsigned int rva006D3750() const; EAStringC(const char *); EAStringC(const EAStringC &); int GetAt(int) const; int rva006D54B0(int,int); ~EAStringC(); EAStringC &operator=(const EAStringC &); };
class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *,int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
// Native InitArray allocates44B; ctor6D91B0 builds type0x16, hash+8,
// AptArray vtableCEA778 and slots+20/+24/+28. Unaccessed state stays opaque.
class AptArray : public AptValue { char m_arrayState[36]; public: AptArray(); static void *operator new(unsigned int n) { return g_pChainBlockAllocatorF4->allocBlock(n); } static void operator delete(void *p,unsigned int n) { g_pChainBlockAllocatorF4->freeBlock(p,n); } AptValue *get(int); void set(int,AptValue *); };
// PC callbacks occupy two independently zero-initialized slots in gAptFuncs.
// Member handlers establish the getter/setter ABI; later source names their role.
AptValue *(__cdecl *g_bfmeAptGetExternAtE17768)(const char *)=0;
void (__cdecl *g_bfmeAptSetExternAtE17764)(const char *,const char *)=0;
class AptString : public AptValue { public: static AptString *Create(); EAStringC str; __forceinline EAStringC *GetInternalString() { return &str; } };
class AptInteger : public AptValue { public: static AptValue *Create(int); int GetInt() const; };
int Rva006CD220Get();
bool rva006fc370(AptValue *);
class AptBoolean { public: static AptValue *Create(bool); };
AptValue *Rva008A4EA0MakeFloat(float);
EAStringC *Rva0070B4F0GetString(int);
extern EAStringC g_eaStringAtE177D4;
extern AptValue *gpUndefinedValue;
extern AptValue *gpGlobalGlobalObject;
class AptValueVector { public: int GetNumValues() const; void ReleaseValues(); };
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
void Rva00709F70Set(int, AptValue *);
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
    int count,capacity;
    AptValue **items;
};

class AptObject;
class Rva006DB160 { public: void *allocBlock(int); };
class Rva006DB270 { public: void freeBlock(void *,int); };
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006FBDB0 : public EAStringC {
public:
    Rva006FBDB0(EAStringC,int,int);
    ~Rva006FBDB0() { context=0; }
    static void *operator new(unsigned int n) { return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n); }
    static void operator delete(void *v) { g_pChainBlockAllocator->freeBlock(v,12); }
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

// Original MAP names AptActionSetup; native cleanup reads function name at+8.
struct AptActionSetup { AptValue *context,*value; const char *name; int action; };
void rva007097B0(void *);
void *AptPushStaticData();
#pragma comment(linker, "/alternatename:?AptPushStaticData@@YAPAXXZ=?PushStaticData@AptScriptFunctionBase@@SAPAXXZ")
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
    unsigned char m_otherStacksAndDebugData[0x24-12];
    struct { int count,capacity; AptValue **items; } thisStack;
    AptScriptFunctionBase *mpCurrentFunction;
    AptCallDebugStack debugCallStack;
    AptConstantPool constantPool;
    unsigned char m_betweenPoolAndFrameBase[0x60-0x48];
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
#define HANDLER(n) static void _FunctionAptAction##n(AptActionInterpreter *const,LocalContextT *const)
    HANDLER(StartDragMovie); HANDLER(RemoveSprite); HANDLER(GotoFrame2); HANDLER(CloneSprite); HANDLER(SetTarget); HANDLER(SetTarget2); HANDLER(CallFrame); HANDLER(GotoLabel); HANDLER(GotoFrame); HANDLER(StopDragMovie); HANDLER(Play); HANDLER(Stop); HANDLER(NextFrame); HANDLER(PrevFrame);
    HANDLER(PushFloat); HANDLER(PushByte); HANDLER(PushWord); HANDLER(PushDWord);
    HANDLER(Return); HANDLER(DefineDictionary); HANDLER(PushStringDictByte); HANDLER(PushStringDictWord);
    HANDLER(PushThis); HANDLER(PushGlobal); HANDLER(Push0); HANDLER(Push1);
    HANDLER(PushTrue); HANDLER(PushFalse); HANDLER(PushUndefined);
    HANDLER(PushThisVariable); HANDLER(PushGlobalVariable); HANDLER(PushZeroSetVar);
    HANDLER(PushString); HANDLER(StringDictByteGetVar); HANDLER(StringDictByteGetMember);
    HANDLER(PushDuplicate); HANDLER(StackSwap); HANDLER(StoreRegister);
    HANDLER(Add); HANDLER(Subtract); HANDLER(Multiply);
    HANDLER(Divide); HANDLER(Modulo); HANDLER(Increment); HANDLER(Decrement);
    HANDLER(Equals); HANDLER(LessThan); HANDLER(And); HANDLER(Or); HANDLER(Not);
    HANDLER(BranchAlways); HANDLER(BranchIfTrue); HANDLER(BranchIfFalse); HANDLER(Pop);
    HANDLER(NewObject); HANDLER(NewMethod);
    HANDLER(CallFunction); HANDLER(CallMethod); HANDLER(With);
    HANDLER(CallFuncAndPop); HANDLER(CallFuncSetVar); HANDLER(CallMethodPop); HANDLER(CallMethodSetVar); HANDLER(DictCallFuncPop); HANDLER(DictCallFuncSetVar); HANDLER(DictCallMethodPop); HANDLER(DictCallMethodSetVar);
    HANDLER(ToInteger); HANDLER(StringLength); HANDLER(GetVariable);
    HANDLER(InitArray);
    HANDLER(GetProperty); HANDLER(SetProperty);
    HANDLER(InitObject);
    HANDLER(StringAdd);
    HANDLER(GetTimer);
    HANDLER(Trace);
    HANDLER(StrictEquals);
    HANDLER(Equals2);
    HANDLER(Add2);
    HANDLER(TargetPath);
    HANDLER(CastOp);
    HANDLER(InstanceOf);
    HANDLER(TypeOf);
    HANDLER(Greater); HANDLER(LessThan2);
    HANDLER(SubString); HANDLER(AsciiToChar);
    HANDLER(Delete); HANDLER(Delete2);
    HANDLER(StringEquals);
    HANDLER(ToNumber); HANDLER(ToString);
    HANDLER(SetVariable); HANDLER(GetMember); HANDLER(SetMember);
    HANDLER(PushStringGetVar); HANDLER(PushStringGetMember); HANDLER(PushStringSetVar); HANDLER(PushStringSetMember);
    HANDLER(End); HANDLER(ToggleQuality); HANDLER(StringLessThan); HANDLER(MBLength); HANDLER(CharToAscii); HANDLER(MBSubString); HANDLER(MBCharToAscii); HANDLER(MBAsciiToChar); HANDLER(BitURShift);
    HANDLER(Push);
    HANDLER(Throw);
    HANDLER(Extends);
    HANDLER(GetUrl2); HANDLER(GetUrl); HANDLER(Try);
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
    HANDLER(DefineFunction);
    HANDLER(DefineFunction2);
    HANDLER(DefineLocal);
    HANDLER(DefineLocal2);
    HANDLER(ImplementsOp);
#undef HANDLER
};
void AptActionInterpreter::_FunctionAptActionPushFloat(AptActionInterpreter *const p, LocalContextT *const c)
{
    const unsigned char *i=c->pInstruction;
    union { float value; struct { char c0,c1,c2,c3; } bytes; } v;
    v.bytes.c0=*i++;v.bytes.c1=*i++;v.bytes.c2=*i++;v.bytes.c3=*i++;
    c->pInstruction=i;
    p->stack.Push(Rva008A4EA0MakeFloat(v.value));
}
void AptActionInterpreter::_FunctionAptActionPushByte(AptActionInterpreter *const p, LocalContextT *const c)
{
    signed char value=*c->pInstruction++;
    p->stack.Push(AptInteger::Create(value));
}
void AptActionInterpreter::_FunctionAptActionPushWord(AptActionInterpreter *const p, LocalContextT *const c)
{
    const unsigned char *i=c->pInstruction;
    union { short value; struct { unsigned char c0,c1; } bytes; } v;
    v.bytes.c0=*i++;v.bytes.c1=*i++;
    c->pInstruction=i;
    p->stack.Push(AptInteger::Create(v.value));
}
void AptActionInterpreter::_FunctionAptActionPushDWord(AptActionInterpreter *const p, LocalContextT *const c)
{
    const unsigned char *i=c->pInstruction;
    volatile union { int value; struct { unsigned char c0,c1,c2,c3; } bytes; } v;
    v.bytes.c0=*i++;v.bytes.c1=*i++;v.bytes.c2=*i++;v.bytes.c3=*i++;
    c->pInstruction=i;
    p->stack.Push(AptInteger::Create(v.value));
}
void AptActionInterpreter::_FunctionAptActionReturn(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->bEncounteredReturn=true;
}
void AptActionInterpreter::_FunctionAptActionDefineDictionary(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const AptConstantPool *data=(const AptConstantPool *)c->pInstruction;
    c->pInstruction+=sizeof(AptConstantPool);
    p->constantPool=*data;
}
void AptActionInterpreter::_FunctionAptActionPushStringDictByte(AptActionInterpreter *const p, LocalContextT *const c)
{
    unsigned char index=*c->pInstruction++;
    p->stack.Push(p->constantPool.apItems[index]);
}
void AptActionInterpreter::_FunctionAptActionPushStringDictWord(AptActionInterpreter *const p, LocalContextT *const c)
{
    const unsigned char *i=c->pInstruction;
    union { unsigned short index; struct { char c0,c1; } bytes; } v;
    v.bytes.c0=*i++;v.bytes.c1=*i++;
    c->pInstruction=i;
    p->stack.Push(p->constantPool.apItems[v.index]);
}
void AptActionInterpreter::_FunctionAptActionPushThis(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptString *s=AptString::Create();
    s->str=*Rva0070B4F0GetString(0xA4);
    p->stack.Push(s);
}
void AptActionInterpreter::_FunctionAptActionPushGlobal(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptString *s=AptString::Create();
    s->str=*Rva0070B4F0GetString(7);
    p->stack.Push(s);
}
void AptActionInterpreter::_FunctionAptActionPush0(AptActionInterpreter *const p, LocalContextT *const c) { p->stack.Push(AptInteger::Create(0)); }
void AptActionInterpreter::_FunctionAptActionPush1(AptActionInterpreter *const p, LocalContextT *const c) { p->stack.Push(AptInteger::Create(1)); }
void AptActionInterpreter::_FunctionAptActionPushTrue(AptActionInterpreter *const p, LocalContextT *const c) { p->stack.Push(AptBoolean::Create(true)); }
void AptActionInterpreter::_FunctionAptActionPushFalse(AptActionInterpreter *const p, LocalContextT *const c) { p->stack.Push(AptBoolean::Create(false)); }
void AptActionInterpreter::_FunctionAptActionPushUndefined(AptActionInterpreter *const p, LocalContextT *const c) { p->stack.Push(gpUndefinedValue); }

typedef char LocalContextSize[sizeof(AptActionInterpreter::LocalContextT)==28 ? 1 : -1];
typedef char ConstantPoolSize[sizeof(AptConstantPool)==8 ? 1 : -1];
// Use the existing byte-verified stack provider's repository spelling.
#pragma comment(linker, "/alternatename:?Push@AptBasePtrStack@@QAEXPAVAptValue@@@Z=?Push@AptBasePtrStack@@QAEXPAVBfmeAptValue006DCD20@@@Z")

void AptActionInterpreter::_FunctionAptActionPushThisVariable(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *v=p->getVariable((AptValue *)c->pCurrentContext,c->pCurWith,Rva0070B4F0GetString(0xA4),1);
    p->stack.Push(v);
}
void AptActionInterpreter::_FunctionAptActionPushGlobalVariable(AptActionInterpreter *const p, LocalContextT *const c)
{
    p->stack.Push(gpGlobalGlobalObject);
}
void AptActionInterpreter::_FunctionAptActionPushZeroSetVar(AptActionInterpreter *const p, LocalContextT *const c)
{
    p->stack.Push(AptInteger::Create(0));
    _FunctionAptActionSetVariable(p,c);
}
void AptActionInterpreter::_FunctionAptActionPushString(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const char *const *data=(const char *const *)c->pInstruction;
    c->pInstruction+=4;
    AptString *s=AptString::Create();
    s->str=*data;
    p->stack.Push(s);
}
void AptActionInterpreter::_FunctionAptActionStringDictByteGetVar(AptActionInterpreter *const p, LocalContextT *const c)
{
    unsigned char index=*c->pInstruction++;
    AptValue *s=p->constantPool.apItems[index];
    EAStringC *name=&s->c_string()->str;
    AptValue *v=p->getVariable((AptValue *)c->pCurrentContext,c->pCurWith,name,1);
    p->stack.Push(v);
}
void AptActionInterpreter::_FunctionAptActionStringDictByteGetMember(AptActionInterpreter *const p, LocalContextT *const c)
{
    unsigned char index=*c->pInstruction++;
    p->stack.Push(p->constantPool.apItems[index]);
    _FunctionAptActionGetMember(p,c);
}

// Source headers declare c_string() const; native callers select this exact
// checked-string provider. The global shares the existing four-byte storage.
#pragma comment(linker, "/alternatename:?c_string@AptValue@@QBEPAVAptString@@XZ=?checkedString@BfmeAptValue006DCD20@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:?gpGlobalGlobalObject@@3PAVAptValue@@A=?g_00E18650@@3VEAStringC@@A")

void AptActionInterpreter::_FunctionAptActionPushStringGetVar(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const char *const *data=(const char *const *)c->pInstruction;
    c->pInstruction+=4;
    g_eaStringAtE177D4=*data;
    AptValue *v=p->getVariable((AptValue *)c->pCurrentContext,c->pCurWith,&g_eaStringAtE177D4,1);
    p->stack.Push(v);
}

void AptActionInterpreter::_FunctionAptActionPushStringGetMember(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const char *const *data=(const char *const *)c->pInstruction;
    c->pInstruction+=4;
    AptString *s=AptString::Create();
    s->str=*data;
    p->stack.Push(s);
    _FunctionAptActionGetMember(p,c);
}

void AptActionInterpreter::_FunctionAptActionPushStringSetVar(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const char *const *data=(const char *const *)c->pInstruction;
    c->pInstruction+=4;
    AptString *s=AptString::Create();
    s->str=*data;
    p->stack.Push(s);
    _FunctionAptActionSetVariable(p,c);
}

void AptActionInterpreter::_FunctionAptActionPushStringSetMember(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const char *const *data=(const char *const *)c->pInstruction;
    c->pInstruction+=4;
    AptString *s=AptString::Create();
    s->str=*data;
    p->stack.Push(s);
    _FunctionAptActionSetMember(p,c);
}

void AptActionInterpreter::_FunctionAptActionPushDuplicate(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *v=p->stack.At(0);
    p->stack.Push(v);
}
void AptActionInterpreter::_FunctionAptActionStackSwap(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *a=p->stack.At(0);
    AptValue *b=p->stack.At(1);
    p->stack.PopNoDec();
    p->stack.PopNoDec();
    p->stack.PushNoInc(a);
    p->stack.PushNoInc(b);
}
void AptActionInterpreter::_FunctionAptActionStoreRegister(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const int *data=(const int *)c->pInstruction;
    c->pInstruction+=4;
    Rva00709F70Set(*data,p->stack.At(0));
}

#pragma comment(linker, "/alternatename:?PushNoInc@AptBasePtrStack@@QAEXPAVAptValue@@@Z=?rva006FE7B0@AptBasePtrStack@@QAEXPAVBfmeAptValue006DCD20@@@Z")

void AptActionInterpreter::_FunctionAptActionAdd(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (aValue->isInteger() && bValue->isInteger()) {
            int a=aValue->c_integer()->GetInt();
            int b=bValue->c_integer()->GetInt();
            result=AptInteger::Create(a+b);
        } else {
            float a=aValue->toFloat();
            float b=bValue->toFloat();
            result=Rva008A4EA0MakeFloat(a+b);
        }
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionSubtract(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (aValue->isInteger() && bValue->isInteger()) {
            int a=aValue->c_integer()->GetInt();
            int b=bValue->c_integer()->GetInt();
            result=AptInteger::Create(b-a);
        } else {
            float a=aValue->toFloat();
            float b=bValue->toFloat();
            result=Rva008A4EA0MakeFloat(b-a);
        }
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionMultiply(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (aValue->isInteger() && bValue->isInteger()) {
            int a=aValue->c_integer()->GetInt();
            int b=bValue->c_integer()->GetInt();
            result=AptInteger::Create(a*b);
        } else {
            float a=aValue->toFloat();
            float b=bValue->toFloat();
            result=Rva008A4EA0MakeFloat(a*b);
        }
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

// Each alias binds the independently checked retail provider. GetInt folds
// with the existing four-byte +8 dword getter; no container identity is inferred.
#pragma comment(linker, "/alternatename:?isUndefined@AptValue@@QBE_NXZ=?isUndefined@BfmeAptValue006DCD20@@QBE_NXZ")
#pragma comment(linker, "/alternatename:?isInteger@AptValue@@QBE_NXZ=?isInteger@BfmeAptValue006DCD20@@QBEHXZ")
#pragma comment(linker, "/alternatename:?c_integer@AptValue@@QBEPAVAptInteger@@XZ=?checkedInteger@BfmeAptValue006DCD20@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:?toFloat@AptValue@@QBEMXZ=?rva006DD460@BfmeAptValue006DCD20@@QAEMXZ")
#pragma comment(linker, "/alternatename:?GetInt@AptInteger@@QBEHXZ=?Length@?$SimpleVecClass@K@@QBEHXZ")

void AptActionInterpreter::_FunctionAptActionDivide(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        float a=aValue->toFloat();
        float b=bValue->toFloat();
        if (a==0.f) result=gpUndefinedValue;
        else result=Rva008A4EA0MakeFloat(b/a);
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionModulo(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        float a=aValue->toFloat();
        if (a==0.f) result=gpUndefinedValue;
        else result=Rva008A4EA0MakeFloat(bfme_fmodf(bValue->toFloat(),a));
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionIncrement(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (value->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (value->isInteger()) result=AptInteger::Create(value->toInteger()+1);
        else result=Rva008A4EA0MakeFloat(value->toFloat()+1.f);
    }
    p->stack.Pop();
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionDecrement(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (value->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (value->isInteger()) result=AptInteger::Create(value->toInteger()-1);
        else result=Rva008A4EA0MakeFloat(value->toFloat()-1.f);
    }
    p->stack.Pop();
    p->stack.Push(result);
}

#pragma comment(linker, "/alternatename:?toInteger@AptValue@@QBEHXZ=?toInteger@BfmeAptValue006DCD20@@QBEHXZ")

void AptActionInterpreter::_FunctionAptActionEquals(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (aValue->isInteger() && bValue->isInteger()) {
            int a=aValue->c_integer()->GetInt();
            int b=bValue->c_integer()->GetInt();
            result=AptBoolean::Create(a==b);
        } else {
            float a=aValue->toFloat();
            float b=bValue->toFloat();
            result=AptBoolean::Create(fabs(a-b)<0.001);
        }
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionLessThan(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (aValue->isInteger() && bValue->isInteger()) {
            int a=aValue->c_integer()->GetInt();
            int b=bValue->c_integer()->GetInt();
            result=AptBoolean::Create(b<a);
        } else {
            float a=aValue->toFloat();
            float b=bValue->toFloat();
            result=AptBoolean::Create(b<a);
        }
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionAnd(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (aValue->isInteger() && bValue->isInteger()) {
            int a=aValue->c_integer()->GetInt();
            int b=bValue->c_integer()->GetInt();
            result=AptBoolean::Create(a && b);
        } else {
            float a=aValue->toFloat();
            float b=bValue->toFloat();
            result=AptBoolean::Create((a!=0.f && b!=0.f) ? true : false);
        }
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionOr(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *aValue=p->stack.At(0);
    AptValue *bValue=p->stack.At(1);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (aValue->isUndefined() || bValue->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) {
        if (aValue->isInteger() && bValue->isInteger()) {
            int a=aValue->c_integer()->GetInt();
            int b=bValue->c_integer()->GetInt();
            result=AptBoolean::Create(a || b);
        } else {
            float a=aValue->toFloat();
            float b=bValue->toFloat();
            result=AptBoolean::Create((a!=0.f || b!=0.f) ? true : false);
        }
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionNot(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    AptValue *result=AptBoolean::Create(!value->toBool());
    p->stack.Pop();
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionBranchAlways(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const int *data=(const int *)c->pInstruction;
    c->pInstruction+=4;
    c->pInstruction+=*data;
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionBranchIfTrue(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const int *data=(const int *)c->pInstruction;
    c->pInstruction+=4;
    AptValue *condition=p->stack.At(0);
    if (condition->toBool()==true) c->pInstruction+=*data;
    p->stack.Pop();
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionBranchIfFalse(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const int *data=(const int *)c->pInstruction;
    c->pInstruction+=4;
    AptValue *condition=p->stack.At(0);
    if (condition->toBool()==false) c->pInstruction+=*data;
    p->stack.Pop();
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionPop(AptActionInterpreter *const p, LocalContextT *const c)
{
    int stackElements=p->stack.count;
    if (stackElements<=p->mnStackFrameBase)
        Rva006CC110Log(3,"--Warning-- Actionscript Popping when no items are in stack!\n");
    if (stackElements>p->mnStackFrameBase) p->stack.Pop();
    if (stackElements==1) {
        if (g_releaseVectorAtE17710->GetNumValues()!=0)
            g_releaseVectorAtE17710->ReleaseValues();
    }
}

// GetNumValues shares retail's four-byte +4 getter; the target count field
// is independently established by AptValueVector::ReleaseValues and PopValue.
#pragma comment(linker, "/alternatename:?GetNumValues@AptValueVector@@QBEHXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")

void AptActionInterpreter::_FunctionAptActionCallFuncAndPop(AptActionInterpreter *const p, LocalContextT *const c)
{
    _FunctionAptActionCallFunction(p,c);
    p->stack.Pop();
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionCallFuncSetVar(AptActionInterpreter *const p, LocalContextT *const c)
{
    _FunctionAptActionCallFunction(p,c);
    _FunctionAptActionSetVariable(p,c);
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionCallMethodPop(AptActionInterpreter *const p, LocalContextT *const c)
{
    _FunctionAptActionCallMethod(p,c);
    p->stack.Pop();
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionCallMethodSetVar(AptActionInterpreter *const p, LocalContextT *const c)
{
    _FunctionAptActionCallMethod(p,c);
    _FunctionAptActionSetVariable(p,c);
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

// Native dictionary-call handlers advance the instruction pointer before the
// call. Later source advances afterward; keep the independently verified order.
void AptActionInterpreter::_FunctionAptActionDictCallFuncPop(AptActionInterpreter *const p, LocalContextT *const c)
{
    unsigned char index=*c->pInstruction++;
    p->stack.Push(p->constantPool.apItems[index]);
    _FunctionAptActionCallFunction(p,c);
    p->stack.Pop();
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionDictCallFuncSetVar(AptActionInterpreter *const p, LocalContextT *const c)
{
    unsigned char index=*c->pInstruction++;
    p->stack.Push(p->constantPool.apItems[index]);
    _FunctionAptActionCallFunction(p,c);
    _FunctionAptActionSetVariable(p,c);
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionDictCallMethodPop(AptActionInterpreter *const p, LocalContextT *const c)
{
    unsigned char index=*c->pInstruction++;
    p->stack.Push(p->constantPool.apItems[index]);
    _FunctionAptActionCallMethod(p,c);
    p->stack.Pop();
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionDictCallMethodSetVar(AptActionInterpreter *const p, LocalContextT *const c)
{
    unsigned char index=*c->pInstruction++;
    p->stack.Push(p->constantPool.apItems[index]);
    _FunctionAptActionCallMethod(p,c);
    _FunctionAptActionSetVariable(p,c);
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionToInteger(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    AptValue *result=0;
    if (Rva006CD220Get()==7) {
        if (value->isUndefined()) result=gpUndefinedValue;
    }
    if (!result) result=AptInteger::Create(value->toInteger());
    p->stack.Pop();
    p->stack.Push(result);
}
void AptActionInterpreter::_FunctionAptActionStringLength(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    EAStringC text;
    value->toString(text);
    AptValue *result=AptInteger::Create(text.rva006D3750());
    p->stack.Pop(1);
    p->stack.Push(result);
}
void AptActionInterpreter::_FunctionAptActionGetVariable(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *name=p->stack.At(0);
    if (!name->isUndefined()) {
        EAStringC text;
        name->toString(text);
        AptValue *value=p->getVariable((AptValue *)c->pCurrentContext,c->pCurWith,&text,1);
        p->stack.Pop();
        p->stack.Push(value);
    }
}

// The native ToNumber shares the source's early return for SWF7 undefined;
// retaining that branch also preserves its final argument-setup scheduling.
void AptActionInterpreter::_FunctionAptActionToNumber(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    if (!value->isFloat() && !value->isInteger()) {
        AptValue *result=gpUndefinedValue;
        if (!rva006fc370(value)) {
            if (Rva006CD220Get()==7 && value->isUndefined()) {
                p->stack.rva006FE920();
                p->stack.Push(result);
                return;
            }
            EAStringC text;
            value->toString(text);
            int place=text.rva006d6070(".");
            if (place!=-1 && place!=text.rva006D3750()) result=Rva008A4EA0MakeFloat(value->toFloat());
            else result=AptInteger::Create(value->toInteger());
        }
        p->stack.rva006FE920();
        p->stack.Push(result);
    }
}
// Native ToString handles SWF7 undefined through pooled text ID A9; the later
// implementation uses Append_ToString. Preserve the native scoped temporary
// and original SetString path, both independently visible in PC calls.
void AptActionInterpreter::_FunctionAptActionToString(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    if (!value->isString()) {
        if (Rva006CD220Get()==7 && value->isUndefined()) {
            AptString *str=AptString::Create();
            str->SetString(Rva0070B4F0GetString(0xA9)->rva00620090());
            p->stack.rva006FE920();
            p->stack.Push(str);
            return;
        }
        EAStringC text;
        value->toString(text);
        p->stack.Pop();
        AptString *str=AptString::Create();
        str->str=text;
        p->stack.Push(str);
    }
}
void AptActionInterpreter::_FunctionAptActionSetVariable(AptActionInterpreter *const p, LocalContextT *const c)
{
    EAStringC text;
    AptValue *value=p->stack.At(0);
    AptValue *name=p->stack.At(1);
    name->toString(text);
    p->setVariable((AptValue *)c->pCurrentContext,c->pCurWith,&text,value,1);
    p->stack.Pop(2);
    if (g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0)
        g_releaseVectorAtE17710->ReleaseValues();
}

#pragma comment(linker, "/alternatename:?isFloat@AptValue@@QBE_NXZ=?isFloat@BfmeAptValue006DCD20@@QBEHXZ")
#pragma comment(linker, "/alternatename:?isString@AptValue@@QBE_NXZ=?isString@BfmeAptValue006DCD20@@QBEHXZ")

// PC equality uses two scoped native strings and retains nResult until the
// Boolean factory; IsEqualTo is the existing provider for the source equality.
void AptActionInterpreter::_FunctionAptActionStringEquals(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *a=p->stack.At(0);
    AptValue *b=p->stack.At(1);
    AptValue *result=0;
    int nResult=0;
    if (Rva006CD220Get()==7) {
        if(a->isUndefined()) ++nResult;
        if(b->isUndefined()) ++nResult;
        switch(nResult) {
        case 1: result=gpUndefinedValue; break;
        case 2: result=AptBoolean::Create(true); break;
        }
    }
    if(!result) {
        EAStringC as,bs;
        a->toString(as);
        b->toString(bs);
        if(as.IsEqualTo(&bs)) nResult=1;
        result=AptBoolean::Create(nResult!=0);
    }
    p->stack.Pop(2);
    p->stack.Push(result);
}

// The native Delete passes bIsMember=0, unlike the later source branch.
// Its virtual slot4 predicate corresponds to ContainsNativeHashVirtual;
// the original AptValue header independently supplies the const bool type.
void AptActionInterpreter::_FunctionAptActionDelete(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *name=p->stack.At(0);
    AptValue *object=p->stack.At(1);
    if(object->ContainsNativeHashVirtual()) {
        EAStringC text;
        name->toString(text);
        p->setVariable(object,c->pCurWith,&text,0,1,1,0);
    }
    p->stack.Pop(2);
    p->stack.Push(AptInteger::Create(1));
}
void AptActionInterpreter::_FunctionAptActionDelete2(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *name=p->stack.At(0);
    EAStringC text;
    name->toString(text);
    p->setVariable((AptValue *)c->pCurrentContext,c->pCurWith,&text,0,1,1,0);
    p->stack.Pop();
    p->stack.Push(AptInteger::Create(1));
}

void AptActionInterpreter::_FunctionAptActionGetMember(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *name=p->stack.At(0);
    AptValue *object=p->stack.At(1);
    if(object->isUndefined() || name->isUndefined()) {
        p->stack.Pop(2);
        p->stack.Push(gpUndefinedValue);
    } else if(object->isArray() && (name->isInteger() || name->isFloat())) {
        AptArray *array=object->c_array();
        AptValue *value=array->get(name->toInteger());
        p->stack.PopAndPush(2,value);
    } else if(object->isExtern()) {
        AptValue *value=g_bfmeAptGetExternAtE17768(name->c_string()->GetInternalString()->rva00620090());
        p->stack.PopAndPush(2,value);
    } else {
        EAStringC text;
        name->toString(text);
        AptValue *value=p->getVariable(object,0,&text,1,0,1);
        p->stack.PopAndPush(2,value);
    }
}
// PC always converts the member name into a temporary (later source adds a
// string fast path). Native pooled ID0 is __proto__; slot6 sets hasClass.
void AptActionInterpreter::_FunctionAptActionSetMember(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    AptValue *name=p->stack.At(1);
    AptValue *object=p->stack.At(2);
    if(object->isArray() && (name->isInteger() || name->isFloat())) {
        AptArray *array=object->c_array();
        array->set(name->toInteger(),value);
    } else if(object->ContainsNativeHashVirtual() || object->isCIH()) {
        EAStringC text;
        name->toString(text);
        p->setVariable(object,c->pCurWith,&text,value,1,0,1);
        if(text.IsEqualTo(Rva0070B4F0GetString(0)) && (object->isObject() || object->isCIH())) object->setHasClass(1);
    } else if(object->isExtern()) {
        EAStringC text;
        value->toString(text);
        AptString *str=name->c_string();
        g_bfmeAptSetExternAtE17764(str->str.rva00620090(),text.rva00620090());
    }
    p->stack.Pop(3);
    if(g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0) g_releaseVectorAtE17710->ReleaseValues();
}

#pragma comment(linker, "/alternatename:?isArray@AptValue@@QBE_NXZ=?isArray@BfmeAptValue006DCD20@@QBEHXZ")

#pragma comment(linker, "/alternatename:?isExtern@AptValue@@QBE_NXZ=?rva006DC300@BfmeAptValue006DCD20@@QBEHXZ")

#pragma comment(linker, "/alternatename:?isObject@AptValue@@QBE_NXZ=?isObject@BfmeAptValue006DCD20@@QBEHXZ")

#pragma comment(linker, "/alternatename:?c_array@AptValue@@QBEPAVAptArray@@XZ=?rva006DCFA0@BfmeAptValue006DCD20@@QAEPAV1@XZ")


#pragma comment(linker, "/alternatename:?PopAndPush@AptBasePtrStack@@QAEXHPAVAptValue@@@Z=?rva006FE880@AptBasePtrStack@@QAEXHPAVBfmeAptValue006DCD20@@@Z")

#pragma comment(linker, "/alternatename:?isCIH@AptValue@@QBE_N_N@Z=?isCIH@BfmeAptValue006DCD20@@QBEH_N@Z")

// The native UTF-8 substring overloads return EAStringC by value. Preserve
// their temporary lifetimes and the clamped one-based ActionScript index.
void AptActionInterpreter::_FunctionAptActionSubString(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *count=p->stack.At(0);
    AptValue *index=p->stack.At(1);
    AptValue *value=p->stack.At(2);
    int nCount=count->toInteger();
    int nIndex=index->toInteger();
    --nIndex;
    if(nIndex<0) nIndex=0;
    EAStringC text;
    value->toString(text);
    AptString *sub=AptString::Create();
    if(nCount==0) sub->str.rva006D3470();
    else if(nCount<0) sub->str=text.rva006D5ED0(nIndex);
    else sub->str=text.rva006d5f30(nIndex,nCount);
    p->stack.Pop(3);
    p->stack.Push(sub);
}
void AptActionInterpreter::_FunctionAptActionAsciiToChar(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    if(!value->isUndefined()) {
        AptString *str=AptString::Create();
        str->str=EAStringC(value->toInteger(),1);
        p->stack.Pop();
        p->stack.Push(str);
    } else {
        p->stack.Pop();
        p->stack.Push(gpUndefinedValue);
    }
}

void AptActionInterpreter::_FunctionAptActionGreater(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *a=p->stack.At(0);
    AptValue *b=p->stack.At(1);
    if(Rva006CD220Get()==7) {
        if(a->isUndefined() || b->isUndefined()) {
            p->stack.Pop(2);
            p->stack.Push(gpUndefinedValue);
            return;
        }
    }
    int result=0;
    if(a->isString() && b->isString()) {
        result=strcmp(a->c_string()->GetInternalString()->rva00620090(),b->c_string()->GetInternalString()->rva00620090())<0;
    } else if(a->isFloat() || b->isFloat()) {
        result=b->toFloat()>a->toFloat();
    } else {
        result=b->toInteger()>a->toInteger();
    }
    p->stack.PopAndPush(2,AptBoolean::Create(result!=0));
}

// PC Trace builds prefix/text/newline before invoking the existing log slot.
// Its SWF7 undefined temporary and null check are visible in native branches;
// later source logs directly and therefore only supplies the semantic lead.
void AptActionInterpreter::_FunctionAptActionTrace(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    EAStringC text;
    AptString *undefined=0;
    if(Rva006CD220Get()==7 && value->isUndefined()) {
        undefined=AptString::Create();
        undefined->SetString(Rva0070B4F0GetString(0xA9)->rva00620090());
        undefined->toString(text);
    }
    if(!undefined) value->toString(text);
    EAStringC line("AptTrace: ");
    line.Rva006D4F00Append(text);
    line.Rva006D50A0Append("\n");
    g_bfmeAptLogAtE1773C("%s",line.rva00620090());
    p->stack.Pop();
}

// PC opcode0x34 at table RVA9DC980 loads the same tick cell reset at
// RVA6CD019 and advanced at6CD8B3. Later source calls it gnCurTick; reuse
// the existing address-qualified provider rather than duplicate its storage.
extern int g_rva00891FA0Value;
void AptActionInterpreter::_FunctionAptActionGetTimer(AptActionInterpreter *const p, LocalContextT *const c)
{
    p->stack.Push(AptInteger::Create(g_rva00891FA0Value));
}
void AptActionInterpreter::_FunctionAptActionLessThan2(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *a=p->stack.At(0);
    AptValue *b=p->stack.At(1);
    if(Rva006CD220Get()==7) {
        if(a->isUndefined() || b->isUndefined()) {
            p->stack.Pop(2);
            p->stack.Push(gpUndefinedValue);
            return;
        }
    }
    int result=0;
    if(a->isString() && b->isString()) {
        result=strcmp(b->c_string()->GetInternalString()->rva00620090(),a->c_string()->GetInternalString()->rva00620090())<0;
    } else if(rva006fc370(a) || rva006fc370(b)) {
        p->stack.Pop(2); p->stack.Push(gpUndefinedValue); return;
    } else if(a->isFloat() || b->isFloat()) {
        result=b->toFloat()<a->toFloat();
    } else {
        result=b->toInteger()<a->toInteger();
    }
    AptValue *v=AptBoolean::Create(result!=0);
    p->stack.Pop(2); p->stack.Push(v);
}

// Native assertion-only handlers. The later source changes End to set the return
// flag; PC retains the original unreachable assertion. Each dispatch slot and
// full 35-byte body was checked independently, including literal and line.
void AptActionInterpreter::_FunctionAptActionEnd(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0xc6b);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
void AptActionInterpreter::_FunctionAptActionToggleQuality(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false && \" [APT] \\\"Toggle Quality\\\" is NOT supported. Please do not use this in your actionscript\\n\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0xcf0);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
void AptActionInterpreter::_FunctionAptActionStringLessThan(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x1204);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
void AptActionInterpreter::_FunctionAptActionMBLength(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x123d);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
void AptActionInterpreter::_FunctionAptActionCharToAscii(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x125a);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
void AptActionInterpreter::_FunctionAptActionMBSubString(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x12b0);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
void AptActionInterpreter::_FunctionAptActionMBCharToAscii(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x12ce);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
void AptActionInterpreter::_FunctionAptActionMBAsciiToChar(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x12eb);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
void AptActionInterpreter::_FunctionAptActionBitURShift(AptActionInterpreter *const p, LocalContextT *const c)
{
    g_bfmeAptAssertAtE17734("false", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x1b92);
    if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
}
// With opcode0x94 points to native708B20; original PDB signature and later
// handler source agree. Native assertions retain original spelling and lines.
class BfmeAptValue006DCD20;
void rva007065e0(int,int,BfmeAptValue006DCD20 *,BfmeAptValue006DCD20 **);
__forceinline AptValue *convertWith(AptCIH *c,AptValue *v) { AptValue *out; rva007065e0((int)c,0,(BfmeAptValue006DCD20 *)v,(BfmeAptValue006DCD20 **)&out); return out; }
void AptActionInterpreter::_FunctionAptActionWith(AptActionInterpreter *const p,LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const unsigned char *const *data=(const unsigned char *const *)c->pInstruction;
    c->pInstruction+=4;
    AptValue *value=p->stack.At(0);
    if(value->isUndefined()) {
        c->pCurWith=0;
        c->pInstruction=*data;
    } else {
        value=convertWith(c->pCurrentContext,value);
        if(!value) {
            g_bfmeAptAssertAtE17734("pWith","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x1DA8);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        if(c->pCurWith) {
            g_bfmeAptAssertAtE17734("!pLocalContext->pCurWith","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x1DA9);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        c->pRemoveWithAt=*data;
        c->pCurWith=value;
        c->pCurWith->AddRef();
    }
    p->stack.Pop();
}



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
void AptActionInterpreter::_FunctionAptActionPlay(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptCIH *current=c->pCurrentContext;
    if (!current->isUndefined() && !current->IsLevelInst()) {
        if(c->pCurWith && c->pCurWith->isCIH()) c->pCurWith->c_cih()->SetIsPlaying(true);
        else if(c->pCurrentContext->isCIH()) current->c_cih()->SetIsPlaying(true);
    }
}
void AptActionInterpreter::_FunctionAptActionStop(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptCIH *current=c->pCurrentContext;
    if (!current->isUndefined() && !current->IsLevelInst() && current->mpCharacterInst)
        current->c_cih()->SetIsPlaying(false);
}
#pragma comment(linker, "/alternatename:?c_cih@AptValue@@QAEPAVAptCIH@@_N@Z=?rva006DCF60@BfmeAptValue006DCD20@@QAEPAV1@_N@Z")
#pragma comment(linker, "/alternatename:?IsLevelInst@AptCIH@@QBE_NXZ=?rva006E03A0@BfmeAptValue006DCD20@@QBEHXZ")
#pragma comment(linker, "/alternatename:?GetSpriteInstBase@AptCIH@@QBEPAUAptSpriteInstBase@@XZ=?rva006CFF40@AptCIH@@QBEPAXXZ")

void AptActionInterpreter::_FunctionAptActionNextFrame(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptCIH *cih=c->pCurrentContext->c_cih();
    cih->jumpToFrame(cih->SpriteBaseInline()->mnFrame+1);
    cih->SpriteBaseInline()->mbIsPlaying=0;
}
void AptActionInterpreter::_FunctionAptActionPrevFrame(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptCIH *cih=c->pCurrentContext->c_cih();
    cih->jumpToFrame(cih->SpriteBaseInline()->mnFrame-1);
    cih->SpriteBaseInline()->mbIsPlaying=0;
}
#pragma comment(linker, "/alternatename:?IsSpriteInstBase@AptCIH@@QBE_NXZ=?isSpriteInstBase@Rva006CFCD0@@QBE_NXZ")

struct AptContextRootState { unsigned char prefix[0x54]; AptValue *head; };
struct AptContextRootDisplay { AptContextRootState *state; };
class Rva006E34D0 { public: unsigned char prefix[0x30]; AptContextRootDisplay *display; unsigned char middle[0x10]; AptValue *mpDragMC; float a,b,c,d,tx,ty; unsigned char toMouse[0x74-0x60]; int mouseX,mouseY; };
extern Rva006E34D0 *g_bfmeAptPtrAtE176D0;
void AptActionInterpreter::_FunctionAptActionStopDragMovie(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *drag=g_bfmeAptPtrAtE176D0->mpDragMC;
    if (drag) drag->Release();
    g_bfmeAptPtrAtE176D0->mpDragMC=gpUndefinedValue;
}

void AptActionInterpreter::_FunctionAptActionGotoFrame(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptCIH *cih=0;
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const int *frame=(const int *)c->pInstruction;
    c->pInstruction+=4;
    if(c->pCurWith && c->pCurWith->isCIH()) cih=c->pCurWith->c_cih();
    else if(c->pCurrentContext->isCIH()) cih=c->pCurrentContext->c_cih();
    if(cih) {
        cih->jumpToFrame(*frame);
        cih->SpriteBaseInline()->mbIsPlaying=0;
    }
    if(g_releaseVectorAtE17710->GetNumValues()!=0 && p->stack.count==0) g_releaseVectorAtE17710->ReleaseValues();
}

void AptActionInterpreter::_FunctionAptActionInitArray(AptActionInterpreter *const p, LocalContextT *const c)
{
    int n=p->stack.At(0)->toInteger();
    p->stack.Pop();
    AptArray *a=new AptArray;
    a->AddRef();
    for(int i=0;i<n;++i) a->set(i,p->stack.At(i));
    p->stack.rva006FE050(n);
    p->stack.PushNoInc(a);
}

class BfmeAptValue006DCD20;
void rva007065e0(int,int,BfmeAptValue006DCD20 *,BfmeAptValue006DCD20 **);
// Native indexed22-entry StringCode table, exactly the88 bytes at DDC928.
// Later gaszPropertyNames supplies semantic order; retain address-qualified storage.
int g_aptPropertyCodesAtDDC928[22]={23,26,25,28,2,17,1,21,22,8,14,16,6,11,4,20,9,5,15,12,24,27};
void AptActionInterpreter::_FunctionAptActionGetProperty(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *index=p->stack.At(0);
    AptValue *target=p->stack.At(1);
    // Snapshot the native output cell at its observed read point.
    AptValue *volatile resolved;
    rva007065e0((int)c->pCurrentContext,(int)c->pCurWith,(BfmeAptValue006DCD20 *)target,(BfmeAptValue006DCD20 **)&resolved);
    AptValue *object=resolved;
    if(object) {
        unsigned int n=index->toInteger();
        AptValue *value=p->getVariable(object,c->pCurWith,Rva0070B4F0GetString(g_aptPropertyCodesAtDDC928[n]),1);
        p->stack.Pop(2);p->stack.Push(value);
    } else {p->stack.Pop(2);p->stack.Push(gpUndefinedValue);}
}
void AptActionInterpreter::_FunctionAptActionSetProperty(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    AptValue *index=p->stack.At(1);
    AptValue *target=p->stack.At(2);
    // Snapshot the native output cell at its observed read point.
    AptValue *volatile resolved;
    rva007065e0((int)c->pCurrentContext,(int)c->pCurWith,(BfmeAptValue006DCD20 *)target,(BfmeAptValue006DCD20 **)&resolved);
    unsigned int n=index->toInteger();
    AptValue *object=resolved;
    if(object) p->setVariable(object,c->pCurWith,Rva0070B4F0GetString(g_aptPropertyCodesAtDDC928[n]),value,1);
    p->stack.Pop(3);
}

// The original AptValue header supplies bool predicates and const checked casts.
// Lookup/Register headers c6dc857ff8e1760a/95fdc6cae0bddecc name these integer
// payloads. PC independently reads +8 after checked casts; only prefixes used.
class AptLookup : public AptValue { public: int nLookup; };
class AptRegister : public AptValue { public: int nVal; };
AptValue *Rva00709EC0Get(int);
void AptActionInterpreter::stackPushIndirect(AptValue *const pValue)
{
    if (!pValue) {
        g_bfmeAptAssertAtE17734("pValue", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.inl", 0x5E);
        if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
    AptValue *pPushValue;
    if (pValue->isLookup()) pPushValue=constantPool.apItems[pValue->c_lookup()->nLookup];
    else if (pValue->isRegister()) {
        int iRegNum=pValue->c_register()->nVal;
        if (iRegNum<0) {
            g_bfmeAptAssertAtE17734("iRegNum >= 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptActionInterpreter.inl", 0x68);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        pPushValue=Rva00709EC0Get(iRegNum);
    } else pPushValue=pValue;
    // Native inlines Push here; preserve its capacity assertion and AddRef order.
    if (stack.count>=stack.capacity) {
        g_bfmeAptAssertAtE17734("m_nElements < m_nCapacity", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x80);
        if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
    stack.items[stack.count++]=pPushValue;
    pPushValue->AddRef();
}
void AptActionInterpreter::_FunctionAptActionPush(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const AptConstantPool *data=(const AptConstantPool *)c->pInstruction;
    c->pInstruction+=sizeof(AptConstantPool);
    for (int i=0;i<data->nItems;++i) p->stackPushIndirect(data->apItems[i]);
}
#pragma comment(linker, "/alternatename:?isLookup@AptValue@@QBE_NXZ=?isLookup@BfmeAptValue006DCD20@@QBEHXZ")
#pragma comment(linker, "/alternatename:?isRegister@AptValue@@QBE_NXZ=?isRegister@BfmeAptValue006DCD20@@QBEHXZ")
#pragma comment(linker, "/alternatename:?c_lookup@AptValue@@QBEPAVAptLookup@@XZ=?checkedLookup@BfmeAptValue006DCD20@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:?c_register@AptValue@@QBEPAVAptRegister@@XZ=?checkedRegister@BfmeAptValue006DCD20@@QAEPAV1@XZ")

void AptActionInterpreter::_FunctionAptActionThrow(AptActionInterpreter *const p, LocalContextT *const c)
{
    if (p->stack.count<1) {
        g_bfmeAptAssertAtE17734("pInterpreter->stack.GetSize() >= 1", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x25BC);
        if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
    AptValue *value=p->stack.At(0);
    value->AddRef();
    p->mpThrownValue=value;
    p->stack.Pop();
}
void AptActionInterpreter::_FunctionAptActionTypeOf(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *v=p->stack.At(0);
    AptString *s=AptString::Create();
    if(v->getIsDefined()) {
        if(v->isInteger() || v->isFloat()) s->SetString(Rva0070B4F0GetString(0x63)->rva00620090());
        else if(v->isBoolean()) s->SetString(Rva0070B4F0GetString(0x27)->rva00620090());
        else if(v->isString()) s->SetString(Rva0070B4F0GetString(0x9d)->rva00620090());
        else if(v->isObject() || v->isArray()) s->SetString(Rva0070B4F0GetString(0x64)->rva00620090());
        else if(v->isCIH()) {
            if(v->c_cih()->IsSpriteInst() || v->c_cih()->IsAnimationInst()) s->SetString(Rva0070B4F0GetString(0x5e)->rva00620090());
            else if(v->c_cih()->IsLevelInst()) s->SetString(Rva0070B4F0GetString(0xa9)->rva00620090());
            else s->SetString(Rva0070B4F0GetString(0x64)->rva00620090());
        }
        else if(v->isNone()) s->SetString(Rva0070B4F0GetString(0x62)->rva00620090());
        else if(v->isUndefined()) s->SetString(Rva0070B4F0GetString(0xa9)->rva00620090());
        else if(v->isScriptFunction() || v->isNativeFunction()) s->SetString(Rva0070B4F0GetString(0x37)->rva00620090());
    } else s->SetString(Rva0070B4F0GetString(0xa9)->rva00620090());
    p->stack.Pop(); p->stack.Push(s);
}


#pragma comment(linker, "/alternatename:?getIsDefined@AptValue@@QBE_NXZ=?get@Rva006DBB60ShrNAndField@@QBE_NXZ")

#pragma comment(linker, "/alternatename:?isNone@AptValue@@QBE_NXZ=?rva006DBFA0@BfmeAptValue006DCD20@@QBEHXZ")

#pragma comment(linker, "/alternatename:?isBoolean@AptValue@@QBE_NXZ=?isBoolean@BfmeAptValue006DCD20@@QBEHXZ")

#pragma comment(linker, "/alternatename:?isScriptFunction@AptValue@@QBE_NXZ=?isScriptFunction@BfmeAptValue006DCD20@@QBEHXZ")

#pragma comment(linker, "/alternatename:?isNativeFunction@AptValue@@QBE_NXZ=?isNativeFunction@BfmeAptValue006DCD20@@QBEHXZ")

#pragma comment(linker, "/alternatename:?IsSpriteInst@AptCIH@@QBE_N_N@Z=?rva006E01A0@BfmeAptValue006DCD20@@QBEH_N@Z")

#pragma comment(linker, "/alternatename:?IsAnimationInst@AptCIH@@QBE_N_N@Z=?rva006CBEE0@BfmeAptValue006DCD20@@QBEH_N@Z")


void AptActionInterpreter::_FunctionAptActionGotoLabel(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const char *const *data=(const char *const *)c->pInstruction;
    c->pInstruction+=4;
    EAStringC label=*data;
    AptCIH *target;
    if(c->pCurWith && c->pCurWith->isCIH()) target=c->pCurWith->c_cih();
    else target=c->pCurrentContext;
    int frame=target->SpriteBaseInline()->character->movie.labelToFrame(&label)+1;
    if(frame-1>=0) {
        target->jumpToFrame(frame-1);
        target->SpriteBaseInline()->mbIsPlaying=0;
    }
}
#pragma comment(linker, "/alternatename:?labelToFrame@AptMovie@@QBEHPBVEAStringC@@@Z=?bfmeGo1034F@BfmeF1034@@QAEHH@Z")

void AptActionInterpreter::_FunctionAptActionCallFrame(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    int frame=-1;
    if(value->isString()) {
        AptValue *labelContext;
        EAStringC name;
        getContext(c->pCurrentContext,c->pCurWith,value->c_string()->GetInternalString(),&labelContext,name);
        frame=labelContext->c_cih()->GetCharacterInst()->character->movie.labelToFrame(&name);
    } else if(value->isInteger()) frame=value->toInteger();
    else {
        g_bfmeAptAssertAtE17734("NOT_REACHED", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x1EFD);
        if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
    p->stack.Pop();
    if(frame!=-1) c->pCurrentContext->GetCharacterInst()->character->movie.runFrameActions(c->pCurrentContext,frame);
}
#pragma comment(linker, "/alternatename:?IsCharacterInst@AptCIH@@QBE_NXZ=?isCharacterInst@BfmeAptValue006DCD20@@QBEHXZ")
#pragma comment(linker, "/alternatename:?runFrameActions@AptMovie@@QAEXPAVAptCIH@@H@Z=?rva0070F5C0@Rva0070F5C0@@QAEXPAVAptCIH@@H@Z")
#pragma comment(linker, "/alternatename:?getContext@AptActionInterpreter@@CA_NPAVAptValue@@0PBVEAStringC@@PAPAV2@AAV3@@Z=?rva006FEC00@@YAEHHPAVEAStringC@@PAH0@Z")

void AptActionInterpreter::_FunctionAptActionSetTarget2(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *object=p->stack.At(0);
    EAStringC name;
    object->toString(name);
    if(name.rva006D3750()==0) {
        if(c->pCurWith) c->pCurWith->Release();
        c->pCurWith=0;
    } else {
        if(c->pCurWith) {
            g_bfmeAptAssertAtE17734("!pLocalContext->pCurWith", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x1087);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        AptValue *target=getObject(c->pCurrentContext,c->pCurWith,&name);
        if(!target) {
            g_bfmeAptAssertAtE17734("pTarget", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x1089);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        c->pRemoveWithAt=0;
        c->pCurWith=target;
        c->pCurWith->AddRef();
    }
    p->stack.Pop();
}

void AptActionInterpreter::_FunctionAptActionSetTarget(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const char *const *data=(const char *const *)c->pInstruction;
    c->pInstruction+=4;
    if((*data)[0]==0) {
        if(c->pCurWith) c->pCurWith->Release();
        c->pCurWith=0;
    } else {
        if(c->pCurWith) {
            g_bfmeAptAssertAtE17734("!pLocalContext->pCurWith", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x1D3A);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        EAStringC name(*data);
        AptValue *target;
        if((*data)[0]=='/' || (*data)[0]=='.') {
            const char *path=*data;
            AptCIH *t=c->pCurrentContext;
            while(path[0]=='.' && path[1]=='.' && t->mpDisplayListParent) {
                t=t->mpDisplayListParent;
                path+=2;
            }
            target=t;
        } else {
            name.TrimRight("/");
            target=getObject(c->pCurrentContext,0,&name);
        }
        if(!target) {
            g_bfmeAptAssertAtE17734("pTarget", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x1D51);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        c->pRemoveWithAt=0;
        c->pCurWith=target;
        c->pCurWith->AddRef();
    }
}

void AptActionInterpreter::_FunctionAptActionCloneSprite(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *depth=p->stack.At(0);
    AptValue *target=p->stack.At(1);
    AptValue *source=p->stack.At(2);
    int n=depth->toInteger();
    p->rva007092F0(c->pCurrentContext,c->pCurWith,source,target,n,0);
    p->stack.Pop(3);
}

// Native type IDs19 (level) and1/42 (strings) come from the target branches
// and switch table; donor enum numbering differs. Native comparison is float.
void AptActionInterpreter::_FunctionAptActionStrictEquals(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *a=p->stack.At(0),*b=p->stack.At(1);
    int result=0;
    if(a->getVtblIndex()==19) a=gpUndefinedValue;
    if(b->getVtblIndex()==19) b=gpUndefinedValue;
    if(Rva006CD220Get()==7) {
        if(a->isUndefined()) ++result;
        if(b->isUndefined()) ++result;
        if(result>0) { p->stack.PopAndPush(2,AptBoolean::Create(result==2));return; }
    }
    if(((a->isInteger() || a->isFloat()) && (b->isInteger() || b->isFloat())) || a->getVtblIndex()==b->getVtblIndex()) {
        switch(a->getVtblIndex()) {
        case 1: case 42:
            if(b->c_string()->GetInternalString()->rva006D3560(a->c_string()->GetInternalString())) result=1;
            break;
        case 6: {
            float fa=a->toFloat();
            if(b->isInteger()) { int nb=b->toInteger(); result=(float)fabs(fa-nb)<0.001f; }
            else { float fb=b->toFloat(); result=(float)fabs(fa-fb)<0.001f; }
            break;
        }
        case 5: case 7: {
            int na=a->toInteger();
            if(b->isInteger()) { int nb=b->toInteger(); result=na==nb; }
            else { float fb=b->toFloat(); result=(float)fabs(na-fb)<0.001f; }
            break;
        }
        default: result=a==b;break;
        }
    }
    p->stack.PopAndPush(2,AptBoolean::Create(result!=0));
}


// Native Equals2 uses exact float equality for two floats; the mixed numeric
// branches use float tolerance. The Boolean fallback tests only operand A.
void    AptActionInterpreter::_FunctionAptActionEquals2(AptActionInterpreter * const pInterpreter, LocalContextT * const pLocalContext)
{

    AptValue *pA = pInterpreter->stack.At(0);
    AptValue *pB = pInterpreter->stack.At(1);
    int nResult = 0;



    if(pA->getVtblIndex()==19)
    {
        pA = gpUndefinedValue;
    }
    if(pB->getVtblIndex()==19)
    {
        pB = gpUndefinedValue;
    }

    
    
    
    
    if(Rva006CD220Get()==7)
    {
        
        if( pA->isUndefined() )
        {
            nResult++;
        }
        if( pB->isUndefined() )
        {
            nResult++;
        }
        if( nResult > 0 )
        {
            
            
            pInterpreter->stack.Pop(2);
            pInterpreter->stack.Push(AptBoolean::Create(nResult==2));
            return;
        }
    }
    


    if( ((pA->isInteger() || pA->isFloat() || pA->isBoolean() || pA->isString()) &&
        (pB->isInteger() || pB->isFloat()|| pB->isBoolean() || pB->isString())) ||
        (pA->getVtblIndex() == pB->getVtblIndex()) )
    {
        if(pA->isUndefined())                                   
        {
            nResult = 1;
        }
        else if(pA->isInteger() && pB->isInteger())             
        {
            nResult = (pA->toInteger() == pB->toInteger());
        }
        else if(pA->isFloat() && pB->isFloat())                 
        {
            nResult = pA->toFloat()==pB->toFloat();
        }
        else if(pA->isString() && pB->isString())               
        {
            if (pB->c_string()->GetInternalString()->IsEqualTo(pA->c_string()->GetInternalString()))
            {
                nResult = 1;
            }
        }
        else if(((pA->isInteger() || pA->isFloat()) && !rva006fc370(pB)) || ((pB->isInteger() || pB->isFloat()) && !rva006fc370(pA)))
        {
            
            bool fStrAIsFloat = false;
            bool fStrBIsFloat = false;
            if  (pA->isString() || pA->isFloat())       
            {
                if  (pA->isFloat() || (pA->c_string()->GetInternalString()->Find('.') != -1))
                {
                    fStrAIsFloat = true;
                }
            }
            if(pB->isString() || pB->isFloat())     
            {
                if  (pB->isFloat() || (pB->c_string()->GetInternalString()->Find('.') != -1))
                {
                    fStrBIsFloat = true;
                }
            }
            if(pA->isInteger())
            {
                int nA = pA->toInteger();
                if(fStrBIsFloat)
                {
                    float fB = pB->toFloat();
                    nResult = (float)fabs(nA - fB) < 0.001f;
                }
                else
                {
                    int nB = pB->toInteger();
                    nResult = (nA == nB);
                }
            }
            else if(pB->isInteger())
            {
                int nB = pB->toInteger();
                if(fStrAIsFloat)
                {
                    float fA = pA->toFloat();
                    nResult = (float)fabs(fA - nB) < 0.001f;
                }
                else
                {
                    int nA = pA->toInteger();
                    nResult = (nA == nB);
                }
            }
            else
            {
                float fA = pA->toFloat();
                float fB = pB->toFloat();
                nResult = (float)fabs(fA - fB) < 0.001f;
            }
        }
        else                                            
        {
            if(pA->isString() && !pB->isBoolean())
            {
                EAStringC sa,sb;
                pA->toString(sa);pB->toString(sb);

                nResult = sa.IsEqualTo(&sb) ? 1 : 0;
            }
            
            else if (pA->isBoolean() && !pB->isString())
            {
                nResult = pA->toInteger() == pB->toInteger() ? 1 : 0;
            }
            else
            {
                nResult = (pA == pB);                   
            }
        }
    }
    else
    {
        if (pA->isUndefined() && pB->isUndefined()) 
        {
            nResult = 1;
        }
    }

    pInterpreter->stack.Pop(2);
    pInterpreter->stack.Push(AptBoolean::Create(nResult != 0));
}

class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table { public: void add(Rva8D0D80String *,Rva8D0D80Value *); };
void AptActionInterpreter::_FunctionAptActionInitObject(AptActionInterpreter *const p, LocalContextT *const c)
{
    int n=p->stack.At(0)->toInteger();
    p->stack.Pop();
    AptValue *object=(AptValue *)p->_createObject((AptValue *)c->pCurrentContext,c->pCurWith,Rva0070B4F0GetString(0x64),0,true);
    if(object) {
        for(int i=0,reg=0;i<n;++i,reg+=2) {
            AptValue *value=p->stack.At(reg);
            AptValue *name=p->stack.At(reg+1);
            EAStringC text;name->toString(text);
            ((Rva8D0D80Table *)((char *)object+8))->add((Rva8D0D80String *)&text,(Rva8D0D80Value *)value);
        }
        p->stack.rva006E3AA0(2*n);
        p->stack.Push(object);object->Release();
    } else {p->stack.rva006FE050(2*n);p->stack.Push(gpUndefinedValue);}
}

// Native static helper uses pB in EBX and pA on the stack. MSVC chooses
// that internal ABI from real C++; branch-local destination binding retains
// the native predicate/member-address ordering (objects seat scheduling fix).
static AptString *_concatAsStrings(AptValue *a,AptValue *b)
{
    AptString *result=AptString::Create();
    EAStringC *str;
    if(b->isString()) {str=result->GetInternalString(); *str=*b->c_string()->GetInternalString();}
    else {str=result->GetInternalString(); b->toString(*str); }
    if(a->isString()) str->Rva006D4F00Append(*a->c_string()->GetInternalString());
    else {EAStringC text;a->toString(text);str->Rva006D4F00Append(text);}
    return result;
}

void AptActionInterpreter::_FunctionAptActionStringAdd(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *a=p->stack.At(0);
    AptValue *b=p->stack.At(1);
    if(Rva006CD220Get()==7) {
        AptString *undefined=AptString::Create();
        undefined->SetString(Rva0070B4F0GetString(0xA9)->rva00620090());
        if(a->isUndefined()) a=undefined;
        if(b->isUndefined()) b=undefined;
    }
    AptValue *result=_concatAsStrings(a,b);
    p->stack.Pop(2);
    p->stack.Push(result);
}

void AptActionInterpreter::_FunctionAptActionAdd2(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *a=p->stack.At(0),*b=p->stack.At(1);
    int version=Rva006CD220Get();
    if(a->isString() || b->isString()) {
        if(version==7) {
            if(a->isUndefined()) {a=AptString::Create();a->c_string()->SetString(Rva0070B4F0GetString(0xa9)->rva00620090());}
            if(b->isUndefined()) {b=AptString::Create();b->c_string()->SetString(Rva0070B4F0GetString(0xa9)->rva00620090());}
        }
        AptString *s=_concatAsStrings(a,b);
        p->stack.Pop(2);p->stack.Push(s);
    } else if((a->isInteger() || b->isInteger()) && !a->isFloat() && !b->isFloat()) {
        if(version==7 && (a->isUndefined() || b->isUndefined())) {p->stack.Pop(2);p->stack.Push(gpUndefinedValue);return;}
        int na=a->toInteger(),nb=b->toInteger();
        p->stack.Pop(2);p->stack.Push(AptInteger::Create(na+nb));
    } else {
        if(version==7 && (a->isUndefined() || b->isUndefined())) {p->stack.Pop(2);p->stack.Push(gpUndefinedValue);return;}
        float fa=a->toFloat(),fb=b->toFloat();
        p->stack.Pop(2);p->stack.Push(Rva008A4EA0MakeFloat(fa+fb));
    }
}

void AptActionInterpreter::_FunctionAptActionNewObject(AptActionInterpreter *const p,LocalContextT *const c)
{
    AptValue *name=p->stack.At(0);
    AptValue *params=p->stack.At(1);
    EAStringC objectName;
    name->toString(objectName);
    int nParams=params->toInteger();
    p->stack.Pop(2);
    AptValue *object=(AptValue *)p->_createObject((AptValue *)c->pCurrentContext,c->pCurWith,&objectName,nParams,true);
    if(object) { p->stack.Push(object); object->Release(); }
    else p->stack.Push(gpUndefinedValue);
}

void AptActionInterpreter::_FunctionAptActionNewMethod(AptActionInterpreter *const p,LocalContextT *const c)
{
    AptValue *name=p->stack.At(0);
    AptValue *context=p->stack.At(1);
    AptValue *params=p->stack.At(2);
    EAStringC objectName;
    name->toString(objectName);
    int nParams=params->toInteger();
    p->stack.Pop();
    p->stack.PopNoDec();
    p->stack.Pop();
    AptValue *object=(AptValue *)p->_createObject(context,c->pCurWith,&objectName,nParams,true);
    context->Release();
    if(object) { p->stack.Push(object); object->Release(); }
    else p->stack.Push(gpUndefinedValue);
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
    __forceinline void SetSuperConstructor(AptValue *p) { AptValue *old=mp__constructor__; mp__constructor__=p; p->AddRef(); if(old) old->Release(); }
};
void AptActionInterpreter::_FunctionAptActionExtends(AptActionInterpreter *const p,LocalContextT *const c)
{
    if (p->stack.GetSize()<2) {
        g_bfmeAptAssertAtE17734("pInterpreter->stack.GetSize() >= 2", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x23FE);
        if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
    AptValue *pSuperClass=p->stack.At(0);
    AptValue *pSubClass=p->stack.At(1);
    if (pSuperClass->ContainsNativeHashVirtual() && pSubClass->isScriptFunction()) {
        AptNativeHash *pSuperHash=pSuperClass->GetNativeHashVirtual();
        AptNativeHash *pSubHash=pSubClass->GetNativeHashVirtual();
        AptValue *pSuperPrototype=pSuperHash->GetPrototype();
        AptValue *pSubPrototype=pSubHash->GetPrototype();
        if (!pSuperPrototype) { pSuperPrototype=new AptPrototype(); pSuperHash->SetPrototype(pSuperPrototype); }
        if (!pSubPrototype) { pSubPrototype=new AptPrototype(); pSubHash->SetPrototype(pSubPrototype); }
        if (!pSubPrototype->isPrototype()) {
            g_bfmeAptAssertAtE17734("pSubPrototype->isPrototype() && \"Object Extending has invalid prototype object!\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x2415);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        pSubPrototype->c_prototype()->SetSuperConstructor(pSuperClass);
        pSuperClass->setHasClass(1);pSubClass->setHasClass(1);
        pSubPrototype->GetNativeHashVirtual()->Set__Proto__(pSuperPrototype);
    } else Rva006CC110Log(3,"--AptWarning-- Actionscript is attempting to use invalid objects in Extends Opcode.");
    p->stack.Pop(2);
}

#pragma comment(linker, "/alternatename:??0AptPrototype@@QAE@XZ=??0Rva006DE1A0@@QAE@XZ")
#pragma comment(linker, "/alternatename:??3AptPrototype@@SAXPAXI@Z=?Rva006F12F0Free@@YAXPAXH@Z")
#pragma comment(linker, "/alternatename:?isPrototype@AptValue@@QBE_NXZ=?isPrototype@BfmeAptValue006DCD20@@QBEHXZ")
#pragma comment(linker, "/alternatename:?c_prototype@AptValue@@QBEPAVAptPrototype@@XZ=?rva006DD120@BfmeAptValue006DCD20@@QAEPAV1@XZ")

// PC prefix slotDDC920 points to FSCommand:; callback E17758 is zero-initialized.
// Original Apt.h callback declaration and native caller establish void cdecl ABI.
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)
extern "C" int __cdecl strncmp(const char *,const char *,unsigned int);
const char *g_bfmeAptFSCommandAtDDC920="FSCommand:";
void (__cdecl *g_bfmeAptCommandAtE17758)(const char *,const char *)=0;
int AptActionInterpreter::doFSCommand(const char *szCommand,const char *szParams)
{
    if (strncmp(szCommand,g_bfmeAptFSCommandAtDDC920,strlen(g_bfmeAptFSCommandAtDDC920))!=0) {
        g_bfmeAptAssertAtE17734("isFSCommand(szCommand)", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0xC4B);
        if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
    szCommand=&szCommand[strlen(g_bfmeAptFSCommandAtDDC920)];
    g_bfmeAptCommandAtE17758(szCommand,szParams);
    return 1;
}

AptValue *AptActionInterpreter::getObject(AptValue *current,AptValue *with,const EAStringC *path)
{
    EAStringC name;
    if(path->rva006D3750()==0) return current;
    AptValue *context;
    getContext(current,with,path,&context,name);
    if(context) {
        AptValue *value=context->findChild(&name,with);
        if(value && value->ContainsNativeHashVirtual()) return value;
    }
    return 0;
}

// Volatile out slot plus stable snapshot preserves native context load scheduling.
void AptActionInterpreter::_FunctionAptActionGotoFrame2(AptActionInterpreter *const p, LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const int *data=(const int *)c->pInstruction;
    c->pInstruction+=4;
    AptValue *value=p->stack.At(0);
    AptCIH *cih=0;
    if(c->pCurWith && c->pCurWith->isCIH()) cih=c->pCurWith->c_cih();
    else if(c->pCurrentContext->isCIH()) cih=c->pCurrentContext->c_cih();
    int frame=-1;
    if(value->isString()) {
        AptValue *volatile labelContext;
        EAStringC name;
        getContext(c->pCurrentContext,c->pCurWith,value->c_string()->GetInternalString(),(AptValue **)&labelContext,name);
        AptValue *resolved=labelContext;
        if(resolved->isCIH() && resolved->c_cih()->IsSpriteInstBase())
            frame=resolved->c_cih()->GetSpriteInstBase()->character->movie.labelToFrame(&name);
    } else if(value->isInteger()) frame=value->toInteger();
    if(frame!=-1) {
        cih->jumpToFrame(frame);
        cih->SpriteBaseInline()->mbIsPlaying=(*data!=0) ? 1 : 0;
    }
    p->stack.Pop();
}
// Rehomed from Rva007065E0Cluster.cpp. Preserve its address-named ABI and
// verified121B body. Visibility lets MSVC prove the output cell does not escape;
// TargetPath then reuses the dead incoming argument slot as retail does.
class BfmeAptValue006DCD20;
BfmeAptValue006DCD20 *rva007064f0(int,int,EAStringC *);
__declspec(noinline) void rva007065e0(int a,int b,BfmeAptValue006DCD20 *value,BfmeAptValue006DCD20 **out) {
 AptValue *v=(AptValue *)value;
 if(v->isCIH(false) || v->ContainsNativeHashVirtual()) {*out=value;return;}
 if(v->isString()) {*out=rva007064f0(a,b,v->c_string()->GetInternalString());return;}
 g_bfmeAptAssertAtE17734("NOT_REACHED","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x7a6);
 if(g_bfmeAptBreakOnAssertAtDDC01C) {__asm int 3}
}

void rva006ffce0(AptValue *,EAStringC &);
void AptActionInterpreter::_FunctionAptActionTargetPath(AptActionInterpreter *const p, LocalContextT *const c)
{
    EAStringC buffer;
    AptValue *obj=p->stack.At(0);
    AptValue *volatile out;
    rva007065e0((int)c->pCurrentContext,(int)c->pCurWith,(BfmeAptValue006DCD20 *)obj,(BfmeAptValue006DCD20 **)&out);
    AptValue *context=out;
    if(context) {
        if(context->isCIH()) rva006ffce0((AptValue *)context->c_cih(),buffer);
        else buffer="";
        AptString *s=AptString::Create();
        s->str=buffer;
        p->stack.Pop(); p->stack.Push(s);
    } else {
        p->stack.Pop(); p->stack.Push(gpUndefinedValue);
    }
}

#pragma comment(linker, "/alternatename:?rva007064f0@@YAPAVBfmeAptValue006DCD20@@HHPAVEAStringC@@@Z=?getObject@AptActionInterpreter@@CAPAVAptValue@@PAV2@0PBVEAStringC@@@Z")

void AptActionInterpreter::_FunctionAptActionRemoveSprite(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *path=p->stack.At(0);
    AptValue *object;
    if(!path->isUndefined()) {
        rva007065e0((int)c->pCurrentContext,(int)c->pCurWith,(BfmeAptValue006DCD20 *)path,(BfmeAptValue006DCD20 **)&object);
        AptValue *resolved=object;
        if(resolved && resolved->isCIH()) {
            AptCIH *cih=resolved->c_cih();
            AptSpriteInstBase *parent=cih->mpDisplayListParent->GetSpriteInstBase();
            parent->displayList.removeClonedObject(cih);
        }
    }
    p->stack.Pop();
}

extern "C" char *__cdecl strcpy(char *,const char *);
#pragma intrinsic(strcpy)
__declspec(noinline) unsigned char rva006FD100(int current,int with,EAStringC *var,int *out,char *name)
{
    const char *cur;
    AptValue *context=(AptValue *)current;
    AptValue *next;
    bool id=false;
    const char *text=var->rva00620090();
    name[0]=0;
    if(text[0]=='/') {
        context=g_bfmeAptPtrAtE176D0->display->state->head;
        cur=text+1;
        *out=(int)context;
        id=true;
    } else {
        *out=current;
        cur=text;
    }
    char dir[256];
    char *dest=dir;
    for(;;) {
        switch(*cur) {
        case '.':
            if(cur[1]=='.') {
                *dest++=*cur++;
                *dest++=*cur++;
                continue;
            }
            *dest=0;
            {EAStringC part(dir);context=context->findChild(&part,(AptValue *)with);}
            with=0;
            if(!context) {*out=0;return id;}
            ++cur;dest=dir;break;
        case ':':
            *dest=0;
            {EAStringC part(dir);next=context->findChild(&part,(AptValue *)with);}
            with=0;
            if(next) {*out=(int)next;strcpy(name,cur+1);return id;}
            ++cur;dest=dir;break;
        case 0:
            *dest=0;
            *out=with ? with : (int)context;
            strcpy(name,dir);return id;
        default: *dest++=*cur++;break;
        }
    }
}

__declspec(noinline) unsigned char rva006FEC00(int value, int allowEmpty, EAStringC *src,
	int *resultSlot, EAStringC *outString)
{
	const char *scan = src->rva00620090();
	char c = *scan++;
	const int strict = allowEmpty;
	bool allDigits = true;
	while (c) {
		if (c < '0') {
			allDigits = false;
			break;
		}
		if (c == ':') {
			allDigits = false;
			break;
		}
		c = *scan++;
	}

	if (allDigits && !strict) {
		*outString = *src;
		*resultSlot = value;
		return 0;
	}

	char buf[0x100];
	unsigned char ok = rva006FD100(value, allowEmpty, src, resultSlot, buf);
	EAStringC tmp(buf);
	*outString = tmp;
	return ok;
}
void AptActionInterpreter::_FunctionAptActionStartDragMovie(AptActionInterpreter *const p, LocalContextT *const c)
{
    AptValue *target=p->stack.At(0);
    if(target->isString()) {
        AptValue *context=0;
        EAStringC name;
        rva006FEC00((int)c->pCurrentContext,(int)c->pCurWith,target->c_string()->GetInternalString(),(int *)&context,&name);
        target=p->getVariable(context,c->pCurWith,&name,1);
    }
    if(!target->isCIH()) {
        g_bfmeAptAssertAtE17734("pTarget->isCIH()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x11BA);
        if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
    int n=3;
    target->AddRef();
    g_bfmeAptPtrAtE176D0->mpDragMC=target;
    g_bfmeAptPtrAtE176D0->tx=0.f;
    g_bfmeAptPtrAtE176D0->ty=0.f;
    g_bfmeAptPtrAtE176D0->a=-9999.f;
    g_bfmeAptPtrAtE176D0->b=-9999.f;
    g_bfmeAptPtrAtE176D0->c=-9999.f;
    g_bfmeAptPtrAtE176D0->d=-9999.f;
    if(!p->stack.At(1)->isInteger()) {
        float mouse=(float)g_bfmeAptPtrAtE176D0->mouseX;
        g_bfmeAptPtrAtE176D0->tx=mouse-target->c_cih()->matrixTX;
        mouse=(float)g_bfmeAptPtrAtE176D0->mouseY;
        g_bfmeAptPtrAtE176D0->ty=mouse-target->c_cih()->matrixTY;
    }
    if(p->stack.At(2)->isInteger()) {
        n+=4;
        g_bfmeAptPtrAtE176D0->d=p->stack.At(3)->toFloat();
        g_bfmeAptPtrAtE176D0->c=p->stack.At(4)->toFloat();
        g_bfmeAptPtrAtE176D0->b=p->stack.At(5)->toFloat();
        g_bfmeAptPtrAtE176D0->a=p->stack.At(6)->toFloat();
    }
    p->stack.rva006E3AA0(n);
}
class AptObject : public AptValue { public: bool DoesImplementObject(AptValue *) const; };
bool AptActionInterpreter::isObjectOfType(AptValue *pObject, AptValue *pInterface)
{
    bool bIsOfType=false;
    if (pObject->ContainsNativeHashVirtual() && pInterface->ContainsNativeHashVirtual()) {
        AptValue *pFuncPrototype=pInterface->GetNativeHashVirtual()->mpPrototype;
        if (!pFuncPrototype->isPrototype()) {
            g_bfmeAptAssertAtE17734("pFuncPrototype->isPrototype()", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x2443);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        if (pObject->isCIH()) {
            AptValue *pProto=pObject->GetNativeHashVirtual()->Get__Proto__();
            while (pProto) {
                if (pProto==pFuncPrototype) bIsOfType=true;
                pProto=pProto->GetNativeHashVirtual()->Get__Proto__();
            }
        } else {
            if (((AptObject *)pObject)->DoesImplementObject(pFuncPrototype)) bIsOfType=true;
        }
    } else if (!pObject->isScriptFunction() && !pObject->isObject() && pObject->getVtblIndex()==pInterface->getVtblIndex()) bIsOfType=true;
    return bIsOfType;
}
void AptActionInterpreter::_FunctionAptActionCastOp(AptActionInterpreter *const p, LocalContextT *const c)
{
    if (p->stack.count<2) {
        g_bfmeAptAssertAtE17734("false && \"[APT] Actionscript Cast Op did not find enough parameters. Check Script code.\"", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x24C9);
        if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        p->stack.PopAndPush(p->stack.count,gpUndefinedValue);
        return;
    }
    AptValue *object=p->stack.At(0);
    AptValue *interfaceValue=p->stack.At(1);
    if (isObjectOfType(object,interfaceValue)) p->stack.PopAndPush(2,object);
    else { p->stack.Pop(2); p->stack.PushNoInc(gpUndefinedValue); }
}
#pragma comment(linker, "/alternatename:?getVtblIndex@AptValue@@QBE?AW4AptVirtualFunctionTable_Indices@@XZ=?get@Rva006DBB30SarDwordField@@QBEHXZ")


void AptActionInterpreter::_FunctionAptActionInstanceOf(AptActionInterpreter *const p, LocalContextT *const c)
{
    if(!(p->stack.count>=2)) {
        g_bfmeAptAssertAtE17734("pInterpreter->stack.GetSize() >= 2","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x248d);
        if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
    if(p->stack.count<2) {
        g_bfmeAptAssertAtE17734("false && \"[APT] Actionscript InstanceOf Op did not find enough parameters. Check Script code.\"","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x2491);
        if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        p->stack.PopAndPush(p->stack.count,gpUndefinedValue);return;
    }
    AptValue *obj=p->stack.At(0);
    AptValue *type=p->stack.At(1);
    bool result=isObjectOfType(obj,type);
    p->stack.PopAndPush(2,AptBoolean::Create(result));
}

class Rva8D0D80Result { public: void rva006FBED0(); };
class AptFrameStack;
extern AptFrameStack *g_bfmeFrameStackAtE1835C;
// Target 706070..706234; donor supplies semantics; native proves +30 function,
// +8 frame hash and this 20-byte action header. runStream 7002C0 has a verified provider below.
struct RuntimeTryBlock { unsigned int trySize,catchSize,finallySize; unsigned char flags; unsigned char unused[2]; unsigned char caughtReg; const char *caughtName; };
void AptActionInterpreter::_FunctionAptActionTry(AptActionInterpreter *const p,LocalContextT *const c)
{
    unsigned int nPreStackSize=p->stack.GetSize();
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const RuntimeTryBlock *data=(const RuntimeTryBlock *)c->pInstruction;
    c->pInstruction+=sizeof(RuntimeTryBlock);
    c->pInstruction+=data->trySize;c->pInstruction+=data->catchSize;c->pInstruction+=data->finallySize;
    p->runStream((const unsigned char *)(data+1),c->pCurrentContext,data->trySize,c->pParentCharacter);
    if (p->mpThrownValue && (data->flags&1)) {
        AptValue *thrown=p->mpThrownValue;
        if (data->flags&4) Rva00709F70Set(data->caughtReg,thrown);
        else {
            EAStringC param(data->caughtName);
            if(p->mpCurrentFunction) {
                if(!g_bfmeFrameStackAtE1835C) ((Rva8D0D80Result *)p->mpCurrentFunction)->rva006FBED0();
                ((AptNativeHash *)((unsigned char *)g_bfmeFrameStackAtE1835C+8))->Set(&param,thrown);
            } else p->setVariable((AptValue *)c->pCurrentContext,0,&param,thrown);
        }
        p->mpThrownValue->Release();p->mpThrownValue=0;
        p->runStream((const unsigned char *)(data+1)+data->trySize,c->pCurrentContext,data->catchSize,c->pParentCharacter);
    }
    if(data->flags&2) {
        AptValue *thrown=p->mpThrownValue;
        if(thrown) { thrown->AddRef();p->mpThrownValue->Release();p->mpThrownValue=0; }
        p->runStream((const unsigned char *)(data+1)+data->trySize+data->catchSize,c->pCurrentContext,data->finallySize,c->pParentCharacter);
        if(thrown && !p->mpThrownValue) { thrown->AddRef();p->mpThrownValue=thrown;thrown->Release(); }
    }
    unsigned int nPostStackSize=p->stack.GetSize();
    if (nPostStackSize>nPreStackSize) p->stack.rva006E3AA0(nPostStackSize-nPreStackSize);
    if((unsigned int)p->stack.GetSize()!=nPreStackSize) {
        g_bfmeAptAssertAtE17734("(uint32_t)pInterpreter->stack.GetSize() == nPreStackSize","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x2599);
        if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
}

#pragma comment(linker, "/alternatename:?g_bfmeFrameStackAtE1835C@@3PAVAptFrameStack@@A=?spFrameStack@AptScriptFunctionBase@@2PAVAptFrameStack@@A")

// Native 6FDA40..6FDC29; buffer capacity260 inferred from frame allocation,
// exact declared source bound within alignment padding is not independently known.
// Load6D1F80 has native-supported original MAP ABI but remains a link backlog.
extern "C" char *__cdecl strcpy(char *,const char *);
#pragma intrinsic(strcpy)
static __forceinline bool bfmeIsFSCommand(const char *s) { return strncmp(s,g_bfmeAptFSCommandAtDDC920,strlen(g_bfmeAptFSCommandAtDDC920))==0; }
class AptLinker { public: void Load(const EAStringC &,EAStringC); };
extern AptLinker *g_bfmeAptLinkerAtE176F8;
void AptActionInterpreter::_FunctionAptActionGetUrl(AptActionInterpreter *const p,LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    struct Data { const char *szUrl,*szWin; };
    const Data *data=(const Data *)c->pInstruction;
    c->pInstruction+=sizeof(Data);
    if (bfmeIsFSCommand(data->szUrl)) p->doFSCommand(data->szUrl,data->szWin);
    else {
        char buffer[260];
        strcpy(buffer,data->szUrl);
        int nLength=strlen(buffer);
        if ((buffer[nLength-1]=='f' || buffer[nLength-1]=='F') &&
            (buffer[nLength-2]=='w' || buffer[nLength-2]=='W') &&
            (buffer[nLength-3]=='s' || buffer[nLength-3]=='S') && buffer[nLength-4]=='.') {
            buffer[nLength-4]=0;
            g_bfmeAptLinkerAtE176F8->Load(EAStringC(buffer),EAStringC(data->szWin));
        } else if (nLength==0) g_bfmeAptLinkerAtE176F8->Load(EAStringC(""),EAStringC(data->szWin));
        else Rva006CC110Log(4,"not loading non-swf file: '%s'\n",buffer);
    }
}

// Native877B through708FAC. Retail tests uppercase W/S at n-1 as written;
// later donor fixed this suffix bug. loadVariables706370 remains unrowed.
void AptActionInterpreter::_FunctionAptActionGetUrl2(AptActionInterpreter *const p,LocalContextT *const c)
{
    AptValue *a=p->stack.At(0),*b=p->stack.At(1);
    EAStringC sa,sb;
    b->toString(sb);
    if(bfmeIsFSCommand(sb.rva00620090())) { a->toString(sa);p->doFSCommand(sb.rva00620090(),sa.rva00620090()); }
    else {
        int n=sb.rva006D3750();EAStringC buf;AptValue *context=0;
        if(n==0 || ((sb.GetAt(n-1)=='f'||sb.GetAt(n-1)=='F') && (sb.GetAt(n-2)=='w'||sb.GetAt(n-1)=='W') && (sb.GetAt(n-3)=='s'||sb.GetAt(n-1)=='S') && sb.GetAt(n-4)=='.')) {
            a->toString(sa);buf=sb;
            if((int)buf.rva006D3750()>=4) buf.rva006D54B0(buf.rva006D3750()-4,4);
            AptValue *v=p->getVariable((AptValue *)c->pCurrentContext,c->pCurWith,&sa);
            if(v->isCIH()) getName(v->c_cih(),sa);
            p->stack.Pop(2);g_bfmeAptLinkerAtE176F8->Load(buf,sa);return;
        } else {
            if(a->isString()) context=p->getVariable((AptValue *)c->pCurrentContext,c->pCurWith,a->c_string()->GetInternalString(),1);
            else context=a;
            p->loadVariables(context,c->pCurWith,&sb);
        }
    }
    p->stack.Pop(2);
}

#pragma comment(linker, "/alternatename:?c_cih@AptValue@@QBEPAVAptCIH@@_N@Z=?rva006DCF60@BfmeAptValue006DCD20@@QAEPAV1@_N@Z")
#pragma comment(linker, "/alternatename:?getName@AptActionInterpreter@@SAXPAVAptCIH@@AAVEAStringC@@@Z=?rva006ffce0@@YAXPAVAptValue@@AAVEAStringC@@@Z")

// CallFunction: original dispatch slot and native 707910..707B77 (615 bytes).
// Same-TU parser definitions above prove its output pointers do not escape,
// allowing the original argument-slot reuse in this handler.
void AptActionInterpreter::_FunctionAptActionCallFunction(AptActionInterpreter *const p,LocalContextT *const c)
{
    AptValue *name=p->stack.At(0);
    AptValue *params=p->stack.At(1);
    EAStringC sVar;
    int nParams=params->toInteger();
    AptValue *function=0;
    AptValue *context=0;
    if(name->isArray()) name=name->c_array()->get(0);
    if(name->isString()) {
        rva006FEC00((int)c->pCurrentContext,(int)c->pCurWith,name->c_string()->GetInternalString(),(int *)&context,&sVar);
        function=p->getVariable(context,c->pCurWith,&sVar,1);
    } else function=name;
    function->AddRef();
    name=0; params=0;
    p->stack.Pop(2);
    p->debugCallStack.Push(new Rva006FBDB0(sVar.rva00620090(),(int)(context?context:(AptValue *)c->pCurrentContext),0x4000000));
    p->callFunction(context?context:(AptValue *)c->pCurrentContext,function,nParams);
    p->debugCallStack.Pop();
    function->Release();
}

// Original Apt.h 5baf9703 callbacks; PC slots E1775C/E17760 each4B start zero.
// The old TO_STRING path below passes null on non-string, exactly as retail does.
AptValue *(__cdecl *g_bfmeAptLoadVariablesAtE1775C)(const char *)=0;
AptValue *(__cdecl *g_bfmeAptLoadVariablesNullAtE17760)()=0;
void AptActionInterpreter::loadVariables(AptValue *context,AptValue *with,const EAStringC *url)
{
    AptValue *value=0;
    if(!url) {
        if(!g_bfmeAptLoadVariablesNullAtE17760) {
            g_bfmeAptAssertAtE17734("gAptFuncs.pfnLoadVariablesNULL","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x3A3);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        value=g_bfmeAptLoadVariablesNullAtE17760();
    } else value=g_bfmeAptLoadVariablesAtE1775C(url->rva00620090());
    EAStringC *text=0;
    if(value->isString()) text=&value->c_string()->str;
    else value->toString(*text);
    const char *cur=text->rva00620090();
    EAStringC key,val;
    for(;;) {
        cur=urlDecode(cur,key,val);
        if(!cur) break;
        if(key.IsEmpty()) { Rva006CC110Log(4,"loadVariable for '%s' returned empty variable name\n",url->rva00620090());continue; }
        AptString *variable=AptString::Create();
        variable->str=val;
        setVariable(context,with,&key,variable,1);
    }
}

void rva006FD630(EAStringC *);
const char *AptActionInterpreter::urlDecode(const char *url,EAStringC &key,EAStringC &value)
{
    const char *cur=url,*equals=0;
    key.rva006D3470();value.rva006D3470();
    for(;cur && *cur && *cur!='&';++cur) if(*cur=='=') equals=cur;
    if(equals) {
        key.Append(url,equals-url);rva006FD630(&key);++equals;
        value.Append(equals,cur-equals);rva006FD630(&value);
        if(*cur=='&') ++cur;
    } else cur=0;
    return cur;
}

#pragma comment(linker, "/alternatename:?Append@EAStringC@@QAEAAV1@QBDI@Z=?bfmeAppendVKG@BfmeBufVKG@@QAEPAV1@PBDI@Z")

#define RUNTIME_ASSERT(e,line,text) do { if(!(e)) { g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",line);if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 } } } while(0)
const unsigned char *AptActionInterpreter::runStream(const unsigned char *stream,AptCIH *current,int maximum,AptCharacterInst *parent)
{
    if(maximum==-1) {
        if(thisStack.count>=thisStack.capacity) {
            g_bfmeAptAssertAtE17734("m_nElements < m_nSize","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x76);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        thisStack.items[thisStack.count++]=(AptValue *)current;((AptValue *)current)->AddRef();
    }
    LocalContextT context;
    context.pCurrentContext=current;context.pCurWith=0;context.pInstruction=stream;context.pRemoveWithAt=0;
    context.pSuper=getVariable((AptValue *)current,0,Rva0070B4F0GetString(0xA0));
    context.bEncounteredReturn=false;context.pParentCharacter=parent;
    int previous=mnStackFrameBase;mnStackFrameBase=stack.GetSize();int before=mnStackFrameBase;
    while(!mpThrownValue) {
        RUNTIME_ASSERT(!context.pRemoveWithAt || context.pInstruction <= context.pRemoveWithAt,0xB43,"!context.pRemoveWithAt || context.pInstruction <= context.pRemoveWithAt");
        if(context.pRemoveWithAt && context.pInstruction==context.pRemoveWithAt) { context.pCurWith->Release();context.pCurWith=0;context.pRemoveWithAt=0; }
        int action=*context.pInstruction++;
        if(context.bEncounteredReturn) break;
        if(maximum>=0 && context.pInstruction-stream>maximum) { stack.Push(gpUndefinedValue);break; }
        else if(!action) { if(maximum>=0) stack.Push(gpUndefinedValue);break; }
        RUNTIME_ASSERT(current == 0 || ((AptValue *)current)->getRefCount() > 0,0xB64,"pCurrentContext == NULL || pCurrentContext->getRefCount() > 0");
        RUNTIME_ASSERT(sGlobalTable[action].mCheckAlignment == action,0xB67,"sGlobalTable[eAction].mCheckAlignment == eAction");
        sGlobalTable[action].mFunctionPointer(this,&context);
        int after=stack.GetSize();RUNTIME_ASSERT(after >= before,0xB6F,"nStackSizeCurrent >= nStackSizePre");
    }
    int after=stack.GetSize();
    if(maximum>=0 && after>mnStackFrameBase) stack.rva006E3AA0(after-mnStackFrameBase-1);
    else if(after>mnStackFrameBase) stack.rva006E3AA0(after-mnStackFrameBase);
    mnStackFrameBase=previous;
    if(maximum==-1) {
        if(thisStack.count<=0) {
            g_bfmeAptAssertAtE17734("size() > 0","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",0x7D);
            if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        thisStack.items[thisStack.count-1]->Release();--thisStack.count;
    }
    int size=stack.GetSize();bool release=false;
    if(!size) release=true;else if(size==1 && stack.rva006FE580(0)==gpUndefinedValue) release=true;
    if(release && g_releaseVectorAtE17710->GetNumValues()!=0) g_releaseVectorAtE17710->ReleaseValues();
    return context.pInstruction;
}

class Rva00700170; struct Rva00702B40Payload;
void rva00702b40(Rva00700170 *,const Rva00702B40Payload *);
void DX8_Assert();
// sGlobalTable name is independently present in original Godfather Jan26 MAP.
// All185 opcode/pointer records independently read at native RVA9DC980.
// Unused entries preserve the native -1/null pair; folded providers retain existing names.
AptActionInterpreter::FunctionTable AptActionInterpreter::sGlobalTable[185] = {
    {0,&_FunctionAptActionEnd},
    {-1,0},
    {-1,0},
    {-1,0},
    {4,&_FunctionAptActionNextFrame},
    {5,&_FunctionAptActionPrevFrame},
    {6,&_FunctionAptActionPlay},
    {7,&_FunctionAptActionStop},
    {8,&_FunctionAptActionToggleQuality},
    {9,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&DX8_Assert},
    {10,&_FunctionAptActionAdd},
    {11,&_FunctionAptActionSubtract},
    {12,&_FunctionAptActionMultiply},
    {13,&_FunctionAptActionDivide},
    {14,&_FunctionAptActionEquals},
    {15,&_FunctionAptActionLessThan},
    {16,&_FunctionAptActionAnd},
    {17,&_FunctionAptActionOr},
    {18,&_FunctionAptActionNot},
    {19,&_FunctionAptActionStringEquals},
    {20,&_FunctionAptActionStringLength},
    {21,&_FunctionAptActionSubString},
    {-1,0},
    {23,&_FunctionAptActionPop},
    {24,&_FunctionAptActionToInteger},
    {-1,0},
    {-1,0},
    {-1,0},
    {28,&_FunctionAptActionGetVariable},
    {29,&_FunctionAptActionSetVariable},
    {-1,0},
    {-1,0},
    {32,&_FunctionAptActionSetTarget2},
    {33,&_FunctionAptActionStringAdd},
    {34,&_FunctionAptActionGetProperty},
    {35,&_FunctionAptActionSetProperty},
    {36,&_FunctionAptActionCloneSprite},
    {37,&_FunctionAptActionRemoveSprite},
    {38,&_FunctionAptActionTrace},
    {39,&_FunctionAptActionStartDragMovie},
    {40,&_FunctionAptActionStopDragMovie},
    {41,&_FunctionAptActionStringLessThan},
    {42,&_FunctionAptActionThrow},
    {43,&_FunctionAptActionCastOp},
    {44,&_FunctionAptActionImplementsOp},
    {-1,0},
    {-1,0},
    {-1,0},
    {48,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&_FunctionAptActionRandom},
    {49,&_FunctionAptActionMBLength},
    {50,&_FunctionAptActionCharToAscii},
    {51,&_FunctionAptActionAsciiToChar},
    {52,&_FunctionAptActionGetTimer},
    {53,&_FunctionAptActionMBSubString},
    {54,&_FunctionAptActionMBCharToAscii},
    {55,&_FunctionAptActionMBAsciiToChar},
    {-1,0},
    {-1,0},
    {58,&_FunctionAptActionDelete},
    {59,&_FunctionAptActionDelete2},
    {60,&_FunctionAptActionDefineLocal},
    {61,&_FunctionAptActionCallFunction},
    {62,&_FunctionAptActionReturn},
    {63,&_FunctionAptActionModulo},
    {64,&_FunctionAptActionNewObject},
    {65,&_FunctionAptActionDefineLocal2},
    {66,&_FunctionAptActionInitArray},
    {67,&_FunctionAptActionInitObject},
    {68,&_FunctionAptActionTypeOf},
    {69,&_FunctionAptActionTargetPath},
    {70,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&rva00702b40},
    {71,&_FunctionAptActionAdd2},
    {72,&_FunctionAptActionLessThan2},
    {73,&_FunctionAptActionEquals2},
    {74,&_FunctionAptActionToNumber},
    {75,&_FunctionAptActionToString},
    {76,&_FunctionAptActionPushDuplicate},
    {77,&_FunctionAptActionStackSwap},
    {78,&_FunctionAptActionGetMember},
    {79,&_FunctionAptActionSetMember},
    {80,&_FunctionAptActionIncrement},
    {81,&_FunctionAptActionDecrement},
    {82,&_FunctionAptActionCallMethod},
    {83,&_FunctionAptActionNewMethod},
    {84,&_FunctionAptActionInstanceOf},
    {85,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&rva00702b40},
    {86,&_FunctionAptActionPushThis},
    {-1,0},
    {88,&_FunctionAptActionPushGlobal},
    {89,&_FunctionAptActionPush0},
    {90,&_FunctionAptActionPush1},
    {91,&_FunctionAptActionCallFuncAndPop},
    {92,&_FunctionAptActionCallFuncSetVar},
    {93,&_FunctionAptActionCallMethodPop},
    {94,&_FunctionAptActionCallMethodSetVar},
    {-1,0},
    {96,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&_FunctionAptActionBitAnd},
    {97,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&_FunctionAptActionBitOr},
    {98,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&_FunctionAptActionBitXor},
    {99,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&_FunctionAptActionBitLShift},
    {100,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&_FunctionAptActionBitRShift},
    {101,&_FunctionAptActionBitURShift},
    {102,&_FunctionAptActionStrictEquals},
    {103,&_FunctionAptActionGreater},
    {-1,0},
    {105,&_FunctionAptActionExtends},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {112,&_FunctionAptActionPushThisVariable},
    {113,&_FunctionAptActionPushGlobalVariable},
    {114,&_FunctionAptActionPushZeroSetVar},
    {115,&_FunctionAptActionPushTrue},
    {116,&_FunctionAptActionPushFalse},
    {117,&_FunctionAptActionPushUndefined},
    {118,&_FunctionAptActionPushUndefined},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {129,&_FunctionAptActionGotoFrame},
    {-1,0},
    {131,&_FunctionAptActionGetUrl},
    {-1,0},
    {-1,0},
    {-1,0},
    {135,&_FunctionAptActionStoreRegister},
    {136,&_FunctionAptActionDefineDictionary},
    {-1,0},
    {138,(void (__cdecl *)(AptActionInterpreter *const,LocalContextT *const))&DX8_Assert},
    {139,&_FunctionAptActionSetTarget},
    {140,&_FunctionAptActionGotoLabel},
    {-1,0},
    {142,&_FunctionAptActionDefineFunction2},
    {143,&_FunctionAptActionTry},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {148,&_FunctionAptActionWith},
    {-1,0},
    {150,&_FunctionAptActionPush},
    {-1,0},
    {-1,0},
    {153,&_FunctionAptActionBranchAlways},
    {154,&_FunctionAptActionGetUrl2},
    {155,&_FunctionAptActionDefineFunction},
    {-1,0},
    {157,&_FunctionAptActionBranchIfTrue},
    {158,&_FunctionAptActionCallFrame},
    {159,&_FunctionAptActionGotoFrame2},
    {-1,0},
    {161,&_FunctionAptActionPushString},
    {162,&_FunctionAptActionPushStringDictByte},
    {163,&_FunctionAptActionPushStringDictWord},
    {164,&_FunctionAptActionPushStringGetVar},
    {165,&_FunctionAptActionPushStringGetMember},
    {166,&_FunctionAptActionPushStringSetVar},
    {167,&_FunctionAptActionPushStringSetMember},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {-1,0},
    {174,&_FunctionAptActionStringDictByteGetVar},
    {175,&_FunctionAptActionStringDictByteGetMember},
    {176,&_FunctionAptActionDictCallFuncPop},
    {177,&_FunctionAptActionDictCallFuncSetVar},
    {178,&_FunctionAptActionDictCallMethodPop},
    {179,&_FunctionAptActionDictCallMethodSetVar},
    {180,&_FunctionAptActionPushFloat},
    {181,&_FunctionAptActionPushByte},
    {182,&_FunctionAptActionPushWord},
    {183,&_FunctionAptActionPushDWord},
    {184,&_FunctionAptActionBranchIfFalse},
};
#pragma comment(linker, "/alternatename:?rva006FE580@AptBasePtrStack@@QAEPAVAptValue@@H@Z=?At@AptBasePtrStack@@QAEPAVBfmeAptValue006DCD20@@H@Z")

// Original MAP overload and later interpreter source identify this234B body.
// PC706950..706A3A verifies pending value+60 and debug stack+34/38/3C.
void AptActionInterpreter::CleanupAfterExecution(void *saved,AptActionSetup *setup) {
 AptValue *pending=mpThrownValue;
 if(pending) {
  EAStringC name;pending->toString(name);
  Rva006CC110Log(3,"<WARNING> Actionscript un-caught exception encountered during \"%s\"\n",setup->name);
  Rva006CC110Log(3,"<WARNING> Actionscript error message: \"%s\"\n",name.rva00620090());
  mpThrownValue->Release();mpThrownValue=0;
 }
 rva007097B0(saved);
 debugCallStack.Pop();
}


// Later _AptActions.h debug-record constructor assigns name/context/type.
// Native6FBD40..6FBDAE uses the older by-value EAStringC ABI and12B record.
Rva006FBDB0::Rva006FBDB0(EAStringC name,int value,int type) {
    *(EAStringC *)this=name;
    context=value;
    action=type;
}

// Original MAP and source identify PrepareForExecution with saved-state return.
// Native700090..70016E validates setup16B and debug record allocation.
void *AptActionInterpreter::PrepareForExecution(AptActionSetup *setup) {
 if(mpThrownValue) {
  g_bfmeAptAssertAtE17734("!hasThrownValue()","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x875);
  if(g_bfmeAptBreakOnAssertAtDDC01C){__asm int 3}
 }
 debugCallStack.Push(new Rva006FBDB0(setup->name,(int)setup->value,setup->action));
 return AptPushStaticData();
}

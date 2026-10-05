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
class AptArray;
class AptNativeHash;
class AptCIH;
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
    AptCIH *c_cih(bool=false);
    AptArray *c_array() const;
    bool isArray() const;
    bool isExtern() const;
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
class AptCIH;
struct AptCharacterInst;
class EAStringC { void *mpData; public: EAStringC &Rva006D4F00Append(const EAStringC &); EAStringC &Rva006D50A0Append(const char *); EAStringC(unsigned int,unsigned int); EAStringC rva006D5ED0(int) const; EAStringC rva006d5f30(int,int) const; void rva006D3470(); bool IsEqualTo(const EAStringC *) const; const char *rva00620090() const; int rva006d6070(const char *,int=0); EAStringC(); unsigned int rva006D3750() const; EAStringC(const char *); ~EAStringC(); EAStringC &operator=(const EAStringC &); };
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
    int count,capacity;
    AptValue **items;
};

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
    AptBasePtrStack stack;
    unsigned char m_otherStacksAndDebugData[0x40-12];
    AptConstantPool constantPool;
    unsigned char m_betweenPoolAndFrameBase[0x64-0x48];
    // Original Godfather debug/release field100; native Pop reads +0x64.
    int mnStackFrameBase;
    bool setVariable(AptValue *, AptValue *, const EAStringC *, AptValue *, int=1, int=1, int=0);
    AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int=1, int=1, int=0);
private:
#define HANDLER(n) static void _FunctionAptAction##n(AptActionInterpreter *const,LocalContextT *const)
    HANDLER(GotoFrame); HANDLER(StopDragMovie); HANDLER(Play); HANDLER(Stop); HANDLER(NextFrame); HANDLER(PrevFrame);
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
    HANDLER(CallFunction); HANDLER(CallMethod); HANDLER(With);
    HANDLER(CallFuncAndPop); HANDLER(CallFuncSetVar); HANDLER(CallMethodPop); HANDLER(CallMethodSetVar); HANDLER(DictCallFuncPop); HANDLER(DictCallFuncSetVar); HANDLER(DictCallMethodPop); HANDLER(DictCallMethodSetVar);
    HANDLER(ToInteger); HANDLER(StringLength); HANDLER(GetVariable);
    HANDLER(InitArray);
    HANDLER(GetProperty); HANDLER(SetProperty);
    HANDLER(GetTimer);
    HANDLER(Trace);
    HANDLER(Greater); HANDLER(LessThan2);
    HANDLER(SubString); HANDLER(AsciiToChar);
    HANDLER(Delete); HANDLER(Delete2);
    HANDLER(StringEquals);
    HANDLER(ToNumber); HANDLER(ToString);
    HANDLER(SetVariable); HANDLER(GetMember); HANDLER(SetMember);
    HANDLER(PushStringGetVar); HANDLER(PushStringGetMember); HANDLER(PushStringSetVar); HANDLER(PushStringSetMember);
    HANDLER(End); HANDLER(ToggleQuality); HANDLER(StringLessThan); HANDLER(MBLength); HANDLER(CharToAscii); HANDLER(MBSubString); HANDLER(MBCharToAscii); HANDLER(MBAsciiToChar); HANDLER(BitURShift);
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

// Default construction folds with the existing empty-string reset provider.
#pragma comment(linker, "/alternatename:??0EAStringC@@QAE@XZ=?clear@EAStringC@@QAEAAV1@XZ")

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

#pragma comment(linker, "/alternatename:?set@AptArray@@QAEXHPAVAptValue@@@Z=?rva006D95E0@BfmeAptValue006DCD20@@QAEXHPAV1@@Z")

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
struct AptSpriteInstBase { unsigned char prefix[0x18]; int mnFrame; int mnObjectClipActions:24; unsigned int mbJustLoaded:1; unsigned int mbIsPlaying:1; unsigned int mnIsCustomControl:2; };
class AptCIH : public AptValue {
public:
    unsigned char prefix[0x4C-8];
    void *mpCharacterInst;
    bool IsLevelInst() const;
    AptSpriteInstBase *GetSpriteInstBase() const;
    bool IsSpriteInstBase() const;
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

class Rva006E34D0 { public: unsigned char prefix[0x44]; AptValue *mpDragMC; };
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

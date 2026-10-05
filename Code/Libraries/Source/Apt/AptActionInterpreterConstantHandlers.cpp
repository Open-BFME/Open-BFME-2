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
// AptValue's opaque8-byte prefix is used solely to place AptString::str at+8.
// PushThis/PushGlobal push pooled NAME strings, not the context objects.
// Slots75(NULL) and76(Undefined) share705320; row it only once as Undefined.
class AptString;
class AptValue { char m_valuePrefix[8]; public: AptString *c_string() const; };
class AptCIH;
struct AptCharacterInst;
class EAStringC { void *mpData; public: EAStringC(const char *); ~EAStringC(); EAStringC &operator=(const EAStringC &); };
class AptString : public AptValue { public: static AptString *Create(); EAStringC str; };
class AptInteger { public: static AptValue *Create(int); };
class AptBoolean { public: static AptValue *Create(bool); };
AptValue *Rva008A4EA0MakeFloat(float);
EAStringC *Rva0070B4F0GetString(int);
extern EAStringC g_eaStringAtE177D4;
extern AptValue *gpUndefinedValue;
extern AptValue *gpGlobalGlobalObject;
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
    void Push(AptValue *);
    void PushNoInc(AptValue *);
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
    AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int=1, int=1, int=0);
private:
#define HANDLER(n) static void _FunctionAptAction##n(AptActionInterpreter *const,LocalContextT *const)
    HANDLER(PushFloat); HANDLER(PushByte); HANDLER(PushWord); HANDLER(PushDWord);
    HANDLER(Return); HANDLER(DefineDictionary); HANDLER(PushStringDictByte); HANDLER(PushStringDictWord);
    HANDLER(PushThis); HANDLER(PushGlobal); HANDLER(Push0); HANDLER(Push1);
    HANDLER(PushTrue); HANDLER(PushFalse); HANDLER(PushUndefined);
    HANDLER(PushThisVariable); HANDLER(PushGlobalVariable); HANDLER(PushZeroSetVar);
    HANDLER(PushString); HANDLER(StringDictByteGetVar); HANDLER(StringDictByteGetMember);
    HANDLER(PushDuplicate); HANDLER(StackSwap); HANDLER(StoreRegister);
    HANDLER(SetVariable); HANDLER(GetMember); HANDLER(SetMember);
    HANDLER(PushStringGetVar); HANDLER(PushStringGetMember); HANDLER(PushStringSetVar); HANDLER(PushStringSetMember);
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

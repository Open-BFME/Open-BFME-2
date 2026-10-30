// cl: /O2 /MD /EHsc
// Native opcode-table entries7049B0/86 and706070/453 retain their PDB
// private static signatures and whole extents. Body provenance is the existing
// ConstantHandlers TU; only register stores use the verified canonical
// AptScriptFunctionBase::SetRegisterValue709F70 instead of its retired name.
// Canonical spFrameStack replaces the old frame-global linker alias.
// Native fields stack0/4/8, currentFunction30, thrownValue60 and28-byte
// LocalContext are the existing target evidence. Untouched storage stays opaque.
// This is a caller identity repair, with no new coverage, pin or donor identity.
#include "AptObject/AptScriptFunction.h"
#include <stddef.h>
struct AptCharacterInst;
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
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
class BfmeAptValue006DCD20;
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

class AptBasePtrStack
{
public:
    int count, capacity;
    AptValue **items;
    BfmeAptValue006DCD20 *At(int);
    void rva006E3AA0(int);
    void rva006FE050(int);
    void rva006FE920();
    AptValue *rva006FE580(int);
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

    __forceinline AptValue *At(int nPos) const
    {
        if (!(count-nPos>0)) {
            g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptBasePtrStack.h", 0x10A);
            if (g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
        }
        return items[count-nPos-1];
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
    void Push(AptValue *);
    __forceinline int GetSize() const { return count; }
};
// Keep the already rowed neutral150B frame-publisher provider spelling.
// Its canonical class reconciliation is separate from this register repair.
class Rva8D0D80Result { public: void rva006FBED0(); };
struct AptCharacterInst;
template<class T> struct AptValuePtrStack
{
    int count, capacity;
    AptValue **items;
    void push(AptValue *);
    void pop();
    __declspec(dllimport) __forceinline void popInline()
    {
        APT_ASSERT(count > 0, "size() > 0",
                   "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x7D)
        items[count - 1]->Release();
        --count;
    }
};


struct AptActionInterpreter
{
public:
	struct DebugCallStackInfo_t;
	struct LocalContextT { const unsigned char *pInstruction; AptCIH *pCurrentContext; AptValue *pCurWith; const unsigned char *pRemoveWithAt; AptValue *pSuper; bool bEncounteredReturn; AptCharacterInst *pParentCharacter; };
	const unsigned char *runStream(const unsigned char *, AptCIH *, int, struct AptCharacterInst *);
	AptValue *getVariable(AptValue *, AptValue *, const EAStringC *, int=1, int=1, int=0);
	void callFunction(AptValue *, AptValue *, int);
private:
	static AptValue *getObject(AptValue *, AptValue *, const EAStringC *);
	AptObject *_createObject(AptValue *, AptValue *, const EAStringC *, int, bool);
public:
	bool setVariable(AptValue *,AptValue *,const EAStringC *,AptValue *,int=1,int=1,int=0);
private:
	static void _FunctionAptActionDefineLocal(AptActionInterpreter *const,LocalContextT *const);
	static void _FunctionAptActionDefineLocal2(AptActionInterpreter *const,LocalContextT *const);
	static void _FunctionAptActionStoreRegister(AptActionInterpreter *const, LocalContextT *const);
	static void _FunctionAptActionTry(AptActionInterpreter *const, LocalContextT *const);
	static void _FunctionAptActionDefineFunction(AptActionInterpreter *const,LocalContextT *const);
	static void _FunctionAptActionDefineFunction2(AptActionInterpreter *const,LocalContextT *const);
public:
	AptBasePtrStack stack; // +0x00
	char m_pad0C[0x18];
	AptValuePtrStack<AptValue> thisStack; // +0x24 +0x24
	AptScriptFunctionBase *mpCurrentFunction; // +0x30 +0x30
	char m_pad34[0xC];
	AptConstantPool constantPool; // +0x40 +0x40
	char m_pad48[0x18];
	AptValue *mpThrownValue; // +0x60 +0x60
	int mnStackFrameBase; // +0x64
};
typedef char RegisterStackSize[sizeof(AptBasePtrStack)==12 ? 1 : -1];
typedef char RegisterContextSize[sizeof(AptActionInterpreter::LocalContextT)==28 ? 1 : -1];
typedef char RegisterFunctionOffset[offsetof(AptActionInterpreter,mpCurrentFunction)==0x30 ? 1 : -1];
typedef char RegisterThrownOffset[offsetof(AptActionInterpreter,mpThrownValue)==0x60 ? 1 : -1];

void AptActionInterpreter::_FunctionAptActionStoreRegister(AptActionInterpreter *const interpreter, LocalContextT *const context)
{
    context->pInstruction=(const unsigned char *)(((unsigned int)context->pInstruction+3)&~3U);
    const int *data=(const int *)context->pInstruction;
    context->pInstruction+=4;
    AptScriptFunctionBase::SetRegisterValue(*data,static_cast<const AptBasePtrStack &>(interpreter->stack).At(0));
}

// Target 706070..706234; donor supplies semantics; native proves +30 function,
// +8 frame hash and this 20-byte action header. runStream 7002C0 has a verified provider below.
struct RuntimeTryBlock { unsigned int trySize,catchSize,finallySize; unsigned char flags; unsigned char unused[2]; unsigned char caughtReg; const char *caughtName; };
void AptActionInterpreter::_FunctionAptActionTry(AptActionInterpreter *const aptActionInterpreter,LocalContextT *const localContextT)
{
    unsigned int nPreStackSize=aptActionInterpreter->stack.GetSize();
    localContextT->pInstruction=(const unsigned char *)(((unsigned int)localContextT->pInstruction+3)&~3U);
    const RuntimeTryBlock *data=(const RuntimeTryBlock *)localContextT->pInstruction;
    localContextT->pInstruction+=sizeof(RuntimeTryBlock);
    localContextT->pInstruction+=data->trySize;localContextT->pInstruction+=data->catchSize;localContextT->pInstruction+=data->finallySize;
    aptActionInterpreter->runStream((const unsigned char *)(data+1),localContextT->pCurrentContext,data->trySize,localContextT->pParentCharacter);
    if (aptActionInterpreter->mpThrownValue && (data->flags&1)) {
        AptValue *thrown=aptActionInterpreter->mpThrownValue;
        if (data->flags&4) AptScriptFunctionBase::SetRegisterValue(data->caughtReg,thrown);
        else {
            EAStringC param(data->caughtName);
            if(aptActionInterpreter->mpCurrentFunction) {
                if(!AptScriptFunctionBase::spFrameStack) ((Rva8D0D80Result *)aptActionInterpreter->mpCurrentFunction)->rva006FBED0();
                ((AptNativeHash *)((unsigned char *)AptScriptFunctionBase::spFrameStack+8))->Set(&param,thrown);
            } else aptActionInterpreter->setVariable((AptValue *)localContextT->pCurrentContext,0,&param,thrown);
        }
        aptActionInterpreter->mpThrownValue->Release();aptActionInterpreter->mpThrownValue=0;
        aptActionInterpreter->runStream((const unsigned char *)(data+1)+data->trySize,localContextT->pCurrentContext,data->catchSize,localContextT->pParentCharacter);
    }
    if(data->flags&2) {
        AptValue *thrown=aptActionInterpreter->mpThrownValue;
        if(thrown) { thrown->AddRef();aptActionInterpreter->mpThrownValue->Release();aptActionInterpreter->mpThrownValue=0; }
        aptActionInterpreter->runStream((const unsigned char *)(data+1)+data->trySize+data->catchSize,localContextT->pCurrentContext,data->finallySize,localContextT->pParentCharacter);
        if(thrown && !aptActionInterpreter->mpThrownValue) { thrown->AddRef();aptActionInterpreter->mpThrownValue=thrown;thrown->Release(); }
    }
    unsigned int nPostStackSize=aptActionInterpreter->stack.GetSize();
    if (nPostStackSize>nPreStackSize) aptActionInterpreter->stack.rva006E3AA0(nPostStackSize-nPreStackSize);
    if((unsigned int)aptActionInterpreter->stack.GetSize()!=nPreStackSize) {
        g_bfmeAptAssertAtE17734("(uint32_t)pInterpreter->stack.GetSize() == nPreStackSize","C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp",0x2599);
        if(g_bfmeAptBreakOnAssertAtDDC01C) { __asm int 3 }
    }
}

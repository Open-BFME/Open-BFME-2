// cl: /MD /EHsc
// Original Redwood6 PDB establishes handler ABI and record sizes24/28.
// PC dispatch9DC980 and complete704B50/704C60 bodies verify identity, offsets,
// allocation size52 and constructor calls. Later0cbfd5f746c89504 is body guide.
// DefineFunction1 retains the native early name lifetime and reassignment.
#include "AptObject/AptScriptFunction.h"
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
__forceinline void *AptScriptFunction1::operator new(unsigned int size) { return g_pChainBlockAllocatorF4->allocBlock(size); }
__forceinline void AptScriptFunction1::operator delete(void *v,unsigned int size) { g_pChainBlockAllocatorF4->freeBlock(v,size); }
__forceinline void *AptScriptFunction2::operator new(unsigned int size) { return g_pChainBlockAllocatorF4->allocBlock(size); }
__forceinline void AptScriptFunction2::operator delete(void *v,unsigned int size) { g_pChainBlockAllocatorF4->freeBlock(v,size); }
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
struct AptCharacterInst;
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
#pragma comment(linker, "/alternatename:?Push@AptBasePtrStack@@QAEXPAVAptValue@@@Z=?Push@AptBasePtrStack@@QAEXPAVBfmeAptValue006DCD20@@@Z")
void AptActionInterpreter::_FunctionAptActionDefineFunction2(AptActionInterpreter *const p,LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const AptAction_DefineFunction2 *data=(const AptAction_DefineFunction2 *)c->pInstruction;
    c->pInstruction+=sizeof(AptAction_DefineFunction2);
    c->pInstruction+=data->nCodeSize;
    data->constantPool=p->constantPool;
    AptCIH *cih=c->pCurrentContext;
    AptScriptFunction2 *fn=new AptScriptFunction2(p->mpCurrentFunction,data,cih);
    if(data->szName[0]==0) p->stack.Push(fn);
    else {
        EAStringC name(data->szName);
        p->setVariable((AptValue *)c->pCurrentContext,c->pCurWith,&name,fn,1);
    }
}
void AptActionInterpreter::_FunctionAptActionDefineFunction(AptActionInterpreter *const p,LocalContextT *const c)
{
    c->pInstruction=(const unsigned char *)(((unsigned int)c->pInstruction+3)&~3U);
    const AptAction_DefineFunction *data=(const AptAction_DefineFunction *)c->pInstruction;
    c->pInstruction+=sizeof(AptAction_DefineFunction);
    c->pInstruction+=data->nCodeSize;
    data->constantPool=p->constantPool;
    EAStringC name(data->szName);
    AptCIH *cih=c->pCurrentContext;
    AptScriptFunction1 *fn=new AptScriptFunction1(p->mpCurrentFunction,data,cih);
    if(data->szName[0]==0) p->stack.Push(fn);
    else {
        name=data->szName;
        p->setVariable((AptValue *)c->pCurrentContext,c->pCurWith,&name,fn,1);
    }
}

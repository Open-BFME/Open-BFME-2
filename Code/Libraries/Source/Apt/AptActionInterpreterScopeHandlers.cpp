// cl: /O2 /MD /EHsc
// PC dispatch slot3C/41 and Redwood6 private static signatures identify these
// handlers. Later AptActionInterpreter.cpp supplies the semantic reference;
// native instructions independently establish interpreter current function+30,
// static frame E1835C, creator scope+28 and native hash at frame+8.
// This TU includes the canonical class rather than copying its private layout.
#include "AptObject/AptScriptFunction.h"
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
class EAStringC { void *mpData; };
class AptString : public AptValue { public: EAStringC str; __forceinline EAStringC *GetInternalString() { return &str; } };
extern AptValue *gpUndefinedValue;
class Rva8D0D80String;
class Rva8D0D80Value;
class Rva8D0D80Table { public: void add(Rva8D0D80String *,Rva8D0D80Value *); };
class BfmeTab1024 { public: int bfmeFind1024(int); };
class AptBasePtrStack
{
public:
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
    int count,capacity;
    AptValue **items;
};

struct AptCharacterInst;
struct AptActionInterpreter {
    struct LocalContextT { const unsigned char *pInstruction; AptCIH *pCurrentContext; AptValue *pCurWith; const unsigned char *pRemoveWithAt; AptValue *pSuper; bool bEncounteredReturn; AptCharacterInst *pParentCharacter; };
    AptBasePtrStack stack;
    char pad[0x30-12];
    AptScriptFunctionBase *mpCurrentFunction;
    bool setVariable(AptValue *,AptValue *,const EAStringC *,AptValue *,int=1,int=1,int=0);
    AptValue *getVariable(AptValue *,AptValue *,const EAStringC *,int=1,int=1,int=0);
private:
    static void _FunctionAptActionDefineLocal(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDefineLocal2(AptActionInterpreter *const,LocalContextT *const);
};
void AptActionInterpreter::_FunctionAptActionDefineLocal(AptActionInterpreter *const p,LocalContextT *const c)
{
    AptValue *value=p->stack.At(0);
    AptValue *name=p->stack.At(1);
    if(p->mpCurrentFunction) {
        AptString *text=name->c_string();
        if(!AptScriptFunctionBase::spFrameStack) p->mpCurrentFunction->rva006FBED0();
        ((Rva8D0D80Table *)((char *)AptScriptFunctionBase::spFrameStack+8))->add((Rva8D0D80String *)text->GetInternalString(),(Rva8D0D80Value *)value);
    } else p->setVariable((AptValue *)c->pCurrentContext,c->pCurWith,name->c_string()->GetInternalString(),value,0,1,0);
    p->stack.Pop(2);
}
void AptActionInterpreter::_FunctionAptActionDefineLocal2(AptActionInterpreter *const p,LocalContextT *const c)
{
    EAStringC *name=p->stack.At(0)->c_string()->GetInternalString();
    AptScriptFunctionBase *fn=p->mpCurrentFunction;
    if(fn) {
        bool exists;
        if(!AptScriptFunctionBase::spFrameStack) {
            if(fn->mpCreatorScope) exists=((BfmeTab1024 *)((char *)fn->mpCreatorScope+8))->bfmeFind1024((int)name)!=0;
            else exists=false;
        } else exists=((BfmeTab1024 *)((char *)AptScriptFunctionBase::spFrameStack+8))->bfmeFind1024((int)name)!=0;
        if(!exists) {
            AptValue *undefined=gpUndefinedValue;
            if(!AptScriptFunctionBase::spFrameStack) fn->rva006FBED0();
            ((Rva8D0D80Table *)((char *)AptScriptFunctionBase::spFrameStack+8))->add((Rva8D0D80String *)name,(Rva8D0D80Value *)undefined);
        }
    } else if(p->getVariable((AptValue *)c->pCurrentContext,c->pCurWith,name,0,1,0)->isUndefined()) p->setVariable((AptValue *)c->pCurrentContext,c->pCurWith,name,gpUndefinedValue,0,1,0);
    p->stack.Pop();
}

// Same target providers and ABI; preserve their existing ledger spellings.
#pragma comment(linker, "/alternatename:?c_string@AptValue@@QBEPAVAptString@@XZ=?checkedString@BfmeAptValue006DCD20@@QAEPAV1@XZ")
#pragma comment(linker, "/alternatename:?isUndefined@AptValue@@QBE_NXZ=?isUndefined@BfmeAptValue006DCD20@@QBE_NXZ")
#pragma comment(linker, "/alternatename:?rva006FBED0@AptScriptFunctionBase@@QAEXXZ=?rva006FBED0@Rva8D0D80Result@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeFind1024@BfmeTab1024@@QAEHH@Z=?lookup@Rva0070B380@@QAEPAXABVEAStringC@@@Z")

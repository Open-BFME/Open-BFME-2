// cl: /MD /EHsc
// Original Redwood6 PDB establishes handler ABI and record sizes24/28.
// PC dispatch9DC980 and complete704B50/704C60 bodies verify identity, offsets,
// allocation size52 and constructor calls. Later0cbfd5f746c89504 is body guide.
// DefineFunction1 retains the native early name lifetime and reassignment.
#include "AptObject/AptScriptFunction.h"
class EAStringC {
    void *data;
public:
    EAStringC(const char *);
    ~EAStringC();
    EAStringC &operator=(const EAStringC &);
};
class Rva006D2A60 { public: void *allocBlock(int); void freeBlock(void *,int); };
extern Rva006D2A60 *g_pChainBlockAllocatorF4;
__forceinline void *AptScriptFunction1::operator new(unsigned int size) { return g_pChainBlockAllocatorF4->allocBlock(size); }
__forceinline void AptScriptFunction1::operator delete(void *v,unsigned int size) { g_pChainBlockAllocatorF4->freeBlock(v,size); }
__forceinline void *AptScriptFunction2::operator new(unsigned int size) { return g_pChainBlockAllocatorF4->allocBlock(size); }
__forceinline void AptScriptFunction2::operator delete(void *v,unsigned int size) { g_pChainBlockAllocatorF4->freeBlock(v,size); }
class AptBasePtrStack { public: void Push(AptValue *); int count,capacity; AptValue **items; };
struct AptCharacterInst;
struct AptActionInterpreter {
    struct LocalContextT { const unsigned char *pInstruction; AptCIH *pCurrentContext; AptValue *pCurWith; const unsigned char *pRemoveWithAt; AptValue *pSuper; bool bEncounteredReturn; AptCharacterInst *pParentCharacter; };
    AptBasePtrStack stack;
    unsigned char prefix[0x30-12];
    AptScriptFunctionBase *mpCurrentFunction;
    unsigned char prefix2[12];
    AptConstantPool constantPool;
    bool setVariable(AptValue *,AptValue *,const EAStringC *,AptValue *,int=1,int=1,int=0);
private:
    static void _FunctionAptActionDefineFunction(AptActionInterpreter *const,LocalContextT *const);
    static void _FunctionAptActionDefineFunction2(AptActionInterpreter *const,LocalContextT *const);
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

// ?rva007097B0@AptScriptFunctionBase@@SAHPAX@Z
// partial score=0.98 date=2026-10-05
// ?rva007097B0@AptScriptFunctionBase@@SAHPAX@Z
// cl: /O2 /MD
// experiment: default-construct + Release in the loop, no gpUndefinedValue store
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
#include <new>
class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
};
extern AptValue *gpUndefinedValue;
class AptScriptFunctionBase {
    static AptValue **spRegBlockBase, **spRegBlockCurrentFrameBase;
    static int snRegBlockCurrentFrameCount, snRegisterBlockSize;
public:
    static int rva007097B0(void *pSaveBase);
};
#define CHECK_AT(cond,text,line) if (!(cond)) { g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp",line); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }

int AptScriptFunctionBase::rva007097B0(void *pSaveBase)
{
    CHECK_AT(spRegBlockBase,"spRegBlockBase",195);
    AptValue **cur=spRegBlockCurrentFrameBase;
    CHECK_AT(pSaveBase>=spRegBlockBase && pSaveBase<=cur,"pSaveBase >= spRegBlockBase && pSaveBase <= spRegBlockCurrentFrameBase",199);
    for(int i=0;i<snRegBlockCurrentFrameCount;++i) {
        AptValue *tmp=cur[i];
        cur[i]=gpUndefinedValue;
        tmp->Release();
    }
    int n=(char *)spRegBlockCurrentFrameBase-(char *)pSaveBase;
    spRegBlockCurrentFrameBase=(AptValue **)pSaveBase;
    n>>=2;
    snRegBlockCurrentFrameCount=n;
    return n;
}
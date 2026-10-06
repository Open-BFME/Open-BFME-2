// cl: /MD
// APT0.19.03 May2006 Xbox release donor: GUID46a11dfd-96b7-4859-900b-d1c12429eda5
// age126; PDB SHA2562c807043754eb23408edb29a3b2de750189b781a63251b732cb2e8471a1d6c3c.
// Donor type records supply class/member spellings and AptCXForm array structure.
// Target assertions independently name AptRenderingContext.cpp and both stacks.
// Retail accesses confirm curCXForm0 / matrix20 / colour stack38 / matrix stack238
// / depths3B8 and3BC; capacities16 and32/24-byte strides are target facts.
// The callback name is descriptive: retail popVertexMatrix calls the pointer at
// VA E177A0 with the restored matrix. No donor callback identity is claimed.
// Boundaries:70E330+84;70E390+77;70E4E0+104;70E550+118 (Ghidra + full returns).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
struct AptCXForm { float scale[4]; float translate[4]; };
struct AptMatrix { float a,b,c,d,tx,ty; };
// VA 0x00E177A0 (.data, zero-filled tail); target code calls this callback
// with the restored vertex matrix. No donor callback identity is asserted.
void (__cdecl *g_bfmeAptMatrixCallbackAtE177A0)(AptMatrix *);
struct AptRenderingContext {
    AptCXForm curCXForm;
    AptMatrix curVertexMatrix;
    AptCXForm aCXFormStack[16];
    AptMatrix aVertexMatrixStack[16];
    int nCXFormStack;
    int nVertexMatrixStack;
    void pushColourTransform();
    void popColourTransform();
    void pushVertexMatrix();
    void popVertexMatrix();
};
#define APT_CHECK(condition,line) if (!(condition)) { g_bfmeAptAssertAtE17734(#condition,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptRenderingContext.cpp",line); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }
#define APT_ARRAYSIZE(a) (int)(sizeof(a)/sizeof((a)[0]))
void AptRenderingContext::pushColourTransform()
{
    APT_CHECK(nCXFormStack < APT_ARRAYSIZE(aCXFormStack),48);
    aCXFormStack[nCXFormStack]=curCXForm;
    ++nCXFormStack;
}
void AptRenderingContext::popColourTransform()
{
    APT_CHECK(nCXFormStack > 0,54);
    --nCXFormStack;
    curCXForm=aCXFormStack[nCXFormStack];
}
void AptRenderingContext::pushVertexMatrix()
{
    APT_CHECK(nVertexMatrixStack < APT_ARRAYSIZE(aVertexMatrixStack),82);
    aVertexMatrixStack[nVertexMatrixStack]=curVertexMatrix;
    ++nVertexMatrixStack;
}
void AptRenderingContext::popVertexMatrix()
{
    APT_CHECK(nVertexMatrixStack > 0,88);
    --nVertexMatrixStack;
    curVertexMatrix=aVertexMatrixStack[nVertexMatrixStack];
    g_bfmeAptMatrixCallbackAtE177A0(&curVertexMatrix);
}

typedef char AptRenderingContextSize[(sizeof(AptRenderingContext)==0x3C0)?1:-1];

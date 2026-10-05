// ?rva007097B0@AptScriptFunctionBase@@SAHPAX@Z
// partial score=0.99 date=2026-10-05
// ?rva007097B0@AptScriptFunctionBase@@SAHPAX@Z
// cl: /O2 /MD
// 0x007097B0, 179 bytes (retail decodes to `ret` at +0xB2; the Ghidra inventory
// records 171 and every prior pass compared only that truncated window, which
// hid the true size AND the true residue -- see reverse/re_attempts.log).
//
// AptScriptFunctionBase frame-pop. The retail plan, read directly here:
//
//   push esi / push edi            (no EBX: pSaveBase stays at [esp+8])
//   mov edi,[esp+0xc]             (the reloaded SECOND stack argument)
//   mov eax,[0xE1834C] / cmp      (CHECK_AT spRegBlockBase at 195)
//   mov eax,[0xE18350] / cmp      (CHECK_AT pSaveBase bounds at 199)
//   mov ecx,[0xE18354] / xor esi,esi / test / jle     loop preheader
//   jmp +8 (padded to 16 with the lea esp,[esp] / nop pair at +0x77)
//   loop body:
//     mov ecx,[eax+esi*4]         the live register
//     mov edx,[0xE18078]          the undefined value, reloaded EVERY iteration
//     mov [eax+esi*4],edx         store BEFORE the release
//     mov eax,[ecx] / call [eax+4]  slot-1 Release
//     mov eax,[0xE18354]          the bound, reloaded at the loop TAIL
//     inc esi / cmp esi,eax
//     mov eax,[0xE18350]          the array base, reloaded at the loop TAIL
//     jl body
//   tail:
//     sub eax,edi
//     mov [0xE18350],edi
//     sar eax,2
//     pop edi
//     mov [0xE18354],eax          the count store, after the pop
//     pop esi / ret
//
// Two things make this body compile, and neither is in any earlier bank:
//
//  - The loop must read the register slots through spRegBlockCurrentFrameBase
//    DIRECTLY, with no local alias. The `cur` alias every earlier bank used
//    moves the bind above both CHECK_AT expands and gives the global-load CSE a
//    reason to reuse the +0x2B load for the whole loop and the tail, which
//    collapses the body to four instructions and loses the tail reload pair.
//    Reading the global directly defeats that CSE and reproduces retail's
//    register plan exactly: ESI as the index, EAX as the array base, the bound
//    in ECX at the preheader, and both tail reloads.
//
//  - The count store must be written as a plain assignment to
//    snRegBlockCurrentFrameCount AFTER the frame-base store, with the shifted
//    value already in a local. Inlining the count into the return expression
//    loses it (155 bytes), and computing it after the frame-base store reads
//    the just-stored value (176 bytes).
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
};
extern AptValue *g_bfmeAptDefaultValueAtE18078;
class AptScriptFunctionBase
{
    static AptValue **spRegBlockBase;
    static AptValue **spRegBlockCurrentFrameBase;
    static int snRegBlockCurrentFrameCount;
    static int snRegisterBlockSize;
public:
    static int rva007097B0(void *pSaveBase);
};
#define CHECK_AT(cond,text,line) if (!(cond)) { g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp",line); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }

#define CHECK_AT(cond,text,line) if (!(cond)) { g_bfmeAptAssertAtE17734(text,"C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptObject\\AptScriptFunction.cpp",line); if (g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak(); }

int AptScriptFunctionBase::rva007097B0(void *pSaveBase)
{
    CHECK_AT(spRegBlockBase,"spRegBlockBase",195);
    CHECK_AT(pSaveBase>=spRegBlockBase && pSaveBase<=spRegBlockCurrentFrameBase,"pSaveBase >= spRegBlockBase && pSaveBase <= spRegBlockCurrentFrameBase",199);
    AptValue **const cur = spRegBlockCurrentFrameBase;

    for (int i = 0; i < snRegBlockCurrentFrameCount; ++i) {
        AptValue *tmp = cur[i];
        cur[i] = g_bfmeAptDefaultValueAtE18078;
        tmp->Release();
    }
    int n = ((char *)cur - (char *)pSaveBase) >> 2;
    spRegBlockCurrentFrameBase = (AptValue **)pSaveBase;
    snRegBlockCurrentFrameCount = n;
    return n;
}

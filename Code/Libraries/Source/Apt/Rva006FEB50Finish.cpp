#include "AptObject/AptScriptFunction.h"
// ?rva006FEB50@AptActionInterpreter@@QAEXXZ
// partial score=0.95 date=2026-09-30
// cl: /MD
// May 2006 Xbox APT0.19.03 PDB supplies member names and class identity.
// Target startup 7B67A0 constructs global VA E182E0 with 6FE980, then registers
// cleanup 7B9C50, which passes the same global to destructor 6FE9C0. That
// destructor and AptActionInterpreter.cpp assertion caller 6FEB50 operate on
// debugCallStack at +34 (see AptInterpreterDebugStack.cpp).
// Target independently establishes zero initialization of five 12-byte stacks
// at 0/C/18/24/34, leaving +30 alone. Only the accessed prefix is modeled;
// donor names/types describe the stack roles, not a recovered full class ABI.
// Retail schedules the next stack's element load AFTER the previous stack's
// zero stores; the two _ReadWriteBarrier scheduling fences below pin that
// order without emitting any instruction.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)
class AptValue;
class AptScriptFunctionBase;
class Rva006DB270
{
public:
    void freeBlock(void *p, int bytes);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class AptBasePtrStack
{
public:
    void rva006FDE50();
};
template<class T> struct AptCtorStackView {
    int count, capacity;
    T **elements;
    AptCtorStackView() : count(0), capacity(0), elements(0) {}
};
template<class T> class AptDebugStack
{
    int m_nElements;
    int m_nCapacity;
    T **m_aElements;
public:
    void Shutdown();
};
struct AptActionInterpreter {
    struct DebugCallStackInfo_t;
    AptCtorStackView<AptValue> stack, withStack, setTargetStack, thisStack;
    AptScriptFunctionBase *mpCurrentFunction;
    AptCtorStackView<DebugCallStackInfo_t> debugCallStack;
    unsigned char gap40[36];
    int mnStackFrameBase;
    void rva006FEB50();
};

void AptActionInterpreter::rva006FEB50()
{
    ((AptBasePtrStack *)&stack)->rva006FDE50();
    if (withStack.elements) {
        g_pChainBlockAllocator->freeBlock(withStack.elements, withStack.capacity * 4);
    }
    withStack.capacity = 0;
    withStack.count = 0;
    withStack.elements = 0;
    _ReadWriteBarrier();
    if (setTargetStack.elements) {
        g_pChainBlockAllocator->freeBlock(setTargetStack.elements, setTargetStack.capacity * 4);
    }
    setTargetStack.capacity = 0;
    setTargetStack.count = 0;
    setTargetStack.elements = 0;
    _ReadWriteBarrier();
    if (thisStack.elements) {
        g_pChainBlockAllocator->freeBlock(thisStack.elements, thisStack.capacity * 4);
    }
    thisStack.capacity = 0;
    thisStack.count = 0;
    thisStack.elements = 0;
    AptScriptFunctionBase::ShutdownStaticData();
    ((AptDebugStack<DebugCallStackInfo_t> *)&debugCallStack)->Shutdown();
    if (mnStackFrameBase != 0) {
        g_bfmeAptAssertAtE17734("mnStackFrameBase == 0", "C:\\projects\\bfme2patch103\\bfme2\\Code\\Libraries\\Source\\Apt\\AptActionInterpreter.cpp", 0x10C);
        if (g_bfmeAptBreakOnAssertAtDDC01C)
            __debugbreak();
    }
}

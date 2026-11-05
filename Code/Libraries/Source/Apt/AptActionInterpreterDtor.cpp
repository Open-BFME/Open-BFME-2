// ??1AptActionInterpreter@@QAE@XZ
// cl: /MD /EHsc
// Native006FE9C0..006FEAEA is a298B nonvirtual destructor: embedded
// debug stack+34, three12B value stacks+C/+18/+24, then base stack.
// The matched AptDebugStack<DebugCallStackInfo_t> supplier and native init/
// Shutdown caller6FEB50 (AptActionInterpreter.cpp assertions, this+34) support
// the interpreter identity. Its nested debug type spelling is release-PDB
// provenance carried by that provider; target independently proves offsets.
// Base stack layout is12B at0. Constructor6FE980 proves value-stack
// boundaries+C/+18/+24 and current-function pointer+30.
// With-stack+C is AptValuePtrStack<AptValue>: native7084D3 passes this+C
// to the WB175A800-named push6E0D60; native708469 calls top6DE160 there.
// This-stack+24 calls the same at6DCC10 helper at708591: saved receiver
// is this+24 from7081CA/7081D1. Native push/pop uses AptValue AddRef/Release;
// May2006 APT donor member spelling is carried by AptInterpreterCtor.cpp.
// The middle buffer element identity remains opaque4B slots. Target _AptValuePtrStack.h
// assertion and sized pool frees prove count0/capacity4/storage8; destructor
// neither releases entries nor zeros fields. C++ member lifetime supplies the
// native3/2/1/0/-1 EH states, not explicit cleanup-label aliases.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void *,unsigned int);
void __debugbreak();
#pragma intrinsic(__debugbreak)
#include "../../../GameEngine/Include/Common/Rva006DB270.h"
extern Rva006DB270 *g_pChainBlockAllocator;
#include "AptBasePtrStack.h"
// The middle stack pointee remains unnamed; the native assertion establishes
// the same AptValuePtrStack family without assuming AptValue element identity.
struct Rva006FE9C0SetTargetElement;
class AptValue;
template<class T> class AptValuePtrStack {
public:
 int count,capacity;T **storage;
 ~AptValuePtrStack() {
  if(storage) {
   if(!g_bfmeAptFreeSizeAtE17730) {
    g_bfmeAptAssertAtE17734("gAptFuncs.pfnMemFreeSize","c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h",82);
    if(g_bfmeAptBreakOnAssertAtDDC01C) __debugbreak();
   }
   g_pChainBlockAllocator->freeBlock(storage,capacity*4);
  }
 }
};
template<class T> class AptDebugStack {
public:
 ~AptDebugStack();
 int elements,capacity;T **storage;
};
struct AptActionInterpreter {
public:
 struct DebugCallStackInfo_t;
 ~AptActionInterpreter();
 AptBasePtrStack stack;
 AptValuePtrStack<AptValue> withStack;
 AptValuePtrStack<Rva006FE9C0SetTargetElement> setTargetStack;
 AptValuePtrStack<AptValue> thisStack;
 void *currentFunction;
 AptDebugStack<DebugCallStackInfo_t> debug34;
};
AptActionInterpreter::~AptActionInterpreter() {}

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
// Buffer element identities remain opaque4B slots. Target _AptValuePtrStack.h
// assertion and sized pool frees prove count0/capacity4/storage8; destructor
// neither releases entries nor zeros fields. C++ member lifetime supplies the
// native3/2/1/0/-1 EH states, not explicit cleanup-label aliases.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *,const char *,int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void (__cdecl *g_bfmeAptFreeSizeAtE17730)(void *,unsigned int);
void __debugbreak();
#pragma intrinsic(__debugbreak)
class Rva006DB270 {public: void freeBlock(void *,int);};
extern Rva006DB270 *g_pChainBlockAllocator;
class AptBasePtrStack {
public:
 ~AptBasePtrStack();
 int elements,capacity;void **storage;
};
class AptOwnedValueSlots12 {
public:
 int count,capacity;void *storage;
 ~AptOwnedValueSlots12() {
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
class AptActionInterpreter {
public:
 struct DebugCallStackInfo_t;
 ~AptActionInterpreter();
 AptBasePtrStack stack;
 AptOwnedValueSlots12 withStack,setTargetStack,thisStack;
 void *currentFunction;
 AptDebugStack<DebugCallStackInfo_t> debug34;
};
AptActionInterpreter::~AptActionInterpreter() {}

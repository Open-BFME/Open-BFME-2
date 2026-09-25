// cl: /O1 /MD
// The pool lock waits briefly on the event created during startup.
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
    void *handle, unsigned long milliseconds);

static void * volatile g_poolYieldEvent = 0;

// MSVC folds a direct global argument into `push [memory]`; retail loads the
// event into eax first. The helper keeps that codegen choice localized.
__forceinline void *loadPoolYieldEvent()
{
    __asm mov eax, g_poolYieldEvent
}

void BFMEPoolYield()
{
    WaitForSingleObject(loadPoolYieldEvent(), 1);
}

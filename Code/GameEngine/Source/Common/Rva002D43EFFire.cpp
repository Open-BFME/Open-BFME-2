// cl: /DNDEBUG /MD /EHsc
// Rva002D43EFFire, retail 0x002D43EF, 117 bytes, sole caller 0x002D4A95.
// UI callback firer: formats the int through the rowed Rva00222834Get
// 0x00222834 and passes its text and the given AsciiString's text (both
// falling back to "") to the UI invoker 0x00222A8B (int-return pin) with
// kind 2, returning the invoker's result.
// The formatted string is a temporary of the call expression: retail reads
// its data through the returned pointer and destroys it after the invoke
// (unwind state 0), and keeps the invoker's result in esi across that
// teardown. The banked 0.93 attempt used a named local, an extern empty
// string and a void return.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"


AsciiString Rva00222834Get(int val);
AsciiString Rva002228E8Get(float val);

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int kind, const char *value, void *a4, void *a5, void *a6, void *a7);
};

int Rva002D43EFFire(Rva00222A8BTarget *target, void *owner, const char *name, int *value, const AsciiString *text)
{
	return target->invoke(owner, name, 2, Rva00222834Get(*value).str(), (void *)text->str(), 0, 0, 0);
}

// Native [0x002D4464,0x002D4531), 205B, cdecl RET0. Both radar callers
// pass target/level/name/int*/float*/float*. The native formatting calls
// evaluate float2, float1, then int; their returned strings remain alive
// through the eight-argument invoke and are destroyed in reverse order.
// The consumed types and lifetime are target evidence. The original helper
// name remains unknown. This immediately follows the 117B sibling above.
int Rva002D4464Fire(Rva00222A8BTarget *target, void *level, const char *name,
                    int *intParam, float *float1, float *float2)
{
	return target->invoke(level, name, 3, Rva00222834Get(*intParam).str(),
	    (void *)Rva002228E8Get(*float1).str(),
	    (void *)Rva002228E8Get(*float2).str(), 0, 0);
}

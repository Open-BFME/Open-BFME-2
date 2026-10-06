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

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int kind, const char *value, void *a4, void *a5, void *a6, void *a7);
};

int Rva002D43EFFire(Rva00222A8BTarget *target, void *owner, const char *name, int *value, const AsciiString *text)
{
	return target->invoke(owner, name, 2, Rva00222834Get(*value).str(), (void *)text->str(), 0, 0, 0);
}

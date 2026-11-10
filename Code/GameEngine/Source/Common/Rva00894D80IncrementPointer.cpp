#include "../../Include/Common/Rva00894D80Accessor.h"

unsigned int Rva00894D80Accessor::increment(unsigned int *value)
{
	return ++*value;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeIncVGO@@YAIPAI@Z=?increment@Rva00894D80Accessor@@SAIPAI@Z")

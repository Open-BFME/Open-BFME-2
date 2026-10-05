// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// Typed Apt callback wrappers: convert the argument to an AsciiString with
// the rowed formatters (Rva0022288EGet for unsigned, Rva002228E8Get for float)
// and return the rowed Rva00222A8BTarget::invoke result for a one-argument
// call. They are template-style siblings over one shape; names are
// address-derived.
//
// ?Rva002162CFInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABI@Z @0x002162CF 99B  unsigned
// ?Rva0021642FInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABM@Z @0x0021642F 103B float
// and three siblings below (int; unsigned+int; unsigned+two strings).
#include "ascii_string.h"

class Rva00222A8BTarget
{
public:
	int invoke(void *owner, const char *name, int argc, const char *a0, void *a1, void *a2, void *a3, void *a4);
};

// StringBase<char>::str() (TheNullChr for an empty string) of a temporary.
static inline const char *Rva002162CFStr(const AsciiString &s)
{
	return ((const StringBase<char> *)&s)->str();
}

AsciiString __cdecl Rva0022288EGet(unsigned int value);
AsciiString __cdecl Rva002228E8Get(float value);

int __cdecl Rva002162CFInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &arg)
{
	return target->invoke(owner, name, 1, Rva002162CFStr(Rva0022288EGet(arg)), 0, 0, 0, 0);
}

int __cdecl Rva0021642FInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const float &arg)
{
	return target->invoke(owner, name, 1, Rva002162CFStr(Rva002228E8Get(arg)), 0, 0, 0, 0);
}

AsciiString __cdecl Rva00222834Get(int value);

// ?Rva0021639AInvoke@@YAHPAVRva00222A8BTarget@@PAXPBDABIABH@Z @0x0021639A 149B
// two arguments, unsigned then int.
int __cdecl Rva0021639AInvoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &a, const int &b)
{
	return target->invoke(owner, name, 2, Rva002162CFStr(Rva0022288EGet(a)), (void *)Rva002162CFStr(Rva00222834Get(b)), 0, 0, 0);
}

// ?Rva00216496Invoke@@YAHPAVRva00222A8BTarget@@PAXPBDABIABVAsciiString@@4@Z @0x00216496 129B
// three arguments, an unsigned then two strings.
int __cdecl Rva00216496Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const unsigned int &a, const AsciiString &b, const AsciiString &c)
{
	return target->invoke(owner, name, 3, Rva002162CFStr(Rva0022288EGet(a)), (void *)Rva002162CFStr(b), (void *)Rva002162CFStr(c), 0, 0);
}

// ?Rva002D4531Invoke@@YAHPAVRva00222A8BTarget@@PAXPBDABH@Z @0x002D4531 99B
// one int argument through the rowed Rva00222834Get.
int __cdecl Rva002D4531Invoke(Rva00222A8BTarget *target, void *owner, const char *name, const int &arg)
{
	return target->invoke(owner, name, 1, Rva002162CFStr(Rva00222834Get(arg)), 0, 0, 0, 0);
}

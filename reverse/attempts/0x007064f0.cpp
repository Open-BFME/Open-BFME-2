// ?rva007064F0@@YAPAVBfmeAptValue006DCD20@@HHPAVEAStringC@@0@Z
// partial score=0.7 date=2026-10-05
// cl: /O2 /MD /EHsc
//
// Address-derived recovery of the 229-byte Apt value factory at RVA 0x007064F0.
// Identity evidence, all read from the retail binary rather than assumed:
//
//   * Four callers push two ints, a name pointer and an out EAStringC* (four
//     stack arguments, so the callee pops them) and use the returned pointer as
//     an Apt value: 0x007065E0 (the pin's own note), 0x00706A40, 0x007074C9 and
//     0x00708A87. The first caller writes the result straight through its own
//     out slot (0x0070661D / 0x00706629 `mov [ecx], eax`).
//   * The name is resolved against an Apt registry keyed by the class's
//     interned name: this body builds the string from `bytes` and `separator`
//     through the rowed ?rva006FEC00@@YAEHHPAVEAStringC@@PAH0@Z (0x006FEC00,
//     its all-digits fast path ahead of the general parser rva006FD100), then
//     looks it up with the unknown callee 0x006DF9A0, whose two arguments are
//     the same (name, out-string) pair this body pushes.
//   * 0x006DF9A0 starts at `push ebx/ebp/esi/edi`, reads its name argument at
//     [esp+0x14] and its out argument at [esp+0x18] (a two-argument frame), calls
//     ?rva006D3750@EAStringC@@QBEIXZ on the first and ?Rva0070B4F0GetString@@YAP
//     AVEAStringC@@H@Z (0x0070B4F0) on `this`, and returns a pointer in eax. Its
//     nine callers all test the returned pointer and all pass (name, out-string).
//
// ?rva007064F0@@YAPAVBfmeAptValue006DCD20@@HHPAVEAStringC@@@Z
//
// The class name below is carried from the near file's Apt value types; it is
// address-derived, not a proven retail class name. The flags line is copied
// from Rva00706330Cluster.cpp, the nearest recovered source in this directory.

#include <excpt.h>

class EAStringC
{
public:
	EAStringC();
	unsigned int rva006D3750() const;
	void Rva006D3010Destroy();
};

// 0x006FEC00, address-derived; see the note above.
int __cdecl rva006FEC00(int bytes, int separator, EAStringC *name,
	EAStringC *out, int unused);

class BfmeAptValue006DCD20
{
public:
	virtual int slot0();
	virtual void slot1();
};

// 0x0070B4F0, address-derived; see the note above.
class Rva0070B4F0
{
public:
	EAStringC *Rva0070B4F0GetString(int index);
};

// 0x006DF9A0, address-derived; see the note above.
class Rva006DF9A0
{
public:
	BfmeAptValue006DCD20 *rva006DF9A0(EAStringC *name, EAStringC *out);
};

// ?rva007064F0@@YAPAVBfmeAptValue006DCD20@@HHPAVEAStringC@@@Z
//
// BfmeAptValue006DCD20 *__cdecl rva007064F0(int bytes, int separator,
//                                            EAStringC *name, EAStringC *out)
//
// Looks a value of the given type up by name. An empty name returns null
// immediately; otherwise the name is rendered from (bytes, separator) and the
// registry is queried, and a null registry answer or a registry entry that
// fails its own vtable test at +0x10 both return null.
BfmeAptValue006DCD20 *__cdecl rva007064F0(int bytes, int separator,
	EAStringC *name, EAStringC *out)
{
	EAStringC local;

	__try
	{
	if (name->rva006D3750() == 0)
	{
		local.Rva006D3010Destroy();
		return 0;
	}

	::rva006FEC00(bytes, separator, name, out, 0);

	if (out == 0)
	{
		local.Rva006D3010Destroy();
		return 0;
	}

	Rva006DF9A0 registry;
	BfmeAptValue006DCD20 *value = registry.rva006DF9A0(name, &local);

	if (value == 0)
	{
		local.Rva006D3010Destroy();
		return 0;
	}

	if (value->slot0() == 0)
	{
		local.Rva006D3010Destroy();
		return 0;
	}

	local.Rva006D3010Destroy();
	return value;
	}
	__finally
	{
	}
}

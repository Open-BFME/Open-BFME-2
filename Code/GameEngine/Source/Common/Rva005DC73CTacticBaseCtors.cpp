// cl: /O1 /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// Skirmish-AI tactic base ctors taking the tactic name:
//   ??0Rva005DC73C@@QAE@ABVAsciiString@@@Z @0x005DC722 26B, vtable 0x00C767DC
//   ??0Rva005DCB27@@QAE@ABVAsciiString@@@Z @0x005DCB0D 26B, vtable 0x00C76834
// Each forwards (name, 1) to the AITactic base ctor 0x004ED3D1 (declared
// here, pinned in reverse/symbols.csv) and installs its own vtable. Same
// base + vtable shape as the landed SimpleAttack ctor
// (??0Rva005AA647@@QAE@XZ @0x005AA6B4, which calls 0x005DC722 with the
// SimpleAttack name). Class views are minimal: vtable width beyond the
// dtor/deleting-dtor slots is unproven and not declared.
#include "ascii_string.h"

class Rva004ECECD
{
public:
	Rva004ECECD(const AsciiString &name, int flags);
	virtual ~Rva004ECECD();
};

class Rva005DC73C : public Rva004ECECD
{
public:
	Rva005DC73C(const AsciiString &name);
	virtual ~Rva005DC73C();
};

Rva005DC73C::Rva005DC73C(const AsciiString &name)
	: Rva004ECECD(name, 1)
{
}

class Rva005DCB27 : public Rva004ECECD
{
public:
	Rva005DCB27(const AsciiString &name);
	virtual ~Rva005DCB27();
};

Rva005DCB27::Rva005DCB27(const AsciiString &name)
	: Rva004ECECD(name, 1)
{
}

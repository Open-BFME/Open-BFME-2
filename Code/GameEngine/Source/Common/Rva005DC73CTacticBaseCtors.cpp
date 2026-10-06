// cl: /MD /GX /DNDEBUG /Ireference/shims/bfme2_ascii
//
// Skirmish-AI tactic base ctors taking the tactic name:
//   ??0Rva005DC73C@@QAE@ABVAsciiString@@@Z @0x005DC722 26B, vtable 0x00C767DC
//   ??0Rva005DCB27@@QAE@ABVAsciiString@@@Z @0x005DCB0D 26B, vtable 0x00C76834
// Each forwards (name, 1) to the AITactic base ctor 0x004ED3D1 (declared
// here, pinned in reverse/symbols.csv) and installs its own vtable. Same
// base + vtable shape as the landed SimpleAttack ctor
// (??0AISimpleAttackTactic@@QAE@XZ @0x005AA6B4, which calls 0x005DC722 with the
// SimpleAttack name). Class views are minimal: vtable width beyond the
// dtor/deleting-dtor slots is unproven and not declared.
#include "ascii_string.h"

class AITactic
{
public:
	AITactic(const AsciiString &name, int flags);
	virtual ~AITactic();
};

class AITacticOffensive : public AITactic
{
public:
	AITacticOffensive(const AsciiString &name);
	virtual ~AITacticOffensive();
};

AITacticOffensive::AITacticOffensive(const AsciiString &name)
	: AITactic(name, 1)
{
}

class AITacticDefensive : public AITactic
{
public:
	AITacticDefensive(const AsciiString &name);
	virtual ~AITacticDefensive();
};

AITacticDefensive::AITacticDefensive(const AsciiString &name)
	: AITactic(name, 1)
{
}

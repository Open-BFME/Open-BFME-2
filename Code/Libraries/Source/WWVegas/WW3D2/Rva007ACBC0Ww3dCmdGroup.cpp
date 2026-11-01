// cl: /O2 /MD
// Dynamic initializer of a file-scope bool that registers the "ww3d" debug
// command group, Zero Hour's DEBUG_CREATE_COMMAND_GROUP shape
// (`static bool __RegisterDebugCmdGroup_##type = AddCommands(#groupname, new
// type)`). Target evidence: game.dat's __xc_a table points at 0x007ACBC0; the
// body allocates four bytes with the rowed ::operator new (0x0002FDA0), stores
// the class table 0x00BCFBF0 when the block is non-null (an inlined
// constructor of a DebugCmdInterface child whose only member is the vptr),
// then calls theDebug's (0x00DE0880) slot 0x84, AddCommands in
// DebugPostStaticInit.cpp, with "ww3d" (0x00BCFD70) and the object, and keeps
// the bool result at 0x00DEC498. The table's slots (folded deleting dtor
// 0x00118640, a command handler at 0x00117DC0 that tests for "help", and a
// Delete at 0x00117F10) fit DebugCmdInterface's virtual dtor, Execute and
// Delete. The child class and the bool are not named in the target; the RVA
// names stand in for them.

class Debug;

// Abstract base only: keep the derived retail table without emitting a base table.
class __declspec(novtable) DebugCmdInterface
{
protected:
	__declspec(dllimport) __forceinline virtual ~DebugCmdInterface() {}

public:
	__declspec(dllimport) __forceinline DebugCmdInterface() {}

	enum CommandMode
	{
		Normal,
		Structured,
		MAX
	};

	virtual bool Execute( Debug &dbg, const char *cmd, CommandMode cmdmode, unsigned argn, const char *const *argv ) = 0;
	virtual void Delete() = 0;
};

class Rva007ACBC0CmdInterface : public DebugCmdInterface
{
public:
	virtual bool Execute( Debug &dbg, const char *cmd, CommandMode cmdmode, unsigned argn, const char *const *argv );
	virtual void Delete();
};

// Placeholder slots up to AddCommands at 0x84; DebugPostStaticInit.cpp
// carries the named view.
#include "../../../../GameEngine/Source/Common/debug.h"

extern Debug *theDebug;

static bool s_rva007ACBC0 = theDebug->AddCommands( "ww3d", new Rva007ACBC0CmdInterface );

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

class DebugCmdInterface
{
protected:
	virtual ~DebugCmdInterface() {}

public:
	DebugCmdInterface() {}

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
class Debug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual bool AddCommands( const char *cmdgroup, DebugCmdInterface *cmdif ); // slot 0x84
};

extern Debug *theDebug;

static bool s_rva007ACBC0 = theDebug->AddCommands( "ww3d", new Rva007ACBC0CmdInterface );

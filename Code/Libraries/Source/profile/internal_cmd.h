// Zero Hour internal_cmd.h: the "profile" debug command group. numResFunc
// at +4 and resFunc at +8 follow the DebugCmdInterface vtable pointer
// (RunResultFunctions, 0x006C6E30).

#ifndef INTERNAL_CMD_H
#define INTERNAL_CMD_H

class ProfileCmdInterface : public DebugCmdInterface
{
	struct Factory
	{
		ProfileResultInterface *(*func)(int, const char *const *);
		const char *name, *arg;
	};

	static unsigned numResIf;
	static Factory *resIf;

	unsigned numResFunc;
	ProfileResultInterface **resFunc;

public:
	ProfileCmdInterface(void) : numResFunc(0), resFunc(0) {}

	static void AddResultFunction(ProfileResultInterface *(*func)(int, const char *const *),
		const char *name, const char *arg);
	void RunResultFunctions(void);

	virtual bool Execute(class Debug &dbg, const char *cmd, CommandMode cmdmode,
		unsigned argn, const char *const *argv);
	virtual void Delete(void) {}
};

#endif // INTERNAL_CMD_H

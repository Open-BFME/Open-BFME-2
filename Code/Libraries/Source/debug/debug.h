// BFME2 debug library: the Debug object as its callers see it.
//
// BFME2 reaches the debug manager through the pointer at 0x00DE0880
// (theDebug, defined in DebugPreStaticInit.cpp) and calls it through its
// vtable; Zero Hour's static Debug:: entry points became forwarders that
// inline away. Slots are those retail's call sites use (profile.cpp
// ProfileAllocMemory/ProfileReAllocMemory crash arm, profile_cmd.cpp
// RunResultFunctions); unnamed slots keep their byte offset only.
// Not yet registered in reverse/canonical_classes.csv: 57 private Debug
// layouts elsewhere still need reconciling against these slots.

#ifndef DEBUG_H
#define DEBUG_H

class Debug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual Debug &operator<<(const char *text);                      // +0x38
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void CrashDone(bool fatal);                                // +0x4C
	virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void SetCrashAddress(void *address, bool set);            // +0x5C
	virtual void SkipNext();                                           // +0x60
	virtual void slot64(); virtual void slot68();
	virtual Debug &CrashBegin(const char *file, int line, const char *group); // +0x6C
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88();
	virtual void Command(const char *cmd);                             // +0x8C

	static bool SkipNext(bool set);
	static bool SimpleMatch(const char *str, const char *pattern);
};

extern Debug *theDebug;

// Zero Hour debug_cmd.h: the command-group interface ProfileCmdInterface
// derives from (vtable at +0, so derived data starts at +4).
class DebugCmdInterface
{
public:
	enum CommandMode
	{
		Normal,
		Structured,
		NumModes
	};

	virtual bool Execute(Debug &dbg, const char *cmd, CommandMode cmdmode,
		unsigned argn, const char *const *argv) = 0;
	virtual void Delete(void) = 0;
};

#endif // DEBUG_H

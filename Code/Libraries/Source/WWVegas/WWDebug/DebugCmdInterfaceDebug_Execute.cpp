// cl: /DNDEBUG /MD /EHsc /Oy-
//
// DebugCmdInterfaceDebug::Execute, retail 0x0003E570 (3471 bytes, ret
// 0x14): the "debug" command group. Not recovered in BFME 1.
//
// Zero Hour's debug_cmd.cpp body, with the BFME2 changes read from the
// retail bytes:
// - New commands: skipstackwalk (the Debug +0x9E79 flag, spelled either
//   way), beep, crash / exception / fatalcrash (deliberate test crashes),
//   windowed (tri-state override at +0x9F55: + forces on, - forces off),
//   fulldump (+0x9F56) and errors (+0x9F57); help texts to match.
// - Frame types are BFME2's: assert 1, crash 2, log 4; the checks list is
//   now the crashes list.
// - exit uses exit code 0.

#include <string.h>
#include <stdlib.h>

extern "C" __declspec(dllimport) int __stdcall Beep(unsigned long frequency, unsigned long duration);
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *out, const char *fmt, ...);

void DebugFreeMemory(void *ptr);
void _bfme_debugRecordCallsite(int kind);

class Debug;

class DebugIOInterface
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04();
	virtual void Execute(Debug &dbg, const char *cmd, bool structuredCmd, unsigned argn,
		const char *const *argv);           // slot 0x14
	virtual void Delete();                  // slot 0x18
};

class DebugCmdInterface
{
public:
	enum CommandMode { Normal, Structured };

	virtual void Delete();
	virtual bool Execute(Debug &dbg, const char *cmd, CommandMode cmdmode, unsigned argn,
		const char *const *argv) = 0;
};

class DebugCmdInterfaceDebug : public DebugCmdInterface
{
public:
	virtual bool Execute(Debug &dbg, const char *cmd, CommandMode cmdmode, unsigned argn,
		const char *const *argv);
};

class Debug
{
public:
	enum { FrameTypeAssert = 1, FrameTypeCrash = 2, FrameTypeLog = 4 };
	enum FrameStatus { Unknown, Skip, NoSkip };
	enum { FRAME_HASH_SIZE = 10007 };

	struct IOFactoryListEntry
	{
		IOFactoryListEntry *next;
		const char *ioID;
		const char *descr;
		DebugIOInterface *(*factory)(void);
		DebugIOInterface *io;
	};

	struct CmdInterfaceListEntry
	{
		CmdInterfaceListEntry *next;
		const char *group;
		DebugCmdInterface *cmdif;
	};

	struct KnownLogGroupList
	{
		KnownLogGroupList *next;
		const char *nameGroup;
		const char *descr;
	};

	struct FrameHashEntry
	{
		FrameHashEntry *next;
		unsigned frameAddr;
		unsigned frameType;
		const char *fileOrGroup;
		int line;
		int hits;
		FrameStatus status;
	};

	struct PatternListEntry
	{
		PatternListEntry *next;
		unsigned frameTypes;
		bool isActive;
		char *pattern;
	};

	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12();
	// MSVC places the overloads at the first one's slot in reverse
	// declaration order: int 0x34, const char * 0x38.
	virtual Debug &operator<<(const char *str);
	virtual Debug &operator<<(int val);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);          // slot 0x4C
	virtual void pad20(); virtual void pad21(); virtual void pad22(); virtual void pad23();
	virtual void SkipNext();                    // slot 0x60
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved); // slot 0x6C

	static bool SimpleMatch(const char *str, const char *pattern);

private:
	friend class DebugCmdInterfaceDebug;

	void AddPatternEntry(unsigned types, bool isActive, const char *pattern);

public:

	unsigned char m_pad04[8];
	IOFactoryListEntry *firstIOFactory;        // +0x0C
	CmdInterfaceListEntry *firstCmdGroup;      // +0x10
	unsigned curStackFrame;                    // +0x14
	FrameHashEntry *frameHash[FRAME_HASH_SIZE]; // +0x18
	unsigned char m_pad9C74[0xC];
	KnownLogGroupList *firstLogGroup;          // +0x9C80
	unsigned char m_pad9C84[0x17C];
	PatternListEntry *firstPatternEntry;       // +0x9E00
	PatternListEntry *lastPatternEntry;        // +0x9E04
	unsigned char m_pad9E08[0x70];
	bool alwaysFlush;                          // +0x9E78
	bool noStackWalk;                          // +0x9E79
	bool timeStamp;                            // +0x9E7A
	unsigned char m_pad9E7B[0xDA];
	signed char windowed;                      // +0x9F55, <0 off, >0 on, 0 auto
	bool fullMiniDump;                         // +0x9F56
	bool logErrorsToFile;                      // +0x9F57
};

extern Debug *theDebug;

// ?Execute@DebugCmdInterfaceDebug@@UAE_NAAVDebug@@PBDW4CommandMode@DebugCmdInterface@@IPBQBD@Z
bool DebugCmdInterfaceDebug::Execute(Debug &dbg, const char *cmd, CommandMode cmdmode,
	unsigned argn, const char *const *argv)
{
	// just for convenience...
	bool normalMode = cmdmode == Normal;

	if (!strcmp(cmd, "help"))
	{
		if (!normalMode)
			return true;

		if (!argn)
		{
			dbg << "debug group help:\n"
				"  list, io, alwaysflush, skipstackwalk, timestamp, exit, beep, clear, add, view, windowed, fulldump, errors\n";
			return true;
		}
		else if (!strcmp(argv[0], "list"))
		{
			dbg << "list (g|l|d|a|c) [ <pattern> ]\n"
				"\n"
				"Shows some or all items of a specific type.\n"
				"\n"
				"The following items are supported:\n"
				"- g: command groups\n"
				"- l: log groups (only those encountered yet)\n"
				"- d: log groups with descriptions (only those that have descriptions)\n"
				"- a: asserts (only those hit yet)\n"
				"- c: crashes (only those failed yet)\n"
				"\n"
				"If a pattern is specified only items matching\n"
				"that pattern are shown. A pattern can contain\n"
				"any character, letter, or a wildcard '*'.\n"
				"\n"
				"Please note that assert and crash items have\n"
				"their line number appended to the current file name,\n"
				"e.g. debug.cpp(13).\n";
			return true;
		}
		else if (!strcmp(argv[0], "io"))
		{
			dbg << "io <I/O Class> <cmd> { <param> }]\n"
				"\n"
				"Issues a I/O class command. I/O class commands are used\n"
				"for determining where all log output should be sent. \n"
				"Please check the list of \ref debug_ioclasses for a list\n"
				"of existing I/O classes.\n"
				"\n"
				"Each existing I/O class must accept at least the\n"
				"following two commands: 'add' and 'remove'. Usually\n"
				"after a class has been added it reacts to the 'help'\n"
				"command as well.\n"
				"\n"
				"If the command is entered without any parameters a list\n"
				"of active I/O classes is shown. Typing 'io ?' retrieves\n"
				"a list of possible I/O classes.\n";
			return true;
		}
		else if (!strcmp(argv[0], "alwaysflush"))
		{
			dbg << "alwaysflush [ (+|-) ]\n\n"
				"Enables/disables flushing after each new entry in\n"
				"the log file (default: off).\n";
			return true;
		}
		else if (!strcmp(argv[0], "skipstackwalk"))
		{
			dbg << "skipstackwalk [ (+|-) ]\n\n"
				"Enables/disables stack walk feature\n"
				"the log file (default: off).\n";
			return true;
		}
		else if (!strcmp(argv[0], "timestamp"))
		{
			dbg << "timestamp [ (+|-) ]\n\n"
				"Enables/disables timestamping each log entry\n"
				"(default: off).\n";
			return true;
		}
		else if (!strcmp(argv[0], "exit"))
		{
			dbg << "exit\n\nExits program immediately.\n";
			return true;
		}
		else if (!strcmp(argv[0], "beep"))
		{
			dbg << "beep\n\nCauses a beep on the internal system speaker.\n";
			return true;
		}
		else if (!strcmp(argv[0], "clear"))
		{
			dbg << "clear (l|a|c)\n\n"
				"Clears the given inclusion/exclusion list\n"
				"(l=logs, a=asserts, c=crashes).\n";
			return true;
		}
		else if (!strcmp(argv[0], "add"))
		{
			dbg << "add (l|a|c) (+|-) <pattern>\n"
				"\n"
				"Adds a pattern to the given list (l=logs, \n"
				"a=asserts, c=crashes). By default all\n"
				"asserts and crashes are active, all logs\n"
				"inactive. Each item is then checked \n"
				"against all pattern in the respective\n"
				"list. If a match is found the active/inactive\n"
				"state is modified accordingly (+ for active,\n"
				"- for inactive). The final state is always\n"
				"the last match.";
			return true;
		}
		else if (!strcmp(argv[0], "view"))
		{
			dbg << "view [ (l|a|c) ]\n\n"
				"Shows the active pattern for the given list\n"
				"(l=logs, a=asserts, c=crashes).\n";
			return true;
		}
		else if (!strcmp(argv[0], "windowed"))
		{
			dbg << "windowed [ (+|-) ]\n\n"
				"Enables/disables windowed mode thus overriding any\n"
				"auto-detected status.\n";
			return true;
		}
		else if (!strcmp(argv[0], "fulldump"))
		{
			dbg << "fulldump [ (+|-) ]\n\n"
				"Enables/disables full memory dumps on crash (default: off).\n";
			return true;
		}
		else if (!strcmp(argv[0], "errors"))
		{
			dbg << "errors [ (+|-) ]\n\n"
				"Enables/disables extra logging of DERRORs into errors.txt (default: on).\n";
			return true;
		}
		return false;
	}

	if (!strcmp(cmd, "list"))
	{
		const char *pattern = argn >= 2 ? argv[1] : "*";

		switch (argn ? *argv[0] : 0)
		{
		case 'g':
			{
				if (normalMode)
					dbg << "Command groups:\n";
				for (Debug::CmdInterfaceListEntry *cur = dbg.firstCmdGroup; cur; cur = cur->next)
					if (Debug::SimpleMatch(cur->group, pattern))
						dbg << cur->group << "\n";
			}
			break;
		case 'l':
		case 'd':
			{
				if (normalMode)
					dbg << "Logs:\n";
				for (Debug::KnownLogGroupList *cur = dbg.firstLogGroup; cur; cur = cur->next)
					if (Debug::SimpleMatch(cur->nameGroup, pattern) &&
						(*argv[0] == 'l' || cur->descr))
					{
						dbg << cur->nameGroup;
						if (cur->descr)
							dbg << " (" << cur->descr << ")";
						dbg << "\n";
					}
			}
			break;
		case 'a':
		case 'c':
			{
				if (normalMode)
					dbg << (*argv[0] == 'a' ? "Asserts:\n" : "Crashes:\n");
				unsigned mask = *argv[0] == 'a' ? Debug::FrameTypeAssert : Debug::FrameTypeCrash;
				for (unsigned k = 0; k < Debug::FRAME_HASH_SIZE; k++)
				{
					for (Debug::FrameHashEntry *cur = dbg.frameHash[k]; cur; cur = cur->next)
					{
						if (!(cur->frameType & mask))
							continue;

						char help[256];
						wsprintfA(help, "%s(%i)", cur->fileOrGroup, cur->line);
						if (Debug::SimpleMatch(help, pattern))
						{
							dbg << help << " (" << cur->hits << " hits)";
							if (cur->status == Debug::Skip)
								dbg << " [off]";
							dbg << "\n";
						}
					}
				}
			}
			break;
		default:
			dbg << "Unknown item type, see help.";
		}

		return true;
	}
	if (!strcmp(cmd, "io"))
	{
		// cmd: io
		if (!argn || !strcmp(argv[0], "?"))
		{
			// show active/all I/O classes
			if (normalMode)
				dbg << (argn ? "Possible:\n" : "Active:\n");

			bool hadItem = false;
			for (Debug::IOFactoryListEntry *cur = dbg.firstIOFactory; cur; cur = cur->next)
			{
				if (!argn && !cur->io)
					continue;

				hadItem = true;
				dbg << cur->ioID << " (" << cur->descr << ")\n";
			}
			if (normalMode && !hadItem)
				dbg << "(none)\n";
		}
		else
		{
			// regular I/O command

			// find I/O class
			Debug::IOFactoryListEntry *cur;
			for (cur = dbg.firstIOFactory; cur; cur = cur->next)
				if (!strcmp(argv[0], cur->ioID))
					break;
			if (!cur)
			{
				dbg << "Unknown I/O class " << argv[0];
				return true; // still return true because we knew the command
			}

			if (argn > 1)
			{
				// 'add' command?
				if (!strcmp(argv[1], "add"))
				{
					if (cur->io)
					{
						dbg << "I/O class already added";
						return true;
					}
					cur->io = cur->factory();
					if (!cur->io)
					{
						dbg << "I/O class factory failed";
						return true;
					}
				}
				// 'remove' command?
				if (!strcmp(argv[1], "remove"))
				{
					if (cur->io)
					{
						cur->io->Delete();
						cur->io = 0;
					}
					return true;
				}
			}

			// now pass along I/O command
			if (!cur->io)
			{
				dbg << "Add I/O class first";
				return true;
			}

			cur->io->Execute(dbg, argn > 1 ? argv[1] : 0, !normalMode, argn > 1 ? argn - 2 : 0,
				argv + 2);
		}
		return true;
	}
	if (!strcmp(cmd, "alwaysflush"))
	{
		if (argn)
		{
			if (*argv[0] == '+')
				dbg.alwaysFlush = true;
			if (*argv[0] == '-')
				dbg.alwaysFlush = false;
		}
		if (normalMode)
			dbg << "Always flush: " << (dbg.alwaysFlush ? "on" : "off");
		else
			dbg << (dbg.alwaysFlush ? "1" : "0");

		return true;
	}
	if (!strcmp(cmd, "skipStackWalk") || !strcmp(cmd, "skipstackwalk"))
	{
		if (argn)
		{
			if (*argv[0] == '+')
				dbg.noStackWalk = true;
			if (*argv[0] == '-')
				dbg.noStackWalk = false;
		}
		if (normalMode)
			dbg << "Skip Stack Walk: " << (dbg.noStackWalk ? "on" : "off");
		else
			dbg << (dbg.noStackWalk ? "1" : "0");

		return true;
	}
	if (!strcmp(cmd, "timestamp"))
	{
		if (argn)
		{
			if (*argv[0] == '+')
				dbg.timeStamp = true;
			if (*argv[0] == '-')
				dbg.timeStamp = false;
		}
		if (normalMode)
			dbg << "Timestamp: " << (dbg.timeStamp ? "on" : "off");
		else
			dbg << (dbg.timeStamp ? "1" : "0");

		return true;
	}
	if (!strcmp(cmd, "exit"))
		exit(0);
	if (!strcmp(cmd, "crash"))
	{
		// test crash: write through a NULL pointer
		*(volatile int *)0 = 1;
		return true;
	}
	if (!strcmp(cmd, "exception"))
		throw &dbg;
	if (!strcmp(cmd, "fatalcrash"))
	{
		_bfme_debugRecordCallsite(1);
		theDebug->SkipNext();
		(theDebug->CrashBegin(0, 0, 0) << "Serious test crash. Everything is fine.").CrashDone(1);
		return true;
	}
	if (!strcmp(cmd, "beep"))
	{
		Beep(1000, 500);
		return true;
	}
	if (!strcmp(cmd, "clear") ||
		!strcmp(cmd, "add") ||
		!strcmp(cmd, "view"))
	{
		unsigned mask = 0;
		if (argn)
		{
			for (const char *p = argv[0]; *p; p++)
			{
				switch (*p)
				{
				case 'l': mask |= Debug::FrameTypeLog; break;
				case 'a': mask |= Debug::FrameTypeAssert; break;
				case 'c': mask |= Debug::FrameTypeCrash; break;
				}
			}
		}
		if (!mask)
			mask = 0xffffffff;

		bool modified = false;
		if (!strcmp(cmd, "clear"))
		{
			// remove some (or all) pattern
			const char *pattern = argn < 2 ? "*" : argv[1];
			for (Debug::PatternListEntry **entryPtr = &dbg.firstPatternEntry; *entryPtr;)
			{
				if ((((*entryPtr)->frameTypes & mask) != 0)
					&& Debug::SimpleMatch((*entryPtr)->pattern, pattern))
				{
					// remove this entry
					modified = true;
					Debug::PatternListEntry *cur = *entryPtr;
					*entryPtr = cur->next;
					DebugFreeMemory(cur->pattern);
					DebugFreeMemory(cur);
				}
				else
					entryPtr = &((*entryPtr)->next);
			}

			// must fixup lastPatternEntry now
			if (dbg.firstPatternEntry)
			{
				Debug::PatternListEntry *cur;
				for (cur = dbg.firstPatternEntry; cur->next; cur = cur->next)
					;
				dbg.lastPatternEntry = cur;
			}
			else
				dbg.lastPatternEntry = 0;
		}
		if (!strcmp(cmd, "add"))
		{
			// add a pattern
			if (argn < 3)
				dbg << "Please specify mode and pattern";
			else
			{
				dbg.AddPatternEntry(mask, *argv[1] == '+', argv[2]);
				modified = true;
			}
		}
		if (!strcmp(cmd, "view"))
		{
			// show list of defined patterns
			for (Debug::PatternListEntry *cur = dbg.firstPatternEntry; cur; cur = cur->next)
			{
				if (!(cur->frameTypes & mask))
					continue;

				if (cur->frameTypes & Debug::FrameTypeLog) dbg << "l";
				if (cur->frameTypes & Debug::FrameTypeAssert) dbg << "a";
				if (cur->frameTypes & Debug::FrameTypeCrash) dbg << "c";

				dbg << (cur->isActive ? " + " : " - ") << cur->pattern << "\n";
			}
		}

		if (modified)
		{
			// pattern list was modified, set all frame entries statuses to Unknown
			for (unsigned k = 0; k < Debug::FRAME_HASH_SIZE; k++)
				for (Debug::FrameHashEntry *cur = dbg.frameHash[k]; cur; cur = cur->next)
					cur->status = Debug::Unknown;
		}
		return true;
	}
	if (!strcmp(cmd, "windowed"))
	{
		if (argn)
		{
			if (*argv[0] == '+')
				dbg.windowed = 1;
			if (*argv[0] == '-')
				dbg.windowed = -1;
		}
		if (normalMode)
			dbg << "Windowed: " << (dbg.windowed > 0 ? "yes" : dbg.windowed < 0 ? "no" : "unknown");
		else
			dbg << (dbg.windowed ? "1" : "0");

		return true;
	}
	if (!strcmp(cmd, "fulldump"))
	{
		if (argn)
		{
			if (*argv[0] == '+')
				dbg.fullMiniDump = true;
			if (*argv[0] == '-')
				dbg.fullMiniDump = false;
		}
		if (normalMode)
			dbg << "Full memory dump: " << (dbg.fullMiniDump ? "on" : "off");
		else
			dbg << (dbg.fullMiniDump ? "1" : "0");

		return true;
	}
	if (!strcmp(cmd, "errors"))
	{
		if (argn)
		{
			if (*argv[0] == '+')
				dbg.logErrorsToFile = true;
			if (*argv[0] == '-')
				dbg.logErrorsToFile = false;
		}
		if (normalMode)
			dbg << "Extra error log: " << (dbg.logErrorsToFile ? "on" : "off");
		else
			dbg << (dbg.logErrorsToFile ? "1" : "0");

		return true;
	}

	// unknown command
	return false;
}

// cl: /DNDEBUG /MD /EHsc /Oy-
//
// Debug::ExecCommand, retail 0x00039E20 (901 bytes, ret 8). BFME 1 has it
// only as a lift (b1 0x0088ABA0).
//
// Zero Hour's command splitter and dispatcher, with the BFME2 changes read
// from the retail bytes:
// - A leading "<frame>:" (digits, blanks allowed) hands the whole command
//   to ScheduleFrameCommand (0x00039720), which keeps the buffer, and
//   returns false.
// - Nested calls (a command running commands) share one output block: only
//   the outermost call starts the output, only it flushes at the end.
// - The command handler's result is returned (false when nothing ran).
// - Command modes and reply types follow the BFME2 enums (CmdReply 4,
//   StructuredCmdReply 5).

#include <string.h>

void *DebugAllocMemory(unsigned int numBytes);
void DebugFreeMemory(void *ptr);

class Debug;

class DebugIOInterface
{
public:
	enum StringType { CmdReply = 4, StructuredCmdReply = 5 };
};

class DebugCmdInterface
{
public:
	enum CommandMode { Normal, Structured };

	virtual void Delete();
	virtual bool Execute(Debug &dbg, const char *cmd, CommandMode cmdmode, unsigned argn,
		const char *const *argv);
};

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str); // slot 0x38

private:
	struct CmdInterfaceListEntry
	{
		CmdInterfaceListEntry *next;
		const char *group;
		DebugCmdInterface *cmdif;
	};

	virtual void StartOutput(DebugIOInterface::StringType type, const char *fmt, ...);
	virtual void AddOutput(const char *str, unsigned len);
	virtual void FlushOutput(bool defaultLog);
	unsigned ScheduleFrameCommand(int frame, const char *command);
	bool ExecCommand(const char *cmdstart, const char *cmdend);

	unsigned char m_pad04[0xC];
	CmdInterfaceListEntry *firstCmdGroup;   // +0x10
	unsigned char m_pad14[0x9E00];
	char curCommandGroup[100];              // +0x9E14
};

// ?ExecCommand@Debug@@AAE_NPBD0@Z
bool Debug::ExecCommand(const char *cmdstart, const char *cmdend)
{
	// alloc & copy string
	char *strbuf = (char *)DebugAllocMemory(cmdend - cmdstart + 1);
	memcpy(strbuf, cmdstart, cmdend - cmdstart);
	strbuf[cmdend - cmdstart] = 0;

	// "<frame>:command" runs the command at that frame
	int frame = 0;
	char *cur = strbuf;
	for (; *cur; ++cur)
	{
		if (*cur != ' ' && *cur != '\t' && (*cur < '0' || *cur > '9'))
			break;
		if (*cur >= '0' && *cur <= '9')
			frame = frame * 10 + *cur - '0';
	}
	if (*cur == ':')
	{
		ScheduleFrameCommand(frame, strbuf);
		return false;
	}

	// for simplicity I'm using a fixed size argv array here...
	// if there are more arguments given than we have we're
	// just dropping the excess arguments
	char *parts[100];
	int numParts = 0;
	char *lastNonWhitespace = 0;
	cur = strbuf;
	bool result = false;

	// regular reply or structured reply?
	DebugIOInterface::StringType reply;
	DebugCmdInterface::CommandMode mode;
	if (*cur == '!')
	{
		cur++;
		reply = DebugIOInterface::StructuredCmdReply;
		mode = DebugCmdInterface::Structured;
	}
	else
	{
		reply = DebugIOInterface::CmdReply;
		mode = DebugCmdInterface::Normal;
	}

	for (;;)
	{
		if (!lastNonWhitespace && (*cur == '\'' || *cur == '"'))
		{
			char quote = *cur++;

			if (numParts < sizeof(parts) / sizeof(*parts))
				parts[numParts++] = cur;

			while (*cur && *cur != quote)
				++cur;
			if (*cur)
				*cur++ = 0;
		}
		else if (*cur == ' ' || *cur == '\t' || !*cur || *cur == ';')
		{
			if (*cur == ';')
				*cur = 0;
			if (lastNonWhitespace)
			{
				if (numParts < sizeof(parts) / sizeof(*parts))
					parts[numParts++] = lastNonWhitespace;
				lastNonWhitespace = 0;
				if (*cur)
					*cur++ = 0;
			}
			else if (*cur)
				++cur;
			else
				break;
		}
		else
		{
			if (!lastNonWhitespace)
				lastNonWhitespace = cur;
			++cur;
		}
	}

	if (numParts)
	{
		// part[0] is the command, part[1..numParts] are arguments

		// split off command group (if any)
		char *p = strchr(parts[0], '.');
		if (p && p - parts[0] < sizeof(curCommandGroup))
		{
			memcpy(curCommandGroup, parts[0], p - parts[0]);
			curCommandGroup[p - parts[0]] = 0;
			++p;
		}
		else
			p = parts[0];

		// nested commands share the outermost command's output
		static int nesting;
		if (!nesting++)
			Debug::StartOutput(reply, "%s.%s", curCommandGroup, p);

		if (mode != DebugCmdInterface::Structured)
			Debug::AddOutput("> ", 2);

		// repeat current command first
		Debug::AddOutput(cmdstart, cmdend - cmdstart);
		Debug::AddOutput("\n", 1);

		// command group known?
		CmdInterfaceListEntry *cur;
		for (cur = firstCmdGroup; cur; cur = cur->next)
			if (!strcmp(curCommandGroup, cur->group))
				break;
		if (!cur)
		{
			// nope, show error message
			(*this) << "Unknown command group " << curCommandGroup;
			*p = 0;
		}

		if (*p)
		{
			// must have command...

			// search for a matching command handler
			for (cur = firstCmdGroup; cur; cur = cur->next)
			{
				if (strcmp(curCommandGroup, cur->group))
					continue;

				result = cur->cmdif->Execute(*this, p, mode, numParts - 1, parts + 1);
				if (result && (strcmp(p, "help") || numParts > 1))
					break;
			}

			// display error message if command not found, break away
			if (!cur && mode == DebugCmdInterface::Normal)
			{
				if (strcmp(p, "help"))
					operator<<("Unknown command");
				else if (numParts > 1)
					operator<<("Unknown command, help not available");
			}
		}

		// flush output only if there is already an active I/O class
		if (!--nesting)
			Debug::FlushOutput(false);
	}

	// cleanup
	DebugFreeMemory(strbuf);
	return result;
}

// cl: /DNDEBUG /MD /EHsc
//
// Debug::CrashBegin, retail 0x0003AD80 (329 bytes, ret 0x0C).
// Ported from Open-BFME-1 WWDebug/Debug_CrashBegin_0088BA10.cpp (2-arg
// member); every address, slot, offset and literal below is read from
// the BFME2 bytes. Sibling of Debug::CheckBegin @0x3A750 (same TU shape,
// same prologue, same header block); see Debug_CheckBegin.cpp.
//
// BFME2 adaptations (all retail-measured):
// - Retail cleans 12 stack bytes (ret 0x0C) for (file, line, reserved):
//   ebp+0x8 (file), ebp+0xC (line) and ebp+0x10 provably never read, so
//   the third parameter is an unread filler; `int reserved` is the neutral
//   choice (same idiom as CheckBegin's reserved). Mangling:
//   ?CrashBegin@Debug@@UAEAAV1@PBDHH@Z.
// - Frame type literal 2 (CheckBegin passes 1).
// - Head `<<` pair is "\n" + RepeatChar('=', 80) + "\n" (no assertion
//   text); the file block runs only under `if (file)` (CheckBegin has no
//   guard). The dead line home [ebp+0xC] hosts `p` after ebx takes line
//   (listbox dead-slot precedent); the frame stays 0x8C.
// - Crash tail is "Error in " + p + ", line " + line + " at " + help +
//   ", reason:\n" with no expression operand (the BFME1 ", reason" tail
//   likewise ends the chain).
// - The `<<` chain and the return run on *this (BFME1 shape), not on the
//   theDebug singleton the CheckBegin TU uses.
// - The two-argument StartOutput("", 10) call rides slot 0x50 (retail vtable
//   at RVA 0x7BE810: slot 0x50 -> 0x38850). MSVC assigns same-name VIRTUAL
//   overloads in reverse declaration order (measured with a minimal probe:
//   declared int-then-str compiles to str@first-slot/int@second-slot), so
//   the two-argument declaration sits AFTER the variadic one in this TU;
//   the variadic overload takes index 21 (slot 0x54, never called
//   indirectly) while the two-argument one lands at index 20 = slot 0x50.
//   Its explicitly-qualified call site still compiles to the direct
//   five-push E8 to matched 0x39B30.
// - MSVC's reverse-overload assignment also explains operator<<: declared
//   (RepeatChar, const char*, int), compiled and retail alike use
//   int@0x34, string@0x38, RepeatChar@0x3C. Do NOT "fix" the declaration
//   order: it already matches retail.
// - All eight literals match retail ("%s(%i)", "\\code\\", "\n", "", "Error
//   in ", ", line ", " at " and ", reason:\n") at 0xBBE958/0xBBEBA8/
//   0xBBE498/0xBBAC1C/0xBBEC50/0xBBEB88/0xBBEB80/0xBBEC44.
// - curType +0x9CF4, curFrameEntry +0x9DFC and curStackFrame +0x14 repeat
//   the reference member layout exactly.
// - The five-push direct call uses the matched variadic StartOutput row at
//   0x39B30, whose this-on-stack shape explains the caller-cleaned 0x14
//   after it (GetTimeFormatA is __stdcall and cleans its own six pushes).
// - Retail CrashBegin is also reachable via Debug vtable slot 0x6C; it has
//   no direct E8 caller in .text (release asserts compile out) — the vtable
//   reference is what keeps the body alive. This TU leaves CrashBegin
//   non-virtual like the BFME1 TU: no body bytes depend on it.

#pragma optimize("y", off)

extern "C" __declspec(dllimport) unsigned long __stdcall GetTimeFormatA(
	unsigned long, unsigned long, const void *, const char *, char *, int);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *, const char *);

struct DebugIOInterface
{
	// Fuller replica matching Debug_LogBegin_0088B8F0.cpp: CrashBegin logs
	// at level Log (2) where CheckBegin logs at 0.
	enum StringType { Assert, Check, Log, Crash, Exception, CmdReply, StructuredCmdReply, Other, MAX };
};

class Debug
{
public:
	class RepeatChar
	{
		char m_char;
		int m_count;

	public:
		RepeatChar(char ch, int count) : m_char(ch), m_count(count) {}
	};

	enum FrameStatus
	{
		Unknown,
		Skip,
		NoSkip
	};

	struct FrameHashEntry
	{
		FrameHashEntry *next;
		unsigned int frameAddr;
		unsigned int frameType;
		const char *fileOrGroup;
		int line;
		int hits;
		FrameStatus status;
	};

	// Placeholder virtuals place operator<< at slots 0x34/0x38/0x3C and
	// the two-argument StartOutput at slot 0x50.
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual Debug &operator<<(const RepeatChar &rep);
	virtual Debug &operator<<(const char *str);
	virtual Debug &operator<<(int val);
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();

private:
	unsigned char m_pad04[8];
	void *firstIOFactory;
	unsigned char m_pad10[4];
	unsigned int curStackFrame; // +0x14
	unsigned char m_pad18[0x9CDC];
	int curType; // +0x9CF4
	char curSource[256]; // +0x9CF8
	int disableAssertsEtc; // +0x9DF8
	FrameHashEntry *curFrameEntry; // +0x9DFC

	// Variadic overload first (private so it mangles EAAX like the matched
	// 0x39B30 row; see header note). Reverse-order assignment then puts the
	// two-argument form at index 20 = slot 0x50 and this one at index 21
	// (slot 0x54, never called indirectly).
	virtual void StartOutput(DebugIOInterface::StringType type, const char *fmt, ...);
	virtual void FlushOutput(bool flag);
	FrameHashEntry *GetFrameEntry(unsigned int addr, unsigned int type,
		const char *fileOrGroup, int line);
	// Declared AFTER the variadic overload on purpose (see header note):
	// MSVC assigns same-name virtual overloads in reverse declaration
	// order, so this two-argument form lands at index 20 = slot 0x50
	// while the variadic one takes index 21 (slot 0x54, unused by body).
	virtual void StartOutput(const char *fmt, unsigned count);

public:
	// Slots 23..26, then CrashBegin in its own slot 27 (+0x6C) of
	// 0x00BBE810, declared after the slots the body calls so they keep
	// their indices.
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

// ?CrashBegin@Debug@@UAEAAV1@PBDHH@Z
Debug &Debug::CrashBegin(const char *file, int line, int reserved)
{
	char help[132];

	if (curType != 7)
		this->Debug::FlushOutput(true);

	curFrameEntry = GetFrameEntry(curStackFrame, 2, file, line);
	if (curFrameEntry->status == 2 || curFrameEntry->status == 3 ||
		curFrameEntry->status == 0)
	{
		this->StartOutput("", 10);
		this->Debug::StartOutput(DebugIOInterface::Log, "%s(%i)",
			file, line);
		++curFrameEntry->hits;

		*this << "\n"
			<< RepeatChar('=', 80)
			<< "\n";

		if (file)
		{
			const char *p = strstr(file, "\\code\\");
			if (p)
				p += 6;
			else
				p = file;

			GetTimeFormatA(0x400, 0, 0, 0, help, 0x80);
			help[128] = 0;
			*this << "Error in "
				<< p
				<< ", line "
				<< line
				<< " at "
				<< help
				<< ", reason:\n";
		}
	}

	return *this;
}

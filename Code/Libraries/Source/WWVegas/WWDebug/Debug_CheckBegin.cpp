// cl: /DNDEBUG /MD /EHsc
//
// Debug::CheckBegin, retail 0x0003A750 (333 bytes, ret 0x10).
// Ported from Open-BFME-1 WWDebug/Debug_CheckBegin_0088B3E0.cpp (334B,
// 3-arg member); every address, slot, offset and literal below is read from
// the BFME2 bytes.
//
// BFME2 adaptations (all retail-measured):
// - Retail cleans 16 stack bytes (ret 0x10) and reads ebp+0x8 (file),
//   ebp+0xC (line) and ebp+0x14 (the string printed after ",\nexpression ").
//   ebp+0x10 is provably never read, so the body takes a fourth parameter
//   whose type is unknowable from the bytes; `int reserved` is the neutral
//   choice. Mangling: ?CheckBegin@Debug@@UAEAAV1@PBDHH0@Z.
// - The two-argument StartOutput("", 10) call rides slot 0x50 (retail vtable
//   at RVA 0x7BE810: slot 0x50 -> 0x38850, slot 0x54 -> WriteBuildInfo
//   0x395D0). MSVC assigns same-name VIRTUAL overloads in reverse declaration
//   order (measured with a minimal probe: declared int-then-str compiles to
//   str@first-slot/int@second-slot), so the two-argument declaration sits
//   AFTER the variadic one in this TU; the variadic overload takes index 21
//   (slot 0x54, never called indirectly) while the two-argument one lands at
//   index 20 = slot 0x50. Its explicitly-qualified call site still compiles
//   to the direct five-push E8 to matched 0x39B30.
// - MSVC's reverse-overload assignment also explains operator<<: declared
//   (RepeatChar, const char*, int), compiled and retail alike use
//   int@0x34, string@0x38, RepeatChar@0x3C. Do NOT "fix" the declaration
//   order: it already matches retail.
// - All eight literals match BFME1 byte for byte ("%s(%i)", "\\code\\",
//   "\n", "\nAssertion failed in ", ", line ", " at ", ",\nexpression "
//   and "") at 0xBBE958/0xBBEBA8/0xBBE498/0xBBEB90/0xBBEB88/0xBBEB80/
//   0xBBEB70/0xBBAC1C.
// - curType +0x9CF4, curFrameEntry +0x9DFC and curStackFrame +0x14 repeat
//   the reference member layout exactly.
// - Frame type literal 1 (BFME2 renumbered the types: Check is 1 and Crash
//   is 2, where Zero Hour has Check 2 and Log 4).
// - The five-push direct call uses the matched variadic StartOutput row at
//   0x39B30, whose this-on-stack shape explains the caller-cleaned 0x1C
//   after the strstr call (GetTimeFormatA is __stdcall and cleans its own
//   six pushes).
// - TheDebug singleton pointer is theDebug COMMON, DIR32-patched from
//   retail like the other WWDebug units.
// - Retail CheckBegin is also reachable via Debug vtable slot 0x64
//   (0x43A750) and CrashBegin via 0x6C; neither has any direct E8 caller in
//   .text (release asserts compile out) — the vtable reference is what keeps
//   the bodies alive. This TU leaves CheckBegin non-virtual like the BFME1
//   TU: no body bytes depend on it.

#pragma optimize("y", off)

extern "C" __declspec(dllimport) unsigned long __stdcall GetTimeFormatA(
	unsigned long, unsigned long, const void *, const char *, char *, int);
extern "C" __declspec(dllimport) char *__cdecl strstr(const char *, const char *);

struct DebugIOInterface
{
	enum StringType
	{
		CheckLog = 0
	};
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
	// Slots 23 and 24, then CheckBegin in its own slot 25 (+0x64) of
	// 0x00BBE810, declared after the slots the body calls so they keep
	// their indices.
	virtual void pad23();
	virtual void pad24();
	virtual Debug &CheckBegin(const char *file, int line, int reserved, const char *expr);
};

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp

// ?CheckBegin@Debug@@UAEAAV1@PBDHH0@Z
Debug &Debug::CheckBegin(const char *file, int line, int reserved, const char *expr)
{
	char help[132];

	if (curType != 7)
		this->Debug::FlushOutput(true);

	curFrameEntry = GetFrameEntry(curStackFrame, 1, file, line);
	if (curFrameEntry->status == 2 || curFrameEntry->status == 3 ||
		curFrameEntry->status == 0)
	{
		this->StartOutput("", 10);
		this->Debug::StartOutput(DebugIOInterface::CheckLog, "%s(%i)",
			curFrameEntry->fileOrGroup, curFrameEntry->line);
		++curFrameEntry->hits;

		const char *p = strstr(file, "\\code\\");
		if (p)
			p += 6;
		else
			p = file;

		GetTimeFormatA(0x400, 0, 0, 0, help, 0x80);
		Debug *debug = theDebug;
		help[128] = 0;
		(*debug) << "\n"
			<< RepeatChar('=', 80)
			<< "\nAssertion failed in "
			<< p
			<< ", line "
			<< line
			<< " at "
			<< help
			<< ",\nexpression "
			<< expr;
	}

	return *theDebug;
}

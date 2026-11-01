// Target facts: BFME2 Debug has no base class and one primary vptr at +0.
// Constructor RVA 0x00038440 (+0x2C) and destructor RVA 0x00038710 (+0x1C)
// both install VA 0x00BBE810 (RVA 0x007BE810). Its 46 entries end at the
// DebugCmdInterfaceDebug table VA 0x00BBE8C8; there is no ctor/dtor table split.
// Slots 0..15 target RVAs 38C30,389C0,38950,3B570,3B510,3B4C0,3B470,38900,
// 388B0,38890,3B420,3B3D0,3B420,3B3D0,3B340,3A620 respectively. Ledger
// names prove the stream types; Zero Hour supplies the long overload names.
// MSVC 7.1 reverses overloaded virtual declarations at their first slot.
// Slot 16 targets deleting destructor RVA 0x00039920, which calls the rowed
// destructor 0x00038710; both remain out of line. Slots 17..28 target RVAs
// 3A8A0,387F0,3AED0,38850,395D0,38770,3A6A0,387D0,3A750,3AC60,3AD80,3B5D0.
// Ledger names prove AssertDone(int), CrashDone(int), WriteBuildInfo,
// frameStatus(unsigned,bool), CheckBegin, LogBegin, CrashBegin and isLogEnabled.
// RVA 0x00038850 copies a 15-byte prefix to +0x9E7C and stores radix +0x9E8C,
// proving Zero Hour's SetPrefixAndRadix. Slot 18 performs Zero Hour's LogDone
// cleanup. Slot 24 increments +0x9DF8 and returns false (SkipNext).
// Static SkipNext(bool), RVA 0x00038790, calls slot 23 (frameStatus), whose
// two stack operands do not establish a separate SetCrashAddress method.
// Slots 29..45 target RVAs 38CB0,38CC0,38D60,38DF0,38E40,38EA0,3B640,3B670,
// 3B700,38EE0,39510,395A0,395B0,395C0,397D0,39880,390D0. Unproven names use
// vslotNN; slot 45 targets the nonvirtual AddLogGroup ledger body 0x000390D0.
// PreStaticInit RVA 0x000385F0 (+0x24) allocates 0x9F68 bytes, calls the
// constructor at +0x44, and increments refCount +0x9C7C at +0x59.
// Constructor stores prove +4,+8,+0xC,+0x10,+0x14; its REP STOSD clears
// 10007 pointers at +0x18 and 0x70 bytes at +0x9C84 (seven 16-byte buffers).
// Its other stores prove +0x9C74,+0x9C78,+0x9C80,+0x9CF4 (sentinel 7),
// +0x9CF8,+0x9DF8,+0x9DFC,+0x9E00,+0x9E04,+0x9E08,+0x9E0C,+0x9E10,
// +0x9E14,+0x9E78,+0x9E79,+0x9E7A,+0x9E8C,+0x9F54..+0x9F58,+0x9F5C,
// +0x9F64. Stack-walk ctor 0x0003C0E0 and dtor 0x0069E440 use +0x9E7B.
// SetBuildInfo RVA 0x00039510 and getters 0x000395A0/B0/C0 prove the three
// 64-byte strings at +0x9E90,+0x9ED0,+0x9F10. String output 0x0003B340 uses
// width +0x9F50 and fill +0x9F54. LogBegin 0x0003AC60 uses mutex +0x9F5C
// and thread +0x9F60. Commands 0x0003E570 prove the flags and list accesses;
// AddFrameEntry 0x00038FF0 proves 28-byte frame records and their fields;
// ScheduleFrameCommand 0x00039720 proves the 8-byte frame-command records.
// Member names shared with Zero Hour debug_debug.h describe these witnessed
// accesses. The remaining storage has neutral names and is not a base class.
// Format ctor RVA 0x000386E0 passes its object address and limit 0x1FF to
// _vsnprintf; retail callers reserve 0x200 bytes. Its buffer name and stream
// forwarding expression come from Zero Hour; BFME2 has no Format vtable slot.
// The registration bodies at 0x00038CC0/38D60/38DF0/38E40/38EA0 implement
// Zero Hour's AddHResultTranslator, RemoveHResultTranslator, AddIOFactory,
// AddCommands and RemoveCommands at slots 30..34. Static wrapper 0x00038370
// dispatches slot 22 to InstallExceptionHandler (0x00038770).
// WaterTextureList caller RVA 0x00200AEA uses a 0x200-byte Format buffer at
// +0x74, calls its constructor at +0x80, then passes the returned buffer
// address unchanged to string slot 14 at +0x8D. This proves the buffer view
// exposed by Format's conversion to const char *.
// Other rowed methods: LookupFrame 0x00038330, GetFrameEntry 0x0003A1B0,
// AddPatternEntry 0x000393E0, ExecCommand 0x00039E20, SimpleMatch 0x00039480,
// PostStaticInit 0x0003A250 and StaticExit 0x000399C0. Zero Hour names the
// frame-status updater called at RVA 0x00039A60. AssertDone at 0x0003AB5E
// compares hits +0x14 with 20; frame status values use 0..3 at +0x18.
// Copy and assignment restrictions follow Zero Hour. No retail out-of-line
// copy or assignment body is identified here.
// AddOutput 0x00039B70 and FlushOutput 0x00039300 prove each IOBuffer's
// pointer, used/allocated counts and lastWasCR byte with a 16-byte stride.

#pragma once
#ifndef BFME2_COMMON_DEBUG_H
#define BFME2_COMMON_DEBUG_H

class DebugIOInterface;
class DebugCmdInterface;

class Debug
{
public:
	class MemDump;
	class HResult;
	class RepeatChar;
	class Format
	{
		friend class Debug;
		Format(const Format &);
		Format &operator=(const Format &);
		char m_buffer[512];
	public:
		explicit Format(const char *format, ...);
		operator const char *() const { return m_buffer; }
	};
	typedef bool (*HResultTranslator)(Debug &debug, long result, void *user);

	virtual Debug &operator<<(const RepeatChar &value);
	virtual Debug &operator<<(const char *value);
	virtual Debug &operator<<(int value);
	virtual Debug &operator<<(unsigned int value);
	virtual Debug &operator<<(long value);
	virtual Debug &operator<<(unsigned long value);
	virtual Debug &operator<<(bool value);
	virtual Debug &operator<<(float value);
	virtual Debug &operator<<(double value);
	virtual Debug &operator<<(short value);
	virtual Debug &operator<<(unsigned short value);
	virtual Debug &operator<<(__int64 value);
	virtual Debug &operator<<(unsigned __int64 value);
	virtual Debug &operator<<(const void *value);
	virtual Debug &operator<<(const MemDump &value);
	virtual Debug &operator<<(HResult value);
	virtual ~Debug();
	virtual bool AssertDone(int mode);
	virtual bool LogDone();
	virtual bool CrashDone(int mode);
	virtual void SetPrefixAndRadix(const char *prefix, int radix);
	virtual void WriteBuildInfo();
	virtual void InstallExceptionHandler();
	virtual bool frameStatus(unsigned int address, bool reset);
	virtual bool SkipNext();
	virtual Debug &CheckBegin(const char *file, int line, int reserved, const char *expression);
	virtual Debug &LogBegin(const char *fileOrGroup);
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
	virtual bool isLogEnabled(unsigned int address);
	virtual unsigned char vslot29();
	virtual void AddHResultTranslator(unsigned int priority, HResultTranslator translator, void *user);
	virtual void RemoveHResultTranslator(HResultTranslator translator, void *user);
	virtual bool AddIOFactory(const char *id, const char *description, DebugIOInterface *(*factory)());
	virtual bool AddCommands(const char *group, DebugCmdInterface *commands);
	virtual void RemoveCommands(DebugCmdInterface *commands);
	virtual bool Command(const char *command);
	virtual void ExecuteFrameCommands(int frame);
	virtual void Update();
	virtual int GetInput(char *buffer, int size, bool *structured);
	virtual void SetBuildInfo(const char *version, const char *internalVersion, const char *buildDate);
	virtual const char *vslot40();
	virtual const char *vslot41();
	virtual const char *vslot42();
	virtual bool IsWindowed();
	virtual void vslot44(unsigned char windowed);
	virtual const char *AddLogGroup(const char *fileOrGroup, const char *description);

	Debug &operator<<(const Format &value) { operator<<(value.m_buffer); return *this; }

	static bool SkipNext(bool set);
	static bool SimpleMatch(const char *text, const char *pattern);

	enum { FRAME_HASH_SIZE = 10007, FRAME_HASH_ALLOC_COUNT = 100, MAX_CHECK_HITS = 20 };
	enum FrameType { FrameTypeAssert = 1, FrameTypeCrash = 2, FrameTypeLog = 4 };
	enum FrameStatus { Unknown, Skip, NoSkip };
	struct FrameHashEntry
	{
		FrameHashEntry *next;
		unsigned int frameAddr;
		unsigned int frameType;
		const char *fileOrGroup;
		int line;
		int hits;
		int status;
	};
	struct FrameCommand
	{
		int frame;
		const char *command;
	};
	struct IOFactoryListEntry
	{
		IOFactoryListEntry *next;
		const char *ioID;
		const char *descr;
		DebugIOInterface *(*factory)();
		DebugIOInterface *io;
		char *input;
		unsigned int inputUsed;
		unsigned int inputAlloc;
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
		char *nameGroup;
		const char *descr;
	};
	struct PatternListEntry
	{
		PatternListEntry *next;
		unsigned int frameTypes;
		bool isActive;
		char *pattern;
	};
	struct IOBuffer
	{
		char *buffer;
		unsigned int used;
		unsigned int alloc;
		bool lastWasCR;
	};

	void *field04;
	unsigned int numHrTranslators;
	IOFactoryListEntry *firstIOFactory;
	CmdInterfaceListEntry *firstCmdGroup;
	unsigned int curStackFrame;
	FrameHashEntry *frameHash[FRAME_HASH_SIZE];
	FrameHashEntry *nextUnusedFrameHash;
	unsigned int numAvailableFrameHash;
	int refCount;
	KnownLogGroupList *firstLogGroup;
	IOBuffer ioBuffer[7];
	int curType;
	char curSource[256];
	int disableAssertsEtc;
	FrameHashEntry *curFrameEntry;
	PatternListEntry *firstPatternEntry;
	PatternListEntry *lastPatternEntry;
	FrameCommand *frameCommands;
	unsigned int numFrameCommands;
	unsigned int frameCommandsAlloc;
	char curCommandGroup[100];
	bool alwaysFlush;
	bool noStackWalk;
	bool timeStamp;
	unsigned char field9E7B;
	char m_prefix[16];
	int m_radix;
	char m_version[64];
	char m_intVersion[64];
	char m_buildDate[64];
	int m_width;
	char m_fillChar;
	signed char windowed;
	bool fullMiniDump;
	bool logErrorsToFile;
	bool noAssertDialog;
	void *m_mutex;
	unsigned int m_threadId;
	bool inAssertDialog;

private:
	friend class DebugCmdInterfaceDebug;
	friend class DebugExceptionhandler;
	Debug();
	Debug(const Debug &);
	Debug &operator=(const Debug &);
	static Debug *PreStaticInit();
	static void PostStaticInit();
	static void StaticExit();
	FrameHashEntry *LookupFrame(unsigned int address);
	FrameHashEntry *AddFrameEntry(unsigned int address, unsigned int type, const char *fileOrGroup, int line);
	FrameHashEntry *GetFrameEntry(unsigned int address, unsigned int type, const char *fileOrGroup, int line);
	void UpdateFrameStatus(FrameHashEntry &entry);
	void AddPatternEntry(unsigned int types, bool active, const char *pattern);
	bool ExecCommand(const char *start, const char *end);
	unsigned int ScheduleFrameCommand(int frame, const char *command);
};

extern Debug *theDebug;

#endif

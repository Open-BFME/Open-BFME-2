// ?load@GameTextTable@@QAE_NPBD0PA_N@Z
// partial score=0.9 date=2026-10-08
#if 0
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/shims/subsystem_bfme2 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// stlport
// GameTextManager (vtable 0x00804FA8, 0x44 bytes, created by
// CreateGameTextInterface 0x002E651F): the string table subsystem.
// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GameText.cpp
// BFME2 keeps Zero Hour's subsystem but moves the label table into a
// 12-byte table object (count, StringInfo array, sorted StringLookUp array)
// with its own STR/CSF readers; the manager holds two of them, the game's
// strings and the map's.
typedef bool Bool;

#include <vector>
#include <algorithm>
#include "ascii_string.h"
#include "unicode_string.h"
#include "subsystem_interface.h"

extern "C" __declspec(dllimport) char *__cdecl strchr(const char *, int);
extern "C" __declspec(dllimport) int __cdecl isspace(int);
extern "C" __declspec(dllimport) char *__cdecl strncpy(char *, const char *, unsigned int);
extern "C" __declspec(dllimport) unsigned short *__cdecl wcsncpy(unsigned short *, const unsigned short *, unsigned int);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextW(void *hwnd, const unsigned short *text);

// File (vtable slots read from the calls below) and the FileSystem calls.
class File
{
public:
	virtual ~File();
	virtual Bool open(const char *filename, int access);
	virtual void close();
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, int mode);
	virtual Bool nextLine(char *buf, int bufSize);
	virtual Bool scanInt(int &newInt);
	virtual Bool scanReal(float &newReal);
	virtual Bool scanString(AsciiString &newString);
	virtual Bool print(const char *format, ...);
	virtual int size();
	virtual int position();
	virtual char *readEntireAndClose();
	virtual File *convertToRAMFile();

	AsciiString m_nameStr;	// +0x04
	int m_access;			// +0x08
	Bool m_open;			// +0x0c
	Bool m_deleteOnClose;	// +0x0d
};

struct FileInfo
{
	int sizeHigh;
	int sizeLow;
	int timestampHigh;
	int timestampLow;
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int bufferSize);
	bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const;
	bool getFileInfo(const char *filename, FileInfo *fileInfo) const;
};

extern FileSystem *TheFileSystem;

class InGameUI
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13(); virtual void pad14(); virtual void pad15();
	virtual void message(UnicodeString format, ...);
};

extern InGameUI *TheInGameUI;
extern class ThingFactory *TheThingFactory;
extern void *ApplicationHWnd;
AsciiString GetRegistryLanguage(void);

// The debug object's crash path (slots read from the calls below).
class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
	class Format
	{
	public:
		Format(const char *format, ...);
		char m_buffer[512];
	};
	Debug &operator<<(const Format &f) { return operator<<(f.m_buffer); }
};

extern Debug *theDebug;
void __cdecl _bfme_debugRecordCallsite(int kind);

#define DEBUG_CRASH(m) \
	do { \
		_bfme_debugRecordCallsite(1); \
		theDebug->SkipNext(); \
		Debug &dbg = theDebug->CrashBegin(0, 0, 0); \
		dbg << Debug::Format m; \
		dbg.CrashDone(1); \
	} while (0)

// Placeholder spellings of the rowed callees this unit reaches.
class Rva002E5611
{
public:
	int rva002E5611(const Rva002E5611 &other);
};

class Rva002CF1E2
{
public:
	void rva002CF1E2();
};

class Rva002E6451
{
public:
	void *rva002E6451(const char *label);
};

class Rva002E6158
{
public:
	~Rva002E6158();
};

// One label/text pair; the array is new[]'d with a cookie (??_U plus the
// rowed vector dtor 0x002E5791).
struct StringInfo
{
	AsciiString label;
	UnicodeString text;
};

struct StringLookUp
{
	AsciiString *label;
	void *info;
};

struct Rva002E5678Cmp
{
	bool operator()(const StringLookUp &a, const StringLookUp &b) const;
};

namespace _STL
{
template <> void sort<StringLookUp *, Rva002E5678Cmp>(StringLookUp *, StringLookUp *, Rva002E5678Cmp);
}

// The label table. clear (0x002E6158) frees both arrays; find (0x002E6451)
// binary-searches the lookup array.
class GameTextTable
{
public:
	GameTextTable() : m_count(0), m_info(0), m_lookup(0) {}
	Bool load(const char *strFile, const char *csfFile, Bool *usedCSF);
	Bool readSTR(const char *filename);
	Bool readCSF(const char *filename);

	unsigned int m_count;	// +0x00
	StringInfo *m_info;		// +0x04
	StringLookUp *m_lookup;	// +0x08
};

struct NoString
{
	NoString *next;
	UnicodeString text;
};

extern const char *g_strFile;
extern const char *g_csfFile;
extern Bool g_useStringFile;
extern UnicodeString TheTranslatedString;

class GameTextManager : public SubsystemInterface
{
public:
	GameTextManager();
	virtual ~GameTextManager();
	virtual void init();
	virtual bool vslot04(int);
	virtual void reset();
	virtual void update();
	virtual UnicodeString fetch(const char *label, Bool *exists);
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists);
	virtual UnicodeString *fetchPtr(const char *label, Bool *exists);
	virtual UnicodeString *fetchPtr(const AsciiString &label, Bool *exists);
	virtual _STL::vector<AsciiString> &getStringsWithLabelPrefix(const AsciiString &label);
	virtual void initMapStringFile(const AsciiString &filename);
	virtual void setTranslateMode(int mode);
	virtual int getTranslateMode();
	virtual void deinit();

	FileInfo m_fileInfo;					// +0x0c
	Bool m_usedCSF;							// +0x1c
	Bool m_initialized;						// +0x1d
	UnicodeString m_failed;					// +0x20
	NoString *m_noStringList;				// +0x24
	int m_unk28;							// +0x28
	GameTextTable *m_textTable;				// +0x2c
	GameTextTable *m_mapTable;				// +0x30
	_STL::vector<AsciiString> m_asciiStringVec;	// +0x34
	int m_translateMode;					// +0x40
};

#endif
// ?load@GameTextTable@@QAE_NPBD0PA_N@Z @0x002E68EC 159B
Bool GameTextTable::load(const char *strFile, const char *csfFile, Bool *usedCSF)
{
	((Rva002E6158 *)this)->~Rva002E6158();
	if (!strFile || !readSTR(strFile)) {
		if (!csfFile)
			return false;
		Bool ok = readCSF(csfFile);
		if (usedCSF)
			*usedCSF = ok;
		if (!ok)
			return false;
	}
	m_lookup = new StringLookUp[m_count];
	StringLookUp *lookup = m_lookup;
	StringInfo *info = m_info;
	for (unsigned int i = 0; i < m_count; i++) {
		lookup->info = info;
		lookup->label = &info->label;
		lookup++;
		info++;
	}
	_STL::sort(m_lookup, m_lookup + m_count, Rva002E5678Cmp());
	return true;
}


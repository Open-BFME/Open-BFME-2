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

// ??0GameTextManager@@QAE@XZ @0x002E63AA 97B
GameTextManager::GameTextManager()
	: m_usedCSF(false), m_initialized(false),
	  m_failed(L"***FATAL*** String Manager failed to initialize properly"),
	  m_noStringList(0), m_unk28(0), m_textTable(0), m_mapTable(0), m_translateMode(0)
{
}

// ?init@GameTextManager@@UAEXXZ @0x002E698B 173B
void GameTextManager::init()
{
	if (m_initialized)
		return;
	m_textTable = new GameTextTable;
	m_initialized = m_textTable->load(g_useStringFile ? g_strFile : 0, g_csfFile, &m_usedCSF);
	if (m_usedCSF)
		TheFileSystem->getFileInfo(g_csfFile, &m_fileInfo);
	UnicodeString name = fetch("GUI:FullGameName", 0);
	if (ApplicationHWnd)
		SetWindowTextW(ApplicationHWnd, name.str());
}

// ?initMapStringFile@GameTextManager@@UAEXABVAsciiString@@@Z @0x002E6A38 74B
void GameTextManager::initMapStringFile(const AsciiString &filename)
{
	if (!m_mapTable)
		m_mapTable = new GameTextTable;
	m_mapTable->load(filename.str(), 0, 0);
}

// ?readSTR@GameTextTable@@QAE_NPBD@Z @0x002E57C6 928B
// The text STR format: label line, quoted string line(s), END.
Bool GameTextTable::readSTR(const char *filename)
{
	File *file = TheFileSystem->openFile(filename, 1, 0);
	if (!file)
		return false;
	file->m_deleteOnClose = true;
	int size = file->size();
	char *data = new char[size + 2];
	file->read(data, size);
	file->close();
	char *ptr = data;
	data[size] = '\n';
	data[size + 1] = 0;
	char *eol;
	while ((eol = strchr(ptr, '\n')) != 0) {
		while (isspace((unsigned char)*ptr))
			ptr++;
		if (eol - ptr > 2 && (*(unsigned int *)ptr & 0x40DFDFDF) == 0x444E45)
			m_count++;
		ptr = eol + 1;
	}
	UnicodeString fmt(L"%hs");
	if (m_count) {
		m_count += 500;
		m_info = new StringInfo[m_count];
		char *next = data;
		const char *label = 0;
		int state = 0;
		unsigned int count = 0;
		int lineNum = 0;
		for (eol = strchr(next, '\n'); eol; eol = strchr(next, '\n')) {
			char *line = next;
			lineNum++;
			next = eol + 1;
			if (line == eol)
				continue;
			*eol = 0;
			while (isspace((unsigned char)*line))
				line++;
			if (line == eol)
				continue;
			if (eol - line > 1 && *(short *)line == '//')
				continue;
			do
				eol--;
			while (isspace((unsigned char)*eol));
			*++eol = 0;
			switch (state) {
			case 0:
				m_info[count].label = line;
				label = line;
				state = 1;
				break;
			case 1:
				if (*line == '"') {
					do
						eol--;
					while (*eol != '"');
					if (eol != line) {
						*eol = 0;
						do
							line++;
						while (isspace((unsigned char)*line));
						char *src = strchr(line, '\\');
						if (src) {
							char *dst = src;
							while (*src) {
								if (*src != '\\') {
									*dst = *src;
								} else {
									switch (*++src) {
									case 0: src--; break;
									case '"': *dst = '"'; break;
									case '\'': *dst = '\''; break;
									case '?': *dst = '?'; break;
									case '\\': *dst = '\\'; break;
									case 'n': *dst = '\n'; break;
									case 't': *dst = '\t'; break;
									}
								}
								src++;
								dst++;
							}
							*dst = 0;
						}
						m_info[count].text.format(&fmt, line);
						state = 2;
						break;
					}
					DEBUG_CRASH(("End quotes missing for string '%s' in file '%s', line %d", label, filename, lineNum));
				}
				count--;
				// fall through: a label without a string must be followed by END
			case 2:
				if (eol - line > 2 && (*(unsigned int *)line & 0xFFDFDFDF) == 0x444E45) {
					state = 0;
					count++;
				} else {
					DEBUG_CRASH(("Unrecognized text or missing 'END' tag for string '%s' in file '%s', line %d", label, filename, lineNum));
				}
				break;
			}
		}
		m_count = count;
	}
	delete[] data;
	return m_count > 0;
}

// The in-memory CSF layout (Zero Hour reads the same records field by field).
enum
{
	CSF_ID = 0x43534620,				// ' FSC'
	CSF_LABEL = 0x4c424c20,				// ' LBL'
	CSF_STRING = 0x53545220,			// ' RTS'
	CSF_STRINGWITHWAVE = 0x53545257		// 'WRTS'
};

struct CSFHeader
{
	int id;
	int version;
	unsigned int num_labels;
	int num_strings;
	int skip;
	int langid;
};

struct CSFLabel
{
	int id;
	unsigned int num_strings;
	int length;
};

struct CSFString
{
	int id;
	int length;
};

// ?readCSF@GameTextTable@@QAE_NPBD@Z @0x002E5EA5 487B
Bool GameTextTable::readCSF(const char *filename)
{
	char buffer[0x2800];
	unsigned short wbuffer[0x2800];
	File *file = TheFileSystem->openFile(filename, 0x21, 0);
	if (!file)
		return false;
	file->m_deleteOnClose = true;
	char *data = file->readEntireAndClose();
	unsigned int count = 0;
	CSFHeader *header = (CSFHeader *)data;
	char *ptr = data + sizeof(CSFHeader);
	if (header->id == CSF_ID) {
		m_info = new StringInfo[header->num_labels];
		while (header->num_labels--) {
			CSFLabel *label = (CSFLabel *)ptr;
			ptr += sizeof(CSFLabel);
			if (label->id != CSF_LABEL)
				break;
			strncpy(buffer, ptr, label->length);
			buffer[label->length] = 0;
			ptr += label->length;
			Bool found = false;
			while (label->num_strings--) {
				CSFString *str = (CSFString *)ptr;
				ptr += sizeof(CSFString);
				switch (str->id) {
				case CSF_STRING:
					if (!found) {
						wcsncpy(wbuffer, (unsigned short *)ptr, str->length);
						wbuffer[str->length] = 0;
						ptr += str->length * 2;
						for (unsigned short *p = wbuffer; *p; p++)
							*p = ~*p;
						m_info[count].label = buffer;
						m_info[count].text = wbuffer;
						count++;
						found = true;
					}
					break;
				case CSF_STRINGWITHWAVE:
					ptr += *(int *)ptr + 4;
					break;
				default:
					header->num_labels = 0;
					label->num_strings = 0;
					break;
				}
			}
		}
		m_count = count;
	}
	delete[] data;
	return m_count > 0;
}

// ?fetchPtr@GameTextManager@@UAEPAVUnicodeString@@PBDPA_N@Z @0x002E65B1 228B
UnicodeString *GameTextManager::fetchPtr(const char *label, Bool *exists)
{
	if (m_translateMode == 1) {
		TheTranslatedString.translate(label);
		return &TheTranslatedString;
	}
	UnicodeString *text = 0;
	if (m_textTable)
		text = (UnicodeString *)((Rva002E6451 *)m_textTable)->rva002E6451(label);
	if (!text && m_mapTable)
		text = (UnicodeString *)((Rva002E6451 *)m_mapTable)->rva002E6451(label);
	if (exists)
		*exists = text != 0;
	if (text)
		return text;
	UnicodeString missing;
	missing.format(L"MISSING: '%hs'", label);
	NoString *noString;
	for (noString = m_noStringList; noString; noString = noString->next) {
		if (!noString->text.compare(missing))
			return &noString->text;
	}
	noString = new NoString;
	noString->text.set(missing);
	noString->next = m_noStringList;
	m_noStringList = noString;
	return &noString->text;
}

// ?vslot04@GameTextManager@@UAE_NH@Z @0x002E5D62 248B
// Reload the string file when its size or timestamp changed.
bool GameTextManager::vslot04(int)
{
	FileInfo info;
	if (m_usedCSF) {
		AsciiString path;
		path.format(g_csfFile, GetRegistryLanguage().str());
		TheFileSystem->getFileInfo(path, &info);
	} else {
		TheFileSystem->getFileInfo(g_strFile, &info);
	}
	if (((Rva002E5611 *)&m_fileInfo)->rva002E5611(*(Rva002E5611 *)&info)) {
		deinit();
		init();
		if (TheInGameUI)
			TheInGameUI->message(UnicodeString(L"RIF: String file reloaded"));
		if (TheThingFactory)
			((Rva002CF1E2 *)TheThingFactory)->rva002CF1E2();
		return true;
	}
	return false;
}

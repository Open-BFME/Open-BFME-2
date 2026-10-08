// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// GameState auto-save (0x002DD7E6), populateSaveGameListbox (0x002DF3B0) and
// the file-static map display-name helper both call (0x002DC16A). They share
// this unit because retail passes the helper's map label in ESI: cl 7.1's
// per-unit custom convention for an internal-linkage function whose call
// sites it can see.
//
// Target evidence: the GUI:AutoSaveName label, the wide pointer cells at
// VA 0x00DBD04C (L"00000000") and 0x00DBD050 (L"__AUTO#SAVE__") beside the
// save-file suffix cells of 0x002DBC97, the call into GameState::saveGame
// 0x002DD38D, and the single caller 0x005212AC (ECX = TheGameState). The
// helper looks the map up in TheMapCache (findMap, bfme_getBaseDisplayName),
// falls back to TheGameText's lookup of the label and finally formats the
// label itself with L"%S". BFME 1's auto-save (0x003BDB80 there) passes the
// same "__AUTO#SAVE__" description. Original names of both are unknown.
//
// populateSaveGameListbox is ZH's GameState method of that name, extended the
// way BFME 1's four-argument version (0x001121A0 there) is: a second list for
// auto-saves (now chosen by SaveGameInfo's IsAutoSaveOrNot field instead of
// the description), a "GUI:NewSaveGame" entry, and per-filter save-type tests.
// BFME 2 adds the iterateSaveFiles mode argument, the file name column taken
// through the 0x00BBA4EC slot, and a per-filter table of column contents.
// Single caller: AptSaveLoad 0x00436FF6 with TheGameState.
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"
// Retail expands this header test inline here; the shim keeps it out of line.
template<> inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length == 0; }

typedef unsigned short WideChar;

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13();
	// cl 7.1 lays overloaded virtuals out in reverse: slot 14 (+0x38) takes
	// the AsciiString label, slot 15 (+0x3C) the C string.
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

class MapMetaData
{
public:
	UnicodeString bfme_getBaseDisplayName();
};
class MapCache
{
public:
	const MapMetaData *findMap(AsciiString mapName);
};
extern MapCache *TheMapCache;

// VA 0x00DBD04C and 0x00DBD050 (see the header comment).
const WideChar *TheAutoSaveFileNameBase = L"00000000";
const WideChar *TheAutoSaveDescription = L"__AUTO#SAVE__";

class GameWindow;
void GadgetListBoxReset(GameWindow *listbox);
int GadgetListBoxGetNumColumns(GameWindow *listbox);
void GadgetListBoxSetColumnWidths(GameWindow *listbox, int numColumns, int *widths);
int GadgetListBoxAddEntryText(GameWindow *listbox, UnicodeString text, int color, int row, int column, bool overwrite = true);
void GadgetListBoxSetItemData(GameWindow *listbox, void *data, int row, int column = 0);
void GadgetListBoxSetSelected(GameWindow *listbox, int selectIndex);

inline int GameMakeColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	return ((unsigned int)alpha << 24) | ((unsigned int)red << 16) | ((unsigned int)green << 8) | blue;
}

struct SYSTEMTIME
{
	unsigned short wYear, wMonth, wDayOfWeek, wDay;
	unsigned short wHour, wMinute, wSecond, wMilliseconds;
};
UnicodeString Rva002DBFAD(SYSTEMTIME date);	// date text (GetDateFormat)
UnicodeString Rva002DC081(SYSTEMTIME time, int flags);	// time text (GetTimeFormat)

// Indirect cdecl slot at VA 0x00BBA4EC, called as _wsplitpath(path, 0, 0,
// fname, 0) with a 256-character name buffer; the slot's own identity is
// unresolved (see its symbols.csv pin).
typedef void (__cdecl *Rva007BA4ECProc)(const WideChar *path, WideChar *drive,
		WideChar *dir, WideChar *fname, WideChar *ext);
extern "C" Rva007BA4ECProc rva007BA4EC;

// BFME 2 SaveGameInfo (0xDE8 bytes; layout from its copy constructor and
// xfer in SaveGameInfoCopyBFME2.cpp, where its rows keep the opaque class
// name). Only the fields read here are named.
struct SaveDate
{
	bool isNewerThan(SaveDate *other);
	unsigned short year, month, day, dayOfWeek;
	unsigned short hour, minute, second, milliseconds;
};

struct BfmeSubobject0022CE19
{
	BfmeSubobject0022CE19();
	virtual ~BfmeSubobject0022CE19();
	BfmeSubobject0022CE19 &operator=(const BfmeSubobject0022CE19 &that);

	AsciiString saveGameMapName;	// +0x04
	AsciiString pristineMapName;	// +0x08
	AsciiString mapLabel;	// +0x0C
	SaveDate date;	// +0x10
	UnicodeString description;	// +0x20
	int saveFileType;	// +0x24
	int isAutoSave;	// +0x28, xfer'd through "IsAutoSaveOrNot"
	AsciiString missionMapName;	// +0x2C
	UnicodeString text30;	// +0x30
	UnicodeString text34;	// +0x34, list column type 2
	char m_pad38[0xDE0 - 0x38];
	bool flagDE0;	// +0xDE0, SaveGameInfo+0x44 sub-object byte +0xD9C
	char m_padDE1[0xDE8 - 0xDE1];
};
typedef BfmeSubobject0022CE19 SaveGameInfo;

// 0xDF4 bytes: new'd by addGameToAvailableList and built by the default
// constructor at 0x00229811, which keeps its address name there.
struct Rva00229811
{
	Rva00229811();

	UnicodeString filename;
	SaveGameInfo saveGameInfo;	// +0x04
	Rva00229811 *next;	// +0xDEC
	Rva00229811 *prev;	// +0xDF0
};
typedef Rva00229811 AvailableGameInfo;

typedef void (*IterateSaveFileCallback)(UnicodeString filename, void *userData);
void addGameToAvailableList(UnicodeString filename, void *userData);	// 0x002DF0B4

// Xfer as the save reader calls it. Each slot keeps its own name: cl 7.1
// lays overloaded virtuals out in reverse.
class Xfer
{
public:
	virtual ~Xfer();
	virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
	virtual int beginBlock(const char *name);	// slot 5
	virtual void endBlock();	// slot 6
	virtual void skipBlock(const char *name);	// slot 7
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void xferSnapshot(Snapshot *snapshot);	// slot 12 (+0x30)
	virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
	virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
	virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
	virtual void v25(); virtual void v26();
	virtual void xferAsciiString(AsciiString *asciiStringData);	// slot 27 (+0x6C)
};

// The reader: an Xfer with its own vtable, built from three null pointers
// (same view as ConnectionManager_heroData.cpp).
struct Rva0060C3C3Stream;
class Rva0060C5FA : public Xfer
{
public:
	Rva0060C5FA(void *a1, void *a2, void *a3);

private:
	char m_pad04[0x20 - 4];
};

class XferLoad
{
public:
	bool Open(Rva0060C3C3Stream *stream, int *version);
};

class Rva0060C45E
{
public:
	void clear();
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

private:
	char *text;
	int tag;
};

class File
{
public:
	virtual ~File();
	virtual bool open(const char *filename, int access);
	virtual void close();
};

// TheFileSystem (VA 0x00E06A48); 0x00600676 forwards to the archive file
// system's slot 2 without reading this.
class FileSystem
{
public:
	File *rva00600676(const WideChar *filename, int access, int bufferSize);
};
extern FileSystem *TheFileSystem;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

// VA 0x00DBD038, ZH's SAVE_FILE_EOF token.
extern const char *SAVE_FILE_EOF;

// clearAvailableGames 0x002DE311 keeps the address spelling it is pinned
// under (Rva002DEE9AClear.cpp, GameStateDtor.cpp).
class Rva002DEE9AOwner
{
public:
	void rva002DE311();
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	char m_pad04[0xC - 4];
};

enum SnapshotType { SNAPSHOT_SAVELOAD = 0 };

class GameState : public SubsystemInterface, public Snapshot
{
public:
	GameState();
	virtual ~GameState();

	int determineCurrentGameSaveFileMode();
	void *rva002DBC97Get(int mode);
	int saveGame(UnicodeString filename, const UnicodeString &desc, int which, bool showMessage, int param5);
	int rva002DD7E6AutoSave();
	bool getSaveGameInfoFromFile(UnicodeString filename, SaveGameInfo *saveGameInfo);
	void iterateSaveFiles(IterateSaveFileCallback callback, void *userData, int mode);
	void populateSaveGameListbox(GameWindow *listbox, GameWindow *autoSaveListbox, bool newSave, int filter);

protected:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);

private:
	struct SnapshotBlock;
	SnapshotBlock *findBlockInfoByToken(AsciiString token, SnapshotType which);

	char m_pad10[0x24 - 0x10];	// m_snapshotBlockList[5]
	SaveGameInfo m_gameInfo;	// +0x24
	char m_padE0C[0xE14 - 0xE0C];
	AvailableGameInfo *m_availableGames;	// +0xE14
	char m_padE18[0xE1C - 0xE18];
};
extern GameState *TheGameState;

// ?getMapDisplayName@@YA?AVUnicodeString@@ABVAsciiString@@@Z @0x002DC16A 253B
static UnicodeString getMapDisplayName(const AsciiString &mapLabel)
{
	UnicodeString name(L"");
	if (TheMapCache)
	{
		const MapMetaData *map = TheMapCache->findMap(mapLabel);
		if (map)
			name = const_cast<MapMetaData *>(map)->bfme_getBaseDisplayName();
	}
	if (name.isEmpty())
	{
		bool exists = false;
		name = TheGameText->fetch(mapLabel, &exists);
		if (!exists)
			name.format(L"%S", mapLabel.str());
	}
	return name;
}

// ?rva002DD7E6AutoSave@GameState@@QAEHXZ @0x002DD7E6 290B
int GameState::rva002DD7E6AutoSave()
{
	int mode = determineCurrentGameSaveFileMode();
	UnicodeString nameFormat(TheAutoSaveFileNameBase);
	if (TheGameText)
		nameFormat = TheGameText->fetch("GUI:AutoSaveName");
	UnicodeString mapName = getMapDisplayName(m_gameInfo.pristineMapName);
	UnicodeString filename;
	filename.format(nameFormat.str(), mapName.str());
	filename.concat((const WideChar *)rva002DBC97Get(mode));
	int result;
	{
		UnicodeString description(TheAutoSaveDescription);
		result = saveGame(filename, description, 0, false, 1);
	}
	return result;
}

// ?populateSaveGameListbox@GameState@@QAEXPAVGameWindow@@0_NH@Z @0x002DF3B0 1148B
void GameState::populateSaveGameListbox(GameWindow *listbox, GameWindow *autoSaveListbox, bool newSave, int filter)
{
	if (!listbox)
		return;
	GadgetListBoxReset(listbox);
	if (autoSaveListbox)
		GadgetListBoxReset(autoSaveListbox);
	int columnWidths[4] = { 28, 36, 19, 17 };
	if (GadgetListBoxGetNumColumns(listbox) != 4)
		GadgetListBoxSetColumnWidths(listbox, 4, columnWidths);
	if (autoSaveListbox && GadgetListBoxGetNumColumns(autoSaveListbox) != 4)
		GadgetListBoxSetColumnWidths(autoSaveListbox, 4, columnWidths);

	unsigned int normalCount = 0;
	unsigned int autoCount = 0;
	if (newSave)
	{
		UnicodeString newSaveText = TheGameText->fetch("GUI:NewSaveGame");
		int index = GadgetListBoxAddEntryText(listbox, newSaveText, GameMakeColor(200, 200, 200, 255), -1, -1);
		GadgetListBoxSetItemData(listbox, 0, index);
		++normalCount;
	}

	((Rva002DEE9AOwner *)this)->rva002DE311();
	int mode = 1;
	if (filter == 2)
		mode = 2;
	else if (filter == 8)
		mode = 4;
	else if (filter == 16)
		mode = 6;
	iterateSaveFiles(addGameToAvailableList, &m_availableGames, mode);

	for (AvailableGameInfo *info = m_availableGames; info; info = info->next)
	{
		SaveGameInfo *save = &info->saveGameInfo;
		if (filter == 1 && save->saveFileType != 1 && save->saveFileType != 0 && save->saveFileType != 8)
			continue;
		if (filter == 2 && save->saveFileType != 2)
			continue;
		if (filter == 8 && save->saveFileType != 4 && save->saveFileType != 3)
			continue;
		if (filter == 16 && save->saveFileType != 6)
			continue;

		WideChar fileName[256];
		rva007BA4EC(info->filename.str(), 0, 0, fileName, 0);
		UnicodeString displayName(fileName);
		GameWindow *list = save->isAutoSave == 1 ? autoSaveListbox : listbox;
		if (!list)
			continue;

		SYSTEMTIME systemTime;
		systemTime.wYear = save->date.year;
		systemTime.wMonth = save->date.month;
		systemTime.wDayOfWeek = save->date.dayOfWeek;
		systemTime.wDay = save->date.day;
		systemTime.wHour = save->date.hour;
		systemTime.wMinute = save->date.minute;
		systemTime.wSecond = save->date.second;
		systemTime.wMilliseconds = save->date.milliseconds;
		UnicodeString mapName = getMapDisplayName(save->mapLabel);

		int color;
		if (save->saveFileType == 1 || save->saveFileType == 4)
			color = GameMakeColor(239, 204, 82, 255);
		else if (save->saveFileType == 6)
			color = save->flagDE0 ? GameMakeColor(239, 204, 82, 255) : GameMakeColor(119, 102, 41, 255);
		else
			color = GameMakeColor(255, 255, 255, 255);

		int columnTypes[4][4] = {
			{ 4, 1, 5, 6 },
			{ 3, 1, 5, 6 },
			{ 1, 0, 5, 6 },
			{ 1, 2, 5, 6 },
		};
		int *columns = columnTypes[0];
		if (filter == 2)
			columns = columnTypes[1];
		else if (filter == 8)
			columns = columnTypes[2];
		else if (filter == 16)
			columns = columnTypes[3];

		int index = -1;
		for (int column = 0; column < 4; ++column)
		{
			UnicodeString text;
			switch (columns[column])
			{
			case 1:
				text = displayName;
				break;
			case 2:
				text = save->text34;
				break;
			case 3:
			case 4:
				text = mapName;
				break;
			case 5:
				text = Rva002DC081(systemTime, 0);
				break;
			case 6:
				text = Rva002DBFAD(systemTime);
				break;
			default:
				text = L" ";
				break;
			}
			index = GadgetListBoxAddEntryText(list, text, color, index, column);
		}
		GadgetListBoxSetItemData(list, info, index);
		if (list == autoSaveListbox)
			++autoCount;
		else
			++normalCount;
	}

	if (normalCount > 0)
	{
		GadgetListBoxSetSelected(listbox, 0);
		GadgetListBoxSetSelected(autoSaveListbox, -1);
	}
	else if (autoCount > 0)
	{
		GadgetListBoxSetSelected(listbox, -1);
		GadgetListBoxSetSelected(autoSaveListbox, 0);
	}
	else
	{
		GadgetListBoxSetSelected(listbox, -1);
		GadgetListBoxSetSelected(autoSaveListbox, -1);
	}
}

// ?getSaveGameInfoFromFile@GameState@@QAE_NVUnicodeString@@PAUBfmeSubobject0022CE19@@@Z @0x002DEEC3 497B
bool GameState::getSaveGameInfoFromFile(UnicodeString filename, SaveGameInfo *saveGameInfo)
{
	bool done = false;
	if (filename.isEmpty() || saveGameInfo == 0)
		return false;

	bool result;
	File *file = TheFileSystem->rva00600676(filename.str(), 0x41, 0);
	if (file == 0)
		result = false;
	else
	{
		Rva0060C5FA xferLoad(0, 0, 0);
		unsigned int version;
		if (!((XferLoad *)&xferLoad)->Open((Rva0060C3C3Stream *)file, (int *)&version))
			result = false;
		else if (version > 1)
			result = false;
		else
		{
			while (!done)
			{
				AsciiString token;
				((Xfer *)&xferLoad)->xferAsciiString(&token);
				if (token.compareNoCase(SAVE_FILE_EOF) == 0)
					done = true;
				else
				{
					if (findBlockInfoByToken(token, SNAPSHOT_SAVELOAD) == 0)
						throw XferException(0, 0);
					if (_strcmpi(token.str(), "CHUNK_GameState") == 0)
					{
						GameState gameState;
						try
						{
							xferLoad.beginBlock("?");
							((Xfer *)&xferLoad)->xferSnapshot(&gameState);
							xferLoad.endBlock();
						}
						catch (...)
						{
							throw;
						}
						*saveGameInfo = gameState.m_gameInfo;
						done = true;
					}
					else
						xferLoad.skipBlock("?");
				}
			}
			((Rva0060C45E *)&xferLoad)->clear();
			result = true;
		}
		file->close();
	}
	return result;
}

// ?addGameToAvailableList@@YAXVUnicodeString@@PAX@Z @0x002DF0B4 317B
// The iterateSaveFiles callback: read the file's SaveGameInfo and insert a
// new AvailableGameInfo into the list at userData, newest first. The catch
// (...) funclet at 0x002DF1EB resumes at the filename release 0x002DF116.
// A failed read returns past the list code while an insert jumps to the end
// of the try: that is the order retail lays the shared cleanup out in.
void addGameToAvailableList(UnicodeString filename, void *userData)
{
	AvailableGameInfo **listHead = (AvailableGameInfo **)userData;

	try
	{
		SaveGameInfo saveGameInfo;
		if (!TheGameState->getSaveGameInfoFromFile(filename, &saveGameInfo))
			return;

		AvailableGameInfo *newInfo = new AvailableGameInfo;

		newInfo->prev = 0;
		newInfo->next = 0;
		newInfo->saveGameInfo = saveGameInfo;
		newInfo->filename = filename;

		if (*listHead == 0)
			*listHead = newInfo;
		else
		{
			AvailableGameInfo *curr, *prev = 0;
			for (curr = *listHead; curr != 0; curr = curr->next)
			{
				prev = curr;
				if (newInfo->saveGameInfo.date.isNewerThan(&curr->saveGameInfo.date))
				{
					if (curr->prev)
						curr->prev->next = newInfo;
					else
						*listHead = newInfo;
					newInfo->prev = curr->prev;
					curr->prev = newInfo;
					newInfo->next = curr;
					goto done;
				}
			}
			prev->next = newInfo;
			newInfo->prev = prev;
		}
	done:
		;
	}
	catch (...)
	{
	}
}

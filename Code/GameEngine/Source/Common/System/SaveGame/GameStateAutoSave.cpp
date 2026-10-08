// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
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
// xfer in SaveGameInfoCopyBFME2.cpp). Only the fields read here are named.
struct SaveGameInfo
{
	void *m_vtable;
	AsciiString saveGameMapName;	// +0x04
	AsciiString pristineMapName;	// +0x08
	AsciiString mapLabel;	// +0x0C
	unsigned short year, month, day, dayOfWeek;	// +0x10
	unsigned short hour, minute, second, milliseconds;
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

struct AvailableGameInfo
{
	UnicodeString filename;
	SaveGameInfo saveGameInfo;	// +0x04
	AvailableGameInfo *next;	// +0xDEC
	AvailableGameInfo *prev;	// +0xDF0
};

typedef void (*IterateSaveFileCallback)(UnicodeString filename, void *userData);
void addGameToAvailableList(UnicodeString filename, void *userData);	// 0x002DF0B4

// clearAvailableGames 0x002DE311 keeps the address spelling it is pinned
// under (Rva002DEE9AClear.cpp, GameStateDtor.cpp).
class Rva002DEE9AOwner
{
public:
	void rva002DE311();
};

class GameState
{
public:
	int determineCurrentGameSaveFileMode();
	void *rva002DBC97Get(int mode);
	int saveGame(UnicodeString filename, const UnicodeString &desc, int which, bool showMessage, int param5);
	int rva002DD7E6AutoSave();
	void iterateSaveFiles(IterateSaveFileCallback callback, void *userData, int mode);
	void populateSaveGameListbox(GameWindow *listbox, GameWindow *autoSaveListbox, bool newSave, int filter);

private:
	char m_pad0[0x2C];
	AsciiString m_pristineMapName;	// +0x2C
	char m_pad30[0xE14 - 0x30];
	AvailableGameInfo *m_availableGames;	// +0xE14
};

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
	UnicodeString mapName = getMapDisplayName(m_pristineMapName);
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
		systemTime.wYear = save->year;
		systemTime.wMonth = save->month;
		systemTime.wDayOfWeek = save->dayOfWeek;
		systemTime.wDay = save->day;
		systemTime.wHour = save->hour;
		systemTime.wMinute = save->minute;
		systemTime.wSecond = save->second;
		systemTime.wMilliseconds = save->milliseconds;
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

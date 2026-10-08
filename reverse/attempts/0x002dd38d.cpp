// ?saveGame@GameState@@QAEHVUnicodeString@@ABV2@H_NH@Z
// partial score=0.99 date=2026-10-08
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// GameState save path: the save-file suffix getter 0x002DBC97 and
// GameState::saveGame 0x002DD38D, which calls it. They share this unit
// because retail saveGame keeps EDX live across the call to 0x002DBC97,
// which MSVC 7.1 does only for a callee defined earlier in the same unit.
//
// Target evidence for saveGame: the GUI:GameSaveComplete,
// GUI:ErrorSavingGame and GUI:Error labels, the XferSave writer opened on a
// File from TheFileSystem and handed to xferSaveData (0x002DCE24), and the
// SaveGameInfo fields it fills at +0x34..+0x58 (date from GetLocalTime).
// The control flow follows Zero Hour's GameState::saveGame (donor); BFME2
// adds the File stream, the save mode from 0x002DBE62 and the player and
// hero names from the game info slots. The flag byte at VA 0x00E02D7B is
// set only by the command-line handler 0x003B9A9C and read here as
// XferSave::Open's third argument; its original name is unknown.
#include "ascii_string.h"
#include "unicode_string.h"
// Retail expands this header test inline here; the shim keeps it out of line.
template<> inline bool StringBase<unsigned short>::isEmpty() const { return !m_data || m_data->length == 0; }

typedef unsigned short WideChar;
typedef struct _SYSTEMTIME {
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDayOfWeek;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
} SYSTEMTIME;
extern "C" __declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME *lpSystemTime);

enum SnapshotType { SNAPSHOT_SAVELOAD = 0 };

class Xfer
{
public:
	virtual ~Xfer();
};

class XferSave : public Xfer
{
public:
	XferSave();
	virtual ~XferSave();
	unsigned char Open(Xfer *stream, int version, bool flag);
	void close();

private:
	char m_body[0x3C];
};

class File
{
public:
	virtual ~File();
	virtual bool open(const WideChar *filename, int access);
	virtual void close();
};

class BFME2FileSystemFacade
{
public:
	File *rva00600676(const WideChar *filename, int access, int bufferSize);
	bool rva006006A9(const WideChar *directory);
};
extern class FileSystem *TheFileSystem;
#define TheFileSystem (*(BFME2FileSystemFacade **)&TheFileSystem)

class GameTextInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual UnicodeString fetch(const char *label, bool *exists = 0);	// slot 15 (+0x3C)
	virtual void v16();
	virtual const UnicodeString *fetchPointer(const char *label, bool *exists);	// slot 17 (+0x44)
};
extern GameTextInterface *TheGameText;

class InGameUI
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14();
	virtual void __cdecl message(UnicodeString format, ...);	// slot 16 (+0x40)
	virtual void __cdecl message(AsciiString stringManagerLabel, ...);	// slot 15 (+0x3C)
};
extern InGameUI *TheInGameUI;

class GameWindow;
GameWindow *MessageBoxOk(UnicodeString titleString, UnicodeString bodyString, void (*okCallback)(void));

class CreateAHeroData
{
public:
	char m_pad0[8];
	UnicodeString m_name;	// +0x08
};

class GameSlot
{
public:
	bool isHuman() const;
	bool isObserver() const;
	CreateAHeroData *getHeroData() { return m_hasHero ? &m_hero : 0; }

	char m_pad0[0x30];
	UnicodeString m_name;	// +0x30
	char m_pad34[0x2C];
	bool m_hasHero;	// +0x60
	CreateAHeroData m_hero;	// +0x64
};

class GameInfo
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual int getLocalSlotNum() const;	// slot 13 (+0x34)
	GameSlot *getSlot(int slotNum);
};
extern GameInfo *TheGameInfo;
extern GameInfo *TheSkirmishGameInfo;

class BfmeDfe6e4
{
public:
	void _M_rva00625699(void);
};
class Rva0023D46F
{
public:
	Rva0023D46F(BfmeDfe6e4 *counter);
	~Rva0023D46F(void)
	{
		if (m_counter)
			m_counter->_M_rva00625699();
	}

private:
	BfmeDfe6e4 *m_counter;
};
class Rva00248558Scope
{
public:
	Rva00248558Scope(void);
	~Rva00248558Scope(void);
};
extern BfmeDfe6e4 *theBfmeDfe6e4;

// 12-byte concat proxy returned by 0x002DBD80 (rowed in Rva002DBD80Make.cpp)
// and turned into a wide string by 0x002DD111 (RegistryAsciiPath.cpp).
struct AsciiStringPlusText
{
	operator UnicodeString();
	int m_00;
	const char *m_ptr;
	int m_len;
};
struct Rva002DBD80Val : AsciiStringPlusText
{
};
Rva002DBD80Val Rva002DBD80Make(int x, const unsigned short *s);

class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};
class Rva002DC74A
{
public:
	UnicodeString rva002DC74A(const UnicodeString &leaf) const;
};

// See the header comment: original name unknown.
extern bool TheSaveGameXferFlag;

extern void *g_00DBD03C;
extern void *g_00DBD040;
extern void *g_00DBD044;
extern void *g_00DBD048;

struct SaveDate
{
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short dayOfWeek;
	unsigned short hour;
	unsigned short minute;
	unsigned short second;
	unsigned short milliseconds;
};

class GameState
{
public:
	int determineCurrentGameSaveFileMode();
	UnicodeString rva002DD282(int mode);
	void *rva002DBC97Get(int mode);
	void xferSaveData(Xfer *xfer, SnapshotType which);
	int saveGame(UnicodeString filename, const UnicodeString &desc, int which, bool showMessage, int param5);

private:
	char m_pad0[0x24];
	void *m_gameInfoVtbl;	// +0x24
	AsciiString m_saveGameMapName;	// +0x28
	AsciiString m_pristineMapName;	// +0x2C
	AsciiString m_mapLabel;	// +0x30
	SaveDate m_date;	// +0x34
	UnicodeString m_description;	// +0x44
	int m_saveFileType;	// +0x48
	int m_4C;	// +0x4C
	AsciiString m_missionMapName;	// +0x50
	UnicodeString m_heroName;	// +0x54
	UnicodeString m_playerNames;	// +0x58
};

// ?rva002DBC97Get@GameState@@QAEPAXH@Z @0x002DBC97 51B: save-file suffix
// for a save mode (L".BfME2Campaign" default, Skirmish for 2, WotR for 3
// and 4, WotRMP for 6). The pointer cells are defined in Rva002DBC97Get.cpp.
void *GameState::rva002DBC97Get(int id)
{
	void *r = g_00DBD03C;
	if (id == 2)
		r = g_00DBD040;
	else if (id == 3 || id == 4)
		r = g_00DBD044;
	else if (id == 6)
		r = g_00DBD048;
	return r;
}

// ?saveGame@GameState@@QAEHVUnicodeString@@ABV2@H_NH@Z @0x002DD38D 1113B
int GameState::saveGame(UnicodeString filename, const UnicodeString &desc, int which, bool showMessage, int param5)
{
	int mode = determineCurrentGameSaveFileMode();
	if (mode == 1 && which == 0)
		which = 4;

	if (filename.isEmpty())
		filename = Rva002DBD80Make((int)&rva002DD282(mode), (const WideChar *)rva002DBC97Get(mode));
	if (filename.isEmpty())
		return 1;

	TheFileSystem->rva006006A9(((const Rva002DC267 *)this)->rva002DC267().str());
	UnicodeString filepath = ((const Rva002DC74A *)this)->rva002DC74A(filename);
	File *file = TheFileSystem->rva00600676(filepath.str(), 0x4A, 0);
	if (file == 0)
	{
		TheInGameUI->message("GUI:Error");
		return 3;
	}

	XferSave xferSave;
	try
	{
		xferSave.Open((Xfer *)file, 1, TheSaveGameXferFlag);
	}
	catch (...)
	{
		file->close();
		TheInGameUI->message("GUI:Error");
		return 3;
	}

	m_description = desc;
	m_saveFileType = mode;
	m_missionMapName.clear();

	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	m_date.year = systemTime.wYear;
	m_date.month = systemTime.wMonth;
	m_date.day = systemTime.wDay;
	m_date.dayOfWeek = systemTime.wDayOfWeek;
	m_date.hour = systemTime.wHour;
	m_date.minute = systemTime.wMinute;
	m_date.second = systemTime.wSecond;
	m_date.milliseconds = systemTime.wMilliseconds;

	{
	m_mapLabel = m_pristineMapName;
	m_4C = param5;
	m_heroName.clear();
	m_playerNames.clear();

	GameInfo *game = TheSkirmishGameInfo;
	if (mode == 6)
		game = TheGameInfo;
	if (game)
	{
		for (int i = 0; i < 8; ++i)
		{
			GameSlot *slot = game->getSlot(i);
			if (slot && slot->isHuman() && !slot->isObserver())
			{
				if (!m_playerNames.isEmpty())
					m_playerNames.concat(L", ");
				m_playerNames.concat(slot->m_name);
			}
		}
		if (game->getLocalSlotNum() >= 0)
		{
			GameSlot *slot = game->getSlot(game->getLocalSlotNum());
			if (slot)
			{
				CreateAHeroData *hero = slot->getHeroData();
				if (hero)
					m_heroName = hero->m_name;
			}
		}
	}

		Rva0023D46F counterRef(theBfmeDfe6e4);
		Rva00248558Scope scope;
		try
		{
			xferSaveData(&xferSave, (SnapshotType)which);
		}
		catch (...)
		{
			UnicodeString msg;
			msg.format(TheGameText->fetchPointer("GUI:ErrorSavingGame", 0), filepath.str());
			MessageBoxOk(TheGameText->fetch("GUI:Error"), msg, 0);
			xferSave.close();
			file->close();
			return 3;
		}
		xferSave.close();
		file->close();

		if (showMessage)
		{
			UnicodeString msg = TheGameText->fetch("GUI:GameSaveComplete");
			TheInGameUI->message(msg);
		}
	}
	return 0;
}

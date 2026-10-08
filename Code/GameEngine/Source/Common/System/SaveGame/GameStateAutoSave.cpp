// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// GameState auto-save (0x002DD7E6) and the file-static map display-name
// helper it calls (0x002DC16A). They share this unit because retail passes
// the helper's map label in ESI: cl 7.1's per-unit custom convention for an
// internal-linkage function whose call sites it can see.
//
// Target evidence: the GUI:AutoSaveName label, the wide pointer cells at
// VA 0x00DBD04C (L"00000000") and 0x00DBD050 (L"__AUTO#SAVE__") beside the
// save-file suffix cells of 0x002DBC97, the call into GameState::saveGame
// 0x002DD38D, and the single caller 0x005212AC (ECX = TheGameState). The
// helper looks the map up in TheMapCache (findMap, bfme_getBaseDisplayName),
// falls back to TheGameText's lookup of the label and finally formats the
// label itself with L"%S". BFME 1's auto-save (0x003BDB80 there) passes the
// same "__AUTO#SAVE__" description. Original names of both are unknown.
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

class GameState
{
public:
	int determineCurrentGameSaveFileMode();
	void *rva002DBC97Get(int mode);
	int saveGame(UnicodeString filename, const UnicodeString &desc, int which, bool showMessage, int param5);
	int rva002DD7E6AutoSave();

private:
	char m_pad0[0x2C];
	AsciiString m_pristineMapName;	// +0x2C
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

// cl: /O1 /G7 /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /Ireference/shims/moduledata
// GameState CRC helper: friend_xferSaveDataForCRC (retail 0x002DDD0B, 50B).
// SaveGameInfo carries pristineMapName at +0x2C with description/
// saveFileType/missionMapName at +0x44/+0x48/+0x50, read off retail's own
// displacements here and in saveGame. The trailing call reaches retail's
// xferSaveData 0x002DCE24; that address is pinned until its row lands.
// stlport
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"

typedef bool Bool;
#define FALSE 0
#define TRUE 1
#define NULL 0
typedef int Int;
enum SnapshotType { SNAPSHOT_SAVELOAD = 0, SNAPSHOT_DEEPCRC_LOGICONLY = 1, SNAPSHOT_NATIVE3 = 3, SNAPSHOT_NATIVE4 = 4 };

class Xfer
{
};

// Retail's twelve-byte subsystem base ahead of the Snapshot view, per the
// rowed GameStateInit unit: a virtual slot plus eight opaque bytes.
class SnapshotSubsystemPrefix
{
public:
	virtual ~SnapshotSubsystemPrefix();
private:
	char m_opaque04[8];
};

class GameState : public SnapshotSubsystemPrefix, public Snapshot
{
public:
	void xferSaveData(Xfer *xfer, SnapshotType which);
	void friend_xferSaveDataForCRC(Xfer *xfer, SnapshotType which);

private:
	struct SaveGameInfo
	{
		char m_opaque00[4];
		AsciiString pristineMapName;
		char m_opaque08[0x14];
		UnicodeString description;
		Int saveFileType;
		char m_opaque4C[4];
		AsciiString missionMapName;
	};
	SaveGameInfo m_gameInfo;
};

// ------------------------------------------------------------------------------------------------
/** Save game to xfer or load game using xfer */
// ------------------------------------------------------------------------------------------------
void GameState::friend_xferSaveDataForCRC(Xfer *xfer, SnapshotType which)
{
	SaveGameInfo *gameInfo = (SaveGameInfo *)((char *)this + 0x28);
	gameInfo->description.clear();
	gameInfo->saveFileType = 0;
	((StringBase<char> *)&gameInfo->missionMapName)->clear();
	((StringBase<char> *)&gameInfo->pristineMapName)->clear();

	xferSaveData(xfer, which);
}

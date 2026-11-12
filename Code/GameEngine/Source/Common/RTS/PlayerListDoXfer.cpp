// cl: /O1 /G7 /Oy- /MD /EHsc
// Clean BF1 PlayerListXfer.cpp donor at ba7ddda7e8 with target-specific
// Xfer::Version1 and signed-int slot31. WB D24980 names PlayerList::DoXfer
// in Common/RTS/PlayerList.cpp; retail 2A7D63..2A7DD0 proves the complete
// 109B boundary, local-player4/count8/player-pointer-arrayC and Snapshot12.
// The mismatch branch formats XferException tag5 and throws the existing
// type-info object recorded in data_ledger at8FFD18. No new pins or RTTI.
// This is an accessed prefix view; the total player-array bound stays open.

typedef unsigned char UnsignedByte;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

class Player;

class PlayerList
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void DoXfer(Xfer *xfer);

private:
	Player *m_local;
	int m_playerCount;
	Player *m_players[1];
};

#include "../../../Include/Common/BfmeFormattedText.h"

union PlayerListXferLocal
{
	XferVersion version;
	BfmeFormattedText error;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *, int, const char *, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *, void *);
extern int g_guardTargetTypeThrowInfo;

void PlayerList::DoXfer(Xfer *xfer)
{
	PlayerListXferLocal local;
	xfer->Version1();

	int playerCount = m_playerCount;
	*xfer == playerCount;
	if (playerCount != m_playerCount)
	{
		bfmeFormatText(&local.error, 5, 0);
		_CxxThrowException(&local.error, &g_guardTargetTypeThrowInfo);
	}

	for (int i = 0; i < playerCount; ++i)
		*xfer == *reinterpret_cast<Snapshot *>(m_players[i]);
}

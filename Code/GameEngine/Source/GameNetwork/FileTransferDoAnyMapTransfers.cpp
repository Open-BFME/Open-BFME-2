// ?DoAnyMapTransfers@@YA_NPAVGameInfo@@@Z
// cl: /O1 /Oi /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii

// Ported from Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// game/GameEngine/Source/GameNetwork/FileTransfer_DoAnyMapTransfers.cpp.
// Native 0x0044D06D..0x0044D285 is a complete cdecl function, confirmed
// against its WorldBuilder body on return from the 0x0044C5C7 dependency.
// BFME2 reads this GameInfo directly and its contents mask at +0x4C;
// it does not assign TheGameInfo. Canonical strings preserve result lifetimes.
#include "ascii_string.h"

#include "../../Include/GameNetwork/GameInfo.h"

// No authored GameInfo header covers this measured BFME layout. Keep the
// local accessor out of the external GameInfo COMDAT contract.
class GameInfo;
static __forceinline int getMapContentsMask(const GameInfo *game);


static __forceinline int getMapContentsMask(const GameInfo *game)
{
	return game->m_mapMask;
}


bool Rva005836B5Initialize(void *context);
void Rva00583015Destroy();

AsciiString GetPreviewFromMap(AsciiString path);
AsciiString GetArtPreviewFromMap(AsciiString path);
AsciiString GetPicPreviewFromMap(AsciiString path);
AsciiString GetINIFromMap(AsciiString path);
AsciiString GetStrFileFromMap(AsciiString path);
AsciiString GetSoloINIFromMap(AsciiString path);
AsciiString GetAssetUsageFromMap(AsciiString path);
AsciiString GetReadmeFromMap(AsciiString path);

bool doFileTransfer(AsciiString filename, int mask);

bool DoAnyMapTransfers(GameInfo *game)
{
	int mask = 0;
	for (int i = 1; i < 8; ++i)
	{
		if (game->getConstSlot(i)->isHuman() &&
			!game->getConstSlot(i)->hasMap())
		{
			mask |= 1 << i;
		}
	}

	if (!mask)
		return true;

	Rva005836B5Initialize(game);
	bool ok = true;
	if (getMapContentsMask(game) & 0x200)
		ok = false;

	if (ok && (getMapContentsMask(game) & 2))
		ok = doFileTransfer(GetPreviewFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(game) & 4))
		ok = doFileTransfer(GetINIFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(game) & 8))
		ok = doFileTransfer(GetStrFileFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(game) & 16))
		ok = doFileTransfer(GetSoloINIFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(game) & 32))
		ok = doFileTransfer(GetAssetUsageFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(game) & 64))
		ok = doFileTransfer(GetReadmeFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(game) & 128))
		ok = doFileTransfer(GetArtPreviewFromMap(game->getMap()), mask);
	if (ok && (getMapContentsMask(game) & 256))
		ok = doFileTransfer(GetPicPreviewFromMap(game->getMap()), mask);
	if (ok)
		ok = doFileTransfer(game->getMap(), mask);

	Rva00583015Destroy();
	return ok;
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /G7 /arch:SSE
// ?parseMiscEvaData@INI@@SAXPAV1@@Z @0x001DCFE5 70B evidence: BlockParse MiscEvaData token VA 0x00DB8D94 parse 0x001DCFE5; donor BFME1 game/GameEngine/Source/GameClient/Eva.cpp INI::parseMiscEvaData; string Cannot override MiscEvaData entries; FieldParse table VA 0x00BDC468; TheEva+0x80
class INI;
#include "../../Include/Common/INI/FieldParse.h"

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

#include "../../Include/Common/INI/INI.h"


class Eva;
extern Eva *TheEva;

// Retail's MiscEvaData field table at VA 0x00BDC468 (.rdata, 112 bytes),
// transcribed from retail's own bytes: six records plus the null terminator.
extern const FieldParse MiscEvaDataFieldParse[] =
{
	{ "EnemySightedMaxVoicePositionScanRange",    &INI::parseReal,                0, 0x00 },
	{ "EnemyCampDestroyedDamageTimeoutMS",        &INI::parseDurationUnsignedInt, 0, 0x04 },
	{ "FriendlyCampDestroyedDamageTimeoutMS",     &INI::parseDurationUnsignedInt, 0, 0x08 },
	{ "MaxMillisecondsToKeepJumpToEvents",        &INI::parseDurationUnsignedInt, 0, 0x0C },
	{ "MaxMillisecondsBeforeResettingLastJumpTo", &INI::parseUnsignedInt,         0, 0x10 },
	{ "MinDistanceBetweenJumpToEvents",           &INI::parseReal,                0, 0x14 },
	{ 0, 0, 0, 0 }
};

void INI::parseMiscEvaData(INI *ini)
{
	if (ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES)
		throw INIException(8, "Cannot override MiscEvaData entries");
	ini->initFromINI((void *)((char *)TheEva + 0x80), MiscEvaDataFieldParse);
}

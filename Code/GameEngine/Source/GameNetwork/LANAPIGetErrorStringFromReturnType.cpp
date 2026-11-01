// ?getErrorStringFromReturnType@LANAPIInterface@@QAE?AVUnicodeString@@W4ReturnType@1@@Z
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Target evidence: Ghidra bounds a 131-byte function at 0x00248EC3. Its retail
// jump table at 0x00248F46 maps values 0..9 to LAN:OK, ErrorTimeout,
// ErrorGameFull, ErrorDuplicateName, ErrorCRCMismatch, WOL:ChatErrorSerialDup,
// ErrorGameStarted, ErrorGameExists, ErrorGameGone, and ErrorBusy; default
// selects LAN:ErrorUnknown. The target fetch call uses GameText slot +0x3C.
// Donor evidence: BFME1 Code and GeneralsMD LANAPICallbacks.cpp identify the
// helper and its enum. BFME1 Code emits RET_SERIAL_DUPE after RET_BUSY, matching
// the target's independently observed relocation order. The name, enum member
// labels, and class relationship follow the donors; target case-to-key mapping
// is established by the jump table and retail string references.
typedef bool Bool;

#include "unicode_string.h"


#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

class LANAPIInterface
{
public:
	enum ReturnType
	{
		RET_OK = 0,
		RET_TIMEOUT,
		RET_GAME_FULL,
		RET_DUPLICATE_NAME,
		RET_CRC_MISMATCH,
		RET_SERIAL_DUPE,
		RET_GAME_STARTED,
		RET_GAME_EXISTS,
		RET_GAME_GONE,
		RET_BUSY,
		RET_UNKNOWN,
		RET_MAX
	};

	UnicodeString getErrorStringFromReturnType( ReturnType ret );
};

UnicodeString LANAPIInterface::getErrorStringFromReturnType(ReturnType ret)
{
	switch (ret)
	{
		case RET_OK:
			return TheGameText->fetch("LAN:OK");
		case RET_TIMEOUT:
			return TheGameText->fetch("LAN:ErrorTimeout");
		case RET_GAME_FULL:
			return TheGameText->fetch("LAN:ErrorGameFull");
		case RET_DUPLICATE_NAME:
			return TheGameText->fetch("LAN:ErrorDuplicateName");
		case RET_CRC_MISMATCH:
			return TheGameText->fetch("LAN:ErrorCRCMismatch");
		case RET_GAME_STARTED:
			return TheGameText->fetch("LAN:ErrorGameStarted");
		case RET_GAME_EXISTS:
			return TheGameText->fetch("LAN:ErrorGameExists");
		case RET_GAME_GONE:
			return TheGameText->fetch("LAN:ErrorGameGone");
		case RET_BUSY:
			return TheGameText->fetch("LAN:ErrorBusy");
		case RET_SERIAL_DUPE:
			return TheGameText->fetch("WOL:ChatErrorSerialDup");
		default:
			return TheGameText->fetch("LAN:ErrorUnknown");
	}
}

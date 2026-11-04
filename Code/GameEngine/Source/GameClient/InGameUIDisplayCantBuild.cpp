// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// stlport
//
// ?displayCantBuildMessage@InGameUI@@UAEXW4LegalBuildCode@@@Z,
// retail 0x0029C291, 101 bytes. Dedicated TU.
//
// ZH reference
// (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/InGameUI.cpp)
// passes one literal per case into TheInGameUI->message; /O1 tail-merges
// the seven identical AsciiString-construction plus slot-0x3C message tails
// into one shared tail, so retail shows one push-per-case feeding one
// StringBase<char> construction and one message call.
// BFME2 adaptations (all retail-measured):
// - LegalBuildCode values are reordered vs ZH: 2=NoClear/3=TooClose/
//   4=Shroud/5=NotFlat/6=Restricted/8=Objects, everything else falls to
//   the There text (retail dec-chain over lbc-2..lbc-8).
// - InGameUI virtuals: message at 0x3C (variadic __cdecl, this on stack),
//   same convention as the slot-0x40 message in
//   InGameUI_selectMatchingAcrossScreen.cpp.
// - Non-virtual member (QAEX), unlike ZH's virtual spelling.

typedef int Int;
typedef bool Bool;

class UnicodeString;
class AsciiString;

#include "ascii_string.h"


// BFME2 values measured from retail 0x29C291; ZH order differs.
enum LegalBuildCode
{
	LBC_OK = 0,
	LBC_NO_CLEAR_PATH = 2,
	LBC_TOO_CLOSE_TO_SUPPLIES = 3,
	LBC_SHROUD = 4,
	LBC_NOT_FLAT_ENOUGH = 5,
	LBC_RESTRICTED_TERRAIN = 6,
	LBC_OBJECTS_IN_THE_WAY = 8,
};

#include "../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

// ?displayCantBuildMessage@InGameUI@@UAEXW4LegalBuildCode@@@Z
void InGameUI::displayCantBuildMessage(LegalBuildCode lbc)
{
	switch (lbc)
	{
		case LBC_NO_CLEAR_PATH:
			TheInGameUI->rva0029E656(AsciiString("GUI:CantBuildNoClearPath"));
			break;
		case LBC_TOO_CLOSE_TO_SUPPLIES:
			TheInGameUI->rva0029E656(AsciiString("GUI:CantBuildTooCloseToSupplies"));
			break;
		case LBC_SHROUD:
			TheInGameUI->rva0029E656(AsciiString("GUI:CantBuildShroud"));
			break;
		case LBC_NOT_FLAT_ENOUGH:
			TheInGameUI->rva0029E656(AsciiString("GUI:CantBuildNotFlatEnough"));
			break;
		case LBC_RESTRICTED_TERRAIN:
			TheInGameUI->rva0029E656(AsciiString("GUI:CantBuildRestrictedTerrain"));
			break;
		case LBC_OBJECTS_IN_THE_WAY:
			TheInGameUI->rva0029E656(AsciiString("GUI:CantBuildObjectsInTheWay"));
			break;
		default:
			TheInGameUI->rva0029E656(AsciiString("GUI:CantBuildThere"));
			break;
	}
}

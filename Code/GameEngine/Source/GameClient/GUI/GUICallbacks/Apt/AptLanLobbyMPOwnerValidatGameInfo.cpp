// cl: /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva005169E0Wrap.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?wrap@Rva005169E0@@QAEEH@Z 0x00444208 (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// BFME2 identity (target evidence; the donor's names were placeholders):
// WorldBuilder's AptLanLobby.cpp:1063 defines
// AptLanLobby::MPOwnerValidatGameInfo as this body, TheLAN null test then
// LANAPI::ValidateGameInfo (0x00449969, the callee below), and retail's LAN
// lobby owner vftable holds it.

class LANGameInfo;
class LANAPI
{
	friend class AptLanLobby;
protected:
	bool ValidateGameInfo(LANGameInfo *game);
};

extern class LANAPI *TheLAN;

class AptLanLobby
{
public:
	unsigned char MPOwnerValidatGameInfo(int a);
};

unsigned char AptLanLobby::MPOwnerValidatGameInfo(int a)
{
	if (TheLAN)
		return TheLAN->ValidateGameInfo((LANGameInfo *)a);
	return 0;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.

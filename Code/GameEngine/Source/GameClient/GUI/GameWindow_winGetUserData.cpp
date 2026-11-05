// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// GameWindow::winGetUserData, retail 0x005C4ACD, 4 bytes.
// Shim GameWindow.h places m_userData at +0x2C; retail is mov eax,[ecx+2Ch]; ret.

#include "../../../Include/GameClient/Bfme2GameWindow.h"

__declspec(noinline) void *GameWindow::winGetUserData()
{
	return m_userData;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeGetEBN@BfmeObjEBN@@QAEPAUBfmeSubEBN@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")
#pragma comment(linker, "/alternatename:?bfmeFindLC@BfmeKeyLC@@QAEPAUBfmeNodeLC@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")
#pragma comment(linker, "/alternatename:?bfmeFindBHF@BfmeSubBHF@@QAEPAUBfmeGotBHF@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGetENK@BfmeObjENK@@QAEPAUBfmeSubENK@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")

// ?rva000A210B@Rva000A210BOwner@@QAEPAXXZ @0x000A210B 7B: returns the user
// data of the GameWindow held at +0 (mov ecx, [ecx]; tail jump to
// winGetUserData above). Owner and name are address-derived; no referencing
// site was found in this pass.
class Rva000A210BOwner
{
public:
	void *rva000A210B();
private:
	GameWindow *m_window00;
};

void *Rva000A210BOwner::rva000A210B()
{
	return m_window00->winGetUserData();
}

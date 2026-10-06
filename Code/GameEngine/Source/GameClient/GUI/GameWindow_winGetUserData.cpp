// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// GameWindow::winGetUserData, retail 0x005C4ACD, 4 bytes.
// Shim GameWindow.h places m_userData at +0x2C; retail is mov eax,[ecx+2Ch]; ret.

class GameWindow
{
	unsigned char _M_layout[0x2C];
	void *m_userData;

public:
	void *winGetUserData();
};

void *GameWindow::winGetUserData()
{
	return m_userData;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeGetEBN@BfmeObjEBN@@QAEPAUBfmeSubEBN@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")
#pragma comment(linker, "/alternatename:?bfmeFindLC@BfmeKeyLC@@QAEPAUBfmeNodeLC@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")
#pragma comment(linker, "/alternatename:?bfmeFindBHF@BfmeSubBHF@@QAEPAUBfmeGotBHF@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")
#pragma comment(linker, "/alternatename:?bfmeGetENK@BfmeObjENK@@QAEPAUBfmeSubENK@@XZ=?winGetUserData@GameWindow@@QAEPAXXZ")

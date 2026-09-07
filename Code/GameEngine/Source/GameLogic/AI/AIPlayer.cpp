// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /GX
//
// BFME2 BuildListInfo desired-gatherers getter, transferred from the exact
// BFME1 reconstruction (Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp).
// Retail BFME2 keeps the field at the same offset (+0x84); the layout
// authority is reference/shims/buildlistinfo/GameLogic/SidesList.h.

class BuildListInfo
{
public:
	int getDesiredGatherers();

private:
	unsigned char m_pre[0x84];
	int m_desiredGatherers;	// +0x84
};

// ?getDesiredGatherers@BuildListInfo@@QAEHXZ
int BuildListInfo::getDesiredGatherers()
{
	return m_desiredGatherers;
}

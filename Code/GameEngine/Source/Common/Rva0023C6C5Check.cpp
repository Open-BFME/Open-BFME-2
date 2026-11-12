// cl: /DNDEBUG /MD
//
// ?rva0023C6C5@BfmeGlob939D@@QAEDXZ @0x0023C6C5, 56B.
// Multiplayer-plus-helper predicate: true when in a multiplayer game, else
// needs recorder playback (mode 1) and the recording's original game mode at
// +0xE74 of 1 or 5. Same GameLogic base call, global and +0xE74 as neighbour
// BfmeGlob939D::bfmeCall939D at 0x0023C6FD without its mode==2 check.
// Retail calls the shared +0x1C accessor at 0x0030F2C7 on TheRecorder
// (VA 0x00E02290), then compares the +0xE74 dword with 1 and 5.

#include "GameLogicObjectLookupView.h"
#include "../../Include/Common/RecorderClass.h"

class BfmeGlob939D : public GameLogic
{
public:
	char rva0023C6C5();
};

char BfmeGlob939D::rva0023C6C5()
{
	if (isInMultiplayerGame())
		return 1;
	if (TheRecorder != 0 && TheRecorder->getMode() == 1)
	{
		int originalGameMode = TheRecorder->m_originalGameMode;
		if (originalGameMode == 1 || originalGameMode == 5)
			return 1;
		return 0;
	}
	return 0;
}

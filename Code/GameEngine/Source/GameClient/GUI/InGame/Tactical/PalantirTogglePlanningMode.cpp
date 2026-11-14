// cl: /O1 /DNDEBUG /MD
// ?TogglePlanningMode@Impl@Palantir@@QAEXXZ @0x002D2F32 109B
// Renamed from placeholder Rva002D2F32Owner::rva002D2F32. Identity: the
// WorldBuilder build's twin asserts assert lines 1425-1426 in EA's own
// C:\Projects\bfme2\Code\GameEngine\Source\GameClient\Gui\InGame\Tactical\Palantir.cpp
// and names Palantir::Impl::TogglePlanningMode; globals and semantics match
// the retail body (TheGameLogic mode 3, own +0x128 gate, local player's
// +0x758 == 2, GameMessage 0x469 through MessageStream slot 0x48).
// Body provenance: placeholder Rva002D2F32Post.cpp (matched, "exact
// identities unproven" views carried over unchanged). The +0x128 owner
// field view claims nothing about Impl's real members.
#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

struct Rva002D2F32Mid
{
	char m_pad[0x750];
	int m_planningMode;
};

#include "../../../../../Include/Common/PlayerList.h"

#include "../../../../../Include/Common/MessageStream.h"

extern class MessageStream *TheMessageStream;

class Palantir
{
public:
	class Impl
	{
	public:
		void TogglePlanningMode();

	private:
		char m_pad[0x128];
		unsigned char m_128;
	};
};

void Palantir::Impl::TogglePlanningMode()
{
	if (TheGameLogic->m_110 == 3)
		return;
	if (m_128 == 0)
		return;
	Rva002D2F32Mid *mid = (Rva002D2F32Mid *)ThePlayerList->m_local;
	if (mid != 0 && mid->m_planningMode == 2) {
		GameMessage *gameMessage = TheMessageStream->appendMessage(GameMessage::MSG_CHANGE_ORDERMODE);
		gameMessage->appendIntegerArgument(0);
		gameMessage->appendIntegerArgument(2);
		return;
	}
	GameMessage *message = TheMessageStream->appendMessage(GameMessage::MSG_CHANGE_ORDERMODE);
	message->appendIntegerArgument(2);
}

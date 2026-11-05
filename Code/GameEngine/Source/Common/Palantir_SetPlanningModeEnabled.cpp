// cl: /O1 /DNDEBUG /MD
//
// ?SetPlanningModeEnabled@Palantir@@QAEXE@Z @0x002D37BD 96B: byte-field setter
// with zero-side effect (thiscall, 1 byte arg, void). No-op when the new
// value equals m_10+0x128; when clearing to zero with ThePlayerList mid
// present and +0x750 == 2, posts message 0x469 with int args (0, 2)
// through the MessageStream slot used by landed 0x002D2F32; then stores
// the value. Callee is landed GameMessage::appendIntegerArgument.
// Views mirror the landed message TU; exact identities unproven.
struct Rva002D37BDMid
{
	char m_pad[0x750];
	int m_750;
};

class PlayerList
{
public:
	char m_pad[0x10];
	Rva002D37BDMid *m_mid;
};
extern PlayerList *ThePlayerList;

#include "../../Include/Common/MessageStream.h"

extern class MessageStream *TheMessageStream;

struct Rva002D37BDMid10
{
	char m_pad[0x128];
	unsigned char m_planningModeEnabled;
};

class Palantir
{
public:
	void SetPlanningModeEnabled(unsigned char enabled);

private:
	char m_pad[0x10];
	Rva002D37BDMid10 *m_10;
};

// ?SetPlanningModeEnabled@Palantir@@QAEXE@Z
void Palantir::SetPlanningModeEnabled(unsigned char enabled)
{
	if (enabled == m_10->m_planningModeEnabled)
		return;
	if (enabled == 0) {
		Rva002D37BDMid *mid = ThePlayerList->m_mid;
		if (mid != 0 && mid->m_750 == 2) {
			GameMessage *gameMessage = TheMessageStream->appendMessage(static_cast<GameMessage::Type>(0x469));
			gameMessage->appendIntegerArgument(0);
			gameMessage->appendIntegerArgument(2);
		}
	}
	m_10->m_planningModeEnabled = enabled;
}

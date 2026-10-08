// cl: /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::PlayerStatusDisplayer (WorldBuilder
// StrategicInGameUIPlayerStatusDisplayer.cpp). Target facts: its objectives
// button handler OnObjectivesButtonLeftClicked 0x005CD649 (virtual, pointer
// at 0x00874FF8; WorldBuilder name) runs 0x005CD625 (unnamed there, pinned
// address-named) on the same object, as does its message translator
// 0x005CD690 (unnamed there) for message type 0x6F. The strategic phase
// behaviors hold one by value right after their ManualPhaseEnder and offer
// it each message (which identifies 0x005CD690's class with this one).

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

class GameMessage
{
public:
	int getType() const { return m_type; }

private:
	char m_pad00[0x10];
	int m_type; // +0x10
};

class Rva005CD649Button;

namespace StrategicInGameUI
{
class PlayerStatusDisplayer
{
public:
	virtual void OnObjectivesButtonLeftClicked(Rva005CD649Button &button);
	GameMessageDisposition rva005CD690(const GameMessage *msg);
	void rva005CD625();
};
}

void StrategicInGameUI::PlayerStatusDisplayer::OnObjectivesButtonLeftClicked(Rva005CD649Button &button)
{
	rva005CD625();
}

GameMessageDisposition StrategicInGameUI::PlayerStatusDisplayer::rva005CD690(const GameMessage *msg)
{
	if (msg->getType() != 0x6F)
		return KEEP_MESSAGE;
	rva005CD625();
	return DESTROY_MESSAGE;
}

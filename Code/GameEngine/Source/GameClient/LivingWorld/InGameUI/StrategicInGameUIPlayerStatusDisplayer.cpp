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
	bool rva005CD625();
private:
	unsigned char m_pad04[0x0C - 0x04];
	bool m_shown0C;
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

// ?rva005CD625@PlayerStatusDisplayer@StrategicInGameUI@@QAE_NXZ @0x005CD625
// 36B: while the display is up (+0x0C) and the living world runs and its
// rowed 0x002B254F check does not hold, the player status screen opens
// (0x00523592) and the answer is true. 0x00523592 only reads the screen's
// global (0x00E04934) and never ECX, so it is called as the static it is
// (pinned); the 0x002B254F result is the byte retail tests.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva002B254F
{
public:
	int rva002B254F();
};

class StrategicPlayerStatus
{
public:
	static void rva00523592Open();
};

bool StrategicInGameUI::PlayerStatusDisplayer::rva005CD625()
{
	if (!m_shown0C || !TheLivingWorldLogic)
		return false;
	if ((unsigned char)reinterpret_cast<Rva002B254F *>(TheLivingWorldLogic)->rva002B254F())
		return false;
	StrategicPlayerStatus::rva00523592Open();
	return true;
}

// ?rva005CD625@PlayerStatusDisplayer@StrategicInGameUI@@QAE_NXZ
// partial score=0.94 date=2026-10-08
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
	char m_pad04[8];
	bool m_flag0C;
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

// ?rva005CD625@PlayerStatusDisplayer@StrategicInGameUI@@QAE_NXZ @0x005CD625 36B
// Bool predicate gating StrategicPlayerStatus update on display flag,
// living-world presence and region check. Evidence: callers 0x005CD649
// 0x005CD69E, callees TheLivingWorldLogic rva002B254F rva00523592,
// pin class proof with bool return from retail al.
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
	void rva00523592();
};
bool StrategicInGameUI::PlayerStatusDisplayer::rva005CD625()
{
	if (m_flag0C == 0)
		return false;
	if (!TheLivingWorldLogic)
		return false;
	bool ok = ((Rva002B254F *)TheLivingWorldLogic)->rva002B254F();
	if (ok)
		return false;
	((StrategicPlayerStatus *)0)->rva00523592();
	return true;
}

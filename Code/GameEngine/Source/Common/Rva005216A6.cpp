// cl: /MD
// ?rva005216A6@Rva005216A6@@QAE_NXZ, retail 0x005216A6 37B unlock via AptMpGameSetup slots.
// __thiscall bool check plus GameInfo-gated bool at +0x288 subobject.
// Evidence: rowed 0x00442C9C plus rowed 0x00443C6E (AptMpGameSetup::Init) plus TheSkirmishGameInfo 0x00A02EF0; caller 0x00522290; prev 0x00521623 next 0x0052180E same dir.
class GameInfo;
extern GameInfo *TheSkirmishGameInfo;

class AptMpGameSetup
{
public:
	bool rva00442C9C();
	bool Init(GameInfo *game, int value);
};

class Rva005216A6
{
public:
	bool rva005216A6();
private:
	char _pad[0x288];
	AptMpGameSetup m_sub;
};

bool Rva005216A6::rva005216A6()
{
	if (!m_sub.rva00442C9C())
		return false;
	return m_sub.Init(TheSkirmishGameInfo, 1);
}

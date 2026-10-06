// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Counts anything past the first two states as interesting.

class BfmeThingXT
{
public:
	int bfmeOddXT(void) const;

private:
	unsigned char m_bfmeHead[0x18];		// 0x00
	int m_bfmeState;			// 0x18
};

int BfmeThingXT::bfmeOddXT(void) const
{
	int state = m_bfmeState;

	if (state != 0 && state != 1)
		return 1;

	return 0;
}

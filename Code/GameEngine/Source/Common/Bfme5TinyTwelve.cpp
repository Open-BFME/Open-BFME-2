// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four more tiny ones: a flag set only in one mode, a table lookup behind a
// null guard, a choice between two objects and a digit parsed out of a
// string. The last two answer through the pointer first, which is what keeps
// the explicit zero and the fall-through on the reading path.

class BfmeHolderCC
{
public:
	char m_bfmeHead[0x0C];					// +0x00
	int m_bfmeValue;					// +0x0C
};

class Gen_006D7C80
{
public:
	int bfmeValue(unsigned char which) const;

private:
	int m_bfmeHead[12];					// +0x00
	BfmeHolderCC *m_bfmeSecond;				// +0x30
	BfmeHolderCC *m_bfmeFirst;				// +0x34
};

// ?bfmeValue@Gen_006D7C80@@QBEHE@Z
int Gen_006D7C80::bfmeValue(unsigned char which) const
{
	if (which)
		return m_bfmeFirst->m_bfmeValue;

	return m_bfmeSecond->m_bfmeValue;
}
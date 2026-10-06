// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Five more: another two-member swap, a chain depth, a size over a sixty-byte
// element, an all-zero test and a one-bit store.

class Gen_003D3220
{
public:
	bool bfmeAllZero(void) const;

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
};

// ?bfmeAllZero@Gen_003D3220@@QBE_NXZ
bool Gen_003D3220::bfmeAllZero(void) const
{
	int *it = m_bfmeStart;
	int *finish = m_bfmeFinish;

	while (it != finish)
	{
		if (*it != 0)
			return false;

		++it;
	}

	return true;
}
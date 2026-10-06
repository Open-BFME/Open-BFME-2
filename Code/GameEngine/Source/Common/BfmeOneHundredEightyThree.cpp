// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// One short errand: calls through a kept address with three arguments.

class BfmeThingCN
{
public:
	void bfmeGoCN(int first, int second, int third);

private:
	unsigned char m_bfmeHead[8];		// 0x0
	void (__cdecl *m_bfmeCall)(int, int, int);	// 0x8
};

void BfmeThingCN::bfmeGoCN(int first, int second, int third)
{
	m_bfmeCall(first, second, third);
}


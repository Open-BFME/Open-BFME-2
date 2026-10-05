// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?rva0056FAA5@Rva0056FAA5@@QAEPAV1@PAV1@0@Z @0x0056FAA5 31B
// Evidence: unlock lane; reads +0x04 of other then this hands to rowed Rva0056F6E9Hook leaves pop-pop assigns dst+0x04 returns dst; caller 0x0056FCF3; prev S5HandleHashCompares read-order lever
int Rva0056F6E9Hook(int a, int b);

class Rva0056FAA5
{
public:
	Rva0056FAA5 *rva0056FAA5(Rva0056FAA5 *dst, Rva0056FAA5 *src);
private:
	char m_head[4];
	int m_04;
};

Rva0056FAA5 *Rva0056FAA5::rva0056FAA5(Rva0056FAA5 *dst, Rva0056FAA5 *src)
{
	int other = src->m_04;
	int mine = m_04;
	dst->m_04 = Rva0056F6E9Hook(mine, other);
	return dst;
}

// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?rva0056FAA5@Rva0056FAA5@@QAEPAV1@PAV1@0@Z @0x0056FAA5 31B
// Evidence: unlock lane; reads +0x04 of other then this hands to rowed Rva0056F6E9Hook leaves pop-pop assigns dst+0x04 returns dst; caller 0x0056FCF3; prev S5HandleHashCompares read-order lever
int Rva0056F6E9Hook(int a, int b);

class Rva0056FAA5
{
public:
	Rva0056FAA5 *rva0056FAA5(Rva0056FAA5 *dst, Rva0056FAA5 *src);
	Rva0056FAA5 *rva0056FCF3(Rva0056FAA5 *src);
	void rva0056FD46(short v);
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

Rva0056FAA5 *Rva0056FAA5::rva0056FCF3(Rva0056FAA5 *src)
{
	Rva0056FAA5 tmp;
	Rva0056FAA5 *res = rva0056FAA5(&tmp, src);
	m_04 = res->m_04;
	return this;
}

// ?rva0056FD46@Rva0056FAA5@@QAEXF@Z @0x0056FD46 24B
// Evidence: unlock lane; movsx word arg hands twice to rowed Rva0056F7F4Hook stores to +0x04
// uses esi for this; callers 0x0056FE21 0x00570474 0x0057085E
int Rva0056F7F4Hook(int left, int right);

void Rva0056FAA5::rva0056FD46(short v)
{
	m_04 = Rva0056F7F4Hook(v, v);
}

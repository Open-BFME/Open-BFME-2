// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

class Rva004C14D0
{
	int m_00;

public:
	Rva004C14D0 &set(int *p, int v);
};

Rva004C14D0 &Rva004C14D0::set(int *p, int v)
{
	*p = 0;
	m_00 = v;
	return *this;
}

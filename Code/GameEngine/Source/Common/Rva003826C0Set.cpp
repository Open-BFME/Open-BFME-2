// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

class Rva003826C0
{
	char m_lead[0x18];
	int m_18;
	int m_1c;

public:
	void set(int a, int b);
};

void Rva003826C0::set(int a, int b)
{
	m_1c = a;
	m_18 = b;
}

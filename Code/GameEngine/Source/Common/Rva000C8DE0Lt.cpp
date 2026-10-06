// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

class Rva000C8DE0
{
	char m_pad;
	unsigned char m_value;

public:
	bool below(int a);
};

bool Rva000C8DE0::below(int a)
{
	return m_value < a;
}

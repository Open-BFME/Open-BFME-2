// cl: /O1 /MD /GX /arch:SSE
// ?rva002972B1@Object@@QAEMM@Z, retail 0x002972B1, 45 bytes. If +0x448 counter
// is below GameLogic +0x40 limit via TheGameLogic, refresh +0x444 through rowed
// 0x00295844, then return +0x444 float. Evidence: callee row 0x00295844
// ?rva00295844@Object@@QAEXM@Z, TheGameLogic use, offsets +0x444/+0x448/+0x40,
// neighbours prev 0x002966A0 next 0x002972DE.
class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	void rva00295844(float range);
	float rva002972B1(float value);
private:
	char m_pad000[0x444];
	float m_444;
	unsigned int m_448;
};

float Object::rva002972B1(float value)
{
	if (m_448 < TheGameLogic->m_40)
		rva00295844(value);
	return m_444;
}

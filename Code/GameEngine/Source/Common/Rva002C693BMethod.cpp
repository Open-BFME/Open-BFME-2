// cl: /O1 /arch:SSE /MD
//
// ?rva002C693B@Rva002C693B@@QAEXXZ @0x002C693B 258B
// Evidence: unlock lane sibling 002C68CE prev Rva002C68CE next stlport caller
// 0x002C6BFF callee rva002A8B59 pin plus TheGameLogic plus ThePlayerList area
// g_00DFEEF8 globals g_Va00BBB8D8 g_secondsPerLogicFrame BfmeZeroRange
// g_00BC26EC floats 0xa4/0xa8 plus 0x170 offsets 0x15c/0x16c/0x174/0x40.
// Identity: honest-address thiscall method no args returning void with frame.
class GameLogic
{
public:
	char m_pad[0x40];
	unsigned int m_40;
};

extern GameLogic *TheGameLogic;

struct Rva002A8B59Data
{
	char m_pad[0xA4];
	float m_a4;
	float m_a8;
};

class Rva002A8F24
{
public:
	Rva002A8B59Data *rva002A8B59(void *p);
};

extern Rva002A8F24 *g_00DFEEF8;

extern float g_Va00BBB8D8;
extern float g_secondsPerLogicFrame;
extern const float BfmeZeroRange;
extern const float g_00BC26EC;

class Rva002C693B
{
public:
	void rva002C693B();

private:
	char m_pad[0x15C];
	void *m_15C;
	char m_pad160[0x0C];
	int m_16C;
	float m_170;
	int m_174;
};

void Rva002C693B::rva002C693B()
{
	Rva002A8B59Data *data = g_00DFEEF8->rva002A8B59(m_15C);
	unsigned int delta = TheGameLogic->m_40 - (unsigned int)m_174;
	switch (m_16C) {
	case 0: {
		float t = (float)delta * g_secondsPerLogicFrame;
		if (t >= data->m_a4) {
			m_170 = 0.0f;
			m_16C = 1;
			return;
		}
		if (!(data->m_a4 > BfmeZeroRange))
			return;
		m_170 = t / data->m_a4;
		break;
	}
	case 1: {
		float t = (float)delta * g_secondsPerLogicFrame;
		float sum = data->m_a8 + data->m_a4;
		if (t >= sum) {
			m_170 = 0.0f;
			m_16C = 2;
			return;
		}
		if (!(sum > BfmeZeroRange))
			return;
		m_170 = t / sum;
		break;
	}
	case 2:
		m_170 = g_Va00BBB8D8;
		break;
	default:
		return;
	}
}

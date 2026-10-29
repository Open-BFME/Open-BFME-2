// cl: /MD
//
// ?updatePhase@SkirmishAI@@QAEXXZ @0x002C693B 258B
// Evidence: unlock lane sibling 002C68CE prev Rva002C68CE next stlport caller
// 0x002C6BFF callee rva002A8B59 pin plus TheGameLogic plus ThePlayerList area
// TheSkirmishAIManager globals g_Va00BBB8D8 g_secondsPerLogicFrame BfmeZeroRange
// g_00BC26EC floats 0xa4/0xa8 plus 0x170 offsets 0x15c/0x16c/0x174/0x40.
// Identity: honest-address thiscall method no args returning void with frame.
#include "GameLogicObjectLookupView.h"

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

extern Rva002A8F24 *TheSkirmishAIManager;

extern float g_secondsPerLogicFrame;
extern const float g_00BC26EC;

class SkirmishAI
{
public:
	void updatePhase();

private:
	char m_pad[0x15C];
	void *m_player;
	char m_pad160[0x0C];
	int m_difficulty16C;
	float m_time170;
	unsigned int m_frame174;
};

void SkirmishAI::updatePhase()
{
	Rva002A8B59Data *data = TheSkirmishAIManager->rva002A8B59(m_player);
	unsigned int delta = TheGameLogic->getFrame() - m_frame174;
	switch (m_difficulty16C) {
	case 0: {
		float t = (float)delta * g_secondsPerLogicFrame;
		if (t >= data->m_a4) {
			m_time170 = 0.0f;
			m_difficulty16C = 1;
			return;
		}
		if (!(data->m_a4 > 0.0f))
			return;
		m_time170 = t / data->m_a4;
		break;
	}
	case 1: {
		float t = (float)delta * g_secondsPerLogicFrame;
		float sum = data->m_a8 + data->m_a4;
		if (t >= sum) {
			m_time170 = 0.0f;
			m_difficulty16C = 2;
			return;
		}
		if (!(sum > 0.0f))
			return;
		m_time170 = t / sum;
		break;
	}
	case 2:
		m_time170 = 1.0f;
		break;
	default:
		return;
	}
}

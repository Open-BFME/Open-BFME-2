// cl: /MD
// ?rva001E415F@Rva001E415F@@QAEXMH@Z @0x001E415F 29B: store float +0x5c and frame+int +0x60.
// Evidence: 3 callers 0x00292D33 0x00295FEA 0x0029605A; TheGameLogic 0xDFE78C frame +0x40.
class GameLogic
{
public:
	char m_pad[0x40];
	int m_frame;
};
extern GameLogic *TheGameLogic;

class Rva001E415F
{
public:
	void rva001E415F(float f, int i);
	char _0[0x5c];
	float m_5c;
	int m_60;
};

void Rva001E415F::rva001E415F(float f, int i)
{
	m_5c = f;
	m_60 = TheGameLogic->m_frame + i;
}

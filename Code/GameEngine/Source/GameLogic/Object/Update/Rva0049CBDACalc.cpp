// cl: /DNDEBUG /MD
// ?rva0049CBDA@Rva0049CBDA@@QAEHXZ @0x0049CBDA 50B
// Frame-gated float to int. Retail calls private GameEngine::rva00225D38
// through TheGameEngine at 0x00DFE710; when true copies +0x14 int to +0x50;
// then returns (int)(TheGameEngine+0x3C float times +0x18 float plus +0x50
// float via int bits). Evidence: unlock lane; caller at 0x003287F9 in
// 0x00328700; unblocks 0x00328700; flags /O1 /arch:SSE /DNDEBUG /MD copied
// from next TU Rva0049D1B1Check.cpp for movss mulss addss cvttss2si. Owner
// unproven so the name stays address-derived; friend grants the private row.
class Rva0049CBDA;

class GameEngine
{
private:
	bool rva00225D38();
	friend class Rva0049CBDA;
	char m_pad00[0x34];
	int m_pad34;
	char m_pad38[0x3C - 0x38];
	float m_float3C;
};

extern GameEngine *TheGameEngine;

class Rva0049CBDA
{
public:
	char m_pad00[0x14];
	int m_int14;
	float m_float18;
	char m_pad1C[0x50 - 0x1C];
	int m_int50;
	int rva0049CBDA();
};

int Rva0049CBDA::rva0049CBDA()
{
	if (TheGameEngine->rva00225D38())
		m_int50 = m_int14;
	float f = TheGameEngine->m_float3C * m_float18 + *(float *)&m_int50;
	return (int)f;
}

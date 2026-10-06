// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

#include "../../../GameEngineDevice/Source/W3DDevice/GameClient/Shadow/BfmeShadowPrefix.h"

class Rva007B12F0Base
{
public:
	Rva007B12F0Base();
	virtual void handle();

private:
	char m_pad[0x54];
};

class Rva007B1380 : public Rva007B12F0Base
{
	int m_58;
	int m_5C;
	float m_60; // +0x60 set to 20.0f by 0x00109D64
	bool m_64; // +0x64 cleared by 0x00109D64

public:
	Rva007B1380();
	void rva00109D64(void); // @0x00109D64 40B abutting ctor
};

Rva007B1380::Rva007B1380()
{
	m_58 = 0;
	m_5C = 0;
}

// ?rva00109D64@Rva007B1380@@QAEXXZ @0x00109D64 40B: float reset abutting ctor.
// Retail: base initialize 0x000EFA4E via rowed Rva000EFA4E (58B prefix),
// [esi+0x58]=0.0f, [esi+0x5C]=0.0f via xorps, [esi+0x60]=20.0f literal,
// [esi+0x64]=0 (byte). /arch:SSE for movss.
void Rva007B1380::rva00109D64(void)
{
	((Rva000EFA4E *)this)->initialize();
	*(float *)&m_58 = 0.0f;
	*(float *)&m_5C = 0.0f;
	m_60 = 20.0f;
	m_64 = false;
}

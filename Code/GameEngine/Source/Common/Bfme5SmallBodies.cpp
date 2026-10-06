// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions: small self-contained bodies.

struct Bfme5Quad16
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
};

class Bfme5QuadOwner
{
public:
	Bfme5Quad16 bfmeGetQuad(void);

	char m_bfmePad[0x84];
	Bfme5Quad16 m_bfmeQuad;
};

Bfme5Quad16 Bfme5QuadOwner::bfmeGetQuad(void)
{
	return m_bfmeQuad;
}

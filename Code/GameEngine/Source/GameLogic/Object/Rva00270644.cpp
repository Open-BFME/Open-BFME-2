// cl: /MD
// ?rva00270644@Rva00270644@@QAEXMM@Z @0x00270644 52B
// Honest 2-float setter with frame via holder 0x00DFE77C slot 0x7C.
// Evidence: movss at +0xD8 +0xDC plus frame at +0x380; holder same as DrawableFade slot1F;
// callers at 0x0027530C 0x0045DF43 0x0046DAE3 0x0046DB53 0x0048578B.
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva00DFE77CHolder
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual int slot1F();
};

#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)

class Rva00270644
{
public:
	void rva00270644(float a, float b);
private:
	unsigned char m_pad00[0xD8];
	float m_D8;
	float m_DC;
	unsigned char m_padE0[0x380 - 0xE0];
	int m_380;
};

void Rva00270644::rva00270644(float a, float b)
{
	m_D8 = a;
	m_DC = b;
	m_380 = TheRva00DFE77C->slot1F();
}

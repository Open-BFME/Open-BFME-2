// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva004E583D@Rva004E583D@@QAEXXZ @0x004E583D 42B.
// Frame-gated dispatch: read TheGameClient's slot-0x7C frame counter (slot1F
// in the Rva0005121FElapsed.cpp holder view); when it has reached m_8,
// forward m_4, the +0x10 block and the surplus to slot 8 on the +0x0 target.
class ClientFrameSubsystem;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

class Rva004E583DClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual unsigned int slot1F();
};

class Rva004E583DTarget
{
public:
	virtual void vf0();
	virtual void vf1();
	virtual void vf2(int a, void *b, int c);
};

class Rva004E583D
{
public:
	void rva004E583D();
private:
	Rva004E583DTarget *m_0;
	int m_4;
	int m_8;
	int m_pad0C;
	int m_10;
};

void Rva004E583D::rva004E583D()
{
	unsigned int n = ((Rva004E583DClient *)((ClientFrameSubsystem *)TheGameClient))->slot1F();
	if (n >= (unsigned int)m_8)
		m_0->vf2(m_4, &m_10, n - m_8);
}

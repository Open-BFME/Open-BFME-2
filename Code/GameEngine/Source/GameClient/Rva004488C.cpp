// cl: /DNDEBUG /MD
class ClientFrameSubsystem;
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
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual unsigned int slot1F();
};
#define TheRva00DFE77C (*(Rva00DFE77CHolder **)&TheGameClient)

class Rva004488C
{
	char m_pad[0x280];
	int m_280;
	unsigned int m_frame;
	float m_val;
public:
	void f(float v);
};

void Rva004488C::f(float v)
{
	unsigned int fr = TheRva00DFE77C->slot1F();
	m_280 = 0;
	m_frame = fr;
	m_val = v;
}

// cl: /MD
// ?Rva004328D8Emit@@YGXPAURva004328D8Payload@@@Z, retail 0x004328D8, 89 bytes.
// Emits two GameMessages once (flag bit0 at +0x14): type 0xC3 then type [esi]
// via MessageStreamSubsystem slot 0x48 (createMessage), then pixel at +4 via
// appendPixelArgument 0x0030F9D8, int at +0xC and timeGetTime via appendInteger
// 0x0030F936 (twice). Precedents Rva005FA91C 0x005FA91C (/O1 /MD, slot 0x48
// createMessage) and Rva005D1F45 (appendType slot 0x48). timeGetTime via IAT
// winmm.dll uses dllimport. Callers 0x00432AA2/0x00432AC5 become ready.
class GameMessage
{
public:
	void appendPixelArgument(const struct ICoord2D &v);
	void appendIntegerArgument(int v);
};

struct ICoord2D
{
	int m_x;
	int m_y;
};

class MessageStream
{
public:
	virtual void _d00(); virtual void _d01(); virtual void _d02(); virtual void _d03();
	virtual void _d04(); virtual void _d05(); virtual void _d06(); virtual void _d07();
	virtual void _d08(); virtual void _d09(); virtual void _d10(); virtual void _d11();
	virtual void _d12(); virtual void _d13(); virtual void _d14(); virtual void _d15();
	virtual void _d16(); virtual void _d17();
	virtual GameMessage *createMessage(int type);
};

extern class MessageStream *TheMessageStream;
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

struct Rva004328D8Payload
{
	int m_type;
	ICoord2D m_pixel;
	int m_0C;
	unsigned char m_pad10[4];
	unsigned char m_flag14;
};

void __stdcall Rva004328D8Emit(Rva004328D8Payload *p)
{
	if (p->m_flag14 & 1)
		return;
	p->m_flag14 |= 1;
	TheMessageStream->createMessage(0xC3);
	GameMessage *msg = TheMessageStream->createMessage(p->m_type);
	msg->appendPixelArgument(p->m_pixel);
	msg->appendIntegerArgument(p->m_0C);
	msg->appendIntegerArgument((int)timeGetTime());
}

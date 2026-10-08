// cl: /EHsc /DNDEBUG /MD
// StrategicInGameUI::QueueUnitButton::OnLeftClicked @0x005F8920 102B: WorldBuilder
// name (StrategicInGameUIQueueUnitButton.cpp lines 217..227, same isShift 1|5
// repeat of message 0x6AC); a virtual, at VA 0x00C79CD4 in its vtable.
// Evidence: thiscall member
// guards on just-landed __cdecl ?Rva005F88F4Get@@YAHH@Z @0x005F88F4 (m_18) and
// its result's virtual slot 7 (+0x1C, m_20), then builds count = 1|5 from
// rowed Keyboard::isShift @0x00232683 over fresh global g_00DFE720 and loops
// MessageStreamSubsystem->appendMessage(0x6AC) plus two rowed
// GameMessage::appendIntegerArgument @0x0030F936 (m_18, m_20). MessageStream
// slot-18 view and subsystem name reused from ReloadIniFileNotices.cpp;
// result-check view is TU-local (slot 7 honest, dummies structural).
class Keyboard
{
public:
	bool isShift();
};

class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual GameMessage *appendMessage(int type);	// slot 18 (+0x48)
};

extern MessageStream *TheMessageStream;	// VA 0x00E00950

extern class Rva0025CEEFHost *g_009FE720;
// ?g_009FE720@@3PAVRva0025CEEFHost@@A: the global at VA 0xdfe720 is ?TheKeyboard@@3PAVKeyboard@@A.
#pragma comment(linker, "/alternatename:?g_009FE720@@3PAVRva0025CEEFHost@@A=?TheKeyboard@@3PAVKeyboard@@A")

class Rva005F8920Result
{
public:
	virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
	virtual void w4(); virtual void w5(); virtual void w6();
	virtual bool rva005F8920Check(int arg);	// slot 7 (+0x1C)
};

namespace StrategicInGameUI
{
class QueueUnitButton
{
public:
	virtual void OnLeftClicked();
private:
	char m_pad04[0x18 - 4];
	int m_18;
	int m_1C;
	int m_20;
};
}

int __cdecl Rva005F88F4Get(int arg);

void StrategicInGameUI::QueueUnitButton::OnLeftClicked()
{
	Rva005F8920Result *res = (Rva005F8920Result *)Rva005F88F4Get(m_18);
	if (!res || !res->rva005F8920Check(m_20))
		return;
	int i;
	Keyboard *kbd = (Keyboard *)g_009FE720;
	i = (kbd->isShift() ? 4 : 0) + 1;
	if (i > 0)
	{
		GameMessage *msg;
		do
		{
			msg = TheMessageStream->appendMessage(0x6AC);
			msg->appendIntegerArgument(m_18);
			msg->appendIntegerArgument(m_20);
		} while (--i);
	}
}

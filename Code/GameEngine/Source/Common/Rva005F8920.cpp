// cl: /EHsc /DNDEBUG /MD
// StrategicInGameUI::QueueUnitButton::OnLeftClicked @0x005F8920 102B: WorldBuilder
// name (StrategicInGameUIQueueUnitButton.cpp lines 217..227, same isShift 1|5
// repeat of message 0x6AC); a virtual, at VA 0x00C79CD4 in its vtable.
// Evidence: thiscall member
// guards on just-landed __cdecl ?Rva005F88F4Get@@YAHH@Z @0x005F88F4 (m_18) and
// its result's virtual slot 7 (+0x1C, m_20), then builds count = 1|5 from
// rowed Keyboard::isShift @0x00232683 over fresh global g_00DFE720 and loops
// TheMessageStream->appendMessage(0x6AC) plus two rowed
// GameMessage::appendIntegerArgument @0x0030F936 (m_18, m_20). MessageStream
// slot-18 view and subsystem name reused from ReloadIniFileNotices.cpp;
// result-check view is TU-local (slot 7 honest, dummies structural).
#include "../../Include/GameClient/KeyboardClass.h"

#include "../../Include/Common/MessageStream.h"


extern MessageStream *TheMessageStream;	// VA 0x00E00950

extern class Keyboard *TheKeyboard;

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
	Keyboard *kbd = TheKeyboard;
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

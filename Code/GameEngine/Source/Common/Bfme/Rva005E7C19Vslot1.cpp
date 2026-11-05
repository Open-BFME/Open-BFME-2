// cl: /MD /EHsc
// ?OnBuildQueueIconSlotRightClicked@Rva005E7C19@@QAEXH@Z @0x005E712A 53B
// Virtual slot 1 (offset 0x4) of vtable 0x00877F14 (class of ??1Rva005E7C19@@UAE@XZ).
// Emits GameMessage 0x6AE via MessageStreamSubsystem slot 0x48 then two integer args:
// chain this+4 -> +0x18 -> +0x18 int, plus this+8 int. Single int param unused (ret 4).
// Evidence: packet disasm with rowed appendIntegerArgument 0x0030F936 and global
// MessageStreamSubsystem VA 0x00A00950; vtable from Rva005E7C19Dtor.cpp; /O1 flags from donor TU.
#include "../../../Include/Common/MessageStream.h"
extern class MessageStream *TheMessageStream;
struct ChainB005E712A
{
	char m_pad[0x18];
	int m_18;
};
struct ChainA005E712A
{
	char m_pad[0x18];
	ChainB005E712A *m_18;
};
namespace StrategicHUD { class BuildQueueIconSlot; }
namespace StrategicInGameUI { class BuildQueueDetailsPanel { public: class Impl; }; class BuildQueueDetailsPanel::Impl { public: class Icon; }; }
class StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon
{
public:
	virtual void OnBuildQueueIconSlotLeftClicked(StrategicHUD::BuildQueueIconSlot *);
	virtual void OnBuildQueueIconSlotRightClicked(StrategicHUD::BuildQueueIconSlot *);
	virtual void OnBuildQueueIconSlotRollOut(StrategicHUD::BuildQueueIconSlot *);
	virtual void OnBuildQueueIconSlotRollOver(StrategicHUD::BuildQueueIconSlot *);
	virtual void rva005E715F(StrategicHUD::BuildQueueIconSlot *);
	virtual void rva005E7166(StrategicHUD::BuildQueueIconSlot *);
private:
	ChainA005E712A *m_04;
	int m_08;
};
void StrategicInGameUI::BuildQueueDetailsPanel::Impl::Icon::OnBuildQueueIconSlotRightClicked(StrategicHUD::BuildQueueIconSlot *unused)
{
	(void)unused;
	GameMessage *msg = TheMessageStream->appendMessage(0x6AE);
	msg->appendIntegerArgument(m_04->m_18->m_18);
	msg->appendIntegerArgument(m_08);
}

// ?rva0029AB48@InGameUI@@QAEXEPAE@Z
// partial score=0.93 date=2026-10-06
// cl: /DNDEBUG /MD /O1 /arch:SSE /G7
// ?rva0029AB48@InGameUI@@QAE_NEPAE@Z, retail 0x0029AB48, 187 bytes.
// Stored callback table entries are adjacent to InGameUI methods including preDraw; the exact
// callback purpose is unproven. Retail reads/writes the byte fields below and emits message 0x469.

class GameMessage
{
public:
	void appendIntegerArgument(int value);
};

class MessageStream
{
public:
#define MESSAGE_SLOT(n) virtual void slot##n();
	MESSAGE_SLOT(0) MESSAGE_SLOT(1) MESSAGE_SLOT(2) MESSAGE_SLOT(3)
	MESSAGE_SLOT(4) MESSAGE_SLOT(5) MESSAGE_SLOT(6) MESSAGE_SLOT(7)
	MESSAGE_SLOT(8) MESSAGE_SLOT(9) MESSAGE_SLOT(10) MESSAGE_SLOT(11)
	MESSAGE_SLOT(12) MESSAGE_SLOT(13) MESSAGE_SLOT(14) MESSAGE_SLOT(15)
	MESSAGE_SLOT(16) MESSAGE_SLOT(17)
#undef MESSAGE_SLOT
	virtual GameMessage *newMessage(int id);
};

extern MessageStream *MessageStreamSubsystem;

class InGameUI
{
public:
#define UI_SLOT(n) virtual void slot##n();
	UI_SLOT(0) UI_SLOT(1) UI_SLOT(2) UI_SLOT(3) UI_SLOT(4) UI_SLOT(5)
	UI_SLOT(6) UI_SLOT(7) UI_SLOT(8) UI_SLOT(9) UI_SLOT(10) UI_SLOT(11)
	UI_SLOT(12) UI_SLOT(13) UI_SLOT(14) UI_SLOT(15) UI_SLOT(16) UI_SLOT(17)
	UI_SLOT(18) UI_SLOT(19) UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23)
	UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29)
	UI_SLOT(30) UI_SLOT(31) UI_SLOT(32) UI_SLOT(33) UI_SLOT(34) UI_SLOT(35)
	UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39) UI_SLOT(40) UI_SLOT(41)
	UI_SLOT(42)
	virtual void slot43(int value);
	UI_SLOT(44) UI_SLOT(45) UI_SLOT(46) UI_SLOT(47) UI_SLOT(48) UI_SLOT(49)
	UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53) UI_SLOT(54) UI_SLOT(55)
	UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59) UI_SLOT(60) UI_SLOT(61)
	UI_SLOT(62) UI_SLOT(63) UI_SLOT(64) UI_SLOT(65) UI_SLOT(66) UI_SLOT(67)
	UI_SLOT(68) UI_SLOT(69) UI_SLOT(70) UI_SLOT(71) UI_SLOT(72) UI_SLOT(73)
	UI_SLOT(74) UI_SLOT(75) UI_SLOT(76) UI_SLOT(77) UI_SLOT(78) UI_SLOT(79)
	UI_SLOT(80)
	virtual void slot81();
#undef UI_SLOT
	unsigned char m_pad04[0x11];
	unsigned char m_flag15;
	unsigned char m_flag16;
	unsigned char m_pad17[0x8b0 - 0x17];
	unsigned char m_flag8b0;
	unsigned char m_pad8b1[7];
	unsigned char m_flag8b8;
	unsigned char m_flag8b9;
	unsigned char m_flag8ba;
	unsigned char m_flag8bb;
	unsigned char m_flag8bc;
	unsigned char m_flag8bd;
	unsigned char m_flag8be;
	unsigned char m_flag8bf;
	unsigned char m_flag8c0;
	unsigned char m_flag8c1;
	unsigned char m_flag8c2;

	void rva0029AB48(unsigned char value, unsigned char *out);
};

void InGameUI::rva0029AB48(unsigned char value, unsigned char *out)
{
	bool active = m_flag15 != 0 && m_flag16 != 0;
	*out = value;
	if (active) {
		if (m_flag15 != 0) {
		 if (m_flag16 == 0) {
			slot43(0);
			slot81();
			m_flag8b8 = 0;
			m_flag8b9 = 0;
			m_flag8b0 = 0;
			m_flag8ba = 0;
			m_flag8bb = 0;
			m_flag8bc = 0;
			m_flag8bd = 0;
			m_flag8be = 0;
			m_flag8bf = 0;
			m_flag8c0 = 0;
			m_flag8c1 = 0;
			m_flag8c2 = 0;
			GameMessage *message = MessageStreamSubsystem->newMessage(0x469);
			message->appendIntegerArgument(0);
			message->appendIntegerArgument(1);
		 }
		}
	}
}

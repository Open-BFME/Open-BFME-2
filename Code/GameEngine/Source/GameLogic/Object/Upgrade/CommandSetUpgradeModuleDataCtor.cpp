// cl: /O1 /MD /GX /DNDEBUG /Oy-
//
// ??0CommandSetUpgradeModuleData@@QAE@XZ, retail 0x00255652, 70 bytes.
// EH ctor over the rowed OpenContainModuleData base (0x253487): the
// compiler-emitted vtable store lands mid-init (after the hoisted member
// lea, before the member zero and the string call), so the classes are
// virtual with declared-only dtors and no source store (Devastate
// precedent). CommandSet at +0x118 is an AsciiString: implicit default
// construction zeroes it (the member dtor is declared-only, which arms
// state 1 with no code) and the body assigns the global empty string
// (VA 0xDE0878, DIR32-masked push) through the folded AsciiString op=
// (pinned at 0x366F0). Own table 0x008572C0 holds exactly CommandSet at
// +0x118; the CommandSetUpgrade pool key at 0x4B3A4B ends where the rowed
// proc begins; the EH factory at 0x255698 news 0x11C and is the only raw
// caller.

class OpenContainModuleData
{
public:
	OpenContainModuleData();
	virtual ~OpenContainModuleData();

private:
	unsigned char m_pad[0x118 - 4];
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString &operator=(const AsciiString &other);
	~AsciiString();

private:
	void *m_data;
};

extern AsciiString g_emptyAsciiString;

class CommandSetUpgradeModuleData : public OpenContainModuleData
{
public:
	CommandSetUpgradeModuleData();
	virtual ~CommandSetUpgradeModuleData();

private:
	AsciiString m_commandSet; // +0x118
};

// ??0CommandSetUpgradeModuleData@@QAE@XZ @0x255652
CommandSetUpgradeModuleData::CommandSetUpgradeModuleData()
{
	m_commandSet = g_emptyAsciiString;
}

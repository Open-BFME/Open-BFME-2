// cl: /O1 /MD /GX /DNDEBUG /Oy-
//
// ??0TooltipUpgradeModuleData@@QAE@XZ, retail 0x0025588E, 91 bytes.
// EH ctor over the rowed OpenContainModuleData base (0x253487): the
// compiler-emitted vtable store lands mid-init, so the classes are virtual
// with declared-only dtors and no source store (Devastate precedent).
// DisplayName at +0x118 and Description at +0x11C are AsciiStrings: implicit
// default construction zeroes both, then the body assigns the global empty
// string (VA 0xDE0878, DIR32-masked push) through the folded AsciiString
// op= (pinned at 0x366F0) twice. Own table 0x00858C38 holds exactly
// DisplayName at +0x118 plus Description at +0x11C; the TooltipUpgrade pool
// key tail at 0x4B7A13 ends where the rowed proc begins; the EH factory at
// 0x2558E9 news 0x120 and is the only raw caller.

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

class TooltipUpgradeModuleData : public OpenContainModuleData
{
public:
	TooltipUpgradeModuleData();
	virtual ~TooltipUpgradeModuleData();

private:
	AsciiString m_displayName; // +0x118
	AsciiString m_description; // +0x11C
};

// ??0TooltipUpgradeModuleData@@QAE@XZ @0x25588E
TooltipUpgradeModuleData::TooltipUpgradeModuleData()
{
	m_displayName = g_emptyAsciiString;
	m_description = g_emptyAsciiString;
}

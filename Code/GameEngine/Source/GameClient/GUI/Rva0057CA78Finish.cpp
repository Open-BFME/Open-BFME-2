// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?GetNextSelectablePlayer@Rva0057CA78@@QAEHH@Z retail 0x0057CA78 142B
// Evidence: this+0x18 via rowed 0x0043DA65 to GameInfo; virtual bool gate at
// vtable +0x30 and int getter at vtable +0x34; rowed getConstSlot (0x003FF2BE)
// and GameSlot::isAI (0x003FF127); slot startPos at +0x10 and playerTemplate at
// +0x18; callers 0x0043E705 / 0x00442EC1 / 0x00442F18 / 0x0057CCC6.
// The identical body with `slot` declared outside the loop allocates the loop
// counter to edi and slot to ebx; declaring the slot pointer inside the loop
// and keeping the compound short-circuit guard flips that to retail's ebx/edi
// and is byte-exact.
class GameSlot;
class AsciiString;
class Rva0057CC15Op;

class Rva0043DA65
{
public:
	int rva0043DA65();
	int m_00; // +0x00
	int m_refs; // +0x04 +0x04, the reference count
	int m_08; // +0x08
};

class GameSlot
{
public:
	bool isAI() const;
	virtual void reset();
	int m_state; // +0x04
	char m_pad08[0x4];
	int m_color; // +0x0C +0x0C
	int m_startPos; // +0x10 +0x10, the start region id, -1 for none
	char m_pad14[0x4];
	int m_playerTemplate; // +0x18 +0x18
};

class GameInfo
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual bool amIHost() const = 0;	// +0x30
	virtual int v34() const = 0;	// +0x34
	AsciiString getMap() const;		// 0x0023E943
	GameSlot *getSlot(int index);		// 0x003FF29F
	const GameSlot *getConstSlot(int slotNum) const;	// 0x003FF2BE

	unsigned char m_pad04[0x10 - 0x4];
	bool m_selectStartPoint;	// +0x10
	unsigned char m_pad11[0x58 - 0x11];
	int m_campaign;		// +0x58, a campaign manager index
	unsigned char m_pad5c[0x8c - 0x5c];
	bool m_8c;		// +0x8C, no region picks while set
	unsigned char m_pad8d[0xc8 - 0x8d];
	int m_c8;		// +0xC8
};

struct Rva0057CA78
{
	char m_pad0[0x18];
	Rva0043DA65 *m_ptr18;
	int GetNextSelectablePlayer(int start);
};

int Rva0057CA78::GetNextSelectablePlayer(int start)
{
	GameInfo *info = (GameInfo *)m_ptr18->rva0043DA65();
	if (!info)
		return -1;
	if (!info->amIHost())
	{
		int local = info->v34();
		const GameSlot *slot = info->getConstSlot(local);
		if (!slot)
			return -1;
		if (slot->m_startPos != -1)
			return -1;
		return local;
	}
	for (int i = start; i < 8; ++i)
	{
		const GameSlot *slot = info->getConstSlot(i);
		if (slot && slot->m_startPos == -1 && slot->m_playerTemplate != -2 &&
			(i == info->v34() || slot->isAI()))
		{
			return i;
		}
	}
	return -1;
}

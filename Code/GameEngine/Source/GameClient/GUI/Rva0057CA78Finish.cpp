// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?rva0057CA78@Rva0057CA78@@QAEHH@Z retail 0x0057CA78 142B
// Evidence: this+0x18 via rowed 0x0043DA65 to GameInfo; virtual bool gate at
// vtable +0x30 and int getter at vtable +0x34; rowed getConstSlot (0x003FF2BE)
// and GameSlot::isAI (0x003FF127); slot startPos at +0x10 and playerTemplate at
// +0x18; callers 0x0043E705 / 0x00442EC1 / 0x00442F18 / 0x0057CCC6.
// The identical body with `slot` declared outside the loop allocates the loop
// counter to edi and slot to ebx; declaring the slot pointer inside the loop
// and keeping the compound short-circuit guard flips that to retail's ebx/edi
// and is byte-exact.
class Rva0043DA65
{
public:
	int rva0043DA65();
};

class GameSlot
{
public:
	virtual void reset();
	bool isAI() const;
	int m_state; // +0x04
	char m_pad08[4]; // +0x08..+0x0B
	int m_color; // +0x0C
	int m_startPos; // +0x10
	char m_pad14[4]; // +0x14
	int m_playerTemplate; // +0x18
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
	virtual bool v30() const = 0;
	virtual int v34() const = 0;
	const GameSlot *getConstSlot(int slotNum) const;
};

struct Rva0057CA78
{
	char m_pad0[0x18];
	Rva0043DA65 *m_ptr18;
	int rva0057CA78(int start);
};

int Rva0057CA78::rva0057CA78(int start)
{
	GameInfo *info = (GameInfo *)m_ptr18->rva0043DA65();
	if (!info)
		return -1;
	if (!info->v30())
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

// ?rva0043DF22@Rva0043DF22@@QAEHXZ
// partial score=0.9 date=2026-10-08
// cl: /DNDEBUG /MD /EHsc
// ?rva0043DF22@Rva0043DF22@@QAEHXZ 0x0043DF22 79B. Counts the first eight game
// slots of the info object at +0x5C that are human, not observers, and have a
// nonzero flag byte at +0x08. Returns 0 when the info object is missing.
class GameSlot
{
public:
	bool isHuman() const;
	bool isObserver() const;
	unsigned char m_pad00[8];
	unsigned char m8; // +0x08
};

class GameInfo
{
public:
	GameSlot *getSlot(int index);
};

class Rva0043DA65
{
public:
	int rva0043DA65();
};

class Rva0043DF22
{
public:
	int rva0043DF22();
private:
	unsigned char m_pad00[0x5C];
	Rva0043DA65 *m_info; // +0x5C
};

int Rva0043DF22::rva0043DF22()
{
	int count = 0;
	int i = 0;
	GameInfo *info = reinterpret_cast<GameInfo *>(m_info->rva0043DA65());
	if (!info)
		return 0;
	for (; i < 8; ++i)
	{
		GameSlot *slot = info->getSlot(i);
		if (slot && slot->isHuman() && !slot->isObserver() && slot->m8 != 0)
			++count;
	}
	return count;
}

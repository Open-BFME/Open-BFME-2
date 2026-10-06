// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004FD9CF@GameSlot@@QBEHXZ @0x004FD9CF 27B
// GameSlot human-plus-flag predicate beside isHuman 0x003FF0F1: calls rowed
// isHuman on the same this then tests the flag byte at +0x48. Evidence:
// unlock lane (unblocks 0x004FE35F 0x00520792); 5 callers pass this in ecx.

class GameSlot
{
public:
	bool isHuman() const;
	int rva004FD9CF() const;

private:
	char m_pad00[0x48];
	bool m_flag48;
};

int GameSlot::rva004FD9CF() const
{
	if (isHuman()) {
		if (m_flag48 != 0)
			return true;
	}
	return false;
}

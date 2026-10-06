// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva00248D35@Rva00248D35@@QAEXHH@Z, retail 0x00248D35, 43 bytes.
// Index*0x1D0 plus GameSlot::isHuman at +0xDC plus set int at +0x2A8.
// Evidence: imul 0x1D0 plus lea plus call isHuman plus ret 8,
// callers at 0x0024A4CA 0x0024A4E1 0x005820C1.

class GameSlot
{
public:
	bool isHuman() const;
};

class Rva00248D35
{
public:
	void rva00248D35(int index, int value);
};

void Rva00248D35::rva00248D35(int index, int value)
{
	char *base = (char *)this;
	GameSlot *slot = (GameSlot *)(base + index * 0x1D0 + 0xDC);
	if (slot->isHuman())
		*(int *)(base + index * 0x1D0 + 0x2A8) = value;
}

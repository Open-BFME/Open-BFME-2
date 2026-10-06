// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??0Rva004F6318Entry@@QAE@PBHABVRva004F6093Holder@@@Z, retail 0x004F6318,
// 29 bytes. Entry ctor for sorted vector: int key at +0 via pointer deref,
// Holder value at +4 via rowed copy ctor 0x004F6093. Same 8-byte entry layout
// as Rva0040CB11Entry at 0x0040CB11 (27B direct int) but key comes through a
// pointer here. Evidence: single caller at 0x004F6A2B in FUN_008f6a1a.

class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other);
};

class Rva004F6318Entry
{
public:
	Rva004F6318Entry(const int *keyPtr, const Rva004F6093Holder &val);
private:
	int m_first;
	Rva004F6093Holder m_second;
};

Rva004F6318Entry::Rva004F6318Entry(const int *keyPtr, const Rva004F6093Holder &val) : m_first(*keyPtr), m_second(val)
{
}

// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?set@Rva0039D7A6Setter@@QAEXPBURva0039D7A6Src@@@Z, retail 0x0039D7A6 (27B).
//
// Leaf thiscall: sets a flag byte at +0x324 to 1 and copies a 12-byte value
// to +0x328 (three dword movsd under /O1).
//
// Provenance: sole caller is the 0x005AA751 site inside UNCLAIMED
// FUN_009aa740 (gap candidate 0x005AA740 in Rva005DCB27Derived.cpp). Adjacent
// rows read the same members: ?get@Rva0039D7C1ByteField@@QBEEXZ reads the
// byte at +0x324 and ?get@Rva0039D7C8LeaGetter@@QBEPAXXZ returns +0x328,
// with Team::getControllingPlayer at 0x0039D7CF immediately after. Owning
// class is otherwise unknown, so this uses an address-honest Rva vehicle.

struct Rva0039D7A6Src
{
	int m00;
	int m04;
	int m08;
};

class Rva0039D7A6Setter
{
public:
	void set(const Rva0039D7A6Src *src);

private:
	char m_pad[0x324];
	unsigned char m_flag324;
	char m_pad325[3];
	Rva0039D7A6Src m_val328;
};

void Rva0039D7A6Setter::set(const Rva0039D7A6Src *src)
{
	m_flag324 = 1;
	m_val328 = *src;
}

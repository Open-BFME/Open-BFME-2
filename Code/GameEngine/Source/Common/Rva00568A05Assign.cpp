// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??4Rva00568A05@@QAEAAV0@ABV0@@Z @0x00568A05 27B: 10-byte copy-assign (4+4+2)
// Two dwords at +0/+4 and word at +8; returns this. Neighbours 0x00568920
// 0x00568A20 share /O1 /G7; caller at 0x00569CA0 unclaimed.
class Rva00568A05
{
public:
	Rva00568A05 &operator=(const Rva00568A05 &other);

private:
	int m00; // +0
	int m04; // +4
	short m08; // +8
};

Rva00568A05 &Rva00568A05::operator=(const Rva00568A05 &other)
{
	m00 = other.m00;
	m04 = other.m04;
	m08 = other.m08;
	return *this;
}

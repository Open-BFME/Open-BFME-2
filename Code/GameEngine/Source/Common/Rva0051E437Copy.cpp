// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0051E437@Rva0051E437@@QAEAAV1@ABV1@@Z @0x0051E437 33B: __thiscall copy of three words at +4/+6/+8; caller 0x0051E939 loops with stride 0xC
class Rva0051E437
{
public:
	Rva0051E437 &rva0051E437(const Rva0051E437 &src);
private:
	int m00;
	unsigned short m04;
	unsigned short m06;
	unsigned short m08;
};
Rva0051E437 &Rva0051E437::rva0051E437(const Rva0051E437 &src)
{
	m04 = src.m04;
	m06 = src.m06;
	m08 = src.m08;
	return *this;
}

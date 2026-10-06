// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??4Rva0040D0A4Entry@@QAEAAV0@ABV0@@Z, retail 0x0040D0A4, 29 bytes.
// 8-byte entry assignment: int at +0 plus Rva002B2F97 holder at +4 via rowed
// assign 0x002B2F97. Same layout as Rva0040CB11Entry but copy-assigns.
// Callers at 0x0040D13D 0x0040D149 0x0040D19C 0x0040D1AC 0x0040D20D.

class Rva002B2F97
{
public:
	Rva002B2F97 &operator=(const Rva002B2F97 &other);
};

class Rva0040D0A4Entry
{
public:
	Rva0040D0A4Entry &operator=(const Rva0040D0A4Entry &other);

private:
	int m_first;
	Rva002B2F97 m_second;
};

Rva0040D0A4Entry &Rva0040D0A4Entry::operator=(const Rva0040D0A4Entry &other)
{
	m_first = other.m_first;
	m_second = other.m_second;
	return *this;
}

// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?get@Rva002E063B@@QBEHXZ @0x002E063B 13B.
// Honest address name: __thiscall sum getter with 2 callers and no callees.
// Byte-exact model: return m_264 + m_1c4.
// Evidence: 2 UNCLAIMED callers 0x002D695F 0x00574681;
// prev 0x002E062E setter (defaults) and next 0x002E0668 clearer (/O1).

struct Rva002E063B
{
	char m_pad[0x1c4];
	int m_1c4;
	char m_pad2[0x264 - 0x1c8];
	int m_264;
	int get() const;
};

int Rva002E063B::get() const
{
	return m_264 + m_1c4;
}

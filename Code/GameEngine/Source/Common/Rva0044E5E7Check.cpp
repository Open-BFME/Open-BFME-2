// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0044E5E7@Rva0044E5E7@@QAE_NXZ @0x0044E5E7 38B
// Predicate over +0x30 +0x04-subject +0x7D: unlock lane; callers at
// 0x0045221D 0x004522B5 in 0x00451FA2; prev DispByteFieldSetters next
// Rva0044E633FilteredFind; returns true only when +0x30==4 and sub +0x84!=0
// with +0x7D gate when sub +0xA8 set.
class Sub0044E5E7
{
public:
	char m_pad00[0x84];
	int m_84;
	int m_88;
	char m_pad8C[0xA8 - 0x8C];
	unsigned char m_a8;
};

class Rva0044E5E7
{
public:
	bool rva0044E5E7();
	bool rva0044E60D();
private:
	char m_pad00[4];
	Sub0044E5E7 *m_ptr04;
	char m_pad08[0x30 - 0x08];
	int m_30;
	char m_pad34[0x7D - 0x34];
	unsigned char m_7D;
};

bool Rva0044E5E7::rva0044E5E7()
{
	Sub0044E5E7 *sub = m_ptr04;
	if (m_30 != 4)
		goto fail;
	if (sub->m_a8 != 0)
	{
		if (m_7D != 0)
			goto fail;
	}
	if (sub->m_84 != 0)
		return true;
fail:
	return false;
}

// ?rva0044E60D@Rva0044E5E7@@QAE_NXZ @0x0044E60D 38B
// Sibling of 0x0044E5E7 in the same TU: +0x30==3 (vs 4) and sub +0x88!=0
// (vs +0x84); same +0x7D gate and +0xA8 check. Evidence: unlock lane;
// caller at 0x0045227F in 0x00451FA2; abuts prev 0x0044E5E7.
bool Rva0044E5E7::rva0044E60D()
{
	Sub0044E5E7 *sub = m_ptr04;
	if (m_30 != 3)
		goto fail;
	if (sub->m_a8 != 0)
	{
		if (m_7D != 0)
			goto fail;
	}
	if (sub->m_88 != 0)
		return true;
fail:
	return false;
}

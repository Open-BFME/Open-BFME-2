// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva00538B2F@Rva00538B2F@@QAEPAURva0052A28EDwordField@@PAU2@@Z placeholder, retail 0x00538B2F, 25 bytes.
// Search list via head at +8 and next at +0x208 through rowed getter 0x0052A28E for key.
// Evidence: callers 0x00538B51 plus 0x00538B9F; prev QuickMatchScreenBaseSlot4 /O1 /DNDEBUG next AsciiStringFoldDeleters /O1 /MD.
struct Rva0052A28EDwordField
{
	int get() const;
	char m_lead[0x208];
	int m_next;
};

struct Rva00538B2F
{
	Rva0052A28EDwordField *rva00538B2F(Rva0052A28EDwordField *key);
	char m_pad[8];
	Rva0052A28EDwordField *m_head;
};

Rva0052A28EDwordField *Rva00538B2F::rva00538B2F(Rva0052A28EDwordField *key)
{
	Rva0052A28EDwordField *cur = m_head;
	while (cur) {
		if (cur == key)
			return cur;
		cur = (Rva0052A28EDwordField *)cur->get();
	}
	return 0;
}

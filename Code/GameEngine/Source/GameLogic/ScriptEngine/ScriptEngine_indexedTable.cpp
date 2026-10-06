// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Indexed accessors over the 20B-stride table at this+0xC, decoded from
// retail (ScriptEngine cluster at 0x0020487E/0x0020488E).
// - 0x0020487E (16B): imul idx*0x14, return the leading dword of the slot.
// - 0x0020488E (20B): same index, return the dword at slot+0x10 plus 4.
// /G7 carries the imul (IMUL law: /O1 alone strength-reduces i*20 to lea).
// Human-readable names; opaque holder (true class unproven; the 53B ctor
// at 0x00204848 builds real sub-objects at +4/+0xC via 0x33A40A/0x33A410).

struct Rva002048x0Elem
{
	int m_first;
	char m_pad[12];
	int m_field10;
};

class Rva002048xxHolder
{
public:
	char m_pad[0xC];
	Rva002048x0Elem *m_items;
	int rva0020487E(int index);
	int rva0020488E(int index);
};

int Rva002048xxHolder::rva0020487E(int index)
{
	return m_items[index].m_first;
}

int Rva002048xxHolder::rva0020488E(int index)
{
	return m_items[index].m_field10 + 4;
}

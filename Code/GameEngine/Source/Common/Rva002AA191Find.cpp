// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva002AA191@Rva002AA191@@QAEHPBVObject@@@Z @0x002AA191 46B: 10-slot find via Rva004D6BCD::rva004D6BCD returns index or -1; callers 0x00273C6C 0x00278FEA; unblocks 0x00273C47.
class Object;
class Rva004D6BCD
{
public:
	bool rva004D6BCD(Object const* obj) const;
};

class Rva002AA191
{
public:
	int rva002AA191(Object const* obj);
	Rva004D6BCD* rva002AA176(int index);
	void rva002AA1BF(void *arg);
private:
	unsigned char m_pad[0x708];
	Rva004D6BCD* m_entries[10];
};

int Rva002AA191::rva002AA191(Object const* obj)
{
	for (int i = 0; i < 10; ++i) {
		if (m_entries[i]->rva004D6BCD(obj))
			return i;
	}
	return -1;
}

Rva004D6BCD* Rva002AA191::rva002AA176(int index)
{
	return (index < 0 || index >= 10) ? 0 : m_entries[index];
}
class Rva004D6BF0
{
public:
	void rva004D6BF0(void *arg);
};
void Rva002AA191::rva002AA1BF(void *arg)
{
	for (int i = 0; i < 10; ++i) {
		Rva004D6BF0 *entry = (Rva004D6BF0 *)m_entries[i];
		if (entry)
			entry->rva004D6BF0(arg);
	}
}

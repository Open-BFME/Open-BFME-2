// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// ?rva0033070E@Rva0033070E@@QAEPAURva0033070EEntry@@ABV?$StringBase@D@@@Z @0x0033070E 46B
// Unlock lane: linear find over pointer array at +0x10/+0x14 comparing
// StringBase at +0x18 via rowed compare 0x000069D6. Caller 0x003BB14B.
template <class T> class StringBase {
public:
	int compare(const StringBase &other) const;
};
struct Rva0033070EEntry {
	char m_pad[0x18];
	StringBase<char> m_name; // +0x18
};
class Rva0033070E {
public:
	Rva0033070EEntry *rva0033070E(const StringBase<char> &key);
private:
	char m_pad0[0x10];
	Rva0033070EEntry **m_start; // +0x10
	Rva0033070EEntry **m_finish; // +0x14
};

Rva0033070EEntry *Rva0033070E::rva0033070E(const StringBase<char> &key)
{
	for (Rva0033070EEntry **cur = m_start; cur != m_finish; ++cur) {
		if ((*cur)->m_name.compare(key) == 0)
			return *cur;
	}
	return 0;
}

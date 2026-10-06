// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?find@Rva0040CB3AIndexedField@@QBEHH@Z @0x0040CB3A 63B and ?findBySecond@Rva0040CC1BIndexedField@@QBEHH@Z @0x0040CC1B 33B
// and ?get@Rva0040CB3AIndexedField@@QBEHH@Z @0x0040CBB8 31B
// Binary search over sorted 8-byte entries at +0x40/+0x44 keyed by first dword; returns index or -1.
// Linear reverse lookup by second dword; returns first or 0. Keyed value getter via binary search; 0 on miss.
// Evidence: 3 callers of 0x40CB3A incl 0x0040CBBF and 0x0040CBE5; 1 caller of 0x40CC1B at 0x00503B5A; 18 callers of 0x40CBB8;
// shared +0x40/+0x44 vector layout with twin getters 0x0040CC0E/0x0040CB2C.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
struct Rva0040CB3AEntry
{
	int first;
	int second;
};

class Rva0040CB3AIndexedField
{
public:
	int find(int key) const;
	int get(int key) const;
	int rva0040CB79(struct ArmySummaryEntry *key) const;
private:
	char m_pad[0x40];
	Rva0040CB3AEntry *m_begin;
	Rva0040CB3AEntry *m_end;
};

int Rva0040CB3AIndexedField::find(int key) const
{
	const Rva0040CB3AEntry *low = m_begin;
	const Rva0040CB3AEntry *high = m_end;
	while (low != high) {
		const Rva0040CB3AEntry *mid = low + (high - low) / 2;
		if (key == mid->first)
			return mid - m_begin;
		if (key > mid->first)
			low = mid + 1;
		else
			high = mid;
	}
	return -1;
}

int Rva0040CB3AIndexedField::get(int key) const
{
	int idx = find(key);
	if (idx < 0)
		return 0;
	return m_begin[idx].second;
}

class ArmySummaryEntry
{
public:
	bool rva0040C3BB(const ArmySummaryEntry *other);
};

int Rva0040CB3AIndexedField::rva0040CB79(ArmySummaryEntry *key) const
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_end - (char *)m_begin) >> 3); ++i) {
		_ReadWriteBarrier();
		if (key->rva0040C3BB((const ArmySummaryEntry *)m_begin[i].second))
			return (int)i;
	}
	return -1;
}

class Rva0040CC1BIndexedField
{
public:
	int findBySecond(int val) const;
private:
	char m_pad[0x40];
	Rva0040CB3AEntry *m_begin;
	Rva0040CB3AEntry *m_end;
};

int Rva0040CC1BIndexedField::findBySecond(int val) const
{
	Rva0040CB3AEntry *end = m_end;
	Rva0040CB3AEntry *cur = m_begin;
	while (cur != end) {
		if (cur->second == val)
			return cur->first;
		++cur;
	}
	return 0;
}

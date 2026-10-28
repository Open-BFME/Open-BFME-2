// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva005B61B3@Rva005B61B3@@QAE_NPAX0@Z @0x005B61B3 189B.
// Honest-address __thiscall comparator with two sort keys at +0/+4.
// Takes two element pointers (ret 8), compares Unicode name at +8 via
// rowed StringBase<G>::compareNoCase at 0x6AA4, version ((major-minor)*100)
// from +C/+10, and byte flag at +0x48. Loops over both keys: equal on the
// first continues to the second, otherwise returns <0 (even keys) or >=0
// (odd keys). Callers are the unclaimed sort helpers around 0x5B6270 and
// the list-box fill at 0x5B6755; prev is Disp8DwordClearers /O1.

template <typename T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const;
private:
	void *m_data;
};

struct Rva005B61B3Elem
{
	char m_00[8];
	StringBase<unsigned short> m_name;
	int m_0C;
	int m_10;
	char m_14[0x48 - 0x14];
	unsigned char m_48;
};

class Rva005B61B3
{
public:
	bool rva005B61B3(void *a_raw, void *b_raw);
private:
	int m_key0;
	int m_key1;
};

bool Rva005B61B3::rva005B61B3(void *a_raw, void *b_raw)
{
	Rva005B61B3Elem *leftHero = (Rva005B61B3Elem *)a_raw;
	Rva005B61B3Elem *rightHero = (Rva005B61B3Elem *)b_raw;
	int nameDiff = leftHero->m_name.compareNoCase(rightHero->m_name);
	int verDiff = (leftHero->m_0C - rightHero->m_0C) * 100 + (leftHero->m_10 - rightHero->m_10);
	int flagDiff = (int)leftHero->m_48 - (int)rightHero->m_48;
	int crit = m_key0;
	for (int i = 0; i < 2; ++i) {
		switch (crit) {
		case 5:
			if (verDiff == 0) {
				if (i == 0)
					break;
			}
			return verDiff >= 0;
		case 4:
			if (verDiff == 0) {
				if (i == 0)
					break;
			}
			return verDiff < 0;
		case 2:
			if (nameDiff == 0) {
				if (i == 0)
					break;
			}
			return nameDiff < 0;
		case 3:
			if (nameDiff == 0) {
				if (i == 0)
					break;
			}
			return nameDiff >= 0;
		case 1:
			if (flagDiff == 0) {
				if (i == 0)
					break;
			}
			return flagDiff >= 0;
		case 0:
			if (flagDiff == 0) {
				if (i == 0)
					break;
			}
			return flagDiff < 0;
		default:
			break;
		}
		crit = m_key1;
	}
	return false;
}
